using System;
using System.Linq;
using System.Text;
using System.Data.SQLite;
using System.Collections.Generic;
using System.Reflection;
using System.ComponentModel;
using System.Windows.Forms;
using System.Threading;

namespace Database.GDB
{
    public class DB : IDisposable
    {
        #region Vars
        private string _fileName;

        private bool _disposed = false;

        private SQLiteConnection _connection;

        private Dictionary<Type, object> _queue = new Dictionary<Type, object>();
        private Dictionary<Type, object> _typeBaseTable = new Dictionary<Type, object>();
        #endregion

        #region Vars - Data
        private Dictionary<Operators, string> _operatorFormat = new Dictionary<Operators, string>() { 
            { Operators.Contains,           "\"{0}\" LIKE '%{1}%'" },
            { Operators.EndsWith,           "\"{0}\" LIKE '%{1}'" },
            { Operators.Equals,             "\"{0}\" = '{1}'" },
            { Operators.GreaterThan,        "\"{0}\" > '{1}'" },
            { Operators.GreaterThanOrEqual, "\"{0}\" >= '{1}'" },
            { Operators.LessThan,           "\"{0}\" < '{1}'" },
            { Operators.LessThanOrEqual,    "\"{0}\" <= '{1}'" },
            { Operators.NotEquals,          "\"{0}\" != '{1}'" },
            { Operators.StartsWith,         "\"{0}\" LIKE '{1}%'" },
            { Operators.Like,               "\"{0}\" LIKE '{1}'" }
        };

        Dictionary<Type, string> _types = new Dictionary<Type, string>() { 
            { typeof(String),   "TEXT" },
            { typeof(DateTime), "DATETIME" },
            { typeof(Decimal),  "NUMERIC" },
            { typeof(Boolean),  "BOOLEAN" },
            { typeof(Byte),     "tinyint" },
            { typeof(Byte[]),   "BLOB" },
            { typeof(Double),   "double" },
            { typeof(Int16),    "SMALLINT" },
            { typeof(Int32),    "INT" },
            { typeof(Int64),    "INTEGER" },
            { typeof(Single),   "FLOAT" }
        };

        Dictionary<Type, string> _defaults = new Dictionary<Type, string>() { 
            { typeof(String),   "" },
            { typeof(DateTime), "0000-01-01 00:00:00" },
            { typeof(Decimal),  "0" },
            { typeof(Boolean),  "0" },
            { typeof(Byte),     "0" },
            { typeof(Byte[]),   "0" },
            { typeof(Double),   "0" },
            { typeof(Int16),    "0" },
            { typeof(Int32),    "0" },
            { typeof(Int64),    "0" },
            { typeof(Single),   "0" }
        };
        #endregion

        #region Init
        public DB(string fileName)
        {
            _fileName = fileName;
        }
        #endregion

        #region Private Member
        private DbTable<T> _getTable<T>()
        {
            Type type = typeof(T);

            if (!_typeBaseTable.ContainsKey(type))
            {
                this.RegisterType<T>();
            }

            return (DbTable<T>)_typeBaseTable[type];
        }

        private string _getValue(object value)
        {
            string str = "NULL";

            if (value != null)
            {
                switch (value.GetType().Name)
                {
                    case "Single":
                    case "Double":
                    case "Decimal":
                        str = value.ToString().Replace(',', '.');
                        break;
                    case "DateTime":
                        str = ((DateTime)value).ToString("s");
                        break;
                    case "Byte[]":
                        str = BitConverter.ToString((byte[])value).Replace("-", "");
                        break;
                    default:
                        str = value.ToString();
                        break;
                }
            }

            return str;
        }
        #endregion

        #region Private Member - Where
        private string _generateWhere(IEnumerable<DbExpression> where)
        {
            StringBuilder sb = new StringBuilder();

            foreach (DbExpression ex in where)
            {
                if (sb.Length != 0)
                {
                    sb.Append(" AND ");
                }

                sb.AppendFormat(
                    _operatorFormat[ex.Operator],
                    ex.Column,
                    _getValue(ex.Value)
                );
            }

            return sb.ToString();
        }
        #endregion

        #region Private Member - Query
        private DbReader<T> _query<T>(string sql, bool empty)
        { 
            SQLiteTransaction transaction = null;
            SQLiteCommand command = _connection.CreateCommand();

            command.CommandText = sql;

            try
            {
                if (empty)
                {
                    DbReader<T> reader = null;

                    transaction = _connection.BeginTransaction();
                    command.Transaction = transaction;

                    command.ExecuteNonQuery();

                    command.CommandText = "SELECT last_insert_rowid();";
                    reader = new DbReader<T>(this, command.ExecuteReader());

                    transaction.Commit();

                    return reader;
                }
                else
                {
                    return new DbReader<T>(this, command.ExecuteReader());
                }
            }
            catch (Exception e)
            {
                MessageBox.Show("Error: " + e.Message);

                return null;
            }
            finally
            {
                if (transaction != null) transaction.Dispose();
                command.Dispose();
            }        
        }
        #endregion

        #region Private Member - Update
        private void _update<T>(T obj, string property)
        {
            DbRow<T> row = new DbRow<T>(this, obj);
            var col = _getTable<T>().Columns.Where(
                c => c.Info.Name == property
            );

            this.Update(row, col);
        }
        #endregion

        #region Private Member - CreateTable
        private bool _createOrUpdateTable<T>(DbTable<T> table, DbReader<T> tableReader = null)
        {
            int i = 0;
            bool insertOldData = false;
            string sbCols = "";

            if (tableReader != null)
            {
                List<int> colsOld = new List<int>();
                List<DbColumn<T>> colsNew = new List<DbColumn<T>>(table.Columns);

                for (i = 0; i < tableReader.FieldCount; i++)
                {
                    DbColumn<T> col = table.Columns.FirstOrDefault(
                        c => c.Name == tableReader.GetFieldName(i) && c.Type == tableReader.GetFieldType(i)
                    );

                    if (col != null)
                    {
                        colsNew.Remove(col);
                    }
                    else
                    {
                        colsOld.Add(i);
                    }
                }

                if (colsOld.Count != 0 || colsNew.Count != 0)
                {
                    if (colsOld.Count == 0)
                    {
                        foreach (DbColumn<T> col in colsNew)
                        {
                            _query<T>(
                                String.Format(
                                    "ALTER TABLE \"{0}\" ADD COLUMN \"{1}\" {2} NOT NULL  DEFAULT '{0}';",
                                    table.Name,
                                    col.Name,
                                    _types[col.Type],
                                    _defaults[col.Type]
                                ),
                                true
                            );
                        }

                        return true;
                    }
                    else
                    {
                        _query<T>(
                            String.Format("ALTER TABLE \"{0}\" RENAME TO \"{0}_backup\";", table.Name),
                            true
                        );

                        sbCols = String.Join(
                            ", ",
                            table.Columns.Where(c => !colsNew.Contains(c)).Select(c => String.Format("\"{0}\"", c.Name)).ToArray()
                        );

                        insertOldData = true;
                    }
                }
                else
                {
                    return false;
                }
            }

            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("CREATE TABLE \"{0}\" (", table.Name);

            i = 0;
            foreach (DbColumn<T> col in table.Columns)
            {
                if (i != 0)
                {
                    sb.Append(", ");
                }

                sb.AppendFormat(
                    "\"{0}\" {1}",
                    col.Name,
                    _types[col.Type]
                );

                if (col == table.PrimaryColumn)
                {
                    sb.AppendFormat(
                        " PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE ",
                        table.PrimaryColumn.Start,
                        table.PrimaryColumn.Increment
                    );
                }
                else
                {
                    sb.AppendFormat(" NOT NULL DEFAULT '{0}' ", _defaults[col.Type]);
                }

                i++;
            }

            sb.Append(");");
            _query<T>(sb.ToString(), false);

            if (insertOldData)
            {
                _query<T>(
                    String.Format(
                        "INSERT INTO \"{0}\" ({1}) SELECT {1} FROM \"{0}_backup\";",
                        table.Name, 
                        sbCols
                    ),
                    true
                );
                _query<T>(
                    String.Format("DROP TABLE \"{0}_backup\";", table.Name),
                    true
                );            
            }

            return insertOldData;
        }
        #endregion

        #region Private Member
        private object _getDefault(Type t)
        {
            return typeof(DB).GetMethod("_getDefaultIntern", BindingFlags.NonPublic | BindingFlags.Instance).MakeGenericMethod(t).Invoke(this, null);
        }

        private T _getDefaultIntern<T>()
        {
            return default(T);
        }
        #endregion

        #region Member
        public void Open()
        {
            if (_connection != null)
            {
                throw new Exception("Connection already open.");
            }

            _connection = new SQLiteConnection("Data Source=" + _fileName);
            _connection.Open();
        }

        public void Dispose()
        {
            if (!_disposed && _connection != null)
            {
                _connection.Close();
            }
        }
        #endregion

        #region Member - Type
        public void RegisterType<T>()
        {
            Type t = typeof(T);

            if (_typeBaseTable.ContainsKey(t)) return;

            DbTable<T> table = new DbTable<T>(this);
            DbReader<T> tables = _query<T>(
                String.Format("SELECT \"name\" FROM \"sqlite_master\" WHERE \"type\" = 'table' AND \"name\" = '{0}' LIMIT 1;", table.Name),
                false
            );

            if (tables.Length == 0)
            {
                _createOrUpdateTable(table);
            }

            _typeBaseTable.Add(t, table);
        }

        public DbTable<T> GetBaseTable<T>()
        {
            return _getTable<T>();
        }
        #endregion

        #region Member - Query
        public DbTable<T> Query<T>(string sql)
        {
            DbTable<T> table = _getTable<T>();
            DbReader<T> reader = _query<T>(sql, false);

            if (_createOrUpdateTable(table, reader))
            {
                reader = _query<T>(sql, false);
            }

            return new DbTable<T>(table, reader);
        }
        #endregion

        #region Member - Select
        public DbRow<T> Select<T>(object primaryValue, bool catchGetDefault = true)
        {
            DbTable<T> table = _getTable<T>();

            try
            {
                return this.Select<T>(table.PrimaryColumn, primaryValue).Rows.First();
            }
            catch
            {
                if (!catchGetDefault) throw new Exception("Id not found.");
            }

            return null;
        }

        public DbTable<T> Select<T>(DbColumn<T> col, object value)
        {
            return this.Select<T>(
                new DbExpression(col.Name, Operators.Equals, value)
            );
        }

        public DbTable<T> Select<T>(params DbExpression[] where)
        {
            return this.Select<T>(
                new List<DbExpression>(where)
            );
        }

        public DbTable<T> Select<T>(IEnumerable<DbExpression> where)
        {
            DbTable<T> table = _getTable<T>();
            StringBuilder sb = new StringBuilder();

            sb.AppendFormat("SELECT * FROM \"{0}\"", table.Name);

            if (where.Count() != 0)
            {
                sb.Append(" WHERE ");
                sb.Append(
                    _generateWhere(where)
                );
            }

            return this.Query<T>(
                sb.ToString()
            );
        }
        #endregion

        #region Member - Insert
        public void Insert<T>(T value, bool returnIfNotNew = true)
        {
            DbTable<T> table = _getTable<T>();
            DbRow<T> row = new DbRow<T>(this, value);

            if (!Object.Equals(row[table.PrimaryColumn], 0L))
            {
                if (returnIfNotNew) return;

                throw new Exception("Object already in Database.");
            }
            
            StringBuilder sb = new StringBuilder();

            sb.AppendFormat("INSERT INTO \"{0}\" (", table.Name);

            int ci = 0;
            foreach (DbColumn<T> col in table.Columns)
            {
                if (col == table.PrimaryColumn) continue;

                if (ci != 0)
                {
                    sb.Append(", ");
                }

                sb.AppendFormat("\"{0}\"", col.Name);

                ci++;
            }

            sb.Append(") VALUES (");

            ci = 0;
            foreach (DbColumn<T> col in row.Table.Columns)
            {
                if (col == row.Table.PrimaryColumn) continue;

                if (ci != 0)
                {
                    sb.Append(", ");
                }

                sb.AppendFormat("'{0}'", _getValue(row[col]));

                ci++;
            }

            sb.Append(");");
            
            DbReader<T> reader = _query<T>(
                sb.ToString(),
                true
            );

            row.SetProperty(
                value,
                table.PrimaryColumn,
                reader.Data[0][0]
            );

            foreach (DbRelation<T> relation in table.Relations)
            {
                relation.Insert(value);
            }

            INotifyPropertyChanged npc = value as INotifyPropertyChanged;

            if (npc != null)
            {
                npc.PropertyChanged += new PropertyChangedEventHandler(Object_PropertyChanged);
            }
        }

        public T InsertNew<T>()
            where T : new()
        {
            T t = new T();
            this.Insert(t);

            return t;
        }

        public void InsertRange<T>(IEnumerable<T> values)
        {
            foreach (T value in values)
            {
                this.Insert<T>(value);
            }
        }
        #endregion

        #region Member - Update
        public void Update<T>(T value)
        {
            DbRow<T> row = new DbRow<T>(this, value);

            this.Update<T>(row);
        }

        public void Update<T>(DbRow<T> row, IEnumerable<DbColumn<T>> columns = null)
        {
            DbTable<T> table = _getTable<T>();
            StringBuilder sb = new StringBuilder();

            if (columns == null)
            {
                columns = table.Columns;
            }

            if (row[table.PrimaryColumn] == null || row[table.PrimaryColumn] == _getDefault(table.PrimaryColumn.Type))
            {
                throw new Exception("Row has no ID. Pleace Insert first.");
            }

            sb.AppendFormat("UPDATE \"{0}\" SET ", table.Name);

            int i = 0;
            foreach (DbColumn<T> col in columns)
            {
                if (col == row.Table.PrimaryColumn) continue;

                if (i != 0)
                {
                    sb.Append(", ");
                }

                sb.AppendFormat("\"{0}\" = '{1}'", col.Name, _getValue(row[col]));

                i++;
            }

            sb.AppendFormat(" WHERE \"{0}\" = '{1}'",
                row.Table.PrimaryColumn.Name,
                _getValue(row[row.Table.PrimaryColumn])
            );

            _query<T>(
                sb.ToString(),
                true
            );
        }
        #endregion

        #region Member - Delete
        public void Delete<T>(T value)
        {
            DbRow<T> row = new DbRow<T>(this, value);

            _query<T>(
                String.Format(
                    "DELETE FROM \"{0}\" WHERE \"{1}\" = '{2}';",
                    row.Table.Name,
                    row.Table.PrimaryColumn.Name,
                    row[row.Table.PrimaryColumn]
                ),
                false
            );
        }
        #endregion

        #region Events
        public void Object_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            typeof(DB).GetMethod(
                "_update",
                BindingFlags.NonPublic | BindingFlags.Instance
            ).MakeGenericMethod(
                sender.GetType()
            ).Invoke(
                this,
                new object[] { sender, e.PropertyName }
            );
        }
        #endregion
    }
}

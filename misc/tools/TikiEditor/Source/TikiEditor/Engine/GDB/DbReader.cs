using System;
using System.Linq;
using System.Data;
using System.Collections.Generic;

namespace Database.GDB
{
    public class DbReader<T>
    {
        #region Vars
        private DB _db;

        private int _fieldCount;

        private string[] _names;
        private Type[] _types;

        private object[][] _data;
        #endregion

        #region Init
        public DbReader(DB db, IDataReader reader)
        {
            _db = db;
            _fieldCount = reader.FieldCount;
            _types = new Type[_fieldCount];
            _names = new string[_fieldCount];

            Dictionary<int, Type> convertTo = new Dictionary<int,Type>();

            for (int i = 0; i < reader.FieldCount; i++)
            {
                _names[i] = reader.GetName(i);

                Type type = reader.GetFieldType(i);
                switch (reader.GetDataTypeName(i).ToUpper())
                {
                    case "FLOAT":
                        type = typeof(float);
                        break;
                }

                if (type != reader.GetFieldType(i))
                {
                    convertTo[i] = type;
                }

                _types[i] = type;
            }

            List<object[]> rows = new List<object[]>();
            while (reader.Read())
            {
                object[] row = new object[reader.FieldCount];

                for (int i = 0; i < reader.FieldCount; i++)
                {
                    if (convertTo.ContainsKey(i))
                    {
                        row[i] = Convert.ChangeType(reader.GetValue(i), convertTo[i]);
                    }
                    else
                    {
                        row[i] = reader.GetValue(i);
                    }                    
                }

                rows.Add(row);
            }

            _data = rows.ToArray();
            reader.Close();
        }
        #endregion

        #region Member
        public Type GetFieldType(int i)
        {
            return _types[i];
        }

        public string GetFieldName(int i)
        {
            return _names[i];
        }
        #endregion

        #region Properties
        public DB Db
        {
            get { return _db; }
        }

        public int FieldCount
        {
            get { return _fieldCount; }
        }

        public int Length
        {
            get { return _data.Length; }
        }

        public object[][] Data
        {
            get { return _data; }
        }
        #endregion
    }
}

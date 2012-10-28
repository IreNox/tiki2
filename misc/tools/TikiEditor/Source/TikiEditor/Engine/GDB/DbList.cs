using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using TikiEditor;

namespace Database.GDB
{
    public class DbList<T> : IList<T>
    {
        #region Vars
        private DB _db;

        private object _parentObject;
        private PropertyInfo _propertyInfo;

        private PropertyInfo _parentInfo;
        private PropertyInfo _childInfo;

        private List<T> _list = new List<T>();
        #endregion

        #region Init
        public DbList(object parent, PropertyInfo info)
        {
            _db = GI.DB;
            _parentObject = parent;
            _propertyInfo = info;

            DataRelationAttribute att = info.GetCustomAttributes(typeof(DataRelationAttribute), true).OfType<DataRelationAttribute>().FirstOrDefault();

            if (att == null)
            {
                throw new Exception("Property has no Relation.");
            }

            _parentInfo = info.ReflectedType.GetProperty(att.BaseFieldname);
            _childInfo = att.TypeChild.GetProperty(att.ChildFieldname);
        }

        public DbList(object obj, PropertyInfo info, T[] data)
            : this(obj, info)
        {
            _list.AddRange(data);
        }
        #endregion

        #region Private Member
        private void _prepareObject(T obj)
        {
            _childInfo.SetValue(
                obj,
                _parentInfo.GetValue(_parentObject, null),
                null
            );
            _db.Insert(obj);
        }
        #endregion

        #region Member - Db
        public void Add(T item)
        {
            _prepareObject(item);
            _list.Add(item);
        }

        public void Insert(int index, T item)
        {
            _prepareObject(item);
            _list.Insert(index, item);
        }

        public bool Remove(T item)
        {
            _db.Delete(item);

            return _list.Remove(item);
        }

        public void RemoveAt(int index)
        {
            this.Remove(
                _list[index]
            );
        }

        public T this[int index]
        {
            get { return _list[index]; }
            set { throw new NotImplementedException(); }
        }

        public void Clear()
        {
            foreach (T item in _list.ToArray())
            {
                this.Remove(item);
            }
        }

        #endregion

        #region Member - Const
        public bool Contains(T item)
        {
            return _list.Contains(item);
        }

        public void CopyTo(T[] array, int arrayIndex)
        {
            _list.CopyTo(array, arrayIndex);
        }

        public int Count
        {
            get { return _list.Count; }
        }

        public bool IsReadOnly
        {
            get { return false; }
        }

        public int IndexOf(T item)
        {
            return _list.IndexOf(item);
        }

        public IEnumerator<T> GetEnumerator()
        {
            return _list.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return _list.GetEnumerator();
        }
        #endregion
    }
}

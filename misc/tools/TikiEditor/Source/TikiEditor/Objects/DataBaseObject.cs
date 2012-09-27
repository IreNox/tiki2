using System;
using System.Linq;
using System.ComponentModel;
using System.Collections.Generic;
using Database.GDB;

namespace TikiEditor.Objects
{
    public class DataBaseObject : INotifyPropertyChanged
    {
        #region Vars
        private long _id = 0;

        private bool _dataBaseEnabled = true;
        private List<string> _changedFields = new List<string>();
        #endregion

        #region Events
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion

        #region Init
        public DataBaseObject()
        { 
        }
        #endregion

        #region Member
        protected void SetProperty<T>(ref T source, T value, string propName)
        { 
            if (!Object.Equals(source, value))
            {
                source = value;
            }

            if (this.PropertyChanged != null && _dataBaseEnabled)
            {
                this.PropertyChanged(
                    this,
                    new PropertyChangedEventArgs(propName)
                );
            }
            else if (!_dataBaseEnabled)
            {
                _changedFields.Add(propName);
            }
        }
        #endregion

        #region Properties
        [Browsable(false)]
        [DataField("ID")]
        [DataFieldPrimary]
        public long ID
        {
            get { return _id; }
            set { this.SetProperty(ref _id, value, "ID"); }
        }

        [Browsable(false)]
        public bool DatabaseEnabled
        {
            get { return _dataBaseEnabled; }
            set
            {
                _dataBaseEnabled = value;

                if (this.PropertyChanged != null && _dataBaseEnabled && _changedFields.Count != 0)
                {
                    foreach (string field in _changedFields.Distinct())
                    {
                        this.PropertyChanged(
                            this,
                            new PropertyChangedEventArgs(field)
                        );
                    }

                    _changedFields.Clear();
                }
            }
        }
        #endregion

        #region Operators
        public override bool Equals(object obj)
        {
            if (obj is DataBaseObject)
            {
                return this == (DataBaseObject)obj;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return _id.GetHashCode();
        }

        public static bool operator ==(DataBaseObject o1, DataBaseObject o2)
        {
            if (((object)o1 == null) && ((object)o2 == null)) return true;
            if (((object)o1 == null) || ((object)o2 == null)) return false;

            return (o1._id == o2._id) && (o1.GetType() == o2.GetType());
        }

        public static bool operator !=(DataBaseObject o1, DataBaseObject o2)
        {
            return !(o1 == o2);
        }
        #endregion
    }
}

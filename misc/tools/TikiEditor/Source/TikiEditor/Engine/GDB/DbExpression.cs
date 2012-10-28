using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Text;

namespace Database.GDB
{
    public enum Operators
    {
        Equals,
        NotEquals,
        GreaterThan,
        GreaterThanOrEqual,
        LessThan,
        LessThanOrEqual,
        StartsWith,
        EndsWith,
        Contains,
        Like
    }

    public class DbExpression
    {
        #region Vars
        private string _column;
        private Operators _operator;
        private object _value;
        #endregion

        #region Init
        public DbExpression(string column, Operators op, object value)
        {
            _column = column;
            _operator = op;
            _value = value;
        }
        #endregion

        #region Properties
        public string Column
        {
            get { return _column; }
        }

        public Operators Operator
        {
            get { return _operator; }
        }

        public object Value
        {
            get { return _value; }
        }
        #endregion
    }
}

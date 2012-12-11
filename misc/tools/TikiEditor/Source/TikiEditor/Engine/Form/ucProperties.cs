using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using System.Reflection;
using System.Runtime.InteropServices;
using System.IO;
using TikiEditor.Objects;

namespace TikiEditor.Designer
{
    public partial class ucProperties : UserControl
    {
        #region Vars
        private Type _currentType;
        private object _currentObject;

        private bool _settingChanged = false;

        private List<FieldData> _propertys = new List<FieldData>();
        private Dictionary<FieldData, SearchFileAttribute> _fieldSearchAtt = new Dictionary<FieldData, SearchFileAttribute>();

        private formProperties _formProperties;

        private Func<Type, bool> _isValueType = delegate(Type t)
        {
            return t == typeof(Byte) ||
                   t == typeof(Int16) ||
                   t == typeof(Int32) ||
                   t == typeof(Int64) ||
                   t == typeof(Single) ||
                   t == typeof(Double) ||
                   t == typeof(Decimal) ||
                   t == typeof(String);
        };
        #endregion

        #region Init
        public ucProperties()
        {
            InitializeComponent();
        }
        #endregion

        #region Init - Type
        private void _initType(Type type)
        {
            if (type == _currentType) return;
            _disposeType();
            _currentType = type;

            var fields = type.GetFields(BindingFlags.Public | BindingFlags.Instance).Select(i => new FieldDescription(i));
            var properties = type.GetProperties().Select(i => new PropertyDescription(i));
            var all = fields.Cast<ReflectionDescription>().Concat(properties).ToArray();

            foreach (ReflectionDescription info in all)
            {
                if (info.Ready)
                {
                    bool browsable = true;
                    SearchFileAttribute searchAtt = null;

                    string text = null;

                    foreach (object obj in info.GetAttributes())
                    {
                        if (obj is DisplayNameAttribute)
                        {
                            DisplayNameAttribute att = (DisplayNameAttribute)obj;

                            text = att.DisplayName;
                        }
                        else if (obj is BrowsableAttribute)
                        {
                            BrowsableAttribute att = (BrowsableAttribute)obj;

                            browsable = att.Browsable;
                        }
                        else if (obj is SearchFileAttribute)
                        {
                            searchAtt = (SearchFileAttribute)obj;
                        }
                    }
                    if (!browsable) continue;

                    if (text == null)
                    {
                        text = info.Name;
                    }

                    Label label = new Label();
                    label.AutoSize = true;
                    label.Text = text + ":";

                    Control controlText = null;
                    //if (info.PropertyType.GetInterfaces().Contains(typeDataObject))
                    //{
                    //    ComboBox comboBox = new ComboBox();
                    //    comboBox.SelectedIndexChanged += new EventHandler(textBox_TextChanged);
                    //    comboBox.DropDownStyle = ComboBoxStyle.DropDownList;

                    //    controlText = comboBox;
                    //}
                    //else 

                    if (info.Type.IsEnum)
                    {
                        ComboBox comboBox = new ComboBox();
                        comboBox.SelectedIndexChanged += new EventHandler(textBox_TextChanged);
                        comboBox.DropDownStyle = ComboBoxStyle.DropDownList;

                        List<EnumData> list = new List<EnumData>();

                        if (info.GetAttributes().OfType<OptionalAttribute>().Count() > 0)
                        {
                            list.Add(
                                new EnumData("")
                            );
                        }
                        list.AddRange(
                            Enum.GetNames(info.Type).Select(s => new EnumData(s))
                        );

                        comboBox.DataSource = list.ToArray();
                        comboBox.ValueMember = "Key";
                        comboBox.DisplayMember = "Value";

                        controlText = comboBox;
                    }
                    else if (info.Type == typeof(bool))
                    {
                        CheckBox checkBox = new CheckBox();
                        checkBox.CheckedChanged += new EventHandler(textBox_TextChanged);
                        checkBox.Text = text;

                        label.Visible = false;

                        controlText = checkBox;
                    }
                    else if (_isValueType(info.Type))
                    {
                        TextBox textBox = new TextBox();
                        textBox.TextChanged += new EventHandler(textBox_TextChanged);

                        controlText = textBox;
                    }
                    else
                    {
                        Button button = new Button();
                        button.Click += new EventHandler(button_Click);
                        button.Text = info.Type.Name;

                        controlText = button;
                    }

                    controlText.Anchor = AnchorStyles.Left | AnchorStyles.Right | AnchorStyles.Top;

                    this.Controls.Add(label);
                    this.Controls.Add(controlText);

                    _propertys.Add(
                        new FieldData(info, label, controlText)
                    );

                    if (searchAtt != null)
                    {
                        var info2 = _propertys.Last();

                        Button button = new Button();
                        button.Text = "...";
                        button.Size = new Size(25, 23);
                        button.Click += new EventHandler(SearchButton_Click);
                        button.Tag = info2;
                        button.Anchor = AnchorStyles.Right | AnchorStyles.Top;
                        _fieldSearchAtt[info2] = searchAtt;

                        this.Controls.Add(button);
                        info2.SearchButton = button;
                    }
                }
            }

            if (_propertys.Count == 0)
            {
                return;
            }

            int tabIndex = 1;
            int posLabelY = this.Padding.Top + 3;
            int posTextBoxY = this.Padding.Top;
            int maxWidth = _propertys.Max(i => i.Label.Size.Width);

            foreach (var go in _propertys.OrderBy(go => go.Label.Text))
            {
                go.Label.Location = new Point(
                    (maxWidth + 6) - go.Label.Size.Width,
                    posLabelY
                );

                go.Control.Location = new Point(
                    (maxWidth + 12),
                    posTextBoxY
                );

                go.Control.Size = new Size(
                    (this.ClientSize.Width - go.Control.Location.X) - 6,
                    20
                );

                if (go.SearchButton != null)
                {
                    go.Control.Size = new Size(
                        go.Control.Size.Width - 28,
                        20
                    );

                    go.SearchButton.Location = new Point(
                        this.ClientSize.Width - 31,
                        posTextBoxY
                    );
                }

                go.Control.Tag = go;
                go.ControlTabIndex = tabIndex;

                tabIndex++;
                posLabelY += 26;
                posTextBoxY += 26;
            }
        }
        #endregion

        #region Private Member
        private void _disposeType()
        {
            foreach (var data in _propertys)
            {
                data.Label.Dispose();
                data.Control.Dispose();
                if (data.SearchButton != null) data.SearchButton.Dispose();
            }
            _propertys.Clear();
        }

        private object _invokeGet(Type type, string member, params object[] args)
        {
            throw new NotImplementedException();

            //var typeDataRead = typeof(DataManager).GetMethod(member, BindingFlags.Static | BindingFlags.Public);
            //typeDataRead.MakeGenericMethod(type);            
            
            //return typeDataRead.Invoke(null, args);
        }
        #endregion

        #region Private Member - FillControl
        private void _fillControl(FieldData go)
        {
            object v = go.Info.GetValue(_currentObject);

            if (v != null)
            {
                //bool dataObject = go.Info.PropertyType.IsSubclassOf(typeof(NameObject));

                //if (dataObject)
                //{
                //    ((ComboBox)go.Control).SelectedValue = ((NameObject)v).Name;
                //}
                //else 

                if (go.Info.Type == typeof(bool))
                {
                    ((CheckBox)go.Control).Checked = (bool)v;
                }
                else if (_isValueType(go.Info.Type))
                {
                    go.Control.Text = v.ToString();
                }
            }
            else
            {
                bool dataObject = go.Info.Type.IsSubclassOf(typeof(DataBaseObject));

                if (dataObject)
                {
                    ((ComboBox)go.Control).SelectedValue = null;
                }
                else if (go.Info.Type.IsSubclassOf(typeof(ValueType)))
                {
                    go.Control.Text = "";
                }
            }
        }
        #endregion

        #region Member - Save
        public bool Save()
        {
            if (_currentObject == null) return false;

            int i = 0;
            foreach (var go in _propertys)
            {
                object value = null;
                //bool dataObject = go.Info.Type.IsSubclassOf(typeof(NameObject));

                //if (dataObject)
                //{
                //    value = _invokeGet(go.Info.Type, "LoadObject", ((ComboBox)go.Control).SelectedValue);
                //}
                //else
                
                if (go.Info.Type.IsEnum)
                {
                    value = Enum.Parse(go.Info.Type, ((ComboBox)go.Control).SelectedValue.ToString());
                }
                else if (go.Info.Type == typeof(bool))
                {
                    value = ((CheckBox)go.Control).Checked;
                }
                else if (_isValueType(go.Info.Type))
                {
                    try
                    {
                        value = Convert.ChangeType(go.Control.Text, go.Info.Type);
                        go.Control.ForeColor = SystemColors.WindowText;
                    }
                    catch
                    {
                        go.Control.ForeColor = Color.Red;
                    }
                }

                if (value != null)
                {
                    try
                    {
                        go.Info.SetValue(_currentObject, value);
                        go.Control.ForeColor = SystemColors.WindowText;
                    }
                    catch
                    {
                        go.Control.ForeColor = Color.Red;
                    }
                }

                i++;
            }
            SettingsChanged = false;

            return true;
        }
        #endregion

        #region Member - LoadObject
        public void LoadObject(object obj)
        {
            if (obj == null) return;
            if (obj == _currentObject) return;

            INotifyPropertyChanged npc = _currentObject as INotifyPropertyChanged;
            if (npc != null)
            {
                npc.PropertyChanged -= new PropertyChangedEventHandler(Object_PropertyChanged);
            }

            _currentObject = obj;
            _initType(obj.GetType());
            
            //foreach (var go in _propertys.Where(go => go.Info.PropertyType.IsSubclassOf(typeof(NameObject))))
            //{
            //    ComboBox comboBox = (ComboBox)go.Control;

            //    object[] objs = _invokeGet(go.Info.PropertyType, "LoadObjectType") as object[];

            //    if (objs != null)
            //    {
            //        string displayMember = "Name";

            //        List<ComboBoxItem> list = new List<ComboBoxItem>();

            //        if (go.Info.GetCustomAttributes(true).OfType<OptionalAttribute>().Count() > 0)
            //        {
            //            list.Add(
            //                new ComboBoxItem(null)
            //            );
            //        }
            //        list.AddRange(
            //            objs.Select(o => new ComboBoxItem(o as NameObject, displayMember))
            //        );

            //        comboBox.DataSource = list.ToArray();
            //        comboBox.ValueMember = "Id";
            //        comboBox.DisplayMember = "Text";
            //    }
            //}

            foreach (var go in _propertys)
            {
                go.Control.Enabled = true;
                go.Control.ForeColor = SystemColors.WindowText;

                _fillControl(go);
            }

            npc = _currentObject as INotifyPropertyChanged;
            if (npc != null)
            {
                npc.PropertyChanged += new PropertyChangedEventHandler(Object_PropertyChanged);
            }

            this.SettingsChanged = false;
        }
        #endregion

        #region Member - EventHandler
        private void button_Click(object sender, EventArgs e)
        {
            FieldData data = (FieldData)(((Control)sender).Tag);

            if (_formProperties == null)
            {
                _formProperties = new formProperties();
            }

            _formProperties.Object = data.Info.GetValue(_currentObject);

            if (_formProperties.ShowDialog() == DialogResult.OK)
            {
                data.Info.SetValue(_currentObject, _formProperties.Object);
            }
        }

        private void textBox_TextChanged(object sender, EventArgs e)
        {
            this.SettingsChanged = true;
        }

        private void SearchButton_Click(object sender, EventArgs e)
        {
            FieldData info = (FieldData)(((Button)sender).Tag);

            dialogOpenFile.Filter = String.Format(
                "{0}|{1}|Alle files|*.*",
                _fieldSearchAtt[info].Description,
                _fieldSearchAtt[info].Extension
            );

            if (dialogOpenFile.ShowDialog(this) != DialogResult.Cancel)
            {
                if (info.Control is TextBox)
                {
                    string fileName = dialogOpenFile.FileName.Replace(
                        Path.GetDirectoryName(Application.ExecutablePath), ""
                    ).Substring(1);
                    //.Substring(0, dialogOpenFile.FileName.Length - Path.GetExtension(dialogOpenFile.FileName).Length);
                    //fileName = fileName.Replace(Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "Content"), ""); //, "");
                    //fileName = fileName.Substring(1);

                    info.Control.Text = fileName;
                }
            }
        }

        private void Object_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            FieldData info = _propertys.FirstOrDefault(i => i.Info.Name == e.PropertyName);

            if (info != null)
            {
                bool sc = _settingChanged;

                _fillControl(info);

                _settingChanged = sc;
            }
        }
        #endregion

        #region Properties
        public bool SettingsChanged {
            get { return _settingChanged; }
            set { _settingChanged = value; }
        }

        public object CurrentObject
        {
            get { return _currentObject; }
            set
            {
                if (SettingsChanged && _currentObject != null && _currentObject != value && _currentObject != value)
                {
                    Save();
                }

                this.LoadObject(value);
            }
        }
        #endregion

        #region Class - EnumItem
        private class EnumData
        {
            #region Vars
            private string _key;
            private string _value;
            #endregion

            #region Init
            public EnumData(string data)
            {
                _key = data;
                _value = data;
            }
            #endregion

            #region Properties
            public string Key
            {
                get { return _key; }
                set { _key = value; }
            }

            public string Value
            {
                get { return _value; }
                set { _value = value; }
            }
            #endregion
        }
        #endregion

        #region Class - FieldData
        private class FieldData
        {
            #region Init
            public FieldData()
            { 
            }

            public FieldData(ReflectionDescription info, Label label, Control control)
            {
                this.Info = info;
                this.Label = label;
                this.Control = control;
            }
            #endregion

            #region Properties
            public int ControlTabIndex { get; set; }

            public Label Label { get; set; }
            public Control Control { get; set; }
            public Button SearchButton { get; set; }

            public ReflectionDescription Info { get; set; }
            #endregion
        }
        #endregion

        #region Class - ComboBoxItem
        public class ComboBoxItem
        {
            #region Vars
            private MemberInfo _info;

            private DataBaseObject _object;
            #endregion

            #region Init
            public ComboBoxItem(DataBaseObject obj)
                : this(obj, "Name")
            {
            }

            public ComboBoxItem(DataBaseObject obj, string textMember)
            {
                _object = obj;

                if (_object != null)
                {
                    Type type = obj.GetType();

                    _info = type.GetProperty(textMember);

                    if (_info == null)
                    {
                        _info = type.GetMember(textMember).FirstOrDefault();
                    }
                }
            }
            #endregion

            #region Properties
            public long Id
            {
                get
                {
                    return _object == null ? 0L : _object.ID;
                }
            }

            public string Text
            {
                get
                {
                    if (_info != null)
                    {
                        object value = null;

                        if (_info is PropertyInfo)
                        {
                            PropertyInfo info = (PropertyInfo)_info;

                            value = info.GetValue(_object, null);
                        }
                        else if (_info is MethodInfo)
                        {
                            MethodInfo info = (MethodInfo)_info;

                            value = info.Invoke(_object, null);
                        }

                        return value == null ? "" : value.ToString();
                    }

                    return "";
                }
            }

            public object Object
            {
                get { return _object; }
            }
            #endregion
        }
        #endregion        

        #region Class - Reflection
        private abstract class ReflectionDescription
        {
            #region Member
            public abstract object GetValue(object obj);

            public abstract void SetValue(object obj, object value);

            public abstract object[] GetAttributes();
            #endregion

            #region Properties
            public abstract Type Type { get; }

            public abstract bool Ready { get; }
            
            public abstract string Name { get; }
            #endregion
        }

        private class FieldDescription : ReflectionDescription
        {
            #region Vars
            private FieldInfo _info;
            #endregion

            #region Init
            public FieldDescription(FieldInfo info)
            {
                _info = info;
            }
            #endregion

            #region Member
            public override object GetValue(object obj)
            {
                return _info.GetValue(obj);
            }

            public override void SetValue(object obj, object value)
            {
                _info.SetValue(obj, value);
            }

            public override object[] GetAttributes()
            {
                return _info.GetCustomAttributes(true);
            }
            #endregion

            #region Properties
            public override bool Ready
            {
                get { return true; }
            }

            public override Type Type
            {
                get { return _info.FieldType;  }
            }

            public override string Name
            {
                get { return _info.Name; }
            }
            #endregion
        }

        private class PropertyDescription : ReflectionDescription
        {
            #region Vars
            private PropertyInfo _info;
            #endregion

            #region Init
            public PropertyDescription(PropertyInfo info)
            {
                _info = info;
            }
            #endregion

            #region Member
            public override object GetValue(object obj)
            {
                return _info.GetValue(obj, null);
            }

            public override void SetValue(object obj, object value)
            {
                _info.SetValue(obj, value, null);
            }

            public override object[] GetAttributes()
            {
                return _info.GetCustomAttributes(true);
            }
            #endregion

            #region Properties
            public override bool Ready
            {
                get { return _info.CanRead && _info.CanWrite; }
            }

            public override Type Type
            {
                get { return _info.PropertyType; }
            }

            public override string Name
            {
                get { return _info.Name; }
            }
            #endregion
        }
        #endregion
    }

    #region Class - SearchFileAttribute
    public class SearchFileAttribute : Attribute
    {
        #region Vars
        private string _desc;
        private string _ext;
        #endregion

        #region Init
        public SearchFileAttribute(string desc, string ext)
        {
            _desc = desc;
            _ext = ext;
        }
        #endregion

        #region Properties
        public string Description
        {
            get { return _desc; }
        }

        public string Extension
        {
            get { return _ext; }
        }
        #endregion
    }
    #endregion
}
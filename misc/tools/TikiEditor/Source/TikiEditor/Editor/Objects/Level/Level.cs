using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Database.GDB;
using System.ComponentModel;
using TikiEditor.Designer;

namespace TikiEditor.Objects
{
    [DataTable("tiki_level")]
    public class Level : DataBaseObject
    {
        #region Vars
        private string _name;

        private string _heightmapFilename;
        private int _heightmapScale;
        private int _heightmapSize;
        private float _heightmapElevation;

        private DbList<LevelEnemy> _enemies;
        private DbList<LevelObject> _objects;
        #endregion

        #region Init
        public Level()
        {
            _enemies = new DbList<LevelEnemy>(this, this.GetType().GetProperty("Enemies"));
            _objects = new DbList<LevelObject>(this, this.GetType().GetProperty("Objects"));
        }
        #endregion

        #region Member
        public void RemoveTransform(BasicTransform transform)
        {
            LevelEnemy enemy = transform as LevelEnemy;

            if (enemy != null)
            {
                _enemies.Remove(enemy);
            }

            LevelObject obj = transform as LevelObject;

            if (obj != null)
            {
                _objects.Remove(obj);
            }
        }
        #endregion

        #region Properties
        [DataField("Name")]
        public string Name
        {
            get { return _name; }
            set { SetProperty(ref _name, value, "Name"); }
        }

        [SearchFile("Image", "*.jpg;*.jpeg;*.png;*.gif;*.dds")]
        [DataField("HeightmapFilename")]
        public string HeightmapFilename
        {
            get { return _heightmapFilename; }
            set { SetProperty(ref _heightmapFilename, value, "HeightmapFilename"); }
        }

        [DataField("HeightmapScale")]
        public int HeightmapScale
        {
            get { return _heightmapScale; }
            set { SetProperty(ref _heightmapScale, value, "HeightmapScale"); }
        }

        [DataField("HeightmapSize")]
        public int HeightmapSize
        {
            get { return _heightmapSize; }
            set { SetProperty(ref _heightmapSize, value, "HeightmapSize"); }
        }

        [DataField("HeightmapElevation")]
        public float HeightmapElevation
        {
            get { return _heightmapElevation; }
            set { SetProperty(ref _heightmapElevation, value, "HeightmapElevation"); }
        }

        [Browsable(false)]
        [DataRelation("ID", typeof(LevelEnemy), "LevelID")]
        public DbList<LevelEnemy> Enemies
        {
            get { return _enemies; }
            set { SetProperty(ref _enemies, value, "Objects"); }
        }

        [Browsable(false)]
        [DataRelation("ID", typeof(LevelObject), "LevelID")]
        public DbList<LevelObject> Objects
        {
            get { return _objects; }
            set { SetProperty(ref _objects, value, "Objects"); }
        }
        #endregion

        #region Properties - Dynamic
        public BasicTransform[] AllTransforms
        {
            get { return _objects.Cast<BasicTransform>().Concat(_enemies).ToArray(); }
        }
        #endregion
    }
}

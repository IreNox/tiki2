using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using TikiEditor.Designer;
using Microsoft.Xna.Framework.Graphics;
using System.ComponentModel;
using System.IO;
using TikiEditor.Objects;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public class ModeLevel : EditorMode
    {
        #region Vars
        private string _heightmapName = null;
        private Heightmap _heightmap;
        private Texture2D _background;

        private int _levelId;
        private Level _level;

        private DrawLevel _draw;
        private ucDesignLevel _designer;
        #endregion

        #region Init
        public ModeLevel(Game game, int levelId)
            : base(game)
        {
            _levelId = levelId;

            _designer = new ucDesignLevel();
            _heightmap = new Heightmap();
        }

        public override void  Init()
        {
            var row = GI.DB.Select<Level>(_levelId);

            if (row != null)
            {
                _level = row.ToObject();
            }
            else
            {
                _level = GI.DB.InsertNew<Level>();
            }

            _level.PropertyChanged += new System.ComponentModel.PropertyChangedEventHandler(Level_PropertyChanged);
            _draw = new DrawLevel();

            Level_PropertyChanged(null, new PropertyChangedEventArgs("HeightmapFilename"));

            Program.Form.LeftControl = _designer;
        }
        #endregion

        #region Member
        public override object  ResetBefore()
        {
            if (_background != null)
            {
                Color[] data = new Color[_background.Width * _background.Height];
                _background.GetData(data);

                return data;
            }

            return null;
        }

        public override void ResetAfter(object userData)
        {
            _draw.Reset();

            if (_background != null)
            {
                _background = new Texture2D(this.GraphicsDevice, _background.Width, _background.Height);
                _background.SetData(
                    (Color[])userData
                );
            }            
        }
        #endregion

        #region Member - Draw/Update
        public override void Draw(GameTime time)
        {
            if (_background != null)
            {
                GI.SpriteBatch.Draw(
                    _background,
                    Vector2.Zero,
                    null,
                    Color.White,
                    0,
                    new Vector2(
                        (float)_background.Width / 2,
                        (float)_background.Height / 2
                    ),
                    CU.ToDisplayUnits(_background.Width / _level.HeightmapSize),
                    SpriteEffects.None,
                    0.01f
                );
            }

            _draw.Draw(time);

            base.Draw(time);
        }

        public override void Update(GameTime time)
        {
            _draw.Update(time);

            float scroll = (float)GI.Control.MouseScroll / 1000;
            float zoom = 1.0f / ((scroll * scroll) + 1);
            if (GI.Camera.Zoom != zoom && zoom > 0) GI.Camera.Zoom = zoom;

            base.Update(time);
        }
        #endregion

        #region Member - EventHandler
        private void Level_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "HeightmapFilename")
            {
                string fileIn = Path.Combine(Path.GetDirectoryName(GI.DataPath), _level.HeightmapFilename);

                if (_heightmapName != _level.HeightmapFilename && File.Exists(fileIn))
                {
                    try
                    {
                        string fileOut = "Content/" + Path.GetFileNameWithoutExtension(_level.HeightmapFilename) + ".png";

                        if (File.Exists(fileOut))
                        {
                            using (Stream io = File.OpenRead(fileOut))
                            {
                                _background = Texture2D.FromStream(GI.Device, io);
                            }
                        }
                        else
                        {
                            _heightmap.LoadHeightmap(fileIn);

                            int[] data = new int[_heightmap.GetWidth() * _heightmap.GetHeight()];
                            _heightmap.FillData(data);

                            Texture2D tex = new Texture2D(
                                this.GraphicsDevice,
                                _heightmap.GetWidth(),
                                _heightmap.GetHeight()
                            );

                            int max = data.Max();

                            tex.SetData(
                                data.Select(c => (float)c / max).Select(c => new Color(c, c, c, 1.0f)).ToArray()
                            );

                            if (_background != null)
                            {
                                _background.Dispose();
                            }

                            _background = tex;

                            using (Stream io = File.OpenWrite(fileOut))
                            {
                                _background.SaveAsPng(io, _background.Width, _background.Height);
                            }
                        }

                        _heightmapName = _level.HeightmapFilename;
                    }
                    catch
                    {
                    }
                }
            }
        }
        #endregion

        #region Properties
        public Level Level
        {
            get { return _level; }
        }

        public DrawLevel LevelDraw
        {
            get { return _draw; }
        }

        internal ucDesignLevel Designer
        {
            get { return _designer; }
        }
        #endregion
    }
}

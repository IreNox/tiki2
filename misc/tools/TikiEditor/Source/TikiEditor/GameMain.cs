using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using TikiEditor.Objects;
using System.IO;
using System.Linq;
using System.ComponentModel;

namespace TikiEditor
{
    public class GameMain : Game
    {
        #region Vars
        private Level _level;

        private GraphicsDeviceManager _graphics;

        private bool _isFullscreen;
        private Point _resetPoint;

        private System.Windows.Forms.Control _window;
        private Designer.formMain _formMain;

        private string _heightmapName;
        private Heightmap _heightmap;
        private Texture2D _background;
        #endregion

        #region Init
        public GameMain()
        {
            _heightmap = new Heightmap();

            _initForm();

            this.IsMouseVisible = true;
            this.Content.RootDirectory = "Content";
        }

        private void _initForm()
        {
            _formMain = new Designer.formMain();
            _formMain.Show();
            Program.Form = _formMain;

            _graphics = new GraphicsDeviceManager(this);
            _graphics.PreferredBackBufferWidth = _formMain.panelViewport.Width;
            _graphics.PreferredBackBufferHeight = _formMain.panelViewport.Height;
            _graphics.PreparingDeviceSettings += (sender, e) =>
            {
                e.GraphicsDeviceInformation.PresentationParameters.IsFullScreen = false;
                e.GraphicsDeviceInformation.PresentationParameters.DeviceWindowHandle = _formMain.panelViewport.Handle;
                e.GraphicsDeviceInformation.GraphicsProfile = GraphicsProfile.HiDef;
            };
            _graphics.ApplyChanges();

            _window = System.Windows.Forms.Control.FromHandle(this.Window.Handle);
            _window.VisibleChanged += (sender, e) =>
            {
                if (_window.Visible) _window.Visible = false;
            };

            Mouse.WindowHandle = _formMain.Handle;
        }

        protected override void Initialize()
        {
            GI.Init(this);

            this.Components.Add(GI.Camera);
            this.Components.Add(GI.Control);
            this.Components.Add(GI.BasicDraw);

            GI.Camera.CurrentPositionCenter = Vector2.Zero;

            _level = GI.Level;
            _level.PropertyChanged += new System.ComponentModel.PropertyChangedEventHandler(Level_PropertyChanged);

            base.Initialize();
        }

        protected override void LoadContent()
        {
            Level_PropertyChanged(null, new PropertyChangedEventArgs("HeightmapFilename"));

            //this.Components.Add(
            //    new Button(
            //        new Vector4(10, 10, 100, 30),
            //        "Boundings",
            //        () => { _debugDraw.ShowBounding = !_debugDraw.ShowBounding; }
            //    )
            //);
        }
        #endregion

        #region Dispose
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        protected override void Dispose(bool disposing)
        {
            GI.DB.Dispose();
            base.Dispose(disposing);
        }
        #endregion

        #region Member
        public void Reset(int width, int height, bool isFullscreen)
        {
            _isFullscreen = isFullscreen;
            _resetPoint = new Point(width, height);
        }
        #endregion

        #region Member - EventHandler
        private void Level_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "HeightmapFilename")
            {
                if (_heightmapName != _level.HeightmapFilename && File.Exists(_level.HeightmapFilename))
                {
                    try
                    {
                        _heightmap.LoadHeightmap(_level.HeightmapFilename);

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
                        _heightmapName = _level.HeightmapFilename;
                    }
                    catch
                    { 
                    }
                }
            }
        }
        #endregion

        #region Member - XNA - Draw
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            GI.SpriteBatch.Begin(SpriteSortMode.Deferred, null, null, null, null, null, GI.Camera.ViewMatrix2D);
            GI.PolygonBatch.Begin();

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

            base.Draw(gameTime);

            GI.SpriteBatch.End();
            GI.PolygonBatch.End();
        }
        #endregion

        #region Member - XNA - Update
        protected override void Update(GameTime gameTime)
        {
            if (_resetPoint != Point.Zero)
            {
                Color[] data = null;

                if (_background != null)
                {
                    data = new Color[_background.Width * _background.Height];
                    _background.GetData(data);
                }

                _graphics.IsFullScreen = _isFullscreen;
                _graphics.PreferredBackBufferWidth = _resetPoint.X;
                _graphics.PreferredBackBufferHeight = _resetPoint.Y;
                _resetPoint = Point.Zero;
                _graphics.ApplyChanges();

                GI.Reset();
                GI.Camera.ResetScreen();
                GI.BasicDraw.Reset();

                if (_background != null)
                {
                    _background = new Texture2D(this.GraphicsDevice, _background.Width, _background.Height);
                    _background.SetData(data);
                }
            }

            Program.Form.UpdateGame();

            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            float scroll = (float)GI.Control.MouseScroll / 1000;
            float zoom = 1.0f / ((scroll * scroll) + 1);
            if (GI.Camera.Zoom != zoom && zoom > 0) GI.Camera.Zoom = zoom;

            if (GI.Control.KeyboardPressed(Keys.F6))
            {
                Program.Form.DesignShow = !Program.Form.DesignShow;
            }

            if (GI.Control.MouseDown(MouseButtons.Right))
            {
                GI.Camera.CurrentPosition += -GI.Control.MouseDistanceDisplay();
            }
            
            base.Update(gameTime);
        }
        #endregion
    }
}

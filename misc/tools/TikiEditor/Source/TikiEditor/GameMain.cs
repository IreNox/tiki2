using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using TikiEditor.Objects;
using System.IO;

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

        private float _zoom = 1;
        private Texture2D _background;
        #endregion

        #region Init
        public GameMain()
        {
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

            base.Initialize();
        }

        protected override void LoadContent()
        {
            if (File.Exists(_level.HeightmapFilename))
            {
                using (Stream stream = File.OpenRead(_level.HeightmapFilename))
                {
                    _background = Texture2D.FromStream(this.GraphicsDevice, stream);
                }
            }

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
                    1.0f,
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
                _graphics.IsFullScreen = _isFullscreen;
                _graphics.PreferredBackBufferWidth = _resetPoint.X;
                _graphics.PreferredBackBufferHeight = _resetPoint.Y;
                _resetPoint = Point.Zero;
                _graphics.ApplyChanges();

                GI.Reset();
                GI.Camera.ResetScreen();
                GI.BasicDraw.Reset();
            }

            Program.Form.UpdateGame();

            if (Keyboard.GetState().IsKeyDown(Keys.Escape))
            {
                this.Exit();
            }

            float zoom = (((float)GI.Control.MouseScroll / 1000) + 1) * _zoom;
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

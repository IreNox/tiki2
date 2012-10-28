using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using TikiEditor.Objects;
using Database.GDB;

namespace TikiEditor
{
    public static class GI
    {
        #region Vars
        private static DB _db;

        private static GameMain _game;
        private static ModeGUI _modeGUI;
        private static ModeLevel _modeLevel;

        private static GraphicsDevice _device;

        private static SpriteBatch _spriteBatch;
        private static PolygonBatch _polygonBatch;

        private static CameraComponent _camera;
        private static ControlComponent _control;

        private static ContentManager _content;
        #endregion

        #region Init
        public static void Init(GameMain game)
        {
            _game = game;
            _device = game.GraphicsDevice;
            _content = game.Content;

            _spriteBatch = new SpriteBatch(_device);
            _polygonBatch = new PolygonBatch(_device);

            _camera = new CameraComponent();
            _control = new ControlComponent();

            _db = new DB("Data/TikiData.sqlite");
            _db.Open();
        }
        #endregion

        #region Member
        public static void Reset()
        {
            _spriteBatch.Dispose();

            _device = _game.GraphicsDevice;

            _spriteBatch = new SpriteBatch(_device);
            _polygonBatch = new PolygonBatch(_device);
        }
        #endregion

        #region Properties
        public static DB DB
        {
            get { return _db; }
        }

        public static SpriteBatch SpriteBatch
        {
            get { return _spriteBatch; }
        }

        public static PolygonBatch PolygonBatch
        {
            get { return _polygonBatch; }
        }

        public static GraphicsDevice Device
        {
            get { return _device; }
        }

        public static GameMain Game
        {
            get { return _game; }
        }
        
        public static CameraComponent Camera
        {
            get { return _camera; }
        }

        public static ControlComponent Control
        {
            get { return _control; }
        }

        public static ContentManager Content
        {
            get { return _content; }
        }

        public static ModeGUI ModeGUI
        {
            get { return GI._modeGUI; }
            set { GI._modeGUI = value; }
        }

        public static ModeLevel ModeLevel
        {
            get { return GI._modeLevel; }
            set { GI._modeLevel = value; }
        }
        #endregion
    }
}

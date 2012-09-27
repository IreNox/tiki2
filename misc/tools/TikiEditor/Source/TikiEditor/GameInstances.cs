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

        private static GraphicsDevice _device;

        private static BasicDraw _basicDraw;
        private static SpriteBatch _spriteBatch;
        private static PolygonBatch _polygonBatch;

        private static CameraComponent _camera;
        private static ControlComponent _control;

        private static ContentManager _content;

        private static Level _level;

        private static object _debug;
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

            var row = _db.Select<Level>(1);
            
            if (row != null)
            {
                _level = row.ToObject();
            }
            else
            {
                _level = _db.InsertNew<Level>();
            }

            _basicDraw = new BasicDraw();
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

        public static BasicDraw BasicDraw
        {
            get { return _basicDraw; }
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

        public static Level Level
        {
            get { return _level; }
        }
        #endregion

        public static object Debug
        {
            get { return GI._debug; }
            set { GI._debug = value; }
        }
    }
}

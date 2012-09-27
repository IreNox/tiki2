using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;

namespace TikiEditor
{
    public class ControlComponent : GameComponent
    {
        #region Vars
        private Point _mouseOffset;
        private MouseState _mousePrevState;
        private MouseState _mouseCurrentState;

        private GamePadState _gamePadPrevState;
        private GamePadState _gamePadCurrentState;

        private KeyboardState _keyboardPrevState;
        private KeyboardState _keyboardCurrentState;
        #endregion

        #region Init
        internal ControlComponent()
            : base(GI.Game)
        {
            _setStates();
        }
        #endregion

        #region Private Member
        private void _setStates()
        {
            _mousePrevState = _mouseCurrentState;
            _mouseCurrentState = Mouse.GetState();

            _gamePadPrevState = _gamePadCurrentState;
            _gamePadCurrentState = GamePad.GetState(PlayerIndex.One);

            _keyboardPrevState = _keyboardCurrentState;
            _keyboardCurrentState = Keyboard.GetState();

#if KINECT
            _kinectPrevState = _kinectCurrentState;
            _kinectCurrentState = Kinect.GetState();
#endif
        }
        #endregion

        #region Member
        public override void Update(GameTime gameTime)
        {
            if (Program.Form.panelViewport.Focused)
            {
                _setStates();
            }

            base.Update(gameTime);
        }
        #endregion

        #region Member - Mouse
        private ButtonState _mouseGetButtonState(MouseState state, MouseButtons button)
        {
            switch (button)
            {
                case MouseButtons.Left:
                    return state.LeftButton;
                case MouseButtons.Middle:
                    return state.MiddleButton;
                case MouseButtons.Right:
                    return state.RightButton;
            }

            return ButtonState.Released;
        }

        public bool MouseUp(MouseState state, MouseButtons button)
        {
            return _mouseGetButtonState(state, button) == ButtonState.Released;
        }

        public bool MouseDown(MouseState state, MouseButtons button)
        {
            return _mouseGetButtonState(state, button) == ButtonState.Pressed;
        }

        public bool MouseUp(MouseButtons button)
        {
            return this.MouseUp(_mouseCurrentState, button);
        }

        public bool MouseDown(MouseButtons button)
        {
            return this.MouseDown(_mousePrevState, button);
        }

        public bool MouseClick(Vector4 rect)
        {
            return this.MouseClick(rect, MouseButtons.Left);
        }

        public bool MouseClick(MouseButtons button)
        {
            return _mouseGetButtonState(_mousePrevState, button) == ButtonState.Pressed &&
                   _mouseGetButtonState(_mouseCurrentState, button) == ButtonState.Released;
        }

        public bool MouseClick(Vector4 rect, MouseButtons button)
        {
            return this.MouseClick(button) && rect.Contains(this.MouseSimVector());
        }

        public bool MousePressed(MouseButtons button)
        {
            return _mouseGetButtonState(_mousePrevState, button) == ButtonState.Released &&
                   _mouseGetButtonState(_mouseCurrentState, button) == ButtonState.Pressed;
        }

        #endregion

        #region Member - Mouse - Position
        public Point MouseDisplayPointNoCamera()
        {
            return this.MouseDisplayPointNoCamera(_mouseCurrentState);
        }

        public Point MouseDisplayPointNoCamera(MouseState state)
        {
            return new Point(
                state.X + _mouseOffset.X,
                state.Y + _mouseOffset.Y
            );
        }

        public Vector2 MouseSimVectorNoCamera()
        {
            return this.MouseSimVectorNoCamera(_mouseCurrentState);
        }

        public Vector2 MouseSimVectorNoCamera(MouseState state)
        {
            return CU.ToSimUnits(
                this.MouseDisplayPointNoCamera(state).ToVector2()
            );
        }

        public Point MouseDisplayPoint()
        {
            return this.MouseDisplayPoint(_mouseCurrentState);
        }

        public Point MouseDisplayPoint(MouseState state)
        {
            Vector2 mouse = this.MouseDisplayPointNoCamera(state).ToVector2() / GI.Camera.RealZoom;

            return (mouse - GI.Camera.CurrentPosition).ToPoint();
        }

        public Vector2 MouseSimVector()
        {
            return this.MouseSimVector(_mouseCurrentState);
        }

        public Vector2 MouseSimVector(MouseState state)
        {
            return CU.ToSimUnits(
                this.MouseDisplayPoint(state).ToVector2()
            );
        }

        public bool MouseContains(Rectangle rect)
        {
            return rect.Contains(
                this.MouseDisplayPoint()
            );
        }

        public Vector2 MouseDistanceSim()
        {
            Vector2 prevPos = this.MouseSimVector(_mousePrevState);
            Vector2 currPos = this.MouseSimVector(_mouseCurrentState);

            return prevPos - currPos;
        }

        public Vector2 MouseDistanceDisplay()
        {
            return CU.ToDisplayUnits(this.MouseDistanceSim());
        }
        #endregion

        #region Member - Keyboard
        public bool KeyboardUp(Keys key)
        {
            return _keyboardCurrentState.IsKeyUp(key);
        }

        public bool KeyboardDown(Keys key)
        {
            return _keyboardCurrentState.IsKeyDown(key);
        }

        public bool KeyboardPressed(Keys key)
        {
            return _keyboardPrevState.IsKeyUp(key) && _keyboardCurrentState.IsKeyDown(key);
        }
        public bool KeyboardReleased(Keys key)
        {
            return _keyboardPrevState.IsKeyDown(key) && _keyboardCurrentState.IsKeyUp(key);
        }
        #endregion

        #region Properties
        public Point MouseOffset
        {
            get { return _mouseOffset; }
            set { _mouseOffset = value; }
        }

        public int MouseScroll
        {
            get { return _mouseCurrentState.ScrollWheelValue; }
        }

        public MouseState MousePrevState
        {
            get { return _mousePrevState; }
        }

        public MouseState MouseCurrentState
        {
            get { return _mouseCurrentState; }
        }

        //public GamePadState GamePadPrevState
        //{
        //    get { return _gamePadPrevState; }
        //}

        //public GamePadState GamePadCurrentState
        //{
        //    get { return _gamePadCurrentState; }
        //}

        //public KeyboardState KeyboardPrevState
        //{
        //    get { return _keyboardPrevState; }
        //}

        //public KeyboardState KeyboardCurrentState
        //{
        //    get { return _keyboardCurrentState; }
        //}

#if KINECT
        public KinectState KinectPrevState
        {
            get { return _kinectPrevState; }
        }

        public KinectState KinectCurrentState
        {
            get { return _kinectCurrentState; }
        }
#endif
        #endregion
    }
}

using System;
using TikiEditor.Designer;

namespace TikiEditor
{
#if WINDOWS || XBOX
    static class Program
    {
        #region Vars
        private static GameMain _game;
        private static formMain _form;
        #endregion

        #region Init
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            using (_game = new GameMain())
            {
                _game.Run();
            }
        }
        #endregion

        #region Properties
        public static GameMain Game
        {
            get { return _game; }
        }

        public static formMain Form
        {
            get { return _form; }
            set { _form = value; }
        }
        #endregion
    }
#endif
}


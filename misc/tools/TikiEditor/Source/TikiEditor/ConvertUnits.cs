using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public static class CU
    {
        public static readonly float DisplayUnitsToSimUnitsRatio = 100f;
        public static readonly float SimUnitsToDisplayUnitsRatio = 1 / DisplayUnitsToSimUnitsRatio;

        public static Rectangle ToDisplayUnits(Rectangle simUnits)
        {
            return new Rectangle(
                (int)ToDisplayUnits(simUnits.X),
                (int)ToDisplayUnits(simUnits.Y),
                (int)ToDisplayUnits(simUnits.Width),
                (int)ToDisplayUnits(simUnits.Height));
        }

        public static float ToDisplayUnits(float simUnits)
        {
            return simUnits * DisplayUnitsToSimUnitsRatio;
        }

        public static float ToDisplayUnits(int simUnits)
        {
            return simUnits * DisplayUnitsToSimUnitsRatio;
        }

        public static Vector2 ToDisplayUnits(Vector2 simUnits)
        {
            return simUnits * DisplayUnitsToSimUnitsRatio;
        }

        public static void ToDisplayUnits(ref Vector2 simUnits, out Vector2 displayUnits)
        {
            Vector2.Multiply(ref simUnits, DisplayUnitsToSimUnitsRatio, out displayUnits);
        }

        public static Vector3 ToDisplayUnits(Vector3 simUnits)
        {
            return simUnits * DisplayUnitsToSimUnitsRatio;
        }

        public static Vector2 ToDisplayUnits(float x, float y)
        {
            return new Vector2(x, y) * DisplayUnitsToSimUnitsRatio;
        }

        public static void ToDisplayUnits(float x, float y, out Vector2 displayUnits)
        {
            displayUnits = Vector2.Zero;
            displayUnits.X = x * DisplayUnitsToSimUnitsRatio;
            displayUnits.Y = y * DisplayUnitsToSimUnitsRatio;
        }

        public static float ToSimUnits(float displayUnits)
        {
            return displayUnits * SimUnitsToDisplayUnitsRatio;
        }

        public static float ToSimUnits(double displayUnits)
        {
            return (float)displayUnits * SimUnitsToDisplayUnitsRatio;
        }

        public static float ToSimUnits(int displayUnits)
        {
            return displayUnits * SimUnitsToDisplayUnitsRatio;
        }

        public static Vector2 ToSimUnits(Vector2 displayUnits)
        {
            return displayUnits * SimUnitsToDisplayUnitsRatio;
        }

        public static Vector3 ToSimUnits(Vector3 displayUnits)
        {
            return displayUnits * SimUnitsToDisplayUnitsRatio;
        }

        public static void ToSimUnits(ref Vector2 displayUnits, out Vector2 simUnits)
        {
            Vector2.Multiply(ref displayUnits, SimUnitsToDisplayUnitsRatio, out simUnits);
        }

        public static Vector2 ToSimUnits(float x, float y)
        {
            return new Vector2(x, y) * SimUnitsToDisplayUnitsRatio;
        }

        public static Vector2 ToSimUnits(double x, double y)
        {
            return new Vector2((float)x, (float)y) * SimUnitsToDisplayUnitsRatio;
        }

        public static void ToSimUnits(float x, float y, out Vector2 simUnits)
        {
            simUnits = Vector2.Zero;
            simUnits.X = x * SimUnitsToDisplayUnitsRatio;
            simUnits.Y = y * SimUnitsToDisplayUnitsRatio;
        }
    }
}
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;

namespace TikiEditor
{
    public static class Extensions
    {
        #region Collections
        public static TValue Add<TKey, TValue>(this Dictionary<TKey, TValue> source, TKey key, TValue value)
        {
            source.Add(
                key,
                value
            );

            return value;
        }

        public static void AddRange<TKey, TValue>(this Dictionary<TKey, TValue> source, Dictionary<TKey, TValue> value)
        {
            foreach (var kvp in value)
            {
                source.Add(
                    kvp.Key,
                    kvp.Value
                );
            }
        }

        public static void AddRange<TKey, TValue>(this Dictionary<TKey, TValue> source, params KeyValuePair<TKey, TValue>[] value)
        {
            foreach (var kvp in value)
            {
                source.Add(
                    kvp.Key,
                    kvp.Value
                );
            }
        }
        #endregion

        #region Vector2
        public static Vector2 Abs(this Vector2 source)
        {
            return new Vector2(
                Math.Abs(source.X),
                Math.Abs(source.Y)
            );
        }

        public static Point ToPoint(this Vector2 source)
        {
            return new Point((int)source.X, (int)source.Y);
        }

        public static Vector2 ToVector2(this Point source)
        {
            return new Vector2(source.X, source.Y);
        }

        public static bool IsReady(this Vector2 source)
        {
            return source.X != 0 || source.Y != 0;
        }

        public static Vector2 CalculateSize(this IEnumerable<Vector2> source)
        {
            return new Vector2(
                source.Max(v => v.X) - source.Min(v => v.X),
                source.Max(v => v.Y) - source.Min(v => v.Y)
            );
        }

        public static Vector2 GetCenter(this Texture2D source)
        {
            return new Vector2(source.Width, source.Height) / 2;
        }

        public static Vector4 ToRectangle(this Vector2 source, Vector2 size)
        {
            Vector2 half = size / 2;

            return new Vector4(
                source.X - half.X,
                source.Y - half.Y,
                size.X,
                size.Y
            );
        }
        #endregion

        #region Vector4
        public static Color ToColor(this Vector4 v)
        {
            return new Color(v.X, v.Y, v.Z, v.W);
        }

        public static Rectangle ToRectangle(this Vector4 source)
        {
            return new Rectangle(
                (int)source.X,
                (int)source.Y,
                (int)source.Z,
                (int)source.W
            );
        }

        public static Vector2[] ToVector2All(this Vector4 source)
        {
            return new Vector2[] {
                source.ToVector2TL(),
                source.ToVector2TR(),
                source.ToVector2BL(),
                source.ToVector2BR()
            };
        }

        public static Vector2 ToVector2TL(this Vector4 source)
        {
            return new Vector2(source.X, source.Y);
        }

        public static Vector2 ToVector2TR(this Vector4 source)
        {
            return new Vector2(source.X + source.Z, source.Y);
        }

        public static Vector2 ToVector2BL(this Vector4 source)
        {
            return new Vector2(source.X, source.Y + source.W);
        }

        public static Vector2 ToVector2BR(this Vector4 source)
        {
            return new Vector2(source.X + source.Z, source.Y + source.W);
        }

        public static bool Contains(this Vector4 source, Vector2 point)
        {
            return (point.X > source.X) &&
                   (point.Y > source.Y) &&
                   (point.X < source.X + source.Z) &&
                   (point.Y < source.Y + source.W);
        }

        public static bool Contains(this Vector4 source, Vector4 rect)
        {
            float w = source.Z - (rect.X - source.X);
            float h = source.W - (rect.Y - source.Y);

            return (rect.X >= source.X) &&
                   (rect.Y >= source.Y) &&
                   (rect.X <= source.X + source.Z) &&
                   (rect.Y <= source.Y + source.W) &&
                   (w >= rect.Z) &&
                   (h >= rect.W);
        }

        public static bool Intersect(this Vector4 source, Vector4 vector)
        {
            return (source.X <= vector.X + vector.Z) && (source.Y <= vector.Y + vector.W) && (source.X + source.Z >= vector.X) && (source.Y + source.W >= vector.Y) ||
                    (source.X + source.Z <= vector.X) && (vector.Y + vector.W >= source.Y) && (source.X + source.Z >= vector.X);
        }
        #endregion
    }
}

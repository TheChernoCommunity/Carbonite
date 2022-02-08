using System;

namespace ModAPI.Math
{
	public struct Vec2f
	{
		public static readonly Vec2f Zero = new Vec2f();

		public float x, y;

		public Vec2f()
        {
			this.x = 0.0f;
			this.y = 0.0f;
        }

		public Vec2f(float x, float y)
        {
			this.x = x;
			this.y = y;
        }

        public static implicit operator Vec3f(Vec2f v)
        {
            return new Vec3f(v.x, v.y, 0.0f);
        }

        public static implicit operator Vec4f(Vec2f v)
        {
            return new Vec4f(v.x, v.y, 0.0f, 0.0f);
        }

        public static Vec2f operator +(Vec2f lhs, Vec2f rhs)
        {
            return new Vec2f(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        public static Vec2f operator -(Vec2f lhs, Vec2f rhs)
        {
            return new Vec2f(lhs.x - rhs.x, lhs.y - rhs.y);
        }

        public static Vec2f operator *(Vec2f lhs, Vec2f rhs)
        {
            return new Vec2f(lhs.x * rhs.x, lhs.y * rhs.y);
        }

        public static Vec2f operator /(Vec2f lhs, Vec2f rhs)
        {
            return new Vec2f(lhs.x / rhs.x, lhs.y / rhs.y);
        }

        public static Vec2f operator *(Vec2f lhs, float rhs)
        {
            return new Vec2f(lhs.x * rhs, lhs.y * rhs);
        }

        public static Vec2f operator *(float lhs, Vec2f rhs)
        {
            return new Vec2f(lhs * rhs.x, lhs * rhs.y);
        }

        public static Vec2f operator /(Vec2f lhs, float rhs)
        {
            float inv = 1.0f / rhs;
            return lhs * inv;
        }

        public static Vec2f operator /(float lhs, Vec2f rhs)
        {
            return new Vec2f(lhs / rhs.x, lhs / rhs.y);
        }

        public static Vec2f operator -(Vec2f vec)
        {
            return new Vec2f(-vec.x, -vec.y);
        }

        public float Dot(Vec2f other)
        {
            return x * other.x + y * other.y;
        }

        public float Angle(Vec2f other)
        {
            float dls = Dot(other) / (Length * other.Length);
            if (dls < -1.0f)
                dls = -1.0f;
            else if (dls > 1.0f)
                dls = 1.0f;
            return MathF.Acos(dls);
        }

        public float Cross(Vec2f other)
        {
            return x * other.y - y * other.x;
        }

        public float LengthSqr => Dot(this);
        public float Length => MathF.Sqrt(LengthSqr);

        public Vec2f Normalized => this / Length;
    }
}
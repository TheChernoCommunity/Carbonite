using System;

namespace ModAPI.Math
{
	public struct Vec3f
	{
		public static readonly Vec3f Zero = new Vec3f();

		public float x, y, z;

		public Vec3f()
        {
			this.x = 0.0f;
			this.y = 0.0f;
            this.z = 0.0f;
        }

		public Vec3f(float x, float y, float z)
        {
			this.x = x;
			this.y = y;
            this.z = z;
        }

        public static implicit operator Vec2f(Vec3f v)
        {
            return new Vec2f(v.x, v.y);
        }

        public static implicit operator Vec4f(Vec3f v)
        {
            return new Vec4f(v.x, v.y, v.z, 0.0f);
        }

        public static Vec3f operator +(Vec3f lhs, Vec3f rhs)
        {
            return new Vec3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        public static Vec3f operator -(Vec3f lhs, Vec3f rhs)
        {
            return new Vec3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }

        public static Vec3f operator *(Vec3f lhs, Vec3f rhs)
        {
            return new Vec3f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
        }

        public static Vec3f operator /(Vec3f lhs, Vec3f rhs)
        {
            return new Vec3f(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
        }

        public static Vec3f operator *(Vec3f lhs, float rhs)
        {
            return new Vec3f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
        }

        public static Vec3f operator *(float lhs, Vec3f rhs)
        {
            return new Vec3f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
        }

        public static Vec3f operator /(Vec3f lhs, float rhs)
        {
            float inv = 1.0f / rhs;
            return lhs * inv;
        }

        public static Vec3f operator /(float lhs, Vec3f rhs)
        {
            return new Vec3f(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
        }

        public static Vec3f operator -(Vec3f vec)
        {
            return new Vec3f(-vec.x, -vec.y, -vec.z);
        }

        public float Dot(Vec3f other)
        {
            return x * other.x + y * other.y + z * other.z;
        }

        public float Angle(Vec3f other)
        {
            float dls = Dot(other) / (Length * other.Length);
            if (dls < -1.0f)
                dls = -1.0f;
            else if (dls > 1.0f)
                dls = 1.0f;
            return MathF.Acos(dls);
        }

        public Vec3f Cross(Vec3f other)
        {
            return new Vec3f(y * other.z - z * other.y, other.x * z - other.z * x, x * other.y - y * other.x);
        }

        public float LengthSqr => Dot(this);
        public float Length => MathF.Sqrt(LengthSqr);

        public Vec3f Normalized => this / Length;
    }
}
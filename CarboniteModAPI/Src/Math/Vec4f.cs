using System;

namespace ModAPI.Math
{
	public struct Vec4f
	{
		public static readonly Vec4f Zero = new Vec4f();

		public float x, y, z, w;

		public Vec4f()
        {
			this.x = 0.0f;
			this.y = 0.0f;
            this.z = 0.0f;
            this.w = 0.0f;
        }

		public Vec4f(float x, float y, float z, float w)
        {
			this.x = x;
			this.y = y;
            this.z = z;
            this.w = w;
        }
        
        public static implicit operator Vec2f(Vec4f v)
        {
            return new Vec2f(v.x, v.y);
        }

        public static implicit operator Vec3f(Vec4f v)
        {
            return new Vec3f(v.x, v.y, v.z);
        }

        public static Vec4f operator +(Vec4f lhs, Vec4f rhs)
        {
            return new Vec4f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }

        public static Vec4f operator -(Vec4f lhs, Vec4f rhs)
        {
            return new Vec4f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        }

        public static Vec4f operator *(Vec4f lhs, Vec4f rhs)
        {
            return new Vec4f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
        }

        public static Vec4f operator /(Vec4f lhs, Vec4f rhs)
        {
            return new Vec4f(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
        }

        public static Vec4f operator *(Vec4f lhs, float rhs)
        {
            return new Vec4f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
        }

        public static Vec4f operator *(float lhs, Vec4f rhs)
        {
            return new Vec4f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
        }

        public static Vec4f operator /(Vec4f lhs, float rhs)
        {
            float inv = 1.0f / rhs;
            return lhs * inv;
        }

        public static Vec4f operator /(float lhs, Vec4f rhs)
        {
            return new Vec4f(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
        }

        public static Vec4f operator -(Vec4f vec)
        {
            return new Vec4f(-vec.x, -vec.y, -vec.z, -vec.w);
        }

        public float Dot(Vec4f other)
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        public float Angle(Vec4f other)
        {
            float dls = Dot(other) / (Length * other.Length);
            if (dls < -1.0f)
                dls = -1.0f;
            else if (dls > 1.0f)
                dls = 1.0f;
            return MathF.Acos(dls);
        }

        public float LengthSqr => Dot(this);
        public float Length => MathF.Sqrt(LengthSqr);

        public Vec4f Normalized => this / Length;
    }
}
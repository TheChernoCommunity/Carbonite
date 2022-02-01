using System;

namespace ModAPI.Math
{
    public static class MathUtils
    {
        public static readonly float HalfPI = MathF.PI * 0.5f;
    }

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
            Vec3f o;
            o.x = v.x;
            o.y = v.y;
            o.z = 0.0f;
            return o;
        }

        public static implicit operator Vec4f(Vec2f v)
        {
            Vec4f o;
            o.x = v.x;
            o.y = v.y;
            o.z = 0.0f;
            o.w = 0.0f;
            return o;
        }

        public static Vec2f operator +(Vec2f lhs, Vec2f rhs)
        {
            Vec2f o;
            o.x = lhs.x + rhs.x;
            o.y = lhs.y + rhs.y;
            return o;
        }
        public static Vec2f operator -(Vec2f lhs, Vec2f rhs)
        {
            Vec2f o;
            o.x = lhs.x - rhs.x;
            o.y = lhs.y - rhs.y;
            return o;
        }
        public static Vec2f operator *(Vec2f lhs, Vec2f rhs)
        {
            Vec2f o;
            o.x = lhs.x * rhs.x;
            o.y = lhs.y * rhs.y;
            return o;
        }
        public static Vec2f operator /(Vec2f lhs, Vec2f rhs)
        {
            Vec2f o;
            o.x = lhs.x / rhs.x;
            o.y = lhs.y / rhs.y;
            return o;
        }
        public static Vec2f operator *(Vec2f lhs, float rhs)
        {
            Vec2f o;
            o.x = lhs.x * rhs;
            o.y = lhs.y * rhs;
            return o;
        }
        public static Vec2f operator *(float lhs, Vec2f rhs)
        {
            Vec2f o;
            o.x = lhs * rhs.x;
            o.y = lhs * rhs.y;
            return o;
        }
        public static Vec2f operator /(Vec2f lhs, float rhs)
        {
            Vec2f o;
            o.x = lhs.x / rhs;
            o.y = lhs.y / rhs;
            return o;
        }
        public static Vec2f operator /(float lhs, Vec2f rhs)
        {
            Vec2f o;
            o.x = lhs / rhs.x;
            o.y = lhs / rhs.y;
            return o;
        }
    }

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
            Vec2f o;
            o.x = v.x;
            o.y = v.y;
            return o;
        }

        public static implicit operator Vec4f(Vec3f v)
        {
            Vec4f o;
            o.x = v.x;
            o.y = v.y;
            o.z = v.z;
            o.w = 0.0f;
            return o;
        }

        public static Vec3f operator +(Vec3f lhs, Vec3f rhs)
        {
            Vec3f o;
            o.x = lhs.x + rhs.x;
            o.y = lhs.y + rhs.y;
            o.z = lhs.z + rhs.z;
            return o;
        }
        public static Vec3f operator -(Vec3f lhs, Vec3f rhs)
        {
            Vec3f o;
            o.x = lhs.x - rhs.x;
            o.y = lhs.y - rhs.y;
            o.z = lhs.z - rhs.z;
            return o;
        }
        public static Vec3f operator *(Vec3f lhs, Vec3f rhs)
        {
            Vec3f o;
            o.x = lhs.x * rhs.x;
            o.y = lhs.y * rhs.y;
            o.z = lhs.z * rhs.z;
            return o;
        }
        public static Vec3f operator /(Vec3f lhs, Vec3f rhs)
        {
            Vec3f o;
            o.x = lhs.x / rhs.x;
            o.y = lhs.y / rhs.y;
            o.z = lhs.z / rhs.z;
            return o;
        }
        public static Vec3f operator *(Vec3f lhs, float rhs)
        {
            Vec3f o;
            o.x = lhs.x * rhs;
            o.y = lhs.y * rhs;
            o.z = lhs.z * rhs;
            return o;
        }
        public static Vec3f operator *(float lhs, Vec3f rhs)
        {
            Vec3f o;
            o.x = lhs * rhs.x;
            o.y = lhs * rhs.y;
            o.z = lhs * rhs.z;
            return o;
        }
        public static Vec3f operator /(Vec3f lhs, float rhs)
        {
            Vec3f o;
            o.x = lhs.x / rhs;
            o.y = lhs.y / rhs;
            o.z = lhs.z / rhs;
            return o;
        }
        public static Vec3f operator /(float lhs, Vec3f rhs)
        {
            Vec3f o;
            o.x = lhs / rhs.x;
            o.y = lhs / rhs.y;
            o.z = lhs / rhs.z;
            return o;
        }
    }

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
            Vec2f o;
            o.x = v.x;
            o.y = v.y;
            return o;
        }

        public static implicit operator Vec3f(Vec4f v)
        {
            Vec3f o;
            o.x = v.x;
            o.y = v.y;
            o.z = v.z;
            return o;
        }

        public static Vec4f operator +(Vec4f lhs, Vec4f rhs)
        {
            Vec4f o;
            o.x = lhs.x + rhs.x;
            o.y = lhs.y + rhs.y;
            o.z = lhs.z + rhs.z;
            o.w = lhs.w + rhs.w;
            return o;
        }
        public static Vec4f operator -(Vec4f lhs, Vec4f rhs)
        {
            Vec4f o;
            o.x = lhs.x - rhs.x;
            o.y = lhs.y - rhs.y;
            o.z = lhs.z - rhs.z;
            o.w = lhs.w - rhs.w;
            return o;
        }
        public static Vec4f operator *(Vec4f lhs, Vec4f rhs)
        {
            Vec4f o;
            o.x = lhs.x * rhs.x;
            o.y = lhs.y * rhs.y;
            o.z = lhs.z * rhs.z;
            o.w = lhs.w * rhs.w;
            return o;
        }
        public static Vec4f operator /(Vec4f lhs, Vec4f rhs)
        {
            Vec4f o;
            o.x = lhs.x / rhs.x;
            o.y = lhs.y / rhs.y;
            o.z = lhs.z / rhs.z;
            o.w = lhs.w / rhs.w;
            return o;
        }
        public static Vec4f operator *(Vec4f lhs, float rhs)
        {
            Vec4f o;
            o.x = lhs.x * rhs;
            o.y = lhs.y * rhs;
            o.z = lhs.z * rhs;
            o.w = lhs.w * rhs;
            return o;
        }
        public static Vec4f operator *(float lhs, Vec4f rhs)
        {
            Vec4f o;
            o.x = lhs * rhs.x;
            o.y = lhs * rhs.y;
            o.z = lhs * rhs.z;
            o.w = lhs * rhs.w;
            return o;
        }
        public static Vec4f operator /(Vec4f lhs, float rhs)
        {
            Vec4f o;
            o.x = lhs.x / rhs;
            o.y = lhs.y / rhs;
            o.z = lhs.z / rhs;
            o.w = lhs.w / rhs;
            return o;
        }
        public static Vec4f operator /(float lhs, Vec4f rhs)
        {
            Vec4f o;
            o.x = lhs / rhs.x;
            o.y = lhs / rhs.y;
            o.z = lhs / rhs.z;
            o.w = lhs / rhs.w;
            return o;
        }
    }

    public struct Quatf
    {
        public static readonly Quatf Zero = new Quatf();
        public static readonly Quatf Identity = new Quatf(0.0f, 0.0f, 0.0f, 1.0f);

        public float x, y, z, w;

        public Quatf()
        {
            this.x = 0.0f;
            this.y = 0.0f;
            this.z = 0.0f;
            this.w = 0.0f;
        }

        public Quatf(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public Vec3f ToEuler()
        {
            float sinr_cosp = 2.0f * (w * x + y * z);
            float cosr_cosp = 1.0f - 2.0f * (x * x + y * y);

            Vec3f euler;
            euler.x = MathF.Atan2(sinr_cosp, cosr_cosp);

            float sinp = 2.0f * (w * y - z * x);
            if (MathF.Abs(sinp) >= 1.0f)
                euler.y = sinp >= 0 ? MathUtils.HalfPI : -MathUtils.HalfPI;
            else
                euler.y = MathF.Asin(sinp);

            float siny_cosp = 2.0f * (w * z + x * y);
            float cosy_cosp = 1.0f - 2.0f * (y * y + z * z);
            euler.z = MathF.Atan2(siny_cosp, cosy_cosp);

            return euler;
        }

        public static Quatf FromEuler(Vec3f euler)
        {
            float cr = MathF.Cos(euler.x * 0.5f);
            float sr = MathF.Sin(euler.x * 0.5f);
            float cp = MathF.Cos(euler.y * 0.5f);
            float sp = MathF.Sin(euler.y * 0.5f);
            float cy = MathF.Cos(euler.z * 0.5f);
            float sy = MathF.Sin(euler.z * 0.5f);

            Quatf quat;
            quat.w = cr * cp * cy + sr * sp * sy;
            quat.x = sr * cp * cy + cr * sp * sy;
            quat.y = cr * sp * cy + sr * cp * sy;
            quat.z = cr * cp * sy + sr * sp * cy;
            return quat;
        }
    }
}

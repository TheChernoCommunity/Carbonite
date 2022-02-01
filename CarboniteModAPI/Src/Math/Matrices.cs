using System;

namespace ModAPI.Math
{
    public struct Mat2f
    {
        public Vec2f c0, c1;

        public float m00 => c0.x;
        public float m01 => c0.y;
        public float m10 => c1.x;
        public float m11 => c1.y;

        public static implicit operator Mat3f(Mat2f m)
        {
            Mat3f o;
            o.c0 = m.c0;
            o.c1 = m.c1;
            o.c2 = new Vec3f(0.0f, 0.0f, 1.0f);
            return o;
        }
        public static implicit operator Mat4f(Mat2f m)
        {
            Mat4f o;
            o.c0 = m.c0;
            o.c1 = m.c1;
            o.c2 = new Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
            o.c3 = new Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
            return o;
        }

        public static Vec2f operator *(Vec2f lhs, Mat2f rhs)
        {
            Vec2f v;
            v.x = lhs.x * rhs.m00 + lhs.y * rhs.m10;
            v.y = lhs.x * rhs.m01 + lhs.y * rhs.m11;
            return v;
        }

        public static Vec2f operator *(Mat2f lhs, Vec2f rhs)
        {
            Vec2f v;
            v.x = lhs.m00 * rhs.x + lhs.m01 * rhs.y;
            v.y = lhs.m10 * rhs.x + lhs.m11 * rhs.y;
            return v;
        }
    }

    public struct Mat3f
    {
        public Vec3f c0, c1, c2;

        public float m00 => c0.x;
        public float m01 => c0.y;
        public float m02 => c0.z;
        public float m10 => c1.x;
        public float m11 => c1.y;
        public float m12 => c1.z;
        public float m20 => c2.x;
        public float m21 => c2.y;
        public float m22 => c2.z;

        public static implicit operator Mat2f(Mat3f m)
        {
            Mat2f o;
            o.c0 = m.c0;
            o.c1 = m.c1;
            return o;
        }
        public static implicit operator Mat4f(Mat3f m)
        {
            Mat4f o;
            o.c0 = m.c0;
            o.c1 = m.c1;
            o.c2 = m.c2;
            o.c3 = new Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
            return o;
        }
    }

    public struct Mat4f
    {
        public Vec4f c0, c1, c2, c3;

        public float m00 => c0.x;
        public float m01 => c0.y;
        public float m02 => c0.z;
        public float m03 => c0.w;
        public float m10 => c1.x;
        public float m11 => c1.y;
        public float m12 => c1.z;
        public float m13 => c1.w;
        public float m20 => c2.x;
        public float m21 => c2.y;
        public float m22 => c2.z;
        public float m23 => c2.w;
        public float m30 => c3.x;
        public float m31 => c3.y;
        public float m32 => c3.z;
        public float m33 => c3.w;

        public static implicit operator Mat2f(Mat4f m)
        {
            Mat2f o;
            o.c0 = m.c0;
            o.c1 = m.c1;
            return o;
        }
        public static implicit operator Mat3f(Mat4f m)
        {
            Mat3f o;
            o.c0 = m.c0;
            o.c1 = m.c1;
            o.c2 = m.c2;
            return o;
        }
    }
}

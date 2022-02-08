using System;

namespace ModAPI.Math
{
	public struct Mat2f
	{
        public static readonly Mat2f Zero = new Mat2f(Vec2f.Zero, Vec2f.Zero);
        public static readonly Mat2f Identity = new Mat2f();

		public Vec2f c0, c1;

        public Vec2f r0
        {
            get => new Vec2f(m00, m10);
            set
            {
                m00 = value.x;
                m10 = value.y;
            }
        }
        public Vec2f r1
        {
            get => new Vec2f(m01, m11);
            set
            {
                m01 = value.x;
                m11 = value.y;
            }
        }

        public float m00
        {
            get => c0.x;
            set => c0.x = value;
        }
        public float m01
        {
            get => c0.y;
            set => c0.y = value;
        }
        public float m10
        {
            get => c1.x;
            set => c1.x = value;
        }
        public float m11
        {
            get => c1.y;
            set => c1.y = value;
        }

        public Mat2f()
        {
            this.c0 = new Vec2f(1.0f, 0.0f);
            this.c1 = new Vec2f(0.0f, 1.0f);
        }

        public Mat2f(Vec2f c0, Vec2f c1)
        {
            this.c0 = c0;
            this.c1 = c1;
        }

        public static implicit operator Mat3f(Mat2f mat)
        {
            return new Mat3f(mat.c0, mat.c1, new Vec3f(0.0f, 0.0f, 1.0f));
        }

        public static implicit operator Mat4f(Mat2f mat)
        {
            return new Mat4f(mat.c0, mat.c1, new Vec4f(0.0f, 0.0f, 1.0f, 0.0f), new Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
        }

        public static Mat2f operator +(Mat2f lhs, Mat2f rhs)
        {
            return new Mat2f(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1);
        }

        public static Mat2f operator -(Mat2f lhs, Mat2f rhs)
        {
            return new Mat2f(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1);
        }

        public static Mat2f operator *(Mat2f lhs, Mat2f rhs)
        {
            return new Mat2f(lhs.c0 * rhs.r0, lhs.c1 * rhs.r1);
        }

        public static Vec2f operator *(Vec2f lhs, Mat2f rhs)
        {
            return new Vec2f(lhs.x * rhs.m00 + lhs.y * rhs.m10, lhs.x * rhs.m01 + lhs.y * rhs.m11);
        }

        public static Vec2f operator *(Mat2f lhs, Vec2f rhs)
        {
            return new Vec2f(lhs.m00 * rhs.x + lhs.m01 * rhs.y, lhs.m10 * rhs.x + lhs.m11 * rhs.y);
        }

        public float Determinant => m00 * m11 - m10 * m01;

        public Mat2f Transposed
        {
            get
            {
                return new Mat2f(r0, r1);
            }
        }

        public Mat2f Inverted
        {
            get
            {
                float inv = 1.0f / Determinant;
                return new Mat2f(new Vec2f(m11 * inv, -m01 * inv), new Vec2f(m00 * inv, -m10 * inv));
            }
        }

        public Mat2f Negated => new Mat2f(-c0, -c1);
    }
}
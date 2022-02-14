using System;

namespace ModAPI.Math
{
	public struct Mat3f
    {
        public static readonly Mat3f Zero = new Mat3f(Vec3f.Zero, Vec3f.Zero, Vec3f.Zero);
        public static readonly Mat3f Identity = new Mat3f();

        public Vec3f c0, c1, c2;

        public Vec3f r0
        {
            get => new Vec3f(m00, m10, m20);
            set
            {
                m00 = value.x;
                m10 = value.y;
                m20 = value.z;
            }
        }
        public Vec3f r1
        {
            get => new Vec3f(m01, m11, m21);
            set
            {
                m01 = value.x;
                m11 = value.y;
                m21 = value.z;
            }
        }
        public Vec3f r2
        {
            get => new Vec3f(m02, m12, m22);
            set
            {
                m02 = value.x;
                m12 = value.y;
                m22 = value.z;
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
        public float m02
        {
            get => c0.z;
            set => c0.z = value;
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
        public float m12
        {
            get => c1.z;
            set => c1.z = value;
        }
        public float m20
        {
            get => c2.x;
            set => c2.x = value;
        }
        public float m21
        {
            get => c2.y;
            set => c2.y = value;
        }
        public float m22
        {
            get => c2.z;
            set => c2.z = value;
        }

        public Mat3f()
        {
            this.c0 = new Vec3f(1.0f, 0.0f, 0.0f);
            this.c1 = new Vec3f(0.0f, 1.0f, 0.0f);
            this.c2 = new Vec3f(0.0f, 0.0f, 1.0f);
        }

        public Mat3f(Vec3f c0, Vec3f c1, Vec3f c2)
        {
            this.c0 = c0;
            this.c1 = c1;
            this.c2 = c2;
        }

        public static implicit operator Mat2f(Mat3f mat)
        {
            return new Mat2f(mat.c0, mat.c1);
        }

        public static implicit operator Mat4f(Mat3f mat)
        {
            return new Mat4f(mat.c0, mat.c1, mat.c2, new Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
        }

        public static Mat3f operator +(Mat3f lhs, Mat3f rhs)
        {
            return new Mat3f(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2);
        }

        public static Mat3f operator -(Mat3f lhs, Mat3f rhs)
        {
            return new Mat3f(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2);
        }

        public static Mat3f operator *(Mat3f lhs, Mat3f rhs)
        {
            return new Mat3f(lhs.c0 * rhs.r0, lhs.c1 * rhs.r1, lhs.c2 * rhs.r2);
        }

        public static Vec3f operator *(Vec3f lhs, Mat3f rhs)
        {
            return new Vec3f(lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20, lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21, lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22);
        }

        public static Vec3f operator *(Mat3f lhs, Vec3f rhs)
        {
            return new Vec3f(lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z, lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z, lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z);
        }

        public float Determinant => m00 * (m11 * m22 - m12 * m21) + m01 * (m12 * m20 - m10 * m22) + m02 * (m10 * m21 - m11 * m20);

        public Mat3f Transposed
        {
            get
            {
                return new Mat3f(r0, r1, r2);
            }
        }

        public Mat3f Inverted
        {
            get
            {
                float inv = 1.0f / Determinant;
                return new Mat3f(new Vec3f((m11 * m22 - m12 * m21) * inv, (-m01 * m22 + m02 * m21) * inv, (m01 * m12 - m02 * m11) * inv),
                    new Vec3f((-m10 * m22 + m12 * m20) * inv, (m00 * m22 - m02 * m20) * inv, (-m00 * m12 + m02 * m10) * inv),
                    new Vec3f((m10 * m21 - m11 * m20) * inv, (-m00 * m21 + m01 * m20) * inv, (m00 * m11 - m01 * m10) * inv));
            }
        }

        public Mat3f Negated => new Mat3f(-c0, -c1, -c2);
    }
}
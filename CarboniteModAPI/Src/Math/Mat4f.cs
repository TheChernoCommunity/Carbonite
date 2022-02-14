using System;

namespace ModAPI.Math
{
	public struct Mat4f
    {
        public static readonly Mat4f Zero = new Mat4f(Vec4f.Zero, Vec4f.Zero, Vec4f.Zero, Vec4f.Zero);
        public static readonly Mat4f Identity = new Mat4f();

        public Vec4f c0, c1, c2, c3;

        public Vec4f r0
        {
            get => new Vec4f(m00, m10, m20, m30);
            set
            {
                m00 = value.x;
                m10 = value.y;
                m20 = value.z;
                m30 = value.w;
            }
        }
        public Vec4f r1
        {
            get => new Vec4f(m01, m11, m21, m31);
            set
            {
                m01 = value.x;
                m11 = value.y;
                m21 = value.z;
                m31 = value.z;
            }
        }
        public Vec4f r2
        {
            get => new Vec4f(m02, m12, m22, m32);
            set
            {
                m02 = value.x;
                m12 = value.y;
                m22 = value.z;
                m32 = value.w;
            }
        }
        public Vec4f r3
        {
            get => new Vec4f(m03, m13, m23, m33);
            set
            {
                m03 = value.x;
                m13 = value.y;
                m23 = value.z;
                m33 = value.w;
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
        public float m03
        {
            get => c0.w;
            set => c0.w = value;
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
        public float m13
        {
            get => c1.w;
            set => c1.w = value;
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
        public float m23
        {
            get => c2.w;
            set => c2.w = value;
        }
        public float m30
        {
            get => c3.x;
            set => c3.x = value;
        }
        public float m31
        {
            get => c3.y;
            set => c3.y = value;
        }
        public float m32
        {
            get => c3.z;
            set => c3.z = value;
        }
        public float m33
        {
            get => c3.w;
            set => c3.w = value;
        }

        public Mat4f()
        {
            this.c0 = new Vec4f(1.0f, 0.0f, 0.0f, 0.0f);
            this.c1 = new Vec4f(0.0f, 1.0f, 0.0f, 0.0f);
            this.c2 = new Vec4f(0.0f, 0.0f, 1.0f, 0.0f);
            this.c3 = new Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
        }

        public Mat4f(Vec4f c0, Vec4f c1, Vec4f c2, Vec4f c3)
        {
            this.c0 = c0;
            this.c1 = c1;
            this.c2 = c2;
            this.c3 = c3;
        }

        public static implicit operator Mat2f(Mat4f mat)
        {
            return new Mat2f(mat.c0, mat.c1);
        }

        public static implicit operator Mat3f(Mat4f mat)
        {
            return new Mat3f(mat.c0, mat.c1, mat.c2);
        }

        public static Mat4f operator +(Mat4f lhs, Mat4f rhs)
        {
            return new Mat4f(lhs.c0 + rhs.c0, lhs.c1 + rhs.c1, lhs.c2 + rhs.c2, lhs.c3 + rhs.c3);
        }

        public static Mat4f operator -(Mat4f lhs, Mat4f rhs)
        {
            return new Mat4f(lhs.c0 - rhs.c0, lhs.c1 - rhs.c1, lhs.c2 - rhs.c2, lhs.c3 - rhs.c3);
        }

        public static Mat4f operator *(Mat4f lhs, Mat4f rhs)
        {
            return new Mat4f(lhs.c0 * rhs.r0, lhs.c1 * rhs.r1, lhs.c2 * rhs.r2, lhs.c3 * rhs.r3);
        }

        public static Vec4f operator *(Vec4f lhs, Mat4f rhs)
        {
            return new Vec4f(lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20 + lhs.w * rhs.m30, lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21 + lhs.w * rhs.m31, lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22 + lhs.w * rhs.m32, lhs.x * rhs.m03 + lhs.y * rhs.m13 + lhs.z * rhs.m23 + lhs.w * rhs.m33);
        }

        public static Vec4f operator *(Mat4f lhs, Vec4f rhs)
        {
            return new Vec4f(lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z + lhs.m03 * rhs.w,
                lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z + lhs.m13 * rhs.w,
                lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z + lhs.m23 * rhs.w,
                lhs.m30 * rhs.x + lhs.m31 * rhs.y + lhs.m32 * rhs.z + lhs.m33 * rhs.w);
        }

        public static Vec3f operator *(Vec3f lhs, Mat4f rhs)
        {
            return new Vec3f(lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20 + rhs.m30,
                lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21 + rhs.m31,
                lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22 + rhs.m32);
        }

        public static Vec3f operator *(Mat4f lhs, Vec3f rhs)
        {
            return new Vec3f(lhs.m00 * rhs.x + lhs.m01 * rhs.y + lhs.m02 * rhs.z + lhs.m03,
                lhs.m10 * rhs.x + lhs.m11 * rhs.y + lhs.m12 * rhs.z + lhs.m13,
                lhs.m20 * rhs.x + lhs.m21 * rhs.y + lhs.m22 * rhs.z + lhs.m23);
        }

        public float Determinant => (m00 * ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32) - m13 * m22 * m31 - m11 * m23 * m32 - m12 * m21 * m33)) - (m01 * ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32) - m13 * m22 * m30 - m10 * m23 * m32 - m12 * m20 * m33)) + (m02 * ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31) - m13 * m21 * m30 - m10 * m23 * m31 - m11 * m20 * m33)) - (m03 * ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31) - m12 * m21 * m30 - m10 * m22 * m31 - m11 * m20 * m32));

        public Mat4f Transposed
        {
            get
            {
                return new Mat4f(r0, r1, r2, r3);
            }
        }

        public Mat4f Inverted
        {
            get
            {
                float inv = 1.0f / Determinant;

                return new Mat4f(new Vec4f(Determinant3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33) * inv, -Determinant3x3(m01, m02, m03, m21, m22, m23, m31, m32, m33) * inv, Determinant3x3(m01, m02, m03, m11, m12, m13, m31, m32, m33) * inv, -Determinant3x3(m01, m02, m03, m11, m12, m13, m21, m22, m23) * inv),
                    new Vec4f(-Determinant3x3(m10, m12, m13, m20, m22, m23, m30, m32, m33) * inv, Determinant3x3(m00, m02, m03, m20, m22, m23, m30, m32, m33) * inv, -Determinant3x3(m00, m02, m03, m10, m12, m13, m30, m32, m33) * inv, Determinant3x3(m00, m02, m03, m10, m12, m13, m20, m22, m23) * inv),
                    new Vec4f(Determinant3x3(m10, m11, m13, m20, m21, m23, m30, m31, m33) * inv, -Determinant3x3(m00, m01, m03, m20, m21, m23, m30, m31, m33) * inv, Determinant3x3(m00, m01, m03, m10, m11, m13, m30, m31, m33) * inv, -Determinant3x3(m00, m01, m03, m10, m11, m13, m20, m21, m23) * inv),
                    new Vec4f(-Determinant3x3(m10, m11, m12, m20, m21, m22, m30, m31, m32) * inv, Determinant3x3(m00, m01, m02, m20, m21, m22, m30, m31, m32) * inv, -Determinant3x3(m00, m01, m02, m10, m11, m12, m30, m31, m32) * inv, Determinant3x3(m00, m01, m02, m10, m11, m12, m20, m21, m22) * inv));
            }
        }

        internal static float Determinant3x3(float t00, float t01, float t02, float t10, float t11, float t12, float t20, float t21, float t22)
        {
            return t00 * (t11 * t22 - t12 * t21) + t01 * (t12 * t20 - t10 * t22) + t02 * (t10 * t21 - t11 * t20);
        }

        public Mat4f Negated => new Mat4f(-c0, -c1, -c2, -c3);
    }
}
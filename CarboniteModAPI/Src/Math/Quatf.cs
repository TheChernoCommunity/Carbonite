using System;

namespace ModAPI.Math
{
	public class Quatf
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

            return new Quatf(sr * cp * cy + cr * sp * sy, cr * sp * cy + sr * cp * sy, cr * cp * sy + sr * sp * cy, cr * cp * cy + sr * sp * sy);
        }
    }
}
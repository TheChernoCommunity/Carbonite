using System;
using System.Runtime.CompilerServices;

namespace ModAPI.Input
{
    public static class Time
    {
        public static float DeltaTime { get { return GetDeltaTime_Native(); } }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float GetDeltaTime_Native();
    }
}

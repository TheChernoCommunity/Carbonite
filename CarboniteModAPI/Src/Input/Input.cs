using System;
using System.Runtime.CompilerServices;

namespace ModAPI.Input
{
    public static class Input
    {
        public static float GetAxis(string name)
        {
            return GetAxis_Native(name);
        }

        public static bool IsButtonDown(string name)
        {
            return IsButtonDown_Native(name);
        }
        public static bool IsButtonUp(string name)
        {
            return IsButtonUp_Native(name);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float GetAxis_Native(string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool IsButtonDown_Native(string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool IsButtonUp_Native(string name);
    }
}

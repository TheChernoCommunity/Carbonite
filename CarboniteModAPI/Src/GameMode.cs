using System;

namespace ModAPI
{
    public abstract class GameMode
    {
        public Type? ClientCharacterController { get; protected set; }
        public Type? ServerCharacterController { get; protected set; }
    }
}
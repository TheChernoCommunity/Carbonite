using System;

using ModAPI;

namespace BaseMod.Freecam
{
    public class FreecamGameMode : GameMode
    {
        public FreecamGameMode()
        {
            ClientCharacterController = typeof(FreecamClientCharacterController);
            ServerCharacterController = null;
        }
    }
}

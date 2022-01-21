using System;

using ModAPI.ECS;
using ModAPI.Input;
using ModAPI.Math;

namespace BaseMod.Freecam
{
    public class FreecamClientCharacterController : Component
    {
        private Vec3f localFreecamVelocity = Vec3f.Zero;

        public static void Update(FreecamClientCharacterController[] components)
        {
            foreach (var component in components)
            {
                var transform = component.Transform;

                component.localFreecamVelocity.x = Input.GetAxis("move.forward");
                component.localFreecamVelocity.y = Input.GetAxis("move.right");
                component.localFreecamVelocity.z = Input.GetAxis("move.up");

                transform.Translation += transform.Matrix * component.localFreecamVelocity * Time.DeltaTime;

                Vec3f euler = transform.Rotation.ToEuler();
                euler.y += Input.GetAxis("move.turnRight") * Time.DeltaTime;
                euler.z += Input.GetAxis("move.turnDown") * Time.DeltaTime;
                transform.Rotation = Quatf.FromEuler(euler);
            }
        }
    }
}

using System;
using System.Runtime.CompilerServices;

using ModAPI.Math;

namespace ModAPI.ECS
{
    public class Entity
    {
        public ulong ID { get; protected set; }

        public Entity(ulong id)
        {
            ID = id;
        }

        public T AddComponent<T>() where T : Component
        {
            return (T)AddComponent_Native(ID, typeof(T));
        }

        public T GetComponent<T>() where T : Component
        {
            return (T)GetComponent_Native(ID, typeof(T));
        }

        public bool HasComponent<T>() where T : Component
        {
            return GetComponent<T>() != null;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern object AddComponent_Native(ulong entityId, Type type);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern object GetComponent_Native(ulong entityId, Type type);
    }

    public abstract class Component
    {
        public ulong ID { get; protected set; }

        public TransformComponent Transform { get { return GetComponent<TransformComponent>(); } }

        public Entity GetEntity()
        {
            return new Entity(ID);
        }

        public T AddComponent<T>() where T : Component
        {
            return GetEntity().AddComponent<T>();
        }

        public T GetComponent<T>() where T : Component
        {
            return GetEntity().GetComponent<T>();
        }
    }

    public class TransformComponent : Component
    {
        public Vec3f Translation { get { return GetTranslation_Native(ID); } set { SetTranslation_Native(ID, ref value); } }
        public Quatf Rotation { get { return GetRotation_Native(ID); } set { SetRotation_Native(ID, ref value); } }
        public Vec3f Scale { get { return GetScale_Native(ID); } set { SetScale_Native(ID, ref value); } }

        public Mat4f Matrix { get { return GetMatrix_Native(ID); } }

        public Vec3f Forward { get { return Matrix.c0; } }
        public Vec3f Right { get { return Matrix.c1; } }
        public Vec3f Up { get { return Matrix.c2; } }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Vec3f GetTranslation_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetTranslation_Native(ulong entityId, ref Vec3f translation);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Quatf GetRotation_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetRotation_Native(ulong entityId, ref Quatf rotation);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Vec3f GetScale_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetScale_Native(ulong entityId, ref Vec3f scale);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Mat4f GetMatrix_Native(ulong entityId);
    }

    public class CameraComponent : Component
    {
        public float FOV { get { return GetFOV_Native(ID); } set { SetFOV_Native(ID, value); } }
        public float Near { get { return GetNear_Native(ID); } set { SetNear_Native(ID, value); } }
        public float Far { get { return GetFar_Native(ID); } set { SetFar_Native(ID, value); } }

        public Mat4f ProjectionMatrix { get { return GetProjectionMatrix_Native(ID); } }
        public Mat4f ViewMatrix { get { return GetViewMatrix_Native(ID); } }
        public Mat4f ProjectionViewMatrix { get { return GetProjectionViewMatrix_Native(ID); } }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float GetFOV_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetFOV_Native(ulong entityId, float fov);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float GetNear_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetNear_Native(ulong entityId, float near);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern float GetFar_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetFar_Native(ulong entityId, float far);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Mat4f GetProjectionMatrix_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Mat4f GetViewMatrix_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern Mat4f GetProjectionViewMatrix_Native(ulong entityId);
    }

    public class StaticMeshComponent : Component
    {
        public UIntPtr Mesh { get { return GetMesh_Native(ID); } set { SetMesh_Native(ID, value); } }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern UIntPtr GetMesh_Native(ulong entityId);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void SetMesh_Native(ulong entityId, UIntPtr mesh);
    }
}

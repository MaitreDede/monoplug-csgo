using System;
using System.Runtime.CompilerServices;

namespace MonoPlug
{
    partial class ClsMain
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Mono_Msg(string msg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern bool Mono_RegisterConCommand(string name, string description, ConCommandDelegate code, int flags);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Mono_UnregisterConCommand(string name);
    }
}

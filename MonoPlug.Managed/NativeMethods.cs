﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;
using System.Threading;

namespace MonoPlug
{
    internal static class NativeMethods
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_Msg(string msg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_Log(string msg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_DevMsg(string msg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_Warning(string msg);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_Error(string msg);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern UInt64 Mono_RegisterConvar(string name, string description, int flags, string defaultValue);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_UnregisterConvar(UInt64 nativeID);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern UInt64 Mono_RegisterConCommand(string name, string description, int flags, ConCommandDelegate code, ConCommandCompleteDelegate complete);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_UnregisterConCommand(UInt64 nativeId);


        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern string Mono_Convar_GetString(UInt64 nativeID);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_Convar_SetString(UInt64 nativeID, string value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern bool Mono_Convar_GetBoolean(UInt64 nativeID);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_Convar_SetBoolean(UInt64 nativeID, bool value);


        //[MethodImpl(MethodImplOptions.InternalCall)]
        //internal static extern ClsPlayer[] Mono_GetPlayers();

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_AttachConsole();
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_DetachConsole();
        //Below is not native attached

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Attach_LevelShutdown();
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Detach_LevelShutdown();

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Mono_ClientDialogMessage(int client, string title, string message, int a, int r, int g, int b, int level, int time);
    }
}

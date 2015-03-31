﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DotNetPlug
{
    internal static class PluginManagerMono
    {
        private const string Internal = "__Internal";

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void Log(string message);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void ExecuteCommand(string command, out string output, out int length);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern int RegisterCommand(string command, string description, FCVar flags, CommandExecuteDelegate callback);
    }
}

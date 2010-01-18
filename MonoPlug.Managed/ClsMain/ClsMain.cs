using System;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Threading;

namespace MonoPlug
{
    /// <summary>
    /// Main class that handle everything
    /// </summary>
    internal sealed partial class ClsMain : MarshalByRefObject
    {
        #region Private fields
        /// <summary>
        /// Plugin instanciated and running 
        /// </summary>
        private readonly Dictionary<AppDomain, ClsPluginBase> _plugins = new Dictionary<AppDomain, ClsPluginBase>();
        private readonly ReaderWriterLock _lckPlugins = new ReaderWriterLock();

        private Dictionary<UInt64, ConVarEntry> _convars = new Dictionary<UInt64, ConVarEntry>();
        private readonly Dictionary<string, ConCommandEntry> _concommands = new Dictionary<string, ConCommandEntry>();

        [Obsolete("Rewriting", true)]
        private readonly Dictionary<UInt64, ConVarEntry> _ConVarString = new Dictionary<UInt64, ConVarEntry>();

        /// <summary>
        /// Available plugin cache list 
        /// </summary>
        private PluginDefinition[] _pluginCache = null;

        //Internal commands and vars
        private ClsConvar _clr_mono_version = null;
        private ClsConCommand _clr_plugin_list = null;
        private ClsConCommand _clr_plugin_refresh = null;
        private ClsConCommand _clr_plugin_load = null;
        private ClsConCommand _clr_plugin_unload = null;

        private int _mainThreadId = 0;
        private int _queueLength = 0;
        private readonly object _lckThreadSync = new object();
        private ManualResetEvent _waitIn;
        private ManualResetEvent _waitOut;

        private int _isInITCall = 0;
        #endregion

        public ClsMain()
        {
        }
    }
}
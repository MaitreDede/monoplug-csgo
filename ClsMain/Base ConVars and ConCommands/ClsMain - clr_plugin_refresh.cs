﻿using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Reflection;

namespace MonoPlug
{
    partial class ClsMain
    {
        //[ConCommand("clr_plugin_refresh", "Refresh plugin list", FCVAR.FCVAR_GAMEDLL)]
        public void clr_plugin_refresh(string args)
        {
            NativeMethods.Mono_Msg("CB: clr_plugin_refresh Enter\n");
            AppDomain dom = null;
            try
            {
                //Create another domain to gather plugin data
                dom = AppDomain.CreateDomain("GetPlugins");
                string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

                NativeMethods.Mono_Msg("CB: clr_plugin_refresh A\n");

                Msg("CLR: Assembly path is : {0}\n", path);

                NativeMethods.Mono_Msg("CB: clr_plugin_refresh B\n");

                //Instanciate the remote wrapper
                ClsMain main = (ClsMain)dom.CreateInstanceFromAndUnwrap(Assembly.GetExecutingAssembly().CodeBase, typeof(ClsMain).FullName);
                NativeMethods.Mono_Msg("CB: clr_plugin_refresh C\n");
                this._pluginCache = main.Remote_GetPluginsFromDirectory(this, path);
                NativeMethods.Mono_Msg("CB: clr_plugin_refresh D\n");
            }
            catch (Exception ex)
            {
                this._pluginCache = new PluginDefinition[] { };
                NativeMethods.Mono_Msg("CB: clr_plugin_refresh E\n");
                Msg("GetPlugins Error : {0}\n", ex.Message);
                Msg("GetPlugins Error : {0}\n", ex.StackTrace);
            }
            finally
            {
                NativeMethods.Mono_Msg("CB: clr_plugin_refresh F\n");
                if (dom != null)
                {
                    //Destroy remote domain
                    NativeMethods.Mono_Msg("CB: clr_plugin_refresh G\n");
                    AppDomain.Unload(dom);
                }
            }
            NativeMethods.Mono_Msg("CB: clr_plugin_refresh Exit\n");
            Msg("Refreshed {0} plugins\n", this._pluginCache.Length);
        }
    }
}

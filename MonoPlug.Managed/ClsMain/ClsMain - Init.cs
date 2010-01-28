﻿using System;
using System.Collections.Generic;
using System.Text;

namespace MonoPlug
{
    partial class ClsMain
    {
        /// <summary>
        /// Init function for main instance 
        /// </summary>
        internal bool Init()
        {
#if DEBUG
            Console.Write("DBG: ClsMain::Init (enter)\n");
            try
            {

                //NativeMethods.Mono_DevMsg(string.Format("DBG: ClsMain::Init main thread id = {0}\n", this._mainThreadId));
#endif
                //get current thread Id to check for interthread calls
                this._mainThreadId = System.Threading.Thread.CurrentThread.ManagedThreadId;
                //this.DevMsg("DBG: ClsMain::Init (C)\n");
                //try
                //{
                //    int wrkTh;
                //    int compTh;
                //    System.Threading.ThreadPool.GetAvailableThreads(out wrkTh, out compTh);
                //    this.DevMsg("ThreadPool Available : wrk={0} cmp={0}\n", wrkTh, compTh);
                //    System.Threading.ThreadPool.GetMinThreads(out wrkTh, out compTh);
                //    this.DevMsg("ThreadPool Minimum  : wrk={0} cmp={0}\n", wrkTh, compTh);
                //    System.Threading.ThreadPool.GetMaxThreads(out wrkTh, out compTh);
                //    this.DevMsg("ThreadPool Maximum  : wrk={0} cmp={0}\n", wrkTh, compTh);
                //}
                //catch (Exception ex)
                //{
                //    this.Warning(ex);
                //}

                //Register base commands and vars
                this._clr_mono_version = this.RegisterConvar(null, "clr_mono_version", "Get current Mono runtime version", FCVAR.FCVAR_SPONLY | FCVAR.FCVAR_CHEAT | FCVAR.FCVAR_PRINTABLEONLY, this.MonoVersion);
                this._clr_plugin_directory = this.RegisterConvar(null, "clr_plugin_directory", "Assembly plugin search path", FCVAR.FCVAR_SPONLY | FCVAR.FCVAR_CHEAT | FCVAR.FCVAR_PRINTABLEONLY, this.GetAssemblyDirectory());

                this._clr_plugin_list = this.RegisterConCommand(null, "clr_plugin_list", "List available plugins and loaded plugins", FCVAR.FCVAR_NONE, this.clr_plugin_list, null);
                this._clr_plugin_refresh = this.RegisterConCommand(null, "clr_plugin_refresh", "Refresh internal list of plugins", FCVAR.FCVAR_NONE, this.clr_plugin_refresh, null);
                this._clr_plugin_load = this.RegisterConCommand(null, "clr_plugin_load", "Load and start a CLR plugin", FCVAR.FCVAR_NONE, this.clr_plugin_load, this.clr_plugin_load_complete);
                this._clr_plugin_unload = this.RegisterConCommand(null, "clr_plugin_unload", "Unload a CLR plugin", FCVAR.FCVAR_NONE, this.clr_plugin_unload, this.clr_plugin_load_complete);
#if DEBUG
                this._clr_test = this.RegisterConCommand(null, "clr_test", "for developpement purposes only", FCVAR.FCVAR_NONE, this.clr_test, null);
#endif

                this.DevMsg("DBG: ClsMain::Init (OK)\n");
                return true;
#if DEBUG
            }
            catch (Exception ex)
            {
                do
                {
                    Console.WriteLine(ex.GetType().FullName);
                    Console.WriteLine(ex.Message);
                    Console.WriteLine(ex.StackTrace);
                }
                while ((ex = ex.InnerException) != null);

                this.Warning(ex);
                return false;
            }
            finally
            {
                Console.Write("DBG: ClsMain::Init (exit)\n");
            }
#endif
        }

        internal void AllPluginsLoaded()
        {
            //Refresh plugin cache
            this.clr_plugin_refresh(string.Empty, null);
            //TODO load a XML config file, and reload last loaded plugins
        }
    }
}

﻿using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Threading;

namespace MonoPlug
{
    public sealed class ConEvents : ClsPluginBase
    {
        delegate void DT(EventHandler d);

        protected override void Load()
        {
            try
            {
                Msg("ConEvents:: Load in AppDomain '{0}'\n", AppDomain.CurrentDomain.FriendlyName);
                this.LevelShutdown += this.Events_LevelShutdown;
                Msg("ConEvents::Loaded\n");
            }
            catch (Exception ex)
            {
                while (ex != null)
                {
                    Msg(ex.GetType().FullName + "\n");
                    Msg(ex.Message + "\n");
                    Msg(ex.StackTrace + "\n");
                    ex = ex.InnerException;
                }
            }
        }

        protected override void Unload()
        {
            this.LevelShutdown -= this.Events_LevelShutdown;
        }

        public override string Name
        {
            get { return "ConEvents"; }
        }

        public override string Description
        {
            get { return "Dump to console all events that managed code can handle."; }
        }

        private void Events_LevelShutdown(object sender, EventArgs e)
        {
            this.Msg("ConEvents: LevelShutdown\n");
        }

    }
}

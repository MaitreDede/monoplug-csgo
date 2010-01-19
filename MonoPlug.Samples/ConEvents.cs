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
                //this.ClientCommand += this.ClientCommand_Sample;
                this.LevelShutdown += this.Events_LevelShutdown;
                this.ConMessage += this.Events_ConMessage;

                this.ClientPutInServer += this.Events_ClientPutInServer;
                this.ClientDisconnect += this.Events_ClientDisconnect;
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
            try
            {
                Msg("ConEvents::Unload : A\n");
                this.LevelShutdown -= this.Events_LevelShutdown;
                //this.ClientCommand -= this.ClientCommand_Sample;
                this.ConMessage -= this.Events_ConMessage;
                this.ClientPutInServer -= this.Events_ClientPutInServer;
                this.ClientDisconnect -= this.Events_ClientDisconnect;
                Msg("ConEvents::Unload : A\n");
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

        private void Events_ClientCommand(object sender, ClientCommandEventArgs e)
        {
            string name;
            if (e.Client == null)
            {
                name = "<null>";
            }
            else
            {
                name = e.Client.Name ?? "<player name is null>";
            }
            this.Msg("ConEvents: ClientCommand from {0} {1}\n", name);
        }

        private void Events_ClientDisconnect(object sender, ClientEventArgs e)
        {
            this.Msg("Client disconnect : {0}\n", e.Client);
        }

        private void Events_ClientPutInServer(object sender, ClientEventArgs e)
        {
            this.Msg("Client Put in server : {0}\n", e.Client);
        }

        private void Events_ConMessage(object sender, ConMessageEventArgs e)
        {
            //don't msg here, potential loopback
        }
    }
}

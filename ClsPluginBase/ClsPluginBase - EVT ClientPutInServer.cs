﻿using System;
using System.Collections.Generic;
using System.Text;

namespace MonoPlug
{
    partial class ClsPluginBase
    {
        private int _EventCounter_ClientPutInServer = 0;
        private static readonly object _EventToken_ClientPutInServer = new object();

        protected event EventHandler ClientPutInServer
        {
            add
            {
                lock (this._events)
                {
                    this._events.AddHandler(_EventToken_ClientPutInServer, value);
                    if (this._EventCounter_ClientPutInServer++ == 0)
                    {
                        this._main.ClientPutInServer_Add(this);
                    }
                }
            }
            remove
            {
                lock (this._events)
                {
                    this._events.RemoveHandler(_EventToken_ClientPutInServer, value);
                    if (--this._EventCounter_ClientPutInServer == 0)
                    {
                        this._main.ClientPutInServer_Remove(this);
                    }
                }
            }
        }

        internal void Raise_ClientPutInServer(object sender, ClientEventArgs e)
        {
            EventHandler d;
            lock (this._events)
            {
                d = (EventHandler)this._events[_EventToken_ClientPutInServer];
            }
            if (d != null)
            {
                d.Invoke(sender, e);
            }
        }
    }
}

﻿using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace MonoPlug
{
    partial class ClsPluginBase
    {
        private int _EventCounter_LevelShutdown = 0;
        private static readonly object _EventToken_LevelShutdown = new object();

        /// <summary>
        /// Event LevelShutdown
        /// </summary>
        protected event EventHandler LevelShutdown
        {
            add
            {
                lock (this._events)
                {
                    this._events.AddHandler(_EventToken_LevelShutdown, value);
                    if (this._EventCounter_LevelShutdown++ == 0)
                    {
                        this._main.LevelShutdown_Add(this);
                    }
                }
            }
            remove
            {
                lock (this._events)
                {
                    this._events.RemoveHandler(_EventToken_LevelShutdown, value);
                    if (--this._EventCounter_LevelShutdown == 0)
                    {
                        this._main.LevelShutdown_Remove(this);
                    }
                }
            }
        }

        internal void Raise_LevelShutdown(object sender, EventArgs e)
        {
            EventHandler d;
            lock (this._events)
            {
                d = (EventHandler)this._events[_EventToken_LevelShutdown];
            }
            if (d != null)
            {
                d.Invoke(sender, e);
            }
        }
    }
}

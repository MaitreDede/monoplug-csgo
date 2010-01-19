﻿using System;
using System.Collections.Generic;
using System.Text;

namespace MonoPlug
{
    partial class ClsPluginBase
    {
        private int _EventCounter_ConMessage = 0;
        private static readonly object _EventToken_ConMessage = new object();

        /// <summary>
        /// Event raised when a console message has been printed
        /// </summary>
        protected event EventHandler<ConMessageEventArgs> ConMessage
        {
            add
            {
                lock (this._events)
                {
                    this._events.AddHandler(_EventToken_ConMessage, value);
                    if (this._EventCounter_ConMessage++ == 0)
                    {
                        this._main.ConMessage_Add(this);
                    }
                }
            }
            remove
            {
                lock (this._events)
                {
                    this._events.RemoveHandler(_EventToken_ConMessage, value);
                    if (--this._EventCounter_ConMessage == 0)
                    {
                        this._main.ConMessage_Remove(this);
                    }
                }
            }

        }

        internal void Raise_ConMessage(object sender, ConMessageEventArgs e)
        {
            EventHandler d;
            lock (this._events)
            {
                d = (EventHandler)this._events[_EventToken_ConMessage];
            }
            if (d != null)
            {
                d.Invoke(sender, e);
            }
        }
    }
}

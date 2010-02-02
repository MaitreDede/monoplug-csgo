﻿using System;

namespace MonoPlug
{
    /// <summary>
    /// Base class for plugins
    /// </summary>
    public abstract partial class ClsPluginBase : MarshalByRefObject
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        public ClsPluginBase()
        {
        }

        #region Abstracts
        /// <summary>
        /// Plugin name
        /// </summary>
        public abstract string Name { get; }
        /// <summary>
        /// Plugin description
        /// </summary>
        public abstract string Description { get; }
        /// <summary>
        /// Plugin load
        /// </summary>
        protected abstract void Load();
        /// <summary>
        /// Plugin unload
        /// </summary>
        protected abstract void Unload();
        #endregion

        private ClsRemote _proxy;
        private ClsPluginMessage _msg;
        private ClsPluginEvents _events;
        private ClsPluginConItem _entry;
        private ClsPluginThreadPool _pool;
        private ClsPluginDatabase _db;

        internal void Init(ClsRemote proxy, IMessage msg, IEventsAttach anchor, IConItemEntry entry, IThreadPool pool, IDatabase db)
        {
            Check.NonNull("proxy", proxy);
            Check.NonNull("msg", msg);
            Check.NonNull("anchor", anchor);
            Check.NonNull("entry", entry);
            Check.NonNull("pool", pool);
            Check.NonNull("db", db);

            this._proxy = proxy;
            this._msg = new ClsPluginMessage(this, msg);
            this._events = new ClsPluginEvents(this, anchor);
            this._entry = new ClsPluginConItem(this, entry);
            this._pool = new ClsPluginThreadPool(this, pool);
            this._db = new ClsPluginDatabase(this, db);
            this.Load();
        }

        public IMessage Message { get { return this._msg; } }
        public IEvents Events { get { return this._events; } }
        public IConItem ConItems { get { return this._entry; } }
        public IThreadPool ThreadPool { get { return this._pool; } }
        public IDatabase Database { get { return this._db; } }
        internal ClsRemote Proxy { get { return this._proxy; } }
        internal ClsPluginEvents PluginEvents { get { return this._events; } }

        internal void Uninit()
        {
            this.Unload();
        }
    }
}

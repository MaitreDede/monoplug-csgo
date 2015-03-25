#ifndef _DOTNETPLUG_PLUGIN_H_
#define _DOTNETPLUG_PLUGIN_H_

#include <ISmmPlugin.h>
#include "Managed.h"
#include <igameevents.h>
#include <iplayerinfo.h>
#include <sh_vector.h>
#include "engine_wrappers.h"

#if defined WIN32 && !defined snprintf
#define snprintf _snprintf
#endif

class DotNetPlugPlugin : public ISmmPlugin
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AllPluginsLoaded();
public: //Hooks
	void Hook_GameFrame(bool simulating);
	void Hook_ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);

public:
	const char *GetAuthor();
	const char *GetName();
	const char *GetDescription();
	const char *GetURL();
	const char *GetLicense();
	const char *GetVersion();
	const char *GetDate();
	const char *GetLogTag();
};


extern DotNetPlugPlugin g_DotNetPlugPlugin;

PLUGIN_GLOBALVARS();

#endif //_DOTNETPLUG_PLUGIN_H_

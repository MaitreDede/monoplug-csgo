#ifndef _DOTNETPLUG_MANAGED_H_
#define _DOTNETPLUG_MANAGED_H_
#ifdef _WIN32
#pragma once
#endif

#include "Types.h"
#include "Helpers.h"
#include "ManagedCommand.h"
#include "EventListener.h"

class ManagedCommand;

class Managed {

public:
	Managed();
	~Managed();
	bool Init(const char* sBaseDir);
	void Cleanup();

	void Load();
	void Tick();
	void Unload();

	void RaiseCommand(int argc, const char** argv);

	static void Log(const char* msg);
	static void ExecuteCommand(const char* cmd, void** output, int* length);
	static bool RegisterCommand(const char* cmd, const char* description, int flags, int id);
	static void UnregisterCommand(int id);

	void RaiseLevelInit(const char *pMapName, const char *pMapEntities, const char *pOldLevel, const char *pLandmarkName, bool loadGame, bool background);
	void RaiseServerActivate(int clientMax);
	void RaiseLevelShutdown();
	void RaiseClientActive();
	void RaiseClientDisconnect();
	void RaiseClientPutInServer();
	void RaiseClientSettingsChanged();
	void RaiseClientConnect();
	void RaiseClientCommand();
private:
	bool s_inited;
	bool InitPlateform(const char* sAssemblyFile);
	void RaiseCommandPlateform(ManagedCommand* cmd, int argc, const char** argv);

	std::map<const char*, int, char_cmp> m_commandsIndex;
	std::map<int, ManagedCommand*> m_commandsClass;

#ifdef MANAGED_WIN32
private:
	ICLRMetaHost *pMetaHost;
	ICLRRuntimeInfo *pRuntimeInfo;
	// ICorRuntimeHost and ICLRRuntimeHost are the two CLR hosting interfaces
	// supported by CLR 4.0. Here we demo the ICorRuntimeHost interface that 
	// was provided in .NET v1.x, and is compatible with all .NET Frameworks. 
	ICorRuntimeHost *pCorRuntimeHost;

	_AssemblyPtr spAssembly_SystemCore;

	variant_t vtPluginManager;
	_MethodInfo* spPluginManagerTick;
	_MethodInfo* spPluginManagerLoad;
	_MethodInfo* spPluginManagerUnload;
	_MethodInfo* spPluginManagerLoadAssembly;
	_MethodInfo* spPluginManagerRaiseCommand;

	_MethodInfo* spPluginManagerInitWin32Engine;

	_MethodInfo* spPluginManagerLevelInit;
	_MethodInfo* spPluginManagerServerActivate;

	_MethodInfo* spPluginManagerLevelShutdown;
	_MethodInfo* spPluginManagerClientActive;
	_MethodInfo* spPluginManagerClientDisconnect;
	_MethodInfo* spPluginManagerClientPutInServer;
	_MethodInfo* spPluginManagerClientSettingsChanged;
	_MethodInfo* spPluginManagerClientConnect;
	_MethodInfo* spPluginManagerClientCommand;

	LPWSTR pszVersion;
	LPWSTR pszAssemblyName;
	LPWSTR pszClassName;
	LPWSTR pszIfaceName;
#endif
#ifdef MANAGED_MONO
private: //Private members
	MonoDomain *pDomain;
	MonoAssembly *pAssembly;
	MonoImage *pAssemblyImage;
	MonoClass *pStringClass;
	MonoClass *pPluginManagerClass;
	MonoClass *pIPluginManagerClass;

	MonoProperty* pPluginManagerInstanceProperty;
	MonoMethod* pPluginManagerInstancePropertyGetMethod;
	MonoObject* pPluginManagerInstanceObject;

	MonoMethod* pMapCallbacksToMono;

	MonoMethod* pPluginManagerLoadMethod;
	MonoMethod* pPluginManagerLoadMethodImplementation;

	MonoMethod* pPluginManagerTickMethod;
	MonoMethod* pPluginManagerTickMethodImplementation;

	MonoMethod* pPluginManagerUnloadMethod;
	MonoMethod* pPluginManagerUnloadMethodImplementation;

	MonoMethod* pPluginManagerLoadAssemblyMethod;
	MonoMethod* pPluginManagerLoadAssemblyMethodImplementation;

	MonoMethod* pPluginManagerRaiseCommandMethod;
	MonoMethod* pPluginManagerRaiseCommandMethodImplementation;
private: //Private methods
	static void LogMono(MonoString* pMsg);
	static void ExecuteCommandMono(MonoString* pMsg, MonoString* pOutput, int* pLength);
	static void RegisterCommandMono(MonoString* pMsg, MonoString* pDesc, int flags, int id);
#endif

public: //Events
	EventListener* EVT_player_death;
public:
	void RaiseGameEvent(GameEvent e, IGameEvent *event);
};


extern Managed g_Managed;

#endif // _DOTNETPLUG_MANAGED_H_
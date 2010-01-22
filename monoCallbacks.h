#ifndef _MONOCALLBACKS_H_
#define _MONOCALLBACKS_H_

#include "Common.h"
#include "CMonoPlug.h"
#include "CMonoCommand.h"
#include "CMonoConvar.h"

bool LessFunc_uint64(uint64 const& k1, uint64 const& k2);

void Mono_Msg(MonoString*);
void Mono_Log(MonoString*);
void Mono_DevMsg(MonoString* msg);
void Mono_Warning(MonoString* msg);
void Mono_Error(MonoString* msg);

uint64 Mono_RegisterConvar(MonoString* name, MonoString* help, int flags, MonoString* defaultValue, MonoDelegate* changeCallback);
bool Mono_UnregisterConvar(uint64 nativeID);

void Mono_CMonoConvar_ValueChanged(IConVar *var, const char *pOldValue, float flOldValue);

MonoString* Mono_Convar_GetString(uint64 nativeID);
void Mono_Convar_SetString(uint64 nativeID, MonoString* value);
bool Mono_Convar_GetBoolean(uint64 nativeID);
void Mono_Convar_SetBoolean(uint64 nativeID, bool value);

bool Mono_RegisterConCommand(MonoString* name, MonoString* help, MonoDelegate* code, int flags, MonoDelegate* complete);
bool Mono_UnregisterConCommand(MonoString* name);

void Attach_ConMessage();
void Detach_ConMessage();

void Mono_ClientDialogMessage(int client, MonoString* title, MonoString* message, int a, int r, int g, int b, int level, int time);


#endif

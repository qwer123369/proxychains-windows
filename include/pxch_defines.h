#pragma once

#ifndef __PXCH_DEFINES_H__
#define __PXCH_DEFINES_H__

#include "stdafx.h"
#include "dll.h"

#ifdef _LP64
#define PRIdword  "u"
#define PRIudword "u"
#else
#define PRIdword  "lu"
#define PRIudword "lu"
#endif

#define _PREFIX_L(s) L ## s
#define PREFIX_L(s) _PREFIX_L(s)

#define WPRDW L"%" PREFIX_L(PRIdword)

// In characters -- start
#define MAX_DLL_PATH_BUFSIZE 1024
#define MAX_CONFIG_FILE_PATH_BUFSIZE 1024
#define MAX_DLL_FILE_NAME_BUFSIZE 64
#define MAX_DLL_FUNC_NAME_BUFSIZE 64
#define MAX_IPC_PIPE_NAME_BUFSIZE 128
#define MAX_COMMAND_EXEC_PATH_BUFSIZE 512
#define MAX_COMMAND_LINE_BUFSIZE 65536
#define MAX_REMOTE_LOG_BUFSIZE 1024
// In characters -- end

typedef struct _PROXYCHAINS_CONFIG {
	DWORD testNum;
	DWORD dwMasterProcessId;
	BOOL bQuiet;
#ifdef __CYGWIN__
	pid_t pidCygwinSoleChildProc;
#endif
	WCHAR szIpcPipeName[MAX_IPC_PIPE_NAME_BUFSIZE];
	WCHAR szConfigPath[MAX_CONFIG_FILE_PATH_BUFSIZE];
	WCHAR szDllPath[MAX_DLL_PATH_BUFSIZE];
	WCHAR szMinHookDllPath[MAX_DLL_PATH_BUFSIZE];
	WCHAR szCommandLine[MAX_COMMAND_LINE_BUFSIZE];
} PROXYCHAINS_CONFIG;


typedef HMODULE(WINAPI* FpGetModuleHandleW)(LPCWSTR);
typedef HMODULE(WINAPI* FpLoadLibraryW)(LPCWSTR);
typedef FARPROC(WINAPI* FpGetProcAddress)(HMODULE, LPCSTR);
typedef BOOL (WINAPI* FpFreeLibrary)(HMODULE);
typedef DWORD (WINAPI* FpGetLastError)(VOID);

typedef struct _INJECT_REMOTE_DATA {
	UINT32 uStructSize;
	UINT32 uEverExecuted;

	DWORD dwParentPid;

	FpGetModuleHandleW fpGetModuleHandleW;
	FpLoadLibraryW fpLoadLibraryW;
	FpGetProcAddress fpGetProcAddress;
	FpFreeLibrary fpFreeLibrary;
	FpGetLastError fpGetLastError;

	CHAR szInitFuncName[MAX_DLL_FUNC_NAME_BUFSIZE];
	CHAR szCIWCVarName[MAX_DLL_FUNC_NAME_BUFSIZE];
	WCHAR szCygwin1ModuleName[MAX_DLL_FILE_NAME_BUFSIZE];

	DWORD dwErrorCode;
	PROXYCHAINS_CONFIG pxchConfig;
} INJECT_REMOTE_DATA;

#ifdef __CYGWIN__
static const WCHAR g_szDllFileName[] = L"cygproxychains_hook.dll";
#else
static const WCHAR g_szDllFileName[] = L"proxychains_hook.dll";
#endif
static const WCHAR g_szMinHookDllFileName[] = L"MinHook.x64.dll";
extern PXCHDLL_API PROXYCHAINS_CONFIG* g_pPxchConfig;

extern BOOL g_bCurrentlyInWinapiCall;

#endif
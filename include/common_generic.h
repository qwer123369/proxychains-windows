// SPDX-License-Identifier: GPL-2.0-or-later
/* common_generic.h
 * Copyright (C) 2020 Feng Shun.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2 as 
 *   published by the Free Software Foundation, either version 3 of the
 *   License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License version 2 for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   version 2 along with this program. If not, see
 *   <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "defines_generic.h"

extern const wchar_t* g_szRuleTargetDesc[3];

// *_early are per-process instead of per-thread, which will cause race condition, and are only used at early stages of DLL loading and hook initializing
extern wchar_t g_szDumpMemoryBuf_early[PXCH_MAX_DUMP_MEMORY_BUFSIZE];
extern wchar_t g_szErrorMessageBuf_early[PXCH_MAX_ERROR_MESSAGE_BUFSIZE];
extern wchar_t g_szFormatHostPortBuf_early[PXCH_MAX_FORMAT_HOST_PORT_BUFSIZE];

// After the load of Hook DLL, they will be per-thread(in TLS), thread safe; before that they are assigned *_early
extern wchar_t* g_szDumpMemoryBuf;
extern wchar_t* g_szErrorMessageBuf;
extern wchar_t* g_szFormatHostPortBuf;

const wchar_t* FormatHostPortToStr(const void* pHostPort, int iAddrLen);
const wchar_t* DumpMemory(const void* p, int iLength);
void IndexToIp(const PROXYCHAINS_CONFIG* pPxchConfig, PXCH_IP_ADDRESS* pIp, PXCH_UINT32 iIndex);
void IpToIndex(const PROXYCHAINS_CONFIG* pPxchConfig, PXCH_UINT32* piIndex, const PXCH_IP_ADDRESS* pIp);
PXCH_UINT32 OpenConfigurationFile(PROXYCHAINS_CONFIG* pPxchConfig);
PXCH_UINT32 OpenHostsFile(const WCHAR* szHostsFilePath);
PXCH_UINT32 ConfigurationFileReadLine(unsigned long long* pullLineNum, wchar_t* chBuf, size_t cbBufSize);
PXCH_UINT32 HostsFileReadLine(unsigned long long* pullHostsLineNum, wchar_t* chBuf, size_t cbBufSize);
PXCH_UINT32 CloseConfigurationFile();
PXCH_UINT32 CloseHostsFile();
long ConfigurationTellPos();
void ConfigurationRewind();
long HostsTellPos();
void HostsRewind();


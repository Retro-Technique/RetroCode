/**
 *
 * Retro Code
 *
 * MIT License
 *
 * Copyright(c) 2014-2024 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "pch.h"
#include "resource.h"

namespace retro
{
	namespace core
	{

		HRESULT QueryRAMUsage(SIZE_T& uRAMUsage)
		{
			PROCESS_MEMORY_COUNTERS MemoryCounters;
			ZeroMemory(&MemoryCounters, sizeof(PROCESS_MEMORY_COUNTERS));

			BOOL bRet = GetProcessMemoryInfo(GetCurrentProcess(), &MemoryCounters, sizeof(PROCESS_MEMORY_COUNTERS));
			if (!bRet)
			{
				return GetLastError();
			}

			uRAMUsage = MemoryCounters.WorkingSetSize;

			return S_OK;
		}

		HRESULT QueryCPUUsage(DOUBLE& fCPUUsage)
		{
			FILETIME IdleTime;
			FILETIME KernelTime;
			FILETIME UserTime;

			BOOL bRet = GetSystemTimes(&IdleTime, &KernelTime, &UserTime);
			if (!bRet)
			{
				return GetLastError();
			}

			FILETIME CreationTime;
			FILETIME ExitTime;
			FILETIME KernelTimeProcess;
			FILETIME UserTimeProcess;

			bRet = GetProcessTimes(GetCurrentProcess(), &CreationTime, &ExitTime, &KernelTimeProcess, &UserTimeProcess);
			if (!bRet)
			{
				return GetLastError();
			}

			const ULARGE_INTEGER ulIdleTime = { IdleTime.dwLowDateTime, IdleTime.dwHighDateTime };
			const ULARGE_INTEGER ulKernelTime = { KernelTime.dwLowDateTime, KernelTime.dwHighDateTime };
			const ULARGE_INTEGER ulUserTime = { UserTime.dwLowDateTime, UserTime.dwHighDateTime };
			const ULARGE_INTEGER ulKernelTimeProcess = { KernelTimeProcess.dwLowDateTime, KernelTimeProcess.dwHighDateTime };
			const ULARGE_INTEGER ulUserTimeProcess = { UserTimeProcess.dwLowDateTime, UserTimeProcess.dwHighDateTime };

			const DOUBLE fIdle = static_cast<DOUBLE>(ulIdleTime.QuadPart);
			const DOUBLE fKernel = static_cast<DOUBLE>(ulKernelTime.QuadPart) - fIdle;
			const DOUBLE fUser = static_cast<DOUBLE>(ulUserTime.QuadPart);
			
			const DOUBLE fKernelProcess = static_cast<DOUBLE>(ulKernelTimeProcess.QuadPart);
			const DOUBLE fUserProcess = static_cast<DOUBLE>(ulUserTimeProcess.QuadPart);

			fCPUUsage = 100. * (fKernelProcess + fUserProcess) / (fKernel + fUser);

			return S_OK;
		}

		CString SizeToString(SIZE_T uBytes)
		{
			static constexpr const UINT UNITS[] = { IDS_EXT_B, IDS_EXT_KB, IDS_EXT_MB, IDS_EXT_GB, IDS_EXT_TB };
			static constexpr const UINT UNIT_COUNT = ARRAYSIZE(UNITS);
			
			DOUBLE fSize = static_cast<DOUBLE>(uBytes);
			INT nIndex = 0;
			
			while (fSize >= 1024 && nIndex < 4)
			{
				fSize /= 1024;
				nIndex++;
			}

			ASSERT(nIndex >= 0);
			ASSERT(nIndex < UNIT_COUNT);

			CString zSize;
			zSize.Format(_T("%.2f %s"), fSize, I18N(UNITS[nIndex]).GetString());
			
			return zSize;
		}

	}
}
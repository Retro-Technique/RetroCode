/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2024 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#include "pch.h"
#include "resource.h"

namespace retro
{
	namespace core
	{

		HRESULT QueryApplicationPrefPath(LPCTSTR pszOrg, LPCTSTR pszApp, CString& strPrefPath)
		{
			if (!pszOrg)
			{
				return E_INVALIDARG;
			}

			if (!pszApp)
			{
				return E_INVALIDARG;
			}

			HRESULT hr = S_OK;
			LPWSTR pszPath = NULL;

			do
			{
				hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &pszPath);
				if (FAILED(hr))
				{
					break;
				}

				strPrefPath.Append(pszPath);
				strPrefPath += _T('\\');
				strPrefPath += pszOrg;

				BOOL bRet = CreateDirectory(strPrefPath.GetString(), NULL);
				if (!bRet)
				{
					hr = GetLastError();
					break;
				}

				strPrefPath += _T('\\');
				strPrefPath += pszApp;

				bRet = CreateDirectory(strPrefPath.GetString(), NULL);
				if (!bRet)
				{
					hr = GetLastError();
				}

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (pszPath)
			{
				CoTaskMemFree(pszPath);
				pszPath = NULL;
			}

			return hr;
		}

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
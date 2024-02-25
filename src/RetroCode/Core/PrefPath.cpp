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

namespace retro
{
	namespace core
	{

		HRESULT QueryApplicationPrefPath(LPCTSTR lpszOrg, LPCTSTR lpszApp, CString& strPrefPath)
		{
			if (!lpszOrg)
			{
				return E_INVALIDARG;
			}

			if (!lpszApp)
			{
				return E_INVALIDARG;
			}

			HRESULT hr = S_OK;
			LPWSTR lpszPath = NULL;

			do
			{
				hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &lpszPath);
				if (FAILED(hr))
				{
					break;
				}

				strPrefPath.Append(lpszPath);
				strPrefPath += _T('\\');
				strPrefPath += lpszOrg;

				BOOL bRet = CreateDirectory(strPrefPath.GetString(), NULL);
				if (!bRet)
				{
					hr = GetLastError();
					break;
				}

				strPrefPath += _T('\\');
				strPrefPath += lpszApp;

				bRet = CreateDirectory(strPrefPath.GetString(), NULL);
				if (!bRet)
				{
					hr = GetLastError();
				}

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (lpszPath)
			{
				CoTaskMemFree(lpszPath);
				lpszPath = NULL;
			}

			return hr;
		}

	}
}
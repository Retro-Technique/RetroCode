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
	namespace mfc
	{

#pragma region Constructors

		IMPLEMENT_DYNCREATE(CRetroWinApp, CWinAppEx)

		CRetroWinApp::CRetroWinApp()
		{
		}

		CRetroWinApp::~CRetroWinApp()
		{
		}

#pragma endregion
#pragma region Operations

		CString CRetroWinApp::GetVersion() const
		{
			CString strVersion;

			TCHAR szFullPath[1024];

			GetModuleFileName(NULL, szFullPath, ARRAYSIZE(szFullPath));

			DWORD       uVerHnd = 0;
			const DWORD dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &uVerHnd);
			if (dwVerInfoSize)
			{
				if (uVerHnd != 0)
				{
					return strVersion;
				}

				HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
				if (!hMem)
				{
					return strVersion;
				}

				LPSTR pszVffInfo = reinterpret_cast <CHAR*>(GlobalLock(hMem));
				if (!pszVffInfo)
				{
					GlobalFree(hMem);
					return strVersion;
				}

				GetFileVersionInfo(szFullPath, uVerHnd, dwVerInfoSize, pszVffInfo);

				struct LANGANDCODEPAGE
				{
					WORD uLanguage;
					WORD uCodePage;
				}*pTranslate;

				UINT uTranslate = 0;

				BOOL bRet = VerQueryValue(pszVffInfo,
					_T("\\VarFileInfo\\Translation"),
					reinterpret_cast <LPVOID*>(&pTranslate),
					&uTranslate);
				if (!bRet)
				{
					uTranslate = 0;
				}

				struct
				{
					LPCTSTR pszSubBlock;
					LPCTSTR pszBuffer;
					UINT    nBufferLen;
				} Queries[] =
				{
					{ _T("ProductVersion"), NULL, 0 },
					{ _T("ProductName"),    NULL, 0 }
				};
				constexpr const UINT uQueryCount = ARRAYSIZE(Queries);

				for (UINT i = 0; i < uQueryCount; i++)
				{
					for (UINT j = 0; j < (uTranslate / sizeof(LANGANDCODEPAGE)); j++)
					{
						CString strSubBlock;
						strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\%s"),
							pTranslate[j].uLanguage,
							pTranslate[j].uCodePage,
							Queries[i].pszSubBlock);

						bRet = VerQueryValue(reinterpret_cast <LPVOID>(pszVffInfo),
							strSubBlock.GetString(),
							(LPVOID*)&Queries[i].pszBuffer,
							&Queries[i].nBufferLen);
						if (bRet)
						{
							break;
						}
					}

					if (!bRet)
					{
						Queries[i].pszBuffer = _T("???");
					}
				}

				strVersion.Format(_T("%s v%s"), Queries[1].pszBuffer, Queries[0].pszBuffer);

				GlobalUnlock(hMem);
				GlobalFree(hMem);
			}

#ifdef _DEBUG
			strVersion += _T(" DEBUG");
#endif

			return strVersion;
		}

#pragma endregion

	}
}
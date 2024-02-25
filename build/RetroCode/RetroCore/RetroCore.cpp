// RetroCore.cpp : définit les routines d'initialisation pour la DLL.
//

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "version.lib")

extern HINSTANCE g_hInstance;

namespace retro
{
	namespace core
	{

		CString GetVersion()
		{
			CString strVersion;

			TCHAR pszFullPath[1024];
			GetModuleFileName(g_hInstance, pszFullPath, ARRAYSIZE(pszFullPath));

			DWORD uVerHnd = 0;
			const DWORD dwVerInfoSize = GetFileVersionInfoSize(pszFullPath, &uVerHnd);
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

				LPSTR pszVffInfo = reinterpret_cast<CHAR*>(::GlobalLock(hMem));
				if (!pszVffInfo)
				{
					GlobalFree(hMem);
					return strVersion;
				}

				GetFileVersionInfo(pszFullPath, uVerHnd, dwVerInfoSize, pszVffInfo);

				struct LANGANDCODEPAGE
				{
					WORD uLanguage;
					WORD uCodePage;
				} *pTranslate;

				UINT uTranslate = 0;

				BOOL bRet = VerQueryValue(pszVffInfo,
					_T("\\VarFileInfo\\Translation"),
					reinterpret_cast<LPVOID*>(&pTranslate),
					&uTranslate);
				if (!bRet)
				{
					uTranslate = 0;
				}

				struct
				{
					LPCTSTR pszSubBlock;
					LPCTSTR pszBuffer;
					UINT nBufferLen;

				} Queries[] =
				{
					{ _T("ProductVersion"), NULL, 0 },
					{ _T("ProductName"), NULL, 0 }
				};
				constexpr const UINT uQueryCount = ARRAYSIZE(Queries);
				const UINT uTranslateCount = uTranslate / sizeof(LANGANDCODEPAGE);

				for (UINT i = 0; i < uQueryCount; i++)
				{
					for (UINT j = 0; j < uTranslateCount; j++)
					{
						CString strSubBlock;
						strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\%s"),
							pTranslate[j].uLanguage,
							pTranslate[j].uCodePage,
							Queries[i].pszSubBlock);

						bRet = VerQueryValue(reinterpret_cast<LPVOID>(pszVffInfo),
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

	}
}
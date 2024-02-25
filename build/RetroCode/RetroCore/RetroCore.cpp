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

			TCHAR lpszFullPath[1024];
			GetModuleFileName(g_hInstance, lpszFullPath, ARRAYSIZE(lpszFullPath));

			DWORD uVerHnd = 0;
			const DWORD dwVerInfoSize = GetFileVersionInfoSize(lpszFullPath, &uVerHnd);
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

				LPSTR lpszVffInfo = reinterpret_cast<CHAR*>(::GlobalLock(hMem));
				if (!lpszVffInfo)
				{
					GlobalFree(hMem);
					return strVersion;
				}

				GetFileVersionInfo(lpszFullPath, uVerHnd, dwVerInfoSize, lpszVffInfo);

				struct LANGANDCODEPAGE
				{
					WORD uLanguage;
					WORD uCodePage;
				} *pTranslate;

				UINT uTranslate = 0;

				BOOL bRet = VerQueryValue(lpszVffInfo,
					_T("\\VarFileInfo\\Translation"),
					reinterpret_cast<LPVOID*>(&pTranslate),
					&uTranslate);
				if (!bRet)
				{
					uTranslate = 0;
				}

				struct
				{
					LPCTSTR lpszSubBlock;
					LPCTSTR lpszBuffer;
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
							Queries[i].lpszSubBlock);

						bRet = VerQueryValue(reinterpret_cast<LPVOID>(lpszVffInfo),
							strSubBlock.GetString(),
							(LPVOID*)&Queries[i].lpszBuffer,
							&Queries[i].nBufferLen);
						if (bRet)
						{
							break;
						}
					}

					if (!bRet)
					{
						Queries[i].lpszBuffer = _T("???");
					}
				}

				strVersion.Format(_T("%s v%s"), Queries[1].lpszBuffer, Queries[0].lpszBuffer);

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
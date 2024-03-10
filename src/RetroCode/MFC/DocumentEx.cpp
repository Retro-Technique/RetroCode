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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace retro
{
	namespace mfc
	{

#pragma region Constructors

		IMPLEMENT_DYNCREATE(CDocumentEx, CDocument)

		CDocumentEx::CDocumentEx() noexcept
		{
			
		}

		CDocumentEx::~CDocumentEx()
		{

		}

#pragma endregion
#pragma region Overridables

		void CDocumentEx::SetModifiedFlag(BOOL bModified)
		{
			if (bModified != IsModified())
			{
				CDocument::SetModifiedFlag(bModified);

				CString strTitle = GetTitle();
				if (bModified)
				{
					strTitle += "*";
				}
				else
				{
					const INT nLen = strTitle.GetLength();
					const TCHAR cLastChar = strTitle.GetAt(nLen - 1);
					if (cLastChar == _T('*'))
					{
						strTitle.Delete(nLen - 1);
					}
				}

				SetTitle(strTitle);

				POSITION pos = GetFirstViewPosition();
				while (pos)
				{
					CView* pView = GetNextView(pos);
					ASSERT(pView);

					CFrameWnd* pParent = pView->GetParentFrame();
					ASSERT(pParent);

					pParent->OnUpdateFrameTitle(TRUE);
				}
			}
		}

		BOOL CDocumentEx::DoSave(LPCTSTR pszPathName, BOOL bReplace)
		{
			const CString strSaveTitle = GetTitle();

			if (IsModified())
			{
				CString strTitle = strSaveTitle;

				const INT nLen = strTitle.GetLength();
				const TCHAR cLastChar = strTitle.GetAt(nLen - 1);
				if (cLastChar == _T('*'))
				{
					strTitle.Delete(nLen - 1);
					SetTitle(strTitle.GetString());
				}
			}

			if (CDocument::DoSave(pszPathName, bReplace))
			{
				return TRUE;
			}

			SetTitle(strSaveTitle);

			return FALSE;
		}

#pragma endregion
#pragma region Messages

		BEGIN_MESSAGE_MAP(CDocumentEx, CDocument)
		END_MESSAGE_MAP()

#pragma endregion

	}
}
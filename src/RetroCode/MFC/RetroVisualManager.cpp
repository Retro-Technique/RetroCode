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

#pragma comment(lib, "dwmapi.lib")

namespace retro
{
	namespace mfc
	{

#pragma region Constructors

		IMPLEMENT_DYNCREATE(CRetroVisualManager, CMFCVisualManagerOffice2007)

		CRetroVisualManager::CRetroVisualManager()
		{
			CRetroVisualManager::SetStyle(CRetroVisualManager::Office2007_ObsidianBlack);
		}

		CRetroVisualManager::~CRetroVisualManager()
		{

		}

#pragma endregion
#pragma region Operations

		HRESULT CRetroVisualManager::SetWindowDarkAttribute(CWnd* pWnd)
		{
			ASSERT(pWnd);
			ASSERT_VALID(pWnd);

			BOOL bValue = TRUE;
			return DwmSetWindowAttribute(pWnd->GetSafeHwnd(), DWMWA_USE_IMMERSIVE_DARK_MODE, &bValue, sizeof(BOOL));
		}

		void CRetroVisualManager::Apply(CListCtrl* pCtrl)
		{
			ASSERT(pCtrl);
			ASSERT_VALID(pCtrl);

			pCtrl->SetBkColor(GRAY_BACKGROUND);
			pCtrl->SetTextBkColor(GRAY_BACKGROUND);
			pCtrl->SetTextColor(WHITE_FOREGROUND);
		}

		void CRetroVisualManager::Apply(CTreeCtrl* pCtrl)
		{
			ASSERT(pCtrl);
			ASSERT_VALID(pCtrl);

			pCtrl->SetBkColor(GRAY_BACKGROUND);
			pCtrl->SetTextColor(WHITE_FOREGROUND);
			pCtrl->SetLineColor(WHITE_FOREGROUND);
		}

		void CRetroVisualManager::Apply(CMFCPropertyGridCtrl* pCtrl)
		{
			ASSERT(pCtrl);
			ASSERT_VALID(pCtrl);

			pCtrl->SetCustomColors(
				GRAY_BACKGROUND,	/* BACKGROUND */
				WHITE_FOREGROUND,	/* TEXT */
				GRAY_BACKGROUND,	/* GROUP BACKGROUND */
				WHITE_FOREGROUND,	/* GROUP TEXT */
				GRAY_BACKGROUND,	/* DESCRIPTION BACKGROUND */
				WHITE_FOREGROUND,	/* DESCRIPTION TEXT */
				WHITE_FOREGROUND);	/* LINE */
		}

		HBRUSH CRetroVisualManager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT uCtlColor)
		{
			UNREFERENCED_PARAMETER(pWnd);
			ASSERT(pDC);

			static constexpr const struct
			{
				COLORREF clrBkColor;
				COLORREF clrTextColor;
				COLORREF clrRetColor;

			} CTLCOLORS[] =
			{
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_MSGBOX */
				{ WHITE_FOREGROUND, GRAY_BACKGROUND, WHITE_FOREGROUND },	/* CTLCOLOR_EDIT */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_LISTBOX */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_BTN */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_DLG */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_SCROLLBAR */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_STATIC */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND },		/* CTLCOLOR_MAX */
				{ GRAY_BACKGROUND, WHITE_FOREGROUND, GRAY_BACKGROUND }		/* DEFAULT */
			};
			static constexpr const UINT CTLCOLOR_COUNT = ARRAYSIZE(CTLCOLORS);

			ASSERT(uCtlColor < CTLCOLOR_COUNT);

			pDC->SetBkColor(CTLCOLORS[uCtlColor].clrBkColor);
			pDC->SetTextColor(CTLCOLORS[uCtlColor].clrTextColor);
			return CreateSolidBrush(CTLCOLORS[uCtlColor].clrRetColor);
		}

		BOOL CRetroVisualManager::OnEraseBkgnd(CDC* pDC, CWnd* pWnd)
		{
			ASSERT(pDC);
			ASSERT(pWnd);
			ASSERT_VALID(pDC);
			ASSERT_VALID(pWnd);

			CRect rcClient;
			pWnd->GetClientRect(&rcClient);

			pDC->FillSolidRect(rcClient, GRAY_BACKGROUND);

			return TRUE;
		}

#pragma endregion
#pragma region Overridables

		void CRetroVisualManager::OnFillTasksPaneBackground(CDC* pDC, CRect rcWorkArea)
		{
			ASSERT(pDC);
			ASSERT_VALID(pDC);

			pDC->FillSolidRect(rcWorkArea, GRAY_BACKGROUND);
		}

	}
}
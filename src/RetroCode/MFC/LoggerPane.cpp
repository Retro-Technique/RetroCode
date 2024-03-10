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
	namespace mfc
	{

		IMPLEMENT_DYNAMIC(CLoggerPane, CDockablePane)

		CLoggerPane::CLoggerPane()
		{

		}

		CLoggerPane::~CLoggerPane()
		{

		}

		BEGIN_MESSAGE_MAP(CLoggerPane, CDockablePane)
			ON_WM_CREATE()
			ON_WM_SIZE()
			ON_COMMAND(ID_LOGGER_CLEAR, &CLoggerPane::OnClear)
		END_MESSAGE_MAP()

		int CLoggerPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
		{
			if (CDockablePane::OnCreate(lpCreateStruct) == -1)
			{
				return -1;
			}

			if (!m_ctrlToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, AFX_IDW_TOOLBAR + 1) ||
				!m_ctrlToolBar.LoadToolBar(IDR_TOOLBAR_LOGGER, 0, 0, TRUE))
			{
				return -1;
			}

			m_ctrlToolBar.SetPaneStyle(m_ctrlToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
			m_ctrlToolBar.SetPaneStyle(m_ctrlToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
			m_ctrlToolBar.SetRouteCommandsViaFrame(FALSE);

			if (!m_ctrlListBox.Create(LBS_NOINTEGRALHEIGHT | LBS_NOSEL | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, { 0, 0, 0, 0 }, this, 1))
			{
				return -1;
			}

			return 0;
		}

		void CLoggerPane::OnSize(UINT nType, int cx, int cy)
		{
			CDockablePane::OnSize(nType, cx, cy);

			const INT cyTlb = m_ctrlToolBar.CalcFixedLayout(FALSE, TRUE).cy;

			m_ctrlToolBar.SetWindowPos(NULL, 0, 0, cx, cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
			m_ctrlListBox.SetWindowPos(NULL, 0, cyTlb, cx, cy - cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
		}

		void CLoggerPane::OnMessage(const CTime& dtDate, core::ELogLevel eLogLevel, LPCTSTR lpszMessage)
		{
			const CString strISO8601 = dtDate.Format(_T("%FT%T%z"));
			const CString strLevel = core::LogLevelToString(eLogLevel);

			SIZE_T uRAMUsage = 0;
			core::QueryRAMUsage(uRAMUsage);
			const CString strRAMUsage = core::SizeToString(uRAMUsage);

			DOUBLE fCPUUsage = 0.;
			core::QueryCPUUsage(fCPUUsage);
			CString strCPUUsage;
			strCPUUsage.Format(_T("%.0f%%"), fCPUUsage);

			CString strLog;
			strLog.Format(_T("[%s] [%s] [%s] [%s] %s"),
				strISO8601.GetString(),
				strLevel.GetString(),
				strRAMUsage.GetString(),
				strCPUUsage.GetString(),
				lpszMessage);

			m_ctrlListBox.AddString(strLog.GetString());
		}

		void CLoggerPane::OnClear()
		{
			m_ctrlListBox.ResetContent();
		}

	}
}
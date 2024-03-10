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

#pragma once

namespace retro
{
	namespace mfc
	{

		class AFX_EXT_API CLoggerPane : public CDockablePane, public core::ILogObserver
		{
			DECLARE_DYNAMIC(CLoggerPane)

		public:

			CLoggerPane();
			virtual ~CLoggerPane();

		private:

			void OnMessage(const CTime& dtDate, core::ELogLevel eLogLevel, LPCTSTR lpszMessage) override;

		protected:

			DECLARE_MESSAGE_MAP()

		private:

			CPaneToolBar	m_ctrlToolBar;
			CRetroListBox	m_ctrlListBox;

		public:

			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg void OnSize(UINT nType, int cx, int cy);
			afx_msg void OnClear();

		};

	}
}
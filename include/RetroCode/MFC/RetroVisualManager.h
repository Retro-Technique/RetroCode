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

		/**
		 * @brief Custom Retro Technique appearance
		 *
		 */
		class AFX_EXT_API CRetroVisualManager : public CMFCVisualManagerOffice2007
		{
#pragma region Constructors

			/**
			 * @brief Enables objects of CObject-derived classes to be created dynamically at run time
			 *
			 */
			DECLARE_DYNCREATE(CRetroVisualManager)

		public:

			/**
			 * @brief Protected default constructor
			 *
			 */
			CRetroVisualManager();

			/**
			 * @brief Destructor
			 *
			 */
			virtual ~CRetroVisualManager();

#pragma endregion
#pragma region Attributes

		private:

			/**
			 * Static member data
			 */
			static constexpr const COLORREF	DARK_BACKGROUND = RGB(32, 32, 32);
			static constexpr const COLORREF	GRAY_BACKGROUND = RGB(83, 83, 83);
			static constexpr const COLORREF	WHITE_FOREGROUND = RGB(245, 245, 245);

#pragma endregion
#pragma region Operations

		public:

			static HRESULT SetWindowDarkAttribute(CWnd* pWnd);
			static void Apply(CListCtrl* pCtrl);
			static void Apply(CTreeCtrl* pCtrl);
			static void Apply(CMFCPropertyGridCtrl* pCtrl);
			static BOOL OnEraseBkgnd(CDC* pDC, CWnd* pWnd);
			static HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT uCtlColor);

#pragma endregion
#pragma region Overridables

		public:

			/**
			 * @brief The framework calls this method when it fills the background of a CMFCTasksPane control
			 * 
			 * @param pDC A pointer to a device context
			 * @param rcWorkArea A rectangle that specifies the boundaries of the task pane
			 * 
			 */
			void OnFillTasksPaneBackground(CDC* pDC, CRect rcWorkArea) override;

#pragma endregion

		};

	}
}

#define RetroVisualManager retro::mfc::CRetroVisualManager
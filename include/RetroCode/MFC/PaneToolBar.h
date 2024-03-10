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
		 * @brief Adapted ToolBar for Panel
		 *
		 */
		class AFX_EXT_API CPaneToolBar : public CMFCToolBar
		{
#pragma region Constructors

			/**
			 * @brief Generates the C++ header code necessary for a CObject-derived
			 * class that can be serialized
			 *
			 */
			DECLARE_DYNAMIC(CPaneToolBar)

		public:

			/**
			 * @brief Protected default constructor
			 *
			 */
			CPaneToolBar();

			/**
			 * @brief Destructor
			 *
			 */
			virtual ~CPaneToolBar();

#pragma endregion
#pragma region Overridables

		public:

			/**
			 * @brief Used internally
			 * 
			 * @param pTarget Used internally
			 * @param bDisableIfNoHndler Used internally
			 *  
			 */
			void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) override;

			/**
			 * @brief Determines whether the toolbar is displayed in the list of toolbars on the Toolbars pane of the Customize dialog box
			 *
			 * @return TRUE if the toolbar object can be displayed in the list box on the toolbar customization page; otherwise FALSE
			 *
			 */
			BOOL AllowShowOnList() const override;

			/**
			 * @brief Recalculates the size and position of a toolbar
			 *
			 */
			void AdjustLayout() override;

#pragma endregion
#pragma region Messages

		protected:

			DECLARE_MESSAGE_MAP()

#pragma endregion

		};

	}
}
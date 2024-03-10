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
		 * @brief Extension class for MFC CDocument
		 * The purpose of this extension is to add a '*' to the app title when
		 * the document is currently modified
		 * 
		 */
		class AFX_EXT_API CDocumentEx : public CDocument
		{
#pragma region Constructors

		protected:

			/**
			 * @brief Protected default constructor
			 *
			 */
			CDocumentEx() noexcept;

			/**
			 * @brief Enables objects of CObject-derived classes to be created dynamically at run time
			 *
			 */
			DECLARE_DYNCREATE(CDocumentEx)

		public:

			/**
			 * @brief Destructor
			 *
			 */
			virtual ~CDocumentEx();

#pragma endregion
#pragma region Overridables

		public:

			/**
			 * @brief Changes the modified state of a control
			 * 
			 * @param bModified The new value for the control's modified flag
			 *
			 */
			void SetModifiedFlag(BOOL bModified = TRUE) override;

			/**
			 * @brief Save the document
			 *
			 * @param pszPathName Path of the document
			 * @param bReplace Replacement
			 *
			 */
			BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace = TRUE) override;

#pragma endregion
#pragma region Messages

		protected:

			DECLARE_MESSAGE_MAP()

#pragma endregion

		};

	}
}
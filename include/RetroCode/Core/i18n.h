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
	namespace core
	{

		/**
		 * @ingroup core
		 * @brief Translates a string resource ID to the corresponding string
		 *
		 * This function takes a string resource ID as input and returns the corresponding
		 * string from the Windows String Table
		 *
		 * @param uID The string resource ID to translate
		 *
		 * @return A CString containing the translated string
		 *
		 */
		CString AFX_EXT_API Translate(UINT uID);

		/**
		 * @ingroup core
		 * @brief Translates a window that contains an application-supplied message and caption, plus a combination of the predefined icons and pushbuttons
		 *
		 * This function takes strings resource ID as input and returns the corresponding
		 * strings from the Windows String Table
		 *
		 * @param pWnd			A pointer to the owner window of the message box to be created
		 * @param uID			The text string resource ID to translate
		 * @param uIDCaption	The caption string resource ID to translate
		 * @param uType			Specifies the contents and behavior of the message box
		 *
		 * @return See Microsoft MessageBox function documentation
		 *
		 */
		INT AFX_EXT_API MessageBoxStringTable(CWnd* pWnd, UINT uIDText, UINT uIDCaption, UINT uType);

	}
}

#define I18N(id) retro::core::Translate(id)
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
		 * @brief CWinAppEx with a getting version
		 *
		 */
		class AFX_EXT_API CRetroWinApp : public CWinAppEx
		{
#pragma region Constructors

			/**
			 * @brief Enables objects of CObject-derived classes to be created dynamically at run time
			 *
			 */
			DECLARE_DYNCREATE(CRetroWinApp)

		protected:

			/**
			 * @brief Protected default constructor
			 *
			 */
			CRetroWinApp();     

			/**
			 * @brief Destructor
			 *
			 */
			virtual ~CRetroWinApp();

#pragma endregion
#pragma region Operations

		public:

			/**
			 * @brief Get the application version
			 *
			 * @return A string with the format '[ProductName] v[ProductVersion]' if release
			 * or '[ProductName] v[ProductVersion] DEBUG] if debug or '???' if not found
			 * 
			 */
			CString GetVersion() const;

#pragma endregion

		};


	}
}

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
		 * @brief Class that represents a generic resource
		 *
		 */
		class AFX_EXT_API CResource : public CObjectEx
		{
		public:

			/**
			 * @brief Adds the ability to access run-time information about an object's class 
			 * when deriving a class from CObjectEx
			 *
			 */
			DECLARE_DYNAMIC(CResource);

		protected:

			/**
			 * @brief Protected default constructor
			 *
			 */
			CResource();

		public:

			/**
			 * @brief Destructor
			 *
			 */
			virtual ~CResource();

		private:

			/**
			 * @brief Deleted copy constructor
			 *
			 */
			CResource(const CResource& Resource) = delete;

			/**
			 * @brief Deleted copy assignment
			 *
			 */
			void operator=(const CResource& Resource) = delete;

		public:

			/**
			 * @brief Loads a resource from a file
			 * 
			 * @param pszFileName The name of the file to load the resource from
			 * 
			 * @return A HRESULT value indicating the success or failure of the operation
			 *
			 */
			virtual HRESULT LoadFromFile(LPCTSTR pszFileName);

			/**
			 * @brief Loads a resource from a memory buffer
			 *
			 * @param pData A pointer to the memory buffer containing the resource data
			 * @param uSize The size of the memory buffer in bytes
			 *
			 * @return A HRESULT value indicating the success or failure of the operation
			 *
			 */
			virtual HRESULT LoadFromMemory(LPCVOID pData, DWORD uSize);

			/**
			 * @brief Loads a resource from a module name
			 *
			 * @param pszModule		The name of the module that contains the resource
			 * @param pszResourceName	The name of the resource to load
			 *
			 * @return A HRESULT value indicating the success or failure of the operation
			 *
			 */
			virtual HRESULT LoadFromResource(LPCTSTR pszModule, LPCTSTR pszResourceName);

			/**
			 * @brief Loads a resource from a module handle
			 *
			 * @param hModule			A handle to the module that contains the resource
			 * @param pszResourceName	The name of the resource to load
			 *
			 * @return A HRESULT value indicating the success or failure of the operation
			 *
			 */
			virtual HRESULT LoadFromResource(HMODULE hModule, LPCTSTR pszResourceName);

		public:

#ifdef _DEBUG
			/**
			 * @brief Produces a diagnostic dump of the object
			 *
			 * @param dc The diagnostic dump context for dumping
			 *
			 */
			void Dump(CDumpContext& dc) const override;

			/**
			 * @brief Validates the object's integrity
			 *
			 */
			void AssertValid() const override;
#endif

			
		};

	}
}
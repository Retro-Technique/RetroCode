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
		 * @brief Encode to Base64 format
		 *
		 * @param pBuffer	Buffer to encode
		 * @param uSize	Size of the buffer \a pBuffer
		 * @param strOut	Encoding result
		 *
		 * @return S_OK if succeeded
		 *
		 */
		HRESULT AFX_EXT_API Base64Encode(LPCVOID pBuffer, UINT_PTR uSize, CString& strOut);

		/**
		 * @ingroup core
		 * @brief Encode to Base64 format
		 *
		 * @param lpszIn	String to encode
		 * @param strOut	Encoding result
		 *
		 * @return S_OK if succeeded
		 *
		 */
		HRESULT AFX_EXT_API Base64Encode(LPCTSTR lpszIn, CString& strOut);

		/**
		 * @ingroup core
		 * @brief Preparation for decoding
		 *
		 * You must first call this function before calling Base64Decode
		 * to know the size of the buffer that will contain the decoding
		 * result.
		 *
		 * @param lpszIn	Base64 string to decode
		 *
		 * @return Required buffer size
		 *
		 * @see Base64Decode
		 *
		 */
		UINT_PTR AFX_EXT_API Base64QuerySize(LPCTSTR lpszIn);

		/**
		 * @ingroup core
		 * @brief Decode from Base64 format
		 *
		 * @param lpszIn	Base64 string to decode
		 * @param pBuffer	Buffer previously allocated by you
		 * @param uSize	Size of the buffer \a pBuffer
		 *
		 * @return S_OK if succeeded
		 *
		 * @see Base64QuerySize
		 *
		 */
		HRESULT AFX_EXT_API Base64Decode(LPCTSTR lpszIn, LPVOID pBuffer, UINT_PTR uSize);

	}
}
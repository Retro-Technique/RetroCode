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
		 * @brief Load an image from a file into an IWICBitmap
		 *
		 * @param pszFileName[in] Path to image file
		 * @param ppBitmap[out] Image buffer
		 * @param tFormat[in] Image format
		 * @param pExternalFactory[in] External factory
		 * 
		 * @note If no factory is provided, it tries using Direct2D factory if any
		 *
		 * @return S_OK if successfully loading the file
		 *
		 */
		HRESULT AFX_EXT_API LoadFromFile(LPCTSTR pszFileName, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat = GUID_WICPixelFormat32bppRGBA, IWICImagingFactory* pExternalFactory = NULL);

		/**
		 * @ingroup core
		 * @brief Load an image from a memory buffer into an IWICBitmap
		 *
		 * @param pData[in] Memory buffer address
		 * @param uSize[in] Memory buffer size in bytes
		 * @param ppBitmap[out] Image buffer
		 * @param tFormat[in] Image format
		 * @param pExternalFactory[in] External factory
		 *
		 * @note If no factory is provided, it tries using Direct2D factory if any
		 *
		 * @return S_OK if successfully loading the memory buffer
		 *
		 */
		HRESULT AFX_EXT_API LoadFromMemory(LPCVOID pData, DWORD uSize, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat = GUID_WICPixelFormat32bppRGBA, IWICImagingFactory* pExternalFactory = NULL);

		HRESULT AFX_EXT_API LoadFromResource(HMODULE hModule, LPCTSTR pszResourceName, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat = GUID_WICPixelFormat32bppRGBA, IWICImagingFactory* pExternalFactory = NULL);


		HRESULT AFX_EXT_API LoadFromResource(LPCTSTR pszModule, LPCTSTR pszResourceName, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat = GUID_WICPixelFormat32bppRGBA, IWICImagingFactory* pExternalFactory = NULL);

		
		/**
		 * @ingroup core
		 * @brief Save an IWICBitmap into a file
		 *
		 * @param pszFileName[in] Path to image file
		 * @param pBitmap[out] Image buffer
		 * @param tFormat[in] Image format
		 * @param pExternalFactory[in] External factory
		 *
		 * @note If no factory is provided, it tries using Direct2D factory if any
		 *
		 * @return S_OK if successfully saving the file
		 *
		 */
		HRESULT AFX_EXT_API SaveToFile(LPCTSTR pszFileName, IWICBitmap* pBitmap, GUID tFormat = GUID_ContainerFormatPng, IWICImagingFactory* pExternalFactory = NULL);

	}
}
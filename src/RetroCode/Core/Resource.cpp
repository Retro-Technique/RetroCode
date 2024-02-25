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

namespace retro
{
	namespace core
	{

		IMPLEMENT_DYNAMIC(CResource, CObjectEx);

		CResource::CResource()
		{

		}

		CResource::~CResource()
		{

		}

		HRESULT CResource::LoadFromFile(LPCTSTR lpszFileName)
		{
			UNREFERENCED_PARAMETER(lpszFileName);

			return E_NOTIMPL;
		}

		HRESULT CResource::LoadFromMemory(LPCVOID pData, DWORD uSize)
		{
			UNREFERENCED_PARAMETER(pData);
			UNREFERENCED_PARAMETER(uSize);

			return E_NOTIMPL;
		}

		HRESULT CResource::LoadFromResource(LPCTSTR lpszModule, LPCTSTR lpszResourceName)
		{
			if (!lpszModule)
			{
				return E_INVALIDARG;
			}

			if (!lpszResourceName)
			{
				return E_INVALIDARG;
			}

			HMODULE hModule = NULL;
			HRESULT hr = S_OK;

			do
			{
				hModule = AfxLoadLibrary(lpszModule);
				if (!hModule)
				{
					hr = GetLastError();
					break;
				}

				hr = LoadFromResource(hModule, lpszResourceName);

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (hModule)
			{
				AfxFreeLibrary(hModule);
			}

			return hr;
		}

		HRESULT CResource::LoadFromResource(HMODULE hModule, LPCTSTR lpszResourceName)
		{
			if (!hModule)
			{
				return E_INVALIDARG;
			}

			if (!lpszResourceName)
			{
				return E_INVALIDARG;
			}

			HRSRC hrSrc = FindResource(hModule, lpszResourceName, RT_RCDATA);
			if (!hrSrc)
			{
				return GetLastError();
			}

			HGLOBAL hGlobal = LoadResource(hModule, hrSrc);
			if (!hGlobal)
			{
				return GetLastError();
			}

			const DWORD uSize = SizeofResource(hModule, hrSrc);
			if (!uSize)
			{
				return GetLastError();
			}

			LPVOID pData = LockResource(hGlobal);
			if (!pData)
			{
				return GetLastError();
			}

			HRESULT hr = LoadFromMemory(pData, uSize);

			UnlockResource(hGlobal);

			return hr;
		}

#ifdef _DEBUG

		void CResource::Dump(CDumpContext& dc) const
		{
			CObjectEx::Dump(dc);
		}

		void CResource::AssertValid() const
		{
			CObjectEx::AssertValid();
		}

#endif

	}
}
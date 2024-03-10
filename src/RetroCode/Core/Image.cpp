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

		static inline IWICImagingFactory* GetImagingFactory(IWICImagingFactory* pExternalFactory)
		{
			IWICImagingFactory* pFactory = pExternalFactory;
			if (!pFactory)
			{
				_AFX_D2D_STATE* pState = AfxGetD2DState();
				if (pState)
				{
					pFactory = pState->GetWICFactory();
				}
			}

			return pFactory;
		}

		HRESULT LoadFromFile(LPCTSTR pszFileName, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat, IWICImagingFactory* pExternalFactory)
		{
			if (!AfxIsValidString(pszFileName, MAX_PATH))
			{
				return E_INVALIDARG;
			}

			if (*ppBitmap)
			{
				return E_INVALIDARG;
			}

			IWICImagingFactory* pFactory = GetImagingFactory(pExternalFactory);			
			if (!pFactory)
			{
				return E_NOT_VALID_STATE;
			}
			
			HRESULT hr = S_OK;
			IWICStream* pStream = NULL;
			IWICBitmapDecoder* pDecoder = NULL;
			IWICBitmapFrameDecode* pFrame = NULL;
			IWICFormatConverter* pConverterFrame = NULL;
			
			do
			{
				hr = pFactory->CreateStream(&pStream);
				if (FAILED(hr))
				{
					break;
				}

				hr = pStream->InitializeFromFilename(pszFileName, GENERIC_READ);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateDecoderFromFilename(pszFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
				if (FAILED(hr))
				{
					break;
				}

				hr = pDecoder->GetFrame(0, &pFrame);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateFormatConverter(&pConverterFrame);
				if (FAILED(hr))
				{
					break;
				}

				hr = pConverterFrame->Initialize(pFrame,
					tFormat,
					WICBitmapDitherTypeNone,
					NULL,
					0.,
					WICBitmapPaletteTypeCustom);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateBitmapFromSource(pConverterFrame, WICBitmapCacheOnDemand, ppBitmap);
				if (FAILED(hr))
				{
					break;
				}

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (pConverterFrame)
			{
				pConverterFrame->Release();
				pConverterFrame = NULL;
			}

			if (pFrame)
			{
				pFrame->Release();
				pFrame = NULL;
			}

			if (pDecoder)
			{
				pDecoder->Release();
				pDecoder = NULL;
			}

			if (pStream)
			{
				pStream->Release();
				pStream = NULL;
			}

			return hr;
		}

		HRESULT LoadFromMemory(LPCVOID pData, DWORD uSize, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat, IWICImagingFactory* pExternalFactory)
		{
			if (!AfxIsValidAddress(pData, uSize, FALSE))
			{
				return E_INVALIDARG;
			}

			if (*ppBitmap)
			{
				return E_INVALIDARG;
			}

			IWICImagingFactory* pFactory = GetImagingFactory(pExternalFactory);
			if (!pFactory)
			{
				return E_NOT_VALID_STATE;
			}

			HRESULT hr = S_OK;
			IWICStream* pStream = NULL;
			IWICBitmapDecoder* pDecoder = NULL;
			IWICBitmapFrameDecode* pFrame = NULL;
			IWICFormatConverter* pConverterFrame = NULL;

			do
			{
				hr = pFactory->CreateStream(&pStream);
				if (FAILED(hr))
				{
					break;
				}

				hr = pStream->InitializeFromMemory(reinterpret_cast<BYTE*>(const_cast<LPVOID>(pData)), uSize);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateDecoderFromStream(pStream, NULL, WICDecodeMetadataCacheOnDemand, &pDecoder);
				if (FAILED(hr))
				{
					break;
				}

				hr = pDecoder->GetFrame(0, &pFrame);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateFormatConverter(&pConverterFrame);
				if (FAILED(hr))
				{
					break;
				}

				hr = pConverterFrame->Initialize(pFrame,
					tFormat,
					WICBitmapDitherTypeNone,
					NULL,
					0.,
					WICBitmapPaletteTypeCustom);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateBitmapFromSource(pConverterFrame, WICBitmapCacheOnDemand, ppBitmap);
				if (FAILED(hr))
				{
					break;
				}

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (pConverterFrame)
			{
				pConverterFrame->Release();
				pConverterFrame = NULL;
			}

			if (pFrame)
			{
				pFrame->Release();
				pFrame = NULL;
			}

			if (pDecoder)
			{
				pDecoder->Release();
				pDecoder = NULL;
			}

			if (pStream)
			{
				pStream->Release();
				pStream = NULL;
			}

			return hr;
		}

		HRESULT LoadFromResource(HMODULE hModule, LPCTSTR pszResourceName, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat, IWICImagingFactory* pExternalFactory)
		{
			if (!hModule)
			{
				return E_INVALIDARG;
			}

			if (!AfxIsValidString(pszResourceName))
			{
				return E_INVALIDARG;
			}

			if (*ppBitmap)
			{
				return E_INVALIDARG;
			}

			HRSRC hrSrc = FindResource(hModule, pszResourceName, RT_RCDATA);
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

			HRESULT hr = LoadFromMemory(pData, uSize, ppBitmap, tFormat, pExternalFactory);

			UnlockResource(hGlobal);

			return hr;
		}

		HRESULT LoadFromResource(LPCTSTR pszModule, LPCTSTR pszResourceName, IWICBitmap** ppBitmap, REFWICPixelFormatGUID tFormat, IWICImagingFactory* pExternalFactory)
		{
			if (!AfxIsValidString(pszModule, MAX_PATH))
			{
				return E_INVALIDARG;
			}

			if (!AfxIsValidString(pszResourceName))
			{
				return E_INVALIDARG;
			}

			if (*ppBitmap)
			{
				return E_INVALIDARG;
			}

			HMODULE hModule = NULL;
			HRESULT hr = S_OK;

			do
			{
				hModule = AfxLoadLibrary(pszModule);
				if (!hModule)
				{
					hr = GetLastError();
					break;
				}

				hr = LoadFromResource(hModule, pszResourceName, ppBitmap, tFormat, pExternalFactory);

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (hModule)
			{
				AfxFreeLibrary(hModule);
			}

			return hr;
		}

		HRESULT SaveToFile(LPCTSTR pszFileName, IWICBitmap* pBitmap, GUID tFormat, IWICImagingFactory* pExternalFactory)
		{
			if (!AfxIsValidString(pszFileName, MAX_PATH))
			{
				return E_INVALIDARG;
			}

			if (!pBitmap)
			{
				return E_INVALIDARG;
			}

			IWICImagingFactory* pFactory = GetImagingFactory(pExternalFactory);
			if (!pFactory)
			{
				return E_NOT_VALID_STATE;
			}

			HRESULT hr = S_OK;
			IWICStream* pStream = NULL;
			IWICBitmapEncoder* pEncoder = NULL;
			IWICBitmapFrameEncode* pFrame = NULL;
			IPropertyBag2* pPropertyBag = NULL;

			do
			{
				hr = pFactory->CreateStream(&pStream);
				if (FAILED(hr))
				{
					break;
				}

				hr = pStream->InitializeFromFilename(pszFileName, GENERIC_WRITE);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFactory->CreateEncoder(tFormat, NULL, &pEncoder);
				if (FAILED(hr))
				{
					break;
				}

				hr = pEncoder->Initialize(pStream, WICBitmapEncoderNoCache);
				if (FAILED(hr))
				{
					break;
				}

				hr = pEncoder->CreateNewFrame(&pFrame, &pPropertyBag);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFrame->Initialize(pPropertyBag);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFrame->WriteSource(pBitmap, NULL);
				if (FAILED(hr))
				{
					break;
				}

				hr = pFrame->Commit();
				if (FAILED(hr))
				{
					break;
				}

				hr = pEncoder->Commit();
				if (FAILED(hr))
				{
					break;
				}

			} while (RETRO_NULL_WHILE_LOOP_CONDITION);

			if (pPropertyBag)
			{
				pPropertyBag->Release();
				pPropertyBag = NULL;
			}

			if (pFrame)
			{
				pFrame->Release();
				pFrame = NULL;
			}

			if (pEncoder)
			{
				pEncoder->Release();
				pEncoder = NULL;
			}

			if (pStream)
			{
				pStream->Release();
				pStream = NULL;
			}

			return hr;
		}

	}
}
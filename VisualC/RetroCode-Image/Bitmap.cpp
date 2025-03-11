/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#include "pch.h"

namespace retro
{
	namespace image
	{

#pragma region Constructors

		IMPLEMENT_DYNAMIC(CBitmapRGBA, CObject)

		CBitmapRGBA::CBitmapRGBA()
			: m_spFactory(AfxGetD2DState() ? AfxGetD2DState()->GetWICFactory() : NULL)
			, m_spBitmap(NULL)
			, m_spLock(NULL)
		{

		}

		CBitmapRGBA::CBitmapRGBA(_In_ IWICImagingFactory* pExternalFactory)
			: m_spFactory(pExternalFactory)
			, m_spBitmap(NULL)
			, m_spLock(NULL)
		{
			
		}

#pragma endregion
#pragma region Operations

		void CBitmapRGBA::Create(_In_ UINT uWidth, _In_ UINT uHeight)
		{
			if (const HRESULT hr = m_spFactory->CreateBitmap(uWidth, uHeight, GUID_WICPixelFormat32bppPRGBA, WICBitmapCacheOnLoad, &m_spBitmap); FAILED(hr))
			{
				throw hr;
			}
		}

		void CBitmapRGBA::Create(_In_ const CSize& szBitmap)
		{
			Create(szBitmap.cx, szBitmap.cy);
		}

		void CBitmapRGBA::LoadFromFile(_In_z_ LPCTSTR pszFileName)
		{
			if (!AfxIsValidString(pszFileName, MAX_PATH))
			{
				AfxThrowInvalidArgException();
			}

			CComPtr<IWICStream> spStream;
			if (const HRESULT hr = m_spFactory->CreateStream(&spStream); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapDecoder> spDecoder;
			if (const HRESULT hr = m_spFactory->CreateDecoderFromFilename(pszFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &spDecoder); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapFrameDecode> spFrame;
			if (const HRESULT hr = spDecoder->GetFrame(0, &spFrame); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICFormatConverter> spConverter;
			if (const HRESULT hr = m_spFactory->CreateFormatConverter(&spConverter); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spConverter->Initialize(spFrame, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = m_spFactory->CreateBitmapFromSource(spConverter, WICBitmapCacheOnLoad, &m_spBitmap); FAILED(hr))
			{
				throw hr;
			}
		}

		void CBitmapRGBA::LoadFromMemory(_In_reads_bytes_(uSize) LPCVOID pData, _In_ DWORD uSize)
		{
			if (!AfxIsValidAddress(pData, uSize, FALSE))
			{
				AfxThrowInvalidArgException();
			}

			CComPtr<IWICStream> spStream;
			if (const HRESULT hr = m_spFactory->CreateStream(&spStream); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spStream->InitializeFromMemory(static_cast<BYTE*>(const_cast<LPVOID>(pData)), uSize); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapDecoder> spDecoder;
			if (const HRESULT hr = m_spFactory->CreateDecoderFromStream(spStream, NULL, WICDecodeMetadataCacheOnDemand, &spDecoder); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapFrameDecode> spFrame;
			if (const HRESULT hr = spDecoder->GetFrame(0, &spFrame); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICFormatConverter> spConverter;
			if (const HRESULT hr = m_spFactory->CreateFormatConverter(&spConverter); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spConverter->Initialize(spFrame, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = m_spFactory->CreateBitmapFromSource(spConverter, WICBitmapCacheOnLoad, &m_spBitmap); FAILED(hr))
			{
				throw hr;
			}
		}

		void CBitmapRGBA::LoadFromResource(_In_ HMODULE hModule, _In_z_ LPCTSTR pszResourceName)
		{
			if (!hModule)
			{
				AfxThrowInvalidArgException();
			}

			if (!AfxIsValidString(pszResourceName))
			{
				AfxThrowInvalidArgException();
			}

			HRSRC hrSrc = FindResource(hModule, pszResourceName, RT_RCDATA);
			if (!hrSrc)
			{
				throw GetLastError();
			}

			HGLOBAL hGlobal = LoadResource(hModule, hrSrc);
			if (!hGlobal)
			{
				throw GetLastError();
			}

			const DWORD uSize = SizeofResource(hModule, hrSrc);
			if (!uSize)
			{
				throw GetLastError();
			}

			LPVOID pData = LockResource(hGlobal);
			if (!pData)
			{
				throw GetLastError();
			}

			LoadFromMemory(pData, uSize);

			UnlockResource(hGlobal);
		}

		void CBitmapRGBA::LoadFromResource(_In_z_ LPCTSTR pszModule, _In_z_ LPCTSTR pszResourceName)
		{
			if (!AfxIsValidString(pszModule, MAX_PATH))
			{
				AfxThrowInvalidArgException();
			}

			if (!AfxIsValidString(pszResourceName))
			{
				AfxThrowInvalidArgException();
			}

			HMODULE hModule = AfxLoadLibrary(pszModule);
			if (!hModule)
			{
				throw GetLastError();
			}

			LoadFromResource(hModule, pszResourceName);

			AfxFreeLibrary(hModule);
		}

		void CBitmapRGBA::SaveToFile(_In_z_ LPCTSTR pszFileName, _In_ const GUID& tFormat)
		{
			if (!AfxIsValidString(pszFileName, MAX_PATH))
			{
				AfxThrowInvalidArgException();
			}

			CComPtr<IWICStream> spStream;
			if (const HRESULT hr = m_spFactory->CreateStream(&spStream); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spStream->InitializeFromFilename(pszFileName, GENERIC_WRITE); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapEncoder> spEncoder;
			if (const HRESULT hr = m_spFactory->CreateEncoder(tFormat, NULL, &spEncoder); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spEncoder->Initialize(spStream, WICBitmapEncoderNoCache); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapFrameEncode> spFrame;
			CComPtr<IPropertyBag2> spPropertyBag;
			if(const HRESULT hr = spEncoder->CreateNewFrame(&spFrame, &spPropertyBag); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->Initialize(spPropertyBag); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->WriteSource(m_spBitmap, NULL); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->Commit(); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spEncoder->Commit(); FAILED(hr))
			{
				throw hr;
			}
		}

		void CBitmapRGBA::SaveToMemory(_Outptr_ LPVOID* ppData, _Out_ DWORD& uSize, _In_ const GUID& tFormat)
		{
			if (!ppData)
			{
				AfxThrowInvalidArgException();
			}

			*ppData = NULL;

			CComPtr<IWICStream> spStream;
			if (const HRESULT hr = m_spFactory->CreateStream(&spStream); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICComponentInfo> spComponentInfo;
			if (const HRESULT hr = m_spFactory->CreateComponentInfo(tFormat, &spComponentInfo); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICPixelFormatInfo> spPixelFormatInfo;
			if (const HRESULT hr = spComponentInfo->QueryInterface(IID_IWICPixelFormatInfo, reinterpret_cast<void**>(&spPixelFormatInfo)); FAILED(hr))
			{
				throw hr;
			}

			UINT uBitsPerPixel = 0u;
			if (const HRESULT hr = spPixelFormatInfo->GetBitsPerPixel(&uBitsPerPixel); FAILED(hr))
			{
				throw hr;
			}

			UINT uWidth = 0u;
			UINT uHeight = 0u;
			if (const HRESULT hr = m_spBitmap->GetSize(&uWidth, &uHeight); FAILED(hr))
			{
				throw hr;
			}

			const UINT uMemSize = uWidth * uHeight * (uBitsPerPixel / 8);
			*ppData = new BYTE[uMemSize]{ 0 };
			if (!*ppData)
			{
				AfxThrowMemoryException();
			}

			if (const HRESULT hr = spStream->InitializeFromMemory(reinterpret_cast<WICInProcPointer>(*ppData), uMemSize); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapEncoder> spEncoder;
			if (const HRESULT hr = m_spFactory->CreateEncoder(tFormat, NULL, &spEncoder); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spEncoder->Initialize(spStream, WICBitmapEncoderNoCache); FAILED(hr))
			{
				throw hr;
			}

			CComPtr<IWICBitmapFrameEncode> spFrame;
			CComPtr<IPropertyBag2> spPropertyBag;
			if (const HRESULT hr = spEncoder->CreateNewFrame(&spFrame, &spPropertyBag); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->Initialize(spPropertyBag); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->SetSize(uWidth, uHeight); FAILED(hr))
			{
				throw hr;
			}

			WICPixelFormatGUID pixelFormat2 = tFormat;
			if (const HRESULT hr = spFrame->SetPixelFormat(&pixelFormat2); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->WriteSource(m_spBitmap, NULL); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFrame->Commit(); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spEncoder->Commit(); FAILED(hr))
			{
				throw hr;
			}

			ULARGE_INTEGER streamSize;
			if (const HRESULT hr = spStream->Seek({ 0 }, STREAM_SEEK_CUR, &streamSize); FAILED(hr))
			{
				throw hr;
			}

			uSize = static_cast<DWORD>(streamSize.QuadPart);
		}

		_Check_return_ CSize CBitmapRGBA::GetSize() const
		{
			if (!m_spBitmap)
			{
				return CSize();
			}

			UINT uWidth = 0u;
			UINT uHeight = 0u;
			
			if (const HRESULT hr = m_spBitmap->GetSize(&uWidth, &uHeight); FAILED(hr))
			{
				throw hr;
			}

			return CSize(uWidth, uHeight);
		}

		_Check_return_ const CColorRGBA* CBitmapRGBA::LockForRead() const
		{
			if (!m_spBitmap)
			{
				return NULL;
			}

			if (const HRESULT hr = m_spBitmap->Lock(NULL, WICBitmapLockRead, &m_spLock); FAILED(hr))
			{
				throw hr;
			}

			UINT uBufferSize = 0u;
			BYTE* pBuffer = NULL;
			if (const HRESULT hr = m_spLock->GetDataPointer(&uBufferSize, &pBuffer); FAILED(hr))
			{
				throw hr;
			}

			return reinterpret_cast<const CColorRGBA*>(pBuffer);
		}

		_Check_return_ CColorRGBA* CBitmapRGBA::LockForWrite()
		{
			if (!m_spBitmap)
			{
				return NULL;
			}
;
			if (const HRESULT hr = m_spBitmap->Lock(NULL, WICBitmapLockWrite, &m_spLock); FAILED(hr))
			{
				throw hr;
			}

			UINT uBufferSize = 0u;
			BYTE* pBuffer = NULL;
			if (const HRESULT hr = m_spLock->GetDataPointer(&uBufferSize, &pBuffer); FAILED(hr))
			{
				throw hr;
			}

			return reinterpret_cast<CColorRGBA*>(pBuffer);
		}

		void CBitmapRGBA::Unlock()
		{
			m_spLock.Release();
		}

		void CBitmapRGBA::Flip(_In_ WICBitmapTransformOptions eOption)
		{
			if (!m_spBitmap)
			{
				return;
			}

			CComPtr<IWICBitmapFlipRotator> spFlipRotator;
			if (const HRESULT hr = m_spFactory->CreateBitmapFlipRotator(&spFlipRotator); FAILED(hr))
			{
				throw hr;
			}

			if (const HRESULT hr = spFlipRotator->Initialize(m_spBitmap, eOption); FAILED(hr))
			{
				throw hr;
			}
		}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

		void CBitmapRGBA::AssertValid() const
		{
			CObject::AssertValid();

			ASSERT(m_spFactory);
		}

		void CBitmapRGBA::Dump(_Inout_ CDumpContext& dc) const
		{
			CObject::Dump(dc);

			dc << _T("m_spBitmap = ") << m_spBitmap << _T("\n");
			dc << _T("m_spFactory = ") << m_spFactory << _T("\n");
			dc << _T("m_spLock = ") << m_spLock << _T("\n");
		}

#endif

#pragma endregion

	}
}
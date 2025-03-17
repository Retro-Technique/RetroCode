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
			const HRESULT hr = m_spFactory->CreateBitmap(uWidth, uHeight, GUID_WICPixelFormat32bppPRGBA, WICBitmapCacheOnLoad, &m_spBitmap);
			ENSURE_HRESULT(hr);
		}

		void CBitmapRGBA::Create(_In_ const CSize& szBitmap)
		{
			Create(szBitmap.cx, szBitmap.cy);
		}

		void CBitmapRGBA::LoadFromFile(_In_z_ LPCTSTR pszFileName)
		{
			ENSURE(AfxIsValidString(pszFileName, MAX_PATH));

			CComPtr<IWICStream> spStream;
			HRESULT hr = m_spFactory->CreateStream(&spStream);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapDecoder> spDecoder;
			hr = m_spFactory->CreateDecoderFromFilename(pszFileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &spDecoder);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapFrameDecode> spFrame;
			hr = spDecoder->GetFrame(0, &spFrame);
			ENSURE_HRESULT(hr);

			CComPtr<IWICFormatConverter> spConverter;
			hr = m_spFactory->CreateFormatConverter(&spConverter);
			ENSURE_HRESULT(hr);

			hr = spConverter->Initialize(spFrame, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
			ENSURE_HRESULT(hr);

			hr = m_spFactory->CreateBitmapFromSource(spConverter, WICBitmapCacheOnLoad, &m_spBitmap);
			ENSURE_HRESULT(hr);
		}

		void CBitmapRGBA::LoadFromMemory(_In_reads_bytes_(uSize) LPCVOID pData, _In_ DWORD uSize)
		{
			ENSURE(AfxIsValidAddress(pData, uSize, FALSE));
	
			CComPtr<IWICStream> spStream;
			HRESULT hr = m_spFactory->CreateStream(&spStream);
			ENSURE_HRESULT(hr);

			hr = spStream->InitializeFromMemory(static_cast<BYTE*>(const_cast<LPVOID>(pData)), uSize);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapDecoder> spDecoder;
			hr = m_spFactory->CreateDecoderFromStream(spStream, NULL, WICDecodeMetadataCacheOnDemand, &spDecoder);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapFrameDecode> spFrame;
			hr = spDecoder->GetFrame(0, &spFrame);
			ENSURE_HRESULT(hr);

			CComPtr<IWICFormatConverter> spConverter;
			hr = m_spFactory->CreateFormatConverter(&spConverter);
			ENSURE_HRESULT(hr);

			hr = spConverter->Initialize(spFrame, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
			ENSURE_HRESULT(hr);

			hr = m_spFactory->CreateBitmapFromSource(spConverter, WICBitmapCacheOnLoad, &m_spBitmap);
			ENSURE_HRESULT(hr);
		}

		void CBitmapRGBA::LoadFromResource(_In_ HMODULE hModule, _In_z_ LPCTSTR pszResourceName)
		{
			ENSURE(hModule);
			ENSURE(AfxIsValidString(pszResourceName));

			HRSRC hrSrc = FindResource(hModule, pszResourceName, RT_RCDATA);
			ENSURE_LAST_ERROR(hrSrc);

			HGLOBAL hGlobal = LoadResource(hModule, hrSrc);
			ENSURE_LAST_ERROR(hGlobal);

			const DWORD uSize = SizeofResource(hModule, hrSrc);
			ENSURE_LAST_ERROR(uSize);

			LPVOID pData = LockResource(hGlobal);
			ENSURE_LAST_ERROR(pData);

			LoadFromMemory(pData, uSize);

			UnlockResource(hGlobal);
		}

		void CBitmapRGBA::LoadFromResource(_In_z_ LPCTSTR pszModule, _In_z_ LPCTSTR pszResourceName)
		{
			ENSURE(AfxIsValidString(pszModule, MAX_PATH));
			ENSURE(AfxIsValidString(pszResourceName));

			HMODULE hModule = AfxLoadLibrary(pszModule);
			ENSURE_LAST_ERROR(hModule);

			LoadFromResource(hModule, pszResourceName);

			AfxFreeLibrary(hModule);
		}

		void CBitmapRGBA::SaveToFile(_In_z_ LPCTSTR pszFileName, _In_ const GUID& tFormat)
		{
			ENSURE(AfxIsValidString(pszFileName, MAX_PATH));

			CComPtr<IWICStream> spStream;
			HRESULT hr = m_spFactory->CreateStream(&spStream);
			ENSURE_HRESULT(hr);

			hr = spStream->InitializeFromFilename(pszFileName, GENERIC_WRITE);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapEncoder> spEncoder;
			hr = m_spFactory->CreateEncoder(tFormat, NULL, &spEncoder);
			ENSURE_HRESULT(hr);

			hr = spEncoder->Initialize(spStream, WICBitmapEncoderNoCache);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapFrameEncode> spFrame;
			CComPtr<IPropertyBag2> spPropertyBag;
			hr = spEncoder->CreateNewFrame(&spFrame, &spPropertyBag);
			ENSURE_HRESULT(hr);

			hr = spFrame->Initialize(spPropertyBag);
			ENSURE_HRESULT(hr);

			hr = spFrame->WriteSource(m_spBitmap, NULL);
			ENSURE_HRESULT(hr);

			hr = spFrame->Commit();
			ENSURE_HRESULT(hr);

			hr = spEncoder->Commit();
			ENSURE_HRESULT(hr);
		}

		void CBitmapRGBA::SaveToMemory(_Outptr_ LPVOID* ppData, _Out_ DWORD& uSize, _In_ const GUID& tFormat)
		{
			ENSURE(ppData);

			*ppData = NULL;

			CComPtr<IWICStream> spStream;
			HRESULT hr = m_spFactory->CreateStream(&spStream);
			ENSURE_HRESULT(hr);

			CComPtr<IWICComponentInfo> spComponentInfo;
			hr = m_spFactory->CreateComponentInfo(tFormat, &spComponentInfo);
			ENSURE_HRESULT(hr);

			CComPtr<IWICPixelFormatInfo> spPixelFormatInfo;
			hr = spComponentInfo->QueryInterface(IID_IWICPixelFormatInfo, reinterpret_cast<void**>(&spPixelFormatInfo));
			ENSURE_HRESULT(hr);

			UINT uBitsPerPixel = 0u;
			hr = spPixelFormatInfo->GetBitsPerPixel(&uBitsPerPixel);
			ENSURE_HRESULT(hr);

			UINT uWidth = 0u;
			UINT uHeight = 0u;
			hr = m_spBitmap->GetSize(&uWidth, &uHeight);
			ENSURE_HRESULT(hr);

			const UINT uMemSize = uWidth * uHeight * (uBitsPerPixel / 8);
			*ppData = new BYTE[uMemSize]{ 0 };
			ENSURE_THROW(*ppData, AfxThrowMemoryException());

			hr = spStream->InitializeFromMemory(reinterpret_cast<WICInProcPointer>(*ppData), uMemSize);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapEncoder> spEncoder;
			hr = m_spFactory->CreateEncoder(tFormat, NULL, &spEncoder);
			ENSURE_HRESULT(hr);

			hr = spEncoder->Initialize(spStream, WICBitmapEncoderNoCache);
			ENSURE_HRESULT(hr);

			CComPtr<IWICBitmapFrameEncode> spFrame;
			CComPtr<IPropertyBag2> spPropertyBag;
			hr = spEncoder->CreateNewFrame(&spFrame, &spPropertyBag);
			ENSURE_HRESULT(hr);

			hr = spFrame->Initialize(spPropertyBag);
			ENSURE_HRESULT(hr);

			hr = spFrame->SetSize(uWidth, uHeight);
			ENSURE_HRESULT(hr);

			WICPixelFormatGUID pixelFormat2 = tFormat;
			hr = spFrame->SetPixelFormat(&pixelFormat2);
			ENSURE_HRESULT(hr);

			hr = spFrame->WriteSource(m_spBitmap, NULL);
			ENSURE_HRESULT(hr);

			hr = spFrame->Commit();
			ENSURE_HRESULT(hr);

			hr = spEncoder->Commit();
			ENSURE_HRESULT(hr);

			ULARGE_INTEGER streamSize;
			hr = spStream->Seek({ 0 }, STREAM_SEEK_CUR, &streamSize);
			ENSURE_HRESULT(hr);

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
			
			HRESULT hr = m_spBitmap->GetSize(&uWidth, &uHeight);
			ENSURE_HRESULT(hr);

			return CSize(uWidth, uHeight);
		}

		_Check_return_ const CColorRGBA* CBitmapRGBA::LockForRead() const
		{
			if (!m_spBitmap)
			{
				return NULL;
			}

			HRESULT hr = m_spBitmap->Lock(NULL, WICBitmapLockRead, &m_spLock);
			ENSURE_HRESULT(hr);

			UINT uBufferSize = 0u;
			BYTE* pBuffer = NULL;
			hr = m_spLock->GetDataPointer(&uBufferSize, &pBuffer);
			ENSURE_HRESULT(hr);

			return reinterpret_cast<const CColorRGBA*>(pBuffer);
		}

		_Check_return_ CColorRGBA* CBitmapRGBA::LockForWrite()
		{
			if (!m_spBitmap)
			{
				return NULL;
			}
;
			HRESULT hr = m_spBitmap->Lock(NULL, WICBitmapLockWrite, &m_spLock);
			ENSURE_HRESULT(hr); 

			UINT uBufferSize = 0u;
			BYTE* pBuffer = NULL;
			hr = m_spLock->GetDataPointer(&uBufferSize, &pBuffer);
			ENSURE_HRESULT(hr);

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
			HRESULT hr = m_spFactory->CreateBitmapFlipRotator(&spFlipRotator);
			ENSURE_HRESULT(hr);

			hr = spFlipRotator->Initialize(m_spBitmap, eOption);
			ENSURE_HRESULT(hr);
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
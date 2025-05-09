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

#ifndef __RETRO_IMAGE_H_INCLUDED__
#error Do not include Bitmap.h directly, include the Image.h file
#endif

#pragma once

namespace retro
{
	namespace image
	{

		class AFX_EXT_CLASS CBitmapRGBA : public CObject
		{
#pragma region Constructors

			DECLARE_DYNAMIC(CBitmapRGBA);

		public:

			CBitmapRGBA();
			explicit CBitmapRGBA(_In_ IWICImagingFactory* pExternalFactory);
			~CBitmapRGBA() = default;

#pragma endregion
#pragma region Attributes

		private:

			CComPtr<IWICImagingFactory>		m_spFactory;
			CComPtr<IWICBitmap>				m_spBitmap;
			mutable CComPtr<IWICBitmapLock>	m_spLock;

#pragma endregion
#pragma region Operations

		public:

			void Create(_In_ UINT uWidth, _In_ UINT uHeight);
			void Create(_In_ const CSize& szBitmap);
			void Copy(_In_ const CBitmapRGBA& Bitmap);
			void LoadFromFile(_In_z_ LPCTSTR pszFileName);
			void LoadFromMemory(_In_reads_bytes_(uSize) LPCVOID pData, _In_ DWORD uSize);
			void LoadFromResource(_In_ HMODULE hModule, _In_z_ LPCTSTR pszResourceName);
			void LoadFromResource(_In_z_ LPCTSTR pszModule, _In_z_ LPCTSTR pszResourceName);
			void SaveToFile(_In_z_ LPCTSTR pszFileName, _In_ const GUID& tFormat = GUID_ContainerFormatPng);
			void SaveToMemory(_Outptr_ LPVOID* ppData, _Out_ DWORD& uSize, _In_ const GUID& tFormat = GUID_ContainerFormatPng);
			_Check_return_ CSize GetSize() const;
			_Check_return_ const CColorRGBA* LockForRead() const;
			_Check_return_ CColorRGBA* LockForWrite();
			void Unlock();
			void Unlock() const;
			void Flip(_In_ WICBitmapTransformOptions eOption);

#pragma endregion
#pragma region Overridables

		public:

#ifdef _DEBUG
			void AssertValid() const override;
			void Dump(_Inout_ CDumpContext& dc) const override;
#endif

#pragma endregion
		};

	}
}
/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2024 Retro Technique
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
#include "ImagingFactory.h"

namespace retro
{
	namespace image
	{

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
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

namespace retro
{
	namespace image
	{

#pragma region Constructors

		CColorRGBA::CColorRGBA()
			: Red(0)
			, Green(0)
			, Blue(0)
			, Alpha(255)
		{

		}

		CColorRGBA::CColorRGBA(const CColorRGBA& Other)
			: Red(Other.Red)
			, Green(Other.Green)
			, Blue(Other.Blue)
			, Alpha(Other.Alpha)
		{

		}

		CColorRGBA::CColorRGBA(COLORREF uColor, BYTE uAlpha)
		{
			FromCOLORREF(uColor);
			Alpha = uAlpha;
		}

		CColorRGBA::CColorRGBA(BYTE uRed, BYTE uGreen, BYTE uBlue, BYTE uAlpha)
			: Red(uRed)
			, Green(uGreen)
			, Blue(uBlue)
			, Alpha(uAlpha)
		{

		}

		CColorRGBA::~CColorRGBA()
		{

		}

#pragma endregion
#pragma region Operations

		void CColorRGBA::FromCOLORREF(COLORREF uColor)
		{
			Red = GetRValue(uColor);
			Green = GetGValue(uColor);
			Blue = GetBValue(uColor);
		}

		COLORREF CColorRGBA::ToCOLORREF() const
		{
			return RGB(Red, Green, Blue);
		}

		void CColorRGBA::FromString(LPCTSTR pszValue)
		{
			ASSERT(AfxIsValidString(pszValue));

			const INT nCount = _stscanf_s(pszValue, _T("RGBA(%hhu,%hhu,%hhu,%hhu)"), &Red, &Green, &Blue, &Alpha);
			ASSERT(nCount == 4);
		}

		CString CColorRGBA::ToString() const
		{
			CString strVect;

			strVect.Format(_T("RGBA(%hhu,%hhu,%hhu,%hhu)"), Red, Green, Blue, Alpha);

			return strVect;
		}

		void CColorRGBA::Serialize(CArchive& ar)
		{
			if (ar.IsStoring())
			{
				ar << Red << Green << Blue << Alpha;
			}
			else
			{
				ar >> Red >> Green >> Blue >> Alpha;
			}
		}

#ifdef _DEBUG

		void CColorRGBA::Dump(CDumpContext& dc) const
		{
			dc << ToString();
		}

#endif

#pragma endregion
#pragma region Overridables

		BOOL CColorRGBA::operator==(const CColorRGBA& Other)
		{
			return (Red == Other.Red) && (Green == Other.Green) && (Blue == Other.Blue) && (Alpha == Other.Alpha);
		}

		BOOL CColorRGBA::operator!=(const CColorRGBA& Other)
		{
			return !(*this == Other);
		}

		CColorRGBA CColorRGBA::operator+(const CColorRGBA& Other)
		{
			return CColorRGBA(core::Min<BYTE>(Red + Other.Red, 255),
				core::Min<BYTE>(Green + Other.Green, 255),
				core::Min<BYTE>(Blue + Other.Blue, 255),
				core::Min<BYTE>(Alpha + Other.Alpha, 255));
		}

		CColorRGBA CColorRGBA::operator-(const CColorRGBA& Other)
		{
			return CColorRGBA(core::Max<BYTE>(Red + Other.Red, 0),
				core::Max<BYTE>(Green + Other.Green, 0),
				core::Max<BYTE>(Blue + Other.Blue, 0),
				core::Max<BYTE>(Alpha + Other.Alpha, 0));
		}

		CColorRGBA CColorRGBA::operator*(const CColorRGBA& Other)
		{
			return CColorRGBA((Red + Other.Red) / 255,
				(Green + Other.Green) / 255,
				(Blue + Other.Blue) / 255,
				(Alpha + Other.Alpha) / 255);
		}

		CColorRGBA& CColorRGBA::operator+=(const CColorRGBA& Other)
		{
			return *this = *this + Other;
		}

		CColorRGBA& CColorRGBA::operator-=(const CColorRGBA& Other)
		{
			return *this = *this - Other;
		}

		CColorRGBA& CColorRGBA::operator*=(const CColorRGBA& Other)
		{
			return *this = *this * Other;
		}

#pragma endregion

	}
}
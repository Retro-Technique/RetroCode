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

namespace retro::math
{

#pragma region Constructors

	IMPLEMENT_SERIAL(CPerlinNoise, CObject, 0);

	CPerlinNoise::CPerlinNoise()
		: m_vSize(500, 500)
		, m_fScale(25.0)
		, m_fPersistence(0.5)
		, m_fLacunarity(2.0)
		, m_nOctaveCount(5)
	{
	
	}

#pragma endregion 
#pragma region Operations

	void CPerlinNoise::Generate()
	{
		ASSERT_VALID(this);

		const INT_PTR nSize = m_vSize.X * m_vSize.Y;

		m_arrNoiseMap.SetSize(nSize);

		DOUBLE fMaxNoiseHeight = 0.;
		DOUBLE fMinNoiseHeight = DBL_MAX;

		for (INT_PTR col = 0; col < m_vSize.Y; col++)
		{
			for (INT_PTR row = 0; row < m_vSize.X; row++)
			{
				DOUBLE fAmplitude = 1.;
				DOUBLE fFrequency = 1.;
				DOUBLE fNoiseHeight = 0.;

				for (INT_PTR i = 0; i < m_nOctaveCount; i++)
				{
					const DOUBLE fSampleX = row / m_fScale * fFrequency;
					const DOUBLE fSampleY = col / m_fScale * fFrequency;

					const DOUBLE fPerlinValue = MakeNoise(fSampleX, fSampleY) * 2. - 1.;

					fNoiseHeight += fPerlinValue * fAmplitude;
					fAmplitude = fAmplitude * m_fPersistence;
					fFrequency = fFrequency * m_fLacunarity;
				}

				fMaxNoiseHeight = Max(fMaxNoiseHeight, fNoiseHeight);
				fMinNoiseHeight = Min(fMinNoiseHeight, fNoiseHeight);

				const INT_PTR nIndex = col * m_vSize.Y + row;
				m_arrNoiseMap.SetAt(nIndex, fNoiseHeight);
			}
		}

		for (INT_PTR i = 0; i < nSize; i++)
		{
			const DOUBLE fNoiseIn = m_arrNoiseMap.GetAt(i);
			const DOUBLE fNoiseOut = InverseLerp(fMinNoiseHeight, fMaxNoiseHeight, fNoiseIn);
			m_arrNoiseMap.SetAt(i, fNoiseOut);
		}
	}

	void CPerlinNoise::Enumerate(MAPENUMPROC pfnEnum, LPVOID pData)
	{
		ASSERT_VALID(this);
		ENSURE(pfnEnum);
		
		for (INT_PTR i = 0; i < m_arrNoiseMap.GetSize(); i++)
		{
			if (!pfnEnum(m_arrNoiseMap.GetAt(i), pData))
			{
				break;
			}
		}
	}

#pragma endregion
#pragma region Overridables

	void CPerlinNoise::Serialize(_Inout_ CArchive& ar)
	{
		CObject::Serialize(ar);

		m_vSize.Serialize(ar);

		if (ar.IsStoring())
		{
			ar << m_fScale;
			ar << m_fPersistence;
			ar << m_fLacunarity;
			ar << m_nOctaveCount;
		}
		else
		{
			ar >> m_fScale;
			ar >> m_fPersistence;
			ar >> m_fLacunarity;
			ar >> m_nOctaveCount;
		}
	}

#ifdef _DEBUG

	void CPerlinNoise::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT(m_vSize.X >= WIDTH_MIN);
		ASSERT(m_vSize.Y >= HEIGHT_MIN);
		ASSERT(m_fScale >= SCALE_MIN);
		ASSERT(m_fPersistence >= PERSISTENCE_MIN);
		ASSERT(m_fLacunarity >= LACUNARITY_MIN);
		ASSERT(m_nOctaveCount >= OCTAVE_COUNT_MIN);
		if (!m_arrNoiseMap.IsEmpty())
		{
			ASSERT(m_arrNoiseMap.GetSize() == m_vSize.X * m_vSize.Y);
		}
	}

	void CPerlinNoise::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		m_vSize.Dump(dc);
		dc << _T("m_fScale = ") << m_fScale << _T("\n");
		dc << _T("m_fPersistence = ") << m_fPersistence << _T("\n");
		dc << _T("m_fLacunarity = ") << m_fLacunarity << _T("\n");
		dc << _T("m_nOctaveCount = ") << m_nOctaveCount << _T("\n");
		dc << _T("m_arrNoiseMap = ") << m_arrNoiseMap << _T("\n");
	}

#endif

#pragma endregion 
#pragma region Implementations

	INT CPerlinNoise::GetNoiseFromHash(INT x, INT y) const
	{
		const INT nTmp = HASH[y % HASH_COUNT];

		return HASH[(nTmp + x) % HASH_COUNT];
	}

	DOUBLE CPerlinNoise::SmoothInterpolation(DOUBLE x, DOUBLE y, DOUBLE s) const
	{
		return Lerp(x, y, s * s * (3. - 2. * s));
	}

	DOUBLE CPerlinNoise::MakeNoise(DOUBLE x, DOUBLE y) const
	{
		const INT x_int = static_cast<INT>(x);
		const INT y_int = static_cast<INT>(y);
		const DOUBLE x_frac = x - x_int;
		const DOUBLE y_frac = y - y_int;
		const INT s = GetNoiseFromHash(x_int, y_int);
		const INT t = GetNoiseFromHash(x_int + 1, y_int);
		const INT u = GetNoiseFromHash(x_int, y_int + 1);
		const INT v = GetNoiseFromHash(x_int + 1, y_int + 1);
		const DOUBLE low = SmoothInterpolation(s, t, x_frac);
		const DOUBLE high = SmoothInterpolation(u, v, x_frac);

		return SmoothInterpolation(low, high, y_frac);
	}

#pragma endregion

}
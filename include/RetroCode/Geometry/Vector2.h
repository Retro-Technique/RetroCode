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

#ifndef __RETRO_GEOMETRY_H_INCLUDED__
#error Do not include Vector2.h directly, include the Geometry.h file
#endif

#pragma once

namespace retro
{
	namespace geometry
	{

		template<typename T>
		class CVector2
		{
#pragma region Constructors

		public:

			CVector2();
			CVector2(T x, T y);
			CVector2(const CPoint& ptPoint);
			CVector2(const CSize& szSize);
			template<typename U>
			explicit CVector2(const CVector2<U>& Vector);
			~CVector2();

#pragma endregion
#pragma region Attributes

		public:

			T X;
			T Y;

#pragma endregion
#pragma region Operations

		public:

			void FromPoint(const CPoint& ptPoint);
			void FromSize(const CSize& szSize);
			CPoint ToPoint() const;
			CSize ToSize() const;
			void FromString(LPCTSTR pszValue);
			CString ToString() const;
			void Serialize(CArchive& ar);
#ifdef _DEBUG
			void Dump(CDumpContext& dc) const;
#endif

#pragma endregion

		};

		typedef CVector2<INT>	CVector2i;
		typedef CVector2<FLOAT>	CVector2f;
		typedef CVector2<UINT>	CVector2u;

		template<typename T>
		CVector2<T> operator+(const CVector2<T>& Left, const CVector2<T>& Right);

		template<typename T>
		CVector2<T>& operator+=(const CVector2<T>& Left, const CVector2<T>& Right);

		template<typename T>
		CVector2<T>& operator-=(const CVector2<T>& Left, const CVector2<T>& Right);

		template<typename T>
		CVector2<T> operator-(const CVector2<T>& Right);

		template<typename T>
		CVector2<T> operator-(const CVector2<T>& Left, const CVector2<T>& Right);

		template<typename T>
		CVector2<T> operator*(const CVector2<T>& Left, T Right);

		template<typename T>
		CVector2<T> operator*(T Left, const CVector2<T>& Right);

		template<typename T>
		CVector2<T>& operator*=(const CVector2<T>& Left, T Right);

		template<typename T>
		CVector2<T> operator/(const CVector2<T>& Left, T Right);

		template<typename T>
		CVector2<T>& operator/=(const CVector2<T>& Left, T Right);

		template<typename T>
		BOOL operator==(const CVector2<T>& Left, const CVector2<T>& Right);

		template<typename T>
		BOOL operator!=(const CVector2<T>& Left, const CVector2<T>& Right);

	}
}

#include "Vector2.inl"
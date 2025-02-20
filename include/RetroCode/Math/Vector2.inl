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

namespace retro::math
{

#pragma region Constructors

	template<typename T>
	CVector2<T>::CVector2()
		: X(0)
		, Y(0)
	{

	}

	template<typename T>
	CVector2<T>::CVector2(T x, T y)
		: X(x)
		, Y(y)
	{

	}

	template<typename T>
	CVector2<T>::CVector2(const CPoint& ptPoint)
		: X(static_cast<T>(ptPoint.x))
		, Y(static_cast<T>(ptPoint.y))
	{

	}

	template<typename T>
	CVector2<T>::CVector2(const CSize& szSize)
		: X(static_cast<T>(szSize.cx))
		, Y(static_cast<T>(szSize.cy))
	{

	}

	template<typename T>
	template<typename U>
	CVector2<T>::CVector2(const CVector2<U>& Vector)
		: X(static_cast<T>(Vector.X))
		, Y(static_cast<T>(Vector.Y))
	{


	}

#pragma endregion
#pragma region Operations

	template<typename T>
	void CVector2<T>::FromPoint(const CPoint& ptPoint)
	{
		X = static_cast<T>(ptPoint.x);
		Y = static_cast<T>(ptPoint.y);
	}

	template<typename T>
	void CVector2<T>::FromSize(const CSize& szSize)
	{
		X = static_cast<T>(szSize.cx);
		Y = static_cast<T>(szSize.cy);
	}

	template<typename T>
	CPoint CVector2<T>::ToPoint() const
	{
		return CPoint(static_cast<INT>(X), static_cast<INT>(Y));
	}

	template<typename T>
	CSize CVector2<T>::ToSize() const
	{
		return CSize(static_cast<INT>(X), static_cast<INT>(Y));
	}

	template<typename T>
	void CVector2<T>::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << X << Y;
		}
		else
		{
			ar >> X >> Y;
		}
	}

#ifdef _DEBUG

	template<typename T>
	void CVector2<T>::Dump(CDumpContext& dc) const
	{
		dc << _T("X = ") << X << _T("\n");
		dc << _T("Y = ") << Y << _T("\n");
	}

#endif

#pragma endregion
#pragma region Overridables

	template<typename T>
	CVector2<T> operator+(const CVector2<T>& Left, const CVector2<T>& Right)
	{
		return CVector2<T>(Left.X + Right.X, Left.Y + Right.Y);
	}

	template<typename T>
	CVector2<T>& operator+=(const CVector2<T>& Left, const CVector2<T>& Right)
	{
		Left.X += Right.X;
		Left.Y += Right.Y;

		return Left;
	}

	template<typename T>
	CVector2<T>& operator-=(const CVector2<T>& Left, const CVector2<T>& Right)
	{
		Left.X -= Right.X;
		Left.Y -= Right.Y;

		return Left;
	}

	template<typename T>
	CVector2<T> operator-(const CVector2<T>& Right)
	{
		return CVector2<T>(-Right.x, -Right.y);
	}

	template<typename T>
	CVector2<T> operator-(const CVector2<T>& Left, const CVector2<T>& Right)
	{
		return CVector2<T>(Left.X - Right.X, Left.Y - Right.Y);
	}

	template<typename T>
	CVector2<T> operator*(const CVector2<T>& Left, T Right)
	{
		return CVector2<T>(Left.X * Right, Left.Y * Right);
	}

	template<typename T>
	CVector2<T> operator*(T Left, const CVector2<T>& Right)
	{
		return CVector2<T>(Right.X * Left, Right.Y * Left);
	}

	template<typename T>
	CVector2<T>& operator*=(const CVector2<T>& Left, T Right)
	{
		Left.X *= Right;
		Left.Y *= Right;

		return Left;
	}

	template<typename T>
	CVector2<T> operator/(const CVector2<T>& Left, T Right)
	{
		return CVector2<T>(Left.X / Right, Left.Y / Right);
	}

	template<typename T>
	CVector2<T>& operator/=(const CVector2<T>& Left, T Right)
	{
		Left.X /= Right;
		Left.Y /= Right;

		return Left;
	}

	template<typename T>
	BOOL operator==(const CVector2<T>& Left, const CVector2<T>& Right)
	{
		return (Left.X == Right.X) && (Left.Y == Right.Y);
	}

	template<typename T>
	BOOL operator!=(const CVector2<T>& Left, const CVector2<T>& Right)
	{
		return (Left.X != Right.X) || (Left.Y != Right.Y);
	}

#pragma endregion

}
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
	CRect<T>::CRect()
		: Point{ 0, 0 }
		, Size{ 0, 0 }
	{

	}

	template<typename T>
	CRect<T>::CRect(T x, T y, T width, T height)
		: Point{ x, y }
		, Size{ width, height }
	{

	}

	template<typename T>
	CRect<T>::CRect(const CVector2<T>& Point, const CVector2<T>& Size)
		: Point(Point)
		, Size(Size)
	{

	}

	template<typename T>
	CRect<T>::CRect(const ::CRect& rcRect)
		: Point{ rcRect.left, rcRect.top }
		, Size{ rcRect.Width(), rcRect.Height() }
	{

	}

	template<typename T>
	template<typename U>
	CRect<T>::CRect(const CRect<U>& Rectangle)
		: Point{ static_cast<T>(Rectangle.Point.X), static_cast<T>(Rectangle.Point.Y) }
		, Size{ static_cast<T>(Rectangle.Size.X), static_cast<T>(Rectangle.Size.Y) }
	{

	}

#pragma endregion
#pragma region Operations

	template<typename T>
	void CRect<T>::FromRect(const ::CRect& rcRect)
	{
		Point.X = static_cast<T>(rcRect.left);
		Point.Y = static_cast<T>(rcRect.top);
		Size.X = static_cast<T>(rcRect.Width());
		Size.Y = static_cast<T>(rcRect.Height());
	}

	template<typename T>
	::CRect CRect<T>::ToRect() const
	{
		return ::CRect(static_cast<INT>(Point.X), static_cast<INT>(Point.Y),
			static_cast<INT>(Right()), static_cast<INT>(Bottom()));
	}

	template<typename T>
	const T& CRect<T>::Left() const
	{
		return Point.X;
	}

	template<typename T>
	const T& CRect<T>::Top() const
	{
		return Point.Y;
	}

	template<typename T>
	T CRect<T>::Right() const
	{
		return Point.X + Size.X;
	}

	template<typename T>
	T CRect<T>::Bottom() const
	{
		return Point.Y + Size.Y;
	}

	template<typename T>
	void CRect<T>::Serialize(CArchive& ar)
	{
		Point.Serialize(ar);
		Size.Serialize(ar);
	}

#ifdef _DEBUG

	template<typename T>
	void CRect<T>::Dump(CDumpContext& dc) const
	{
		dc << _T("Point.X = ") << Point.X << _T("\n");
		dc << _T("Point.Y = ") << Point.Y << _T("\n");
		dc << _T("Size.X = ") << Size.X << _T("\n");
		dc << _T("Size.Y = ") << Size.Y << _T("\n");
	}

#endif

#pragma endregion
#pragma region Overridables

	template<typename T>
	BOOL operator==(const CRect<T>& Left, const CRect<T>& Right)
	{
		return (Left.Point.X == Right.Point.X) && (Left.Point.Y == Right.Point.Y) && (Left.Size.X == Right.Size.X) && (Left.Size.Y == Right.Size.Y);
	}

	template<typename T>
	BOOL operator!=(const CRect<T>& Left, const CRect<T>& Right)
	{
		return !(Left == Right);
	}

#pragma endregion

}
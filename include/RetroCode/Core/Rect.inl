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

namespace retro
{
	namespace core
	{

		template<typename T>
		TRect<T>::TRect()
			: Point{ 0, 0 }
			, Size{ 0, 0 }
		{

		}

		template<typename T>
		TRect<T>::TRect(T x, T y, T width, T height)
			: Point{ x, y }
			, Size{ width, height }
		{

		}

		template<typename T>
		TRect<T>::TRect(const TVector2<T>& Point, const TVector2<T>& Size)
			: Point(Point)
			, Size(Size)
		{

		}

		template<typename T>
		TRect<T>::TRect(const CRect& rcRect)
			: Point{ rcRect.left, rcRect.top }
			, Size{ rcRect.Width(), rcRect.Height() }
		{

		}
		
		template<typename T>
		template<typename U>
		TRect<T>::TRect(const TRect<U>& Rectangle)
			: Point{ static_cast<T>(Rectangle.Point.X), static_cast<T>(Rectangle.Point.Y) }
			, Size{ static_cast<T>(Rectangle.Size.X), static_cast<T>(Rectangle.Size.Y) }
		{

		}

		template<typename T>
		TRect<T>::~TRect()
		{

		}

		template<typename T>
		void TRect<T>::FromRect(const CRect& rcRect)
		{
			Point.X = static_cast<T>(rcRect.left);
			Point.Y = static_cast<T>(rcRect.top);
			Size.X = static_cast<T>(rcRect.Width());
			Size.Y = static_cast<T>(rcRect.Height());
		}

		template<typename T>
		CRect TRect<T>::ToRect() const
		{
			return CRect(static_cast<INT>(Point.X), static_cast<INT>(Point.Y),
				static_cast<INT>(Right()), static_cast<INT>(Bottom()));
		}

		template<typename T>
		const T& TRect<T>::Left() const
		{
			return Point.X;
		}

		template<typename T>
		const T& TRect<T>::Top() const
		{
			return Point.Y;
		}

		template<typename T>
		T TRect<T>::Right() const
		{
			return Point.X + Size.X;
		}

		template<typename T>
		T TRect<T>::Bottom() const
		{
			return Point.Y + Size.Y;
		}

		template<typename T>
		void TRect<T>::Serialize(CArchive& ar)
		{
			Point.Serialize(ar);
			Size.Serialize(ar);
		}

#ifdef _DEBUG

		template<typename T>
		void TRect<T>::Dump(CDumpContext& dc) const
		{
			Point.Dump(dc);
			Size.Dump(dc);
		}

#endif

		template<typename T>
		BOOL operator==(const TRect<T>& Left, const TRect<T>& Right)
		{
			return (Left.Point.X == Right.Point.X) && (Left.Point.Y == Right.Point.Y) && (Left.Size.X == Right.Size.X) && (Left.Size.Y == Right.Size.Y);
		}

		template<typename T>
		BOOL operator!=(const TRect<T>& Left, const TRect<T>& Right)
		{
			return !(Left == Right);
		}

	}
}
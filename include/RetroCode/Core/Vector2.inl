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
		TVector2<T>::TVector2()
			: X(0)
			, Y(0)
		{

		}

		template<typename T>
		TVector2<T>::TVector2(T x, T y)
			: X(x)
			, Y(y)
		{

		}

		template<typename T>
		TVector2<T>::TVector2(const CPoint& ptPoint)
			: X(static_cast<T>(ptPoint.x))
			, Y(static_cast<T>(ptPoint.y))
		{

		}

		template<typename T>
		TVector2<T>::TVector2(const CSize& szSize)
			: X(static_cast<T>(szSize.cx))
			, Y(static_cast<T>(szSize.cy))
		{

		}

		template<typename T>
		template<typename U>
		TVector2<T>::TVector2(const TVector2<U>& Vector)
			: X(static_cast<T>(Vector.X))
			, Y(static_cast<T>(Vector.Y))
		{


		}

		template<typename T>
		TVector2<T>::~TVector2()
		{

		}

		template<typename T>
		void TVector2<T>::FromPoint(const CPoint& ptPoint)
		{
			X = static_cast<T>(ptPoint.x);
			Y = static_cast<T>(ptPoint.y);
		}

		template<typename T>
		void TVector2<T>::FromSize(const CSize& szSize)
		{
			X = static_cast<T>(szSize.cx);
			Y = static_cast<T>(szSize.cy);
		}

		template<typename T>
		CPoint TVector2<T>::ToPoint() const
		{
			return CPoint(static_cast<INT>(X), static_cast<INT>(Y));
		}

		template<typename T>
		CSize TVector2<T>::ToSize() const
		{
			return CSize(static_cast<INT>(X), static_cast<INT>(Y));
		}

		template<typename T>
		void TVector2<T>::Serialize(CArchive& ar)
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
		void TVector2<T>::Dump(CDumpContext& dc) const
		{
			dc << _T("(") << X << _T(";") << Y << _T(")");
		}

#endif

		template<typename T>
		TVector2<T> operator+(const TVector2<T>& Left, const TVector2<T>& Right)
		{
			return TVector2<T>(Left.X + Right.X, Left.Y + Right.Y);
		}

		template<typename T>
		TVector2<T>& operator+=(const TVector2<T>& Left, const TVector2<T>& Right)
		{
			Left.X += Right.X;
			Left.Y += Right.Y;

			return Left;
		}

		template<typename T>
		TVector2<T>& operator-=(const TVector2<T>& Left, const TVector2<T>& Right)
		{
			Left.X -= Right.X;
			Left.Y -= Right.Y;

			return Left;
		}

		template<typename T>
		TVector2<T> operator-(const TVector2<T>& Right)
		{
			return TVector2<T>(-Right.x, -Right.y);
		}

		template<typename T>
		TVector2<T> operator-(const TVector2<T>& Left, const TVector2<T>& Right)
		{
			return TVector2<T>(Left.X - Right.X, Left.Y - Right.Y);
		}

		template<typename T>
		TVector2<T> operator*(const TVector2<T>& Left, T Right)
		{
			return TVector2<T>(Left.X * Right, Left.Y * Right);
		}

		template<typename T>
		TVector2<T> operator*(T Left, const TVector2<T>& Right)
		{
			return TVector2<T>(Right.X * Left, Right.Y * Left);
		}

		template<typename T>
		TVector2<T>& operator*=(const TVector2<T>& Left, T Right)
		{
			Left.X *= Right;
			Left.Y *= Right;

			return Left;
		}

		template<typename T>
		TVector2<T> operator/(const TVector2<T>& Left, T Right)
		{
			return TVector2<T>(Left.X / Right, Left.Y / Right);
		}

		template<typename T>
		TVector2<T>& operator/=(const TVector2<T>& Left, T Right)
		{
			Left.X /= Right;
			Left.Y /= Right;

			return Left;
		}

		template<typename T>
		BOOL operator==(const TVector2<T>& Left, const TVector2<T>& Right)
		{
			return (Left.X == Right.X) && (Left.Y == Right.Y);
		}

		template<typename T>
		BOOL operator!=(const TVector2<T>& Left, const TVector2<T>& Right)
		{
			return (Left.X != Right.X) || (Left.Y != Right.Y);
		}

	}
}
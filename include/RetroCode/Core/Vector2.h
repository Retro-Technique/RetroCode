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

#pragma once

namespace retro
{
	namespace core
	{

		/**
		 * @brief Template structure for a 2D vector
		 *
		 */
		template<typename T>
		struct TVector2
		{

			/**
			 * @brief Default constructor
			 *
			 */
			TVector2();

			/**
			 * @brief Construct a new TVector2 object with given components
			 * 
			 * @param x The x component
			 * @param y The y component
			 *
			 */
			TVector2(T x, T y);

			/**
			 * @brief Construct a new TVector2 object from a MFC CPoint
			 *
			 * @param ptPoint The CPoint component
			 *
			 */
			TVector2(const CPoint& ptPoint);

			/**
			 * @brief Construct a new TVector2 object from a MFC CSize
			 *
			 * @param szSize The CSize component
			 *
			 */
			TVector2(const CSize& szSize);

			/**
			 * @brief Construct a new TVector2 object from another vector of a different type
			 *
			 * @param Vector The other vector
			 * 
			 */
			template<typename U>
			explicit TVector2(const TVector2<U>& Vector);

			/**
			 * @brief Destructor
			 *
			 */
			~TVector2();

			/**
			 * @brief Set the TVector2 object from a MFC CPoint
			 *
			 * @param ptPoint The CPoint component
			 *
			 */
			void FromPoint(const CPoint& ptPoint);

			/**
			 * @brief Set the TVector2 object from a MFC CPoint
			 *
			 * @param szSize The CSize component
			 *
			 */
			void FromSize(const CSize& szSize);

			/**
			 * @brief Convert TVector2 object to a MFC CPoint
			 *
			 * @return The CPoint component
			 *
			 */
			CPoint ToPoint() const;

			/**
			 * @brief Convert TVector2 object to a MFC CSize
			 *
			 * @return The CSize component
			 *
			 */
			CSize ToSize() const;

			/**
			 * @brief Reads or writes this object from or to an archive
			 *
			 * @param ar A CArchive object to serialize to or from
			 *
			 */
			void Serialize(CArchive& ar);

#ifdef _DEBUG
			/**
			 * @brief Produces a diagnostic dump of the object
			 *
			 * @param dc The diagnostic dump context for dumping
			 *
			 */
			void Dump(CDumpContext& dc) const;
#endif

			T X; /**< X coordinate of the vector */
			T Y; /**< Y coordinate of the vector */

		};

		typedef TVector2<INT>	TVector2i;
		typedef TVector2<FLOAT>	TVector2f;
		typedef TVector2<UINT>	TVector2u;

		/**
		 * @relates TVector2
		 * @brief Add another vector to this vector and return a new vector as the result
		 *
		 * @param Left Left vector
		 * @param Right Right vector
		 *
		 * @return The result of the addition
		 *
		 */
		template<typename T>
		TVector2<T> operator+(const TVector2<T>& Left, const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Add another vector to this vector and return a reference to this vector
		 *
		 * @param Left Left vector
		 * @param Right Right vector
		 *
		 * @return A reference to this vector
		 *
		 */
		template<typename T>
		TVector2<T>& operator+=(const TVector2<T>& Left, const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Subtract another vector from this vector and return a reference to this vector
		 *
		  * @param Left Left vector
		 * @param Right Right vector
		 *
		 * @return A reference to this vector
		 *
		 */
		template<typename T>
		TVector2<T>& operator-=(const TVector2<T>& Left, const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Subtract another vector from this vector and return a new vector as the result
		 *
		 * @param Right Right vector
		 *
		 * @return The result of the subtraction
		 *
		 */
		template<typename T>
		TVector2<T> operator-(const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Subtract another vector from this vector and return a new vector as the result
		 *
		 * @param Left Left vector
		 * @param Right Right vector
		 *
		 * @return The result of the subtraction
		 *
		 */
		template<typename T>
		TVector2<T> operator-(const TVector2<T>& Left, const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Multiply this vector by a scalar and return a new vector as the result
		 *
		 * @param Left Left vector
		 * @param Right Right scalar
		 *
		 * @return The result of the multiplication
		 *
		 */
		template<typename T>
		TVector2<T> operator*(const TVector2<T>& Left, T Right);

		/**
		 * @relates TVector2
		 * @brief Multiply this vector by a scalar and return a new vector as the result
		 *
		  * @param Left Left scalar
		 * @param Right Right vector
		 *
		 * @return The result of the multiplication
		 *
		 */
		template<typename T>
		TVector2<T> operator*(T Left, const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Multiply this vector by a scalar and return a reference to this vector
		 *
		 * @param Left Left vector
		 * @param Right Right scalar
		 *
		 * @return A reference to this vector
		 *
		 */
		template<typename T>
		TVector2<T>& operator*=(const TVector2<T>& Left, T Right);

		/**
		 * @relates TVector2
		 * @brief Divide this vector by a scalar and return a new vector as the result
		 *
		 * @param Left Left vector
		 * @param Right Right scalar
		 *
		 * @return The result of the division
		 *
		 */
		template<typename T>
		TVector2<T> operator/(const TVector2<T>& Left, T Right);

		/**
		 * @relates TVector2
		 * @brief Divide this vector by a scalar and return a reference to this vector
		 *
		 * @param Left Left vector
		 * @param Right Right scalar
		 *
		 * @return A reference to this vector
		 *
		 */
		template<typename T>
		TVector2<T>& operator/=(const TVector2<T>& Left, T Right);

		/**
		 * @relates TVector2
		 * @brief Compare this vector with another vector for equality and return true if they are equal, false otherwise
		 *
		 * @param Left Left vector
		 * @param Right Right vector
		 *
		 * @return True if the vectors are equal, false otherwise
		 *
		 */
		template<typename T>
		BOOL operator==(const TVector2<T>& Left, const TVector2<T>& Right);

		/**
		 * @relates TVector2
		 * @brief Compare this vector with another vector for inequality and return true if they are not equal, false otherwise
		 *
		 * @param Left Left vector
		 * @param Right Right vector
		 *
		 * @return True if the vectors are not equal, false otherwise
		 *
		 */
		template<typename T>
		BOOL operator!=(const TVector2<T>& Left, const TVector2<T>& Right);

	}
}

#include "Vector2.inl"
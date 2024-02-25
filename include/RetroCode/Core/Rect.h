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
		 * @brief Template structure for a rectangle
		 *
		 */
		template<typename T>
		struct TRect
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				TRect();

				/**
				 * @brief Construct a new rectangle object with given components
				 *
				 * @param x The x component
				 * @param y The y component
				 * @param width The width component
				 * @param height The height component
				 *
				 */
				TRect(T x, T y, T width, T height);

				/**
				 * @brief Construct a new rectangle object with given components
				 *
				 * @param Point The TVector2 component representing the position
				 * @param Size The TVector2 component representing the size
				 *
				 */
				TRect(const TVector2<T>& Point, const TVector2<T>& Size);

				/**
				 * @brief Construct a new TRect object from a MFC CRect
				 *
				 * @param rcRect The CPoint component
				 *
				 */
				TRect(const CRect& rcRect);

				/**
				 * @brief Construct a new TRect object from another rectangle of a different type
				 *
				 * @param Rectangle The other rectangle
				 *
				 */
				template<typename U>
				explicit TRect(const TRect<U>& Rectangle);

				/**
				 * @brief Destructor
				 *
				 */
				~TRect();

				/**
				 * @brief Set the TRect object from a MFC CRect
				 *
				 * @param rcRect The CRect component
				 *
				 */
				void FromRect(const CRect& rcRect);

				/**
				 * @brief Convert TRect object to a MFC CRect
				 *
				 * @return The CRect component
				 *
				 */
				CRect ToRect() const;

				/**
				 * @brief Get the position of the rectangle's left corner
				 *
				 * @return The left corner
				 *
				 */
				const T& Left() const;

				/**
				 * @brief Get the position of the rectangle's top corner
				 *
				 * @return The top corner
				 *
				 */
				const T& Top() const;

				/**
				 * @brief Get the position of the rectangle's right corner
				 *
				 * @return The right corner
				 *
				 */
				T Right() const;
				
				/**
				 * @brief Get the position of the rectangle's bottom corner
				 *
				 * @return The bottom corner
				 *
				 */
				T Bottom() const;

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

				TVector2<T> Point; /**< Position of the rectangle */
				TVector2<T> Size;  /**< Size of the rectangle */

		};

		typedef TRect<INT>		TIntRect;
		typedef TRect<FLOAT>	TFloatRect;

		/**
		 * @relates TRect
		 * @brief Compare this rectangle with another rectangle for equality and return true if they are equal, false otherwise
		 *
		 * @param Left Left rectangle
		 * @param Right Right rectangle
		 *
		 * @return True if the rectangles are equal, false otherwise
		 *
		 */
		template<typename T>
		BOOL operator==(const TRect<T>& Left, const TRect<T>& Right);

		/**
		 * @relates TRect
		 * @brief Compare this rectangle with another rectangle for inequality and return true if they are not equal, false otherwise
		 *
		 * @param Left Left rectangle
		 * @param Right Right rectangle
		 *
		 * @return True if the rectangles are not equal, false otherwise
		 *
		 */
		template<typename T>
		BOOL operator!=(const TRect<T>& Left, const TRect<T>& Right);

	}
}

#include "Rect.inl"
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
		 * @brief Class template for manipulating fixed size arrays
		 *
		 */
		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE = const TYPE&>
		class CStaticArray
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				CStaticArray();

				/**
				 * @brief Destructor
				 *
				 */
				~CStaticArray();

				/**
				 * @brief Returns the number of elements
				 *
				 * @return The number of elements in the underlying container
				 *
				 */
				INT_PTR GetSize() const;

				/**
				 * @brief Returns the current upper bound of this array
				 *
				 * @return The current upper bound
				 *
				 */
				INT_PTR GetUpperBound() const;

				/**
				 * @brief Returns the array element at the specified index
				 *
				 * @param Idx An integer index that is greater than or equal to 0
				 *
				 * @return The array element currently at this index
				 *
				 */
				const TYPE& GetAt(INT_PTR nIndex) const;

				/**
				 * @brief Returns the array element at the specified index
				 *
				 * @param Idx An integer index that is greater than or equal to 0
				 *
				 * @return The array element currently at this index
				 *
				 */
				TYPE& GetAt(INT_PTR nIndex);

				/**
				 * @brief Direct access to the underlying array
				 *
				 * @return The pointer to the underlying array serving as element storage
				 *
				 */
				const TYPE* GetData() const;

				/**
				 * @brief Direct access to the underlying array
				 *
				 * @return The pointer to the underlying array serving as element storage
				 *
				 */
				TYPE* GetData();

				/**
				 * @brief Sets the array element at the specified index
				 *
				 * @param nIndex An integer index that is greater than or equal to 0
				 * @param newElement The new element value to be stored at the specified position
				 *
				 */
				void SetAt(INT_PTR nIndex, ARG_TYPE newElement);

			private:

				/**
				 * Member data
				 */
				TYPE m_Buffer[SIZE];

		};

	}

}

#include "StaticArray.inl"
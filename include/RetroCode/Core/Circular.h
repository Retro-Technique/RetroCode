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
		 * @brief Class template for manipulating a fixed sized container
		 * 
		 * It works as if the memory was contiguous and circular.
		 * It allows to handle data streams or to implement FIFO behavior.
		 * It pushes the elements to the back of the container and removes them
		 * from the front, by rotating the gead and tail pointers.
		 *
		 */
		template<typename TYPE, typename ARG_TYPE = const TYPE&>
		class CCircular
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				CCircular();

				/**
				 * @brief Destructor
				 *
				 */
				~CCircular();

				/**
				 * @brief Set the size of the container
				 *
				 * @param nSize The size of the container
				 *
				 */
				void SetSize(INT_PTR nSize);

				/**
				 * @brief Inserts an element in front
				 *
				 * @param newElement The value of the element to push
				 *
				 */
				void Push(ARG_TYPE newElement);

				/**
				 * @brief Returns the size of the container
				 *
				 * @return The size of the container
				 *
				 */
				INT_PTR GetSize() const;

				/**
				 * @brief Returns the number of elements
				 *
				 * @return The number of elements in the underlying container
				 *
				 */
				INT_PTR GetCount() const;

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
				 * @brief Returns the array element at the specified index
				 *
				 * @param Idx An integer index that is greater than or equal to 0
				 *
				 * @return The array element currently at this index
				 *
				 */
				const TYPE& GetAt(INT_PTR nIndex) const;

				/**
				 * @brief Clear the contents
				 *
				 * Erases all elements from the container.
				 * After this call, GetSize() returns zero.
				 *
				 * @see GetSize
				 *
				 */
				void RemoveAll();

				/**
				 * @brief Checks whether the underlying container is empty
				 *
				 * Checks if the underlying container has no elements.
				 *
				 * @return True if the underlying container is empty, false otherwise
				 *
				 */
				BOOL IsEmpty() const;

			private:

				/**
				 * Member data
				 */
				CArray<TYPE, ARG_TYPE> m_Buffer;
				INT_PTR m_nFirstIdx;
				INT_PTR m_nLastIdx;

		};

	}
}

#include "Circular.inl"
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
		 * @brief Class template for manipulating a FIFO data container
		 *
		 */
		template<typename TYPE, typename ARG_TYPE = const TYPE&>
		class CQueue
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				CQueue();

				/**
				 * @brief Destructor
				 *
				 */
				~CQueue();

				/**
				 * @brief Inserts element at the end
				 *
				 * Pushes the given element value to the end of the queue.
				 * 
				 * @param newElement The value of the element to push
				 * 
				 * @return The index of the added element
				 * 
				 */
				INT_PTR Push(ARG_TYPE newElement);

				/**
				 * @brief Removes the first element
				 *
				 * Removes and element from the front of the queue.
				 *
				 */
				void Pop();

				/**
				 * @brief Access the first element
				 *
				 * Returns reference to the first element in the queue.
				 * This element will be the first element to be removed on
				 * a call to Pop().
				 * 
				 * @return The reference to the first element
				 * 
				 * @see Pop
				 *
				 */
				TYPE& Front();

				/**
				 * @brief Access the first element
				 *
				 * Returns reference to the first element in the queue.
				 * This element will be the first element to be removed on
				 * a call to Pop().
				 *
				 * @return The reference to the first element
				 *
				 * @see Pop
				 *
				 */
				const TYPE& Front() const;

				/**
				 * @brief Access the last element
				 *
				 * Returns reference to the last element in the queue.
				 * This is the most recently pushed element.
				 *
				 * @return The reference to the last element
				 *
				 */
				TYPE& Back();

				/**
				 * @brief Access the last element
				 *
				 * Returns reference to the last element in the queue.
				 * This is the most recently pushed element.
				 *
				 * @return The reference to the last element
				 *
				 */
				const TYPE& Back() const;

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
				 * @brief Returns the number of elements
				 *
				 * Returns the number of elements in the underlying container.
				 *
				 * @return The number of elements in the container
				 *
				 */
				INT_PTR GetSize() const;

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
				CArray<TYPE> m_ArrayFifo;

		};

	}
}

#include "Queue.inl"
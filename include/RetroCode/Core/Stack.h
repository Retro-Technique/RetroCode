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
		 * @brief Class template for manipulating a LIFO data container
		 *
		 */
		template<typename TYPE, typename ARG_TYPE = const TYPE&>
		class CStack
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				CStack();

				/**
				 * @brief Destructor
				 *
				 */
				~CStack();

				/**
				 * @brief Inserts element at the top
				 * 
				 * Pushes the givent element value to the top of the stack.
				 * 
				 * @param newElement The value of the element to push
				 * 
				 * @return The index of the added element
				 *
				 */
				INT_PTR Push(ARG_TYPE newElement);

				/**
				 * @brief Removes the top element
				 * 
				 * Removes the top element from the stack.
				 *
				 */
				void Pop();

				/**
				 * @brief Accesses the top element
				 * 
				 * Returns reference to the top element in the stack.
				 * This is the most recently pushed element.
				 * This element will be removed on a call to Pop().
				 * 
				 * @see Pop
				 *
				 */
				const TYPE& Top() const;

				/**
				 * @brief Accesses the top element
				 *
				 * Returns reference to the top element in the stack.
				 * This is the most recently pushed element.
				 * This element will be removed on a call to Pop().
				 *
				 * @see Pop
				 *
				 */
				TYPE& Top();

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
				CArray<TYPE, ARG_TYPE> m_ArrayLifo;

		};

	}
}

#include "Stack.inl"
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
		 * @brief Class template for manipulating a thread-safe FIFO data container
		 *
		 */
		template<typename TYPE, typename ARG_TYPE = const TYPE&>
		class CMessageQueue
		{
		public:

			/**
			 * @brief Default constructor
			 *
			 */
			CMessageQueue();

			/**
			 * @brief Destructor
			 *
			 */
			~CMessageQueue();

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
			 * @brief Get next message if any
			 *
			 * @param Element The next message
			 *
			 * @return True if not empty
			 *
			 */
			BOOL GetNextMessage(TYPE& Element);

			/**
			 * @brief Waits until the queue is not empty anymore
			 *
			 * @param dwMilliseconds	The time-out interval, in milliseconds
			 * @param bAlertable		See MSDN documentation
			 *
			 * @return The event that caused the function to return
			 * 
			 * @see https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobjectex
			 *
			 */
			DWORD WaitIncomingMessage(DWORD dwMilliseconds = INFINITE, BOOL bAlertable = FALSE);

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
			CCriticalSection		m_Mutex;
			CEvent					m_NotEmpty;
			CQueue<TYPE, ARG_TYPE>	m_Queue;

		};

	}
}

#include "MessageQueue.inl"
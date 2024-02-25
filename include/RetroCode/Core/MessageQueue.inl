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

		template<typename TYPE, typename ARG_TYPE>
		CMessageQueue<TYPE, ARG_TYPE>::CMessageQueue()
			: m_NotEmpty(FALSE, TRUE)
		{
		}

		template<typename TYPE, typename ARG_TYPE>
		CMessageQueue<TYPE, ARG_TYPE>::~CMessageQueue()
		{
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CMessageQueue<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
		{
			CCritSecLock Lock(m_Mutex);

			const INT_PTR nRet = m_Queue.Push(newElement);

			m_NotEmpty.SetEvent();

			return nRet;
		}

		template<typename TYPE, typename ARG_TYPE>
		BOOL CMessageQueue<TYPE, ARG_TYPE>::IsEmpty() const
		{
			CCritSecLock Lock(m_Mutex);
			
			return m_Queue.IsEmpty();
		}

		template<typename TYPE, typename ARG_TYPE>
		BOOL CMessageQueue<TYPE, ARG_TYPE>::GetNextMessage(TYPE& Element)
		{
			CCritSecLock Lock(m_Mutex);

			if (m_Queue.IsEmpty())
			{
				return FALSE;
			}

			Element = m_Queue.Front();

			m_Queue.Pop();

			if (m_Queue.IsEmpty())
			{
				m_NotEmpty.ResetEvent();
			}

			return TRUE;
		}

		template<typename TYPE, typename ARG_TYPE>
		DWORD CMessageQueue<TYPE, ARG_TYPE>::WaitIncomingMessage(DWORD dwMilliseconds, BOOL bAlertable)
		{
			return WaitForSingleObjectEx(m_NotEmpty, dwMilliseconds, bAlertable);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CMessageQueue<TYPE, ARG_TYPE>::RemoveAll()
		{
			CCritSecLock Lock(m_Mutex);

			m_Queue.RemoveAll();
			m_NotEmpty.ResetEvent();
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CMessageQueue<TYPE, ARG_TYPE>::GetSize() const
		{
			CCritSecLock Lock(m_Mutex);

			return m_Queue.GetSize();
		}

	}
}
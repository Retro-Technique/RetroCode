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
		CQueue<TYPE, ARG_TYPE>::CQueue()
		{

		}

		template<typename TYPE, typename ARG_TYPE>
		CQueue<TYPE, ARG_TYPE>::~CQueue()
		{

		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CQueue<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
		{
			return m_ArrayFifo.Add(newElement);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CQueue<TYPE, ARG_TYPE>::Pop()
		{
			m_ArrayFifo.RemoveAt(0);
		}

		template<typename TYPE, typename ARG_TYPE>
		TYPE& CQueue<TYPE, ARG_TYPE>::Front()
		{
			return m_ArrayFifo.GetAt(0);
		}

		template<typename TYPE, typename ARG_TYPE>
		const TYPE& CQueue<TYPE, ARG_TYPE>::Front() const
		{
			return m_ArrayFifo.GetAt(0);
		}

		template<typename TYPE, typename ARG_TYPE>
		TYPE& CQueue<TYPE, ARG_TYPE>::Back()
		{
			return m_ArrayFifo.GetAt(m_ArrayFifo.GetUpperBound());
		}

		template<typename TYPE, typename ARG_TYPE>
		const TYPE& CQueue<TYPE, ARG_TYPE>::Back() const
		{
			return m_ArrayFifo.GetAt(m_ArrayFifo.GetUpperBound());
		}

		template<typename TYPE, typename ARG_TYPE>
		TYPE& CQueue<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex)
		{
			return m_ArrayFifo.GetAt(nIndex);
		}

		template<typename TYPE, typename ARG_TYPE>
		const TYPE& CQueue<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
		{
			return m_ArrayFifo.GetAt(nIndex);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CQueue<TYPE, ARG_TYPE>::RemoveAll()
		{
			m_ArrayFifo.RemoveAll();
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CQueue<TYPE, ARG_TYPE>::GetSize() const
		{
			return m_ArrayFifo.GetSize();
		}

		template<typename TYPE, typename ARG_TYPE>
		BOOL CQueue<TYPE, ARG_TYPE>::IsEmpty() const
		{
			return m_ArrayFifo.IsEmpty();
		}

	}
}
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
		CCircular<TYPE, ARG_TYPE>::CCircular()
			: m_nFirstIdx(0)
			, m_nLastIdx(0)
		{

		}

		template<typename TYPE, typename ARG_TYPE>
		CCircular<TYPE, ARG_TYPE>::~CCircular()
		{

		}

		template<typename TYPE, typename ARG_TYPE>
		void CCircular<TYPE, ARG_TYPE>::SetSize(INT_PTR nSize)
		{
			m_nFirstIdx = 0;
			m_nLastIdx = 0;

			m_Buffer.SetSize(nSize);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CCircular<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
		{
			m_Buffer.SetAt(m_nLastIdx++, newElement);

			if (m_nLastIdx >= m_Buffer.GetSize())
			{
				m_nLastIdx -= m_Buffer.GetSize();
			}
			if (m_nLastIdx == m_nFirstIdx && ++m_nFirstIdx >= m_Buffer.GetSize())
			{
				m_nFirstIdx -= m_Buffer.GetSize();
			}
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CCircular<TYPE, ARG_TYPE>::GetSize() const
		{
			return m_Buffer.GetSize();
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CCircular<TYPE, ARG_TYPE>::GetCount() const
		{
			if (m_nLastIdx >= m_nFirstIdx)
			{
				return m_nLastIdx - m_nFirstIdx;
			}

			return m_Buffer.GetSize() - m_nFirstIdx + m_nLastIdx;
		}

		template<typename TYPE, typename ARG_TYPE>
		TYPE& CCircular<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex)
		{
			INT_PTR uOffset = m_nFirstIdx + nIndex;
			const INT_PTR uCount = m_Buffer.GetSize();

			if (uOffset >= uCount)
			{
				uOffset -= uCount;
			}

			return m_Buffer.GetAt(uOffset);
		}

		template<typename TYPE, typename ARG_TYPE>
		const TYPE& CCircular<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
		{
			INT_PTR uOffset = m_nFirstIdx + nIndex;
			const INT_PTR uCount = m_Buffer.GetSize();

			if (uOffset >= uCount)
			{
				uOffset -= uCount;
			}

			return m_Buffer.GetAt(uOffset);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CCircular<TYPE, ARG_TYPE>::RemoveAll()
		{
			m_nFirstIdx = 0;
			m_nLastIdx = 0;
		}

		template<typename TYPE, typename ARG_TYPE>
		BOOL CCircular<TYPE, ARG_TYPE>::IsEmpty() const
		{
			return m_nFirstIdx == m_nLastIdx;
		}

	}

}
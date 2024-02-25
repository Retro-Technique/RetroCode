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

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		CStaticArray<TYPE, SIZE, ARG_TYPE>::CStaticArray()
		{

		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		CStaticArray<TYPE, SIZE, ARG_TYPE>::~CStaticArray()
		{

		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		INT_PTR CStaticArray<TYPE, SIZE, ARG_TYPE>::GetSize() const
		{
			return SIZE;
		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		INT_PTR CStaticArray<TYPE, SIZE, ARG_TYPE>::GetUpperBound() const
		{
			return (SIZE - 1);
		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		const TYPE& CStaticArray<TYPE, SIZE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
		{
			ASSERT(nIndex >= 0 && nIndex < SIZE);

			if (nIndex >= 0 && nIndex < SIZE)
			{
				return m_Buffer[nIndex];
			}

			AfxThrowInvalidArgException();
		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		TYPE& CStaticArray<TYPE, SIZE, ARG_TYPE>::GetAt(INT_PTR nIndex)
		{
			ASSERT(nIndex >= 0 && nIndex < SIZE);

			if (nIndex >= 0 && nIndex < SIZE)
			{
				return m_Buffer[nIndex];
			}

			AfxThrowInvalidArgException();
		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		const TYPE* CStaticArray<TYPE, SIZE, ARG_TYPE>::GetData() const
		{
			return (const TYPE*)m_Buffer;
		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		TYPE* CStaticArray<TYPE, SIZE, ARG_TYPE>::GetData()
		{
			return (TYPE*)m_Buffer;
		}

		template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
		void CStaticArray<TYPE, SIZE, ARG_TYPE>::SetAt(INT_PTR nIndex, ARG_TYPE newElement)
		{
			m_Buffer[nIndex] = newElement;
		}

	}
}
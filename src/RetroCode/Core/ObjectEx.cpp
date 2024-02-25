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

#include "pch.h"

namespace retro
{
	namespace core
	{

		IMPLEMENT_DYNAMIC(CObjectEx, CObject);

		CObjectEx::CObjectEx()
			: m_uReferenceCounter(1)
		{

		}

		CObjectEx::~CObjectEx()
		{

		}

		void CObjectEx::AddRef() const
		{
			InterlockedIncrement(&m_uReferenceCounter);
		}

		BOOL CObjectEx::Release() const
		{
			const ULONGLONG uReferenceCounter = InterlockedDecrement(&m_uReferenceCounter);

			if (0 == uReferenceCounter)
			{
				delete this;
				return TRUE;
			}

			return FALSE;
		}

		ULONGLONG CObjectEx::GetReferenceCounter() const
		{
			return m_uReferenceCounter;
		}

#ifdef _DEBUG

		void CObjectEx::Dump(CDumpContext& dc) const
		{
			CObject::Dump(dc);
			
			dc << _T("Ref Count: ") << m_uReferenceCounter;
		}

		void CObjectEx::AssertValid() const
		{
			CObject::AssertValid();

			ASSERT(m_uReferenceCounter > 0);
		}

#endif

	}

}
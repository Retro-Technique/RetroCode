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
	namespace mfc
	{

		CDocument* GetActiveDocument(CRuntimeClass* pClass)
		{
			ASSERT(pClass);
			ASSERT(pClass->IsDerivedFrom(RUNTIME_CLASS(CDocument)));

			CWnd* pMainWnd = AfxGetMainWnd();
			if (!pMainWnd)
			{
				return NULL;
			}

			if (pMainWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
			{
				CFrameWnd* pFrame = STATIC_DOWNCAST(CMDIFrameWnd, pMainWnd)->GetActiveFrame();
				if (!pFrame)
				{
					return NULL;
				}

				CDocument* pDocument = pFrame->GetActiveDocument();
				if (pDocument && pDocument->IsKindOf(pClass))
				{
					return pDocument;
				}
			}

			if (pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
			{
				return STATIC_DOWNCAST(CFrameWnd, pMainWnd)->GetActiveDocument();
			}

			return NULL;
		}

	}
}
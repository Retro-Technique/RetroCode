/**
 *
 * Retro Code
 *
 * MIT License
 *
 * Copyright(c) 2014-2023 Retro Technique
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
	namespace scene
	{

		IMPLEMENT_SERIAL(CDrawableNode, CTransformableNode, 1);

		CDrawableNode::CDrawableNode()
			: m_bNeedUpdateCache(TRUE)
			, m_uAlpha(255)
			, m_bVisible(TRUE)
		{

		}

		CDrawableNode::~CDrawableNode()
		{

		}

		void CDrawableNode::SetVisible(BOOL bVisible)
		{
			m_bVisible = bVisible;
		}

		void CDrawableNode::SetAlpha(BYTE uAlpha)
		{
			m_uAlpha = uAlpha;
		}

		BOOL CDrawableNode::IsVisible() const
		{
			return m_bVisible;
		}

		BYTE CDrawableNode::GetAlpha() const
		{
			return m_uAlpha;
		}

		BOOL CDrawableNode::IsWorldVisible() const
		{
			if (!IsVisible())
			{
				return FALSE;
			}

			return CNode::IsWorldVisible();
		}

		void CDrawableNode::OnDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const
		{
			ASSERT(pView);
			ASSERT_VALID(pView);
			ASSERT(pRenderTarget);
			ASSERT_VALID(pRenderTarget);

			if (!m_bVisible)
			{
				return;
			}

			CTransformableNode::OnDraw(pView, pRenderTarget);
		}

		void CDrawableNode::Serialize(CArchive& ar)
		{
			CTransformableNode::Serialize(ar);

			if (ar.IsStoring())
			{
				ar << m_bVisible << m_uAlpha;
			}
			else
			{
				ar >> m_bVisible >> m_uAlpha;
			}
		}

#ifdef _DEBUG

		void CDrawableNode::Dump(CDumpContext& dc) const
		{
			CTransformableNode::Dump(dc);

			dc << _T("Visible: ") << m_bVisible;
			dc << _T("Alpha: ") << m_uAlpha;
		}

		void CDrawableNode::AssertValid() const
		{
			CTransformableNode::AssertValid();
		}

#endif

	}
}
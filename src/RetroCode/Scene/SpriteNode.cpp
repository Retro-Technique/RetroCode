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

		IMPLEMENT_SERIAL(CSpriteNode, CDrawableNode, 1);

		CSpriteNode::CSpriteNode()
			: m_pD2DBitmap(NULL)
			, m_bUseSource(FALSE)
		{
			
		}

		CSpriteNode::~CSpriteNode()
		{
			if (m_pD2DBitmap)
			{
				delete m_pD2DBitmap;
				m_pD2DBitmap = NULL;
			}
		}

		void CSpriteNode::SetTexture(LPCTSTR pszTexture)
		{
			m_strTexture = pszTexture;
			m_bNeedUpdateCache = TRUE;
		}

		void CSpriteNode::SetUseSource(BOOL bUseSource)
		{
			m_bUseSource = bUseSource;
		}

		void CSpriteNode::SetSource(const CD2DRectF& rcSource)
		{
			m_rcSource = rcSource;
		}

		LPCTSTR CSpriteNode::GetTexture() const
		{
			return m_strTexture.GetString();
		}

		BOOL CSpriteNode::IsUseSource() const
		{
			return m_bUseSource;
		}

		const CD2DRectF& CSpriteNode::GetSource() const
		{
			return m_rcSource;
		}

		void CSpriteNode::DoUpdate()
		{
			if (m_bNeedUpdateCache)
			{
				if (m_pD2DBitmap)
				{
					delete m_pD2DBitmap;
					m_pD2DBitmap = NULL;
				}

				m_pD2DBitmap = new CD2DBitmap(NULL, m_strTexture.GetString());

				m_bNeedUpdateCache = FALSE;
			}
		}

		void CSpriteNode::DoDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const
		{
			ASSERT(pView);
			ASSERT_VALID(pView);
			ASSERT(pRenderTarget);
			ASSERT_VALID(pRenderTarget);

			if (!m_pD2DBitmap)
			{
				return;
			}
			
			const CD2DSizeU vPixelSize = m_pD2DBitmap->GetPixelSize();
			const CD2DRectF rcDestination = CD2DRectF(0.f, 0.f, static_cast<FLOAT>(vPixelSize.width), static_cast<FLOAT>(vPixelSize.height));
			const FLOAT fOpacity = CDrawableNode::GetAlpha() / 255.f;
			const D2D1_BITMAP_INTERPOLATION_MODE eInterpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
			const CD2DRectF rcSource = IsUseSource() ? GetSource() : CD2DRectF();

			pRenderTarget->DrawBitmap(m_pD2DBitmap, rcDestination, fOpacity, eInterpolationMode, &rcSource);
		}

		void CSpriteNode::Serialize(CArchive& ar)
		{
			CDrawableNode::Serialize(ar);

			if (ar.IsStoring())
			{
				ar << m_strTexture << m_bUseSource << m_rcSource.left << m_rcSource.top << m_rcSource.right << m_rcSource.bottom;
			}
			else
			{
				ar >> m_strTexture >> m_bUseSource >> m_rcSource.left >> m_rcSource.top >> m_rcSource.right >> m_rcSource.bottom;
			}
		}

#ifdef _DEBUG

		void CSpriteNode::Dump(CDumpContext& dc) const
		{
			CDrawableNode::Dump(dc);

			dc << _T("Texture: ") << m_strTexture;
			dc << _T("UseSource: ") << m_bUseSource;
			dc << _T("Source: (") << m_rcSource.left << _T(";") << m_rcSource.top << _T(";") << m_rcSource.right << _T(";") << m_rcSource.bottom << _T(")");
		}

		void CSpriteNode::AssertValid() const
		{
			CDrawableNode::AssertValid();

			ASSERT(m_rcSource.left >= 0.f);
			ASSERT(m_rcSource.top >= 0.f);
			ASSERT(m_rcSource.right >= 0.f);
			ASSERT(m_rcSource.bottom >= 0.f);
			ASSERT(m_rcSource.left < m_rcSource.right);
			ASSERT(m_rcSource.top < m_rcSource.bottom);
		}

#endif

	}
}
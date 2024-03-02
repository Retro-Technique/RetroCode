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

#pragma once

namespace retro
{
	namespace scene
	{

		class AFX_EXT_API CSpriteNode : public CDrawableNode
		{
#pragma region Constructors

		public:

			DECLARE_SERIAL(CSpriteNode);

		protected:

			CSpriteNode();

		public:

			virtual ~CSpriteNode();

		private:

			CSpriteNode(const CSpriteNode& Node) = delete;
			void operator=(const CSpriteNode& Node) = delete;

#pragma endregion
#pragma region Attributes

		private:

			CD2DBitmap* m_pD2DBitmap;

		private:

			CString		m_strTexture;
			BOOL		m_bUseSource;
			CD2DRectF	m_rcSource;
			
		public:

			void SetTexture(LPCTSTR pszTexture);
			void SetUseSource(BOOL bUseSource);
			void SetSource(const CD2DRectF& rcSource);
			LPCTSTR GetTexture() const;
			BOOL IsUseSource() const;
			const CD2DRectF& GetSource() const;

#pragma endregion
#pragma region Overridables

		public:

			void DoUpdate() override;
			void DoDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const override;
			void Serialize(CArchive& ar) override;
#ifdef _DEBUG
			void Dump(CDumpContext& dc) const override;
			void AssertValid() const override;
#endif

#pragma endregion

		};

	}
}
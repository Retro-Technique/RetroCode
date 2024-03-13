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
	namespace scene
	{

		class AFX_EXT_API CSceneView : public CView
		{
#pragma region Constructors

			DECLARE_DYNCREATE(CSceneView)

		protected:

			CSceneView();
			virtual ~CSceneView();

#pragma endregion
#pragma region Attributes

		public:

			CSceneDocument* GetDocument() const;

		private:

			core::CStack<D2D1::Matrix3x2F> m_stackMatrix;

#pragma endregion
#pragma region Operations

		public:

			void PushMatrix();
			void MultMatrix(const D2D1::Matrix3x2F& mMatrix);
			void PopMatrix();

#pragma endregion
#pragma region Overridables

		public:

			BOOL PreCreateWindow(CREATESTRUCT& cs) override;
			void OnInitialUpdate() override;
			void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
			void OnDraw(CDC* pDC) override;   

#pragma endregion
#pragma region Messages

		protected:

			DECLARE_MESSAGE_MAP()

		public:

			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			afx_msg LRESULT OnRecreateD2DResources(WPARAM wParam, LPARAM lParam);
			afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);
			afx_msg void OnSize(UINT uType, int cx, int cy);

#pragma endregion

		};

#ifndef _DEBUG  
		inline CSceneDocument* CSceneView::GetDocument() const
		{
			return reinterpret_cast<CSceneDocument*>(m_pDocument);
		}
#endif

	}
}




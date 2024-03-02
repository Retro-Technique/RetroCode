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
#include "resource.h"

namespace retro
{
	namespace scene
	{

#pragma region Constructors

		IMPLEMENT_DYNCREATE(CSceneView, CView)

		CSceneView::CSceneView()
		{

		}

		CSceneView::~CSceneView()
		{

		}

#pragma endregion

		BEGIN_MESSAGE_MAP(CSceneView, CView)
			ON_WM_CREATE()
			ON_REGISTERED_MESSAGE(AFX_WM_RECREATED2DRESOURCES, &CSceneView::OnRecreateD2DResources)
			ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CSceneView::OnDraw2D)
			ON_WM_SIZE()
		END_MESSAGE_MAP()

#pragma region Attributes

#ifdef _DEBUG

		CSceneDocument* CSceneView::GetDocument() const
		{
			ASSERT_KINDOF(CSceneDocument, m_pDocument);
			return DYNAMIC_DOWNCAST(CSceneDocument, m_pDocument);
		}

#endif

#pragma endregion
#pragma region Operations

		void CSceneView::PushMatrix()
		{
			if (m_stackMatrix.IsEmpty())
			{
				m_stackMatrix.Push(D2D1::Matrix3x2F::Identity());
			}

			const D2D1::Matrix3x2F& mTop = m_stackMatrix.Top();
			m_stackMatrix.Push(mTop);
		}

		void CSceneView::MultMatrix(const D2D1::Matrix3x2F& mMatrix)
		{
			if (m_stackMatrix.IsEmpty())
			{
				return;
			}

			D2D1::Matrix3x2F& mTop = m_stackMatrix.Top();
			mTop = mTop * mMatrix;
		}

		void CSceneView::PopMatrix()
		{
			if (m_stackMatrix.IsEmpty())
			{
				return;
			}

			m_stackMatrix.Pop();
		}

#pragma endregion
#pragma region Overridables

		BOOL CSceneView::PreCreateWindow(CREATESTRUCT& cs)
		{
			cs.style &= ~WS_BORDER;

			return CView::PreCreateWindow(cs);
		}

		void CSceneView::OnInitialUpdate()
		{
			CNode* pRoot = GetRootDocument();

			pRoot->OnInitialUpdate();

			CView::OnInitialUpdate();
		}

		void CSceneView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
		{
			UNREFERENCED_PARAMETER(pSender);
			UNREFERENCED_PARAMETER(lHint);
			UNREFERENCED_PARAMETER(pHint);

			CNode* pRoot = GetRootDocument();

			pRoot->OnUpdate();
		}

		void CSceneView::OnDraw(CDC* pDC)
		{
			UNREFERENCED_PARAMETER(pDC);
		}

#pragma endregion
#pragma region Implementations

		CNode* CSceneView::GetRootDocument()
		{
			CSceneDocument* pDocument = GetDocument();
			ASSERT(pDocument);
			ASSERT_VALID(pDocument);

			/*
				CNode* pRoot = pDocument->GetRoot();
				ASSERT(pRoot);
				ASSERT_VALID(pRoot);

				return pRoot;
			*/

			return NULL;
		}

		const CNode* CSceneView::GetRootDocument() const
		{
			CSceneDocument* pDocument = GetDocument();
			ASSERT(pDocument);
			ASSERT_VALID(pDocument);

			/*
				const CNode* pRoot = pDocument->GetRoot();
				ASSERT(pRoot);
				ASSERT_VALID(pRoot);

				return pRoot;
			*/

			return NULL;
		}

#pragma endregion
#pragma region Messages

		int CSceneView::OnCreate(LPCREATESTRUCT lpCreateStruct)
		{
			if (CView::OnCreate(lpCreateStruct) == -1)
			{
				return -1;
			}

			EnableD2DSupport();

			if (!IsD2DSupportEnabled())
			{
				return -1;
			}

			return 0;
		}

		LRESULT CSceneView::OnRecreateD2DResources(WPARAM wParam, LPARAM lParam)
		{
			UNREFERENCED_PARAMETER(wParam);
			UNREFERENCED_PARAMETER(lParam);

			return 0L;
		}

		LRESULT CSceneView::OnDraw2D(WPARAM wParam, LPARAM lParam)
		{
			UNREFERENCED_PARAMETER(wParam);

			CHwndRenderTarget* pRenderTarget = reinterpret_cast <CHwndRenderTarget*>(lParam);
			ASSERT(pRenderTarget);
			ASSERT_VALID(pRenderTarget);

			const CNode* pRoot = GetRootDocument();
	
			pRoot->OnDraw(this, pRenderTarget);

			return 0L;
		}

		void CSceneView::OnSize(UINT uType, int cx, int cy)
		{
			CView::OnSize(uType, cx, cy);

			CNode* pRoot = GetRootDocument();

			pRoot->OnResize(core::TVector2i(cx, cy));
		}

#pragma endregion

	}
}
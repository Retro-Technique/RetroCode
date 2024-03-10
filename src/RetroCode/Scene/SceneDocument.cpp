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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace retro
{
	namespace scene
	{

#pragma region Constructors

		IMPLEMENT_DYNCREATE(CSceneDocument, CDocumentEx)

		BEGIN_MESSAGE_MAP(CSceneDocument, CDocumentEx)
		END_MESSAGE_MAP()

		CSceneDocument::CSceneDocument() noexcept
			: m_pRoot(NULL)
		{
			
		}

		CSceneDocument::~CSceneDocument()
		{
			
		}

#pragma endregion
#pragma region Operations

		CNode* CSceneDocument::CreateNode(LPCTSTR pszType)
		{
			if (!pszType)
			{
				return NULL;
			}

			CObject* pObject = CRuntimeClass::CreateObject(pszType);
			if (!pObject)
			{
				return NULL;
			}

			ASSERT_KINDOF(CNode, pObject);

			CNode* pNode = STATIC_DOWNCAST(CNode, pObject);
			
			pNode->SetDocument(this);

			return pNode;
		}

#pragma endregion
#pragma region Overridables

		BOOL CSceneDocument::OnNewDocument()
		{
			if (!CDocumentEx::OnNewDocument())
			{
				return FALSE;
			}

			HRESULT hr = Load();
			if (FAILED(hr))
			{
				return FALSE;
			}

			return TRUE;
		}

		BOOL CSceneDocument::OnOpenDocument(LPCTSTR pszPathName)
		{
			if (!CDocumentEx::OnOpenDocument(pszPathName))
			{
				return FALSE;
			}

			HRESULT hr = Load();
			if (!FAILED(hr))
			{
				return FALSE;
			}

			return TRUE;
		}

		BOOL CSceneDocument::OnSaveDocument(LPCTSTR pszPathName)
		{

			return CDocumentEx::OnSaveDocument(pszPathName);
		}

		void CSceneDocument::OnCloseDocument()
		{

			CDocumentEx::OnCloseDocument();
		}

		void CSceneDocument::DeleteContents()
		{
			Unload();

			CDocumentEx::DeleteContents();
		}

		void CSceneDocument::Serialize(CArchive& ar)
		{
			if (ar.IsStoring())
			{
				ar << m_pRoot;
			}
			else
			{
				ar >> m_pRoot;
			}

			m_ResourceManager.Serialize(ar);
		}

#ifdef _DEBUG

		void CSceneDocument::AssertValid() const
		{
			CDocumentEx::AssertValid();
		}

		void CSceneDocument::Dump(CDumpContext& dc) const
		{
			CDocumentEx::Dump(dc);

			AFXDUMP(m_pRoot);
		}

#endif

#pragma endregion
#pragma region Implementations

		HRESULT CSceneDocument::Load()
		{
			CNode* pNode = CreateNode(_T("CNode"));
			if (!pNode)
			{
				return E_OUTOFMEMORY;
			}

			pNode->SetName(_T("~"));
			m_pRoot = pNode;

			return S_OK;
		}

		void CSceneDocument::Unload()
		{
			if (m_pRoot)
			{
				delete m_pRoot;
				m_pRoot = NULL;
			}
		}

#pragma endregion

	}
}
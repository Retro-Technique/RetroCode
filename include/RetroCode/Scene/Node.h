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

		class CSceneDocument;
		class CSceneView;
		class CViewNode;

		class AFX_EXT_API CNode : public core::CObjectEx
		{
#pragma region Constructors

		public:

			DECLARE_SERIAL(CNode);

		protected:

			CNode();

		public:

			virtual ~CNode();

		private:

			CNode(const CNode& Node) = delete;
			void operator=(const CNode& Node) = delete;

#pragma endregion 
#pragma region Attributes

		private:

			CSceneDocument* m_pDocument;
			CNode*			m_pParent;
			CString			m_strName;
			BOOL			m_bActive;
			CObList			m_Children;

		public:

			void SetName(LPCTSTR pszName);
			LPCTSTR GetName() const;
			void SetActive(BOOL bActive);
			BOOL IsActive() const;
			BOOL IsWorldActive() const;

#pragma endregion 
#pragma region Operations

		public:

			void AddChild(CNode* pChild);
			void RemoveChild(CNode* pChild);
			void RemoveChildren();
			void Detach();
			const CNode* GetParent() const;
			CNode* GetParent();
			const CNode* GetNodeFromName(LPCTSTR pszName) const;
			CNode* GetNodeFromName(LPCTSTR pszName);

#pragma endregion 
#pragma region Overridables

		protected:	

			virtual D2D1::Matrix3x2F Get3x2Matrix() const;
			virtual CViewNode* GetWorldView();
			virtual const CViewNode* GetWorldView() const;
			virtual void DoInitialUpdate();
			virtual void DoUpdate();
			virtual void DoDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const;
			virtual void DoResize(const core::TVector2i& vSize);
			virtual BOOL IsWorldVisible() const;		
			virtual void OnInitialUpdate();
			virtual void OnUpdate();
			virtual void OnDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const;
			virtual void OnResize(const core::TVector2i& vSize);

		public:

			void Serialize(CArchive& ar) override;
#ifdef _DEBUG
			void Dump(CDumpContext& dc) const override;
			void AssertValid() const override;
#endif

#pragma endregion 
#pragma region Implementations

		private:

			void SetDocument(CSceneDocument* pDocument);
			void RebuildingConnections();

#pragma endregion 

			friend class CSceneDocument;
			friend class CSceneView;
			friend class CTransformableNode;

		};

	}
}
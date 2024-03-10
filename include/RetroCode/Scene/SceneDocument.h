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

		class CNode;

		class CSceneDocument : public mfc::CDocumentEx
		{
#pragma region Constructors

		protected:

			CSceneDocument() noexcept;
			DECLARE_DYNCREATE(CSceneDocument)

		public:

			virtual ~CSceneDocument();

#pragma endregion
#pragma region Operations

		public:

			CNode* CreateNode(LPCTSTR pszType);

#pragma endregion
#pragma region Attributes

		private:

			CResourceManager	m_ResourceManager;
			CNode*				m_pRoot;

#pragma endregion
#pragma region Overridables

		public:

			BOOL OnNewDocument() override;
			BOOL OnOpenDocument(LPCTSTR pszPathName) override;
			BOOL OnSaveDocument(LPCTSTR pszPathName) override;
			void OnCloseDocument() override;
			void DeleteContents() override;
			void Serialize(CArchive& ar) override;
#ifdef _DEBUG
			void AssertValid() const override;
			void Dump(CDumpContext& dc) const override;
#endif

#pragma endregion
#pragma region Implementations

		private:

			HRESULT Load();
			void Unload();

#pragma endregion 
#pragma region Messages

		protected:

			DECLARE_MESSAGE_MAP()

#pragma endregion 
		};

	}
}
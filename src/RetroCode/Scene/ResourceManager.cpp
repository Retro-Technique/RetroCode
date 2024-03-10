#include "pch.h"

namespace retro
{
	namespace scene
	{

#pragma region Constructors

		IMPLEMENT_SERIAL(CResourceManager, CObject, 1);

		CResourceManager::CResourceManager()
		{

		}

		CResourceManager::~CResourceManager()
		{

		}

#pragma endregion
#pragma region Operations

		void CResourceManager::OnInitialUpdate()
		{

		}

		void CResourceManager::OnUpdate()
		{
			
		}

#pragma endregion
#pragma region Overridables

		void CResourceManager::Serialize(CArchive& ar)
		{
			CObject::Serialize(ar);

			m_Resources.Serialize(ar);
		}

#ifdef _DEBUG

		void CResourceManager::Dump(CDumpContext& dc) const
		{
			CObject::Dump(dc);

			AFXDUMP(m_Resources);
		}

		void CResourceManager::AssertValid() const
		{
			CObject::AssertValid();

			ASSERT_VALID(&m_Resources);
		}

#endif

#pragma endregion

	}
}
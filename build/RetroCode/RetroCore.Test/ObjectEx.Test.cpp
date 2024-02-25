#include "pch.h"
#include "CppUnitTest.h"

class CMyObject : public retro::core::CObjectEx
{
private:

	DECLARE_DYNCREATE(CMyObject);

protected:

	CMyObject() {}

public:

	virtual ~CMyObject() {}

private:

	CMyObject(const CMyObject& Object) = delete;
	void operator=(const CMyObject& Object) = delete;

};

IMPLEMENT_DYNCREATE(CMyObject, retro::core::CObjectEx);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(ObjectExTest)
	{
	public:

		TEST_METHOD(TestReference)
		{
			CMyObject* pObject = DYNAMIC_DOWNCAST(CMyObject, CMyObject::CreateObject());
			if (pObject)
			{
				const INT nFirstRef = static_cast<INT>(pObject->GetReferenceCounter());
				pObject->AddRef();
				const INT nSecondRef = static_cast<INT>(pObject->GetReferenceCounter());
				const BOOL bIsReleasedAfterSecond = pObject->Release();
				const INT nThirdRef = static_cast<INT>(pObject->GetReferenceCounter());
				const BOOL bIsReleasedAfterThird = pObject->Release();

				Assert::AreEqual(1, nFirstRef);
				Assert::AreEqual(2, nSecondRef);
				Assert::AreEqual(FALSE, bIsReleasedAfterSecond);
				Assert::AreEqual(1, nThirdRef);
				Assert::AreEqual(TRUE, bIsReleasedAfterThird);
			}
		}

	};
}

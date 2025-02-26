#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeCollectionTest
{
	TEST_CLASS(FixedTest)
	{
	public:
		
		TEST_METHOD(TestAt)
		{
			retro::coll::CFixed<INT, 5> Ints;

			Ints.SetAt(0, 1);
			Ints.SetAt(1, 2);
			Ints.SetAt(2, 3);
			Ints.SetAt(3, 4);
			Ints.SetAt(4, 5);

			const INT_PTR nUpperBound = Ints.GetUpperBound();
			const INT nAtLowerBound = Ints.GetAt(0);
			const INT nAtUpperBound = Ints.GetAt(nUpperBound);

			Assert::AreEqual(INT_PTR(4), nUpperBound);
			Assert::AreEqual(1, nAtLowerBound);
			Assert::AreEqual(5, nAtUpperBound);
		}

		TEST_METHOD(TestData)
		{
			retro::coll::CFixed<INT, 5> Ints;

			Ints.SetAt(0, 1);
			Ints.SetAt(1, 2);
			Ints.SetAt(2, 3);
			Ints.SetAt(3, 4);
			Ints.SetAt(4, 5);

			const INT* pData = Ints.GetData();
			const INT nData = *Ints.GetData();

			Assert::IsNotNull(pData);
			Assert::AreEqual(1, nData);
		}

		TEST_METHOD(TestException)
		{
			Assert::ExpectException<CInvalidArgException*>([]()
				{
					retro::coll::CFixed<INT, 2> Ints;

					Ints.GetAt(3);
				});
		}

	};
}

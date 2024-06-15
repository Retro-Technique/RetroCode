#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(QueueTest)
	{
	public:

		TEST_METHOD(TestPushPop)
		{
			retro::core::CQueue<INT> Ints;

			Ints.Push(1);
			Ints.Push(2);

			{
				const INT_PTR nSize = Ints.GetSize();
				const INT nFront = Ints.Front();
				const INT nBack = Ints.Back();

				Assert::AreEqual((INT_PTR)2, nSize);
				Assert::AreEqual(1, nFront);
				Assert::AreEqual(2, nBack);
			}

			Ints.Pop();

			{
				const INT_PTR nSize = Ints.GetSize();
				const INT nFront = Ints.Front();
				const INT nBack = Ints.Back();

				Assert::AreEqual((INT_PTR)1, nSize);
				Assert::AreEqual(2, nFront);
				Assert::AreEqual(2, nBack);
			}

			Ints.Pop();

			{
				const BOOL bEmpty = Ints.IsEmpty();

				Assert::IsTrue(bEmpty);
			}
		}

	};
}

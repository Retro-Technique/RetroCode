#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(StackTest)
	{
	public:

		TEST_METHOD(TestPushPop)
		{
			retro::core::CStack<INT> Ints;

			Ints.Push(1);
			Ints.Push(2);

			{
				const INT_PTR nSize = Ints.GetSize();
				const INT nTop = Ints.Top();

				Assert::AreEqual((INT_PTR)2, nSize);
				Assert::AreEqual(2, nTop);
			}

			Ints.Pop();

			{
				const INT_PTR nSize = Ints.GetSize();
				const INT nTop = Ints.Top();

				Assert::AreEqual((INT_PTR)1, nSize);
				Assert::AreEqual(1, nTop);
			}

			Ints.Pop();

			{
				const BOOL bEmpty = Ints.IsEmpty();

				Assert::IsTrue(bEmpty);
			}
		}

	};
}

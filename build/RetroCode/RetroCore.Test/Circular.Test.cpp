#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(CircularTest)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			retro::core::CCircular<INT> Ints;

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();

			Assert::IsTrue(bEmpty);
			Assert::AreEqual((INT_PTR)0, nSize);
			Assert::AreEqual((INT_PTR)0, nCount);
		}

		TEST_METHOD(TestCapacity)
		{
			retro::core::CCircular<INT> Ints;

			Ints.SetSize(5);

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();

			Assert::IsTrue(bEmpty);
			Assert::AreEqual((INT_PTR)5, nSize);
			Assert::AreEqual((INT_PTR)0, nCount);
		}

		TEST_METHOD(TestPush)
		{
			retro::core::CCircular<INT> Ints;

			Ints.SetSize(5);

			Ints.Push(1);
			Ints.Push(2);
			Ints.Push(3);

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();
			const INT nAt0 = Ints.GetAt(0);
			const INT nAt1 = Ints.GetAt(1);
			const INT nAt2 = Ints.GetAt(2);
			const INT nAt3 = Ints.GetAt(3);
			const INT nAt4 = Ints.GetAt(4);

			Assert::IsFalse(bEmpty);
			Assert::AreEqual((INT_PTR)5, nSize);
			Assert::AreEqual((INT_PTR)3, nCount);
			Assert::AreEqual(0, nAt0);
			Assert::AreEqual(0, nAt1);
			Assert::AreEqual(1, nAt2);
			Assert::AreEqual(2, nAt3);
			Assert::AreEqual(3, nAt4);
		}

		TEST_METHOD(TestClear)
		{
			retro::core::CCircular<INT> Ints;

			Ints.SetSize(5);

			Ints.Push(1);
			Ints.Push(2);
			Ints.Push(3);

			Ints.RemoveAll();

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();

			Assert::IsTrue(bEmpty);
			Assert::AreEqual((INT_PTR)0, nSize);
			Assert::AreEqual((INT_PTR)0, nCount);
		}

	};
}

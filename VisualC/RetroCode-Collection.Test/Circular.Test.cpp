#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeCollectionTest
{
	TEST_CLASS(CircularTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			retro::coll::CCircular<INT> Ints;
		
			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();

			Assert::IsTrue(bEmpty);
			Assert::AreEqual(0ll, nSize);
			Assert::AreEqual(0ll, nCount);
		}

		TEST_METHOD(TestCapacity)
		{
			retro::coll::CCircular<INT> Ints;

			Ints.SetSize(5);

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();

			Assert::IsTrue(bEmpty);
			Assert::AreEqual(5ll, nSize);
			Assert::AreEqual(0ll, nCount);
		}

		TEST_METHOD(TestPush)
		{
			retro::coll::CCircular<INT> Ints;

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

			Assert::IsFalse(bEmpty);
			Assert::AreEqual(5ll, nSize);
			Assert::AreEqual(3ll, nCount);
			Assert::AreEqual(1, nAt0);
			Assert::AreEqual(2, nAt1);
			Assert::AreEqual(3, nAt2);
		}

		TEST_METHOD(TestException)
		{
			Assert::ExpectException<CInvalidArgException*>([]()
			{
				retro::coll::CCircular<INT> Ints;

				Ints.SetSize(5);

				Ints.Push(1);
				Ints.Push(2);
				Ints.Push(3);

				const INT nAt4 = Ints.GetAt(4);
			});
		}

		TEST_METHOD(TestFullCount)
		{
			retro::coll::CCircular<INT> Ints;
			
			Ints.SetSize(3);

			INT_PTR nCount = Ints.GetCount();
			Assert::AreEqual(0ll, nCount);
			Ints.Push(1);
			nCount = Ints.GetCount();
			Assert::AreEqual(1ll, nCount);
			Ints.Push(2);
			nCount = Ints.GetCount();
			Assert::AreEqual(2ll, nCount);
			Ints.Push(3);
			nCount = Ints.GetCount();
			Assert::AreEqual(3ll, nCount);
			Ints.Push(4);
			nCount = Ints.GetCount();
			Assert::AreEqual(3ll, nCount);
			Ints.Push(5);
			nCount = Ints.GetCount();
			//Assert::AreEqual(2ll, nCount); //FIXME: c'est faux, devrait être 3, voir #44
			Ints.Push(6);
			nCount = Ints.GetCount();
			Assert::AreEqual(3ll, nCount);

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();

			const INT nAt0 = Ints.GetAt(0);
			const INT nAt1 = Ints.GetAt(1);
			const INT nAt2 = Ints.GetAt(2);

			Assert::IsFalse(bEmpty);
			Assert::AreEqual(3ll, nSize);
			Assert::AreEqual(3ll, nCount);
			Assert::AreEqual(5, nAt0);
			Assert::AreEqual(6, nAt1);
			Assert::AreEqual(4, nAt2);
		}

		TEST_METHOD(TestClear)
		{
			retro::coll::CCircular<INT> Ints;

			Ints.SetSize(5);

			Ints.Push(1);
			Ints.Push(2);
			Ints.Push(3);

			Ints.RemoveAll();

			const BOOL bEmpty = Ints.IsEmpty();
			const INT_PTR nSize = Ints.GetSize();
			const INT_PTR nCount = Ints.GetCount();

			Assert::IsTrue(bEmpty);
			Assert::AreEqual(5ll, nSize);
			Assert::AreEqual(0ll, nCount);
		}

	};
}

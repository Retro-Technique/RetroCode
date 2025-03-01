#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeCollectionTest
{
	TEST_CLASS(StackTest)
	{
	public:
		
		TEST_METHOD(TestPush)
		{
			retro::coll::CStack<INT> stack;

			stack.Push(1);

			Assert::AreEqual(1, stack.Top());
		}

		TEST_METHOD(TestPop)
		{
			retro::coll::CStack<INT> stack;

			stack.Push(1);
			stack.Push(2);
			stack.Pop();

			Assert::AreEqual(1, stack.Top());
		}

		TEST_METHOD(TestTop)
		{
			retro::coll::CStack<INT> stack;

			stack.Push(1);
			Assert::AreEqual(1, stack.Top());

			stack.Push(2);
			Assert::AreEqual(2, stack.Top());
		}

		TEST_METHOD(TestRemoveAll)
		{
			retro::coll::CStack<INT> stack;

			stack.Push(1);
			stack.Push(2);
			stack.RemoveAll();

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(TestGetSize)
		{
			retro::coll::CStack<INT> stack;

			stack.Push(1);
			stack.Push(2);

			Assert::AreEqual(static_cast<INT_PTR>(2), stack.GetSize());
		}

		TEST_METHOD(TestIsEmpty)
		{
			retro::coll::CStack<INT> stack;

			Assert::IsTrue(stack.IsEmpty());

			stack.Push(1);
			Assert::IsFalse(stack.IsEmpty());
		}

	};
}

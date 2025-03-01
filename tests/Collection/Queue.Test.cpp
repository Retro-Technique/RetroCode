#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeCollectionTest
{
	TEST_CLASS(QueueTest)
	{
	public:
		
		TEST_METHOD(TestPush)
		{
			retro::coll::CQueue<INT> queue;

			queue.Push(1);

			Assert::AreEqual(1, queue.Front());
		}

		TEST_METHOD(TestPop)
		{
			retro::coll::CQueue<INT> queue;

			queue.Push(1);
			queue.Push(2);
			queue.Pop();

			Assert::AreEqual(2, queue.Front());
		}

		TEST_METHOD(TestFront)
		{
			retro::coll::CQueue<INT> queue;

			queue.Push(1);
			Assert::AreEqual(1, queue.Front());

			queue.Push(2);
			Assert::AreEqual(1, queue.Front());
		}

		TEST_METHOD(TestBack)
		{
			retro::coll::CQueue<INT> queue;

			queue.Push(1);
			Assert::AreEqual(1, queue.Back());

			queue.Push(2);
			Assert::AreEqual(2, queue.Back());
		}

		TEST_METHOD(TestRemoveAll)
		{
			retro::coll::CQueue<INT> queue;

			queue.Push(1);
			queue.Push(2);
			queue.RemoveAll();

			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(TestGetSize)
		{
			retro::coll::CQueue<INT> queue;

			queue.Push(1);
			queue.Push(2);

			Assert::AreEqual(static_cast<INT_PTR>(2), queue.GetSize());
		}

		TEST_METHOD(TestIsEmpty)
		{
			retro::coll::CQueue<INT> queue;

			Assert::IsTrue(queue.IsEmpty());

			queue.Push(1);

			Assert::IsFalse(queue.IsEmpty());
		}

	};
}

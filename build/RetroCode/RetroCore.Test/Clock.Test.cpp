#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(ClockTest)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			retro::core::CClock Clock;

			Assert::AreNotEqual(0ull, Clock.GetElapsedTime());
		}

		TEST_METHOD(TestGetElapsedTime)
		{
			retro::core::CClock Clock;

			const ULONGLONG uBefore = Clock.GetElapsedTime();
			Sleep(1000);
			const ULONGLONG uAfter = Clock.GetElapsedTime();

			Assert::IsTrue(uAfter > uBefore);
			Assert::IsTrue(1000ull <= uAfter - uBefore);
		}

		TEST_METHOD(TestRestart)
		{
			retro::core::CClock Clock;

			const ULONGLONG uBefore = Clock.GetElapsedTime();
			const ULONGLONG uRestart = Clock.Restart();
			const ULONGLONG uAfter = Clock.GetElapsedTime();

			Assert::AreEqual(uBefore, uRestart);
			Assert::AreEqual(0ull, uAfter);
		}

	};
}

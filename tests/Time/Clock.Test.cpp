#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(ClockTest)
	{
	public:

		TEST_METHOD(TestElapsedTimeAfterInstantiation)
		{
			retro::time::CClock Clock;

			const ULONGLONG uElapsedTime = Clock.GetElapsedTime();

			Assert::IsTrue(0llu <= uElapsedTime);
			Assert::IsTrue(10llu > uElapsedTime);
		}

		TEST_METHOD(TestElapsedTimeAfterDelay)
		{
			retro::time::CClock Clock;

			Sleep(100);
			const ULONGLONG uElapsedTime = Clock.GetElapsedTime();

			Assert::IsTrue(90llu <= uElapsedTime);
			Assert::IsTrue(110llu >= uElapsedTime);
		}

		TEST_METHOD(TestRestart)
		{
			retro::time::CClock Clock;

			Sleep(100);
			Clock.Restart();
			const ULONGLONG uElapsedTime = Clock.GetElapsedTime();

			Assert::IsTrue(0llu <= uElapsedTime);
			Assert::IsTrue(10llu > uElapsedTime);
		}
		TEST_METHOD(TestRestartReturnValue)
		{
			retro::time::CClock Clock;

			Sleep(100);
			const ULONGLONG uElapsedTime = Clock.Restart();

			Assert::IsTrue(90llu <= uElapsedTime);
			Assert::IsTrue(110llu >= uElapsedTime);
		}

	};
}

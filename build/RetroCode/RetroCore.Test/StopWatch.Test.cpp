#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(StopWatchTest)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			retro::core::CStopWatch StopWatch;

			Assert::IsFalse(StopWatch.GetElapsedTime());
			Assert::IsFalse(StopWatch.IsRunning());
		}

		TEST_METHOD(TestGetElapsedTime)
		{
			retro::core::CStopWatch StopWatch;

			StopWatch.Start();
			const ULONGLONG uBefore = StopWatch.GetElapsedTime();
			Sleep(1000);
			const ULONGLONG uAfter = StopWatch.GetElapsedTime();

			Assert::IsTrue(uAfter > uBefore);
			Assert::IsTrue(1000ull <= uAfter - uBefore);
		}

		TEST_METHOD(TestIsRunning)
		{
			retro::core::CStopWatch StopWatch;

			const BOOL bBeforeStart = StopWatch.IsRunning();
			StopWatch.Start();
			const BOOL bAfterStart = StopWatch.IsRunning();
			StopWatch.Stop();
			const BOOL bAfterStop = StopWatch.IsRunning();

			Assert::IsFalse(bBeforeStart);
			Assert::IsTrue(bAfterStart);
			Assert::IsFalse(bAfterStop);
		}

		TEST_METHOD(TestStart)
		{
			retro::core::CStopWatch StopWatch;

			const ULONGLONG uBefore = StopWatch.GetElapsedTime();
			StopWatch.Start();
			Sleep(1000);
			const ULONGLONG uAfter = StopWatch.GetElapsedTime();

			Assert::IsTrue(uAfter > uBefore);
			Assert::IsTrue(1000ull <= uAfter - uBefore);
		}

		TEST_METHOD(TestStop)
		{
			retro::core::CStopWatch StopWatch;

			StopWatch.Start();
			Sleep(1000);
			StopWatch.Stop();
			const ULONGLONG uAfter = StopWatch.GetElapsedTime();
			Sleep(1000);
			const ULONGLONG uLater = StopWatch.GetElapsedTime();

			Assert::IsTrue(1000ull <= uAfter);
			Assert::IsTrue(uAfter <= uLater);
		}

		TEST_METHOD(TestReset)
		{
			retro::core::CStopWatch StopWatch;

			StopWatch.Start();
			Sleep(1000);
			StopWatch.Reset();

			Assert::IsFalse(StopWatch.GetElapsedTime());
			Assert::IsFalse(StopWatch.IsRunning());
		}

		TEST_METHOD(TestRestart)
		{
			retro::core::CStopWatch StopWatch;

			StopWatch.Start();
			Sleep(1000);
			StopWatch.Restart();
			const ULONGLONG uAfterRestart = StopWatch.GetElapsedTime();
			const BOOL bIsRunningAfterRestart = StopWatch.IsRunning();
			Sleep(1000);
			const ULONGLONG uAfterSleeping = StopWatch.GetElapsedTime();

			Assert::IsFalse(uAfterRestart);
			Assert::IsTrue(bIsRunningAfterRestart);
			Assert::IsTrue(1000ull <= uAfterSleeping);
		}

	};
}

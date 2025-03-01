#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(TimerTest)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			retro::time::CTimer Timer;

			Assert::IsFalse(Timer.GetRemainingTime());
			Assert::IsFalse(Timer.IsRunning());
		}

		TEST_METHOD(TestGetRemainingTime)
		{
			retro::time::CTimer Timer;

			Timer.Reset(2000);
			Timer.Start();
			const ULONGLONG uBefore = Timer.GetRemainingTime();
			Sleep(1000);
			const ULONGLONG uAfter = Timer.GetRemainingTime();

			Assert::IsTrue(uBefore > uAfter);
			Assert::IsTrue(1000ull <= uBefore - uAfter);
		}

		TEST_METHOD(TestIsRunning)
		{
			retro::time::CTimer Timer;

			const BOOL bBeforeStart = Timer.IsRunning();
			Timer.Restart(2000);
			const BOOL bAfterStart = Timer.IsRunning();
			Timer.Stop();
			const BOOL bAfterStop = Timer.IsRunning();

			Assert::IsFalse(bBeforeStart);
			Assert::IsTrue(bAfterStart);
			Assert::IsFalse(bAfterStop);
		}

		TEST_METHOD(TestIsExpired)
		{
			retro::time::CTimer Timer;

			Timer.Reset(1000);
			Timer.Start();
			const BOOL bIsExpired = Timer.IsExpired();
			Sleep(2000);
			const BOOL bIsExpiredAfterSleeping = Timer.IsExpired();

			Assert::IsFalse(bIsExpired);
			Assert::IsTrue(bIsExpiredAfterSleeping);
		}

		TEST_METHOD(TestStart)
		{
			retro::time::CTimer Timer;

			Timer.Stop();
			Timer.Restart(2000);
			const BOOL bIsRunning = Timer.IsRunning();
			Timer.Start();
			const BOOL bIsDoNothing = Timer.IsRunning();

			Assert::IsTrue(bIsRunning);
			Assert::IsTrue(bIsDoNothing);
		}

		TEST_METHOD(TestStop)
		{
			retro::time::CTimer Timer;

			Timer.Start();
			Timer.Stop();
			const BOOL bIsRunning = Timer.IsRunning();
			Timer.Stop();
			const BOOL bIsDoNothing = Timer.IsRunning();

			Assert::IsFalse(bIsRunning);
			Assert::IsFalse(bIsDoNothing);
		}

		TEST_METHOD(TestReset)
		{
			retro::time::CTimer Timer;

			Timer.Stop();
			Timer.Reset(5000);
			const ULONGLONG uFiveSec = Timer.GetRemainingTime();
			Timer.Start();
			Timer.Reset(15000);
			const BOOL bIsRunning = Timer.IsRunning();
			const ULONGLONG uFifteenSec = Timer.GetRemainingTime();

			Assert::IsTrue(5000ull <= uFiveSec);
			Assert::IsFalse(bIsRunning);
			Assert::IsTrue(15000ull <= uFifteenSec);
		}

		TEST_METHOD(TestRestart)
		{
			retro::time::CTimer Timer;

			Timer.Stop();
			Timer.Restart(5000);
			const BOOL bIsRunningFive = Timer.IsRunning();
			const ULONGLONG uFiveSec = Timer.GetRemainingTime();
			Timer.Restart(15000);
			const BOOL bIsRunningFifteen = Timer.IsRunning();
			const ULONGLONG uFifteenSec = Timer.GetRemainingTime();

			Assert::IsTrue(bIsRunningFive);
			Assert::IsTrue(5000ull <= uFiveSec);
			Assert::IsTrue(bIsRunningFifteen);
			Assert::IsTrue(15000ull <= uFifteenSec);
		}

	};
}

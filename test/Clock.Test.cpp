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
			rc::CClock Clock;

			const int32_t nElapsedTime = Clock.GetElapsedTime();

			Assert::IsTrue(0 <= nElapsedTime);
			Assert::IsTrue(10 > nElapsedTime);
		}

		TEST_METHOD(TestElapsedTimeAfterDelay)
		{
			rc::CClock Clock;

			Sleep(100);
			const int32_t nElapsedTime = Clock.GetElapsedTime();

			Assert::IsTrue(90 <= nElapsedTime);
			Assert::IsTrue(110 >= nElapsedTime);
		}

		TEST_METHOD(TestRestart)
		{
			rc::CClock Clock;

			Sleep(100);
			Clock.Restart();
			const int32_t nElapsedTime = Clock.GetElapsedTime();

			Assert::IsTrue(0 <= nElapsedTime);
			Assert::IsTrue(10 > nElapsedTime);
		}
		TEST_METHOD(TestRestartReturnValue)
		{
			rc::CClock Clock;

			Sleep(100);
			const int32_t nElapsedTime = Clock.Restart();

			Assert::IsTrue(90 <= nElapsedTime);
			Assert::IsTrue(110 >= nElapsedTime);
		}

	};
}

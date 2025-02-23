#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeMathTest
{

	TEST_CLASS(RandomTest)
	{
	public:

		TEST_METHOD(TestNextInteger)
		{
			retro::math::CRandom Random;

			const int32_t nRandom = Random.NextInteger();

			Assert::IsTrue(0 <= nRandom);
			Assert::IsTrue(32767 >= nRandom);
		}

		TEST_METHOD(TestNextIntegerWithMax)
		{
			retro::math::CRandom Random;
			const int32_t nMax = 10;

			const int32_t nRandom = Random.NextInteger(nMax);

			Assert::IsTrue(0 <= nRandom);
			Assert::IsTrue(nMax > nRandom);
		}

		TEST_METHOD(TestNextIntegerWithMinAndMax)
		{
			retro::math::CRandom Random;
			const int32_t nMin = 5;
			const int32_t nMax = 15;

			const int32_t nRandom = Random.NextInteger(nMin, nMax);

			Assert::IsTrue(nMin <= nRandom);
			Assert::IsTrue(nMax > nRandom);
		}

		TEST_METHOD(TestNextFloat)
		{
			retro::math::CRandom Random;

			const FLOAT fRandom = Random.NextFloat();

			Assert::IsTrue(0.f <= fRandom);
			Assert::IsTrue(1.f >= fRandom);
		}

		TEST_METHOD(TestNextDouble)
		{
			retro::math::CRandom Random;

			const DOUBLE fRandom = Random.NextDouble();

			Assert::IsTrue(0. <= fRandom);
			Assert::IsTrue(1. >= fRandom);
		}

		TEST_METHOD(TestNextBytes)
		{
			retro::math::CRandom Random;
			const uint8_t uLowerBound = 0;
			const uint8_t hHigherBound = 255;
			const size_t uByteCount = 10;
			uint8_t* pBytes = new uint8_t[uByteCount];
			if (!pBytes)
			{
				return;
			}

			Random.NextBytes(pBytes, uByteCount);

			for (size_t i = 0; i < uByteCount; i++)
			{
				Assert::IsTrue(uLowerBound <= pBytes[i]);
				Assert::IsTrue(hHigherBound >= pBytes[i]);
			}

			delete[] pBytes;
		}

		TEST_METHOD(TestNextBoolean)
		{
			retro::math::CRandom Random;

			const BOOL bRandom = Random.NextBoolean();

			Assert::IsTrue(bRandom == TRUE || bRandom == FALSE);
		}

	};

}

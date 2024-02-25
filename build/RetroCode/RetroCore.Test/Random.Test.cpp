#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(RandomTest)
	{
	public:

		TEST_METHOD(TestNextInteger)
		{
			retro::core::CRandom Random;

			const INT nRandom = Random.NextInteger();

			Assert::IsTrue(0 <= nRandom);
			Assert::IsTrue(32767 >= nRandom);
		}

		TEST_METHOD(TestNextIntegerWithMax)
		{
			retro::core::CRandom Random;
			const INT nMax = 10;

			const INT nRandom = Random.NextInteger(nMax);

			Assert::IsTrue(0 <= nRandom);
			Assert::IsTrue(nMax > nRandom);
		}

		TEST_METHOD(TestNextIntegerWithMinAndMax)
		{
			retro::core::CRandom Random;
			const INT nMin = 5;
			const INT nMax = 15;

			const INT nRandom = Random.NextInteger(nMin, nMax);

			Assert::IsTrue(nMin <= nRandom);
			Assert::IsTrue(nMax > nRandom);
		}

		TEST_METHOD(TestNextFloat)
		{
			retro::core::CRandom Random;

			const FLOAT fRandom = Random.NextFloat();

			Assert::IsTrue(0.f <= fRandom);
			Assert::IsTrue(1.f >= fRandom);
		}

		TEST_METHOD(TestNextDouble)
		{
			retro::core::CRandom Random;

			const DOUBLE fRandom = Random.NextDouble();

			Assert::IsTrue(0. <= fRandom);
			Assert::IsTrue(1. >= fRandom);
		}

		TEST_METHOD(TestNextBytes)
		{
			retro::core::CRandom Random;
			const UCHAR uLowerBound = 0;
			const UCHAR hHigherBound = 255;
			const UINT uByteCount = 10;
			UCHAR* pBytes = new UCHAR[uByteCount];
			if (!pBytes)
			{
				return;
			}

			Random.NextBytes(pBytes, uByteCount);

			for (UINT i = 0; i < uByteCount; i++)
			{
				Assert::IsTrue(uLowerBound <= pBytes[i]);
				Assert::IsTrue(hHigherBound >= pBytes[i]);
			}

			delete[] pBytes;
		}

		TEST_METHOD(TestNextBoolean)
		{
			retro::core::CRandom Random;

			const BOOL bRandom = Random.NextBoolean();

			Assert::IsTrue(bRandom == TRUE || bRandom == FALSE);
		}

	};
}

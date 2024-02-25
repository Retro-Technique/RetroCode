#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(OperationTest)
	{
	public:

		TEST_METHOD(TestSwap)
		{
			INT nA = 1;
			INT nB = 2;
			DOUBLE fC = 3.14;
			DOUBLE fD = 2.71;
			CString strE(_T("Hello"));
			CString strF(_T("World"));

			retro::core::Swap(nA, nB);
			retro::core::Swap(fC, fD);
			retro::core::Swap(strE, strF);

			Assert::AreEqual(2, nA);
			Assert::AreEqual(1, nB);
			Assert::AreEqual(2.71, fC, 0.01);
			Assert::AreEqual(3.141, fD, 0.01);
			Assert::AreEqual(_T("World"), strE.GetString());
			Assert::AreEqual(_T("Hello"), strF.GetString());
		}

		TEST_METHOD(TestMin)
		{
			const INT nA = 1;
			const INT nB = 2;
			const INT nC = -1;
			const INT nD = -2;
			const INT nE = 0;
			const DOUBLE fF = 3.14;
			const DOUBLE fG = -2.71;

			const INT nFirstRes = retro::core::Min(nA, nB);
			const INT nSecondRes = retro::core::Min(nC, nD);
			const INT nThirdRes = retro::core::Min(nE, nE);
			const DOUBLE fFourthRes = retro::core::Min(fF, fG);

			Assert::AreEqual(1, nFirstRes);
			Assert::AreEqual(-2, nSecondRes);
			Assert::AreEqual(0, nThirdRes);
			Assert::AreEqual(-2.71, fFourthRes, 0.01);
		}

	};
}

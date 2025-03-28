#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeMathTest
{

	TEST_CLASS(MatrixStackTest)
	{
	public:

		TEST_METHOD(TestAllocate)
		{
			BOOL bIsDifferent = TRUE;

			HRESULT hr = Allocate(8, bIsDifferent);

			Assert::AreEqual(FALSE, bIsDifferent, _T("Memory leak"));
			Assert::IsTrue(SUCCEEDED(hr), _com_error(hr).ErrorMessage());
		}

		TEST_METHOD(TestReallocate)
		{
			BOOL bIsDifferent = TRUE;

			HRESULT hr = Allocate(24, bIsDifferent);

			Assert::AreEqual(FALSE, bIsDifferent, _T("Memory leak"));
			Assert::IsTrue(SUCCEEDED(hr), _com_error(hr).ErrorMessage());
		}

	private:

		HRESULT Allocate(INT nPushCount, BOOL& bIsMemDifferent)
		{
			retro::memory::CMemoryLeakChecker mlc;

			mlc.Begin();
			{
				retro::math::CMatrixStack MatrixStack;

				for (INT i = 1; i <= nPushCount; i++)
				{
					const FLOAT fVal = static_cast<FLOAT>(i);
					D2D1::Matrix3x2F* pTop = const_cast<D2D1::Matrix3x2F*>(MatrixStack.GetTop());

					pTop->m11 = fVal;
					pTop->m12 = fVal;
					pTop->m21 = fVal;
					pTop->m22 = fVal;
					pTop->dx = fVal;
					pTop->dy = fVal;

					MatrixStack.Push();
				}

				for (INT i = nPushCount; i >= 1; i--)
				{
					const FLOAT fVal = static_cast<FLOAT>(i);

					MatrixStack.Pop();

					D2D1::Matrix3x2F mMatrix(fVal, fVal, fVal, fVal, fVal, fVal);
					const D2D1::Matrix3x2F* pTop = MatrixStack.GetTop();

					const INT nCompare = memcmp(&mMatrix, pTop, sizeof(D2D1::Matrix3x2F));
					if (0 != nCompare)
					{
						return E_FAIL;
					}
				}
			}

			bIsMemDifferent = mlc.End();

			return S_OK;
		}

	};

}

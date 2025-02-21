#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeMathTest
{

	TEST_CLASS(CollideTest)
	{
	public:

		TEST_METHOD(TestCollidePointPoint)
		{
			retro::math::CVector2f v1(3.f, 4.f);
			retro::math::CVector2f v2(3.f, 4.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollidePointPoint(v1, v2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollidePointLine)
		{
			retro::math::CVector2f v(3.f, 3.f);
			retro::math::CFloatLine ln(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollidePointLine(v, ln);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollidePointRect)
		{
			retro::math::CVector2f v(3.f, 4.f);
			retro::math::CFloatRect rc(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollidePointRect(v, rc);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollidePointCircle)
		{
			retro::math::CVector2f v(3.f, 4.f);
			retro::math::CFloatCircle circ(retro::math::CVector2f(3.f, 3.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollidePointCircle(v, circ);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideLineLine)
		{
			retro::math::CFloatLine ln1(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			retro::math::CFloatLine ln2(retro::math::CVector2f(1.f, 5.f), retro::math::CVector2f(5.f, 1.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollideLineLine(ln1, ln2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideLineRect)
		{
			retro::math::CFloatLine ln(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			retro::math::CFloatRect rc(retro::math::CVector2f(2.f, 2.f), retro::math::CVector2f(4.f, 4.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollideLineRect(ln, rc);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideLineCircle)
		{
			retro::math::CFloatLine ln(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			retro::math::CFloatCircle circ(retro::math::CVector2f(3.f, 3.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollideLineCircle(ln, circ);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideRectRect)
		{
			retro::math::CFloatRect rc1(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			retro::math::CFloatRect rc2(retro::math::CVector2f(2.f, 2.f), retro::math::CVector2f(4.f, 4.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollideRectRect(rc1, rc2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideRectCircle)
		{
			retro::math::CFloatRect rc(retro::math::CVector2f(1.f, 1.f), retro::math::CVector2f(5.f, 5.f));
			retro::math::CFloatCircle circ(retro::math::CVector2f(3.f, 3.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollideRectCircle(rc, circ);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideCircleCircl)
		{
			retro::math::CFloatCircle circ1(retro::math::CVector2f(3.f, 3.f), 2.f);
			retro::math::CFloatCircle circ2(retro::math::CVector2f(5.f, 5.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::math::IsCollideCircleCircle(circ1, circ2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

	};

}

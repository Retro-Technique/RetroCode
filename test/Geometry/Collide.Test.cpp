#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroGeometryTest
{
	TEST_CLASS(CollideTest)
	{
	public:

		TEST_METHOD(TestCollidePointPoint)
		{
			retro::geometry::CVector2f v1(3.f, 4.f);
			retro::geometry::CVector2f v2(3.f, 4.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollidePointPoint(v1, v2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollidePointLine)
		{
			retro::geometry::CVector2f v(3.f, 3.f);
			retro::geometry::CFloatLine ln(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollidePointLine(v, ln);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollidePointRect)
		{
			retro::geometry::CVector2f v(3.f, 4.f);
			retro::geometry::CFloatRect rc(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollidePointRect(v, rc);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollidePointCircle)
		{
			retro::geometry::CVector2f v(3.f, 4.f);
			retro::geometry::CFloatCircle circ(retro::geometry::CVector2f(3.f, 3.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollidePointCircle(v, circ);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideLineLine)
		{
			retro::geometry::CFloatLine ln1(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			retro::geometry::CFloatLine ln2(retro::geometry::CVector2f(1.f, 5.f), retro::geometry::CVector2f(5.f, 1.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollideLineLine(ln1, ln2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideLineRect)
		{
			retro::geometry::CFloatLine ln(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			retro::geometry::CFloatRect rc(retro::geometry::CVector2f(2.f, 2.f), retro::geometry::CVector2f(4.f, 4.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollideLineRect(ln, rc);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideLineCircle)
		{
			retro::geometry::CFloatLine ln(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			retro::geometry::CFloatCircle circ(retro::geometry::CVector2f(3.f, 3.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollideLineCircle(ln, circ);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideRectRect)
		{
			retro::geometry::CFloatRect rc1(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			retro::geometry::CFloatRect rc2(retro::geometry::CVector2f(2.f, 2.f), retro::geometry::CVector2f(4.f, 4.f));
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollideRectRect(rc1, rc2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideRectCircle)
		{
			retro::geometry::CFloatRect rc(retro::geometry::CVector2f(1.f, 1.f), retro::geometry::CVector2f(5.f, 5.f));
			retro::geometry::CFloatCircle circ(retro::geometry::CVector2f(3.f, 3.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollideRectCircle(rc, circ);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

		TEST_METHOD(TestCollideCircleCircl)
		{
			retro::geometry::CFloatCircle circ1(retro::geometry::CVector2f(3.f, 3.f), 2.f);
			retro::geometry::CFloatCircle circ2(retro::geometry::CVector2f(5.f, 5.f), 2.f);
			const BOOL bExpectedCollision = TRUE;

			const BOOL bActualCollision = retro::geometry::IsCollideCircleCircle(circ1, circ2);

			Assert::AreEqual(bExpectedCollision, bActualCollision);
		}

	};
}

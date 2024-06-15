#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroGeometryTest
{
	TEST_CLASS(DistanceTest)
	{
	public:

		TEST_METHOD(TestEuclidianDistanceVector2)
		{
			retro::geometry::CVector2<DOUBLE> v1(3.0, 4.0);
			retro::geometry::CVector2<DOUBLE> v2(6.0, 8.0);
			const DOUBLE fExpectedDistance = 5.0;

			const DOUBLE fActualDistance = retro::geometry::EuclidianDistance(v1, v2);

			Assert::AreEqual(fExpectedDistance, fActualDistance, 0.001);
		}

		TEST_METHOD(TestEuclidianDistanceCoordinates)
		{
			const DOUBLE x1 = 3.0, y1 = 4.0, x2 = 6.0, y2 = 8.0;
			const DOUBLE fExpectedDistance = 5.0;

			const DOUBLE fActualDistance = retro::geometry::EuclidianDistance(x1, y1, x2, y2);

			Assert::AreEqual(fExpectedDistance, fActualDistance, 0.001);
		}

		TEST_METHOD(TestManhattanDistanceVector2)
		{
			retro::geometry::CVector2i v1(3, 4);
			retro::geometry::CVector2i v2(6, 8);
			const INT nExpectedDistance = 7;

			const INT nActualDistance = retro::geometry::ManhattanDistance(v1, v2);

			Assert::AreEqual(nExpectedDistance, nActualDistance);
		}

		TEST_METHOD(TestManhattanDistanceCoordinates)
		{
			const INT x1 = 3, y1 = 4, x2 = 6, y2 = 8;
			const INT nExpectedDistance = 7;

			const INT nActualDistance = retro::geometry::ManhattanDistance(x1, y1, x2, y2);

			Assert::AreEqual(nExpectedDistance, nActualDistance);
		}

	};
}

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
    TEST_CLASS(DurationTest)
    {
    public:

        TEST_METHOD(TestAsWeeks)
        {            
            const rc::CDuration duration = rc::seconds(7 * 24 * 60 * 60);

            const float32_t fWeeks = duration.AsWeeks();

            Assert::AreEqual(1.f, fWeeks);
        }

        TEST_METHOD(TestAsDays)
        {
            const rc::CDuration duration = rc::seconds(24 * 60 * 60);

            const float32_t fDays = duration.AsDays();

            Assert::AreEqual(1.f, fDays);
        }

        TEST_METHOD(TestAsHours)
        {
            const rc::CDuration duration = rc::seconds(60 * 60);
         
            const float32_t fHours = duration.AsHours();
            
            Assert::AreEqual(1.f, fHours);
        }

        TEST_METHOD(TestAsMinutes)
        {
            const rc::CDuration duration = rc::seconds(60);
         
            const float32_t fMinutes = duration.AsMinutes();

            Assert::AreEqual(1.f, fMinutes);
        }

        TEST_METHOD(TestAsSeconds)
        {
            const rc::CDuration duration = rc::seconds(1);
         
            const time_t nSeconds = duration.AsSeconds();

            Assert::AreEqual(1ll, nSeconds);
        }

        TEST_METHOD(TestIsPositive)
        {
            const rc::CDuration duration = rc::seconds(1);
         
            const boolean_t bIsPositive = duration.IsPositive();
            
            Assert::IsTrue(bIsPositive);
        }

        TEST_METHOD(TestIsNegative)
        {
            const rc::CDuration duration = rc::seconds(-1);

            const boolean_t bIsNegative = duration.IsNegative();

            Assert::IsTrue(bIsNegative);
        }

        TEST_METHOD(TestIsNull)
        {
            rc::CDuration duration = rc::seconds(0);
                     
            boolean_t bIsNull = duration.IsNull();

            Assert::IsTrue(bIsNull);
        }

        TEST_METHOD(TestWeeksFromString)
        {
            rc::CDuration duration;
         
            duration.FromString("2w");

            Assert::AreEqual(2.f, duration.AsWeeks());
            Assert::AreEqual(14.f, duration.AsDays());
            Assert::AreEqual(336.f, duration.AsHours());
            Assert::AreEqual(20160.f, duration.AsMinutes());
            Assert::AreEqual(1209600ll, duration.AsSeconds());
        }

        TEST_METHOD(TestDaysFromString)
        {
            rc::CDuration duration;

            duration.FromString("28d");

            Assert::AreEqual(4.f, duration.AsWeeks());
            Assert::AreEqual(28.f, duration.AsDays());
            Assert::AreEqual(672.f, duration.AsHours());
            Assert::AreEqual(40320.f, duration.AsMinutes());
            Assert::AreEqual(2419200ll, duration.AsSeconds());
        }

        TEST_METHOD(TestHoursFromString)
        {
            rc::CDuration duration;

            duration.FromString("48h");

            Assert::AreEqual(0.28f, duration.AsWeeks(), 0.01f);
            Assert::AreEqual(2.f, duration.AsDays());
            Assert::AreEqual(48.f, duration.AsHours());
            Assert::AreEqual(2880.f, duration.AsMinutes());
            Assert::AreEqual(172800ll, duration.AsSeconds());
        }

        TEST_METHOD(TestNull)
        {
            rc::CDuration duration;

            duration.Null();
                        
            Assert::AreEqual(0.0f, duration.AsWeeks());
            Assert::AreEqual(0.0f, duration.AsDays());
            Assert::AreEqual(0.0f, duration.AsHours());
            Assert::AreEqual(0.0f, duration.AsMinutes());
            Assert::AreEqual(0ll, duration.AsSeconds());
        }

        TEST_METHOD(TestAddition)
        {
            const rc::CDuration duration1 = rc::seconds(1);
            const rc::CDuration duration2 = rc::seconds(2);
         
            const rc::CDuration result = duration1 + duration2;
            
            Assert::AreEqual(3ll, result.AsSeconds());
        }

        TEST_METHOD(TestSubtraction)
        {
            const rc::CDuration duration1 = rc::seconds(2);
            const rc::CDuration duration2 = rc::seconds(1);

            const rc::CDuration result = duration1 - duration2;
            
            Assert::AreEqual(1ll, result.AsSeconds());
        }

        TEST_METHOD(TestMultiplication)
        {
            const rc::CDuration duration = rc::seconds(1);
         
            const rc::CDuration result = duration * 2;
            
            Assert::AreEqual(2ll, result.AsSeconds());
        }

        TEST_METHOD(TestDivision)
        {
            const rc::CDuration duration = rc::seconds(2);

            const rc::CDuration result = duration / 2;

            Assert::AreEqual(1ll, result.AsSeconds());
        }

        TEST_METHOD(TestModulo)
        {
            const rc::CDuration duration1 = rc::seconds(3);
            const rc::CDuration duration2 = rc::seconds(2);
         
            const rc::CDuration result = duration1 % duration2;
            
            Assert::AreEqual(1ll, result.AsSeconds());
        }
    };
}

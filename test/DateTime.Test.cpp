#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(DateTimeTest)
	{
	public:

		TEST_METHOD(TestDefaultConstructor)
		{
			rc::CDateTime dt;

			Assert::IsFalse(dt.IsValid());
			Assert::AreEqual(rc::CDateTime::INVALID_TIMESTAMP, dt.GetTimestamp());
		}

        TEST_METHOD(TestTimestampConstructor)
        {
            time_t timestamp = 1609459200; // 2021-01-01 01:00:00 UTC+1
            rc::CDateTime dt(timestamp);
            Assert::IsTrue(dt.IsValid());
            Assert::AreEqual(timestamp, dt.GetTimestamp());

            tm details = {};
            dt.ToDesc(details);
            Assert::AreEqual(2021, details.tm_year + 1900);
            Assert::AreEqual(1, details.tm_mon + 1);
            Assert::AreEqual(1, details.tm_mday);
            Assert::AreEqual(1, details.tm_hour);
            Assert::AreEqual(0, details.tm_min);
            Assert::AreEqual(0, details.tm_sec);
        }

        TEST_METHOD(TestInvalidTimestampConstructor)
        {
            rc::CDateTime dt(rc::CDateTime::INVALID_TIMESTAMP);

            Assert::IsFalse(dt.IsValid());
            Assert::AreEqual(rc::CDateTime::INVALID_TIMESTAMP, dt.GetTimestamp());
        }

        TEST_METHOD(TestFromDesc)
        {
            rc::CDateTime dt;

            tm details = {};
            details.tm_year = 2021 - 1900;
            details.tm_mon = 1 - 1;
            details.tm_mday = 1;
            details.tm_hour = 1;
            details.tm_min = 0;
            details.tm_sec = 0;

            dt.FromDesc(details);
            Assert::IsTrue(dt.IsValid());
            Assert::AreEqual(1609459200ll, dt.GetTimestamp()); // 2021-01-01 01:00:00 UTC+1

            details.tm_year = -1;
            dt.FromDesc(details);
            Assert::IsFalse(dt.IsValid());
            Assert::AreEqual(rc::CDateTime::INVALID_TIMESTAMP, dt.GetTimestamp());
        }

        TEST_METHOD(TestFormat)
        {
            time_t timestamp = 1609459200; // 2021-01-01 01:00:00 UTC+1
            rc::CDateTime dt(timestamp);

            rc::CString str;
            dt.Format("%Y-%m-%d %H:%M:%S", str);
            Assert::AreEqual("2021-01-01 01:00:00", str.Ptr());

            dt.Format("%c", str);
            Assert::AreEqual("Fri Jan  1 01:00:00 2021", str.Ptr());

            dt.Format("%x", str);
            Assert::AreEqual("01/01/21", str.Ptr());

            dt.Format("%X", str);
            Assert::AreEqual("01:00:00", str.Ptr());

            rc::CDateTime dtInvalid;
            dtInvalid.Format("%Y-%m-%d %H:%M:%S", str);
            Assert::AreEqual("", str.Ptr());
        }

        TEST_METHOD(TestComparisonOperators)
        {
            time_t timestamp1 = 1609459200; // 2021-01-01 01:00:00 UTC+1
            time_t timestamp2 = 1614537600; // 2021-02-28 19:40:00 UTC+1
            rc::CDateTime dt1(timestamp1);
            rc::CDateTime dt2(timestamp2);

            Assert::IsTrue(dt1 == dt1);
            Assert::IsFalse(dt1 == dt2);
            Assert::IsTrue(dt1 != dt2);
            Assert::IsFalse(dt1 != dt1);
            Assert::IsTrue(dt1 < dt2);
            Assert::IsFalse(dt1 > dt2);
            Assert::IsTrue(dt1 <= dt1);
            Assert::IsTrue(dt1 <= dt2);
            Assert::IsFalse(dt1 >= dt2);
            Assert::IsTrue(dt1 >= dt1);

            rc::CDateTime dtInvalid;
            Assert::IsFalse(dtInvalid == dt1);
            Assert::IsTrue(dtInvalid != dt1);
            Assert::IsTrue(dtInvalid < dt1);
            Assert::IsFalse(dtInvalid > dt1);
            Assert::IsTrue(dtInvalid <= dt1);
            Assert::IsFalse(dtInvalid >= dt1);
        }

        TEST_METHOD(TestAdditionAndSubtractionOperators)
        {
            time_t timestamp = 1609459200; // 2021-01-01 01:00:00 UTC+1
            rc::CDateTime dt(timestamp);

            rc::CDuration dur = rc::weeks(1.f); // 1 semaine
            rc::CDateTime dtResult = dt + dur;
            Assert::AreEqual(timestamp + 7 * 24 * 60 * 60, dtResult.GetTimestamp());

            dtResult = dt - dur;
            Assert::AreEqual(timestamp - 7 * 24 * 60 * 60, dtResult.GetTimestamp());

            rc::CDuration durResult = dt - dtResult;
            Assert::AreEqual(dur.AsSeconds(), durResult.AsSeconds());
        }

	};
}

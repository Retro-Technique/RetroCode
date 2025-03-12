#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeCollectionTest
{
	TEST_CLASS(BitFieldTest)
	{
	public:
		
        TEST_METHOD(TestGetSize)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            Assert::AreEqual(INT_PTR(16), BitField.GetSize());
        }

        TEST_METHOD(TestGetCount)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            BitField.SetAt(0, TRUE);
            BitField.SetAt(1, TRUE);

            Assert::AreEqual(INT_PTR(2), BitField.GetCount());
        }

        TEST_METHOD(TestSetAndGet)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            BitField.SetAt(0, TRUE);
            Assert::IsTrue(BitField.GetAt(0));

            BitField.SetAt(0, FALSE);
            Assert::IsFalse(BitField.GetAt(0));
        }

        TEST_METHOD(TestReset)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            BitField.SetAt(0, TRUE);
            BitField.Reset();

            Assert::IsFalse(BitField.GetAt(0));
        }

        TEST_METHOD(TestIsAll)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            for (INT_PTR i = 0; i < 16; ++i)
            {
                BitField.SetAt(i, TRUE);
            }

            Assert::IsTrue(BitField.IsAll());
        }

        TEST_METHOD(TestIsAny)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            BitField.SetAt(0, TRUE);
            Assert::IsTrue(BitField.IsAny());

            BitField.Reset();
            Assert::IsFalse(BitField.IsAny());
        }

        TEST_METHOD(TestIsNone)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            Assert::IsTrue(BitField.IsNone());

            BitField.SetAt(0, TRUE);
            Assert::IsFalse(BitField.IsNone());
        }

        TEST_METHOD(TestBoundarySetAndGet)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            BitField.SetAt(15, TRUE);
            Assert::IsTrue(BitField.GetAt(15));

            BitField.SetAt(15, FALSE);
            Assert::IsFalse(BitField.GetAt(15));
        }

        TEST_METHOD(TestOutOfBoundsSet)
        {
            Assert::ExpectException<CInvalidArgException*>([]()
                {
                    retro::coll::CBitField<BYTE, 16> BitField;

                    BitField.SetAt(16, TRUE);
                });
        }

        TEST_METHOD(TestOutOfBoundsGet)
        {
            Assert::ExpectException<CInvalidArgException*>([]()
                {
                    retro::coll::CBitField<BYTE, 16> BitField;

                    BitField.GetAt(16);
                });
        }

        TEST_METHOD(TestPartialIsAll)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            for (INT_PTR i = 0; i < 15; ++i)
            {
                BitField.SetAt(i, TRUE);
            }

            Assert::IsFalse(BitField.IsAll());
        }

        TEST_METHOD(TestPartialIsNone)
        {
            retro::coll::CBitField<BYTE, 16> BitField;

            for (INT_PTR i = 0; i < 15; ++i)
            {
                BitField.SetAt(i, TRUE);
            }

            Assert::IsFalse(BitField.IsNone());
        }

	};
}

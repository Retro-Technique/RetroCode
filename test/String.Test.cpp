#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(StringTest)
	{
	public:

		TEST_METHOD(TestEmptyConstructor)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str;

			Assert::AreEqual(size_t(0), str.GetLength());
			Assert::AreEqual(char_t('\0'), str.GetAt(0));

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestConstructor)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str(pszTest);

			Assert::AreEqual(size_t(13), str.GetLength());
			Assert::AreEqual(char_t('H'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestCopyConstructor)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str1(pszTest);
			rc::CString str2(str1);

			Assert::AreEqual(size_t(13), str2.GetLength());
			Assert::AreEqual(char_t('H'), str2.GetAt(0));
			Assert::AreEqual(char_t('!'), str2.GetAt(12));
			Assert::AreEqual(char_t('\0'), str2.GetAt(13));

			END_MEMORY_CHECK
		}
		TEST_METHOD(TestDestructor)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			
			rc::CString str(pszTest);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestSetAt)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str(pszTest);

			str.SetAt(0, 'h');

			Assert::AreEqual(size_t(13), str.GetLength());
			Assert::AreEqual(char_t('h'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestGetAt)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str(pszTest);

			Assert::AreEqual(char_t('H'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));
			Assert::AreEqual(char_t('\0'), str.GetAt(14));

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestIsEmpty)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str;

			Assert::IsTrue(str.IsEmpty());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestLockBuffer)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			lpcstr pszText2 = "Goodbye, world!";
			const size_t uText2Len = strlen(pszText2);
			rc::CString str(pszTest);

			lpstr pszBuffer = str.LockBuffer(100);
			Assert::IsNotNull(pszBuffer);
			strncpy(pszBuffer, pszText2, uText2Len + 1);
			str.UnlockBuffer(uText2Len);

			Assert::AreEqual(size_t(uText2Len), str.GetLength());
			Assert::AreEqual(char_t('G'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(uText2Len - 1));
			Assert::AreEqual(char_t('\0'), str.GetAt(uText2Len));

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestFind)
		{
			BEGIN_MEMORY_CHECK

			const rc::CString str("Hello, world!");

			const uint32_t uIndex1 = str.Find("world");
			const uint32_t uIndex2 = str.Find("Hello");
			const uint32_t uIndex3 = str.Find("!");
			const uint32_t uIndex4 = str.Find("xyz");

			Assert::AreEqual(uint32_t(7), uIndex1);
			Assert::AreEqual(uint32_t(0), uIndex2);
			Assert::AreEqual(uint32_t(12), uIndex3);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex4);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestFindOffset)
		{
			BEGIN_MEMORY_CHECK

			const rc::CString str("Hello, world! Hello, world!");

			const uint32_t uIndex1 = str.Find("world", 2);
			const uint32_t uIndex2 = str.Find("world", 8);
			const uint32_t uIndex3 = str.Find("world", 22);
			const uint32_t uIndex4 = str.Find("xyz", 7);

			Assert::AreEqual(uint32_t(7), uIndex1);
			Assert::AreEqual(uint32_t(21), uIndex2);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex3);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex4);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestFindChar)
		{
			BEGIN_MEMORY_CHECK

			const rc::CString str("Hello, world!");

			const uint32_t uIndex1 = str.Find('l');
			const uint32_t uIndex2 = str.Find('o');
			const uint32_t uIndex3 = str.Find('!');
			const uint32_t uIndex4 = str.Find('x');

			Assert::AreEqual(uint32_t(2), uIndex1);
			Assert::AreEqual(uint32_t(4), uIndex2);
			Assert::AreEqual(uint32_t(12), uIndex3);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex4);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestFindCharOffset)
		{
			BEGIN_MEMORY_CHECK

			const rc::CString str("Hello, world! Hello, world!");

			const uint32_t uIndex1 = str.Find('l', 1);
			const uint32_t uIndex2 = str.Find('l', 5);
			const uint32_t uIndex3 = str.Find('l', 25);
			const uint32_t uIndex4 = str.Find('x', 7);

			Assert::AreEqual(uint32_t(2), uIndex1);
			Assert::AreEqual(uint32_t(10), uIndex2);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex3);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex4);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestReverseFind)
		{
			BEGIN_MEMORY_CHECK

			const rc::CString str("Hello, world!");

			const uint32_t uIndex1 = str.ReverseFind('l');
			const uint32_t uIndex2 = str.ReverseFind('o');
			const uint32_t uIndex3 = str.ReverseFind('!');
			const uint32_t uIndex4 = str.ReverseFind('x');

			Assert::AreEqual(uint32_t(10), uIndex1);
			Assert::AreEqual(uint32_t(8), uIndex2);
			Assert::AreEqual(uint32_t(12), uIndex3);
			Assert::AreEqual(uint32_t(rc::CString::INVALID_STR_POS), uIndex4);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestAppend)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest1 = "Hello, ";
			lpcstr pszTest2 = "world!";
			rc::CString str(pszTest1);

			str.Append(pszTest2, 6);

			Assert::AreEqual(size_t(13), str.GetLength());
			Assert::AreEqual(char_t('H'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestMakeUpper)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str(pszTest);

			str.MakeUpper();

			Assert::AreEqual(size_t(13), str.GetLength());
			Assert::AreEqual(char_t('H'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));
			for (size_t i = 0; i < 13; ++i)
			{
				Assert::IsTrue(
					isupper(str.GetAt(i)) ||
					isspace(str.GetAt(i)) ||
					ispunct(str.GetAt(i)) ||
					str.GetAt(i) == '\0');
			}

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestMakeLower)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str(pszTest);

			str.MakeLower();

			Assert::AreEqual(size_t(13), str.GetLength());
			Assert::AreEqual(char_t('h'), str.GetAt(0));
			Assert::AreEqual(char_t('!'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));
			for (size_t i = 0; i < 13; ++i)
			{
				Assert::IsTrue(
					islower(str.GetAt(i)) || 
					isspace(str.GetAt(i)) || 
					ispunct(str.GetAt(i)) ||
					str.GetAt(i) == '\0');
			}

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestMakeReverse)
		{
			BEGIN_MEMORY_CHECK

			lpcstr pszTest = "Hello, world!";
			rc::CString str(pszTest);

			str.MakeReverse();

			Assert::AreEqual(size_t(13), str.GetLength());
			Assert::AreEqual(char_t('!'), str.GetAt(0));
			Assert::AreEqual(char_t('H'), str.GetAt(12));
			Assert::AreEqual(char_t('\0'), str.GetAt(13));
			for (size_t i = 0; i < 13; ++i)
			{
				Assert::AreEqual(char_t(pszTest[12 - i]), str.GetAt(i));
			}

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestAssignmentLpcstr)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str;
			str = "Hello, world!";

			Assert::AreEqual("Hello, world!", str.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestAssignmentCString)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, world!");
			rc::CString str2;
			str2 = str1;

			Assert::AreEqual("Hello, world!", str2.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestAdditionLpcstr)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str("Hello, ");
			str += "world!";

			Assert::AreEqual("Hello, world!", str.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestAdditionChar)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str("Hello, ");
			str += 'w';

			Assert::AreEqual("Hello, w", str.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestAdditionCString)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, ");
			rc::CString str2("world!");
			str1 += str2;

			Assert::AreEqual("Hello, world!", str1.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestEqualityCString)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, world!");
			rc::CString str2("Hello, world!");
			rc::CString str3("Hello, Mars!");

			Assert::IsTrue(str1 == str2);
			Assert::IsFalse(str1 == str3);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestEqualityLpcstr)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str("Hello, world!");

			Assert::IsTrue(str == "Hello, world!");
			Assert::IsFalse(str == "Hello, Mars!");

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestDifferenceCString)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, world!");
			rc::CString str2("Hello, world!");
			rc::CString str3("Hello, Mars!");

			Assert::IsFalse(str1 != str2);
			Assert::IsTrue(str1 != str3);

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestDifferenceLpcstr)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str("Hello, world!");

			Assert::IsFalse(str != "Hello, world!");
			Assert::IsTrue(str != "Hello, Mars!");

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestRemove)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str("Hello, world!");

			const size_t uCount1 = str.Remove('l');
			const size_t uCount2 = str.Remove('x');
			const size_t uCount3 = str.Remove(' ');

			Assert::AreEqual(size_t(3), uCount1);
			Assert::AreEqual(size_t(0), uCount2);
			Assert::AreEqual(size_t(1), uCount3);
			Assert::AreEqual("Heo,word!", str.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestDelete)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, world!");
			rc::CString str2("Hello, world!");
			rc::CString str3("Hello, world!");
			rc::CString str4("Hello, world!");

			const size_t uCount1 = str1.Delete(7, 5);
			const size_t uCount2 = str2.Delete(0, 5);
			const size_t uCount3 = str3.Delete(12, 10);
			const size_t uCount4 = str4.Delete(12, 0);

			Assert::AreEqual(size_t(5), uCount1);
			Assert::AreEqual("Hello, !", str1.Ptr());
			Assert::AreEqual(size_t(5), uCount2);
			Assert::AreEqual(", world!", str2.Ptr());
			Assert::AreEqual(size_t(1), uCount3);
			Assert::AreEqual("Hello, world", str3.Ptr());
			Assert::AreEqual(size_t(0), uCount4);
			Assert::AreEqual("Hello, world!", str4.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestReplaceChar)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, world!");
			rc::CString str2("Hello, world!");
			rc::CString str3("Hello, world!");

			const size_t uCount1 = str1.Replace('l', 'x');
			const size_t uCount2 = str2.Replace('x', 'y');
			const size_t uCount3 = str3.Replace(' ', 'x');

			Assert::AreEqual(size_t(3), uCount1);
			Assert::AreEqual("Hexxo, worxd!", str1.Ptr());
			Assert::AreEqual(size_t(0), uCount2);
			Assert::AreEqual("Hello, world!", str2.Ptr());
			Assert::AreEqual(size_t(1), uCount3);
			Assert::AreEqual("Hello,xworld!", str3.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestReplaceString)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str1("Hello, world!");
			rc::CString str2("Hello, world!");
			rc::CString str3("Hello, world! world! world!");
			rc::CString str4("Hello, world!");

			const size_t uCount1 = str1.Replace("world", "mars");
			const size_t uCount2 = str2.Replace("xyz", "abc");
			const size_t uCount3 = str3.Replace("world", "mars");
			const size_t uCount4 = str4.Replace("world", "");

			Assert::AreEqual(size_t(1), uCount1);
			Assert::AreEqual("Hello, mars!", str1.Ptr());
			Assert::AreEqual(size_t(0), uCount2);
			Assert::AreEqual("Hello, world!", str2.Ptr());
			Assert::AreEqual(size_t(3), uCount3);
			Assert::AreEqual("Hello, mars! mars! mars!", str3.Ptr());
			Assert::AreEqual(size_t(1), uCount4);
			Assert::AreEqual("Hello, !", str4.Ptr());

			END_MEMORY_CHECK
		}

		TEST_METHOD(TestSplit)
		{
			BEGIN_MEMORY_CHECK

			rc::CString str("Hello, world! How, are, you?");
			lpcstr aTokens[] = { "Hello", " world! How", " are", " you?" };

			str.Split(",", [](lpcstr pszToken, lpvoid pData)
				{
					static uint32_t uIndex = 0;

					lpcstr* ppTokens = reinterpret_cast<lpcstr*>(pData);

					Assert::AreEqual(ppTokens[uIndex++], pszToken);

				}, aTokens);

			END_MEMORY_CHECK
		}

	};
}

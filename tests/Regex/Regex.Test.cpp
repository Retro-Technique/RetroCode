#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeRegexTest
{
	TEST_CLASS(RegexTest)
	{
	private:

		static constexpr const INT ERROR_MESSAGE_COUNT = 256;

	public:

		TEST_METHOD(TestMatchingPaulDiLascia)
		{
			static constexpr LPCTSTR REGEX_PATTERN = _T("{a+}{b*}");
			static constexpr BOOL CASE_SENSITIVE = TRUE;
			static constexpr LPCTSTR REGEX_TEXT = _T("aabcfgaadfabbg");
			static constexpr LPCTSTR MATCH_EXPECTEDS[] = { _T("aa"), _T("b"), _T("aa"), _T("a"), _T("bb") };

			TestMatching(REGEX_PATTERN, REGEX_TEXT, CASE_SENSITIVE, MATCH_EXPECTEDS);
		}

		TEST_METHOD(TestMatchingCaptureGroups)
		{
			static constexpr LPCTSTR REGEX_PATTERN = _T("({a+})({b*})");
			static constexpr BOOL CASE_SENSITIVE = TRUE;
			static constexpr LPCTSTR REGEX_TEXT = _T("aabcfgaadfabbg");
			static constexpr LPCTSTR MATCH_EXPECTEDS[] = { _T("aa"), _T("b"), _T("aa"), _T("a"), _T("bb") };

			TestMatching(REGEX_PATTERN, REGEX_TEXT, CASE_SENSITIVE, MATCH_EXPECTEDS);
		}

		TEST_METHOD(TestMatchingCaseInsensitive)
		{
			static constexpr LPCTSTR REGEX_PATTERN = _T("{a+}{b*}");
			static constexpr BOOL CASE_SENSITIVE = FALSE;
			static constexpr LPCTSTR REGEX_TEXT = _T("AaBbCcAaBb");
			static constexpr LPCTSTR MATCH_EXPECTEDS[] = { _T("Aa"), _T("Bb"), _T("Aa"), _T("Bb") };

			TestMatching(REGEX_PATTERN, REGEX_TEXT, CASE_SENSITIVE, MATCH_EXPECTEDS);
		}

	private:

		void TestMatching(LPCTSTR pszPattern, LPCTSTR pszText, BOOL bCaseSensitive, const LPCTSTR pszExpected[])
		{
			BOOL bIsMemDifferent = FALSE;
			BOOL bIsMatching = FALSE;
			BOOL bIsSuccess = TRUE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };

			retro::memory::CMemoryLeakChecker mlc;

			try
			{
				mlc.Begin();

				{
					retro::regex::CRegExp Regex;

					Regex.Compile(pszPattern, bCaseSensitive);

					bIsMatching = Regex.Match(pszText, [](LPCTSTR pszMatch, LPVOID pData) -> BOOL
						{
							static INT s_nIndex = 0;

							const LPCTSTR* pszExpected = static_cast<const LPCTSTR*>(pData);

							Assert::AreEqual(pszExpected[s_nIndex++], pszMatch, _T("Invalid match"));

							return TRUE;

						}, const_cast<LPCTSTR*>(pszExpected));
				}

				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(acErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::IsTrue(bIsMatching, _T("No match"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

	};
}
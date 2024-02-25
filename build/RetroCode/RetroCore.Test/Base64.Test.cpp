#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCoreTest
{
	TEST_CLASS(Base64Test)
	{
	public:

		TEST_METHOD(TestEmptyString)
		{
			const CString strInput;
			const CString strExpected(_T("AAA="));
			CString strEncoded;
			CString strDecoded;

			HRESULT hrEncoded = retro::core::Base64Encode(strInput.GetString(), strEncoded);
			const UINT_PTR uSize = retro::core::Base64QuerySize(strEncoded.GetString());
			LPTSTR lpczBuffer = strDecoded.GetBufferSetLength((INT)uSize);
			HRESULT hrDecoded = retro::core::Base64Decode(strEncoded.GetString(), lpczBuffer, uSize);
			strDecoded.ReleaseBuffer((INT)uSize);

			Assert::IsTrue(SUCCEEDED(hrEncoded));
			Assert::AreEqual(strExpected.GetString(), strEncoded.GetString());
			Assert::IsTrue(SUCCEEDED(hrDecoded));
			Assert::AreEqual(strInput.GetString(), strDecoded.GetString());
		}

		TEST_METHOD(TestSimpleString)
		{
			const CString strInput(_T("Hello world!"));
			const CString strExpected(_T("SABlAGwAbABvACAAdwBvAHIAbABkACEAAAA="));
			CString strEncoded;
			CString strDecoded;

			HRESULT hrEncoded = retro::core::Base64Encode(strInput.GetString(), strEncoded);
			const UINT_PTR uSize = retro::core::Base64QuerySize(strEncoded.GetString());
			LPTSTR lpczBuffer = strDecoded.GetBufferSetLength((INT)uSize);
			HRESULT hrDecoded = retro::core::Base64Decode(strEncoded.GetString(), lpczBuffer, uSize);
			strDecoded.ReleaseBuffer((INT)uSize);

			Assert::IsTrue(SUCCEEDED(hrEncoded));
			Assert::AreEqual(strExpected.GetString(), strEncoded.GetString());
			Assert::IsTrue(SUCCEEDED(hrDecoded));
			Assert::AreEqual(strInput.GetString(), strDecoded.GetString());
		}

	};
}

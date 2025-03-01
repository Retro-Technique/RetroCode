#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeImageTest
{
	TEST_CLASS(ImageTest)
	{
	public:
		
		ImageTest()
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			SetCurrentDirectory(_T("..\\..\\RetroCode-Image.Test"));
		}

		TEST_METHOD(TestCreateWithDimensions)
		{			
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CSize szExpected = { 100, 120 };
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;
			BOOL bIsMemDifferent = FALSE;
			CSize szBitmap;

			try
			{
				mlc.Begin();

				retro::image::CBitmapRGBA Bitmap;

				Bitmap.Create(szExpected);

				szBitmap = Bitmap.GetSize();

				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(acErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(szExpected.cx, szBitmap.cx, _T("Width not equal"));
			Assert::AreEqual(szExpected.cy, szBitmap.cy, _T("Height not equal"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestLoadBMP)
		{
			TestLoadFromFile(_T("res\\TR.bmp"));
		}

		TEST_METHOD(TestLoadJPG)
		{
			TestLoadFromFile(_T("res\\TR.jpg"));
		}

		TEST_METHOD(TestLoadPNG)
		{
			TestLoadFromFile(_T("res\\TR.png"));
		}

		TEST_METHOD(TestLoadGIF)
		{
			TestLoadFromFile(_T("res\\TR.gif"));
		}

		TEST_METHOD(TestLoadResourceFromDLL)
		{
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;
			BOOL bIsMemDifferent = FALSE;

			try
			{
				mlc.Begin();

				retro::image::CBitmapRGBA Bitmap;
				
				Bitmap.LoadFromResource(_T("res\\data.dll"), MAKEINTRESOURCE(102));

				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(acErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestSaveToFile)
		{
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;
			BOOL bIsMemDifferent = FALSE;
			BOOL bIsFileExists = FALSE;

			try
			{
				mlc.Begin();

				retro::image::CBitmapRGBA Bitmap;

				Bitmap.Create({ 100, 120 });

				Bitmap.SaveToFile(OUTPUT_FILE);

				CFileStatus Status = { 0 };
				bIsFileExists = CFile::GetStatus(OUTPUT_FILE, Status);

				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(acErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::IsTrue(bIsFileExists, _T("File doesn't exist"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));

			if (bIsFileExists)
			{
				CFile::Remove(OUTPUT_FILE);
			}
		}

		TEST_METHOD(TestLockForRead)
		{
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;
			BOOL bIsMemDifferent = FALSE;
			const retro::image::CColorRGBA* pPixels = NULL;

			try
			{
				mlc.Begin();

				retro::image::CBitmapRGBA Bitmap;

				Bitmap.Create({ 100, 120 });

				pPixels = Bitmap.LockForRead();
				
				Bitmap.Unlock();

				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(acErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::IsNotNull(pPixels, _T("Null pixels"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

	private:

		static constexpr const INT ERROR_MESSAGE_COUNT = 256;
		static constexpr LPCTSTR OUTPUT_FILE = _T("res \\output.png");

	private:

		void TestLoadFromFile(LPCTSTR pszFileName)
		{
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;
			BOOL bIsMemDifferent = FALSE;

			try
			{
				retro::image::CBitmapRGBA Bitmap;

				mlc.Begin();

				Bitmap.LoadFromFile(pszFileName);

				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(acErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

	};
}

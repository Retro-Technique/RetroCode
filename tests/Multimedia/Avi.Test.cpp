#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeMultimediaTest
{

	TEST_CLASS(AviTest)
	{
	public:

		AviTest()
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			SetCurrentDirectory(_T("..\\..\\RetroCode-Multimedia.Test"));
		}
		
		TEST_METHOD(TestPLANET)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualVideo;
			FLOAT fFrameRate = 0.f;
			LONG nFrameCount = 0l;

			BOOL bIsSuccess = LoadAvi(VIDEOS[0]._pszFileName, durActualVideo, bIsMemDifferent, fFrameRate, nFrameCount, acErrorMessage);

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(VIDEOS[0]._fFrameRate, fFrameRate, 0.1f, _T("Invalid framerate"));
			Assert::AreEqual(VIDEOS[0]._nFrameCount, nFrameCount, _T("Invalid frame count"));
			Assert::AreEqual(CTimeSpan(0, 0, 0, VIDEOS[0]._nSeconds).GetSeconds(), durActualVideo.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestLoadDEADCITY)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualSound;
			FLOAT fFrameRate = 0.f;
			LONG nFrameCount = 0l;

			BOOL bIsSuccess = LoadAvi(VIDEOS[1]._pszFileName, durActualSound, bIsMemDifferent, fFrameRate, nFrameCount, acErrorMessage);

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(VIDEOS[1]._fFrameRate, fFrameRate, 0.1f, _T("Invalid framerate"));
			Assert::AreEqual(VIDEOS[1]._nFrameCount, nFrameCount, _T("Invalid frame count"));
			Assert::AreEqual(CTimeSpan(0, 0, 0, VIDEOS[1]._nSeconds).GetSeconds(), durActualSound.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

	private:

		static constexpr const INT ERROR_MESSAGE_COUNT = 256;
		static constexpr const struct
		{
			LPCTSTR _pszFileName;
			LONG	_nSeconds;
			FLOAT	_fFrameRate;
			LONG	_nFrameCount;

		} VIDEOS[] =
		{
			{ _T("res\\PLANET.AVI"), 30l, 30.f, 901l },
			{ _T("res\\DEADCITY.AVI"), 57l, 25.f, 1427l }
		};
		static constexpr const INT_PTR VIDEO_COUNT = ARRAYSIZE(VIDEOS);

	private:

		BOOL LoadAvi(LPCTSTR pszFileName, CTimeSpan& durActualVideo, BOOL& bIsMemDifferent, FLOAT& fFrameRate, LONG& nFrameCount, LPTSTR pszErrorMessage)
		{
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;

			try
			{
				mlc.Begin();

				retro::multimedia::CAvi avi;

				avi.OpenFromFile(pszFileName);

				durActualVideo = avi.GetDuration();
				fFrameRate = avi.GetFrameRate();
				nFrameCount = avi.GetFrameCount();
				bIsMemDifferent = mlc.End();
			}
			catch (CException* e)
			{
				bIsSuccess = FALSE;
				e->GetErrorMessage(pszErrorMessage, ERROR_MESSAGE_COUNT);
				e->Delete();
			}

			return bIsSuccess;
		}

	};

}

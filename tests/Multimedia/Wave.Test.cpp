#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RetroCodeMultimediaTest
{

	TEST_CLASS(WaveTest)
	{
	public:

		WaveTest()
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			SetCurrentDirectory(_T("..\\..\\RetroCode-Multimedia.Test"));
		}
		
		TEST_METHOD(TestBOURB1M1)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualSound;

			BOOL bIsSuccess = LoadWave(SOUNDS[0]._pszFileName, durActualSound, bIsMemDifferent, acErrorMessage);

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(CTimeSpan(0, 0, 0, SOUNDS[0]._nSeconds).GetSeconds(), durActualSound.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestLoadGRPLAFF1)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualSound;

			BOOL bIsSuccess = LoadWave(SOUNDS[1]._pszFileName, durActualSound, bIsMemDifferent, acErrorMessage);

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(CTimeSpan(0, 0, 0, SOUNDS[1]._nSeconds).GetSeconds(), durActualSound.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestLoadHELLO)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualSound;

			BOOL bIsSuccess = LoadWave(SOUNDS[2]._pszFileName, durActualSound, bIsMemDifferent, acErrorMessage);

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(CTimeSpan(0, 0, 0, SOUNDS[2]._nSeconds).GetSeconds(), durActualSound.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestLoadSIREN1)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualSound;

			BOOL bIsSuccess = LoadWave(SOUNDS[3]._pszFileName, durActualSound, bIsMemDifferent, acErrorMessage);

			Assert::IsTrue(bIsSuccess, acErrorMessage);
			Assert::AreEqual(CTimeSpan(0, 0, 0, SOUNDS[3]._nSeconds).GetSeconds(), durActualSound.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

		TEST_METHOD(TestLoadEQUITATION)
		{
			BOOL bIsMemDifferent = FALSE;
			TCHAR acErrorMessage[ERROR_MESSAGE_COUNT] = { _T("\0") };
			CTimeSpan durActualSound;

			BOOL bIsSuccess = LoadWave(SOUNDS[4]._pszFileName, durActualSound, bIsMemDifferent, acErrorMessage);

			Assert::IsFalse(bIsSuccess, acErrorMessage);
			Assert::AreEqual(CTimeSpan(0, 0, 0, SOUNDS[4]._nSeconds).GetSeconds(), durActualSound.GetSeconds(), _T("Invalid duration"));
			Assert::IsFalse(bIsMemDifferent, _T("Memory leak"));
		}

	private:

		static constexpr const INT ERROR_MESSAGE_COUNT = 256;
		static constexpr const struct
		{
			LPCTSTR _pszFileName;
			LONG	_nSeconds;

		} SOUNDS[] =
		{
			{ _T("res\\BOURB1M1.WAV"), 17l },
			{ _T("res\\GRPLAFF1.WAV"), 2l },
			{ _T("res\\HELLO.WAV"), 5l },
			{ _T("res\\SIREN1.WAV"), 3l },
			{ _T("res\\EQUITATION.PNG"), 0l }
		};
		static constexpr const INT_PTR SOUND_COUNT = ARRAYSIZE(SOUNDS);

	private:

		BOOL LoadWave(LPCTSTR pszFileName, CTimeSpan& durActualSound, BOOL& bIsMemDifferent, LPTSTR pszErrorMessage)
		{
			retro::memory::CMemoryLeakChecker mlc;
			BOOL bIsSuccess = TRUE;

			try
			{
				mlc.Begin();

				retro::multimedia::CWave wave;

				wave.LoadFromFile(pszFileName);

				durActualSound = wave.GetDuration();
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

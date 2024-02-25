/**
 *
 * Retro Code
 *
 * MIT License
 *
 * Copyright(c) 2014-2024 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once

namespace retro
{
	namespace core
	{

		class CLogManager
		{
			private:

				CLogManager();
				~CLogManager();

			public:

				HRESULT RegisterObserver(ILogObserver* pObserver);
				void UnregisterObserver(ILogObserver* pObserver);
				void UnregisterAll();
				void Log(LPCTSTR lpszMessage, ELogLevel eLogLevel);
				void LogInterfaceError(LPCTSTR lpszMessage, HRESULT hr, ELogLevel eLogLevel);
				void LogWinError(LPCTSTR lpszMessage, DWORD dwError, ELogLevel eLogLevel);
				void Flush();
				void Clear();

			private:

				void DispatchLogs(const CTime& dtNow, ELogLevel eLogLevel, LPCTSTR lpszMessage);

			private:

				CMutex					m_Mutex;
				CList<ILogObserver*>	m_Observers;
				CString					m_strLastMessage;
				INT						m_nRepeatedMessageCount;

				struct TLog
				{
					CTime		dtDate;
					ELogLevel	eLevel;
					CString		strMessage;
				};

				CList<TLog>		m_Historic;

			public:

				static CLogManager& GetInstance();

			private:

				static CLogManager ms_Instance;

		};

#define LogManager CLogManager::GetInstance()

	}
}
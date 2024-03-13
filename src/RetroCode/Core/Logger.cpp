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

#include "pch.h"
#include "resource.h"

namespace retro
{
	namespace core
	{

		CLogger::CLogger(INT_PTR nHistoricSize)
			: m_nRepeatedMessageCount(0)
		{
			m_Historic.SetSize(nHistoricSize);
		}

		CLogger::~CLogger()
		{

		}

		HRESULT CLogger::RegisterObserver(ILogObserver* pObserver)
		{
			ASSERT(pObserver);

			POSITION pos = m_Observers.AddTail(pObserver);
			if (!pos)
			{
				return E_OUTOFMEMORY;
			}

			return S_OK;
		}

		void CLogger::UnregisterObserver(ILogObserver* pObserver)
		{
			ASSERT(pObserver);

			POSITION pos = m_Observers.Find(pObserver);
			if (pos)
			{
				m_Observers.RemoveAt(pos);
			}
		}

		void CLogger::UnregisterAll()
		{
			m_Observers.RemoveAll();
		}

		void CLogger::Log(LPCTSTR pszMessage, ELogLevel eLogLevel)
		{
			ASSERT(AfxIsValidString(pszMessage));

			m_Mutex.Lock();
			
			if (StrCmp(m_strLastMessage.GetString(), pszMessage) == 0)
			{
				m_nRepeatedMessageCount++;
				return;
			}

			const CTime dtNow = CTime::GetCurrentTime();

			if (m_nRepeatedMessageCount > 0)
			{
				CString strTmp;
				strTmp.FormatMessage(IDS_LOG_REPEAT_MSG, m_nRepeatedMessageCount);

				DispatchLogs(dtNow, ELogLevel_Information, strTmp.GetString());

				m_nRepeatedMessageCount = 0;
			}

			m_strLastMessage = pszMessage;

			DispatchLogs(dtNow, eLogLevel, pszMessage);

			m_Mutex.Unlock();
		}

		void CLogger::Log(UINT uFormatID, ELogLevel eLogLevel)
		{
			CString strFormat;

			if (strFormat.LoadString(uFormatID))
			{
				Log(strFormat.GetString(), eLogLevel);
			}
		}

		void CLogger::LogInterfaceError(LPCTSTR pszMessage, HRESULT hr, ELogLevel eLogLevel)
		{
			ASSERT(AfxIsValidString(pszMessage));

			_com_error Error(hr);
			CString strError;
		
			strError += pszMessage;
			strError += Error.ErrorMessage();

			Log(strError.GetString(), eLogLevel);
		}

		void CLogger::LogWinError(LPCTSTR pszMessage, DWORD dwError, ELogLevel eLogLevel)
		{
			ASSERT(AfxIsValidString(pszMessage));

			HRESULT hr = __HRESULT_FROM_WIN32(dwError);
			LogInterfaceError(pszMessage, hr, eLogLevel);
		}

		void CLogger::Flush()
		{
			m_Mutex.Lock();

			const INT_PTR nLogCount = m_Historic.GetCount();

			for (INT_PTR i = 0; i < nLogCount; i++)
			{
				const TLog& Entry = m_Historic.GetAt(i);

				POSITION pos = m_Observers.GetHeadPosition();
				while (pos)
				{
					ILogObserver* pObserver = m_Observers.GetNext(pos);
					if (pObserver)
					{
						pObserver->OnMessage(Entry.dtDate, Entry.eLevel, Entry.strMessage.GetString());
					}
				}
			}

			m_Mutex.Unlock();
		}

		void CLogger::Clear()
		{
			m_Mutex.Lock();

			m_Historic.RemoveAll();

			m_Mutex.Unlock();
		}

		void CLogger::DispatchLogs(const CTime& dtNow, ELogLevel eLogLevel, LPCTSTR pszMessage)
		{
			ASSERT(pszMessage);

			TLog Entry;
			Entry.dtDate = dtNow;
			Entry.eLevel = eLogLevel;
			Entry.strMessage = pszMessage;

			m_Historic.Push(Entry);

			POSITION pos = m_Observers.GetHeadPosition();
			while (pos)
			{
				ILogObserver* pObserver = m_Observers.GetNext(pos);
				if (pObserver)
				{
					pObserver->OnMessage(dtNow, eLogLevel, pszMessage);
				}
			}
		}

	}
}
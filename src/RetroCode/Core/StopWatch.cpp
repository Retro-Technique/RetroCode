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

namespace retro
{
	namespace core
	{

		CStopWatch::CStopWatch()
			: m_uTimeBuffer(0)
			, m_bRunning(FALSE)
		{

		}

		CStopWatch::~CStopWatch()
		{

		}

		ULONGLONG CStopWatch::GetElapsedTime() const
		{
			return m_bRunning ? m_uTimeBuffer + m_Clock.GetElapsedTime() : m_uTimeBuffer;
		}

		BOOL CStopWatch::IsRunning() const
		{
			return m_bRunning;
		}

		void CStopWatch::Start()
		{
			if (!m_bRunning)
			{
				m_bRunning = TRUE;
				m_Clock.Restart();
			}
		}

		void CStopWatch::Stop()
		{
			if (m_bRunning)
			{
				m_bRunning = FALSE;
				m_uTimeBuffer += m_Clock.GetElapsedTime();
			}
		}

		void CStopWatch::Reset()
		{
			m_uTimeBuffer = 0;
			m_bRunning = false;
		}

		void CStopWatch::Restart()
		{
			Reset();
			Start();
		}

	}
}
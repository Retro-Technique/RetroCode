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

		CTimer::CTimer()
			: m_uLimit(0)
		{

		}

		CTimer::~CTimer()
		{
			
		}

		ULONGLONG CTimer::GetRemainingTime() const
		{
			return m_uLimit - m_StopWatch.GetElapsedTime();
		}

		BOOL CTimer::IsRunning() const
		{
			return m_StopWatch.IsRunning() && !IsExpired();
		}

		BOOL CTimer::IsExpired() const
		{
			return m_StopWatch.GetElapsedTime() >= m_uLimit;
		}

		void CTimer::Start()
		{
			m_StopWatch.Start();
		}

		void CTimer::Stop()
		{
			m_StopWatch.Stop();
		}

		void CTimer::Reset(const ULONGLONG uTimeLimit)
		{
			if (uTimeLimit <= 0)
			{
				return;
			}

			m_uLimit = uTimeLimit;
			m_StopWatch.Reset();
		}

		void CTimer::Restart(const ULONGLONG uTimeLimit)
		{
			Reset(uTimeLimit);
			Start();
		}

	}
}
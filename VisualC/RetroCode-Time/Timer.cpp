/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#include "pch.h"

namespace retro
{
	namespace time
	{

#pragma region Constructors

		IMPLEMENT_DYNAMIC(CTimer, CObject)

		CTimer::CTimer()
			: m_uLimit(0ull)
		{

		}

#pragma endregion
#pragma region Operations

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

		void CTimer::Reset(ULONGLONG uTimeLimit)
		{
			if (uTimeLimit <= 0ull)
			{
				return;
			}

			m_uLimit = uTimeLimit;
			m_StopWatch.Reset();
		}

		void CTimer::Restart(ULONGLONG uTimeLimit)
		{
			Reset(uTimeLimit);
			Start();
		}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

		void CTimer::AssertValid() const
		{
			CObject::AssertValid();

			m_StopWatch.AssertValid();
		}

		void CTimer::Dump(CDumpContext& dc) const
		{
			CObject::Dump(dc);

			m_StopWatch.Dump(dc);
			dc << _T("m_uLimit = ") << m_uLimit << _T("\n");
		}

#endif

#pragma endregion

	}
}
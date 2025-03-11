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
#include "MMIOException.h"

namespace retro::multimedia
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CMMIO, CObject)

	CMMIO::CMMIO()
		: m_hMMIO(NULL)
	{

	}

	CMMIO::~CMMIO()
	{
		Close();
	}

#pragma endregion
#pragma region Operations

	void CMMIO::OpenFromFile(LPCTSTR pszFileName, DWORD uFlags)
	{
		ASSERT(AfxIsValidString(pszFileName, MAX_PATH));

		CMMIOInfo mmioInfo;
		if (m_hMMIO = mmioOpen(const_cast<LPTSTR>(pszFileName), &mmioInfo, uFlags); !m_hMMIO)
		{
			throw new CMMIOException(mmioInfo.wErrorRet);
		}
	}

	void CMMIO::OpenFromMemory(CMMMemoryIOInfo& mmioInfo)
	{
		if (m_hMMIO = mmioOpen(NULL, &mmioInfo, MMIO_READWRITE); !m_hMMIO)
		{
			throw new CMMIOException(mmioInfo.wErrorRet);
		}
	}

	void CMMIO::Close(UINT uFlags)
	{
		if (m_hMMIO)
		{
			mmioClose(m_hMMIO, uFlags);
			m_hMMIO = NULL;
		}
	}

	BOOL CMMIO::Ascend(CMMChunk& mmckInfo, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioAscend(m_hMMIO, &mmckInfo, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

	BOOL CMMIO::Descend(CMMChunk& mmckInfo, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioDescend(m_hMMIO, &mmckInfo, 0, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

	BOOL CMMIO::Descend(CMMChunk& mmckInfo, CMMChunk& mmckParent, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioDescend(m_hMMIO, &mmckInfo, &mmckParent, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

	LONG CMMIO::Read(HPSTR pData, LONG nLen)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return 0;
		}

		return mmioRead(m_hMMIO, pData, nLen);
	}

	LONG CMMIO::Write(LPCSTR pData, LONG nLen)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return 0;
		}

		return mmioWrite(m_hMMIO, pData, nLen);
	}

	LONG CMMIO::Seek(LONG nOffset, INT nOrigin)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return 0;
		}

		return mmioSeek(m_hMMIO, nOffset, nOrigin);
	}

	LRESULT CMMIO::SendMessage(UINT uMsg, LPARAM lParam1, LPARAM lParam2)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return 0;
		}

		return mmioSendMessage(m_hMMIO, uMsg, lParam1, lParam2);
	}

	BOOL CMMIO::SetBuffer(LPSTR pBuffer, LONG nBuffer, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioSetBuffer(m_hMMIO, pBuffer, nBuffer, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

	BOOL CMMIO::GetInfo(CMMIOInfo& mmioInfo, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioGetInfo(m_hMMIO, &mmioInfo, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

	BOOL CMMIO::SetInfo(const CMMIOInfo& mmioInfo, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioSetInfo(m_hMMIO, &mmioInfo, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

	BOOL CMMIO::Advance(CMMIOInfo& mmioInfo, UINT uFlags)
	{
		ASSERT_VALID(this);

		if (!m_hMMIO)
		{
			return FALSE;
		}

		if (const MMRESULT mmr = mmioAdvance(m_hMMIO, &mmioInfo, uFlags); MMSYSERR_NOERROR != mmr)
		{
			throw new CMMIOException(mmr);
		}

		return TRUE;
	}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

	void CMMIO::AssertValid() const
	{
		CObject::AssertValid();
	}

	void CMMIO::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_hMMIO = ") << m_hMMIO << _T("\n");
	}

#endif

#pragma endregion

}
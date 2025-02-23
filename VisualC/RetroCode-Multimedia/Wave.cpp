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

namespace retro::multimedia
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CWave, CObject)

	CWave::CWave()
		: m_pData(NULL)
		, m_uDataLen(0)
	{

	}

	CWave::~CWave()
	{
		Unload();
	}

#pragma endregion
#pragma region Operations

	void CWave::LoadFromFile(LPCTSTR pszFileName)
	{
		ASSERT(AfxIsValidString(pszFileName, MAX_PATH));

		Unload();

		CFileException fileException;
		CFile fileWave;
		if (!fileWave.Open(pszFileName, CFile::modeRead, &fileException))
		{
			AfxThrowFileException(fileException.m_cause, fileException.m_lOsError, pszFileName);
		}

		m_uDataLen = static_cast<DWORD>(fileWave.GetLength());

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, m_uDataLen);
		if (!hGlobal)
		{
			AfxThrowMemoryException();
		}

		LPVOID pBuffer = GlobalLock(hGlobal);
		m_pData = static_cast<LPBYTE>(pBuffer);

		fileWave.Read(m_pData, m_uDataLen);
	}

	void CWave::Unload()
	{
		if (m_pData)
		{
			GlobalFree(m_pData);
			m_pData = NULL;
			m_uDataLen = 0;
		}
	}

	BOOL CWave::IsValid() const
	{
		return m_pData ? TRUE : FALSE;
	}

	BOOL CWave::Play(BOOL bAsync, BOOL bLooped) const
	{
		ASSERT_VALID(this);
		
		if (!IsValid())
		{
			return FALSE;
		}

		DWORD uFlags = SND_MEMORY | SND_NODEFAULT;
		uFlags |= bAsync ? SND_ASYNC : SND_SYNC;
		uFlags |= bLooped ? (SND_ASYNC | SND_LOOP) : 0;

		return PlaySound(reinterpret_cast<LPCTSTR>(m_pData), NULL, uFlags);
	}

	BOOL CWave::GetFormat(WAVEFORMATEX& wfFormat) const
	{
		ASSERT_VALID(this);

		if (!IsValid())
		{
			return FALSE;
		}

		CMMIO mmio;

		CMMMemoryIOInfo mmioInfo(reinterpret_cast<HPSTR>(m_pData), m_uDataLen);
		mmio.OpenFromMemory(mmioInfo);

		CMMTypeChunk mmckParent('W', 'A', 'V', 'E');
		mmio.Descend(mmckParent, MMIO_FINDRIFF);

		CMMIdChunk mmckSubChunk('f', 'm', 't', ' ');
		mmio.Descend(mmckSubChunk, mmckParent, MMIO_FINDCHUNK);

		mmio.Read(reinterpret_cast<HPSTR>(&wfFormat), sizeof(WAVEFORMATEX));

		mmio.Ascend(mmckSubChunk);

		mmio.Close();

		return TRUE;
	}

	DWORD CWave::GetDataLen() const
	{
		ASSERT_VALID(this);

		if (!IsValid())
		{
			return 0;
		}

		CMMIO mmio;

		CMMMemoryIOInfo mmioInfo(reinterpret_cast<HPSTR>(m_pData), m_uDataLen);
		mmio.OpenFromMemory(mmioInfo);

		CMMTypeChunk mmckParent('W', 'A', 'V', 'E');
		mmio.Descend(mmckParent, MMIO_FINDRIFF);

		CMMIdChunk mmckSubChunk('d', 'a', 't', 'a');
		mmio.Descend(mmckSubChunk, mmckParent, MMIO_FINDCHUNK);

		mmio.Close();
	
		return mmckSubChunk.cksize;
	}

	DWORD CWave::GetData(LPBYTE pWaveData, DWORD uMaxToCopy) const
	{
		ASSERT_VALID(this);

		if (!AfxIsValidAddress(pWaveData, uMaxToCopy))
		{
			return 0;
		}

		if (!IsValid())
		{
			return 0;
		}

		CMMIO mmio;

		CMMMemoryIOInfo mmioInfo(reinterpret_cast<HPSTR>(m_pData), m_uDataLen);
		mmio.OpenFromMemory(mmioInfo);

		CMMTypeChunk mmckParent('W', 'A', 'V', 'E');
		mmio.Descend(mmckParent, MMIO_FINDRIFF);

		const DWORD uReadLen = mmio.Read(reinterpret_cast<HPSTR>(pWaveData), uMaxToCopy);

		mmio.Close();

		return uReadLen;
	}

	CTimeSpan CWave::GetDuration() const
	{
		ASSERT_VALID(this);

		WAVEFORMATEX wfFormat = { 0 };
		GetFormat(wfFormat);

		const FLOAT fSeconds = static_cast<FLOAT>(GetDataLen()) / (wfFormat.nAvgBytesPerSec * wfFormat.nBlockAlign);
		const INT nSeconds = static_cast<INT>(fSeconds);

		return CTimeSpan(0, 0, 0, nSeconds);
	}

	WORD CWave::GetChannelCount() const
	{
		ASSERT_VALID(this);

		WAVEFORMATEX wfFormat = { 0 };
		GetFormat(wfFormat);

		return wfFormat.nChannels;
	}

	DWORD CWave::GetSampleRate() const
	{
		ASSERT_VALID(this);

		WAVEFORMATEX wfFormat = { 0 };
		GetFormat(wfFormat);

		return wfFormat.nSamplesPerSec;
	}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

	void CWave::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT_POINTER(m_pData, BYTE);
		ASSERT(m_uDataLen > 0);
	}

	void CWave::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_pData = ") << m_pData << _T("\n");
		dc << _T("m_uDataLen = ") << m_uDataLen << _T("\n");
	}

#endif

#pragma endregion

}
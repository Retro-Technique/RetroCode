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
#include "Win32Exception.h"

namespace retro::multimedia
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CAvi, CObject)

	CAvi::CAvi()
		: m_pAVIFile(NULL)
		, m_pAVIStream(NULL)
		, m_pGetFrame(NULL)
	{
		AVIFileInit();
	}

	CAvi::~CAvi()
	{
		Close();

		AVIFileExit();
	}

#pragma endregion
#pragma region Operations

	void CAvi::OpenFromFile(_In_z_ LPCTSTR pszFileName)
	{
		ASSERT(AfxIsValidString(pszFileName, MAX_PATH));

		Close();

		if (const HRESULT hr = AVIFileOpen(&m_pAVIFile, pszFileName, OF_READ, NULL); FAILED(hr))
		{
			throw new CWin32Exception(hr);
		}

		if (const HRESULT hr = AVIFileGetStream(m_pAVIFile, &m_pAVIStream, streamtypeVIDEO, 0l); FAILED(hr))
		{
			throw new CWin32Exception(hr);
		}

		if (m_pGetFrame = AVIStreamGetFrameOpen(m_pAVIStream, NULL); !m_pGetFrame)
		{
			throw new CWin32Exception(E_FAIL);
		}
	}

	void CAvi::Close()
	{
		if (m_pGetFrame)
		{
			AVIStreamGetFrameClose(m_pGetFrame);
			m_pGetFrame = NULL;
		}

		if (m_pAVIStream)
		{
			AVIStreamRelease(m_pAVIStream);
			m_pAVIStream = NULL;
		}

		if (m_pAVIFile)
		{
			AVIFileRelease(m_pAVIFile);
			m_pAVIFile = NULL;
		}
	}

	FLOAT CAvi::GetFrameRate() const
	{
		ASSERT_VALID(this);

		if (!m_pAVIFile)
		{
			return 0.f;
		}

		AVISTREAMINFO aviStreamInfo = { 0 };
		HRESULT hr = AVIStreamInfo(m_pAVIStream, &aviStreamInfo, sizeof(AVISTREAMINFO));
		if (FAILED(hr))
		{
			return 0.f;
		}

		return static_cast<FLOAT>(aviStreamInfo.dwRate) / aviStreamInfo.dwScale;
	}

	CTimeSpan CAvi::GetDuration() const
	{
		ASSERT_VALID(this);

		if (!m_pAVIStream)
		{
			return CTimeSpan();
		}

		const LONG nStreamLengthTime = AVIStreamLengthTime(m_pAVIStream);
		const INT nSeconds = static_cast<INT>(nStreamLengthTime / 1000);

		return CTimeSpan(0, 0, 0, nSeconds);
	}

	LONG CAvi::GetFrameCount() const
	{
		ASSERT_VALID(this);

		if (!m_pAVIStream)
		{
			return 0;
		}

		return AVIStreamLength(m_pAVIStream);
	}

	LONG CAvi::GetFirstFrameIndex() const
	{
		ASSERT_VALID(this);

		if (!m_pAVIStream)
		{
			return -1;
		}

		return AVIStreamStart(m_pAVIStream);
	}

	const LPBYTE CAvi::GetFrameBuffer(_In_ LONG nIndex) const
	{
		ASSERT_VALID(this);

		if (!m_pGetFrame)
		{
			return NULL;
		}

		return static_cast<const LPBYTE>(AVIStreamGetFrame(m_pGetFrame, nIndex));
	}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

	void CAvi::AssertValid() const
	{
		CObject::AssertValid();

		if (!m_pAVIFile)
		{
			ASSERT_NULL_OR_POINTER(m_pAVIStream, PAVISTREAM);
			ASSERT_NULL_OR_POINTER(m_pGetFrame, PGETFRAME);
		}		
	}

	void CAvi::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_pAVIFile = ") << m_pAVIFile << _T("\n");
		dc << _T("m_pAVIStream = ") << m_pAVIStream << _T("\n");
		dc << _T("m_pGetFrame = ") << m_pGetFrame << _T("\n");
	}

#endif

#pragma endregion

}
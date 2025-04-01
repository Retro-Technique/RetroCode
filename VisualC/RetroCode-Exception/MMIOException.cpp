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
#include "resource.h"

namespace retro::exception
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CMMIOException, CException)

	CMMIOException::CMMIOException(UINT mmResult)
		: m_mmResult(mmResult)
	{

	}

#pragma endregion
#pragma region Overridables

	_Success_(return != 0)
	BOOL CMMIOException::GetErrorMessage(
			_Out_writes_z_(nMaxError) LPTSTR lpszError,
			_In_ UINT nMaxError,
			_Out_opt_ PUINT pnHelpContext) const
	{
		ENSURE(AfxIsValidString(lpszError, nMaxError));

		if (pnHelpContext)
		{
			*pnHelpContext = 0;
		}

		_stprintf_s(lpszError, nMaxError, _T("MMIO - %s"), ErrorToString(m_mmResult).GetString());

		return TRUE;
	}

#ifdef _DEBUG

	void CMMIOException::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT(m_mmResult != MMSYSERR_NOERROR);
	}

	void CMMIOException::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_mmResult = ") << m_mmResult << _T("\n");
	}

#endif

#pragma endregion
#pragma region Implementations

	UINT CMMIOException::ErrorToIDS(INT nResult) const
	{
		static constexpr const UINT RESOURCE_IDS[] =
		{
			IDS_MMIOERR_FILENOTFOUND,
			IDS_MMIOERR_OUTOFMEMORY,
			IDS_MMIOERR_CANNOTOPEN,
			IDS_MMIOERR_CANNOTCLOSE,
			IDS_MMIOERR_CANNOTREAD,
			IDS_MMIOERR_CANNOTWRITE,
			IDS_MMIOERR_CANNOTSEEK,
			IDS_MMIOERR_CANNOTEXPAND,
			IDS_MMIOERR_CHUNKNOTFOUND,
			IDS_MMIOERR_UNBUFFERED,
			IDS_MMIOERR_PATHNOTFOUND,
			IDS_MMIOERR_ACCESSDENIED,
			IDS_MMIOERR_SHARINGVIOLATION,
			IDS_MMIOERR_NETWORKERROR,
			IDS_MMIOERR_TOOMANYOPENFILES,
			IDS_MMIOERR_INVALIDFILE
		};
		static constexpr const INT_PTR RESOURCE_IDS_COUNT = ARRAYSIZE(RESOURCE_IDS);

		C_ASSERT(RESOURCE_IDS_COUNT == (MMIOERR_INVALIDFILE - MMIOERR_BASE));

		ENSURE(nResult > MMIOERR_BASE);
		ENSURE(nResult <= MMIOERR_INVALIDFILE);

		const INT_PTR nIndex = nResult - MMIOERR_BASE - 1;

		ASSERT(nIndex >= 0);
		ASSERT(nIndex < RESOURCE_IDS_COUNT);

		return RESOURCE_IDS[nIndex];
	}

	CString CMMIOException::ErrorToString(UINT mmResult) const
	{
		CString strError;

		if (!strError.LoadString(ErrorToIDS(mmResult)))
		{
			return _T("<IDS NOT FOUND>");
		}

		return strError;
	}

#pragma endregion
}
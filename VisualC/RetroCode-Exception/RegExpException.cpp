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

	IMPLEMENT_DYNAMIC(CRegExpException, CException)

	CRegExpException::CRegExpException(INT nResult)
		: m_nResult(nResult)
	{

	}

#pragma endregion
#pragma region Overridables

	_Success_(return != 0)
		BOOL CRegExpException::GetErrorMessage(
			_Out_writes_z_(nMaxError) LPTSTR lpszError,
			_In_ UINT nMaxError,
			_Out_opt_ PUINT pnHelpCon_T) const
	{
		ENSURE(AfxIsValidString(lpszError, nMaxError));

		if (pnHelpCon_T)
		{
			*pnHelpCon_T = 0;
		}

		_stprintf_s(lpszError, nMaxError, _T("Regex - %s"), ErrorToString(m_nResult).GetString());

		return TRUE;
	}

#ifdef _DEBUG

	void CRegExpException::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT(m_nResult != REPARSE_ERROR_OK);
	}

	void CRegExpException::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_nResult = ") << m_nResult << _T("\n");
	}

#endif

#pragma endregion
#pragma region Implementations

	UINT CRegExpException::ErrorToIDS(INT nResult) const
	{
		static constexpr const UINT RESOURCE_IDS[] =
		{
			IDS_REPARSE_ERROR_OUTOFMEMORY,
			IDS_REPARSE_ERROR_BRACE_EXPECTED,
			IDS_REPARSE_ERROR_PAREN_EXPECTED,
			IDS_REPARSE_ERROR_BRACKET_EXPECTED,
			IDS_REPARSE_ERROR_UNEXPECTED,
			IDS_REPARSE_ERROR_EMPTY_RANGE,
			IDS_REPARSE_ERROR_INVALID_GROUP,
			IDS_REPARSE_ERROR_INVALID_RANGE,
			IDS_REPARSE_ERROR_EMPTY_REPEATOP,
			IDS_REPARSE_ERROR_INVALID_INPUT
		};
		static constexpr const INT_PTR RESOURCE_IDS_COUNT = ARRAYSIZE(RESOURCE_IDS);

		C_ASSERT(RESOURCE_IDS_COUNT == (REPARSE_ERROR_INVALID_INPUT - REPARSE_ERROR_OK));

		ENSURE(nResult > REPARSE_ERROR_OK);
		ENSURE(nResult <= REPARSE_ERROR_INVALID_INPUT);

		const INT_PTR nIndex = nResult - REPARSE_ERROR_OK - 1;

		ASSERT(nIndex >= 0);
		ASSERT(nIndex < RESOURCE_IDS_COUNT);

		return RESOURCE_IDS[nIndex];
	}

	CString CRegExpException::ErrorToString(INT nResult) const
	{
		CString strError;
		
		if (!strError.LoadString(ErrorToIDS(nResult)))
		{
			return _T("<IDS NOT FOUND>");
		}
		
		return strError;
	}

#pragma endregion

}
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

namespace retro::exception
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CWin32Exception, CException)

		CWin32Exception::CWin32Exception(HRESULT hr)
		: m_hr(hr)
	{

	}

	CWin32Exception::CWin32Exception(DWORD dwLastError)
		: m_hr(HRESULT_FROM_WIN32(dwLastError))
	{

	}

#pragma endregion
#pragma region Overridables

	_Success_(return != 0)
	BOOL CWin32Exception::GetErrorMessage(
			_Out_writes_z_(nMaxError) LPTSTR lpszError,
			_In_ UINT nMaxError,
			_Out_opt_ PUINT pnHelpContext) const
	{
		ENSURE(AfxIsValidString(lpszError, nMaxError));
		
		if (pnHelpContext)
		{
			*pnHelpContext = 0;
		}

		_stprintf_s(lpszError, nMaxError, _T("Win32 error: %s"), _com_error(m_hr).ErrorMessage());

		return TRUE;
	}

#ifdef _DEBUG

	void CWin32Exception::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT(FAILED(m_hr));
	}

	void CWin32Exception::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_hr = ") << m_hr << _T("\n");
	}

#endif

#pragma endregion
}
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

	IMPLEMENT_DYNAMIC(CReportException, CObject)

	CReportException::CReportException(CException* e, LPCTSTR pszMsg, LPCTSTR pszFile, INT nLine, BOOL bToDelete)
		: m_pException(e)
		, m_pszMsg(pszMsg)
		, m_pszFile(pszFile)
		, m_nLine(nLine)
		, m_bToDelete(bToDelete)
	{

	}

	CReportException::~CReportException()
	{
		if (m_bToDelete)
		{
			m_pException->Delete();
		}
	}

#pragma endregion
#pragma region Operations

	LPCTSTR CReportException::Report()
	{
		ASSERT_VALID(this);

		static constexpr const INT_PTR EXCEPTION_MAX_ERROR_LENGTH = 512;

		TCHAR m_szErrorMessage[EXCEPTION_MAX_ERROR_LENGTH]{ 0 };
		if (m_pException->GetErrorMessage(m_szErrorMessage, EXCEPTION_MAX_ERROR_LENGTH, 0))
		{
			m_strMessage.Format(_T("%Ts (%Ts:%d)\t%Ts"), m_pszMsg, m_pszFile, m_nLine, m_szErrorMessage);
		}
		else
		{
			m_strMessage.Format(_T("%Ts (%Ts:%d)"), m_pszMsg, m_pszFile, m_nLine);
		}

		return m_strMessage.GetString();
	}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

	void CReportException::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT_POINTER(m_pException, CException);
		m_pException->AssertValid();
		ASSERT(AfxIsValidString(m_pszMsg));
		ASSERT(AfxIsValidString(m_pszFile));
		ASSERT(m_nLine > 0);
		ASSERT(m_bToDelete == TRUE || m_bToDelete == FALSE);
	}

	void CReportException::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		if (m_pException)
		{
			m_pException->Dump(dc);
		}
		dc << _T("m_pszMsg = ") << m_pszMsg << _T("\n");
		dc << _T("m_pszFile = ") << m_pszFile << _T("\n");
		dc << _T("m_nLine = ") << m_nLine << _T("\n");
		dc << _T("m_bToDelete = ") << m_bToDelete << _T("\n");
	}

#endif

#pragma endregion

}
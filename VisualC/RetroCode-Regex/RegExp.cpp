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
#include "RegExpImpl.h"

namespace retro::regex
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CRegExp, CObject)

	CRegExp::CRegExp()
		: m_pImpl(new priv::CRegExpImpl)
	{
		
	}

	CRegExp::~CRegExp()
	{
		if (m_pImpl)
		{
			delete m_pImpl;
			m_pImpl = NULL;
		}
	}

#pragma endregion
#pragma region Operations

	void CRegExp::Compile(_In_z_ LPCTSTR pszPattern, _In_ BOOL bCaseSensitive) const
	{
		ENSURE_THROW(m_pImpl, AfxThrowMemoryException());

		m_pImpl->Compile(pszPattern, bCaseSensitive);
	}

	BOOL CRegExp::Match(_In_z_ LPCTSTR pszText, CStringList& listMatches) const
	{
		ENSURE_THROW(m_pImpl, AfxThrowMemoryException());

		return m_pImpl->Match(pszText, listMatches);
	}

	BOOL CRegExp::Match(_In_z_ LPCTSTR pszText, CStringArray& arrMatches) const
	{
		ENSURE_THROW(m_pImpl, AfxThrowMemoryException());

		return m_pImpl->Match(pszText, arrMatches);
	}

	BOOL CRegExp::Match(_In_z_ LPCTSTR pszText, MATCHENUMPROC pfnEnumProc, LPVOID pData) const
	{
		ENSURE_THROW(m_pImpl, AfxThrowMemoryException());

		return m_pImpl->Match(pszText, pfnEnumProc, pData);
	}

#pragma endregion
#pragma region Overridables

#ifdef _DEBUG

	void CRegExp::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT_POINTER(m_pImpl, priv::CRegExpImpl);
		ASSERT_VALID(m_pImpl);
	}

	void CRegExp::Dump(_Inout_ CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("m_pImpl = ") << m_pImpl;
	}

#endif

#pragma endregion

}
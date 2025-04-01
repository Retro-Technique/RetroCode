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

namespace retro::regex::priv
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CRegExpImpl, CObject)

	CRegExpImpl::CRegExpImpl()
	{

	}

#pragma endregion
#pragma region Operations

	void CRegExpImpl::Compile(_In_z_ LPCTSTR pszPattern, _In_ BOOL bCaseSensitive)
	{
		ENSURE(AfxIsValidString(pszPattern));

		const REParseError status = m_Regex.Parse(pszPattern, bCaseSensitive);
		ENSURE_REGEX(status);
	}

	BOOL CRegExpImpl::Match(_In_z_ LPCTSTR pszText, CStringList& listMatches)
	{
		return Match(pszText, [](LPCTSTR pszMatch, LPVOID pData) -> BOOL
			{
				CStringList* pList = reinterpret_cast<CStringList*>(pData);
				ASSERT_POINTER(pList, CStringList);
				ASSERT_VALID(pList);

				pList->AddTail(pszMatch);

				return TRUE;

			}, &listMatches);
	}

	BOOL CRegExpImpl::Match(_In_z_ LPCTSTR pszText, CStringArray& arrMatches)
	{
		return Match(pszText, [](LPCTSTR pszMatch, LPVOID pData) -> BOOL
			{
				CStringArray* pArray = reinterpret_cast<CStringArray*>(pData);
				ASSERT_POINTER(pArray, CStringArray);
				ASSERT_VALID(pArray);

				pArray->Add(pszMatch);

				return TRUE;

			}, &arrMatches);
	}

	BOOL CRegExpImpl::Match(_In_z_ LPCTSTR pszText, CRegExp::MATCHENUMPROC pfnEnumProc, LPVOID pData)
	{
		ENSURE(AfxIsValidString(pszText));
		ENSURE(pfnEnumProc);

		CAtlREMatchContext<> mc;
		LPCTSTR pszNext = pszText;
		BOOL bMatched = FALSE;

		while (m_Regex.Match(pszNext, &mc, &pszNext))
		{
			for (UINT i = 0; i < mc.m_uNumGroups; i++)
			{
				CAtlREMatchContext<>::MatchGroup mg{ 0 };
				mc.GetMatch(i, &mg);
				
				const CString strMatch(mg.szStart);
				const CString strLeft(strMatch.Left(mg.szEnd - mg.szStart));

				if (strLeft.IsEmpty())
				{
					continue;
				}

				bMatched = TRUE;

				if (!pfnEnumProc(strLeft.GetString(), pData))
				{
					break;
				}
			}
		}

		return bMatched;
	}

#pragma endregion

}
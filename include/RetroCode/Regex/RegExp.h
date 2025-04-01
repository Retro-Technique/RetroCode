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

#pragma once

#ifndef __RETRO_REGEX_H_INCLUDED__
#error Do not include RegExp.h directly, include the Regex.h file
#endif

namespace retro::regex
{

	namespace priv
	{
		class CRegExpImpl;
	}

	class AFX_EXT_CLASS CRegExp : public CObject
	{
#pragma region Constructors

		DECLARE_DYNAMIC(CRegExp)

	public:

		CRegExp();
		~CRegExp();

#pragma endregion
#pragma region Attributes

	private:

		priv::CRegExpImpl* m_pImpl;

#pragma endregion
#pragma region Operations

	public:

		typedef BOOL(* MATCHENUMPROC)(LPCTSTR, LPVOID);

		void Compile(_In_z_ LPCTSTR pszPattern, _In_ BOOL bCaseSensitive = TRUE) const;
		BOOL Match(_In_z_ LPCTSTR pszText, CStringList& listMatches) const;
		BOOL Match(_In_z_ LPCTSTR pszText, CStringArray& arrMatches) const;
		BOOL Match(_In_z_ LPCTSTR pszText, MATCHENUMPROC pfnEnumProc, LPVOID pData = NULL) const;

#pragma endregion
#pragma region Overridables

	public:

#ifdef _DEBUG
		void AssertValid() const override;
		void Dump(_Inout_ CDumpContext& dc) const override;
#endif

#pragma endregion
	};

}
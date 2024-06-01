/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2024 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist freestanding "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
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

namespace rc
{

	typedef void (ONTOKENIZEPROC)(lpcstr, lpvoid);

	class RETRO_CODE_API CString
	{
	public:

		static constexpr const auto INVALID_STR_POS = static_cast<uint32_t>(-1);
		static constexpr const char_t INVALID_CHAR = NULL;

	public:

		CString();
		CString(const CString& strCopy);
		explicit CString(lpcstr pszCopy);
		~CString();

	private:

		lpstr	m_pszBuffer;
		size_t	m_uLength;

	public:

		void SetAt(uint32_t uIndex, char_t cChar);
		const char_t& GetAt(uint32_t uIndex) const;
		uint32_t Find(lpcstr pszLookup) const;
		uint32_t Find(lpcstr pszToFind, uint32_t uOffset) const;
		uint32_t Find(char_t cLookup) const;
		uint32_t Find(char_t cToFind, uint32_t uOffset) const;
		uint32_t ReverseFind(char_t cToFind) const;
		CString& Append(lpcstr pszStr, size_t uLength);
		CString& Append(lpcstr pszStr);
		void Format(lpcstr pszFormat, ...);
		void FormatAdd(lpcstr pszFormat, ...);
		lpcstr Ptr() const;
		size_t GetLength() const;
		void Empty();
		boolean_t IsEmpty() const;
		void MakeUpper();
		void MakeLower();
		void MakeReverse();
		lpstr LockBuffer(size_t uLength);
		void UnlockBuffer(size_t uNewLength);
		size_t Remove(char_t cToRemove);
		size_t Delete(uint32_t uIndex, size_t uCount);
		size_t Replace(char_t cOld, char_t cNew);
		size_t Replace(lpcstr pszOld, lpcstr pszNew);
		void Split(lpcstr pszDelimiter, ONTOKENIZEPROC pfnOnTokenize, lpvoid pData = NULL);
		CString& operator=(lpcstr pszCopy);
		CString& operator=(const CString& strCopy);
		CString& operator+=(lpcstr pszSuffix);
		CString& operator+=(char_t cCharacter);
		CString& operator+=(const CString& strSuffix);
		CString operator+(const CString& strOther);
		CString operator+(lpcstr pszOther);
		boolean_t operator==(const CString& strOther);
		boolean_t operator==(lpcstr pszOther);
		boolean_t operator!=(const CString& strOther);
		boolean_t operator!=(lpcstr pszOther);

	private:

		void Alloc(size_t uLength);
		void SetLength(size_t uLength);
		void Free();

	};

	boolean_t operator<(const CString& strLeft, const CString& strRight);
	boolean_t operator>(const CString& strLeft, const CString& strRight);
	boolean_t operator<=(const CString& strLeft, const CString& strRight);
	boolean_t operator>=(const CString& strLeft, const CString& strRight);

}
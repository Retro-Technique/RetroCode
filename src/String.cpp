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

#include "../include/RetroCode.h"

namespace rc
{

	CString::CString()
		: m_pszBuffer(NULL)
		, m_uLength(0)
	{
		Alloc(0);
	}

	CString::CString(const CString& strCopy)
		: m_pszBuffer(NULL)
		, m_uLength(0)
	{
		const size_t uLength = strCopy.GetLength();
		Alloc(uLength);
		if (m_pszBuffer)
		{
			strncpy(m_pszBuffer, strCopy.Ptr(), uLength + 1);
		}
	}

	CString::CString(lpcstr pszCopy)
		: m_pszBuffer(NULL)
		, m_uLength(0)
	{
		const size_t uLength = strlen(pszCopy);
		Alloc(uLength);
		if (m_pszBuffer)
		{
			strncpy(m_pszBuffer, pszCopy, uLength + 1);
		}
	}

	CString::~CString()
	{
		Free();
	}

	void CString::SetAt(uint32_t uIndex, char_t cChar)
	{
		if (!m_pszBuffer || uIndex >= GetLength())
		{
			return;
		}

		m_pszBuffer[uIndex] = cChar;
	}

	const char_t& CString::GetAt(uint32_t uIndex) const
	{
		if (!m_pszBuffer || uIndex >= GetLength())
		{
			return INVALID_CHAR;
		}

		return m_pszBuffer[uIndex];
	}

	uint32_t CString::Find(lpcstr zLookup) const
	{
		return Find(zLookup, 0);
	}

	uint32_t CString::Find(lpcstr zToFind, uint32_t uOffset) const
	{
		const uint32_t uLength = GetLength();
		if (uOffset >= uLength)
		{
			return INVALID_STR_POS;
		}

		lpcstr pszRes = strstr(m_pszBuffer + uOffset, zToFind);

		return pszRes ? (pszRes - m_pszBuffer) : INVALID_STR_POS;
	}

	uint32_t CString::Find(char_t cLookup) const
	{
		return Find(cLookup, 0);
	}

	uint32_t CString::Find(char_t cToFind, uint32_t uOffset) const
	{
		const uint32_t uLength = GetLength();
		if (uOffset >= uLength)
		{
			return INVALID_STR_POS;
		}

		lpcstr pszRes = strchr(m_pszBuffer + uOffset, cToFind);

		return pszRes ? (pszRes - m_pszBuffer) : INVALID_STR_POS;
	}

	uint32_t CString::ReverseFind(char_t cToFind) const
	{
		lpcstr pszRes = strrchr(m_pszBuffer, cToFind);

		return pszRes ? (pszRes - m_pszBuffer) : INVALID_STR_POS;
	}

	CString& CString::Append(lpcstr pszStr, size_t uLength)
	{
		if (pszStr)
		{
			const size_t uOldLength = GetLength();
			const size_t uNewLength = uOldLength + uLength;

			Alloc(uNewLength);

			lpstr pszTail = m_pszBuffer + uOldLength;

			strncpy(pszTail, pszStr, uLength);
			SetLength(uNewLength);
		}

		return *this;
	}

	CString& CString::Append(lpcstr pszStr)
	{
		return Append(pszStr, strlen(pszStr));
	}

	void CString::Format(lpcstr pszFormat, ...)
	{
		if (!pszFormat)
		{
			return;
		}

		va_list arglist;
		va_start(arglist, pszFormat);

		const size_t uLength = vsnprintf(NULL, 0, pszFormat, arglist);

		Alloc(uLength);

		vsprintf(m_pszBuffer, pszFormat, arglist);

		va_end(arglist);

		SetLength(uLength);
	}

	void CString::FormatAdd(lpcstr pszFormat, ...)
	{
		if (!pszFormat)
		{
			return;
		}

		va_list arglist;
		va_start(arglist, pszFormat);

		const size_t uPreviousLength = GetLength();
		const size_t uNewLength = vsnprintf(NULL, 0, pszFormat, arglist);

		Alloc(uNewLength + uPreviousLength);

		vsprintf(m_pszBuffer + uPreviousLength, pszFormat, arglist);

		va_end(arglist);

		SetLength(uNewLength + uPreviousLength);
	}

	lpcstr CString::Ptr() const
	{
		return m_pszBuffer;
	}

	size_t CString::GetLength() const
	{
		return m_uLength;
	}

	void CString::Empty()
	{
		Alloc(0);
	}

	boolean_t CString::IsEmpty() const
	{
		return m_uLength == 0;
	}

	void CString::MakeUpper()
	{
		if (IsEmpty())
		{
			return;
		}

		for (size_t i = 0; i < m_uLength; i++)
		{
			m_pszBuffer[i] = static_cast<char_t>(toupper(m_pszBuffer[i]));
		}
	}

	void CString::MakeLower()
	{
		if (IsEmpty())
		{
			return;
		}

		for (size_t i = 0; i < m_uLength; i++)
		{
			m_pszBuffer[i] = static_cast<char_t>(tolower(m_pszBuffer[i]));
		}
	}

	void CString::MakeReverse()
	{
		if (IsEmpty())
		{
			return;
		}

		for (size_t i = 0; i < m_uLength / 2; i++)
		{
			char_t cTemp = m_pszBuffer[i];
			m_pszBuffer[i] = m_pszBuffer[m_uLength - i - 1];
			m_pszBuffer[m_uLength - i - 1] = cTemp;
		}
	}

	lpstr CString::LockBuffer(size_t uLength)
	{
		Alloc(uLength);

		return m_pszBuffer;
	}

	void CString::UnlockBuffer(size_t uNewLength)
	{
		assert(uNewLength <= m_uLength);

		SetLength(uNewLength);
	}

	size_t CString::Remove(char_t cToRemove)
	{
		size_t uCount = 0;

		for (size_t i = 0; i < m_uLength; i++)
		{
			if (m_pszBuffer[i] == cToRemove)
			{
				uCount++;
			}
			else if (uCount > 0)
			{
				m_pszBuffer[i - uCount] = m_pszBuffer[i];
			}
		}

		if (uCount > 0)
		{
			m_uLength -= uCount;
			m_pszBuffer[m_uLength] = '\0';
		}

		return uCount;
	}

	size_t CString::Delete(uint32_t uIndex, size_t uCount)
	{
		if (uCount == 0)
		{
			return 0;
		}

		if (uIndex >= m_uLength)
		{
			return 0;
		}

		if (uIndex + uCount > m_uLength)
		{
			uCount = m_uLength - uIndex;
		}

		memmove(m_pszBuffer + uIndex, m_pszBuffer + uIndex + uCount, m_uLength - uIndex - uCount);
		m_uLength -= uCount;
		m_pszBuffer[m_uLength] = '\0';

		return uCount;
	}

	size_t CString::Replace(char_t cOld, char_t cNew)
	{
		uint32_t uCount = 0;

		for (size_t i = 0; i < m_uLength; i++)
		{
			if (m_pszBuffer[i] == cOld)
			{
				m_pszBuffer[i] = cNew;
				uCount++;
			}
		}
		return uCount;
	}

	size_t CString::Replace(lpcstr pszOld, lpcstr pszNew)
	{
		if (!pszOld)
		{
			return 0;
		}

		if (!pszNew)
		{
			return 0;
		}

		const size_t uOldLength = strlen(pszOld);
		if (uOldLength == 0)
		{
			return 0;
		}

		const size_t uNewLength = strlen(pszNew);

		size_t uCount = 0;
		for (size_t i = 0; i <= m_uLength - uOldLength; i++)
		{
			if (strncmp(m_pszBuffer + i, pszOld, uOldLength) == 0)
			{
				memmove(m_pszBuffer + i + uNewLength, m_pszBuffer + i + uOldLength, m_uLength - i - uOldLength);
				memcpy(m_pszBuffer + i, pszNew, uNewLength);
				m_uLength += uNewLength - uOldLength;
				i += uNewLength - 1;
				uCount++;
			}
		}

		m_pszBuffer[m_uLength] = '\0';

		return uCount;
	}

	void CString::Split(lpcstr pszDelimiter, ONTOKENIZEPROC pfnOnTokenize, lpvoid pData)
	{
		if (!pszDelimiter)
		{
			return;
		}

		if (!pfnOnTokenize)
		{
			return;
		}

		CString strCopy(m_pszBuffer);

		char_t* pszToken = strtok(strCopy.m_pszBuffer, pszDelimiter);
		while (pszToken)
		{
			pfnOnTokenize(pszToken, pData);
			pszToken = strtok(NULL, pszDelimiter);
		}
	}

	void CString::Alloc(size_t uLength)
	{
		lpstr pszTemp = m_pszBuffer;
		const size_t uRealLength = uLength + 1;

		do
		{
			if (m_pszBuffer) /* if already allocated */
			{
				if (uLength <= m_uLength) /* but enough space */
				{
					break;
				}
				else /* but not enough space */
				{
					pszTemp = (lpstr)realloc(m_pszBuffer, uRealLength * sizeof(char_t));
					break;
				}
			}

			if (!m_pszBuffer) /* if not yet allocated */
			{
				pszTemp = (lpstr)malloc(uRealLength * sizeof(char_t));
				break;
			}

		} while (RETRO_NULL_WHILE_LOOP_CONDITION);

		if (!pszTemp)
		{
			return;
		}

		m_pszBuffer = pszTemp;
		SetLength(uLength);
	}

	void CString::SetLength(size_t uLength)
	{
		if (m_pszBuffer)
		{
			m_pszBuffer[uLength] = '\0';
			m_uLength = uLength;
		}
	}

	void CString::Free()
	{
		if (m_pszBuffer)
		{
			free(m_pszBuffer);
			m_pszBuffer = NULL;
		}

		m_uLength = 0;
	}

	CString& CString::operator=(lpcstr pszCopy)
	{
		const size_t uLength = strlen(pszCopy);
		Alloc(uLength);
		if (m_pszBuffer)
		{
			strncpy(m_pszBuffer, pszCopy, uLength + 1);
		}

		return *this;
	}

	CString& CString::operator=(const CString& strCopy)
	{
		const size_t uLength = strCopy.GetLength();
		Alloc(uLength);
		if (m_pszBuffer)
		{
			strncpy(m_pszBuffer, strCopy.Ptr(), uLength + 1);
		}

		return *this;
	}

	CString& CString::operator+=(lpcstr suffix)
	{
		return Append(suffix, strlen(suffix));
	}

	CString& CString::operator+=(char_t cCharacter)
	{
		return Append(&cCharacter, 1);
	}

	CString& CString::operator+=(const CString& suffix)
	{
		return Append(suffix.Ptr(), suffix.GetLength());
	}

	CString CString::operator+(const CString& pszOther)
	{
		CString strTmp;

		strTmp.Alloc(GetLength() + pszOther.GetLength());
		strTmp += *this;
		strTmp += pszOther;

		return strTmp;
	}

	CString CString::operator+(lpcstr pszOther)
	{
		CString strTmp;
		const size_t uOtherLength = strlen(pszOther);

		strTmp.Alloc(GetLength() + uOtherLength);
		strTmp += *this;
		strTmp.Append(pszOther, uOtherLength);

		return strTmp;
	}

	boolean_t CString::operator==(const CString& strOther)
	{
		return (GetLength() == strOther.GetLength()) && (strcmp(Ptr(), strOther.Ptr()) == 0);
	}

	boolean_t CString::operator==(lpcstr strOther)
	{
		return strcmp(Ptr(), strOther) == 0;
	}

	boolean_t CString::operator!=(const CString& strOther)
	{
		return !(*this == strOther);
	}

	boolean_t CString::operator!=(lpcstr strOther)
	{
		return !(*this == strOther);
	}

	boolean_t operator<(const CString& strLeft, const CString& strRight)
	{
		return strcmp(strLeft.Ptr(), strRight.Ptr()) < 0;
	}

	boolean_t operator>(const CString& strLeft, const CString& strRight)
	{
		return strRight < strLeft;
	}

	boolean_t operator<=(const CString& strLeft, const CString& strRight)
	{
		return !(strRight < strLeft);
	}

	boolean_t operator>=(const CString& strLeft, const CString& strRight)
	{
		return !(strLeft < strRight);
	}

}
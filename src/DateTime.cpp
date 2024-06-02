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
	constexpr auto MAX_FORMAT_DATE_SIZE = 128;

	CDateTime::CDateTime()
		: m_nTimestamp(INVALID_TIMESTAMP)
	{
		
	}

	CDateTime::CDateTime(time_t nTimestamp)
		: m_nTimestamp(nTimestamp)
	{

	}

	CDateTime::~CDateTime()
	{
		
	}

	time_t CDateTime::GetTimestamp() const
	{
		return m_nTimestamp;
	}

	void CDateTime::FromDesc(const tm& Details)
	{
		tm TM;

		memcpy(&TM, &Details, sizeof(tm));

		const time_t nTimestamp = mktime(&TM);

		m_nTimestamp = nTimestamp;
	}

	void CDateTime::ToDesc(tm& Details) const
	{
		if (!IsValid())
		{
			return;
		}

		const tm* pTM = localtime(&m_nTimestamp);
		if (!pTM)
		{
			return;
		}

		memcpy(&Details, pTM, sizeof(tm));
	}

	boolean_t CDateTime::IsValid() const
	{
		return m_nTimestamp != INVALID_TIMESTAMP;
	}

	void CDateTime::Format(lpcstr pszFormat, CString& strResult) const
	{
		static constexpr lpcstr TOO_BIG = "<TOO BIG>";

		if (!IsValid())
		{
			return;
		}

		const tm* pTM = localtime(&m_nTimestamp);
		if (!pTM)
		{
			return;
		}

		lpstr zBuffer = strResult.LockBuffer(MAX_FORMAT_DATE_SIZE);

		const size_t uBuffLen = strftime(zBuffer, MAX_FORMAT_DATE_SIZE, pszFormat, pTM);

		strResult.UnlockBuffer(uBuffLen);

		if (0 == uBuffLen)
		{
			strResult = TOO_BIG;
		}
	}

	boolean_t CDateTime::operator==(const CDateTime& dtOther) const 
	{ 
		return m_nTimestamp == dtOther.m_nTimestamp;
	}

	boolean_t CDateTime::operator!=(const CDateTime& dtOther) const
	{ 
		return m_nTimestamp != dtOther.m_nTimestamp;
	}

	boolean_t CDateTime::operator<(const CDateTime& dtOther) const 
	{ 
		return m_nTimestamp < dtOther.m_nTimestamp;
	}

	boolean_t CDateTime::operator>(const CDateTime& dtOther) const 
	{ 
		return m_nTimestamp > dtOther.m_nTimestamp;
	}

	boolean_t CDateTime::operator<=(const CDateTime& dtOther) const 
	{ 
		return m_nTimestamp <= dtOther.m_nTimestamp;
	}

	boolean_t CDateTime::operator>=(const CDateTime& dtOther) const 
	{ 
		return m_nTimestamp >= dtOther.m_nTimestamp;
	}

	CDateTime CDateTime::operator+(const CDuration& durTime) const
	{
		return CDateTime(m_nTimestamp + durTime.AsSeconds());
	}

	CDateTime CDateTime::operator-(const CDuration& durTime) const
	{
		return CDateTime(m_nTimestamp - durTime.AsSeconds());
	}

	CDateTime CDateTime::operator+=(const CDuration& durTime)
	{
		m_nTimestamp += durTime.AsSeconds();
		return *this;
	}

	CDateTime CDateTime::operator-=(const CDuration& durTime)
	{
		m_nTimestamp -= durTime.AsSeconds();
		return *this;
	}

	CDuration CDateTime::operator-(const CDateTime& dtOther) const
	{
		return seconds(m_nTimestamp - dtOther.m_nTimestamp);
	}

	CDateTime CDateTime::GetCurrentDateTime()
	{
		const time_t nTimestamp = time(NULL);

		return CDateTime(nTimestamp);
	}

}
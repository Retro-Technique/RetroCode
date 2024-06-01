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

	constexpr auto _7_DAYS_A_WEEK = 7;
	constexpr auto _24_HOURS_A_DAY = 24;
	constexpr auto _60_MINUTES_AN_HOUR = 60;
	constexpr auto _60_SECONDS_A_MINUTE = 60;

	constexpr auto TICK_COUNT_IN_A_SECOND = 1;
	constexpr auto TICK_COUNT_IN_A_MINUTE = TICK_COUNT_IN_A_SECOND * _60_SECONDS_A_MINUTE;
	constexpr auto TICK_COUNT_IN_AN_HOUR = TICK_COUNT_IN_A_MINUTE * _60_MINUTES_AN_HOUR;
	constexpr auto TICK_COUNT_IN_A_DAY = TICK_COUNT_IN_AN_HOUR * _24_HOURS_A_DAY;
	constexpr auto TICK_COUNT_IN_A_WEEK = TICK_COUNT_IN_A_DAY * _7_DAYS_A_WEEK;

	CDuration::CDuration()
		: m_nSeconds(0)
	{

	}

	CDuration::CDuration(time_t nMilliseconds)
		: m_nSeconds(nMilliseconds)
	{

	}

	CDuration::~CDuration()
	{

	}

	float32_t CDuration::AsWeeks() const
	{
		return AsDays() / _7_DAYS_A_WEEK;
	}

	float32_t CDuration::AsDays() const
	{
		return AsHours() / _24_HOURS_A_DAY;
	}

	float32_t CDuration::AsHours() const
	{
		return AsMinutes() / _60_MINUTES_AN_HOUR;
	}

	float32_t CDuration::AsMinutes() const
	{
		return static_cast<float32_t>(AsSeconds()) / _60_SECONDS_A_MINUTE;
	}

	time_t CDuration::AsSeconds() const
	{
		return m_nSeconds;
	}

	boolean_t CDuration::IsPositive() const
	{
		return m_nSeconds > 0;
	}

	boolean_t CDuration::IsNegative() const
	{
		return m_nSeconds < 0;
	}

	boolean_t CDuration::IsNull() const
	{
		return m_nSeconds == 0;
	}

	void CDuration::FromString(lpcstr pszValue)
	{
		if (!pszValue)
		{
			return;
		}

		time_t nSeconds = 0;
		int32_t i = 0;
		boolean_t bHasDigit = false;

		while (pszValue[i] >= '0' && pszValue[i] <= '9')
		{
			bHasDigit = true;
			nSeconds = nSeconds * 10 + (pszValue[i] - '0');
			++i;
		}

		if (!bHasDigit)
		{
			return;
		}

		uint64_t uMultiplier = 0;

		if (pszValue[i] == '\0')
		{
			uMultiplier = TICK_COUNT_IN_A_SECOND;
		}
		else if (pszValue[i] == 's' &&
			(pszValue[i + 1] == '\0' ||
				(pszValue[i + 1] == 'e' && pszValue[i + 2] == 'c' && pszValue[i + 3] == '\0')))
		{
			uMultiplier = TICK_COUNT_IN_A_SECOND;
		}
		else if (pszValue[i] == 'm' && pszValue[i + 1] == 'i' && pszValue[i + 2] == 'n' && pszValue[i + 3] == '\0')
		{
			uMultiplier = TICK_COUNT_IN_A_MINUTE;
		}
		else if (pszValue[i] == 'h' && pszValue[i + 1] == '\0')
		{
			uMultiplier = TICK_COUNT_IN_AN_HOUR;
		}
		else if (pszValue[i] == 'd' && pszValue[i + 1] == '\0')
		{
			uMultiplier = TICK_COUNT_IN_A_DAY;
		}
		else if ((pszValue[i] == 'w' && pszValue[i + 1] == '\0') ||
			(pszValue[i] == 's' && pszValue[i + 1] == 'e' && pszValue[i + 2] == 'm' && pszValue[i + 3] == '\0'))
		{
			uMultiplier = TICK_COUNT_IN_A_WEEK;
		}
		else
		{
			return;
		}

		nSeconds = nSeconds * uMultiplier;
		m_nSeconds = nSeconds;
	}

	void CDuration::Null()
	{
		m_nSeconds = 0;
	}

	CDuration weeks(float32_t fAmount)
	{
		return days(fAmount * _7_DAYS_A_WEEK);
	}

	CDuration days(float32_t fAmount)
	{
		return hours(fAmount * _24_HOURS_A_DAY);
	}

	CDuration hours(float32_t fAmount)
	{
		return minutes(fAmount * _60_MINUTES_AN_HOUR);
	}

	CDuration minutes(float32_t fAmount)
	{
		return seconds(static_cast<time_t>(fAmount * _60_SECONDS_A_MINUTE));
	}

	CDuration seconds(time_t nAmount)
	{
		return CDuration(nAmount);
	}

	boolean_t operator ==(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() == Right.AsSeconds();
	}

	boolean_t operator !=(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() != Right.AsSeconds();
	}

	boolean_t operator <(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() < Right.AsSeconds();
	}

	boolean_t operator >(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() > Right.AsSeconds();
	}
	boolean_t operator <=(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() <= Right.AsSeconds();
	}

	boolean_t operator >=(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() >= Right.AsSeconds();
	}

	CDuration operator +(CDuration Left, CDuration Right)
	{
		return seconds(Left.AsSeconds() + Right.AsSeconds());
	}

	CDuration& operator +=(CDuration& Left, CDuration Right)
	{
		return Left = Left + Right;
	}

	CDuration operator -(CDuration Left, CDuration Right)
	{
		return seconds(Left.AsSeconds() - Right.AsSeconds());
	}

	CDuration& operator -=(CDuration& Left, CDuration Right)
	{
		return Left = Left - Right;
	}

	CDuration operator *(CDuration Left, time_t nRight)
	{
		return seconds(Left.AsSeconds() * nRight);
	}

	CDuration operator *(time_t nLeft, CDuration Right)
	{
		return Right * nLeft;
	}

	CDuration& operator *=(CDuration& Left, time_t nRight)
	{
		return Left = Left * nRight;
	}

	CDuration operator /(CDuration Left, time_t nRight)
	{
		return seconds(Left.AsSeconds() / nRight);
	}

	CDuration& operator /=(CDuration& Left, time_t nRight)
	{
		return Left = Left / nRight;
	}

	time_t operator /(CDuration Left, CDuration Right)
	{
		return Left.AsSeconds() / Right.AsSeconds();
	}

	CDuration operator %(CDuration Left, CDuration Right)
	{
		return seconds(Left.AsSeconds() % Right.AsSeconds());
	}

	CDuration& operator %=(CDuration& Left, CDuration Right)
	{
		return Left = Left % Right;
	}

}
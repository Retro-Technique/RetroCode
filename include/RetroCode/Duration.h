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

#pragma once

namespace rc
{

	class RETRO_CODE_API CDuration
	{
	public:

		CDuration();
		~CDuration();

	private:

		explicit CDuration(time_t nSeconds);

	private:

		time_t m_nSeconds;

	public:

		float32_t AsWeeks() const;
		float32_t AsDays() const;
		float32_t AsHours() const;
		float32_t AsMinutes() const;
		time_t AsSeconds() const;
		boolean_t IsPositive() const;
		boolean_t IsNegative() const;
		boolean_t IsNull() const;
		void FromString(lpcstr pszValue);
		void Null();

	private:

		friend CDuration RETRO_CODE_API weeks(float32_t);
		friend CDuration RETRO_CODE_API days(float32_t);
		friend CDuration RETRO_CODE_API hours(float32_t);
		friend CDuration RETRO_CODE_API minutes(float32_t);
		friend CDuration RETRO_CODE_API seconds(time_t);

	};

	CDuration RETRO_CODE_API weeks(float32_t fAmount);
	CDuration RETRO_CODE_API days(float32_t fAmount);
	CDuration RETRO_CODE_API hours(float32_t fAmount);
	CDuration RETRO_CODE_API minutes(float32_t fAmount);
	CDuration RETRO_CODE_API seconds(time_t nAmount);

	RETRO_CODE_API boolean_t operator ==(CDuration Left, CDuration Right);
	RETRO_CODE_API boolean_t operator !=(CDuration Left, CDuration Right);
	RETRO_CODE_API boolean_t operator <(CDuration Left, CDuration Right);
	RETRO_CODE_API boolean_t operator >(CDuration Left, CDuration Right);
	RETRO_CODE_API boolean_t operator <=(CDuration Left, CDuration Right);
	RETRO_CODE_API boolean_t operator >=(CDuration Left, CDuration Right);
	RETRO_CODE_API CDuration operator +(CDuration Left, CDuration Right);
	RETRO_CODE_API CDuration& operator +=(CDuration& Left, CDuration Right);
	RETRO_CODE_API CDuration operator -(CDuration Left, CDuration Right);
	RETRO_CODE_API CDuration& operator -=(CDuration& Left, CDuration Right);
	RETRO_CODE_API CDuration operator *(CDuration Left, time_t nRight);
	RETRO_CODE_API CDuration operator *(time_t nLeft, CDuration Right);
	RETRO_CODE_API CDuration& operator *=(CDuration& Left, time_t nRight);
	RETRO_CODE_API CDuration operator /(CDuration Left, time_t nRight);
	RETRO_CODE_API CDuration& operator /=(CDuration& Left, time_t nRight);
	RETRO_CODE_API time_t operator /(CDuration Left, CDuration Right);
	RETRO_CODE_API CDuration operator %(CDuration Left, CDuration Right);
	RETRO_CODE_API CDuration& operator %=(CDuration& Left, CDuration Right);

}
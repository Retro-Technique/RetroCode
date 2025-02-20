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

#ifndef __RETRO_MATH_H_INCLUDED__
#error Do not include Collide.h directly, include the Math.h file
#endif

#pragma once

namespace retro::math
{

	template<typename T>
	BOOL IsCollidePointPoint(const CVector2<T> vLeft, const CVector2<T> vRight);

	template<typename T>
	BOOL IsCollidePointLine(const CVector2<T> vLeft, const CLine<T> lnRight);

	template<typename T>
	BOOL IsCollidePointRect(const CVector2<T> vLeft, const CRect<T> rcRight);

	template<typename T>
	BOOL IsCollidePointCircle(const CVector2<T> vLeft, const CCircle<T> circRight);

	template<typename T>
	BOOL IsCollideLineLine(const CLine<T> lnLeft, const CLine<T> lnRight);

	template<typename T>
	BOOL IsCollideLineRect(const CLine<T> lnLeft, const CRect<T> rcRight);

	template<typename T>
	BOOL IsCollideLineCircle(const CLine<T> lnLeft, const CCircle<T> circRight);

	template<typename T>
	BOOL IsCollideRectRect(const CRect<T> rcLeft, const CRect<T> rcRight);

	template<typename T>
	BOOL IsCollideRectCircle(const CRect<T> rcLeft, const CCircle<T> circRight);

	template<typename T>
	BOOL IsCollideCircleCircle(const CCircle<T> circLeft, const CCircle<T> circRight);

}

#include "Collide.inl"
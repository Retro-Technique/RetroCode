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

namespace retro::math
{

	template<typename T>
	T EuclidianDistance(const CVector2<T>& vStart, const CVector2<T>& vEnd)
	{
		return EuclidianDistance(vStart.X, vStart.Y, vEnd.X, vEnd.Y);
	}

	template<typename T>
	T EuclidianDistance(T x1, T y1, T x2, T y2)
	{
		return EuclidianDistance(static_cast<DOUBLE>(x1), static_cast<DOUBLE>(y1), static_cast<DOUBLE>(x2), static_cast<DOUBLE>(y2));
	}

	template<>
	inline FLOAT EuclidianDistance(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2)
	{
		return sqrtf(powf((x1 - x2), 2.f) + powf((y1 - y2), 2.f));
	}

	template<>
	inline DOUBLE EuclidianDistance(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2)
	{
		return sqrt(pow((x1 - x2), 2.) + pow((y1 - y2), 2.));
	}

	template<typename T>
	T ManhattanDistance(const CVector2<T>& vStart, const CVector2<T>& vEnd)
	{
		return ManhattanDistance(vStart.X, vStart.Y, vEnd.X, vEnd.Y);
	}

	template<typename T>
	T ManhattanDistance(T x1, T y1, T x2, T y2)
	{
		return ManhattanDistance(static_cast<DOUBLE>(x1), static_cast<DOUBLE>(y1), static_cast<DOUBLE>(x2), static_cast<DOUBLE>(y2));
	}

	template<>
	inline FLOAT ManhattanDistance(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2)
	{
		return fabsf(x1 - x2) + fabsf(y1 - y2);
	}

	template<>
	inline DOUBLE ManhattanDistance(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2)
	{
		return fabs(x1 - x2) + fabs(y1 - y2);
	}

	template<>
	inline INT ManhattanDistance(INT x1, INT y1, INT x2, INT y2)
	{
		return abs(x1 - x2) + abs(y1 - y2);
	}

	template<>
	inline LONG ManhattanDistance(LONG x1, LONG y1, LONG x2, LONG y2)
	{
		return labs(x1 - x2) + labs(y1 - y2);
	}

	template<>
	inline LONGLONG ManhattanDistance(LONGLONG x1, LONGLONG y1, LONGLONG x2, LONGLONG y2)
	{
		return llabs(x1 - x2) + llabs(y1 - y2);
	}

}
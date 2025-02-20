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
	BOOL IsCollidePointPoint(const CVector2<T> vLeft, const CVector2<T> vRight)
	{
		return vLeft == vRight;
	}

	template<typename T>
	BOOL IsCollidePointLine(const CVector2<T> vLeft, const CLine<T> lnRight)
	{
		const T d1 = EuclidianDistance(lnRight.Start, vLeft);
		const T d2 = EuclidianDistance(lnRight.End, vLeft);
		const T nLineLength = EuclidianDistance(lnRight.Start, lnRight.End);

		return d1 + d2 == nLineLength;
	}

	template<typename T>
	BOOL IsCollidePointRect(const CVector2<T> vLeft, const CRect<T> rcRight)
	{
		return(vLeft.X >= rcRight.Point.X) &&
			(vLeft.X <= rcRight.Point.X + rcRight.Size.X) &&
			(vLeft.Y >= rcRight.Point.Y) &&
			(vLeft.Y <= rcRight.Point.Y + rcRight.Size.Y);
	}

	template<typename T>
	BOOL IsCollidePointCircle(const CVector2<T> vLeft, const CCircle<T> circRight)
	{
		const T dx = vLeft.X - circRight.Center.X;
		const T dy = vLeft.Y - circRight.Center.Y;

		return (dx * dx + dy * dy) <= (circRight.Radius * circRight.Radius);
	}

	template<typename T>
	BOOL IsCollideLineLine(const CLine<T> lnLeft, const CLine<T> lnRight)
	{
		const T nDeterminant = (lnLeft.End.X - lnLeft.Start.X) * (lnRight.End.Y - lnRight.Start.Y) -
			(lnLeft.End.Y - lnLeft.Start.Y) * (lnRight.End.X - lnRight.Start.X);
		if (nDeterminant == 0)
		{
			return FALSE;
		}

		const T t = ((lnRight.Start.X - lnLeft.Start.X) * (lnRight.End.Y - lnRight.Start.Y) -
			(lnRight.Start.Y - lnLeft.Start.Y) * (lnRight.End.X - lnRight.Start.X)) / nDeterminant;
		const T u = ((lnRight.Start.X - lnLeft.Start.X) * (lnLeft.End.Y - lnLeft.Start.Y) -
			(lnRight.Start.Y - lnLeft.Start.Y) * (lnLeft.End.X - lnLeft.Start.X)) / nDeterminant;

		return (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
	}

	template<typename T>
	BOOL IsCollideLineRect(const CLine<T> lnLeft, const CRect<T> rcRight)
	{
		if (IsCollidePointRect(lnLeft.Start, rcRight) || IsCollidePointRect(lnLeft.End, rcRight))
		{
			return TRUE;
		}

		const CLine<T> Borders[] =
		{
			{rcRight.Point, {rcRight.Point.X + rcRight.Size.X, rcRight.Point.Y}},
			{{rcRight.Point.X + rcRight.Size.X, rcRight.Point.Y}, {rcRight.Point.X + rcRight.Size.X, rcRight.Point.Y + rcRight.Size.Y}},
			{{rcRight.Point.X + rcRight.Size.X, rcRight.Point.Y + rcRight.Size.Y}, {rcRight.Point.X, rcRight.Point.Y + rcRight.Size.Y}},
			{rcRight.Point, {rcRight.Point.X, rcRight.Point.Y + rcRight.Size.Y}}
		};
		static constexpr const INT_PTR BORDER_COUNT = sizeof(Borders) / sizeof(Borders[0]);

		for (INT_PTR i = 0; i < BORDER_COUNT; i++)
		{
			if (IsCollideLineLine(lnLeft, Borders[i]))
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	template<typename T>
	BOOL IsCollideLineCircle(const CLine<T> lnLeft, const CCircle<T> circRight)
	{
		if (IsCollidePointCircle(lnLeft.Start, circRight) || IsCollidePointCircle(lnLeft.End, circRight))
		{
			return TRUE;
		}

		const T dx = lnLeft.End.X - lnLeft.Start.X;
		const T dy = lnLeft.End.Y - lnLeft.Start.Y;
		const T a = dy;
		const T b = -dx;
		const T c = dx * lnLeft.Start.Y - dy * lnLeft.Start.X;
		const T dist = abs(a * circRight.Center.X + b * circRight.Center.Y + c) / sqrt(a * a + b * b);

		return dist <= circRight.Radius;
	}

	template<typename T>
	BOOL IsCollideRectRect(const CRect<T> rcLeft, const CRect<T> rcRight)
	{
		return IsCollidePointRect(rcLeft.Point, rcRight) ||
			IsCollidePointRect({ static_cast<T>(rcLeft.Point.X + rcLeft.Size.X), rcLeft.Point.Y }, rcRight) ||
			IsCollidePointRect({ rcLeft.Point.X, static_cast<T>(rcLeft.Point.Y + rcLeft.Size.Y) }, rcRight) ||
			IsCollidePointRect({ static_cast<T>(rcLeft.Point.X + rcLeft.Size.X), static_cast<T>(rcLeft.Point.Y + rcLeft.Size.Y) }, rcRight);
	}

	template<typename T>
	BOOL IsCollideRectCircle(const CRect<T> rcLeft, const CCircle<T> circRight)
	{
		const T nClosestX = Max(rcLeft.Point.X, Min(circRight.Center.X, rcLeft.Point.X + rcLeft.Size.X));
		const T nClosestY = Max(rcLeft.Point.Y, Min(circRight.Center.Y, rcLeft.Point.Y + rcLeft.Size.Y));

		const T dx = nClosestX - circRight.Center.X;
		const T dy = nClosestY - circRight.Center.Y;

		return (dx * dx + dy * dy) <= (circRight.Radius * circRight.Radius);
	}

	template<typename T>
	BOOL IsCollideCircleCircle(const CCircle<T> circLeft, const CCircle<T> circRight)
	{
		const T fDistance = EuclidianDistance(circLeft.Center, circRight.Center);

		return fDistance < (circLeft.Radius + circRight.Radius);
	}

}
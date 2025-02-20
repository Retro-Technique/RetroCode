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

#pragma region Constructors

	template<typename T>
	CCircle<T>::CCircle()
		: Center{ 0, 0 }
		, Radius(0)
	{

	}

	template<typename T>
	CCircle<T>::CCircle(T CenterX, T CenterY, T Radius)
		: Center{ CenterX, CenterY }
		, Radius(Radius)
	{

	}

	template<typename T>
	CCircle<T>::CCircle(const CVector2<T>& Center, T Radius)
		: Center(Center)
		, Radius(Radius)
	{

	}

	template<typename T>
	template<typename U>
	CCircle<T>::CCircle(const CCircle<U>& Circle)
		: Center{ static_cast<T>(Circle.Center.X), static_cast<T>(Circle.Center.Y) }
		, Radius{ static_cast<T>(Circle.Radius) }
	{

	}

#pragma endregion
#pragma region Overridables

	template<typename T>
	void CCircle<T>::Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		if (ar.IsStoring())
		{
			ar << Center << Radius;
		}
		else
		{
			ar >> Center >> Radius;
		}
	}

#ifdef _DEBUG

	template<typename T>
	void CCircle<T>::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("Center: ") << Center << _T("\n");
		dc << _T("Radius: ") << Radius << _T("\n");
	}

#endif

	template<typename T>
	BOOL operator==(const CCircle<T>& Left, const CCircle<T>& Right)
	{
		return (Left.Center.X == Right.Center.X) && (Left.Center.Y == Right.Center.Y) && (Left.Radius == Right.Radius);
	}

	template<typename T>
	BOOL operator!=(const CCircle<T>& Left, const CCircle<T>& Right)
	{
		return !(Left == Right);
	}

#pragma endregion

}
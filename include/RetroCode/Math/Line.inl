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
	CLine<T>::CLine()
		: Start{ 0, 0 }
		, End{ 0, 0 }
	{

	}

	template<typename T>
	CLine<T>::CLine(T startx, T starty, T endx, T endy)
		: Start{ startx, starty }
		, End{ endx, endy }
	{

	}

	template<typename T>
	CLine<T>::CLine(const CVector2<T>& Start, const CVector2<T>& End)
		: Start(Start)
		, End(End)
	{

	}

	template<typename T>
	template<typename U>
	CLine<T>::CLine(const CLine<U>& Line)
		: Start{ static_cast<T>(Line.Start.X), static_cast<T>(Line.Start.Y) }
		, End{ static_cast<T>(Line.End.X), static_cast<T>(Line.End.Y) }
	{

	}

#pragma endregion
#pragma region Overridables

	template<typename T>
	void CLine<T>::Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		if (ar.IsStoring())
		{
			ar << Start << End;
		}
		else
		{
			ar >> Start >> End;
		}
	}

#ifdef _DEBUG

	template<typename T>
	void CLine<T>::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << _T("Start: ") << Start << _T("\n");
		dc << _T("End: ") << End << _T("\n");
	}

#endif

	template<typename T>
	BOOL operator==(const CLine<T>& Left, const CLine<T>& Right)
	{
		return (Left.Start.X == Right.Start.X) && (Left.Start.Y == Right.Start.Y) && (Left.End.X == Right.End.X) && (Left.End.Y == Right.End.Y);
	}

	template<typename T>
	BOOL operator!=(const CLine<T>& Left, const CLine<T>& Right)
	{
		return !(Left == Right);
	}

#pragma endregion

}
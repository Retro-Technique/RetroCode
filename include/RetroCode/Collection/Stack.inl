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

namespace retro::coll
{

#pragma region Operations

	template<typename TYPE, typename ARG_TYPE>
	INT_PTR CStack<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
	{
		return m_arrBuffer.Add(newElement);
	}

	template<typename TYPE, typename ARG_TYPE>
	void CStack<TYPE, ARG_TYPE>::Pop()
	{
		if (IsEmpty())
		{
			return;
		}

		m_arrBuffer.RemoveAt(m_arrBuffer.GetUpperBound());
	}

	template<typename TYPE, typename ARG_TYPE>
	const TYPE& CStack<TYPE, ARG_TYPE>::Top() const
	{
		return m_arrBuffer.GetAt(m_arrBuffer.GetUpperBound());
	}

	template<typename TYPE, typename ARG_TYPE>
	TYPE& CStack<TYPE, ARG_TYPE>::Top()
	{
		return m_arrBuffer.GetAt(m_arrBuffer.GetUpperBound());
	}

	template<typename TYPE, typename ARG_TYPE>
	void CStack<TYPE, ARG_TYPE>::RemoveAll()
	{
		m_arrBuffer.RemoveAll();
	}

	template<typename TYPE, typename ARG_TYPE>
	INT_PTR CStack<TYPE, ARG_TYPE>::GetSize() const
	{
		return m_arrBuffer.GetSize();
	}

	template<typename TYPE, typename ARG_TYPE>
	BOOL CStack<TYPE, ARG_TYPE>::IsEmpty() const
	{
		return m_arrBuffer.IsEmpty();
	}

#pragma endregion
#pragma region Overridables

	template<typename TYPE, typename ARG_TYPE>
	void CStack<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		m_arrBuffer.Serialize(ar);
	}

#ifdef _DEBUG

	template<typename TYPE, typename ARG_TYPE>
	void CStack<TYPE, ARG_TYPE>::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		m_arrBuffer.Dump(dc);
	}

	template<typename TYPE, typename ARG_TYPE>
	void CStack<TYPE, ARG_TYPE>::AssertValid() const
	{
		CObject::AssertValid();

		m_arrBuffer.AssertValid();
	}

#endif

#pragma endregion

}
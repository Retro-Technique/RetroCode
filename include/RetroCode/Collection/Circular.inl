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

#pragma region Constructors

	template<typename TYPE, typename ARG_TYPE>
	CCircular<TYPE, ARG_TYPE>::CCircular()
		: m_nHead(0ll)
		, m_nTail(0ll)
	{

	}

#pragma endregion
#pragma region Operations

	template<typename TYPE, typename ARG_TYPE>
	void CCircular<TYPE, ARG_TYPE>::SetSize(INT_PTR nSize)
	{
		m_nHead = 0ll;
		m_nTail = 0ll;

		m_arrBuffer.SetSize(nSize);
	}

	template<typename TYPE, typename ARG_TYPE>
	INT_PTR CCircular<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
	{
		const INT_PTR nIndex = m_nTail;

		m_arrBuffer.SetAt(nIndex, newElement);

		m_nTail++;

		if (m_nTail >= GetSize())
		{
			m_nTail -= GetSize();
		}

		if (m_nTail == m_nHead && ++m_nHead >= GetSize())
		{
			m_nHead -= GetSize();
		}

		return nIndex;
	}

	template<typename TYPE, typename ARG_TYPE>
	TYPE& CCircular<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex)
	{
		ASSERT(nIndex >= 0);
		ASSERT(nIndex < GetCount());

		if (nIndex >= GetCount())
		{
			AfxThrowInvalidArgException();
		}

		INT_PTR nOffset = m_nHead + nIndex;

		if (nOffset >= GetSize())
		{
			nOffset -= GetSize();
		}

		return m_arrBuffer.GetAt(nOffset);
	}

	template<typename TYPE, typename ARG_TYPE>
	const TYPE& CCircular<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
	{
		ASSERT(nIndex >= 0);
		ASSERT(nIndex < GetCount());

		if (nIndex >= GetCount())
		{
			AfxThrowInvalidArgException();
		}

		const INT_PTR nOffset = m_nHead + nIndex;

		if (nOffset >= GetSize())
		{
			return nOffset -= GetSize();
		}

		return m_arrBuffer.GetAt(nOffset);
	}

	template<typename TYPE, typename ARG_TYPE>
	INT_PTR CCircular<TYPE, ARG_TYPE>::GetCount() const
	{
		if (m_nTail >= m_nHead)
		{
			return m_nTail - m_nHead;
		}

		//FIXME: Problème ici, voir #44

		return GetSize() - m_nHead + m_nTail + 1;
	}

	template<typename TYPE, typename ARG_TYPE>
	void CCircular<TYPE, ARG_TYPE>::RemoveAll()
	{
		m_nHead = 0ll;
		m_nTail = 0ll;
	}

	template<typename TYPE, typename ARG_TYPE>
	INT_PTR CCircular<TYPE, ARG_TYPE>::GetSize() const
	{
		return m_arrBuffer.GetSize();
	}

	template<typename TYPE, typename ARG_TYPE>
	BOOL CCircular<TYPE, ARG_TYPE>::IsEmpty() const
	{
		return m_nHead == m_nTail;
	}

#pragma endregion
#pragma region Overridables

	template<typename TYPE, typename ARG_TYPE>
	void CCircular<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		m_arrBuffer.Serialize(ar);
		if (ar.IsStoring())
		{
			ar << m_nHead << m_nTail;
		}
		else
		{
			ar >> m_nHead >> m_nTail;
		}
	}

#ifdef _DEBUG

	template<typename TYPE, typename ARG_TYPE>
	void CCircular<TYPE, ARG_TYPE>::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		m_arrBuffer.Dump(dc);
		dc << _T("m_nHead = ") << m_nHead << _T("\n");
		dc << _T("m_nTail = ") << m_nTail << _T("\n");
	}

	template<typename TYPE, typename ARG_TYPE>
	void CCircular<TYPE, ARG_TYPE>::AssertValid() const
	{
		CObject::AssertValid();
		
		m_arrBuffer.AssertValid();
		ASSERT(m_nHead >= 0ll);
		ASSERT(m_nHead < GetSize());
		ASSERT(m_nTail >= 0ll);
		ASSERT(m_nTail < GetSize());
	}

#endif

#pragma endregion

}
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

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	CFixed<TYPE, SIZE, ARG_TYPE>::CFixed()
		: m_pData{ 0 }
	{

	}

#pragma endregion
#pragma region Operations

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	INT_PTR CFixed<TYPE, SIZE, ARG_TYPE>::GetSize() const
	{
		return SIZE;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	INT_PTR CFixed<TYPE, SIZE, ARG_TYPE>::GetUpperBound() const
	{
		return (SIZE - 1);
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	const TYPE& CFixed<TYPE, SIZE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
	{
		ASSERT(nIndex >= 0);
		ASSERT(nIndex < SIZE);

		if (nIndex >= 0 && nIndex < SIZE)
		{
			return m_pData[nIndex];
		}

		AfxThrowInvalidArgException();
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	TYPE& CFixed<TYPE, SIZE, ARG_TYPE>::GetAt(INT_PTR nIndex)
	{
		ASSERT(nIndex >= 0);
		ASSERT(nIndex < SIZE);

		if (nIndex >= 0 && nIndex < SIZE)
		{
			return m_pData[nIndex];
		}

		AfxThrowInvalidArgException();
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	const TYPE* CFixed<TYPE, SIZE, ARG_TYPE>::GetData() const
	{
		return (const TYPE*)m_pData;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	TYPE* CFixed<TYPE, SIZE, ARG_TYPE>::GetData()
	{
		return (TYPE*)m_pData;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CFixed<TYPE, SIZE, ARG_TYPE>::SetAt(INT_PTR nIndex, ARG_TYPE newElement)
	{
		ASSERT(nIndex >= 0);
		ASSERT(nIndex < SIZE);

		if (nIndex >= 0 && nIndex < SIZE)
		{
			m_pData[nIndex] = newElement;
			return;
		}
	
		AfxThrowInvalidArgException();
	}

#pragma endregion
#pragma region Overridables

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CFixed<TYPE, SIZE, ARG_TYPE>::Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		if (ar.IsStoring())
		{
			ar.WriteCount(SIZE);
		}
		
		SerializeElements<TYPE>(ar, m_pData, SIZE);
	}

#ifdef _DEBUG

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CFixed<TYPE, SIZE, ARG_TYPE>::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << "with " << SIZE << " elements";
		if (dc.GetDepth() > 0)
		{
			dc << "\n";
			DumpElements<TYPE>(dc, m_pData, SIZE);
		}

		dc << "\n";
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CFixed<TYPE, SIZE, ARG_TYPE>::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT(AfxIsValidAddress(m_pData, SIZE * sizeof(TYPE)));
	}

#endif

#pragma endregion

}
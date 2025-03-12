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
	CBitField<TYPE, SIZE, ARG_TYPE>::CBitField()
		: m_aBytes{0}
	{

	}

#pragma endregion
#pragma region Operations

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	INT_PTR CBitField<TYPE, SIZE, ARG_TYPE>::GetSize() const
	{
		return SIZE;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	INT_PTR CBitField<TYPE, SIZE, ARG_TYPE>::GetCount() const
	{
		INT_PTR nCount = 0;

		for (INT_PTR i = 0; i < SIZE; i++)
		{
			if (GetAt(i))
			{
				nCount++;
			}
		}

		return nCount;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CBitField<TYPE, SIZE, ARG_TYPE>::SetAt(INT_PTR nIndex, BOOL bValue)
	{
		ENSURE(nIndex >= 0);
		ENSURE(nIndex < SIZE);

		if (bValue)
		{
			m_aBytes[nIndex / (sizeof(BYTE) * 8)] |= (1 << (nIndex % (sizeof(BYTE) * 8)));
		}
		else
		{
			m_aBytes[nIndex / (sizeof(BYTE) * 8)] &= ~(1 << (nIndex % (sizeof(BYTE) * 8)));
		}
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	BOOL CBitField<TYPE, SIZE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
	{
		ENSURE(nIndex >= 0);
		ENSURE(nIndex < SIZE);

		return (m_aBytes[nIndex / (sizeof(BYTE) * 8)] & (1 << (nIndex % (sizeof(BYTE) * 8)))) != 0;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CBitField<TYPE, SIZE, ARG_TYPE>::Reset()
	{
		ZeroMemory(m_aBytes, sizeof(m_aBytes));
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	BOOL CBitField<TYPE, SIZE, ARG_TYPE>::IsAll() const
	{
		for (INT_PTR i = 0; i < SIZE; i++)
		{
			if (!GetAt(i))
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	BOOL CBitField<TYPE, SIZE, ARG_TYPE>::IsAny() const
	{
		for (INT_PTR i = 0; i < SIZE; i++)
		{
			if (GetAt(i))
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	BOOL CBitField<TYPE, SIZE, ARG_TYPE>::IsNone() const
	{
		return !IsAny();
	}

#pragma endregion
#pragma region Overridables

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CBitField<TYPE, SIZE, ARG_TYPE>::Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);

		if (ar.IsStoring())
		{
			ar.WriteCount(SIZE);
		}

		SerializeElements<TYPE>(ar, m_aBytes, sizeof(m_aBytes));
	}

#ifdef _DEBUG

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CBitField<TYPE, SIZE, ARG_TYPE>::Dump(CDumpContext& dc) const
	{
		CObject::Dump(dc);

		dc << "with " << SIZE << " elements";
		if (dc.GetDepth() > 0)
		{
			dc << "\n";
			for (INT_PTR i = 0; i < SIZE; i++)
			{
				dc << GetAt(i);
			}
		}
		dc << "\n";
	}

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE>
	void CBitField<TYPE, SIZE, ARG_TYPE>::AssertValid() const
	{
		CObject::AssertValid();

		ASSERT(AfxIsValidAddress(m_aBytes, sizeof(m_aBytes)));
	}

#endif

#pragma endregion

}
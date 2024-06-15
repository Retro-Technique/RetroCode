/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2024 Retro Technique
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

namespace retro
{
	namespace core
	{

#pragma region Constructors

		template<typename TYPE, typename ARG_TYPE>
		CCircular<TYPE, ARG_TYPE>::CCircular()
			: m_nFirstIdx(0)
			, m_nLastIdx(0)
		{

		}

		template<typename TYPE, typename ARG_TYPE>
		CCircular<TYPE, ARG_TYPE>::~CCircular()
		{

		}

#pragma endregion
#pragma region Operations

		template<typename TYPE, typename ARG_TYPE>
		void CCircular<TYPE, ARG_TYPE>::SetSize(INT_PTR nSize)
		{
			m_nFirstIdx = 0;
			m_nLastIdx = 0;

			m_arrBuffer.SetSize(nSize);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CCircular<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
		{
			m_arrBuffer.SetAt(m_nLastIdx++, newElement);

			if (m_nLastIdx >= m_arrBuffer.GetSize())
			{
				m_nLastIdx -= m_arrBuffer.GetSize();
			}
			if (m_nLastIdx == m_nFirstIdx && ++m_nFirstIdx >= m_arrBuffer.GetSize())
			{
				m_nFirstIdx -= m_arrBuffer.GetSize();
			}
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CCircular<TYPE, ARG_TYPE>::GetSize() const
		{
			return m_arrBuffer.GetSize();
		}

		template<typename TYPE, typename ARG_TYPE>
		INT_PTR CCircular<TYPE, ARG_TYPE>::GetCount() const
		{
			if (m_nLastIdx >= m_nFirstIdx)
			{
				return m_nLastIdx - m_nFirstIdx;
			}

			return m_arrBuffer.GetSize() - m_nFirstIdx + m_nLastIdx;
		}

		template<typename TYPE, typename ARG_TYPE>
		TYPE& CCircular<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex)
		{
			INT_PTR uOffset = m_nFirstIdx + nIndex;
			const INT_PTR uCount = m_arrBuffer.GetSize();

			if (uOffset >= uCount)
			{
				uOffset -= uCount;
			}

			return m_arrBuffer.GetAt(uOffset);
		}

		template<typename TYPE, typename ARG_TYPE>
		const TYPE& CCircular<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
		{
			INT_PTR uOffset = m_nFirstIdx + nIndex;
			const INT_PTR uCount = m_arrBuffer.GetSize();

			if (uOffset >= uCount)
			{
				uOffset -= uCount;
			}

			return m_arrBuffer.GetAt(uOffset);
		}

		template<typename TYPE, typename ARG_TYPE>
		void CCircular<TYPE, ARG_TYPE>::RemoveAll()
		{
			m_nFirstIdx = 0;
			m_nLastIdx = 0;
		}

		template<typename TYPE, typename ARG_TYPE>
		BOOL CCircular<TYPE, ARG_TYPE>::IsEmpty() const
		{
			return m_nFirstIdx == m_nLastIdx;
		}

#pragma endregion

	}

}
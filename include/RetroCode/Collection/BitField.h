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

#ifndef __RETRO_COLLECTION_H_INCLUDED__
#error Do not include BitField.h directly, include the Collection.h file
#endif

#pragma once

namespace retro::coll
{

	template<typename TYPE, INT_PTR SIZE, typename ARG_TYPE = const TYPE&>
	class CBitField : public CObject
	{
#pragma region Constructors

	public:

		CBitField();
		~CBitField() = default;

#pragma endregion
#pragma region Attributes

	private:

		static constexpr const INT_PTR BIT_COUNT = SIZE % 8 ? SIZE + 8 - SIZE % 8 : SIZE;

	private:

		BYTE m_aBytes[BIT_COUNT];

#pragma endregion
#pragma region Operations

	public:

		INT_PTR GetSize() const;
		INT_PTR GetCount() const;
		void SetAt(_In_ INT_PTR nIndex, _In_ BOOL bValue);
		BOOL GetAt(_In_ INT_PTR nIndex) const;
		void Reset();
		BOOL IsAll() const;
		BOOL IsAny() const;
		BOOL IsNone() const;

#pragma endregion
#pragma region Overridables

	public:

		void Serialize(_Inout_ CArchive& ar) override;
#ifdef _DEBUG
		void Dump(_Inout_ CDumpContext& dc) const override;
		void AssertValid() const override;
#endif

#pragma endregion

	};

}

#include "BitField.inl"
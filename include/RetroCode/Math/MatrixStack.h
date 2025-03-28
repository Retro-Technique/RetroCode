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

#ifndef __RETRO_MATH_H_INCLUDED__
#error Do not include MatrixStack.h directly, include the Math.h file
#endif

#pragma once

namespace retro::math
{

	class AFX_EXT_CLASS CMatrixStack : public CObject
	{
#pragma region Constructors

		DECLARE_DYNAMIC(CMatrixStack);

	public:

		CMatrixStack();
		~CMatrixStack();

#pragma endregion
#pragma region Attributes

	private:

		static constexpr const INT_PTR START_SIZE = 16;
		static constexpr const INT_PTR ALIGNMENT_SIZE = START_SIZE;

	private:

		INT_PTR				m_nSackSize;
		INT_PTR				m_nCurrent;
		D2D1::Matrix3x2F*	m_pStack;

#pragma endregion
#pragma region Operations

	public:

		_Check_return_ const D2D1::Matrix3x2F Top() const;
		_Check_return_ const D2D1::Matrix3x2F* GetTop() const;
		_Check_return_ INT_PTR GetSize() const;
		void Pop();
		void Push();
		void LoadIdentity();
		void LoadMatrix(_In_ const D2D1::Matrix3x2F& mMatrix);
		void MultiplyMatrix(_In_ const D2D1::Matrix3x2F& mMatrix);
		void Rotate(_In_ FLOAT fAngle, _In_ const D2D1_POINT_2F& ptOrigin);
		void Scale(_In_ FLOAT fScale, _In_ const D2D1_POINT_2F& ptOrigin);
		void Translate(_In_ const D2D1_SIZE_F& szTranslation);

#pragma endregion
#pragma region Overridables

	public:

#ifdef _DEBUG
		void AssertValid() const override;
		void Dump(_Inout_ CDumpContext& dc) const override;
#endif

#pragma endregion
#pragma region Implementations

	private:

		void Allocate();
		void Reallocate(INT_PTR nNewSize);
		void Free();

#pragma endregion
	};

}
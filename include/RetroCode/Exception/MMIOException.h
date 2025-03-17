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

#ifndef __RETRO_EXCEPTION_H_INCLUDED__
#error Do not include MMIOException.h directly, include the Exception.h file
#endif

#pragma once

namespace retro::exception
{

	class AFX_EXT_CLASS CMMIOException : public CException
	{
#pragma region Constructors
		
		DECLARE_DYNAMIC(CMMIOException)

	public:

		CMMIOException(MMRESULT mmResult);
		~CMMIOException() = default;

#pragma endregion
#pragma region Attributes

	private:

		MMRESULT m_mmResult;

#pragma endregion
#pragma region Overridables

	public:

		_Success_(return != 0)
			BOOL GetErrorMessage(
				_Out_writes_z_(nMaxError) LPTSTR lpszError,
				_In_ UINT nMaxError,
				_Out_opt_ PUINT pnHelpContext = NULL) const override;

#ifdef _DEBUG
		void AssertValid() const override;
		void Dump(_Inout_ CDumpContext& dc) const override;
#endif

#pragma endregion
#pragma region Implementations

	private:

		LPCTSTR ErrorToString(
			MMRESULT mmResult) const;

#pragma endregion
	};

}
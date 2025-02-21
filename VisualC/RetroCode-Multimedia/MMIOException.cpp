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

#include "pch.h"
#include "MMIOException.h"

namespace retro::multimedia
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CMMIOException, CException)

	CMMIOException::CMMIOException(MMRESULT mmResult)
		: m_mmResult(mmResult)
	{

	}

#pragma endregion
#pragma region Overridables

	BOOL CMMIOException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError, PUINT pnHelpContext) const
	{
		ASSERT(lpszError && AfxIsValidString(lpszError, nMaxError));

		if (pnHelpContext)
		{
			*pnHelpContext = 0;
		}

		_stprintf_s(lpszError, nMaxError, _T("MMIO error: %s"), ErrorToString(m_mmResult));

		return TRUE;
	}

#pragma endregion
#pragma region Implementations

	LPCTSTR CMMIOException::ErrorToString(MMRESULT mmResult) const
	{
		switch (mmResult)
		{
		case MMIOERR_FILENOTFOUND: return _T("The file is not opened, and the function does not return a valid multimedia file I/O file handle");
		case MMIOERR_CANNOTOPEN: return _T("The file cannot be opened");
		case MMIOERR_CANNOTCLOSE: return _T("The file cannot be closed");
		case MMIOERR_ACCESSDENIED: return _T("The file is protected and cannot be opened");
		case MMIOERR_INVALIDFILE: return _T("Another failure condition occurred. This is the default error for an open-file failure");
		case MMIOERR_NETWORKERROR: return _T("The network is not responding to the request to open a remote file");
		case MMIOERR_PATHNOTFOUND: return _T("The directory specification is incorrect");
		case MMIOERR_SHARINGVIOLATION: return _T("The file is being used by another application and is unavailable");
		case MMIOERR_TOOMANYOPENFILES: return _T("The number of files simultaneously open is at a maximum level. The system has run out of available file handles");
		case MMIOERR_CHUNKNOTFOUND: return _T("The end of the file (or the end of the parent chunk, if given) was reached before the desired chunk was found");
		case MMIOERR_CANNOTSEEK: return _T("There was an error while seeking to the end of the chunk");
		case MMIOERR_CANNOTWRITE: return _T("The contents of the buffer could not be written to disk");
		case MMIOERR_CANNOTEXPAND: return _T("The specified memory file cannot be expanded, probably because the adwInfo member of the MMIOINFO structure was set to zero in the initial call to the mmioOpen function");
		case MMIOERR_CANNOTREAD: return _T("An error occurred while refilling the buffer");
		case MMIOERR_OUTOFMEMORY: return _T("There was not enough memory to expand a memory file for further writing");
		case MMIOERR_UNBUFFERED: return _T("The specified file is not opened for buffered I/O");
		default: break;
		}

		return _T("Unknown MM error");
	}

#pragma endregion
}
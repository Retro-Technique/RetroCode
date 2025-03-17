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
#error Do not include Macros.h directly, include the Exception.h file
#endif

#pragma once

#define THROW_WIN32_EXCEPTION(err) throw new retro::exception::CWin32Exception(err)
#define THROW_MMIO_EXCEPTION(mmr) throw new retro::exception::CMMIOException(mmr)

#define ENSURE_HRESULT(hr) ENSURE_THROW(SUCCEEDED(hr), THROW_WIN32_EXCEPTION(hr))
#define ENSURE_LAST_ERROR(cond) ENSURE_THROW(cond, THROW_WIN32_EXCEPTION(GetLastError()))
#define ENSURE_MMIO(mmr) ENSURE_THROW(MMSYSERR_NOERROR == mmr, THROW_MMIO_EXCEPTION(mmr))

#define REPORT_EXCEPTION_AND_DELETE(szMsg) retro::exception::CReportException(e, szMsg, _T(__FILE__), __LINE__).Report()
#define REPORT_EXCEPTION_NO_DELETE(szMsg) retro::exception::CReportException(e, szMsg, _T(__FILE__), __LINE__, FALSE).Report()
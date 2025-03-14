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
#error Do not include PerlinNoise.h directly, include the Math.h file
#endif

#pragma once

namespace retro::math
{

	AFX_EXT_API 
	_Check_return_ 
	DOUBLE PerlinNoise(
		_In_ DOUBLE x, 
		_In_ DOUBLE y);

	AFX_EXT_API 
	_Check_return_ 
	DOUBLE* NoiseMap(
		_Inout_updates_all_(uWidth * uHeight)  DOUBLE* pNoiseMap,
		_In_ UINT uWidth, 
		_In_ UINT uHeight, 
		_In_ DOUBLE fScale, 
		_In_ UINT uOctaveCount, 
		_In_ FLOAT fPersistance, 
		_In_ FLOAT fLacunarity);

}
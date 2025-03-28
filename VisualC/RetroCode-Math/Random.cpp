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

namespace retro::math
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CRandom, CObject);

	CRandom::CRandom()
	{
		Seed();
	}

	CRandom::CRandom(_In_ UINT uSeed)
	{
		Seed(uSeed);
	}

#pragma endregion
#pragma region Operations

	void CRandom::Seed()
	{
		const CTime dtNow = CTime::GetCurrentTime();
		const time_t nTimestamp = dtNow.GetTime();
		const UINT uSeed = static_cast<UINT>(nTimestamp);

		Seed(uSeed);
	}

	void CRandom::Seed(_In_ UINT uSeed)
	{
		srand(uSeed);
	}

	_Check_return_ INT CRandom::NextInteger() const
	{
		return rand();
	}

	_Check_return_ INT CRandom::NextInteger(_In_ INT nMaxValueExcluded) const
	{
		return NextInteger() % nMaxValueExcluded;
	}

	_Check_return_ INT CRandom::NextInteger(_In_ INT nMinValueIncluded, _In_ INT nMaxValueExcluded) const
	{
		return (NextInteger() % (nMaxValueExcluded - nMinValueIncluded)) + nMinValueIncluded;
	}

	_Check_return_ FLOAT CRandom::NextFloat() const
	{
		return static_cast<FLOAT>(NextInteger()) / RAND_MAX;
	}

	_Check_return_ DOUBLE CRandom::NextDouble() const
	{
		return NextInteger() / RAND_MAX;
	}

	void CRandom::NextBytes(_Out_writes_(uByteCount) LPBYTE pBytes, _In_ UINT_PTR uByteCount) const
	{
		ENSURE(AfxIsValidAddress(pBytes, uByteCount * sizeof(BYTE), TRUE));

		for (UINT_PTR i = 0; i < uByteCount; i++)
		{
			pBytes[i] = static_cast<BYTE>(NextInteger(0, sizeof(BYTE)));
		}
	}

	_Check_return_ BOOL CRandom::NextBoolean() const
	{
		return NextInteger() & 1;
	}

#pragma endregion

}
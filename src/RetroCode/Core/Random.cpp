/**
 *
 * Retro Code
 *
 * MIT License
 *
 * Copyright(c) 2014-2024 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "pch.h"

namespace retro
{
	namespace core
	{

		CRandom::CRandom()
		{
			const CTime dtNow = CTime::GetCurrentTime();
			const time_t nTimestamp = dtNow.GetTime();
			const UINT uSeed = static_cast<UINT>(nTimestamp);

			Seed(uSeed);
		}

		CRandom::CRandom(UINT uSeed)
		{
			Seed(uSeed);
		}

		CRandom::~CRandom()
		{

		}

		void CRandom::Seed(UINT uSeed)
		{
			srand(uSeed);
		}

		INT CRandom::NextInteger()
		{
			return rand();
		}

		INT CRandom::NextInteger(INT nMaxValueExcluded)
		{
			return NextInteger() % nMaxValueExcluded;
		}

		INT CRandom::NextInteger(INT nMinValueIncluded, INT nMaxValueExcluded)
		{
			return (NextInteger() % (nMaxValueExcluded - nMinValueIncluded)) + nMinValueIncluded;
		}

		FLOAT CRandom::NextFloat()
		{
			return static_cast<FLOAT>(NextInteger()) / RAND_MAX;
		}

		DOUBLE CRandom::NextDouble()
		{
			return NextInteger() / RAND_MAX;
		}

		void CRandom::NextBytes(BYTE* pBytes, UINT uByteCount)
		{
			if (!pBytes)
			{
				return;
			}

			for (UINT i = 0; i < uByteCount; i++)
			{
				pBytes[i] = static_cast<BYTE>(NextInteger(0, sizeof(BYTE)));
			}
		}

		BOOL CRandom::NextBoolean()
		{
			return NextInteger() & 1;
		}

	}
}
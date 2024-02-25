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

		HRESULT Shuffle(INT* pIndexes, UINT uIndexCount)
		{
			if (!pIndexes)
			{
				return E_INVALIDARG;
			}

			if (uIndexCount == 0)
			{
				return E_INVALIDARG;
			}

			for (UINT i = 0; i < uIndexCount; i++)
			{
				pIndexes[i] = i;
			}

			CRandom Random;

			UINT uIndexCount2 = uIndexCount;
			for (UINT i = 0; i < uIndexCount; i++)
			{
				const UINT uIndex = Random.NextInteger(0, uIndexCount2);
				const INT nTemp = pIndexes[uIndex];
				pIndexes[uIndex] = pIndexes[uIndexCount2 - 1];
				pIndexes[uIndexCount - i - 1] = nTemp;
				uIndexCount2--;
			}

			return S_OK;
		}

	}
}
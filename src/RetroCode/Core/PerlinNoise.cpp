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

		static inline INT Noise2(INT x, INT y)
		{
			static constexpr const INT HASH[] = { 208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
							 185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
							 9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
							 70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
							 203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
							 164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
							 228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
							 232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
							 193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
							 101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
							 135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
							 114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219 };
			static constexpr const INT HASH_COUNT = ARRAYSIZE(HASH);

			const INT nTmp = HASH[y % HASH_COUNT];

			return HASH[(nTmp + x) % HASH_COUNT];
		}

		static inline DOUBLE LinInter(DOUBLE x, DOUBLE y, DOUBLE s)
		{
			return x + s * (y - x);
		}

		static inline DOUBLE SmoothInter(DOUBLE x, DOUBLE y, DOUBLE s)
		{
			return LinInter(x, y, s * s * (3. - 2. * s));
		}

		DOUBLE PerlinNoise(DOUBLE x, DOUBLE y)
		{
			const INT x_int = static_cast<INT>(x);
			const INT y_int = static_cast<INT>(y);
			const DOUBLE x_frac = x - x_int;
			const DOUBLE y_frac = y - y_int;
			const INT s = Noise2(x_int, y_int);
			const INT t = Noise2(x_int + 1, y_int);
			const INT u = Noise2(x_int, y_int + 1);
			const INT v = Noise2(x_int + 1, y_int + 1);
			const DOUBLE low = SmoothInter(s, t, x_frac);
			const DOUBLE high = SmoothInter(u, v, x_frac);

			return SmoothInter(low, high, y_frac);
		}

		HRESULT NoiseMap(DOUBLE* pNoiseMap, UINT uWidth, UINT uHeight, DOUBLE fScale, UINT uOctaveCount, FLOAT fPersistance, FLOAT fLacunarity)
		{
			if (!pNoiseMap)
			{
				return E_INVALIDARG;
			}

			if (uWidth < 1)
			{
				uWidth = 1;
			}

			if (uHeight < 1)
			{
				uHeight = 1;
			}

			if (fScale <= 0.)
			{
				fScale = 0.0001;
			}

			if (fLacunarity < 1.f)
			{
				fLacunarity = 1.f;
			}

			const UINT uSize = uWidth * uHeight;

			DOUBLE fMaxNoiseHeight = 0.;
			DOUBLE fMinNoiseHeight = DBL_MAX;

			for (UINT col = 0; col < uHeight; col++)
			{
				for (UINT row = 0; row < uWidth; row++)
				{
					DOUBLE fAmplitude = 1.;
					DOUBLE fFrequency = 1.;
					DOUBLE fNoiseHeight = 0.;

					for (UINT i = 0; i < uOctaveCount; i++)
					{
						const DOUBLE fSampleX = row / fScale * fFrequency;
						const DOUBLE fSampleY = col / fScale * fFrequency;

						const DOUBLE fPerlinValue = PerlinNoise(fSampleX, fSampleY) * 2. - 1.;

						fNoiseHeight += fPerlinValue * fAmplitude;
						fAmplitude = fAmplitude * fPersistance;
						fFrequency = fFrequency * fLacunarity;
					}

					fMaxNoiseHeight = Max(fMaxNoiseHeight, fNoiseHeight);
					fMinNoiseHeight = Min(fMinNoiseHeight, fNoiseHeight);

					const UINT uIndex = col * uWidth + row;
					pNoiseMap[uIndex] = fNoiseHeight;
				}
			}

			for (UINT i = 0; i < uSize; i++)
			{
				pNoiseMap[i] = InverseLerp(fMinNoiseHeight, fMaxNoiseHeight, pNoiseMap[i]);
			}

			return S_OK;
		}

	}
}
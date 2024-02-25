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

		DOUBLE LinearInterpolate(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE x)
		{
			if (x1 == x2)
			{
				return y1;
			}

			return y1 + ((x - x1) / (x2 - x1)) * (y2 - y1);
		}

		DOUBLE BilinearInterpolate(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE q11, DOUBLE q12, DOUBLE q21, DOUBLE q22, DOUBLE x, DOUBLE y)
		{
			return (q11 * (x2 - x) * (y2 - y) +
				q21 * (x - x1) * (y2 - y) +
				q12 * (x2 - x) * (y - y1) +
				q22 * (x - x1) * (y - y1)) / ((x2 - x1) * (y2 - y1));
		}

		DOUBLE Lerp(DOUBLE a, DOUBLE b, DOUBLE t)
		{
			t = Clamp(t, a, b);

			return a + t * (b - a);
		}

		DOUBLE InverseLerp(DOUBLE a, DOUBLE b, DOUBLE t)
		{
			if (a == b)
			{
				return 0.;
			}

			return (t - a) / (b - a);
		}

	}
}
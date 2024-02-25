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

namespace retro
{
	namespace core
	{

		template<typename T>
		void Swap(T& a, T& b)
		{
			T temp = a;
			a = b;
			b = temp;
		}

		template<typename T>
		const T& Min(const T& a, const T& b)
		{
			return (b < a) ? b : a;
		}

		template<typename T>
		const T& Max(const T& a, const T& b)
		{
			return (b > a) ? b : a;
		}

		template<typename T>
		const T& Clamp(const T& val, const T& min, const T& max)
		{
			if (val < min)
			{
				return min;
			}

			if (val > max)
			{
				return max;
			}

			return val;
		}

		template<typename T>
		T EuclidianDistance(T x1, T y1, T x2, T y2)
		{
			return EuclidianDistance(static_cast<DOUBLE>(x1), static_cast<DOUBLE>(y1), static_cast<DOUBLE>(x2), static_cast<DOUBLE>(y2));
		}

		template<>
		inline FLOAT EuclidianDistance(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2)
		{
			return sqrtf(powf((x1 - x2), 2.f) + powf((y1 - y2), 2.f));
		}

		template<>
		inline DOUBLE EuclidianDistance(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2)
		{
			return sqrt(pow((x1 - x2), 2.f) + pow((y1 - y2), 2.f));
		}

		template<typename T>
		T ManhattanDistance(T x1, T y1, T x2, T y2)
		{
			return ManhattanDistance(static_cast<DOUBLE>(x1), static_cast<DOUBLE>(y1), static_cast<DOUBLE>(x2), static_cast<DOUBLE>(y2));
		}

		template<>
		inline FLOAT ManhattanDistance(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2)
		{
			return fabsf(x1 - x2) + fabsf(y1 - y2);
		}

		template<>
		inline DOUBLE ManhattanDistance(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2)
		{
			return fabs(x1 - x2) + fabs(y1 - y2);
		}

		template<>
		inline INT ManhattanDistance(INT x1, INT y1, INT x2, INT y2)
		{
			return abs(x1 - x2) + abs(y1 - y2);
		}

		template<>
		inline LONG ManhattanDistance(LONG x1, LONG y1, LONG x2, LONG y2)
		{
			return labs(x1 - x2) + labs(y1 - y2);
		}

		template<>
		inline LONGLONG ManhattanDistance(LONGLONG x1, LONGLONG y1, LONGLONG x2, LONGLONG y2)
		{
			return llabs(x1 - x2) + llabs(y1 - y2);
		}

	}
}
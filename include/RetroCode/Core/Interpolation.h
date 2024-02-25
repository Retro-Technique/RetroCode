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

#pragma once

namespace retro
{
	namespace core
	{

		/**
		 * @ingroup core
		 * @brief Performs a linear interpolation between two points
		 *
		 * @param x1 The x-coordinate of the first point
		 * @param y1 The y-coordinate of the first point
		 * @param x2 The x-coordinate of the second point
		 * @param y2 The y-coordinate of the second point
		 * @param x The x-coordinate of the point to interpolate
		 *
		 * @return The y-coordinate of the interpolated point
		 *
		 */
		DOUBLE AFX_EXT_API LinearInterpolate(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE x);

		/**
		 * @ingroup core
		 * @brief Performs a bilinear interpolation between four points
		 *
		 * @param x1 The x-coordinate of the first corner of the rectangle
		 * @param y1 The y-coordinate of the first corner of the rectangle
		 * @param x2 The x-coordinate of the second corner of the rectangle
		 * @param y2 The y-coordinate of the second corner of the rectangle
		 * @param q11 The value at the first corner of the rectangle
		 * @param q12 The value at the second corner of the rectangle
		 * @param q21 The value at the third corner of the rectangle
		 * @param q22 The value at the fourth corner of the rectangle
		 * @param x The x-coordinate of the point to interpolate
		 * @param y The y-coordinate of the point to interpolate
		 * 
		 * @return The value at the interpolated point
		 *
		 */
		DOUBLE AFX_EXT_API BilinearInterpolate(DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2, DOUBLE q11, DOUBLE q12, DOUBLE q21, DOUBLE q22, DOUBLE x, DOUBLE y);

		/**
		 * @ingroup core
		 * @brief Performs a linear interpolation between two values
		 *
		 * @param a The first value
		 * @param b The second value
		 * @param t The interpolation parameter between 0 and 1
		 *
		 * @return The interpolated value between a and b proportionally to \a t
		 *
		 */
		DOUBLE AFX_EXT_API Lerp(DOUBLE a, DOUBLE b, DOUBLE t);

		/**
		 * @ingroup core
		 * @brief Performs an inverse linear interpolation between two values
		 *
		 * @param a The first value
		 * @param b The second value
		 * @param value The value to invert between \a a and \a b
		 *
		 * @return The interpolation parameter between 0 and 1 that corresponds to the position of value between \a a and \a b
		 *
		 */
		DOUBLE AFX_EXT_API InverseLerp(DOUBLE a, DOUBLE b, DOUBLE t);

	}
}
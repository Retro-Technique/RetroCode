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
		 * @brief Swaps the values of two variables
		 *
		 * @param a	A reference to the first variable
		 * @param b	A reference to the second variable
		 *
		 */
		template<typename T>
		void Swap(T& a, T& b);

		/**
		 * @ingroup core
		 * @brief Returns the smaller of two values
		 *
		 * @param a	A reference to the first variable
		 * @param b	A reference to the second variable
		 * 
		 * @return A reference to the smaller value
		 *
		 */
		template<typename T>
		const T& Min(const T& a, const T& b);

		/**
		 * @ingroup core
		 * @brief Returns the larger  of two values
		 *
		 * @param a	A reference to the first variable
		 * @param b	A reference to the second variable
		 *
		 * @return A reference to the larger value
		 *
		 */
		template<typename T>
		const T& Max(const T& a, const T& b);

		/**
		 * @ingroup core
		 * @brief Clamps a value between a minimum and a maximum value
		 *
		 * @param val The value to clamp
		 * @param min The minimum value
		 * @param max The maximum value
		 *
		 * @return A reference to the clamped value, which is either val, min or max depending on which is closest to val
		 *
		 */
		template<typename T>
		const T& Clamp(const T& val, const T& min, const T& max);

		/**
		 * @ingroup core
		 * @brief Computes the Euclidean distance between two points
		 *
		 * @param x1 The x coordinate of the first point
		 * @param y1 The y coordinate of the first point
		 * @param x2 The x coordinate of the second point
		 * @param y2 The y coordinate of the second point
		 *
		 * @return The Euclidean distance between the two points
		 * 
		 * @pre The parameters must be of the same type T
		 *
		 */
		template<typename T>
		T EuclidianDistance(T x1, T y1, T x2, T y2);

		/**
		 * @ingroup core
		 * @brief Computes the Manhattan distance between two points
		 *
		 * @param x1 The x coordinate of the first point
		 * @param y1 The y coordinate of the first point
		 * @param x2 The x coordinate of the second point
		 * @param y2 The y coordinate of the second point
		 *
		 * @return The Manhattan distance between the two points
		 *
		 * @pre The parameters must be of the same type T
		 *
		 */
		template<typename T>
		T ManhattanDistance(T x1, T y1, T x2, T y2);

	}
}

#include "Operation.inl"
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
		 * @brief Class for generating pseudo-random numbers
		 *
		 */
		class AFX_EXT_API CRandom
		{
			public:

				/**
				 * @brief Default constructor
				 * 
				 * Initializes the random number generator with a default seed.
				 *
				 */
				CRandom();

				/**
				 * @brief Constructor with a specified seed
				 *
				 * Initializes the random number generator with the given seed.
				 *
				 * @param uSeed The seed to use for the random number generator
				 * 
				 */
				explicit CRandom(UINT uSeed);

				/**
				 * @brief Destructor
				 *
				 */
				~CRandom();

			public:

				/**
				 * @brief Sets the seed for the random number generator
				 * 
				 * @param uSeed The seed to use for the random number generator
				 *
				 */
				void Seed(UINT uSeed);

				/**
				 * @brief Returns a random integer in the range [0 ; 32767]
				 *
				 * @return A random integer in the range [0 ; 32767]
				 *
				 */
				INT NextInteger();												

				/**
				 * @brief Returns a random integer in the range [0 ; nMaxValueExcluded[
				 *
				 * @param nMaxValueExcluded The upper bound (excluded) of the random number range
				 * 
				 * @return A random integer in the range [0 ; nMaxValueExcluded[
				 *
				 */
				INT NextInteger(INT nMaxValueExcluded);							

				/**
				 * @brief Returns a random integer in the range [nMinValueIncluded ; nMaxValueExcluded[
				 *
				 * @param nMinValueIncluded The lower bound (included) of the random number range
				 * @param nMaxValueExcluded The upper bound (excluded) of the random number range
				 *
				 * @return A random integer in the range [nMinValueIncluded ; nMaxValueExcluded[
				 *
				 */
				INT NextInteger(INT nMinValueIncluded, INT nMaxValueExcluded);	

				/**
				 * @brief Returns a random float in the range [0.f ; 1.f]
				 *
				 * @return A random float in the range [0.f ; 1.f]
				 *
				 */
				FLOAT NextFloat();												

				/**
				 * @brief Returns a random double in the range [0. ; 1.]
				 *
				 * @return A random double in the range [0. ; 1.]
				 *
				 */
				DOUBLE NextDouble();											

				/**
				 * @brief Fills an array of bytes with random values in the range [0 ; 255]
				 *
				 * @param pBytes		A pointer to the array of bytes to fill with random values
				 * @param uByteCount	The number of bytes to fill with random values
				 *
				 */
				void NextBytes(BYTE* pBytes, UINT uByteCount);

				/**
				 * @brief Returns a random boolean value (TRUE or FALSE)
				 *
				 * @return A random boolean value (TRUE or FALSE)
				 *
				 */
				BOOL NextBoolean();												

		};

	}
}
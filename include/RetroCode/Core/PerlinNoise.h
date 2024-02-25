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
		 * @brief Computes a Perlin noise value for a given 2D point
		 *
		 * Perlin noise is a type of gradient noise that can be used to create natural-looking 
		 * textures, such as clouds, terrain, or marble. It is based on interpolating random values
		 * at each integer coordinate of a grid, and using the fractional part of the point
		 * as the interpolation parameter. The result is a smooth and continuous noise function.
		 *
		 * @param x The x coordinate of the point
		 * @param y The y coordinate of the point
		 *
		 * @return A Perlin noise value
		 *
		 */
		DOUBLE AFX_EXT_API PerlinNoise(DOUBLE x, DOUBLE y);

		/**
		 * @ingroup core
		 * @brief Generates a noise map from given parameters
		 *
		 * @param pNoiseMap		A pointer to a one-dimensional array of float that will contain the generated noise map
		 * @param uWidth		The width of the noise map in pixels
		 * @param uHeight		The height of the noise map in pixels
		 * @param fScale		The scale factor that determines the level of detail of the noise map
		 * @param uOctaveCount	The number of octaves used for Perlin noise
		 * @param fPersistance	The persistance that controls the amplitude of successive octaves
		 * @param fLacunarity	The lacunarity that controls the frequency of successive octaves
		 * 
		 * @return S_OK if the generation was successful
		 *
		 */
		HRESULT AFX_EXT_API NoiseMap(DOUBLE* pNoiseMap, UINT uWidth, UINT uHeight, DOUBLE fScale, UINT uOctaveCount, FLOAT fPersistance, FLOAT fLacunarity);

	}
}
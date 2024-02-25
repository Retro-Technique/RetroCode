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
		 * @brief Query the RAM usage of the application
		 *
		 * @param uRAMUsage Reference to a SIZE_T variable to receive the RAM usage in bytes
		 *
		 * @return S_OK if successful, or an error value otherwise
		 *
		 */
		HRESULT AFX_EXT_API QueryRAMUsage(SIZE_T& uRAMUsage);

		/**
		 * @ingroup core
		 * @brief Query the CPU usage of the application
		 *
		 * @param fCPUUsage Reference to a DOUBLE variable to receive the CPU usage in percentage
		 *
		 * @return S_OK if successful, or an error value otherwise
		 *
		 */
		HRESULT AFX_EXT_API QueryCPUUsage(DOUBLE& fCPUUsage);

		/**
		 * @ingroup core
		 * @brief Formats a size in bytes as a human-readable string
		 * 
		 * This function takes a size in bytes as input and returns a string
		 * representing the size in a human-readable format, using the appropriate
		 * unit (B, KB, MB, GB, or TB) depending on the magnitude of the size
		 *
		 * @param uBytes The size in bytes to format
		 *
		 * @return A string representing the size in a human-readable format
		 *
		 */
		CString AFX_EXT_API SizeToString(SIZE_T uBytes);

	}
}
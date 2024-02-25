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
		 * @brief Class for measuring elapsed time with start, stop and reset functions
		 *
		 */
		class AFX_EXT_API CStopWatch
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				CStopWatch();

				/**
				 * @brief Destructor
				 *
				 */
				~CStopWatch();

			public:

				/**
				 * @brief Get the elapsed time since the stop watch was started or restarted
				 *
				 * @return The number of milliseconds representing the elapsed time
				 *
				 */
				ULONGLONG GetElapsedTime() const;

				/**
				 * @brief Check if the stop watch is running or not
				 *
				 * @return True if the stop watch is running, false otherwise
				 *
				 */
				BOOL IsRunning() const;

				/**
				 * @brief Start the stop watch if it is not already running
				 *
				 */
				void Start();

				/**
				 * @brief Stop the stop watch if it is running and add the elapsed time to the time buffer
				 *
				 */
				void Stop();

				/**
				 * @brief Reset the stop watch to zero elapsed time and not running
				 *
				 */
				void Reset();

				/**
				 * @brief Restart the stop watch and reset the elapsed time to zero
				 *
				 */
				void Restart();

			private:

				/**
				 * Member data
				 */
				CClock		m_Clock;
				ULONGLONG	m_uTimeBuffer;
				BOOL		m_bRunning;

		};

	}
}
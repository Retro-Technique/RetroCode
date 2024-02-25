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
		 * @brief Class for measuring remaining time with a specified time limit
		 *
		 */
		class AFX_EXT_API CTimer
		{
			public:

				/**
				 * @brief Default constructor
				 *
				 */
				CTimer();

				/**
				 * @brief Destructor
				 *
				 */
				~CTimer();

			public:

				/**
				 * @brief Get the remaining time until the timer expires
				 *
				 * @return The number of milliseconds representing the remaining time
				 *
				 */
				ULONGLONG GetRemainingTime() const;

				/**
				 * @brief Check if the timer is running or not
				 *
				 * @return True if the timer is running, false otherwise
				 *
				 */
				BOOL IsRunning() const;

				/**
				 * @brief Check if the timer is expired or not
				 *
				 * @return True if the timer is expired, false otherwise
				 *
				 */
				BOOL IsExpired() const;

				/**
				 * @brief Start the timer if it is not already running
				 *
				 */
				void Start();

				/**
				 * @brief Stop the timer if it is running
				 *
				 */
				void Stop();

				/**
				 * @brief Reset the timer with a new time limit and not running
				 *
				 * @param uTimeLimit The new time limit for the timer
				 *
				 */
				void Reset(const ULONGLONG uTimeLimit);

				/**
				 * @brief Restart the timer with a new time limit and reset the remaining time
				 *
				 * @param uTimeLimit The new time limit for the timer
				 *
				 */
				void Restart(const ULONGLONG uTimeLimit);

			private:

				/**
				 * Member data
				 */
				CStopWatch	m_StopWatch;
				ULONGLONG	m_uLimit;

		};

	}
}
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
		 * @brief Logs a message with a given log level
		 *
		 * @param lpszMessage	The text of the message to log
		 * @param eLogLevel		The log level of the message
		 *
		 * @note The default log level value is ELogLevel_Information
		 *
		 */
		void AFX_EXT_API Log(LPCTSTR lpszMessage, ELogLevel eLogLevel = ELogLevel_Information);

		/**
		 * @ingroup core
		 * @brief Logs an error message with a given HRESULT code
		 *
		 * @param lpszMessage	The text of the message to log
		 * @param hr			The HRESULT code of the error
		 * @param eLogLevel		The log level of the message
		 *
		 * @note The default log level value is ELogLevel_Error
		 *
		 */
		void AFX_EXT_API LogInterfaceError(LPCTSTR lpszMessage, HRESULT hr, ELogLevel eLogLevel = ELogLevel_Error);

		/**
		 * @ingroup core
		 * @brief Logs an error message with a given Windows error code
		 *
		 * @param lpszMessage	The text of the message to log
		 * @param hr			The Windows error code of the error
		 * @param eLogLevel		The log level of the message
		 *
		 * @note The default log level value is ELogLevel_Error
		 *
		 */
		void AFX_EXT_API LogWinError(LPCTSTR lpszMessage, DWORD dwError, ELogLevel eLogLevel = ELogLevel_Error);

		/**
		 * @ingroup core
		 * @brief Registers a log observer to receive notifications from the log source
		 *
		 * @param pObserver	A pointer to the log observer object to register
		 * @param bFlush	A flag that indicates whether to flush the existing log messages to the observer
		 *
		 * @return A HRESULT value indicating the success or failure of the operation
		 *
		 * @note The default flush value is false
		 * 
		 */
		HRESULT AFX_EXT_API RegisterLogObserver(ILogObserver* pObserver, BOOL bFlush = FALSE);

		/**
		 * @ingroup core
		 * @brief Unregisters a log observer from receiving notifications from the log source
		 *
		 * @param pObserver	A pointer to the log observer object to unregister
		 *
		 */
		void AFX_EXT_API UnregisterLogObserver(ILogObserver* pObserver);

		/**
		 * @ingroup core
		 * @brief Unregisters all log observers from receiving notifications from the log source
		 *
		 */
		void AFX_EXT_API UnregisterAllObserver();

	}
}

#define LogDbg(msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::Log(__txt__.GetString(), retro::core::ELogLevel_Debug); }
#define LogInf(msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::Log(__txt__.GetString(), retro::core::ELogLevel_Information); }
#define LogPrc(msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::Log(__txt__.GetString(), retro::core::ELogLevel_Process); }
#define LogWarn(msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::Log(__txt__.GetString(), retro::core::ELogLevel_Warning); }
#define LogErr(msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::Log(__txt__.GetString(), retro::core::ELogLevel_Error); }
#define LogWinMsg(err, msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::LogWinError(__txt__.GetString(), err); }
#define LogHRMsg(hr, msg, ...) { CString __txt__; __txt__.Format(msg, __VA_ARGS__); retro::core::LogInterfaceError(__txt__.GetString(), hr); }
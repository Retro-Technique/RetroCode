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

/**
 * Headers
 */
#include "Common.h"

#include "Core/i18n.h"
#include "Core/LogLevel.h"
#include "Core/ILogObserver.h"
#include "Core/Logger.h"
#include "Core/Operation.h"
#include "Core/StaticArray.h"
#include "Core/Stack.h"
#include "Core/Queue.h"
#include "Core/MessageQueue.h"
#include "Core/Circular.h"
#include "Core/Random.h"
#include "Core/Interpolation.h"
#include "Core/PerlinNoise.h"
#include "Core/ObjectEx.h"
#include "Core/Base64.h"
#include "Core/Shuffle.h"
#include "Core/Clock.h"
#include "Core/StopWatch.h"
#include "Core/Timer.h"
#include "Core/PrefPath.h"
#include "Core/System.h"
#include "Core/Resource.h"
#include "Core/Image.h"
#include "Core/Color.h"
#include "Core/Vector2.h"
#include "Core/Rect.h"
#include "Core/LogManager.h"

namespace retro
{
	namespace core
	{

		/**
		 * @ingroup core
		 * @brief Get Retro Core runtime version
		 *
		 * @return The version of Retro Core
		 *
		 */
		AFX_EXT_API CString GetVersion();

	}
}

/**
 * @defgroup core Core module
 *
 * Base module of RetroCode, defining various utilities. It provides
 * container, algorithm, mathematics, logs, timing classes.
 *
 */
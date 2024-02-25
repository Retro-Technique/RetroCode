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

#include "pch.h"

namespace retro
{
	namespace core
	{

		TColorRGBA::TColorRGBA()
			: Red(0)
			, Green(0)
			, Blue(0)
			, Alpha(255)
		{

		}

		TColorRGBA::TColorRGBA(const TColorRGBA& Other)
			: Red(Other.Red)
			, Green(Other.Green)
			, Blue(Other.Blue)
			, Alpha(Other.Alpha)
		{

		}

		TColorRGBA::TColorRGBA(COLORREF uColor, BYTE uAlpha)
		{
			FromCOLORREF(uColor);
			Alpha = uAlpha;
		}

		TColorRGBA::TColorRGBA(BYTE red, BYTE green, BYTE blue, BYTE alpha)
			: Red(red)
			, Green(green)
			, Blue(blue)
			, Alpha(alpha)
		{

		}

		TColorRGBA::~TColorRGBA()
		{

		}

		BOOL TColorRGBA::operator==(const TColorRGBA& Other)
		{
			return (Red == Other.Red) && (Green == Other.Green) && (Blue == Other.Blue) && (Alpha == Other.Alpha);
		}

		BOOL TColorRGBA::operator!=(const TColorRGBA& Other)
		{
			return !(*this == Other);
		}

		TColorRGBA TColorRGBA::operator+(const TColorRGBA& Other)
		{
			return TColorRGBA(core::Min<BYTE>(Red + Other.Red, 255),
				core::Min<BYTE>(Green + Other.Green, 255),
				core::Min<BYTE>(Blue + Other.Blue, 255),
				core::Min<BYTE>(Alpha + Other.Alpha, 255));
		}

		TColorRGBA TColorRGBA::operator-(const TColorRGBA& Other)
		{
			return TColorRGBA(core::Max<BYTE>(Red + Other.Red, 0),
				core::Max<BYTE>(Green + Other.Green, 0),
				core::Max<BYTE>(Blue + Other.Blue, 0),
				core::Max<BYTE>(Alpha + Other.Alpha, 0));
		}

		TColorRGBA TColorRGBA::operator*(const TColorRGBA& Other)
		{
			return TColorRGBA((Red + Other.Red) / 255,
				(Green + Other.Green) / 255,
				(Blue + Other.Blue) / 255,
				(Alpha + Other.Alpha) / 255);
		}

		TColorRGBA& TColorRGBA::operator+=(const TColorRGBA& Other)
		{
			return *this = *this + Other;
		}

		TColorRGBA& TColorRGBA::operator-=(const TColorRGBA& Other)
		{
			return *this = *this - Other;
		}

		TColorRGBA& TColorRGBA::operator*=(const TColorRGBA& Other)
		{
			return *this = *this * Other;
		}

		void TColorRGBA::FromCOLORREF(COLORREF uColor)
		{
			Red = GetRValue(uColor);
			Green = GetGValue(uColor);
			Blue = GetBValue(uColor);
		}

		COLORREF TColorRGBA::ToCOLORREF() const
		{
			return RGB(Red, Green, Blue);
		}

	}
}
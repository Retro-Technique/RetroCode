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
		 * @brief Structure representing a color with red, green, blue and alpha components
		 *
		 */
		struct AFX_EXT_API TColorRGBA
		{
			static constexpr const auto ALPHA_OPAQUE = 255;		/**< The value of the alpha component for an opaque color */
			static constexpr const auto ALPHA_TRANSPARENT = 0;	/**< The value of the alpha component for a transparent color */

			/**
			 * @brief Default constructor
			 *
			 */
			TColorRGBA();

			/**
			 * @brief Copy constructor
			 *
			 * @param Other The RGBA component
			 *
			 */
			TColorRGBA(const TColorRGBA& Other);

			/**
			 * @brief Constructor with COLORREF
			 *
			 * @param uColor The COLORREF value
			 * @param uAlpha The alpha component
			 *
			 */
			explicit TColorRGBA(COLORREF uColor, BYTE uAlpha = ALPHA_OPAQUE);

			/**
			 * @brief Constructor with RGBA components
			 *
			 * @param uRed   The red component
			 * @param uGreen The green component
			 * @param uBlue	 The blue component
			 * @param uAlpha The alpha component
			 *
			 */
			TColorRGBA(BYTE uRed, BYTE uGreen, BYTE uBlue, BYTE uAlpha = ALPHA_OPAQUE);

			/**
			 * @brief Destructor
			 *
			 */
			~TColorRGBA();

			/**
			 * @brief Overloaded binary == operator to compare two colors
			 *
			 * @param Other The other color to compare with
			 *
			 * @return True if the two colors are equal, false otherwise
			 *
			 */
			BOOL operator==(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary != operator to compare two colors
			 *
			 * @param Other The other color to compare with
			 *
			 * @return True if the two colors are different, false otherwise
			 *
			 */
			BOOL operator!=(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary + operator to add two colors
			 *
			 * @param Other The other color to add with
			 *
			 * @return The result of adding the two colors component-wise
			 *
			 * @note If the result of the addition is greater than 255, it is clamped to 255
			 *
			 */
			TColorRGBA operator+(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary - operator to subtract two colors
			 *
			 * @param Other The other color to subtract with
			 *
			 * @return The result of subtracting the two colors component-wise
			 *
			 * @note If the result of the subtraction is less than 0, it is clamped to 0
			 *
			 */
			TColorRGBA operator-(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary * operator to multiply two colors
			 *
			 * @param Other The other color to multiply with
			 *
			 * @return The result of multiplying the two colors component-wise
			 *
			 * @note The result is divided by 255 to preserve the range of values
			 *
			 */
			TColorRGBA operator*(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary += operator to add another color and assign the result to this one
			 *
			 * @param Other The other color to add with
			 *
			 * @return A reference to this after adding it with the other color
			 *
			 * @note This function is equivalent to calling this = this + Other
			 *
			 */
			TColorRGBA& operator+=(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary -= operator to subtract another color and assign the result to this one
			 *
			 * @param Other The other color to subtract with
			 *
			 * @return A reference to this after subtracting it with the other color
			 *
			 * @note This function is equivalent to calling this = this - Other
			 *
			 */
			TColorRGBA& operator-=(const TColorRGBA& Other);

			/**
			 * @brief Overloaded binary *= operator to multiply another color and assign the result to this one
			 *
			 * @param Other The other color to multiply with
			 *
			 * @return A reference to this after multiplying it with the other color
			 *
			 * @note This function is equivalent to calling this = this * Other
			 *
			 */
			TColorRGBA& operator*=(const TColorRGBA& Other);

			/**
			 * @brief Converts the color from a COLORREF value
			 *
			 * This function sets the red, green and blue components of the color from the given COLORREF value.
			 *
			 * @param uColor The COLORREF value to convert from
			 *
			 * @note The alpha component is not modified
			 *
			 */
			void FromCOLORREF(COLORREF uColor);

			/**
			 * @brief Converts the color to a COLORREF value
			 *
			 * This function returns a COLORREF value that is composed of the red, green and blue components of the color.
			 *
			 * @return The COLORREF value that represents the color
			 *
			 * @note The alpha component is ignored
			 *
			 */
			COLORREF ToCOLORREF() const;

			BYTE Red;	/**< The red component of the color */
			BYTE Green;	/**< The green component of the color */
			BYTE Blue;	/**< The blue component of the color */
			BYTE Alpha;	/**< The alpha component of the color */

		};

	}
}

#define ColorRGBA_AliceBlue				retro::core::TColorRGBA(0xfffff8f0)
#define ColorRGBA_AntiqueWhite			retro::core::TColorRGBA(0xffd7ebfa)	
#define ColorRGBA_Aqua					retro::core::TColorRGBA(0xffffff00)	
#define ColorRGBA_AquaMarine			retro::core::TColorRGBA(0xffd4ff7f)
#define ColorRGBA_Azure					retro::core::TColorRGBA(0xfffffff0)
#define ColorRGBA_Beige					retro::core::TColorRGBA(0xffdcf5f5)
#define ColorRGBA_Bisque				retro::core::TColorRGBA(0xffc4e4ff)
#define ColorRGBA_Black					retro::core::TColorRGBA(0xff000000)	
#define ColorRGBA_BlancheDalmond		retro::core::TColorRGBA(0xffcdebff)
#define ColorRGBA_Blue					retro::core::TColorRGBA(0xffff0000)
#define ColorRGBA_BlueViolet			retro::core::TColorRGBA(0xffe22b8a)
#define ColorRGBA_Brown					retro::core::TColorRGBA(0xff2a2aa5)	
#define ColorRGBA_BurlyWood				retro::core::TColorRGBA(0xff87b8de)	
#define ColorRGBA_CadetBlue				retro::core::TColorRGBA(0xffa09e5f)
#define ColorRGBA_Chartreuse			retro::core::TColorRGBA(0xff00ff7f)
#define ColorRGBA_Chocolate				retro::core::TColorRGBA(0xff1e69d2)
#define ColorRGBA_Coral					retro::core::TColorRGBA(0xff507fff)
#define ColorRGBA_CornFlowerBlue		retro::core::TColorRGBA(0xffed9564)
#define ColorRGBA_CornSilk				retro::core::TColorRGBA(0xffdcf8ff)
#define ColorRGBA_Crimson				retro::core::TColorRGBA(0xff3c14dc)
#define ColorRGBA_Cyan					retro::core::TColorRGBA(0xffffff00)	
#define ColorRGBA_DarkBlue				retro::core::TColorRGBA(0xff8b0000)
#define ColorRGBA_DarkCyan				retro::core::TColorRGBA(0xff8b8b00)
#define ColorRGBA_DarkGoldenRod			retro::core::TColorRGBA(0xff0b86b8)
#define ColorRGBA_DarkGray				retro::core::TColorRGBA(0xffa9a9a9)
#define ColorRGBA_DarkGreen				retro::core::TColorRGBA(0xff006400)
#define ColorRGBA_DarkKhaki				retro::core::TColorRGBA(0xff6bb7bd)	 
#define ColorRGBA_DarkMagenta			retro::core::TColorRGBA(0xff8b008b)
#define ColorRGBA_DarkOliveGreen		retro::core::TColorRGBA(0xff2f6b55)	 
#define ColorRGBA_DarkOrange			retro::core::TColorRGBA(0xff008cff)
#define ColorRGBA_DarkOrchid			retro::core::TColorRGBA(0xffcc3299)
#define ColorRGBA_DarkRed				retro::core::TColorRGBA(0xff00008b)
#define ColorRGBA_DarkSalmon			retro::core::TColorRGBA(0xff7a96e9)
#define ColorRGBA_DarkSeaGreen			retro::core::TColorRGBA(0xff8fbc8f)	 
#define ColorRGBA_DarkSlateBlue			retro::core::TColorRGBA(0xff8b3d48)
#define ColorRGBA_DarkSlateGray			retro::core::TColorRGBA(0xff4f4f2f) 
#define ColorRGBA_DarkTurquoise			retro::core::TColorRGBA(0xffd1ce00) 
#define ColorRGBA_DarkViolet			retro::core::TColorRGBA(0xffd30094) 
#define ColorRGBA_DeepPink				retro::core::TColorRGBA(0xff9314ff) 
#define ColorRGBA_DeepSkyBlue			retro::core::TColorRGBA(0xffffbf00) 
#define ColorRGBA_DimGray				retro::core::TColorRGBA(0xff696969) 
#define ColorRGBA_DodgerBlue			retro::core::TColorRGBA(0xffff901e)
#define ColorRGBA_FireBrick				retro::core::TColorRGBA(0xff2222b2)
#define ColorRGBA_FloralWhite			retro::core::TColorRGBA(0xfff0faff)
#define ColorRGBA_ForestGreen			retro::core::TColorRGBA(0xff228b22)
#define ColorRGBA_Fuchsia				retro::core::TColorRGBA(0xffff00ff)
#define ColorRGBA_GainsBoro				retro::core::TColorRGBA(0xffdcdcdc)
#define ColorRGBA_GhostWhite			retro::core::TColorRGBA(0xfffff8f8)
#define ColorRGBA_Gold					retro::core::TColorRGBA(0xff00d7ff)
#define ColorRGBA_GoldenRod				retro::core::TColorRGBA(0xff20a5da)
#define ColorRGBA_Gray					retro::core::TColorRGBA(0xff808080)
#define ColorRGBA_Green					retro::core::TColorRGBA(0xff008000)
#define	ColorRGBA_GreenYellow			retro::core::TColorRGBA(0xff2fffad)
#define ColorRGBA_HoneyDew				retro::core::TColorRGBA(0xfff0fff0)
#define ColorRGBA_HotPink				retro::core::TColorRGBA(0xffb469ff)
#define ColorRGBA_IndianRed				retro::core::TColorRGBA(0xff5c5ccd) 
#define ColorRGBA_Indigo				retro::core::TColorRGBA(0xff82004b) 
#define ColorRGBA_Ivory					retro::core::TColorRGBA(0xfff0ffff)
#define ColorRGBA_Khaki					retro::core::TColorRGBA(0xff8ce6f0)
#define ColorRGBA_Lavender				retro::core::TColorRGBA(0xfffae6e6)
#define ColorRGBA_LavenderBlush			retro::core::TColorRGBA(0xfff5f0ff)
#define ColorRGBA_LawnGreen				retro::core::TColorRGBA(0xff00fc7c)
#define ColorRGBA_LemonChiffon			retro::core::TColorRGBA(0xffcdfaff)
#define ColorRGBA_LightBlue				retro::core::TColorRGBA(0xffe6d8ad)
#define ColorRGBA_LightCoral			retro::core::TColorRGBA(0xff8080f0)
#define ColorRGBA_LightCyan				retro::core::TColorRGBA(0xffffffe0)
#define ColorRGBA_LightGoldenRodYellow	retro::core::TColorRGBA(0xffd2fafa)
#define ColorRGBA_LightGray				retro::core::TColorRGBA(0xffd3d3d3)
#define ColorRGBA_LightGreen			retro::core::TColorRGBA(0xff90ee90)
#define ColorRGBA_LightPink				retro::core::TColorRGBA(0xffc1b6ff)
#define ColorRGBA_LightSalmon			retro::core::TColorRGBA(0xff7aa0ff)
#define ColorRGBA_LightSeaGreen			retro::core::TColorRGBA(0xffaab220)
#define ColorRGBA_LightSkyBlue			retro::core::TColorRGBA(0xffface87)
#define ColorRGBA_LightSlateGray		retro::core::TColorRGBA(0xff998877)
#define ColorRGBA_LightSteelBlue		retro::core::TColorRGBA(0xffdec4b0)
#define ColorRGBA_LightYellow			retro::core::TColorRGBA(0xffe0ffff)
#define ColorRGBA_Lime					retro::core::TColorRGBA(0xff00ff00)
#define ColorRGBA_LimeGreen				retro::core::TColorRGBA(0xff32cd32)
#define ColorRGBA_Linen					retro::core::TColorRGBA(0xffe6f0fa)
#define ColorRGBA_Magenta				retro::core::TColorRGBA(0xffff00ff)
#define ColorRGBA_Maroon				retro::core::TColorRGBA(0xff000080)
#define ColorRGBA_MediumAquaMarine		retro::core::TColorRGBA(0xffaacd66)
#define ColorRGBA_MediumBlue			retro::core::TColorRGBA(0xffcd0000)
#define ColorRGBA_MediumOrchid			retro::core::TColorRGBA(0xffd355ba)
#define ColorRGBA_MediumPurple			retro::core::TColorRGBA(0xffdb7093)
#define ColorRGBA_MediumSeaGreen		retro::core::TColorRGBA(0xff71b33c)
#define ColorRGBA_MediumSlateBlue		retro::core::TColorRGBA(0xffee687b)
#define ColorRGBA_MediumSpringGreen		retro::core::TColorRGBA(0xff9afa00)
#define ColorRGBA_MediumTurquoise		retro::core::TColorRGBA(0xffccd148)
#define ColorRGBA_MediumVioletRed		retro::core::TColorRGBA(0xff8515c7)
#define ColorRGBA_MidnightBlue			retro::core::TColorRGBA(0xff701919)
#define ColorRGBA_MintCream				retro::core::TColorRGBA(0xfffafff5)
#define ColorRGBA_MistyRose				retro::core::TColorRGBA(0xffe1e4ff)
#define ColorRGBA_Moccasin				retro::core::TColorRGBA(0xffb5e4ff)
#define ColorRGBA_NavajoWhite			retro::core::TColorRGBA(0xffaddeff)
#define ColorRGBA_Navy					retro::core::TColorRGBA(0xff800000) 
#define ColorRGBA_OldLace				retro::core::TColorRGBA(0xffe6f5fd) 
#define ColorRGBA_Olive					retro::core::TColorRGBA(0xff008080) 
#define ColorRGBA_OliveDrab				retro::core::TColorRGBA(0xff238e6b) 
#define ColorRGBA_Orange				retro::core::TColorRGBA(0xff00a5ff) 
#define ColorRGBA_OrangeRed				retro::core::TColorRGBA(0xff0045ff) 
#define ColorRGBA_Orchid				retro::core::TColorRGBA(0xffd670da) 
#define ColorRGBA_PaleGoldenRod			retro::core::TColorRGBA(0xffaae8ee)
#define ColorRGBA_PaleGreen				retro::core::TColorRGBA(0xff98fb98)
#define ColorRGBA_PaleTurquoise			retro::core::TColorRGBA(0xffeeeeaf)
#define ColorRGBA_PaleVioletRed			retro::core::TColorRGBA(0xff9370db)
#define ColorRGBA_PapayaWhip			retro::core::TColorRGBA(0xffd5efff)
#define ColorRGBA_PeachPuff				retro::core::TColorRGBA(0xffb9daff)
#define ColorRGBA_Peru					retro::core::TColorRGBA(0xff3f85cd)
#define ColorRGBA_Pink					retro::core::TColorRGBA(0xffcbc0ff)
#define ColorRGBA_Plum					retro::core::TColorRGBA(0xffdda0dd)
#define ColorRGBA_PowderBlue			retro::core::TColorRGBA(0xffe6e0b0)
#define ColorRGBA_Purple				retro::core::TColorRGBA(0xff800080)
#define ColorRGBA_RebeccaPurple			retro::core::TColorRGBA(0xff993366)
#define ColorRGBA_Red					retro::core::TColorRGBA(0xff0000ff)
#define ColorRGBA_RosyBrown				retro::core::TColorRGBA(0xff8f8fbc)
#define ColorRGBA_RoyalBlue				retro::core::TColorRGBA(0xffe16941)
#define ColorRGBA_SaddleBrown			retro::core::TColorRGBA(0xff13458b)
#define ColorRGBA_Salmon				retro::core::TColorRGBA(0xff7280fa)
#define ColorRGBA_SandyBrown			retro::core::TColorRGBA(0xff60a4f4)
#define ColorRGBA_SeaGreen				retro::core::TColorRGBA(0xff578b2e)
#define ColorRGBA_SeaShell				retro::core::TColorRGBA(0xffeef5ff)
#define ColorRGBA_Sienna				retro::core::TColorRGBA(0xff2d52a0)
#define ColorRGBA_Silver				retro::core::TColorRGBA(0xffc0c0c0)
#define ColorRGBA_SkyBlue				retro::core::TColorRGBA(0xffebce87)
#define ColorRGBA_SlateBlue				retro::core::TColorRGBA(0xffcd5a6a)
#define ColorRGBA_SlateGray				retro::core::TColorRGBA(0xff908070)
#define ColorRGBA_Snow					retro::core::TColorRGBA(0xfffafaff)
#define ColorRGBA_SpringGreen			retro::core::TColorRGBA(0xff7fff00)
#define ColorRGBA_SteelBlue				retro::core::TColorRGBA(0xffb48246)
#define ColorRGBA_Tan					retro::core::TColorRGBA(0xff8cb4d2)
#define ColorRGBA_Teal					retro::core::TColorRGBA(0xff808000)
#define ColorRGBA_Thistle				retro::core::TColorRGBA(0xffd8bfd8)
#define ColorRGBA_Tomato				retro::core::TColorRGBA(0xff4763ff)
#define ColorRGBA_Transparent			retro::core::TColorRGBA(0x00000000, ALPHA_TRANSPARENT)
#define ColorRGBA_Turquoise				retro::core::TColorRGBA(0xffd0e040)
#define ColorRGBA_Violet				retro::core::TColorRGBA(0xffee82ee)
#define ColorRGBA_Wheat					retro::core::TColorRGBA(0xffb3def5)
#define ColorRGBA_White					retro::core::TColorRGBA(0xffffffff)
#define ColorRGBA_WhiteSmoke			retro::core::TColorRGBA(0xfff5f5f5)
#define ColorRGBA_Yellow				retro::core::TColorRGBA(0xff00ffff)
#define ColorRGBA_YellowGreen			retro::core::TColorRGBA(0xff32cd9a)
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
		 * @brief Extension class for MFC CObject
		 *
		 */
		class AFX_EXT_API CObjectEx : public CObject
		{
			public:

				/**
				 * @brief Generates the C++ header code necessary for a CObject-derived 
				 * class that can be serialized
				 *
				 */
				DECLARE_DYNAMIC(CObjectEx);

			protected:

				/**
				 * @brief Protected default constructor
				 *
				 */
				CObjectEx();

			public:

				/**
				 * @brief Destructor
				 *
				 */
				virtual ~CObjectEx();

			private:

				/**
				 * @brief Deleted copy constructor
				 *
				 */
				CObjectEx(const CObjectEx& ObjectEx) = delete;

				/**
				 * @brief Deleted copy assignment
				 *
				 */
				void operator=(const CObjectEx& ObjectEx) = delete;

			public:

				/**
				 * @brief Grabs the object. Increments the reference counter by one
				 *
				 */
				void AddRef() const;

				/**
				 *  @brief Drops the object. Decrements the reference counter by one
				 *
				 *  @return True if the object is done
				 *
				 */
				BOOL Release() const;

				/**
				 *  @brief Get the reference count
				 *
				 *  @return The reference count
				 *
				 */
				ULONGLONG GetReferenceCounter() const;

			public:

#ifdef _DEBUG
				/**
				 * @brief Produces a diagnostic dump of the object
				 *
				 * @param dc The diagnostic dump context for dumping
				 *
				 */
				void Dump(CDumpContext& dc) const override;

				/**
				 * @brief Validates the object's integrity
				 *
				 */
				void AssertValid() const override;
#endif

			private:

				/**
				 * Member data
				 */
				volatile mutable ULONGLONG m_uReferenceCounter;

		};

	}

}
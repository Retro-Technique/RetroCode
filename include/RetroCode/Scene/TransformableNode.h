/**
 *
 * Retro Code
 *
 * MIT License
 *
 * Copyright(c) 2014-2023 Retro Technique
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
	namespace scene
	{

		class AFX_EXT_API CTransformableNode : public CNode
		{
#pragma region Constructors

		public:

			DECLARE_SERIAL(CTransformableNode);

		protected:

			CTransformableNode();

		public:

			virtual ~CTransformableNode();

		private:

			CTransformableNode(const CTransformableNode& Node) = delete;
			void operator=(const CTransformableNode& Node) = delete;

#pragma endregion
#pragma region Attributes

		private:

			D2D1_POINT_2F	m_vOrigin;
			D2D1_SIZE_F		m_vPosition;
			FLOAT			m_fRotation;
			D2D1_SIZE_F		m_vScale;

		public:

			void SetPosition(FLOAT fX, FLOAT fY);
			void SetPosition(const D2D1_SIZE_F& vPosition);
			void SetRotation(FLOAT fAngle);
			void SetScale(FLOAT fFactorX, FLOAT fFactorY);
			void SetScale(const D2D1_SIZE_F& vFactor);
			void SetOrigin(FLOAT fX, FLOAT fY);
			void SetOrigin(const D2D1_POINT_2F& vOrigin);
			void Move(FLOAT fOffsetX, FLOAT fOffsetY);
			void Move(const D2D1_SIZE_F& vOffset);
			void Rotate(FLOAT fAngle);
			void Scale(FLOAT fFactorX, FLOAT fFactorY);
			void Scale(const D2D1_SIZE_F& vFactor);
			const D2D1_SIZE_F& GetPosition() const;
			D2D1_POINT_2F GetWorldPosition() const;
			FLOAT GetRotation() const;
			const D2D1_SIZE_F& GetScale() const;
			const D2D1_POINT_2F& GetOrigin() const;
			D2D1::Matrix3x2F GetWorld3x2Matrix() const;

#pragma endregion
#pragma region Overridables

		public:

			D2D1::Matrix3x2F Get3x2Matrix() const override;
			void OnDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const override;
			void Serialize(CArchive& ar) override;
#ifdef _DEBUG
			void Dump(CDumpContext& dc) const override;
			void AssertValid() const override;
#endif

#pragma endregion
			
		};

	}
}
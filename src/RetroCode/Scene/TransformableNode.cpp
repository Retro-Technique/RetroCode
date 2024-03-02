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

#include "pch.h"

namespace retro
{
	namespace scene
	{

		IMPLEMENT_SERIAL(CTransformableNode, CNode, 1);

		CTransformableNode::CTransformableNode()
			: m_vScale(D2D1::SizeF(1.f, 1.f))
			, m_fRotation(0.f)
			, m_vPosition(D2D1::SizeF())
			, m_vOrigin(D2D1::Point2F())
		{

		}

		CTransformableNode::~CTransformableNode()
		{

		}

		void CTransformableNode::SetPosition(FLOAT fX, FLOAT fY)
		{
			m_vPosition.width = fX;
			m_vPosition.height = fY;
		}

		void CTransformableNode::SetPosition(const D2D1_SIZE_F& vPosition)
		{
			SetPosition(vPosition.width, vPosition.height);
		}

		void CTransformableNode::SetRotation(FLOAT fAngle)
		{
			m_fRotation = fmodf(fAngle, 360.f);
			if (m_fRotation < 0)
			{
				m_fRotation += 360.f;
			}
		}

		void CTransformableNode::SetScale(FLOAT fFactorX, FLOAT fFactorY)
		{
			m_vScale.width = fFactorX;
			m_vScale.height = fFactorY;
		}

		void CTransformableNode::SetScale(const D2D1_SIZE_F& vFactor)
		{
			SetScale(vFactor.width, vFactor.height);
		}

		void CTransformableNode::SetOrigin(FLOAT fX, FLOAT fY)
		{
			m_vOrigin.x = fX;
			m_vOrigin.y = fY;
		}

		void CTransformableNode::SetOrigin(const D2D1_POINT_2F& vOrigin)
		{
			SetOrigin(vOrigin.x, vOrigin.y);
		}

		void CTransformableNode::Move(FLOAT fOffsetX, FLOAT fOffsetY)
		{
			SetPosition(m_vPosition.width + fOffsetX, m_vPosition.height + fOffsetY);
		}

		void CTransformableNode::Move(const D2D1_SIZE_F& vOffset)
		{
			Move(vOffset.width, vOffset.height);
		}

		void CTransformableNode::Rotate(FLOAT fAngle)
		{
			SetRotation(m_fRotation + fAngle);
		}

		void CTransformableNode::Scale(FLOAT fFactorX, FLOAT fFactorY)
		{
			SetScale(m_vScale.width * fFactorX, m_vScale.height * fFactorY);
		}

		void CTransformableNode::Scale(const D2D1_SIZE_F& vFactor)
		{
			SetScale(m_vScale.width * vFactor.width, m_vScale.height * vFactor.height);
		}

		const D2D1_SIZE_F& CTransformableNode::GetPosition() const
		{
			return m_vPosition;
		}

		D2D1_POINT_2F CTransformableNode::GetWorldPosition() const
		{
			return D2D1_POINT_2F() * GetWorld3x2Matrix();
		}

		FLOAT CTransformableNode::GetRotation() const
		{
			return m_fRotation;
		}

		const D2D1_SIZE_F& CTransformableNode::GetScale() const
		{
			return m_vScale;
		}

		const D2D1_POINT_2F& CTransformableNode::GetOrigin() const
		{
			return m_vOrigin;
		}

		D2D1::Matrix3x2F CTransformableNode::Get3x2Matrix() const
		{
			const D2D1::Matrix3x2F mScale = D2D1::Matrix3x2F::Scale(m_vScale, m_vOrigin);
			const D2D1::Matrix3x2F mRotation = D2D1::Matrix3x2F::Rotation(m_fRotation, m_vOrigin);
			const D2D1::Matrix3x2F mTranslate = D2D1::Matrix3x2F::Translation(m_vPosition);

			return mScale * mRotation * mTranslate;
		}

		D2D1::Matrix3x2F CTransformableNode::GetWorld3x2Matrix() const
		{
			D2D1::Matrix3x2F mMatrix = D2D1::Matrix3x2F::Identity();
			
			for (const CNode* pNode = this; pNode != NULL; pNode = pNode->GetParent())
			{
				mMatrix = pNode->Get3x2Matrix() * mMatrix;
			}

			return mMatrix;
		}

		void CTransformableNode::OnDraw(CSceneView* pView, CHwndRenderTarget* pRenderTarget) const
		{
			ASSERT(pView);
			ASSERT_VALID(pView);
			ASSERT(pRenderTarget);
			ASSERT_VALID(pRenderTarget);

			pView->PushMatrix();
			pView->MultMatrix(Get3x2Matrix());

			CNode::OnDraw(pView, pRenderTarget);

			pView->PopMatrix();
		}

		void CTransformableNode::Serialize(CArchive& ar)
		{
			CNode::Serialize(ar);

			if (ar.IsStoring())
			{
				ar << m_vScale.width << m_vScale.height << m_fRotation << m_vPosition.width << m_vPosition.height;
			}
			else
			{
				ar >> m_vScale.width >> m_vScale.height >> m_fRotation >> m_vPosition.width >> m_vPosition.height;
			}
		}

#ifdef _DEBUG

		void CTransformableNode::Dump(CDumpContext& dc) const
		{
			CNode::Dump(dc);

			dc << _T("Position: (") << m_vPosition.width << _T(";") << m_vPosition.height << _T(")");
			dc << _T("Rotation: ") << m_fRotation;
			dc << _T("Scale: (") << m_vScale.width << _T(";") << m_vScale.height << _T(")");
			dc << _T("Origin: (") << m_vOrigin.x << _T(";") << m_vOrigin.y << _T(")");
		}

		void CTransformableNode::AssertValid() const
		{
			CNode::AssertValid();

			ASSERT(m_fRotation >= 0.f);
			ASSERT(m_fRotation <= 360.f);
		}

#endif

	}
}
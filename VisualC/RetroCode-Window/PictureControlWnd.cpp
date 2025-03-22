/**
 *
 * Retro Code
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 Retro Technique
 *
 * This software is a computer program whose purpose is to provide
 * minimalist "C with classes" functionalities.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#include "pch.h"

namespace retro::wnd
{

#pragma region Constructors

	IMPLEMENT_DYNAMIC(CPictureControlWnd, CStatic)

	CPictureControlWnd::CPictureControlWnd(UINT uBitmapResourceID)
		: m_uBitmapResourceID(uBitmapResourceID)
	{

	}

	CPictureControlWnd::~CPictureControlWnd()
	{

	}

#pragma endregion
#pragma region Overridables

	void CPictureControlWnd::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		CBitmap Img;

		if (!Img.LoadBitmap(m_uBitmapResourceID))
		{
			return;
		}

		BITMAP bmp;
		if (const INT nRet = Img.GetBitmap(&bmp); nRet == 0)
		{
			return;
		}

		CSize szDestination;
		CPoint ptDestination;
		const CSize szBitmap = { bmp.bmWidth, bmp.bmHeight };

		CalcLayout(lpDrawItemStruct, szBitmap, ptDestination, szDestination);

		DrawPicture(lpDrawItemStruct, Img, szBitmap, ptDestination, szDestination);
	}

#pragma endregion
#pragma region Implementations

	void CPictureControlWnd::CalcLayout(LPDRAWITEMSTRUCT lpDrawItemStruct, const CSize& szBitmap, CPoint& ptDestination, CSize& szDestination)
	{
		ASSERT_POINTER(lpDrawItemStruct, sizeof(LPDRAWITEMSTRUCT));

		const CSize szControl = { lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom };

		if (szBitmap.cx * szControl.cy > szControl.cx * szBitmap.cy)
		{
			szDestination.cx = szControl.cx;
			szDestination.cy = MulDiv(szDestination.cx, szBitmap.cy, szBitmap.cx);
		}
		else
		{
			szDestination.cy = szControl.cy;
			szDestination.cx = MulDiv(szDestination.cy, szBitmap.cx, szBitmap.cy);
		}

		ptDestination.y = (szControl.cy - szDestination.cy) / 2;
		ptDestination.x = (szControl.cx - szDestination.cx) / 2;
	}

	void CPictureControlWnd::DrawPicture(LPDRAWITEMSTRUCT lpDrawItemStruct, const CBitmap& Bitmap, const CSize& szBitmap, const CPoint& ptDestination, const CSize& szDestination)
	{
		ASSERT_POINTER(lpDrawItemStruct, sizeof(LPDRAWITEMSTRUCT));

		Gdiplus::Graphics gfx(lpDrawItemStruct->hDC);
		Gdiplus::Bitmap bitmap(Bitmap, NULL);
		Gdiplus::Rect destRect(ptDestination.x, ptDestination.y, szDestination.cx, szDestination.cy);
		Gdiplus::Rect srcRect(0, 0, szBitmap.cx, szBitmap.cy);

		gfx.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBilinear);
		gfx.DrawImage(&bitmap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel);
	}

#pragma endregion
#pragma region Messages

	BEGIN_MESSAGE_MAP(CPictureControlWnd, CStatic)
	END_MESSAGE_MAP()

#pragma endregion

}
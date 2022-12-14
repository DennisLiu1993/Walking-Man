//Eric_20200212A_修改: 軸控面板相關燈號。
#include "pch.h"
#include "Light.h"


CLight::CLight()
{
	m_bmpGreenLight_On.LoadBitmap (IDB_BITMAP_GREENLIGHT_ON);
	m_bmpGreenLight_Off.LoadBitmap (IDB_BITMAP_GREENLIGHT_OFF);
	m_bmpRedLight_On.LoadBitmap (IDB_BITMAP_REDLIGHT_ON);
	m_bmpRedLight_Off.LoadBitmap (IDB_BITMAP_REDLIGHT_OFF);

	m_iColor = 0;
	m_bLight = TRUE;
}

CLight::~CLight()
{
}

void CLight::Init (CWnd* pwndStatic)
{
	if (!pwndStatic)
		return;

	DrawBitmap (pwndStatic);

}

void CLight::SetLightColor (int iColor, CWnd* pwndStatic)
{
	m_iColor = iColor;

	DrawBitmap (pwndStatic);
}

void CLight::SetLight (BOOL bLight, CWnd* pwndStatic)
{
	m_bLight = bLight;

	DrawBitmap (pwndStatic);
}

HBITMAP CLight::CopyBitmap(HBITMAP hSourceHbitmap)
{
	CDC sourceDC;
	CDC destDC;
	sourceDC.CreateCompatibleDC(NULL);
	destDC.CreateCompatibleDC(NULL);

	//The bitmap information.
	BITMAP bm = {0};

	//Get the bitmap information.
	::GetObject(hSourceHbitmap, sizeof(bm), &bm);

	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), bm.bmWidth, bm.bmHeight);

	HBITMAP hbmOldSource = (HBITMAP)::SelectObject(sourceDC.m_hDC, hSourceHbitmap);
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject(destDC.m_hDC, hbmResult);
	destDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &sourceDC, 0, 0, SRCCOPY );

	// Restore DCs
	::SelectObject(sourceDC.m_hDC, hbmOldSource);
	::SelectObject(destDC.m_hDC, hbmOldDest);
	::DeleteObject(sourceDC.m_hDC);
	::DeleteObject(destDC.m_hDC);

	return hbmResult;
}

BOOL CLight::DrawBitmap (CWnd* pwndStatic)
{
	if (!pwndStatic)
		return FALSE;

	CRect Rect;
	CStatic* pstaticPic = NULL;
	CPen penFrame;
	CPen* ppenOld = NULL;

	pstaticPic = ((CStatic*)pwndStatic);

	if (!pstaticPic)
		return FALSE;

	pstaticPic->GetClientRect (&Rect);

	CDC* pdcPic = pstaticPic->GetDC();

	CBitmap* pbitmap = NULL;
	if (m_bLight)
	{
		if (0 == m_iColor)
			pbitmap = &m_bmpRedLight_On;
		else if (1 == m_iColor)
			pbitmap = &m_bmpGreenLight_On;
	}
	else
	{
		if (0 == m_iColor)
			pbitmap = &m_bmpRedLight_Off;
		else if (1 == m_iColor)
			pbitmap = &m_bmpGreenLight_Off;
	}

	BITMAP bmp;
	pbitmap->GetBitmap(&bmp);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pdcPic);
	dcMem.SelectObject(pbitmap);
 
	CDC dc;
	dc.CreateCompatibleDC(pdcPic);

	CBitmap bmpbuf;                    //bmpbuf是要放入控件中的Bitmap 
	bmpbuf.CreateCompatibleBitmap(pdcPic, Rect.Width(), Rect.Height());

	CBitmap* pbmpPicOld = dc.SelectObject (&bmpbuf);

	//填入背景色
	dc.FillSolidRect (Rect, RGB (240, 240, 240));
	//dc.SelectStockObject(NULL_BRUSH);

	//將圖畫至dc上
	dc.TransparentBlt (Rect.left, Rect.top, Rect.Width(), Rect.Height(), &dcMem, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB (0, 128, 0));

	//將圖貼至dc上
	((CStatic*)pwndStatic)->SetBitmap((HBITMAP)bmpbuf);

	dc.SelectObject(pbmpPicOld);

	pstaticPic->ReleaseDC(pdcPic);
	dcMem.DeleteDC();
	dc.DeleteDC();

	//更新畫面
	((CStatic*)pwndStatic)->RedrawWindow ();

	return TRUE;
}

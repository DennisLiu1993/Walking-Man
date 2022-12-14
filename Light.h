//Eric_20200212A_修改: 軸控面板相關燈號。
#pragma once
#include "resource.h"
#include "afxwin.h"

#define LIGHT_GREEN_ON		1
#define LIGHT_GREEN_OFF		2
#define LIGHT_RED_ON		3
#define LIGHT_RED_OFF		4
#define LIGHT_INDEX_MAX		4		

class CLight
{
public:
	CLight();
	~CLight();
public:
	void	Init (CWnd* pwndStatic);							//初始化
	void	SetLightColor (int iColor, CWnd* pwndStatic);		//設定
	void	SetLight (BOOL bLight, CWnd* pwndStatic);			//設定燈號狀態
	CBitmap	m_bmpGreenLight_On;
	CBitmap	m_bmpGreenLight_Off;
	CBitmap	m_bmpRedLight_On;
	CBitmap	m_bmpRedLight_Off;
	int		m_iColor;											//燈色 0: Red, 1: Green.
	BOOL	m_bLight;											//燈號狀態
	BOOL	DrawBitmap (CWnd* pwndStatic);
	HBITMAP CopyBitmap (HBITMAP hbmpSource);
};

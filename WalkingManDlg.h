
// WalkingManDlg.h : header file
//

#pragma once
#include "Light.h"
#define GRID_NUM 16

// CWalkingManDlg dialog
class CWalkingManDlg : public CDialogEx
{
// Construction
public:
	CWalkingManDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WALKINGMAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CLight m_light1;
	CStatic m_static[GRID_NUM][GRID_NUM];
	CLight m_light[GRID_NUM][GRID_NUM];
	BOOL m_bOn[GRID_NUM][GRID_NUM];

	void SetLight ();
	afx_msg void OnStnClickedStaticLight1 ();
	CComboBox m_comboPage;
	afx_msg void OnCbnSelchangeComboPage ();
	int m_iPage;
	afx_msg void OnTimer (UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart ();
};

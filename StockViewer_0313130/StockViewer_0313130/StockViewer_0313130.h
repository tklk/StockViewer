
// StockViewer_0313130.h : StockViewer_0313130 ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CStockViewer_0313130App:
// �аѾ\��@�����O�� StockViewer_0313130.cpp
//

class CStockViewer_0313130App : public CWinApp
{
public:
	CStockViewer_0313130App();


// �мg
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �{���X��@
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStockViewer_0313130App theApp;

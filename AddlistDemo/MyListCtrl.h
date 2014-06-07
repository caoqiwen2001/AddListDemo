#pragma once
#include "afxcmn.h"

class CMyListCtrl :public CListCtrl
{
public:
	CMyListCtrl(void);
 virtual BOOL  OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) ;
	~CMyListCtrl(void);
// 	DECLARE_MESSAGE_MAP()
// 	afx_msg void OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

#include "StdAfx.h"
#include "MyListCtrl.h"
#include "resource.h"
CMyListCtrl::CMyListCtrl(void)
{
}

CMyListCtrl::~CMyListCtrl(void)
{

}
BOOL CMyListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	HD_NOTIFY   *pHDN = (HD_NOTIFY*)lParam;

	if((pHDN->hdr.code == HDN_BEGINTRACKW || pHDN->hdr.code == HDN_BEGINTRACKA)
		&& pHDN->iItem == 0)            // Prevent only first (col# 0) from resizing
	{
		*pResult = TRUE;                // disable tracking
		return TRUE;                    // Processed message
	}

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}
// BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
//     ON_NOTIFY(HDN_BEGINTRACKW|HDN_BEGINTRACKA,IDC_LIST1,OnNotify )
	//END_MESSAGE_MAP()
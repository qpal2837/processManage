#pragma once

#include <vector>
using namespace std;
// CMyTabCtrl
class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	vector<CDialog*> m_Dlgs;

public:
	VOID InsertTabItem(int index, LPCWSTR TabName, CDialog* Dialog, INT Id);

	VOID ShowTab(int index);

	VOID InsertTabItems(int count, ...);
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropFiles(HDROP hDropInfo);

};




// SockSeverDlg.h: 헤더 파일
//
#include "MySocket.h"

#pragma once


// CSockSeverDlg 대화 상자
class CSockSeverDlg : public CDialogEx
{
// 생성입니다.
public:
	CSockSeverDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void OnAccept();
	void OnReceive();
	void OnSend();
	void OnConnect();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKSEVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CString m_Address_str;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnListen();
	afx_msg void OnBnClickedBtnSend();

	CListBox m_ctlRecv;
	CString m_strMessage;
	int Server_Chack = 0;

	CMySocket m_sListenSocket;
	CMySocket m_sConnectSocket;
	BOOL	m_bConnected;//끊어졌는지 않끊어졌는지 판단용
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClose();
	CIPAddressCtrl m_IPControl;
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnConnect3();
	CString m_strNICK;
	afx_msg void OnBnClickedBtnConnect4();
	CString m_strMyNick;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush		brh;
};

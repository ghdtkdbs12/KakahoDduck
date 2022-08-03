// MySocket.cpp: 구현 파일
//

#include "pch.h"
#include "SockSever.h"
#include "MySocket.h"
#include "SockSeverDlg.h"


// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 멤버 함수
void CMySocket::OnAccept(int nErrorCode)
{
	if (nErrorCode == 0)
		((CSockSeverDlg*)m_pWnd)->OnAccept();
}

void CMySocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)
		((CSockSeverDlg*)m_pWnd)->OnReceive();
}

void CMySocket::OnSend(int nErrorCode)
{
	if (nErrorCode == 0)
		((CSockSeverDlg*)m_pWnd)->OnSend();
}

void CMySocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		((CSockSeverDlg*)m_pWnd)->OnConnect();
	}
}


// SockSeverDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SockSever.h"
#include "SockSeverDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSockSeverDlg 대화 상자



CSockSeverDlg::CSockSeverDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOCKSEVER_DIALOG, pParent)
	, m_strMessage(_T(""))
	, m_strNICK(_T(""))
	, m_strMyNick(_T(""))
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CSockSeverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LREVD, m_ctlRecv);
	DDX_Text(pDX, IDC_EMSG, m_strMessage);
	DDX_Control(pDX, IDC_IPADDRESS, m_IPControl);
	DDX_Text(pDX, IDC_NICK_NAME, m_strNICK);
	DDX_Text(pDX, IDC_MY_NICK_NAME, m_strMyNick);
}

BEGIN_MESSAGE_MAP(CSockSeverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LISTEN, &CSockSeverDlg::OnBnClickedBtnListen)
	ON_BN_CLICKED(IDC_BTN_SEND, &CSockSeverDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CSockSeverDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CSockSeverDlg::OnBnClickedBtnClose)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS, &CSockSeverDlg::OnIpnFieldchangedIpaddress)
	ON_BN_CLICKED(IDC_BTN_CONNECT3, &CSockSeverDlg::OnBnClickedBtnConnect3)
	ON_BN_CLICKED(IDC_BTN_CONNECT4, &CSockSeverDlg::OnBnClickedBtnConnect4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSockSeverDlg 메시지 처리기

BOOL CSockSeverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_sListenSocket.SetParent(this);
	m_sConnectSocket.SetParent(this);

	m_bConnected = FALSE;

	SetBackgroundColor(RGB(255, 255, 0));
	brh.CreateSolidBrush(RGB(155,187,212));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSockSeverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSockSeverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSockSeverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSockSeverDlg::OnIpnFieldchangedIpaddress(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BYTE Ip[4];
	m_IPControl.GetAddress(Ip[0], Ip[1], Ip[2], Ip[3]);

	CString str;
	m_Address_str.Format(_T("%d.%d.%d.%d"), Ip[0], Ip[1], Ip[2], Ip[3]);
	
	*pResult = 0;
}

void CSockSeverDlg::OnBnClickedBtnConnect()
{
	if (Server_Chack == 0)
	{
		if (m_Address_str == "")
		{
			m_ctlRecv.AddString("클라이언트에 접속하지 못하였습니다.");
		}
		else {
			m_sConnectSocket.Create();
			m_sConnectSocket.Connect(m_Address_str, 5000);
			SetDlgItemText(IDC_STATIC_CONNECTED_IP, m_Address_str);
			Server_Chack = 1;
		}
	}
	else
	{
		m_ctlRecv.AddString("*******현재 서버를 사용중 입니다*******");
	}


}



void CSockSeverDlg::OnBnClickedBtnListen()
{
	if (Server_Chack == 0)
	{
		m_sListenSocket.Create(5000);//소켓생성 + 바인딩 (5000)포트
		m_sListenSocket.Listen();
		Server_Chack = 1;
	}
	else
	{
		m_ctlRecv.AddString("*******현재 서버를 사용중 입니다*******");
	}

}


void CSockSeverDlg::OnBnClickedBtnSend()
{
	int iLen;
	int iSend;

	UpdateData(TRUE);

	if (m_strMessage != "")
	{
		iLen = m_strMessage.GetLength();
		iSend = m_sConnectSocket.Send(m_strMessage, iLen);

		if (iSend == SOCKET_ERROR)
		{
			m_ctlRecv.AddString("메세지를 보내지 못했습니다.");
		}
		else
		{
			if (m_strMyNick != "")
			{
				m_ctlRecv.AddString(m_strMyNick + " : " + m_strMessage);
			}
			else {
				m_ctlRecv.AddString("나 : " + m_strMessage);
			}
			
		}
	}
}

void CSockSeverDlg::OnAccept()
{
	if (!m_bConnected)//False 인경우
	{
		m_sListenSocket.Accept(m_sConnectSocket);
		m_bConnected = TRUE;

		m_ctlRecv.AddString("**********클라이언트가 접속했습니다.**********");
	}
}

void CSockSeverDlg::OnReceive()
{
	char* pBuf = new char[1025];
	int iBufSize = 1024;
	int iRcvd;
	CString strRcvd;

	iRcvd = m_sConnectSocket.Receive(pBuf, iBufSize);

	if (iRcvd == SOCKET_ERROR)
	{
		m_ctlRecv.AddString("메세지를 보내지 못했습니다.");
	}
	else
	{
		pBuf[iRcvd] = NULL;
		strRcvd = pBuf;
		if (m_strNICK != "")
		{
			m_ctlRecv.AddString(m_strNICK + " : " + strRcvd);
		}
		else {
			m_ctlRecv.AddString("상대방 : " + strRcvd);
		}
		
		UpdateData(FALSE);
	}
}

void CSockSeverDlg::OnSend()
{

}

void CSockSeverDlg::OnConnect()
{

}

void CSockSeverDlg::OnBnClickedBtnClose()
{
	m_sConnectSocket.Close();
	m_sListenSocket.Close();
	Server_Chack = 0;
}



BOOL CSockSeverDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
		else if (pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



void CSockSeverDlg::OnBnClickedBtnConnect3()
{
	UpdateData(TRUE);	
}


void CSockSeverDlg::OnBnClickedBtnConnect4()
{
	UpdateData(TRUE);
}


HBRUSH CSockSeverDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		if (pWnd->GetDlgCtrlID() == IDC_LREVD)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));

			return brh;
		}
	}

	// TODO:  여기서 DC의 특성을 변경합니다.
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

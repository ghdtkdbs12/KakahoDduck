#pragma once

// CMySocket 명령 대상

class CMySocket : public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();

	void SetParent(CDialog* pWnd)
	{
		m_pWnd = pWnd;
	}

protected:
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);

private:
	CDialog* m_pWnd;
protected:
	virtual void OnConnect(int nErrorCode);
};



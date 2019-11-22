#pragma once
#include <string>
inline namespace LChangeValueType
	{
//---------------char* to string
	inline	std::string get_stringfromchar(char *p)
		{
			return (std::string)p;
		}
	inline	std::string get_stringfromchar(const char *p)
		{
			return (std::string)p;
		}
//---------------string to char
       #define get_constcharfromstring(X) X.c_str()
       #define get_charfromstring(X) (char*)X.c_str()
//-----------------wchar to char warning:must delete []dst after use dst;
	inline	wchar_t * char_to_wchar(char *src  )
		{
			int iSize;
			wchar_t *dst =NULL;
			if (dst!=NULL)
			{
				delete[]dst;
				dst = NULL;
			}
			iSize = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0); 
			dst = new wchar_t[iSize]; 
			MultiByteToWideChar(CP_ACP, 0, src, -1, dst, iSize);
			return dst;
		}
//-----------------char to wchar warning:must delete []dst after use dst;
	inline	char * wchar_to_char(wchar_t *src)
		{
			int iSize;
			char *dst = NULL;
			if (dst != NULL)
			{
				delete[]dst;
				dst = NULL;
			}			
			iSize = WideCharToMultiByte(CP_ACP, 0, src, -1, NULL, 0, NULL, NULL); 
			dst = new char[iSize];
			WideCharToMultiByte(CP_ACP, 0, src, -1, dst, iSize, NULL, NULL);
			return dst;
		}
//-----------------------CString to string 
	inline	std::string cstring_to_string(CString *src)
		{
		  CStringA str = (CStringA)*src;
          return (std::string)((const char*)str);
		}
//----------------------string to CString
	inline	CString string_to_cstring(std::string *src)
		{
			std::string src1 = *src;
			CStringA str =(CStringA)src1.c_str();
			return (CString)str;
		}
//----------------------CString to charwarning:must delete []dst after use dst; 
	inline	char* cstring_to_char(CString *src)
		{
			CStringA str = (CStringA)*src;
			int len = str.GetLength();
			char* dst1 = new char[len+1];
			char *dst =(char*)((const char*) str);
			memcpy(dst1, dst, len+1);
			return dst1;
		}
//----------------------char to CString;
	inline	CString char_to_cstring(char* src)
		{
			return (CString)src;
		}
/*/---------------------------
CString to int  UNICODE  _wtoi(str);_wtof
int.float. to CString use Format;
-----------------------------*/
	}
namespace LSocket {
#include<WinSock2.h>
//#include <WS2tcpip.h>
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 1//��������stdafx.h�ĵ�һ���������°�ı���
#define READER_COUNT	1		// number of readers can be connected
#define RECV_DATA_MAX	10240
#define WM_SOCKET WM_USER+1//�Զ�����Ϣ
enum ServerOrClient
	{
		Client = 0,
	    Server = 1
	};

	class MySocket
	{
	public:
		MySocket::MySocket(int nSocketType = SOCK_STREAM, HWND hwnd=NULL)
		{
			m_socketype = SOCK_STREAM;
			m_nSendTimeout = 1000;//ms
			m_nRecvTimeout = 1000;
			m_nConnectTimeout = 2;//second
			m_socket = INVALID_SOCKET;
			m_hwnd = hwnd;
		}
		MySocket::~MySocket()
		{

			for (int i = 0; i < READER_COUNT; i++) {
				if (accept_socket[i] != INVALID_SOCKET) {
					closesocket(accept_socket[i]);
					accept_socket[i] = INVALID_SOCKET;
				}
			}

			if (m_socket != INVALID_SOCKET) {
				closesocket(m_socket);
				m_socket = INVALID_SOCKET;
			}
			WSACleanup();
		}

	private:
		SOCKET m_socket;
		int m_socketype;//------tcp udp;
		int m_nSendTimeout;
		int m_nRecvTimeout;
		int m_nConnectTimeout;
		HWND m_hwnd;
	public:
		SOCKET Get_SOCKET() { return m_socket; }
		SOCKET Get_AcceptSocket(int num) { return accept_socket[num]; }
		void Set_HWND(HWND h_wnd) { m_hwnd = h_wnd; }
		bool is_ready;//��ʼ�����
		bool is_connected;
		//----------------------��������
		SOCKET accept_socket[READER_COUNT];
		bool accept_socket_ready[READER_COUNT];

		//--------------------------------------------socket ��ʼ��
		void Socket_init()
		{
			WSAData data;
			WORD wVersionRequested = MAKEWORD(2, 0);
			if (!WSAStartup(wVersionRequested, &data))
			{
				m_socket = socket(AF_INET, m_socketype, 0);
				if (m_socket != INVALID_SOCKET)
				{
					if (::setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&m_nSendTimeout, sizeof(m_nSendTimeout)) == SOCKET_ERROR)
						return;
					if (::setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&m_nSendTimeout, sizeof(m_nSendTimeout)) == SOCKET_ERROR)
						return;

					int rcvbuf;
					int rcvbufsize = sizeof(int);

					if (getsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (char*)&rcvbuf, &rcvbufsize) != SOCKET_ERROR)
					{
						if (rcvbuf<65536)
							rcvbuf = 65536;
						setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (char*)&rcvbuf, rcvbufsize);
					}

					if (getsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char*)&rcvbuf, &rcvbufsize) != SOCKET_ERROR)
					{
						if (rcvbuf<65536)
							rcvbuf = 65536;
						setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char*)&rcvbuf, rcvbufsize);
					}
					is_ready = true;
					is_connected = false;
				}
			}
			else
			{
				is_ready = false;
			}
		}
		//--------------------------------------------------
		static UINT SrServerSocket_doAccept(LPVOID pParam) {
			MySocket *p = (MySocket*)pParam;
			static sockaddr_in dst[READER_COUNT];
			int size = sizeof(sockaddr_in);
			static int dst_len = sizeof(dst);
			SOCKET valsoc;
			SOCKET server = p->Get_SOCKET();
			for (int i = 0; i < READER_COUNT; i++) {
				// Wait for connection from a reader in blocking mode.
				valsoc = accept(server, (struct sockaddr *)&dst[i], &dst_len);
				//CString stradd = CString(inet_ntoa(dst[i].sin_addr));
		       // if (CString(inet_ntoa(dst[i].sin_addr)) == _T("192.168.3.10"))//10-----------�޸�2���ط�
					{
						p->accept_socket_ready[i] = true;
						p->accept_socket[i] = valsoc;//��ȡ���ӵ�socket��
						p->is_connected = true;
					}
				CString s;				
				s.Format(_T("%S:%d������"), inet_ntoa(dst[i].sin_addr), ntohs(dst[i].sin_port));
				MessageBox(0,s,_T(""),NULL);
			}
			return 0;
		}
		void m_connect(UINT nSocketPort = 6666, LPCTSTR lpszSocketAddress = NULL, ServerOrClient type = Client) {
			if (type == Client)//�ǿͻ���
			{
				char *p = "ok";
				int sendlen = LSend(p, 2);
				sendlen = LSend(p, 2);
				if (sendlen<0)
				{
					if (m_socket!=INVALID_SOCKET)
					{
						closesocket(m_socket);
						m_socket = INVALID_SOCKET;
					}
					Socket_init();
				}
				else
				{
					if (sendlen ==2)
					{
						return;
					}
				}
				if (!is_ready)
					return;
				const wchar_t *lpctStr = lpszSocketAddress;
				int iSize;
				char *dst = NULL;

				iSize = WideCharToMultiByte(CP_ACP, 0, lpctStr, -1, NULL, 0, NULL, NULL);
				dst = new char[iSize];
				WideCharToMultiByte(CP_ACP, 0, lpctStr, -1, dst, iSize, NULL, NULL);

				int ret;
				ULONG ul = 1;//���������ģʽ����ֹ���Ӳ��Ͽ���
				ret = ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul);
				if (ret == SOCKET_ERROR)
					return;


				sockaddr_in addr;
				addr.sin_family = AF_INET;
				addr.sin_port =htons(nSocketPort);
				addr.sin_addr.s_addr = inet_addr((const char*)dst);

			    ret = connect(m_socket, (const struct sockaddr*)&addr, sizeof(addr));
				delete[]dst;

				struct timeval timeout;
				fd_set r;
				FD_ZERO(&r);
				FD_SET(m_socket, &r);
				timeout.tv_sec = m_nConnectTimeout;
				timeout.tv_usec = 0;
				ret = select(0, 0, &r, 0, &timeout);
				if (ret <= 0)
				{
					//closesocket(m_socket);
					MessageBox(0,_T("���ӷ�����ʧ�ܣ�"), _T(""), 0);
					return;//���ӳ�ʱ
				}
				//���û�����ģʽ
				ULONG ul1 = 0;
				ret = ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul1);
				if (ret == SOCKET_ERROR)
					return;
				is_connected = true;
				if (m_hwnd != NULL)
				{
					WSAAsyncSelect(m_socket, m_hwnd, WM_SOCKET,FD_CLOSE );// FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT);
				}
			}
			else//�Ƿ�����
			{
				//----------��ʼ��������socket
				if (m_socket==INVALID_SOCKET)
				{
					Socket_init();
				}
				else
				{
					return;
				}

				if (!is_ready)
					return;


				struct sockaddr_in src;
				memset(&src, 0, sizeof(src));

				src.sin_port = htons(nSocketPort);
				src.sin_family = AF_INET;
				src.sin_addr.S_un.S_addr = INADDR_ANY;

			    bind(m_socket, (struct sockaddr *)&src, sizeof(src));
				listen(m_socket, 5);	// Maximum pending request is 5.


				// Create new thread to accept asynchronously.
				AfxBeginThread(SrServerSocket_doAccept, this, THREAD_PRIORITY_IDLE);
			}			
		}
		int LSend(const char*buf, int len) { return send(m_socket, buf, len, 0); }
		int LRecv( char*buf, int len) { return recv(m_socket, buf, len, 0); }
	};
}
namespace LCOMPORT {
	class MyComPort
	{
	public:
		MyComPort()
		{
			m_hComm = INVALID_HANDLE_VALUE;
		}
		~MyComPort()
		{
			CloseComm();
		}
		bool OpenComm(int comport)
		{
			CString strCommName;
			CString strErrInfo;

			strCommName.Format(_T("COM%d"), comport);

			m_hComm = ::CreateFile(strCommName,  /*Ҫ�򿪴�������*/
				GENERIC_READ | GENERIC_WRITE,  /*�������д*/
				0,  /*��ռ��ʽ*/
				NULL,  /*��ȫ����*/
				OPEN_EXISTING,  /*�򿪶����Ǵ���*/
				0, /*ͬ����ʽ*/
				NULL);  /*ģ����*/

			if (m_hComm == INVALID_HANDLE_VALUE)
			{
				strErrInfo.Format(_T("��COM%dʧ�ܣ�"), comport);
				AfxMessageBox(strErrInfo);
				return FALSE;
			}
			else
			{
				return TRUE;
			}
		}
		//�رմ��ں���
		void CloseComm()
		{
			if (m_hComm != INVALID_HANDLE_VALUE)
			{
				::CloseHandle(m_hComm);
				m_hComm = INVALID_HANDLE_VALUE;
			}
		}

		//���ô��ں���
		BOOL SetComm(int nBaudRate, int nParity, int nByteSize, int nStopBits)
		{
			DCB stDCB;
			memset(&stDCB, 0, sizeof(stDCB));
			if (!::GetCommState(m_hComm, &stDCB))  //��ȡ���ڵ�ǰ״̬����?
				return FALSE;
			stDCB.BaudRate = nBaudRate;  //������
			stDCB.fParity = 0;
			stDCB.Parity = nParity;      //��żУ��λ(NOPARITY��)
			stDCB.ByteSize = nByteSize;  //ÿ���ֽ���λ
			stDCB.StopBits = nStopBits;  //ֹͣλ(ONESTOPBIT��)
			if (!::SetCommState(m_hComm, &stDCB))  //���ô���״̬����
				return FALSE;

			if (!::SetupComm(m_hComm, 1024, 1024))  //�������뻺����������������Ĵ�С
				return FALSE;
			::PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);  //����������������

			return TRUE;
		}

		//���ó�ʱ����
		BOOL SetTimeOuts()
		{
			COMMTIMEOUTS stTimeOuts;

			stTimeOuts.ReadIntervalTimeout = 0;  //�趨����ʱ
			stTimeOuts.ReadTotalTimeoutMultiplier = 100;
			stTimeOuts.ReadTotalTimeoutConstant = 500;

			stTimeOuts.WriteTotalTimeoutMultiplier = 100;  //�趨д��ʱ
			stTimeOuts.WriteTotalTimeoutConstant = 500;

			::SetCommTimeouts(m_hComm, &stTimeOuts);  //���ó�ʱ
			::PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);  //����������������
			return TRUE;
		}

		//�����ں���
		BOOL ReadComm(char * lpBuf, int nLen)
		{
			if (::ReadFile(m_hComm, lpBuf, nLen, (DWORD *)&nLen, NULL) == FALSE)
			{
				return FALSE;
			}
			else
			{
				/*
				CString str;
				str.Format("%d",nLen);
				AfxMessageBox(str);
				*/

				//::PurgeComm(m_hComm,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
				return TRUE;
			}
		}

		//д���ں���
		BOOL WriteComm(char * lpBuf, int nLen)
		{
			if (::WriteFile(m_hComm, lpBuf, nLen, (DWORD *)&nLen, NULL) == FALSE)
			{
				return FALSE;
			}
			else
			{
				/*
				CString str;
				str.Format("%d",nLen);
				AfxMessageBox(str);
				*/
				return TRUE;
			}
		}
		void ClearComm()
		{
			::PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);  //����������������
		}
		HANDLE Get_CommHandle() { return m_hComm; }
	private:
		HANDLE m_hComm;
	};
}
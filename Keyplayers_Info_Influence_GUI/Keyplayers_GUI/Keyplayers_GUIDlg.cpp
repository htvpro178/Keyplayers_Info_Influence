
// Keyplayers_GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Keyplayers_GUI.h"
#include "Keyplayers_GUIDlg.h"
#include "afxdialogex.h"

#include "iostream"
#include "fstream"
#include "iomanip"
#include "conio.h"
#include "cstdlib"
#include "windows.h"
#include "ctime"
#include "fstream"
#include "string"
#include <vector>
#include <sstream>

using namespace std;

#define CTH 5

int MTLIKE[1557][1557],n,a[1557], dinh;
float MTTS[1557][1557],MTKEYPLAYER[1557],b[1557],dodaidd[1557][1557],dodaidd1[1557][1557],P=0;
string mtduongdi[1557][1557],tt,mtduongdi1[1557][1557];
HANDLE myMutex;
bool m_sDone = false;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeyplayers_GUIDlg dialog




CKeyplayers_GUIDlg::CKeyplayers_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyplayers_GUIDlg::IDD, pParent)
	, m_sFileIn(_T(""))
	, m_sNumOfKey(_T(""))
	, m_sResult1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyplayers_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEIN, m_sFileIn);
	DDX_Text(pDX, IDC_EDIT_NUM_KEY, m_sNumOfKey);
	DDX_Text(pDX, IDC_EDIT_KQ_PP1, m_sResult1);
}

BEGIN_MESSAGE_MAP(CKeyplayers_GUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CKeyplayers_GUIDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_PP1, &CKeyplayers_GUIDlg::OnBnClickedBtnPp1)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CKeyplayers_GUIDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CKeyplayers_GUIDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_RESET, &CKeyplayers_GUIDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CKeyplayers_GUIDlg message handlers

BOOL CKeyplayers_GUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_sFileIn = "";
	m_sNumOfKey = "";
	m_sResult1 = "";
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyplayers_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyplayers_GUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyplayers_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

string IntToString ( int number )
{
  std::ostringstream oss;

  // Works just like cout
  oss<< number;

  // Return the underlying string
  return oss.str();
}
string Xuat_Duong_Di(int s,int e,int truoc[])
{
	int s1[100];int t=1,m=1;char ch[10];
	s1[t]=e;t++;
	while(truoc[e]!=0)
	{
		s1[t]=truoc[e];t++;
		e=truoc[e];
	}
	string stt="";
	for(int i=t-1;i>=1;i--)
	{
		itoa(s1[i],ch,10);
		stt+=ch;stt+="-";
	}
	return stt;
		
}
void swap(int &a,int &b)
{
	int temp=a;
	a=b;
	b=temp;
}
void swapf(float &a,float &b)
{
	float temp=a;
	a=b;
	b=temp;
}
void sapxepmt()
{
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			if(b[i]<b[j])
			{
				swapf(b[i],b[j]);
				swap(a[i],a[j]);
			}
}

void ghimt(float mtg[1557])
{
	string ddan="Taptinketqua.txt";
	ofstream ghi (ddan);
	ghi<<n<<"\n";ghi<<"Cac dinh anh huong sap giam dan\n";
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
		b[i]=mtg[i];
	}
	sapxepmt();
	for(int i=1;i<=n;i++)
	{
		ghi<<"Suc anh huong cua dinh "<<a[i]<<" : "<<b[i];ghi<<"\n";
	}

}

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  return internal;
}

void docmt(string filename)
{
    ifstream readMTLike (filename);
	ifstream readMTLike1 (filename);
	if(!readMTLike.is_open())
    {
        cout<<"Can't open the file.\n";
        return ;
    }
    else 
	{		
		string line;
		std::getline(readMTLike, line);
		vector<string> sep = split(line, ' ');
		n = sep.size();
        for(int i = 1; i <= n; i++)
			for(int j=1;j<=n;j++)
			{
				readMTLike1>>MTLIKE[i][j];
				//spreadRatio[i][j] = 1.0;
			}
    }
    readMTLike.close();
	readMTLike1.close();
}
void taomt(string filename)
{
	docmt(filename);
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			if(i==j)
			{
				MTTS[i][j]=0;
			}
			else
			{
				if(MTLIKE[i][j]!=0)
					MTTS[i][j]=(1.0*MTLIKE[i][j])/MTLIKE[i][i];
				else
					MTTS[i][j]=MTLIKE[i][j];
			}
		}
}


bool kiemtrabac(int batdau,int ketthuc, float MTKT[1557][1557])
{
	bool bacv=false,bacr=false;
	for(int i=1;i<=n;i++)
	{
		if(MTKT[batdau][i]!=0&&batdau!=i)
			bacr=true;
		if(MTKT[i][ketthuc]!=0&&ketthuc!=i)
			bacv=true;
	}

	if(bacv==true&&bacr==true)
		return true;
	return false;
}
float Duong_di_hai_dinh(int source,int end,float MTTSIN[1557][1557])
{
	if(kiemtrabac(source,end,MTTSIN)==false || source==end)
	{
		mtduongdi[source][end]="0";
		dodaidd[source][end]=0;
		return 0;
	}
	else
	{
		if(MTTSIN[source][end]!=0)
		{
			char t[10];
			dodaidd[source][end]=MTTSIN[source][end];
			tt="";
			itoa(source,t,10);
			tt+=t;tt+="-";
			itoa(end,t,10);
			tt+=t;tt+="-";
			mtduongdi[source][end]=tt;
			return MTTSIN[source][end];

		}
		else
		{   
			int DanhDau[1557];
			float Nhan[1557], min;
			int Truoc[1557], XP;

			for(int i=1; i<=n; i++)
			{
				Nhan[i] = MAXINT;
				DanhDau[i] = 0;
				Truoc[i] = 0;
			}
			Nhan[source] = 0;
			DanhDau[source] = 1;
			XP = source;

			while(XP != end)
			{
				for(int j=1; j<=n; j++)
					if(MTTSIN[XP][j]>0 && Nhan[j]>=MTTSIN[XP][j]+Nhan[XP] && DanhDau[j]==0) 
					{
						Nhan[j] = MTTSIN[XP][j]+Nhan[XP];
						Truoc[j] = XP;
					}

				min = MAXINT;
			
				for(int j = 1; j<=n; j++)
					if(min>=Nhan[j] && DanhDau[j]==0)
					{
						min = Nhan[j];
						XP = j;
					}
				DanhDau[XP] = 1;
			}
			//cout<<"Duong di ngan nhat la"<<Nhan[end]<<endl;
			//cout<<source+1<<" <_"<<Truoc[end] + 1;
			if(Nhan[end]!=0)
			{
				mtduongdi[source][end]=Xuat_Duong_Di(source,end,Truoc);
				//cout<<mtduongdi[source][end]<<endl;
				dodaidd[source][end]=Nhan[end];
				return Nhan[end];
			}
			else
			{
				mtduongdi[source][end]="0";
				dodaidd[source][end]=0;
				return 0;
			}
		}
	}
}


int tachchuoi(string s,int node)
{
	 char kt='-',ch[10];
	 itoa(node,ch,10);
	 string dinh=ch;
	 int len=s.length(),dem=1;
	 string a11[100],t="";
	for(int i=0;i<len;i++)
	{
		if(i!=0 && i!=s.length()-2)
		{
		
			if(s[i]!=kt)
			{
				t+=s[i];
			
			}
			else
			{
				a11[dem]=t;
				dem++;
				t="";
			}
		}
	}

	for(int i=1;i<=dem;i++)
	{
		if(a11[i].compare(dinh)==0)
			return 1;
		
	}
	return 0;
	
}
int Kiem_tra_dinh(int dinh)
{
	for(int i=1;i<=n;i++)
		if(MTTS[dinh][i]!=0)
			return 1;
	return 0;
}
DWORD WINAPI taske(LPVOID) 
{
	int node=0;
	while(node<n)
	{
		 DWORD dwWaitResult; 
         dwWaitResult = WaitForSingleObject(myMutex, INFINITE);
        switch (dwWaitResult) 
        {
            case WAIT_OBJECT_0: 
            { 
					node = dinh; 
					dinh++;
					ReleaseMutex(myMutex);
					if (node<=n)
					{
						for(int j=1;j<=n;j++)
							if ( node != j)
								Duong_di_hai_dinh(node,j,MTTS);
					}

				break; 
			} 
			
			  case WAIT_ABANDONED: 
					 return FALSE; 
        }
   }
	return 0;
}

DWORD WINAPI taskkey(LPVOID) 
{
	int node=0;
	while(node<n)
	{
	float tongloai;
	
    DWORD dwWaitResult; 

        dwWaitResult = WaitForSingleObject(myMutex, INFINITE);  
 
        switch (dwWaitResult) 
        {
            case WAIT_OBJECT_0: 
            { 
                    node = dinh; 
					dinh++;
					ReleaseMutex(myMutex);
					if (node<=n)
					{
						if(Kiem_tra_dinh(node)==1)
						{
							float(*mttemp)[1557]=new float[1557][1557];
							for(int i=1;i<=n;i++)
							{
								for(int j=1;j<=n;j++)
								{
									if(i==node)
										mttemp[i][j]=0;
									else
										mttemp[i][j]=MTTS[i][j];
								}
							}
							tongloai=0;
							for(int i=1;i<=n;i++)
							{
								for(int j=1;j<=n;j++)
								{
									if(dodaidd1[i][j]==0||i==node)
										tongloai+=0;
									else
									{
										if(tachchuoi(mtduongdi1[i][j],node)==0 && dodaidd1[i][j] > 0)
										{
											tongloai += 1/( dodaidd1[i][j]*1.0);
										}
										else
										{
											float tempdd = 0.0;
											tempdd = Duong_di_hai_dinh(i,j,mttemp);
											if ( tempdd > 0)
											{
												tongloai += 1/(tempdd*1.0);
											}
										}
									}
								}
							}
							MTKEYPLAYER[node]=(P-(tongloai/(n*(n-1))))/P;
						}
						else
							MTKEYPLAYER[node]=0;
					}
				  break;
                } 
				case WAIT_ABANDONED: 
					 return FALSE; 
        }
  	}
	return 0;
}

void handlerResult(bool sDone)
{
	if ( sDone == false)
	{	
		dinh = 1;
		myMutex = CreateMutex(NULL, FALSE, NULL);           
		if (myMutex == NULL) 
		{
			printf("CreateMutex error: %d\n", GetLastError());
		}
		HANDLE thr[100]; 
		DWORD thrid; 
		for(int i=0;i<=CTH-1;i++)
		{
			thr[i]=CreateThread(NULL,0,taske,0,0,&thrid); 
		}
		WaitForMultipleObjects(CTH, thr, TRUE, INFINITE);
		CloseHandle(myMutex); 

		float tong=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if ( dodaidd[i][j] > 0)
				{
					tong+=(1/dodaidd[i][j]*1.0);
					dodaidd1[i][j]=dodaidd[i][j];
					mtduongdi1[i][j]=mtduongdi[i][j];
				}
			}
		}
		P=tong/(n*(n-1));
	
		dinh = 1;
		myMutex = CreateMutex(NULL, FALSE, NULL);             

		if (myMutex == NULL) 
		{
			printf("Tao mutex bi loi \n", GetLastError());
		}
		for(int i=0;i<=CTH-1;i++)
		{
			thr[i]=CreateThread(NULL,0,taskkey,0,0,&thrid); 
		}
		WaitForMultipleObjects(CTH, thr, TRUE, INFINITE);
		CloseHandle(myMutex);
		ghimt(MTKEYPLAYER);
		//cout<<"Danh sach "<<n<<" phan tu co suc anh huong nhat "<<endl<<endl;
		//cout<<"            Dinh          "<<" Do mat thong tin"<<endl<<endl;
		//for(int i=1;i<=n;i++)
			//cout<<"             "<<a[i]<<"                 "<<b[i]<<endl<<endl;
	}

	/*for( int i=1; i<=n; i++)
	{
		for( int j=1; j<=n; j++)
		{
			if ( flag == false ) // flag cho pp1
			{
				//if ( LenPath[i][j] > 0 || m_IsPath[i][j] == true )
				if ( m_IsPath[i][j] == true )
				{
					string topValue = IntToString( j );
					affectionTop[i].empty();
					affectionTop[i].append(topValue);
					affectionTop[i].append(" ");
					stringLenPath[i].append(topValue);
					stringLenPath[i].append(" : ");
					stringLenPath[i].append(FloatToString( LenPath[i][j] ));
					stringLenPath[i].append("\n");
				}
			
				//cout<<"LenPath["<<i<<"]["<<j<<"]"<<LenPath[i][j]<<"\n";
				LenSum[i] += LenPath[i][j];
			}
		}
	}*/
}

void CKeyplayers_GUIDlg::OnBnClickedBtnOpenfile()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle = L"Choose the input file";
	dlg.m_ofn.lpstrInitialDir = L"E:\\DATA\\Study\\social network\\Coding\\BAO CAO\\Source Code\\data_test";
	if ( dlg.DoModal() == IDOK)
	{
		m_sFileIn = dlg.m_ofn.lpstrFile;
		UpdateData(FALSE);
	}
}

void CKeyplayers_GUIDlg::OnBnClickedBtnPp1()
{
	// TODO: Add your control notification handler code here
	if ( m_sDone == false )
	{
		UpdateData(TRUE);
		time_t rawtime;
		time(&rawtime);	
		CString tempTime = (CString)ctime(&rawtime);
		SetDlgItemText(IDC_START_TIME1,tempTime);
		SetDlgItemText(IDC_STATUS1, L"Đang xử lý...");
		int top;
		top = _tstoi(m_sNumOfKey);
		
		if ( ProcessFiles(m_sFileIn, top, false ) == TRUE)
		{
			// Convert a TCHAR string to a LPCSTR
			CT2CA pszConvertedAnsiString (m_sFileIn);
			// construct a std::string using the LPCSTR input
			string strMtLike (pszConvertedAnsiString);
			//TRACE("ket qua tra ve là : [%s]\n", strStd.c_str());
			taomt(strMtLike);
			if ( ProcessFiles(m_sFileIn, top, true ) == TRUE)
			{
				handlerResult( m_sDone);
				//writeMT(LenSum, top);
		
				//CString m_sResult = L"Danh sach " + m_sNumOfKey + L" phan tu co suc anh huong lon nhat trong do thi:\n" ;
				CString m_sResult;
				for(int i=1;i<=top;i++)
				{
					CString aStr, memberStr, bStr ;
					aStr.Format(L"%d", a[i]);
					//memberStr.Format(L"%s", member[i].c_str());
					bStr.Format(L"%f", b[i]);
					//CString m_sResultTemp = L"    " + aStr + L" (" + memberStr + L")           " + bStr + L"\r\n";
					if (aStr.GetLength() == 4 )
					{
						m_sResult += L"                            " + aStr + L"                                                        " + bStr + L"\r\n";
					}
					if (aStr.GetLength() == 3 )
					{
						m_sResult += L"                            " + aStr + L"                                                          " + bStr + L"\r\n";
					}
					else if (aStr.GetLength() == 2 )
					{
						m_sResult += L"                            " + aStr + L"                                                            " + bStr + L"\r\n";
					}
					else
					{
						m_sResult += L"                            " + aStr + L"                                                              " + bStr + L"\r\n";
					}
				}
				SetDlgItemText(IDC_EDIT_KQ_PP1, m_sResult);
				m_sDone = true;
				SetDlgItemText(IDC_STATUS1, L"Đã xong!");
				time(&rawtime);
				CString tempTime = (CString)ctime(&rawtime);
				SetDlgItemText(IDC_END_TIME1,tempTime);
			}
		}
	}
	else
	{
		MessageBox(L"Đã tính xong", L"Information", MB_OK | MB_ICONINFORMATION);
	}
}

BOOL CKeyplayers_GUIDlg::ProcessFiles(CString sFileIn, int top, bool loadFile)
{
	if (loadFile == false)
	{
		CFile fileIn;
		if ( fileIn.Open(sFileIn, CFile::modeRead) == FALSE )
		{
			CString sMsg;
			sMsg.Format(L"Không thể mở File %s", sFileIn);
			MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		if (top < 1 ) 
		{
			CString sMsg;
			sMsg.Format(L"Vui lòng kiểm tra số lượng Keyplayers");
			MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		int a;
		fileIn.Read(&a, sizeof(int));
	}
	else
	{
		if (top < 1 || top > n) 
		{
			CString sMsg;
			sMsg.Format(L"Vui lòng kiểm tra số lượng Keyplayers");
			MessageBox(sMsg, L"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}		
	}
	return TRUE;
}

void CKeyplayers_GUIDlg::OnBnClickedBtnAbout()
{
	// TODO: Add your control notification handler code here
	MessageBox(L"Xác định Keyplayers dựa vào sức ảnh hưởng thông tin v1.0\r\nCH1301114 - Huỳnh Thanh Việt", L"Information", MB_OK | MB_ICONINFORMATION);
}


void CKeyplayers_GUIDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void CKeyplayers_GUIDlg::OnBnClickedBtnReset()
{
	// TODO: Add your control notification handler code here
	if (n>0)
	{
		dinh = 0;
		P = 0.0;
		tt = "";
		for( int i = 0; i<=n; i++)
		{
			a[i] = 0;
			b[i] = 0.0;
			MTKEYPLAYER[i] = 0.0;
			m_sDone = false;
			for ( int j = 0; j<=n; j++)
			{
				MTLIKE[i][j] = 0;
				MTTS[i][j] = 0.0;
				dodaidd[i][j] = 0.0;
				dodaidd1[i][j] = 0.0;
				mtduongdi[i][j] = "";
				mtduongdi1[i][j] = 0.0;
			}
		}
		n = 0;
		CString temp;
		temp.Format(L"%s", "");
		UpdateData(FALSE);

		SetDlgItemText(IDC_EDIT_KQ_PP1, temp);
		SetDlgItemText(IDC_STATUS1, temp);
		SetDlgItemText(IDC_START_TIME1,temp);
		SetDlgItemText(IDC_END_TIME1,temp);

		SetDlgItemText(IDC_EDIT_FILEIN, temp);
		SetDlgItemText(IDC_EDIT_NUM_KEY, temp);

		m_sFileIn = "";
		m_sNumOfKey = "";
		m_sResult1 = "";
	}
}


// DragDemoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DragDemo.h"
#include "DragDemoDlg.h"
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


// CDragDemoDlg 대화 상자



CDragDemoDlg::CDragDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAGDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pImgListDrag = NULL;
	m_nIndexLeftSel = -1;
	/*for (int i = 0; i <= 10; i++)
		RCheck[i] = 0;*/
}

void CDragDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LEFT, m_List_Left);
	//  DDX_Control(pDX, IDC_LIST_RIGHT, m_List_Rigth);
	DDX_Control(pDX, IDC_LIST_RIGHT, m_List_Right);
}

BEGIN_MESSAGE_MAP(CDragDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_LEFT, &CDragDemoDlg::OnLvnBegindragListLeft)
//	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDragDemoDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CDragDemoDlg 메시지 처리기

BOOL CDragDemoDlg::OnInitDialog()
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

	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_ImageList); // 비트맵 불러옴

	static CImageList ImgList;
	ImgList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 5, 0);
	ImgList.Add(&Bitmap, RGB(0, 0, 0));
	m_List_Left.SetImageList(&ImgList, LVSIL_NORMAL);
	m_List_Right.SetImageList(&ImgList, LVSIL_NORMAL);

	CString strItem = _T("");
	for (int i = 0; i < 5; i++) {
		strItem.Format(_T("%dth Item"), i); // 문자열 설정
		m_List_Left.InsertItem(i, strItem, i); // 문자열 및 이미지 대입
	}

	DWORD dwExStyle = m_List_Left.GetExtendedStyle();
	m_List_Left.SetExtendedStyle(dwExStyle | LVS_EX_BORDERSELECT); // 확장 스타일 적용
	dwExStyle = m_List_Right.GetExtendedStyle();
	m_List_Right.SetExtendedStyle(dwExStyle | LVS_EX_BORDERSELECT);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDragDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDragDemoDlg::OnPaint()
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
HCURSOR CDragDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDragDemoDlg::OnLvnBegindragListLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	

	CPoint ptDrag, ptAction;
	m_nIndexLeftSel = pNMLV->iItem; // 선택된 항목의 인덱스를 저장
	m_pImgListDrag = m_List_Left.CreateDragImage(pNMLV->iItem, &ptDrag); // 새로운 이미지 목록을 만듬
	m_pImgListDrag->SetBkColor(RGB(0, 0, 0));
	ptAction = pNMLV->ptAction; // 드래그를 시작한 좌표가 들어감

	SetCapture(); // 마우스 포인터가 윈도우 영역을 벗어나더라도 마우스 메시지를 수신할수 있다
	m_pImgListDrag->BeginDrag(0, ptAction - ptDrag); //(이미지 인덱스, 마우스 포인터에 맞춰야 할 좌표)
	m_List_Left.ClientToScreen(&ptAction);
	m_pImgListDrag->DragEnter(NULL, ptAction); // 드래그 상태가 됨, 이때 반투명한 드래그 이미지가 출력
	*pResult = 0;
}


//void CDragDemoDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CDialogEx::OnNcMouseMove(nHitTest, point);
//}


void CDragDemoDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pImgListDrag != NULL) {
		ClientToScreen(&point);

		CWnd* pWnd = CWnd::WindowFromPoint(point); // 대화 상자에 있는 좌표를 대입
		if (pWnd != NULL) { 
			if (this == pWnd || IsChild(pWnd)) {
				m_pImgListDrag->DragEnter(NULL, point); // 이미지를 다시 화면에 나오게 한다.
				m_pImgListDrag->DragMove(point); // 인자로 전달받은 좌표에 드래그 이미지 출력
			}
			else {
				m_pImgListDrag->DragLeave(NULL); // 드래그 이미지를 지운다, 이게 없으면 포인터가 없어졌을때 없어진 그 자리에 이미지가 남는다.
			} // Enter와 Leave는 다이얼로그에서 마우스가 나갔을경우 활성화 되는것 같다.
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDragDemoDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTmp = _T("");
	if (m_pImgListDrag != NULL) {
		ClientToScreen(&point);

		m_pImgListDrag->DragLeave(NULL);
		m_pImgListDrag->EndDrag(); // 드래그가 끝났음을 알림
		ReleaseCapture();

		// 오른쪽 리스트에 아이템 추가
		CWnd* pWnd = CWnd::WindowFromPoint(point);
		
			if (pWnd == &m_List_Right && m_nIndexLeftSel >= 0) { // 포인터의 주소가 오른쪽 리스트이고, 왼쪽 리스트에서 선택한 항목이 있다면
				LVITEM lvItem;
				TCHAR szBuffer[256];
				::ZeroMemory(&lvItem, sizeof(lvItem));
				::ZeroMemory(szBuffer, sizeof(256));

				lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
				lvItem.iItem = m_nIndexLeftSel;
				lvItem.pszText = szBuffer;
				lvItem.cchTextMax = 256;
				m_List_Left.GetItem(&lvItem);

				m_List_Right.InsertItem(0, lvItem.pszText, lvItem.iImage); // 오른쪽 리스트에 추가
				
			}


			// 왼쪽 리스트이면 구체적인 아이템 인덱스 출력
			else {
				m_List_Left.ScreenToClient(&point); // 왼쪽 리스트 기준 좌표로 변환
				int nIndex = m_List_Left.HitTest(point); // 인자로 전달받은 좌표에 해당하는 항목이 있는지 검사한다.(HitTest함수 기능)
				if (nIndex >= 0) {
					strTmp.Format(_T("Drop on %dth item"), nIndex);
					AfxMessageBox(strTmp);
				}
			}
			int RIndex = m_nIndexLeftSel;
			RCheck[RIndex] = m_nIndexLeftSel;

			delete m_pImgListDrag;
			
		}
	

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDragDemoDlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_List_Right.DeleteAllItems();
}


// MFCApplication2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2Dlg 대화 상자



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET_TIME_BTN, &CMFCApplication2Dlg::OnBnClickedGetTimeBtn)
	ON_BN_CLICKED(IDC_START_BTN, &CMFCApplication2Dlg::OnBnClickedStartBtn)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication2Dlg 메시지 처리기

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication2Dlg::OnPaint()
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedGetTimeBtn()
{
	/*
	// time_t, tm은 c++ 지원 함수이기에 리눅스에서도 사용이 가능!
	time_t cur_time = time(NULL);
	tm * p_time = localtime(&cur_time);

	CString str;
	str.Format(L"%d년 %d월 %d일 %d시 %d분 %d초", p_time->tm_year+1900, p_time->tm_mon+1, p_time->tm_mday, p_time->tm_hour, p_time->tm_min, p_time->tm_sec);
	*/

	/*
	// Windows 방식으로 구현
	CTime cur_time = CTime::GetCurrentTime();

	CString str;
	// str.Format(L"%d년 %d월 %d일 %d시 %d분 %d초", cur_time.GetYear(), cur_time.GetMonth(), cur_time.GetDay(), cur_time.GetHour(), cur_time.GetMinute(), cur_time.GetSecond());
	str = cur_time.Format("%A, %B, %d, %Y");
	// %A - 요일(영어로)
	// %B - 월(영어로)
	// %d - 일
	// %Y - 월(숫자로)
	// strftime 구조체의 설명을 참조하자

	str = cur_time.Format("%F %T");		// 2019-01-09 13:46:51 이런형태로 출력
	*/

	// 밀리세컨드 단위로 얻고 싶다면??
	SYSTEMTIME cur_time;
	GetLocalTime(&cur_time);

	CString str;
	str.Format(L"%d년 %d월 %d일 %d시 %d분 %d초 (%dms)", cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);


	SetDlgItemText(IDC_SHOW_TIME_EDIT, str);
}


void CALLBACK MyTimerProc(HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_system_time)
{
	// ah_wnd : 대화상자의 윈도우 핸들
	// a_msg_id : WM_TIMER가 들어옴
	//a_timer_id : 타이머 아이디
	// a_system_time : 무시(NULL)

	if (a_timer_id == 1) {
		// OnBnClickedGetTimeBtn();
		::SendMessage(ah_wnd, WM_COMMAND, MAKEWPARAM(IDC_GET_TIME_BTN, BN_CLICKED));
	}

} 

void CMFCApplication2Dlg::OnBnClickedStartBtn()
{
	if (m_timer_flat != 0) {
		// SetTimer(1, 200, NULL);
		// (참고) SetTimer(1, 200, &MyTimerProc::MyTimerProc);
		// 와 같은 방식으로 MyTimerProc내부에 MyTimerProc를 넣는 방식도 가능하지만
		// static void CALLBACK MyTimerProc(HWND ah_wnd, UINT a_msg_id, UINT_PTR a_timer_id, DWORD a_system_time)
		// static으로 MyTimerProc를 선언하면서 MyTimerProc내부에서 CMFCApplication2Dlg변수를 사용할 수 없다..
		// 가령 m_timer_flat와 같은 변수 사용불가!
		// 다른 방법으로 써보자.
		SetTimer(1, 200, MyTimerProc);
		m_timer_flat = 1;
	}
}


void CMFCApplication2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		OnBnClickedGetTimeBtn();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMFCApplication2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_timer_flat == 1) {
		KillTimer(1);
	}
}

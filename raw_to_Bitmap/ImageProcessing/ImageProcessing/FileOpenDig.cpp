// FileOpenDig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "FileOpenDig.h"
#include "afxdialogex.h"


// CFileOpenDig 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFileOpenDig, CDialogEx)


CFileOpenDig::CFileOpenDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_DigWidth(0)
	, m_DigHeight(0)
	, m_Gray(FALSE)
{

}

CFileOpenDig::~CFileOpenDig()
{
}
UINT CFileOpenDig::GetWidth(void) {
	return m_DigWidth;
}
UINT CFileOpenDig::GetHeight(void) {
	return m_DigHeight;
}
void CFileOpenDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DigWidth);
	DDX_Text(pDX, IDC_EDIT2, m_DigHeight);
	DDX_Radio(pDX, IDC_RADIO1, m_Gray);
}


BEGIN_MESSAGE_MAP(CFileOpenDig, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CFileOpenDig::OnEnChangeEdit1)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO1,IDC_RADIO2, &CFileOpenDig::OnBnClickedRadio)
END_MESSAGE_MAP()


// CFileOpenDig 메시지 처리기입니다.


void CFileOpenDig::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CFileOpenDig::OnBnClickedRadio(UINT msg)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

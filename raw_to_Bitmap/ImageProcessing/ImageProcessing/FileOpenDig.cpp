// FileOpenDig.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "FileOpenDig.h"
#include "afxdialogex.h"


// CFileOpenDig ��ȭ �����Դϴ�.

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


// CFileOpenDig �޽��� ó�����Դϴ�.


void CFileOpenDig::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CFileOpenDig::OnBnClickedRadio(UINT msg)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

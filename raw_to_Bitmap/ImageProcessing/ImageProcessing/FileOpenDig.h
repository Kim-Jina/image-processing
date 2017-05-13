#pragma once


// CFileOpenDig 대화 상자입니다.

class CFileOpenDig : public CDialogEx
{
	DECLARE_DYNAMIC(CFileOpenDig)

public:
	CFileOpenDig(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileOpenDig();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
private:
	UINT m_DigWidth;
	UINT m_DigHeight;

public:
	UINT GetWidth(void);
	UINT GetHeight(void);
	afx_msg void OnBnClickedRadio(UINT msg);
	BOOL m_Gray;
};

#pragma once


// CFileOpenDig ��ȭ �����Դϴ�.

class CFileOpenDig : public CDialogEx
{
	DECLARE_DYNAMIC(CFileOpenDig)

public:
	CFileOpenDig(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileOpenDig();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

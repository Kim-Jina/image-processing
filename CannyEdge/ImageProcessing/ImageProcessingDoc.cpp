
// ImageProcessingDoc.cpp : CImageProcessingDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"

#include <propkey.h>

#include "FileOpenDig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
	ON_COMMAND(ID_CANNYEDGE_CANNYEDGE, &CImageProcessingDoc::OnCannyedgeCannyedge)
END_MESSAGE_MAP()


// CImageProcessingDoc ����/�Ҹ�

CImageProcessingDoc::CImageProcessingDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc ����

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc ���


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CFileOpenDig myDig;
	FILE* f = fopen(lpszPathName, "rb");  // open file

	// Dialog
	if (myDig.DoModal() == IDOK)
	{
		Image.m_uiHeight = myDig.GetHeight();
		Image.m_uiWidth = Image.m_BMPWidth = myDig.GetWidth();
		
		if (Image.m_uiWidth & 0x03)
			Image.m_BMPheader.biWidth = Image.m_BMPWidth = (Image.m_uiWidth + (4 - Image.m_uiWidth & 0x03));
		
		if (myDig.m_Gray == FALSE) {		// Ouput Gray Image
			// memory allocation for Image class

			Image.m_puclmgBuf = new UCHAR*[Image.m_uiHeight];
			*Image.m_puclmgBuf = new UCHAR[Image.m_uiHeight*Image.m_uiWidth];

			for (UINT i = 1; i < Image.m_uiHeight; i++)
				Image.m_puclmgBuf[i] = Image.m_puclmgBuf[i - 1] + Image.m_uiWidth;

			fread(*Image.m_puclmgBuf, sizeof(UCHAR), Image.m_uiWidth*Image.m_uiHeight, f);

			fclose(f);

			Image.m_pucBMP = new UCHAR[Image.m_uiHeight * Image.m_BMPWidth * 3];

			// convert raw format to Bitmap
			Image.MakeBMP(Image.m_puclmgBuf);
		}
		else {								// Ouput RGB Image
			// memory allocation for Image class

			Image.m_puclmgBuf = new UCHAR*[Image.m_uiHeight];
			*Image.m_puclmgBuf = new UCHAR[Image.m_uiHeight*Image.m_uiWidth * 3];

			for (UINT i = 1; i < Image.m_uiHeight; i++)
				Image.m_puclmgBuf[i] = Image.m_puclmgBuf[i - 1] + Image.m_uiWidth * 3;

			fread(*Image.m_puclmgBuf, sizeof(UCHAR), Image.m_uiWidth*Image.m_uiHeight * 3, f);

			fclose(f);

			Image.m_pucBMP = new UCHAR[Image.m_uiHeight * Image.m_BMPWidth * 3];

			// convert raw format to Bitmap
			Image.MakeRGB();
		}
	}

	return TRUE;
}


void CImageProcessingDoc::OnCannyedgeCannyedge()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Image.E_image = Image.Alloc(Image.m_uiHeight, Image.m_uiWidth);

	Image.CannyEdge();
	Image.MakeBMP(Image.E_image);
	UpdateAllViews(nullptr);
}

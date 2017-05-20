
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessingDoc 진단

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


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Image.E_image = Image.Alloc(Image.m_uiHeight, Image.m_uiWidth);

	Image.CannyEdge();
	Image.MakeBMP(Image.E_image);
	UpdateAllViews(nullptr);
}

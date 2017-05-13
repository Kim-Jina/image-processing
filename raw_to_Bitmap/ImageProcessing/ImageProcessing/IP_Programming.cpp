#include "stdafx.h"
#include "IP_Programming.h"


CIP_Programming::CIP_Programming():m_pucBMP(nullptr),m_puclmgBuf(nullptr),m_uiHeight(0),m_uiWidth(0) // initialize variables
{
	m_BMPheader.biSize = sizeof(BITMAPINFOHEADER);
	m_BMPheader.biPlanes = 1;
	m_BMPheader.biBitCount = 24;
	m_BMPheader.biCompression = BI_RGB;
	m_BMPheader.biSizeImage = 0;
	m_BMPheader.biXPelsPerMeter = 0;
	m_BMPheader.biYPelsPerMeter = 0;
	m_BMPheader.biClrUsed = 0;
	m_BMPheader.biClrImportant = 0;
}


CIP_Programming::~CIP_Programming()
{
}

void CIP_Programming::MakeBMP(void) {		// Make Gray Bitmap Image
	m_BMPheader.biWidth = m_uiWidth;
	m_BMPheader.biHeight = m_uiHeight;

	// Save raw Iamge in Bitmap Image by reversing Image
	int index = 0;
	for (UINT i = 0; i < m_uiHeight; i++) {
		for (UINT j = 0; j < m_uiWidth; j++) {
			m_pucBMP[index++] = m_puclmgBuf[m_uiHeight - i - 1][j];
			m_pucBMP[index++] = m_puclmgBuf[m_uiHeight - i - 1][j];
			m_pucBMP[index++] = m_puclmgBuf[m_uiHeight - i - 1][j];
		}
		for (UINT j = 0; j < static_cast<int>(m_BMPWidth - m_uiWidth); j++)
			index++;
	}
}

void CIP_Programming::MakeRGB(void) {	// Make RGB Bitmap Image
	m_BMPheader.biWidth = m_uiWidth;
	m_BMPheader.biHeight = m_uiHeight;
	
	// Save raw Iamge in Bitmap Image by reversing Image and making RGB value
	int index = 0;
	for (UINT i = 0; i < m_uiHeight; i++) {
		for (UINT j = 0; j < m_uiWidth * 3; j += 3) {
			m_pucBMP[index++] = m_puclmgBuf[m_uiHeight - i - 1][j + 2];	// B
			m_pucBMP[index++] = m_puclmgBuf[m_uiHeight - i - 1][j + 1];	// G
			m_pucBMP[index++] = m_puclmgBuf[m_uiHeight - i - 1][j];		// R
		}
		for (UINT j = 0; j < static_cast<int>(m_BMPWidth - m_uiWidth); j++)
			index++;
	}
}

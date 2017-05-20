#pragma once
class CIP_Programming
{
public:
	// Bitmap
	BITMAPINFOHEADER m_BMPheader;
	UCHAR* m_pucBMP;

	// raw
	UCHAR** m_puclmgBuf;
	UCHAR** E_image;

	// size
	UINT m_uiHeight;
	UINT m_uiWidth;

	UINT m_BMPWidth;

	CIP_Programming();
	~CIP_Programming();

public:
	void MakeBMP(UCHAR** image);
	void MakeRGB();
	void CannyEdge();
	UCHAR** Alloc(int h, int w);
	double** Alloc_D(int h, int w);
};


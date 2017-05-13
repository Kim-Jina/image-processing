#pragma once
class CIP_Programming
{
public:
	// Bitmap
	BITMAPINFOHEADER m_BMPheader;
	UCHAR* m_pucBMP;

	// raw
	UCHAR** m_puclmgBuf;

	// size
	UINT m_uiHeight;
	UINT m_uiWidth;

	UINT m_BMPWidth;

	CIP_Programming();
	~CIP_Programming();

public:
	void MakeBMP(void);
	void MakeRGB(void);
};


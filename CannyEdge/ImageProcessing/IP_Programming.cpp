#include "stdafx.h"
#include "IP_Programming.h"
#include <cmath>
#include <stack>

using namespace std;

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

void CIP_Programming::MakeBMP(UCHAR** image) {		// Make Gray Bitmap Image
	m_BMPheader.biWidth = m_uiWidth;
	m_BMPheader.biHeight = m_uiHeight;
	
	m_puclmgBuf = image;

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

void CIP_Programming::MakeRGB() {	// Make RGB Bitmap Image
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

UCHAR** CIP_Programming::Alloc(int h, int w) { // memory allocation
	UCHAR** m;

	m = new UCHAR*[h];
	for (int i = 0; i < h; i++)
		m[i] = new UCHAR[w];

	return m;
}

double** CIP_Programming::Alloc_D(int h, int w) { // memory allocation
	double** m;

	m = new double*[h];
	for (int i = 0; i < h; i++)
		m[i] = new double[w];

	return m;
}

void CIP_Programming::CannyEdge() {	// Canny Edge Detection
	///////////////////////// Declaration & Allocation //////////////////////////////
	UCHAR** P_image = Alloc(m_uiHeight + 4, m_uiWidth + 4);
	UCHAR** G_image = Alloc(m_uiHeight, m_uiWidth);
	UCHAR** S_image = Alloc(m_uiHeight, m_uiWidth);
	stack<int> S_i, S_j;
	int G_mask[5][5] = { { 2,4,5,4,2 },{ 4,9,12,9,4 },{ 5,12,15,12,5 },{ 4,9,12,9,4 },{ 2,4,5,4,2 } };
	int S_mask_x[3][3] = { { -1,0,1 },{ -2,0,2 },{ -1,0,1 } };
	int S_mask_y[3][3] = { { -1,-2,-1 },{ 0,0,0 },{ 1,2,1 } };
	double **x = Alloc_D(m_uiHeight, m_uiWidth);
	double **y = Alloc_D(m_uiHeight, m_uiWidth);
	double G_value;
	int high = 50;
	int low = 20;
	int s_edge = 255;
	int w_edge = 130;
	int direction;

	///////////////////////// PADDING ///////////////////////////////
	// 1. Middle
	for (UINT i = 2; i < m_uiHeight + 2; i++) {
		for (UINT j = 2; j < m_uiWidth + 2; j++) {
			P_image[i][j] = m_puclmgBuf[i - 2][j - 2];
		}
	}
	// 2. Corner
	for (UINT i = 0; i < 2; i++) {
		for (UINT j = 0; j < 2; j++) {
			for (UINT a = 0; a < 2; a++) {
				for (UINT b = 0; b < 2; b++) {
					P_image[i * (m_uiHeight + 2) + a][j * (m_uiWidth + 2) + b] = m_puclmgBuf[i * (m_uiHeight - 2) + a][j * (m_uiWidth - 2) + b];
				}
			}
		}
	}
	// 3. Edge
	for (UINT i = 0; i < 2; i++) {
		for (UINT j = 2; j < m_uiWidth + 2; j++) {
			for (UINT a = 0; a < 2; a++) {
				P_image[i * (m_uiHeight + 2) + a][j] = m_puclmgBuf[i * (m_uiHeight - 2) + a][j - 2];
				P_image[j][i *  (m_uiWidth + 2) + a] = m_puclmgBuf[j - 2][i * (m_uiWidth - 2) + a];
			}
		}
	}

	///////////////////////// Gaussian ////////////////////////
	for (UINT i = 0; i < m_uiHeight; i++) {
		for (UINT j = 0; j < m_uiWidth; j++) {
			G_value = 0;
			for (UINT a = 0; a < 5; a++) {
				for (UINT b = 0; b < 5; b++) {
					G_value += P_image[i + a][j + b] * G_mask[a][b];
				}
			}
			G_value /= 159;
			G_image[i][j] = (int)G_value;
		}
	}
	
	//////////////////////// Sobel //////////////////////////////
	for (int i = 1; i < m_uiHeight - 1; i++) {
		for (int j = 1; j < m_uiWidth - 1; j++) {
			x[i][j] = y[i][j] = 0;
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					x[i][j] += S_mask_x[a][b] * G_image[i + a - 1][j + b - 1];
					y[i][j] += S_mask_y[a][b] * G_image[i + a - 1][j + b - 1];
				}
			}

			double value = abs(x[i][j]) + abs(y[i][j]);

			if (value > 255)
				value = 255;
			if (value < 0)
				value = 0;

			S_image[i][j] = (int)value;
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	for (int i = 1; i < m_uiHeight - 1; i++) {
		for (int j = 1; j < m_uiWidth - 1; j++) {
			///////////////////// Non Maximum Suppression //////////////////
			if (S_image[i][j] > low) {
				if (x[i][j] != 0.f) {
					double angle = atan2(y[i][j], x[i][j]) * 180 / 3.14159265358979323846f;
					if (((angle >= -22.5f) && (angle < 22.5f)) || (angle >= 157.5f) && (angle < -157.5f))
						direction = 0;
					else if (((angle >= 22.5f) && (angle < 67.5f)) || ((angle >= -157.5f) && (angle < -112.5f)))
						direction = 1;
					else if (((angle >= 67.5) && (angle < 112.5)) || ((angle >= -112.5) && (angle < -67.5)))
						direction = 2;
					else
						direction = 3;
				}
				else
					direction = 2;

				bool max = false;
				if (direction == 0) {
					if ((S_image[i][j] >= S_image[i][j - 1]) && (S_image[i][j] > S_image[i][j + 1]))
						max = true;
				}
				else if (direction == 1) {
					if ((S_image[i][j] >= S_image[i - 1][j - 1]) && (S_image[i][j] > S_image[i + 1][j + 1]))
						max = true;
				}
				else if (direction == 2) {
					if ((S_image[i][j] >= S_image[i - 1][j]) && (S_image[i][j] > S_image[i + 1][j]))
						max = true;
				}
				else {
					if ((S_image[i][j] >= S_image[i - 1][j + 1]) && (S_image[i][j] > S_image[i + 1][j - 1]))
						max = true;
				}

				//////////////////////// Double Threshold ////////////////////////
				if (max == true) {
					if (S_image[i][j] > high) {
						E_image[i][j] = s_edge;
						S_i.push(i);
						S_j.push(j);
					}
					else
						E_image[i][j] = w_edge;
				}
			}
		}
	}

	///////////////////////////// Tracking //////////////////////////////////
	while (!S_i.empty()){
		int i = S_i.top();
		int j = S_j.top();
		S_i.pop();
		S_j.pop();

		// 8-connected neighborhood
		for (int a = i - 1; a < i + 2; a++) {
			for (int b = j - 1; b < j + 2; b++) {
				if (E_image[a][b] == w_edge) {
					E_image[a][b] = s_edge;
					S_i.push(a);
					S_j.push(b);
				}
			}
		}
	}

	for (int i = 0; i < m_uiHeight; i++) {
		for (int j = 0; j < m_uiWidth; j++) {
			if (E_image[i][j] != s_edge) 
				E_image[i][j] = 0;
		}
	}
}
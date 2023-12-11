
// ImagePro_20212052View.cpp: CImagePro20212052View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_20212052.h"
#endif

#include "ImagePro_20212052Doc.h"
#include "ImagePro_20212052View.h"

#include <math.h>
#include< vfw.h >

#include "CAngleInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImagePro20212052View

IMPLEMENT_DYNCREATE(CImagePro20212052View, CScrollView)

BEGIN_MESSAGE_MAP(CImagePro20212052View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImagePro20212052View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CImagePro20212052View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImagePro20212052View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImagePro20212052View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImagePro20212052View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImagePro20212052View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImagePro20212052View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_BIN, &CImagePro20212052View::OnPixelBin)
	ON_COMMAND(ID_PIXEL_TWO_SUB, &CImagePro20212052View::OnPixelTwoSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CImagePro20212052View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_MEANING, &CImagePro20212052View::OnRegionMeaning)
	ON_COMMAND(ID_REGION_PREWITT, &CImagePro20212052View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROERTS, &CImagePro20212052View::OnRegionRoerts)
	ON_COMMAND(ID_REGION_SOBEL, &CImagePro20212052View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVE_FILTERING, &CImagePro20212052View::OnRegionAveFiltering)
	ON_COMMAND(ID_REGION_MED_FILTERING, &CImagePro20212052View::OnRegionMedFiltering)
	ON_COMMAND(ID_COLOR_TO_GRAY, &CImagePro20212052View::OnColorToGray)
	ON_COMMAND(ID_MOPOLOGY_B, &CImagePro20212052View::OnMopologyB)
	ON_COMMAND(ID_EROSION, &CImagePro20212052View::OnErosion)
	ON_COMMAND(ID_DILATION, &CImagePro20212052View::OnDilation)
	ON_COMMAND(ID_OPENING, &CImagePro20212052View::OnOpening)
	ON_COMMAND(ID_CLOSING, &CImagePro20212052View::OnClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImagePro20212052View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTEROLATION, &CImagePro20212052View::OnGeometryZoominInterolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUB, &CImagePro20212052View::OnGeometryZoomoutSub)
	
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImagePro20212052View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CImagePro20212052View::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImagePro20212052View::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CImagePro20212052View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CImagePro20212052View::OnGeometryFlip)
	ON_COMMAND(ID_GEOMETRY_W, &CImagePro20212052View::OnGeometryW)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CImagePro20212052View::OnAviView)
	ON_COMMAND(ID_PIXEL_HISTO_ST, &CImagePro20212052View::OnPixelHistoSt)
END_MESSAGE_MAP()

// CImagePro20212052View 생성/소멸

CImagePro20212052View::CImagePro20212052View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	bAviMode = false;

}

CImagePro20212052View::~CImagePro20212052View()
{
}

BOOL CImagePro20212052View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImagePro20212052View 그리기

void CImagePro20212052View::OnDraw(CDC*pDC)
{
	CImagePro20212052Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	int y, x;

	if (bAviMode)
	{
		LoadAviFile(pDC);
		bAviMode = false;
		return;
	}
	
	if (pDoc->inputImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3 * x + 0], pDoc->inputImg[y][3 * x + 1], pDoc->inputImg[y][3 * x + 2]));
		}
	}
	if (pDoc->resultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(pDoc->imageWidth + 20 + x, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(pDoc->imageWidth + 20 + x, y, RGB(pDoc->resultImg[y][3 * x + 0], pDoc->resultImg[y][3 * x + 1], pDoc->resultImg[y][3 * x + 2]));

		}
	}

	if (pDoc->inputImg2 != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel((pDoc->imageWidth + 20) * 2 + x, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel((pDoc->imageWidth + 20) * 2 + x, y, RGB(pDoc->inputImg2[y][3 * x + 0], pDoc->inputImg2[y][3 * x + 1], pDoc->inputImg2[y][3 * x + 2]));
		}

	}
	if (pDoc->gResultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
		}
		else
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->gResultImg[y][3 * x + 0], pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));

		}
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CImagePro20212052View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImagePro20212052View 인쇄


void CImagePro20212052View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImagePro20212052View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImagePro20212052View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImagePro20212052View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImagePro20212052View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImagePro20212052View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImagePro20212052View 진단

#ifdef _DEBUG
void CImagePro20212052View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImagePro20212052View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImagePro20212052Doc* CImagePro20212052View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagePro20212052Doc)));
	return (CImagePro20212052Doc*)m_pDocument;
}
#endif //_DEBUG


// CImagePro20212052View 메시지 처리기


void CImagePro20212052View::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->inputImg[y][x] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][x] = value;
			}
			else
			{
				value = pDoc->inputImg[y][3 * x + 0] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 0] = value;

				value = pDoc->inputImg[y][3 * x + 1] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 1] = value;

				value = pDoc->inputImg[y][3 * x + 2] + 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 2] = value;
			}

		}
	Invalidate();
}


void CImagePro20212052View::OnPixelSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;

	int x, y;
	int value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->inputImg[y][x] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][x] = value;
			}
			else
			{
				value = pDoc->inputImg[y][3 * x + 0] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 0] = value;

				value = pDoc->inputImg[y][3 * x + 1] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 1] = value;

				value = pDoc->inputImg[y][3 * x + 2] - 100;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 2] = value;
			}

		}
	Invalidate();
}


void CImagePro20212052View::OnPixelMul()
{
	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y;
	int value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->inputImg[y][x] *1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][x] = value;
			}
			else
			{
				value = pDoc->inputImg[y][3 * x + 0] *1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 0] = value;

				value = pDoc->inputImg[y][3 * x + 1] *1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 1] = value;

				value = pDoc->inputImg[y][3 * x + 2] *1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 2] = value;
			}

		}

	Invalidate();
}


void CImagePro20212052View::OnPixelDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int x, y;
	int value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = pDoc->inputImg[y][x] / 1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][x] = value;
			}
			else
			{
				value = pDoc->inputImg[y][3 * x + 0] / 1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 0] = value;

				value = pDoc->inputImg[y][3 * x + 1] / 1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 1] = value;

				value = pDoc->inputImg[y][3 * x + 2] / 1.5;
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->resultImg[y][3 * x + 2] = value;
			}

		}

	Invalidate();
}


void CImagePro20212052View::OnPixelHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;

	int x, y, k;
	int hist[256], sum[256];
	int acc_hist = 0;
	int N = (float)(pDoc->imageWidth*pDoc->imageHeight);
	/*int rsum[256], gsum[256], bsum[256]; */

	for (k = 0; k < 256; k++)	hist[k] = 0;

	for (y = 0; y <pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
			hist[pDoc->inputImg[y][x]]++;


	for (k = 0; k < 256; k++)
	{
		acc_hist += hist[k];
		sum[k] = acc_hist;
	}

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			
			if (pDoc->depth = 1)
			{
				k = pDoc->inputImg[y][x];
				pDoc->resultImg[y][x] = (float)sum[k] / N * 255;

			}
			else
			{
				k = pDoc->inputImg[y][x];
				pDoc->resultImg[y][3*x+0] = (float)sum[k] / N * 255;
				k = pDoc->inputImg[y][x];
				pDoc->resultImg[y][3 * x + 1] = (float)sum[k] / N * 255;
				k = pDoc->inputImg[y][x];
				pDoc->resultImg[y][3 * x + 2] = (float)sum[k] / N * 255;
			}
		}
	Invalidate();
}


void CImagePro20212052View::OnPixelTwoImageAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->imageHeight; y++)
			for (x = 0; x < pDoc->imageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->resultImg[y][x] = 0.5 * pDoc->inputImg[y][x] + 0.5 * pDoc->inputImg2[y][x];
				}
				else
				{
					pDoc->resultImg[y][3 * x + 0] = 0.5 * pDoc->inputImg[y][3 * x + 0] + 0.5 * pDoc->inputImg2[y][3 * x + 0];
					pDoc->resultImg[y][3 * x + 1] = 0.5 * pDoc->inputImg[y][3 * x + 1] + 0.5 * pDoc->inputImg2[y][3 * x + 1];
					pDoc->resultImg[y][3 * x + 2] = 0.5 * pDoc->inputImg[y][3 * x + 2] + 0.5 * pDoc->inputImg2[y][3 * x + 2];
				}
			}

		Invalidate();
	}
}


void CImagePro20212052View::OnPixelBin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y;
	int therehold = 150;

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++)
		{
			if (pDoc->inputImg[y][x] > therehold) pDoc->resultImg[y][x] = 255;
			else	pDoc->resultImg[y][x] = 0;
		}
	Invalidate();
}


void CImagePro20212052View::OnPixelTwoSub()
{
	// 이거 수정
	CImagePro20212052Doc* pDoc = GetDocument();
	CFileDialog dlg(true);
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for (y = 0; y < pDoc->imageHeight; y++)
			for (x = 0; x < pDoc->imageWidth; x++)
			{
				if (pDoc->depth == 1)
				{
					pDoc->resultImg[y][x] =  pDoc->inputImg[y][x] + 0.5 * pDoc->inputImg2[y][x];
				}
				else
				{
					pDoc->resultImg[y][3 * x + 0] = 0.5 * pDoc->inputImg[y][3 * x + 0] + 0.5 * pDoc->inputImg2[y][3 * x + 0];
					pDoc->resultImg[y][3 * x + 1] = 0.5 * pDoc->inputImg[y][3 * x + 1] + 0.5 * pDoc->inputImg2[y][3 * x + 1];
					pDoc->resultImg[y][3 * x + 2] = 0.5 * pDoc->inputImg[y][3 * x + 2] + 0.5 * pDoc->inputImg2[y][3 * x + 2];
				}
			}

		Invalidate();
	}
}



void CImagePro20212052View::OnRegionSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	float kernel[3][3] = { { 0, -1,  0},
								{-1,  5, -1},
								{ 0, -1,  0} };

	convolve(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImagePro20212052View::convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	for (y = 1; y < rows - 1; y++)
		for (x = 1; x < cols - 1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;
				outimg[y][x] = sum;
			}
			else
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inimg[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}
				rsum += bias;	gsum += bias;	bsum += bias;
				if (rsum > 255)	rsum = 255;
				else if (rsum < 0)	rsum = 0;
				if (gsum > 255)	gsum = 255;
				else if (gsum < 0)	gsum = 0;
				if (bsum > 255)	bsum = 255;
				else if (bsum < 0)	bsum = 0;

				outimg[y][3 * x + 0] = rsum;
				outimg[y][3 * x + 1] = gsum;
				outimg[y][3 * x + 2] = bsum;
			}
		}
}


void CImagePro20212052View::OnRegionMeaning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1.0 / 9.0,1.0 / 9.0,1.0 / 9.0},
							{1.0 / 9.0,1.0 / 9.0,1.0 / 9.0},
							{1.0 / 9.0,1.0 / 9.0,1.0 / 9.0} };

	convolve(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImagePro20212052View::OnRegionPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	float maskH[3][3] = { { -1,  -1,  -1},
							{  0,   0,   0},
							{  1,   1,   1} };
	float maskV[3][3] = { { 1,   0,  -1},
							{ 1,   0,  -1},
							{ 1,   0,  -1} };

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->imageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImg, Er, pDoc->imageWidth, pDoc->imageHeight, maskH, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;
				pDoc->resultImg[y][x] = sum;
			}
			else
			{
				rsum = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rsum > 255)		rsum = 255;
				else if (rsum < 0)	rsum = 0;

				gsum = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gsum > 255)		gsum = 255;
				else if (rsum < 0)	gsum = 0;

				bsum = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bsum > 255)		bsum = 255;
				else if (rsum < 0)	bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255)			sum = 255;
				else if (sum < 0)		sum = 0;

				pDoc->resultImg[y][3 * x + 0] = sum;
				pDoc->resultImg[y][3 * x + 1] = sum;
				pDoc->resultImg[y][3 * x + 2] = sum;
			}
		}

	for (i = 0; i < pDoc->imageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImagePro20212052View::OnRegionRoerts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	float maskH[3][3] = { { -1, 0},
							
							{  0,1} };
	float maskV[3][3] = { {0,  -1},
							
							{ 1,  0} };

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->imageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImg, Er, pDoc->imageWidth, pDoc->imageHeight, maskH, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;

				//이진화
				//if (sum > 150)		sum = 255;
				//else                sum = 0;

				pDoc->resultImg[y][x] = sum;
			}
			else
			{
				rsum = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rsum > 255)		rsum = 255;
				else if (rsum < 0)	rsum = 0;

				gsum = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gsum > 255)		gsum = 255;
				else if (rsum < 0)	gsum = 0;

				bsum = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bsum > 255)		bsum = 255;
				else if (rsum < 0)	bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255)			sum = 255;
				else if (sum < 0)		sum = 0;

				//이진화
				//if (sum > 150)		sum = 255;
				//else                sum = 0;

				pDoc->resultImg[y][3 * x + 0] = sum;
				pDoc->resultImg[y][3 * x + 1] = sum;
				pDoc->resultImg[y][3 * x + 2] = sum;
			}
		}

	for (i = 0; i < pDoc->imageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImagePro20212052View::OnRegionSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	float maskH[3][3] = { { -1,  -2,  -1},
						{  0,   0,   0},
						{  1,   2,   1} };
	float maskV[3][3] = { { 1,   0,  -1},
							{ 2,   0,  -2},
							{ 1,   0,  -1} };

	unsigned char** Er, ** Ec;
	int i, x, y;
	int sum, rsum, gsum, bsum;

	//메모리할당
	Er = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->imageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->imageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->imageWidth * pDoc->depth);
	}

	convolve(pDoc->inputImg, Er, pDoc->imageWidth, pDoc->imageHeight, maskH, 128, pDoc->depth);
	convolve(pDoc->inputImg, Ec, pDoc->imageWidth, pDoc->imageHeight, maskV, 128, pDoc->depth);

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (sum > 255)	sum = 255;
				else if (sum < 0)	sum = 0;

				//이진화
				//if (sum > 150)		sum = 255;
				//else                sum = 0;

				pDoc->resultImg[y][x] = sum;
			}
			else
			{
				rsum = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				if (rsum > 255)		rsum = 255;
				else if (rsum < 0)	rsum = 0;

				gsum = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				if (gsum > 255)		gsum = 255;
				else if (rsum < 0)	gsum = 0;

				bsum = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));
				if (bsum > 255)		bsum = 255;
				else if (rsum < 0)	bsum = 0;

				sum = sqrt(rsum * rsum + gsum * gsum + bsum * bsum);
				if (sum > 255)			sum = 255;
				else if (sum < 0)		sum = 0;

				//이진화
				//if (sum > 150)		sum = 255;
				//else                sum = 0;

				pDoc->resultImg[y][3 * x + 0] = sum;
				pDoc->resultImg[y][3 * x + 1] = sum;
				pDoc->resultImg[y][3 * x + 2] = sum;
			}
		}

	for (i = 0; i < pDoc->imageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImagePro20212052View::OnRegionAveFiltering()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y, i, j;
	int sum, rsum, gsum, bsum;

	//5*5 영역의 평균값
	for (y = 2; y < pDoc->imageHeight - 2; y++)
		for (x = 2; x < pDoc->imageWidth - 2; x++)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < 5; j++)
					for (i = 0; i < 5; i++)
					{
						sum += pDoc->inputImg[y + j - 2][x + i - 2];
					}
				sum /= 25;

				if (sum > 255)		sum = 255;
				else if (sum < 0)		sum = 0;

				pDoc->resultImg[y][x] = sum;
			}
			else
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < 5; j++)
					for (i = 0; i < 5; i++)
					{
						rsum += pDoc->inputImg[y + j - 2][3 * (x + i - 2) + 0];
						gsum += pDoc->inputImg[y + j - 2][3 * (x + i - 2) + 1];
						bsum += pDoc->inputImg[y + j - 2][3 * (x + i - 2) + 2];
					}
				rsum /= 25;		gsum /= 25;		bsum /= 25;

				if (rsum > 255)			rsum = 255;
				else if (rsum < 0)		rsum = 0;
				if (gsum > 255)			gsum = 255;
				else if (gsum < 0)		gsum = 0;
				if (bsum > 255)			bsum = 255;
				else if (bsum < 0)		bsum = 0;

				pDoc->resultImg[y][3 * x + 0] = rsum;
				pDoc->resultImg[y][3 * x + 1] = gsum;
				pDoc->resultImg[y][3 * x + 2] = bsum;
			}
		}

	Invalidate();
}


void CImagePro20212052View::OnRegionMedFiltering()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y, i, j;
	int n[9], temp;

	for (y = 1; y < pDoc->imageHeight - 1; y++)
		for (x = 1; x < pDoc->imageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				n[0] = pDoc->inputImg[y - 1][x - 1];
				n[1] = pDoc->inputImg[y - 1][x + 0];
				n[2] = pDoc->inputImg[y - 1][x + 1];
				n[3] = pDoc->inputImg[y - 0][x - 1];
				n[4] = pDoc->inputImg[y - 0][x + 0];
				n[5] = pDoc->inputImg[y - 0][x + 1];
				n[6] = pDoc->inputImg[y + 1][x - 1];
				n[7] = pDoc->inputImg[y + 1][x + 0];
				n[8] = pDoc->inputImg[y + 1][x + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImg[y][x] = n[4];
			}
			else
			{
				n[0] = pDoc->inputImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->inputImg[y - 1][3 * (x + 0) + 0];
				n[2] = pDoc->inputImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->inputImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->inputImg[y - 0][3 * (x + 0) + 0];
				n[5] = pDoc->inputImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->inputImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->inputImg[y + 1][3 * (x + 0) + 0];
				n[8] = pDoc->inputImg[y + 1][3 * (x + 1) + 0];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImg[y][3 * x + 0] = n[4];

				n[0] = pDoc->inputImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->inputImg[y - 1][3 * (x + 0) + 1];
				n[2] = pDoc->inputImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->inputImg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->inputImg[y - 0][3 * (x + 0) + 1];
				n[5] = pDoc->inputImg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->inputImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->inputImg[y + 1][3 * (x + 0) + 1];
				n[8] = pDoc->inputImg[y + 1][3 * (x + 1) + 1];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImg[y][3 * x + 1] = n[4];

				n[0] = pDoc->inputImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->inputImg[y - 1][3 * (x + 0) + 2];
				n[2] = pDoc->inputImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->inputImg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->inputImg[y - 0][3 * (x + 0) + 2];
				n[5] = pDoc->inputImg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->inputImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->inputImg[y + 1][3 * (x + 0) + 2];
				n[8] = pDoc->inputImg[y + 1][3 * (x + 1) + 2];

				//sorting=오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
					{
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}

				pDoc->resultImg[y][3 * x + 2] = n[4];
			}
		}

	Invalidate();
}


void CImagePro20212052View::OnColorToGray()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->depth == 1)	return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			gray = (pDoc->inputImg[y][3 * x + 0] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2]) / 3;
			pDoc->inputImg[y][3 * x + 0] = gray;
			pDoc->inputImg[y][3 * x + 1] = gray;
			pDoc->inputImg[y][3 * x + 2] = gray;
		}
	Invalidate();
}


void CImagePro20212052View::OnMopologyB()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	int x, y;
	int th = 100;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->inputImg[y][x] > th)
					pDoc->inputImg[y][x] = 255;
				else
					pDoc->inputImg[y][x] = 0;
			}
			else
			{
				if (pDoc->inputImg[y][3 * x + 0] > th)
				{
					pDoc->inputImg[y][3 * x + 0] = 255;
					pDoc->inputImg[y][3 * x + 1] = 255;
					pDoc->inputImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->inputImg[y][3 * x + 0] = 0;
					pDoc->inputImg[y][3 * x + 1] = 0;
					pDoc->inputImg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}


void CImagePro20212052View::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y;
	int min;

	for (y = 1; y < pDoc->imageHeight - 1; y++)
		for (x = 1; x < pDoc->imageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				min = 255;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][x + i - 1] < min)
							min = pDoc->inputImg[y + j - 1][x + i - 1];
					}
				pDoc->resultImg[y][x] = min;
			}
			else
			{
				min = 255;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 0] < min)
							min = pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 0];
					}
				pDoc->resultImg[y][3 * x + 0] = min;

				min = 255;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 1] < min)
							min = pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 1];
					}
				pDoc->resultImg[y][3 * x + 1] = min;

				min = 255;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 2] < min)
							min = pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 2];
					}
				pDoc->resultImg[y][3 * x + 2] = min;
			}
		}
	Invalidate();
}


void CImagePro20212052View::OnDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y;
	int max;

	for (y = 1; y < pDoc->imageHeight - 1; y++)
		for (x = 1; x < pDoc->imageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][x + i - 1] > max)
							max = pDoc->inputImg[y + j - 1][x + i - 1];
					}
				pDoc->resultImg[y][x] = max;
			}
			else
			{
				max = 0;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 0] > max)
							max = pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 0];
					}
				pDoc->resultImg[y][3 * x + 0] = max;

				max = 0;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 1] > max)
							max = pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 1];
					}
				pDoc->resultImg[y][3 * x + 1] = max;

				max = 0;
				for (int j = 0; j < 3; j++)
					for (int i = 0; i < 3; i++)
					{
						if (pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 2] > max)
							max = pDoc->inputImg[y + j - 1][3 * (x + i - 1) + 2];
					}
				pDoc->resultImg[y][3 * x + 2] = max;
			}
		}
	Invalidate();
}

void CImagePro20212052View::CopyResultToInput()
{
	// TODO: 여기에 구현 코드 추가.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			pDoc->inputImg[y][x] = pDoc->resultImg[y][x];
		}
}
void CImagePro20212052View::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnErosion();
	CopyResultToInput();
	OnErosion();
	CopyResultToInput();
	OnErosion();
	CopyResultToInput();

	CopyResultToInput();
	OnDilation();
	CopyResultToInput();
	OnDilation();
	CopyResultToInput();
	OnDilation();
}


void CImagePro20212052View::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	OnDilation();
	CopyResultToInput();
	OnDilation();
	CopyResultToInput();
	OnDilation();
	CopyResultToInput();

	CopyResultToInput();
	OnErosion();
	CopyResultToInput();
	OnErosion();
	CopyResultToInput();
	OnErosion();
}





void CImagePro20212052View::OnGeometryZoominPixelCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	int x, y, i, j;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth * xscale;
	pDoc->gImageHeight = pDoc->imageHeight * yscale;
	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	/*	// 전방향사상
		for(y=0;y<pDoc->imageHeight;y++)
			for (x = 0; x < pDoc->imageWidth; x++)
			{
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
						if (pDoc->depth == 1)
						{
							pDoc->gResultImg[yscale * y + j][xscale * x + i] = pDoc->inputImg[y][x];
						}
						else
						{
							pDoc->gResultImg[yscale * y + j][3 * (xscale * x + i) + 0] = pDoc->inputImg[y][3 * x + 0];
							pDoc->gResultImg[yscale * y + j][3 * (xscale * x + i) + 1] = pDoc->inputImg[y][3 * x + 1];
							pDoc->gResultImg[yscale * y + j][3 * (xscale * x + i) + 2] = pDoc->inputImg[y][3 * x + 2];
						}
			}
	*/
	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->inputImg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 2];
			}
		}

	Invalidate();
}


void CImagePro20212052View::OnGeometryZoominInterolation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	int x, y, i, j;

	float xscale = 2.6;
	float yscale = 1.3;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth * xscale;
	pDoc->gImageHeight = pDoc->imageHeight * yscale;
	// 메모리 
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;

			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->imageWidth - 1)	Bx = pDoc->imageWidth - 1;
			if (Cy > pDoc->imageHeight - 1)	Cy = pDoc->imageHeight - 1;
			if (Dx > pDoc->imageWidth - 1)	Dx = pDoc->imageWidth - 1;
			if (Dy > pDoc->imageHeight - 1)	Dy = pDoc->imageHeight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->inputImg[Ay][Ax] + alpha * pDoc->inputImg[By][Bx];
				F = (1 - alpha) * pDoc->inputImg[Cy][Cx] + alpha * pDoc->inputImg[Dy][Dx];
				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 0] + alpha * pDoc->inputImg[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 0] + alpha * pDoc->inputImg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 1] + alpha * pDoc->inputImg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 1] + alpha * pDoc->inputImg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 2] + alpha * pDoc->inputImg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 2] + alpha * pDoc->inputImg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}

		}

	Invalidate();
}


void CImagePro20212052View::OnGeometryZoomoutSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y, i, j;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth / xscale;
	pDoc->gImageHeight = pDoc->imageHeight / yscale;
	
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->inputImg[y * yscale][x * xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 2];
			}

		}

	Invalidate();
}




void CImagePro20212052View::OnGeometryZoomoutMeanSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	OnRegionMeaning();
	CopyResultToInput();
	OnGeometryZoomoutSub();
}


void CImagePro20212052View::OnGeometryZoomoutAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y, i, j;
	int src_x, src_y;
	int sum,rsum,gsum,bsum;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth / xscale;
	pDoc->gImageHeight = pDoc->imageHeight / yscale;
	// 메모리
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향
	for (y = 0; y < pDoc->imageHeight - yscale; y += yscale)
		for (x = 0; x < pDoc->imageWidth - xscale; x += xscale)
		{
			sum = 0; rsum = 0; gsum = 0; bsum = 0;
			for (j = 0; j < yscale; j++)
				for (i = 0; i < xscale; i++)
				{
					src_x = x + i;
					src_y = y + j;
					sum += pDoc->inputImg[src_y][src_x];
					rsum += pDoc->inputImg[src_y][3*src_x+0];
					gsum += pDoc->inputImg[src_y][3*src_x+1];
					bsum += pDoc->inputImg[src_y][3*src_x+2];
					if(pDoc->depth=1)
					pDoc->gResultImg[y / yscale][x / xscale] = sum / (xscale * yscale);
					else
					{
						pDoc->gResultImg[y / yscale][3*(x / xscale)+0] = sum / ((3*xscale+0) * yscale);
						pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = sum / ((3 * xscale + 1) * yscale);
						pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = sum / ((3 * xscale + 2) * yscale);
					}
				}
			

		}
	Invalidate();

}

#define PI 3.141596521
void CImagePro20212052View::OnGeometryRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	CAngleInputDlg dlg;

	int angle = 30;	// degree
	float radian;
	int x, y, i;
	int Cx, Cy, Hy;
	int x_source, y_source;
	int xdiff, ydiff;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL)
		return;
	angle = dlg.m_iAngle;

	radian = PI / 180 * angle;

	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageHeight * fabs(cos(PI / 2 - radian)) +
		pDoc->imageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->imageHeight * fabs(cos(radian)) +
		pDoc->imageWidth * fabs(cos(PI / 2 - radian));
	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//중심점
	Cx = pDoc->imageWidth / 2;
	Cy = pDoc->imageHeight / 2;
	//y의 마지막좌표
	Hy = pDoc->imageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->imageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->imageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = ((Hy - y) - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - (((Hy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1)
			{
				if (x_source<0 || x_source>pDoc->imageWidth - 1 ||
					y_source<0 || y_source>pDoc->imageHeight - 1)
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->inputImg[y_source][x_source];
			}
			else
			{
				if (x_source<0 || x_source>pDoc->imageWidth - 1 ||
					y_source<0 || y_source>pDoc->imageHeight - 1)
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->inputImg[y_source][3 * (x_source)+0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->inputImg[y_source][3 * (x_source)+1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->inputImg[y_source][3 * (x_source)+2];

				}
			}
		}
	Invalidate();
}


void CImagePro20212052View::OnGeometryMirror()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				pDoc->resultImg[y][pDoc->imageWidth - 1 - x] = pDoc->inputImg[y][x];
			}
			else
			{
				pDoc->resultImg[y][3 * (pDoc->imageWidth - 1 - x) + 0] = pDoc->inputImg[y][3 * x + 0];
				pDoc->resultImg[y][3 * (pDoc->imageWidth - 1 - x) + 1] = pDoc->inputImg[y][3 * x + 1];
				pDoc->resultImg[y][3 * (pDoc->imageWidth - 1 - x) + 2] = pDoc->inputImg[y][3 * x + 2];
			}
		}

	Invalidate();
}


void CImagePro20212052View::OnGeometryFlip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				pDoc->resultImg[pDoc->imageHeight - 1 - y][x] = pDoc->inputImg[y][x];
			}
			else
			{
				pDoc->resultImg[pDoc->imageHeight - 1 - y][3 * (x)+0] = pDoc->inputImg[y][3 * x + 0];
				pDoc->resultImg[pDoc->imageHeight - 1 - y][3 * (x)+1] = pDoc->inputImg[y][3 * x + 1];
				pDoc->resultImg[pDoc->imageHeight - 1 - y][3 * (x)+2] = pDoc->inputImg[y][3 * x + 2];
			}
		}

	Invalidate();
}


typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = { 100,100,150,150 };
control_line mctrl_dest = { 100,100,200,200 };

void CImagePro20212052View::OnGeometryW()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();

	control_line source_lines[5] = { {100,100,150,150},
		{0,0,pDoc->imageWidth - 1,0},
		{pDoc->imageWidth - 1,0,pDoc->imageWidth - 1,pDoc->imageHeight - 1},
		{pDoc->imageWidth - 1,pDoc->imageHeight - 1,0,pDoc->imageHeight - 1},
		{0,pDoc->imageHeight - 1,0,0} };
	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->imageWidth - 1,0},
		{pDoc->imageWidth - 1,0,pDoc->imageWidth - 1,pDoc->imageHeight - 1},
		{pDoc->imageWidth - 1,pDoc->imageHeight - 1,0,pDoc->imageHeight - 1},
		{0,pDoc->imageHeight - 1,0,0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;

	double u;	// 수직 교차점의 위치
	double h;	// 제어선으로부터 픽셀의 수직변위
	double d;	// 제어선과 픽셀 사이의 거리 
	double tx, ty;		// 결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
	double xp, yp;	// 각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치   
	double weight;	// 각 제어선의 가중치 
	double totalweight;		// 가중치의 합   
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, y1, x2, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;	// 제어선의수
	int line;
	int source_x, source_y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;
			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0)		d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1)	d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else				d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalweight += weight;
			}

			source_x = x + tx / totalweight;
			source_y = y + ty / totalweight;

			if (source_x < 0)			source_x = 0;
			else if (source_x > pDoc->imageWidth - 1)		source_x = pDoc->imageWidth - 1;
			if (source_y < 0)			source_y = 0;
			else if (source_y > pDoc->imageHeight - 1)		source_y = pDoc->imageHeight - 1;

			if (pDoc->depth == 1)
			{
				pDoc->resultImg[y][x] = pDoc->inputImg[source_y][source_x];
			}
			else
			{
				pDoc->resultImg[y][3 * x + 0] = pDoc->inputImg[source_y][3 * source_x + 0];
				pDoc->resultImg[y][3 * x + 1] = pDoc->inputImg[source_y][3 * source_x + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->inputImg[source_y][3 * source_x + 2];
			}
		}

	Invalidate();
}

CPoint mpos_st, mpos_end;
void CImagePro20212052View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}

void CImagePro20212052View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	pDC->SelectObject(&pen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);
	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx)	mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else				mctrl_source.Px = Ax + (Ax - Bx) / 2;

	if (Ay < By)	mctrl_source.Py = Ay - (By - Ay) / 2;
	else				mctrl_source.Py = Ay + (Ay - By) / 2;

	// 기준위치
	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}

void CImagePro20212052View::OnAviView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"AVI파일(*.avi)|*.avi|모든파일(*.*)|*.*|");

	if (dlg.DoModal() == IDOK)
	{
		AVIFileName = dlg.GetPathName();
		bAviMode = true;
		Invalidate();
	}
}

void CImagePro20212052View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;

	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++)
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < si.dwLength; frame++)
			{
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih)	continue;

				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/*
				for(y=0;y<fi.dwHeight;y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight-1-y,
							RGB(image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
					}
				*/
				pDC->SetStretchBltMode(COLORONCOLOR);
				::SetDIBitsToDevice(pDC->GetSafeHdc(),
					0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth,
					image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(30);
			}

		}
	}
	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();
}

void CImagePro20212052View::OnPixelHistoSt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImagePro20212052Doc* pDoc = GetDocument();
	if (pDoc->inputImg == NULL) return;
	
	int x, y;
	int low = 255, high = 0;

	for(y=0;y<pDoc->imageHeight;y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->inputImg[y][x] < low)
				low = pDoc->inputImg[y][x];
		}

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->inputImg[y][x] > high	)
				high = pDoc->inputImg[y][x];
		}
	float mult = 255.0f / (float)(high - low);
	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			pDoc->resultImg[y][x] = (unsigned char)((pDoc->inputImg[y][x] - low) * mult);

		}
	Invalidate();
}

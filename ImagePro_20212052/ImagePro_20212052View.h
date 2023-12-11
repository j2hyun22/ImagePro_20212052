
// ImagePro_20212052View.h: CImagePro20212052View 클래스의 인터페이스
//

#pragma once


class CImagePro20212052View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImagePro20212052View() noexcept;
	DECLARE_DYNCREATE(CImagePro20212052View)

// 특성입니다.
public:
	CImagePro20212052Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImagePro20212052View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelBin();
	afx_msg void OnPixelTwoSub();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionMeaning();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoerts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAveFiltering();
	afx_msg void OnRegionMedFiltering();
	afx_msg void OnColorToGray();
	afx_msg void OnMopologyB();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnOpening();
	afx_msg void OnClosing();
	void CopyResultToInput();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterolation();
	afx_msg void OnGeometryZoomoutSub();
	afx_msg void OnGeometryZoomoutSharp();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryZoomoutAvg();
	afx_msg void OnGeometryRotate();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnGeometryW();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CString AVIFileName;
	bool bAviMode;
	void LoadAviFile(CDC* pDC);
	afx_msg void OnAviView();
	afx_msg void OnPixelHistoSt();
};

#ifndef _DEBUG  // ImagePro_20212052View.cpp의 디버그 버전
inline CImagePro20212052Doc* CImagePro20212052View::GetDocument() const
   { return reinterpret_cast<CImagePro20212052Doc*>(m_pDocument); }
#endif


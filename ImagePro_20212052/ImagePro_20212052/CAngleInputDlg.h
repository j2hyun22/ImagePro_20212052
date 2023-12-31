#pragma once


// CAngleInputDlg 대화 상자

class CAngleInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAngleInputDlg)

public:
	CAngleInputDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAngleInputDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_iAngle;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk1();
};

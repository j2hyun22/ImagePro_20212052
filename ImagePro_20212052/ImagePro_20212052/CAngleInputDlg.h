#pragma once


// CAngleInputDlg ��ȭ ����

class CAngleInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAngleInputDlg)

public:
	CAngleInputDlg(CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
	virtual ~CAngleInputDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_iAngle;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk1();
};

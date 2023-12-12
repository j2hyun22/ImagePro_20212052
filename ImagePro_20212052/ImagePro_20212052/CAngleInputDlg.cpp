// CAngleInputDlg.cpp: ���� ����
//

#include "pch.h"
#include "ImagePro_20212052.h"
#include "CAngleInputDlg.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(CAngleInputDlg, CDialogEx)

CAngleInputDlg::CAngleInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANGLE, pParent)
	, m_iAngle(0)
{

}

CAngleInputDlg::~CAngleInputDlg()
{
}

void CAngleInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleInputDlg, CDialogEx)
	
	ON_BN_CLICKED(IDOK1, &CAngleInputDlg::OnBnClickedOk1)
END_MESSAGE_MAP()


// CAngleInputDlg �޽��� ó����




void CAngleInputDlg::OnBnClickedOk1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}

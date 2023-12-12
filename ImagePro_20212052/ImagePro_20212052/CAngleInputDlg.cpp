// CAngleInputDlg.cpp: 구현 파일
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


// CAngleInputDlg 메시지 처리기




void CAngleInputDlg::OnBnClickedOk1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

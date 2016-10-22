
// MFC_ScreenShotView.cpp : CMFC_ScreenShotView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFC_ScreenShot.h"
#endif

#include "MFC_ScreenShotDoc.h"
#include "MFC_ScreenShotView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_ScreenShotView

IMPLEMENT_DYNCREATE(CMFC_ScreenShotView, CView)

BEGIN_MESSAGE_MAP(CMFC_ScreenShotView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SHOT_WIND, &CMFC_ScreenShotView::OnShotWind)
	ON_COMMAND(ID_SHOT_RECT, &CMFC_ScreenShotView::OnShotRect)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_SHOT_RECT, &CMFC_ScreenShotView::OnUpdateShotRect)
END_MESSAGE_MAP()

// CMFC_ScreenShotView ����/����

CMFC_ScreenShotView::CMFC_ScreenShotView()
{
	// TODO: �ڴ˴���ӹ������
	m_bLButtonDown = FALSE; // ������������Ϊ��
	m_bErase = FALSE; // ����Ҫ����Ϊ��
	pGrayPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // ������ɫ���߱�

	pHollowBrush = new CBrush();
	pHollowBrush->CreateStockObject(NULL_BRUSH);//��ˢ

	isRectShot = false;
}

CMFC_ScreenShotView::~CMFC_ScreenShotView()
{
}

BOOL CMFC_ScreenShotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFC_ScreenShotView ����

void CMFC_ScreenShotView::OnDraw(CDC* /*pDC*/)
{
	CMFC_ScreenShotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFC_ScreenShotView ��ӡ

BOOL CMFC_ScreenShotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFC_ScreenShotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFC_ScreenShotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFC_ScreenShotView ���

#ifdef _DEBUG
void CMFC_ScreenShotView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_ScreenShotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_ScreenShotDoc* CMFC_ScreenShotView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_ScreenShotDoc)));
	return (CMFC_ScreenShotDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_ScreenShotView ��Ϣ�������


void CMFC_ScreenShotView::OnShotWind()
{
	// TODO: �ڴ���������������
	HDC hdc = ::GetDC(NULL); // ��ȡ��ĻDC�ľ��
	CDC screenDC; // �������ĻDC����
	screenDC.Attach(hdc); // ������ĻDC���
	CDC mdc; // ������ڴ�DC����
	mdc.CreateCompatibleDC(&screenDC); // ��������ĻDC���ݵ��ڴ�DC
	CBitmap bmp, *pOldBmp; // ����λͼ�����ָ��
	int w = GetDeviceCaps(hdc, HORZRES); // ��ȡ��Ļ�����أ�
	int h = GetDeviceCaps(hdc, VERTRES); // ��ȡ��Ļ�ߣ����أ�
										 // ��������ĻDC���ݵ�λͼ����
	bmp.CreateCompatibleBitmap(&screenDC, w, h);
	pOldBmp = mdc.SelectObject(&bmp); // ��λͼѡ���ڴ�DC
	GetTopLevelFrame()->ShowWindow(SW_HIDE); // ���س��򴰿�
	Sleep(500); // ����һ�Σ�0.5�룩ʱ��
				// ץȡ��Ļ��ͼ���ڴ�DC�е�ͼ��
	mdc.BitBlt(0, 0, w, h, &screenDC, 0, 0, SRCCOPY);
	GetTopLevelFrame()->ShowWindow(SW_SHOW); // ��ʾ���򴰿�
											 // �����ļ��Ի���Ҫ�õ���չ����������
	wchar_t filters[] = L"λͼ�ļ�(*.bmp)|*.bmp|ͼ�ν�����ʽ�ļ�(*.gif)|*.gif|\����ͼ��ר����[JPEG]�ļ�(*.jpg)|*.jpg|����ֲ����ͼ���ļ�(*.png)|*.png|�����ļ�(*.*)|*.*||";
	CFileDialog fileDlg(FALSE, L"bmp", L"s.bmp", OFN_HIDEREADONLY, filters);// falseΪ���棬trueΪ��
	if (fileDlg.DoModal() == IDOK) {
		CImage img;
		img.Attach(bmp);
		img.Save(fileDlg.GetPathName());
	}
	mdc.SelectObject(pOldBmp);
	bmp.DeleteObject();
	screenDC.Detach();
	::ReleaseDC(NULL, hdc);

}


void CMFC_ScreenShotView::OnShotRect()
{
	// TODO: �ڴ���������������
	isRectShot = !isRectShot;
}


void CMFC_ScreenShotView::OnUpdateShotRect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (isRectShot) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CMFC_ScreenShotView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isRectShot) {
		SetCapture();
		m_bLButtonDown = TRUE;
		p0 = point;// ���ζԽ���һ��
		pm = p0;// ���ζԽ�����һ��
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMFC_ScreenShotView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isRectShot) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//���ÿ�ˢ���
			if (m_bErase) {
				pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			}
			else {
				m_bErase = TRUE;
			}
			pDC->Rectangle(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			pm = point;
			ReleaseDC(pDC);//��ӦGetDC
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CMFC_ScreenShotView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isRectShot) {
		ReleaseCapture();
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//�������
			pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));

			// ��ͼ
			CDC mdc; // �����ڴ�DC
			mdc.CreateCompatibleDC(pDC); // �����뵱ǰDC���ݵ��ڴ�DC
			CBitmap bmp; // ����λͼ���������ڴ�DC�еĻ�����
						 // �������Ϊw��h���뵱ǰDC���ݵ�λͼ
			int w = abs(p0.x - point.x);
			int h = abs(p0.y - point.y);
			bmp.CreateCompatibleBitmap(pDC, w, h);
			mdc.SelectObject(&bmp); // ����λͼѡ���ڴ�DC
									// ��ָ�����δ����ڴ�DC���е�λͼ��
			mdc.BitBlt(0, 0, w, h, pDC, min(p0.x, point.x), min(p0.y, point.y), SRCCOPY);
			
			wchar_t filters[] = L"λͼ�ļ�(*.bmp)|*.bmp|ͼ�ν�����ʽ�ļ�(*.gif)|*.gif|\����ͼ��ר����[JPEG]�ļ�(*.jpg)|*.jpg|����ֲ����ͼ���ļ�(*.png)|*.png|�����ļ�(*.*)|*.*||";
			CFileDialog fileDlg(FALSE, L"bmp", L"s.bmp", OFN_HIDEREADONLY, filters);// falseΪ���棬trueΪ��
			if (fileDlg.DoModal() == IDOK) {
				CImage img;
				img.Attach(bmp);
				img.Save(fileDlg.GetPathName());
			}

			bmp.DeleteObject();
			mdc.Detach();


			//��ԭ����
			m_bLButtonDown = FALSE;
			m_bErase = FALSE;
			ReleaseDC(pDC);
		}
	}

	CView::OnLButtonUp(nFlags, point);
}

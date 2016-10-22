
// MFC_ScreenShotView.cpp : CMFC_ScreenShotView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CMFC_ScreenShotView 构造/析构

CMFC_ScreenShotView::CMFC_ScreenShotView()
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown = FALSE; // 设左鼠标键按下为假
	m_bErase = FALSE; // 设需要擦除为假
	pGrayPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // 创建灰色点线笔

	pHollowBrush = new CBrush();
	pHollowBrush->CreateStockObject(NULL_BRUSH);//空刷

	isRectShot = false;
}

CMFC_ScreenShotView::~CMFC_ScreenShotView()
{
}

BOOL CMFC_ScreenShotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC_ScreenShotView 绘制

void CMFC_ScreenShotView::OnDraw(CDC* /*pDC*/)
{
	CMFC_ScreenShotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFC_ScreenShotView 打印

BOOL CMFC_ScreenShotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC_ScreenShotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC_ScreenShotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFC_ScreenShotView 诊断

#ifdef _DEBUG
void CMFC_ScreenShotView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_ScreenShotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_ScreenShotDoc* CMFC_ScreenShotView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_ScreenShotDoc)));
	return (CMFC_ScreenShotDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_ScreenShotView 消息处理程序


void CMFC_ScreenShotView::OnShotWind()
{
	// TODO: 在此添加命令处理程序代码
	HDC hdc = ::GetDC(NULL); // 获取屏幕DC的句柄
	CDC screenDC; // 定义空屏幕DC对象
	screenDC.Attach(hdc); // 连接屏幕DC句柄
	CDC mdc; // 定义空内存DC对象
	mdc.CreateCompatibleDC(&screenDC); // 创建与屏幕DC兼容的内存DC
	CBitmap bmp, *pOldBmp; // 定义位图对象和指针
	int w = GetDeviceCaps(hdc, HORZRES); // 获取屏幕宽（像素）
	int h = GetDeviceCaps(hdc, VERTRES); // 获取屏幕高（像素）
										 // 创建与屏幕DC兼容的位图对象
	bmp.CreateCompatibleBitmap(&screenDC, w, h);
	pOldBmp = mdc.SelectObject(&bmp); // 将位图选入内存DC
	GetTopLevelFrame()->ShowWindow(SW_HIDE); // 隐藏程序窗口
	Sleep(500); // 休眠一段（0.5秒）时间
				// 抓取屏幕截图到内存DC中的图像
	mdc.BitBlt(0, 0, w, h, &screenDC, 0, 0, SRCCOPY);
	GetTopLevelFrame()->ShowWindow(SW_SHOW); // 显示程序窗口
											 // 保存文件对话框要用的扩展名过滤器串
	wchar_t filters[] = L"位图文件(*.bmp)|*.bmp|图形交换格式文件(*.gif)|*.gif|\联合图象专家组[JPEG]文件(*.jpg)|*.jpg|可移植网络图形文件(*.png)|*.png|所有文件(*.*)|*.*||";
	CFileDialog fileDlg(FALSE, L"bmp", L"s.bmp", OFN_HIDEREADONLY, filters);// false为保存，true为打开
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
	// TODO: 在此添加命令处理程序代码
	isRectShot = !isRectShot;
}


void CMFC_ScreenShotView::OnUpdateShotRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (isRectShot) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CMFC_ScreenShotView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isRectShot) {
		SetCapture();
		m_bLButtonDown = TRUE;
		p0 = point;// 矩形对角线一点
		pm = p0;// 矩形对角线另一点
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMFC_ScreenShotView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isRectShot) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//设置空刷填充
			if (m_bErase) {
				pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			}
			else {
				m_bErase = TRUE;
			}
			pDC->Rectangle(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			pm = point;
			ReleaseDC(pDC);//对应GetDC
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CMFC_ScreenShotView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isRectShot) {
		ReleaseCapture();
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//设置填充
			pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));

			// 截图
			CDC mdc; // 定义内存DC
			mdc.CreateCompatibleDC(pDC); // 创建与当前DC兼容的内存DC
			CBitmap bmp; // 定义位图对象（用作内存DC中的画布）
						 // 创建宽高为w、h并与当前DC兼容的位图
			int w = abs(p0.x - point.x);
			int h = abs(p0.y - point.y);
			bmp.CreateCompatibleBitmap(pDC, w, h);
			mdc.SelectObject(&bmp); // 将该位图选入内存DC
									// 将指定矩形传入内存DC（中的位图）
			mdc.BitBlt(0, 0, w, h, pDC, min(p0.x, point.x), min(p0.y, point.y), SRCCOPY);
			
			wchar_t filters[] = L"位图文件(*.bmp)|*.bmp|图形交换格式文件(*.gif)|*.gif|\联合图象专家组[JPEG]文件(*.jpg)|*.jpg|可移植网络图形文件(*.png)|*.png|所有文件(*.*)|*.*||";
			CFileDialog fileDlg(FALSE, L"bmp", L"s.bmp", OFN_HIDEREADONLY, filters);// false为保存，true为打开
			if (fileDlg.DoModal() == IDOK) {
				CImage img;
				img.Attach(bmp);
				img.Save(fileDlg.GetPathName());
			}

			bmp.DeleteObject();
			mdc.Detach();


			//还原参数
			m_bLButtonDown = FALSE;
			m_bErase = FALSE;
			ReleaseDC(pDC);
		}
	}

	CView::OnLButtonUp(nFlags, point);
}

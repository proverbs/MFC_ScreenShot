
// MFC_ScreenShotView.h : CMFC_ScreenShotView 类的接口
//

#pragma once


class CMFC_ScreenShotView : public CView
{
protected: // 仅从序列化创建
	CMFC_ScreenShotView();
	DECLARE_DYNCREATE(CMFC_ScreenShotView)

// 特性
public:
	CMFC_ScreenShotDoc* GetDocument() const;

	BOOL m_bLButtonDown, // 判断是否按下左鼠标键
		m_bErase; // 是否需要擦除图形
	CPoint p0, pm; // 记录直线起点和动态终点
	CPen *pGrayPen;// 定义灰色笔的对象指针，用于动态画图时的边框显示
	CBrush *pHollowBrush; // 空刷，用于封闭图形动态画图

	bool isRectShot;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFC_ScreenShotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShotWind();
	afx_msg void OnShotRect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUpdateShotRect(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // MFC_ScreenShotView.cpp 中的调试版本
inline CMFC_ScreenShotDoc* CMFC_ScreenShotView::GetDocument() const
   { return reinterpret_cast<CMFC_ScreenShotDoc*>(m_pDocument); }
#endif



// MFC_ScreenShotView.h : CMFC_ScreenShotView ��Ľӿ�
//

#pragma once


class CMFC_ScreenShotView : public CView
{
protected: // �������л�����
	CMFC_ScreenShotView();
	DECLARE_DYNCREATE(CMFC_ScreenShotView)

// ����
public:
	CMFC_ScreenShotDoc* GetDocument() const;

	BOOL m_bLButtonDown, // �ж��Ƿ���������
		m_bErase; // �Ƿ���Ҫ����ͼ��
	CPoint p0, pm; // ��¼ֱ�����Ͷ�̬�յ�
	CPen *pGrayPen;// �����ɫ�ʵĶ���ָ�룬���ڶ�̬��ͼʱ�ı߿���ʾ
	CBrush *pHollowBrush; // ��ˢ�����ڷ��ͼ�ζ�̬��ͼ

	bool isRectShot;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFC_ScreenShotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MFC_ScreenShotView.cpp �еĵ��԰汾
inline CMFC_ScreenShotDoc* CMFC_ScreenShotView::GetDocument() const
   { return reinterpret_cast<CMFC_ScreenShotDoc*>(m_pDocument); }
#endif


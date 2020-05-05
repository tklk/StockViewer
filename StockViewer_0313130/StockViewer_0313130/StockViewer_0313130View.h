
// StockViewer_0313130View.h : CStockViewer_0313130View 類別的介面
//

#pragma once


class CStockViewer_0313130View : public CView
{
protected: // 僅從序列化建立
	CStockViewer_0313130View();
	DECLARE_DYNCREATE(CStockViewer_0313130View)

// 屬性
public:
	CStockViewer_0313130Doc* GetDocument() const;

// 作業
public:
	int shift;
	int techindex;
	int period;
	int color;
	CPoint pt;
	CPoint pt2;
	//日月線轉換
	int ptperiod;
	int currentshift;
	int numDWM;

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CStockViewer_0313130View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPrevious();
	afx_msg void OnNext();
	afx_msg void OnFirst();
	afx_msg void OnLast();
	afx_msg void OnUpdatePrevious(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFirst(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLast(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNone();
	afx_msg void OnKd();
	afx_msg void OnUpdateNone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateKd(CCmdUI *pCmdUI);
	afx_msg void OnMacd();
	afx_msg void OnUpdateMacd(CCmdUI *pCmdUI);
	afx_msg void OnDay();
	afx_msg void OnWeek();
	afx_msg void OnMonth();
	afx_msg void OnUpdateDay(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWeek(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMonth(CCmdUI *pCmdUI);
	afx_msg void OnWhite();
	afx_msg void OnBlack();
	afx_msg void OnUpdateWhite(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBlack(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // StockViewer_0313130View.cpp 中的偵錯版本
inline CStockViewer_0313130Doc* CStockViewer_0313130View::GetDocument() const
   { return reinterpret_cast<CStockViewer_0313130Doc*>(m_pDocument); }
#endif


//  �t�d�Ҧ���ƳB�z
// StockViewer_0313130Doc.h : CStockViewer_0313130Doc ���O������
//
#include "stock.h"

#pragma once


class CStockViewer_0313130Doc : public CDocument
{
protected: // �ȱq�ǦC�ƫإ�
	CStockViewer_0313130Doc();
	DECLARE_DYNCREATE(CStockViewer_0313130Doc)

// �ݩ�
public:
	CStock data;
// �@�~
public:

// �мg
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �{���X��@
public:
	virtual ~CStockViewer_0313130Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ���j�M�B�z�`���]�w�j�M���e�� Helper �禡
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

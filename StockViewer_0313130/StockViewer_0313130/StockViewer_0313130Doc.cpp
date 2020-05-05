
// StockViewer_0313130Doc.cpp : CStockViewer_0313130Doc 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "StockViewer_0313130.h"
#endif

#include "StockViewer_0313130Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStockViewer_0313130Doc

IMPLEMENT_DYNCREATE(CStockViewer_0313130Doc, CDocument)

BEGIN_MESSAGE_MAP(CStockViewer_0313130Doc, CDocument)
END_MESSAGE_MAP()


// CStockViewer_0313130Doc 建構/解構

CStockViewer_0313130Doc::CStockViewer_0313130Doc()
{
	// TODO:  在此加入一次建構程式碼

}

CStockViewer_0313130Doc::~CStockViewer_0313130Doc()
{
}

BOOL CStockViewer_0313130Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)

	return TRUE;
}




// CStockViewer_0313130Doc 序列化

void CStockViewer_0313130Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此加入儲存程式碼
	}
	else
	{
		int i;
		CString fn = ar.GetFile()->GetFilePath(); // 取得檔案路徑與檔名
		char *filename = new char[fn.GetLength() + 1];
		for (i = 0; i < fn.GetLength(); i++)
			filename[i] = fn[i];
		filename[i] = '\0';
		data.Read(filename);

		// TODO:  在此加入載入程式碼
	}
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CStockViewer_0313130Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜尋處理常式的支援
void CStockViewer_0313130Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開

	// 範例:     strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CStockViewer_0313130Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CStockViewer_0313130Doc 診斷

#ifdef _DEBUG
void CStockViewer_0313130Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStockViewer_0313130Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStockViewer_0313130Doc 命令

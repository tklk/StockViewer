
// StockViewer_0313130Doc.cpp : CStockViewer_0313130Doc ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
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


// CStockViewer_0313130Doc �غc/�Ѻc

CStockViewer_0313130Doc::CStockViewer_0313130Doc()
{
	// TODO:  �b���[�J�@���غc�{���X

}

CStockViewer_0313130Doc::~CStockViewer_0313130Doc()
{
}

BOOL CStockViewer_0313130Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �b���[�J���s��l�Ƶ{���X
	// (SDI ���|���Φ����)

	return TRUE;
}




// CStockViewer_0313130Doc �ǦC��

void CStockViewer_0313130Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �b���[�J�x�s�{���X
	}
	else
	{
		int i;
		CString fn = ar.GetFile()->GetFilePath(); // ���o�ɮ׸��|�P�ɦW
		char *filename = new char[fn.GetLength() + 1];
		for (i = 0; i < fn.GetLength(); i++)
			filename[i] = fn[i];
		filename[i] = '\0';
		data.Read(filename);

		// TODO:  �b���[�J���J�{���X
	}
}

#ifdef SHARED_HANDLERS

// �Y�Ϫ��䴩
void CStockViewer_0313130Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �ק�o�q�{���X�Hø�s��󪺸��
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

// �j�M�B�z�`�����䴩
void CStockViewer_0313130Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// �]�w�Ӧۤ���ƪ��j�M���e�C
	// ���e�������ӥH ";" �j�}

	// �d��:     strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CStockViewer_0313130Doc �E�_

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


// CStockViewer_0313130Doc �R�O

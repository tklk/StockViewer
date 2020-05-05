// Stock.cpp : ��@��
//

#include "stdafx.h"
#include "StockViewer_0313130.h"
#include "Stock.h"
#include "math.h"


// CStock

IMPLEMENT_DYNAMIC(CStock, CWnd)

CStock::CStock()
{
	num = 0;
	date = NULL;
	open = NULL;
	close = NULL;
	high = NULL;
	low = NULL;
	vol = NULL;
	adjust = NULL;
	
	MA5 = NULL;
	MA10 = NULL;
	MA20 = NULL;
	MV5 = NULL;
	MV20 = NULL;

	RSV = NULL;
	rsvMAX = NULL;
	rsvMIN = NULL;
	K9 = NULL;
	D9 = NULL;

	DI = NULL;
	EMA12 = NULL;
	EMA26 = NULL;
	DIF = NULL;
	MACD = NULL;
	OSC = NULL;
	
	openDWM = NULL;
	highDWM = NULL;
	lowDWM = NULL;
	closeDWM = NULL;
	volDWM = NULL;
	dateDWM = NULL;
}

CStock::~CStock()
{
	if (open != NULL)
		delete [] open;
	if (close != NULL)
		delete[] close;
	if (high != NULL)
		delete [] high;
	if (low != NULL)
		delete[] low;
	if (vol != NULL)
		delete[] vol;
	if (adjust != NULL)
		delete[] adjust;

	if (MA5 != NULL)
		delete[] MA5;
	if (MA10 != NULL)
		delete[] MA10;
	if (MA20 != NULL)
		delete[] MA20;
	if (MV5 != NULL)
		delete[] MV5;
	if (MV20 != NULL)
		delete[] MV20;

	if (RSV != NULL)
		delete[] RSV;
	if (rsvMAX != NULL)
		delete[] rsvMAX;
	if (rsvMIN != NULL)
		delete[] rsvMIN;
	if (K9 != NULL)
		delete[] K9;
	if (D9 != NULL)
		delete[] D9;

	if (DI != NULL)
		delete[] DI;
	if (EMA12 != NULL)
		delete[] EMA12;
	if (EMA26 != NULL)
		delete[] EMA26;
	if (DIF != NULL)
		delete[] DIF;
	if (MACD != NULL)
		delete[] MACD;
	if (OSC != NULL)
		delete[] OSC;

	if (openDWM != NULL)
		delete[] openDWM;
	if (highDWM != NULL)
		delete[] highDWM;
	if (lowDWM != NULL)
		delete[] lowDWM;
	if (closeDWM != NULL)
		delete[] closeDWM;
	if (volDWM != NULL)
		delete[] volDWM;
	if (dateDWM != NULL)
		delete[] dateDWM;
}

void CStock::Read(char* filename)
{
	FILE* fid;
	fopen_s(&fid, filename, "r");
	fscanf_s(fid, "%d", &num);
	if (date != NULL)
		delete[] date;
	date = new int[num];
	if (open != NULL)
		delete[] open;
	open = new double[num];
	if (close != NULL)
		delete[] close;
	close = new double[num];
	if (high != NULL)
		delete[] high;
	high = new double[num];
	if (low != NULL)
		delete[] low;
	low = new double[num];
	if (vol != NULL)
		delete[] vol;
	vol = new int[num];
	if (adjust != NULL)
		delete[] adjust;
	adjust = new double[num];

	if (MA5 != NULL)
		delete[] MA5;
	MA5 = new double[num];
	if (MA10 != NULL)
		delete[] MA10;
	MA10 = new double[num];
	if (MA20 != NULL)
		delete[] MA20;
	MA20 = new double[num];
	if (MV5 != NULL)
		delete[] MV5;
	MV5 = new double[num];
	if (MV20 != NULL)
		delete[] MV20;
	MV20 = new double[num];

	if (RSV != NULL)
		delete[] RSV;
	RSV = new double[num];
	if (rsvMAX != NULL)
		delete[] rsvMAX;
	rsvMAX = new double[num];
	if (rsvMIN != NULL)
		delete[] rsvMIN;
	rsvMIN = new double[num];
	if (K9 != NULL)
		delete[] K9;
	K9 = new double[num];
	if (D9 != NULL)
		delete[] D9;
	D9 = new double[num];
	if (DI != NULL)
		delete[] DI;
	DI = new double[num];
	if (EMA12 != NULL)
		delete[] EMA12;
	EMA12 = new double[num];
	if (EMA26 != NULL)
		delete[] EMA26;
	EMA26 = new double[num];
	if (DIF != NULL)
		delete[] DIF;
	DIF = new double[num];
	if (MACD != NULL)
		delete[] MACD;
	MACD = new double[num];
	if (OSC != NULL)
		delete[] OSC;
	OSC = new double[num];

	if (openDWM != NULL)
		delete[] openDWM;
	openDWM = new double[num];
	if (highDWM != NULL)
		delete[] highDWM;
	highDWM = new double[num];
	if (lowDWM != NULL)
		delete[] lowDWM;
	lowDWM = new double[num];
	if (closeDWM != NULL)
		delete[] closeDWM;
	closeDWM = new double[num];
	if (volDWM != NULL)
		delete[] volDWM;
	volDWM = new double[num];
	if (dateDWM != NULL)
		delete[] dateDWM;
	dateDWM = new int[num];
	for (int i = 0; i < num; i++)//////fid �O��򲾨�U�@�C��?
	{
		fscanf_s(fid, "%d,", &date[i]);
		fscanf_s(fid, "%lf,", &open[i]);
		fscanf_s(fid, "%lf,", &high[i]);
		fscanf_s(fid, "%lf,", &low[i]);
		fscanf_s(fid, "%lf,", &close[i]);
		fscanf_s(fid, "%ld,", &vol[i]);
		fscanf_s(fid, "%lf", &adjust[i]);
	}
	fclose(fid);
}

double CStock::QueryAdjust(int date1)
{
	for (int i = 0; i < num; i++)
	{
		if (date[i] == date1)
			return adjust[i];
	}
	return -1;
}

void CStock::Draw(CDC* pDC2, int H, int W, int shift, CPoint pt2, int techindex, int period, int color)
{
	if (num == 0)
		return;
	// �s�e��
	CDC* m_pMemDC;
	CBitmap* m_pBitmap;
	m_pMemDC = new CDC();
	m_pBitmap = new CBitmap();
	m_pMemDC->CreateCompatibleDC(pDC2);
	m_pBitmap->CreateCompatibleBitmap(pDC2, W, H);
	m_pMemDC->SelectObject(m_pBitmap);
	if (color==1)
		m_pMemDC->FloodFill(5, 5, RGB(255, 255, 255));
	else
		m_pMemDC->FloodFill(5, 5, RGB(0, 0, 0));
	CDC* pDC;
	pDC = m_pMemDC;
	//
	CPen Rpen, Gpen, OBpen, OWpen, Dpen, MA5pen, MA10pen, MA20pen, Mousepen, Wpen;
	CBrush Rbrush(RGB(255, 0, 0)), Gbrush(RGB(0, 128, 0)), Mousebrush(RGB(0, 85, 255));
	Rpen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // ����
	Gpen.CreatePen(PS_SOLID, 1, RGB(0, 128, 0)); // ��
	OBpen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // �²ʵ�
	OWpen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // �ղʵ�
	Dpen.CreatePen(PS_DASH, 1, RGB(200, 200, 200)); // ��u��
	MA5pen.CreatePen(PS_SOLID, 1, RGB(0, 43, 255)); // �`�ŵ�
	MA10pen.CreatePen(PS_SOLID, 1, RGB(241, 168, 10)); // �ﵧ
	MA20pen.CreatePen(PS_SOLID, 1, RGB(0, 178, 51)); // �G��
	Mousepen.CreatePen(PS_SOLID, 2, RGB(0, 85, 255)); // �G�ŵ�
	Wpen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // �յ�

	int i = 0;
	int t = 0;
	int x, x1, x2, y1, y2, y3, y4, y5;
	
	int margin1, margin2, margin3, margin4; // ���u���Z
	double copen, chigh, clow, cclose, cmark; // �̤W���
	int cvol;  // �̤W���
	double sum;
	double popen, phigh, plow, pclose;
	int k; // ����
	double y_MA; // MA y�y��
	double cMA5, cMA10, cMA20; // �g MA5 MA10  MA20 ���
	double cK9, cD9, cRSV; // �޳N����
	int cMV5, cMV20; // �g MV5 MV20 ���
	double y_MV; // MV y�y��
	int cdate, cday, cmonth, lmonth, cyear, lyear; // �ɶ����
	double cMACD, cDIF, cEMA12, cEMA26; // �޳N����
	// ��u��u�g�u
	int numDWM, remainder, denominator;
	if (period == 0)
	{
		numDWM = num;
		for (i = 0; i < num; i++)
		{
			openDWM[i] = open[i];
			highDWM[i] = high[i];
			lowDWM[i] = low[i];
			closeDWM[i] = close[i];
			volDWM[i] = vol[i];
			dateDWM[i] = date[i];
		}
	}
	else if (period == 1)
	{
		remainder = num % 5;
		k = 5;
		if (remainder != 0)
		{
			numDWM = num / 5 + 1;		
			for (i = 0; i < numDWM; i++)
			{
				sum = 0;
				popen = 0;
				pclose = 0;
				if (i == 0)
				{
					denominator = remainder;
					t = i * 5;
				}
				else
				{
					denominator = k;
					t = remainder - 1 + (i - 1) * 5;
				}
				phigh = high[t];
				plow = low[t];
				for (int j = 0; j < denominator; j++)
				{
					if (phigh < high[t + j])
						phigh = high[t + j];
					if (plow > low[t + j])
						plow = low[t + j];
					sum = sum + vol[t + j];
					if (j == 0)
						closeDWM[i] = close[t + j];
					if (j == denominator - 1)
						openDWM[i] = open[t + j];
				}
				highDWM[i] = phigh;
				lowDWM[i] = plow;
				volDWM[i] = sum;
				if (i == 0)
					dateDWM[i] = date[i];
				else
					dateDWM[i] = date[i * 5 + remainder - 1];
			}	
		}
		else
		{
			numDWM = num / 5;
			for (i = 0; i < numDWM; i++)
			{
				sum = 0;
				popen = 0;
				pclose = 0;
				t = i * 5;
				phigh = high[t];
				plow = low[t];
				for (int j = 0; j < k; j++)
				{
					if (phigh < high[t + j])
						phigh = high[t + j];
					if (plow > low[t + j])
						plow = low[t + j];
					sum = sum + vol[t + j];
					if (j == 0)
						closeDWM[i] = close[t + j];
					if (j == k - 1)
						openDWM[i] = open[t + j];
				}
				highDWM[i] = phigh;
				lowDWM[i] = plow;
				volDWM[i] = sum;
				dateDWM[i] = date[t];
			}
		}
	}
	else
	{
		remainder = num % 20;
		k = 20;
		if (remainder != 0)
		{
			numDWM = num / 20 + 1;
			for (i = 0; i < numDWM; i++)
			{
				sum = 0;
				popen = 0;
				pclose = 0;
				if (i == 0)
				{
					denominator = remainder;
					t = i * 20;
				}
				else
				{
					denominator = k;
					t = remainder - 1 + (i - 1) * 20;
				}
				phigh = high[t];
				plow = low[t];
				for (int j = 0; j < denominator; j++)
				{
					if (phigh < high[t + j])
						phigh = high[t + j];
					if (plow > low[t + j])
						plow = low[t + j];
					sum = sum + vol[t + j];
					if (j == 0)
						closeDWM[i] = close[t + j];
					if (j == denominator - 1)
						openDWM[i] = open[t + j];
				}
				highDWM[i] = phigh;
				lowDWM[i] = plow;
				volDWM[i] = sum;
				if (i == 0)
					dateDWM[i] = date[i];
				else
					dateDWM[i] = date[i * 20 + remainder - 1];
			}
		}
		else
		{
			numDWM = num / 20;
			for (i = 0; i < numDWM; i++)
			{
				sum = 0;
				popen = 0;
				pclose = 0;
				t = i * 20;
				phigh = high[t];
				plow = low[t];
				for (int j = 0; j < k; j++)
				{
					if (phigh < high[t + j])
						phigh = high[t + j];
					if (plow > low[t + j])
						plow = low[t + j];
					sum = sum + vol[t + j];
					if (j == 0)
						closeDWM[i] = close[t + j];
					if (j == k - 1)
						openDWM[i] = open[t + j];
				}
				highDWM[i] = phigh;
				lowDWM[i] = plow;
				volDWM[i] = sum;
				dateDWM[i] = date[t];
			}
		}
	}

	CString str;
	
	double minprice = lowDWM[shift];
	double maxprice = highDWM[shift];
	double maxvol = volDWM[shift];
	int maxy = 20 + 16;
	int miny = H / 2;
	int maxy2 = miny + 20;
	int miny2 = H * 3 / 4; // int miny2 = miny + 100;
	int maxy3 = miny2 + 20 + 16;
	int miny3 = H - 15;
	/*
	int miny3 = miny2 + 120 + 16;
	int maxy4 = miny3 + 20;
	int miny4 = miny3 + 120;
	*/
	for (i = 0; i < (W - 45) / 10; i++)
	{
		if (maxprice < highDWM[i + shift])
		{
			maxprice = highDWM[i + shift];
		}
		if (minprice > lowDWM[i + shift])
		{
			minprice = lowDWM[i + shift];
		}
		if (maxvol < volDWM[i + shift])
		{
			maxvol = volDWM[i + shift];
		}
	}

	// �D������u
	pDC->SelectObject(&Dpen);
	if (maxprice - minprice < 10)
		margin1 = 1;
	else if (maxprice - minprice < 50)
		margin1 = 5;
	else if (maxprice - minprice < 100)
		margin1 = 10;
	else if (maxprice - minprice < 1000)
		margin1 = 100;
	else
		margin1 = 1000;
	for (i = (int)(minprice / margin1 + 1)*margin1; i <= (int)(maxprice / margin1)*margin1; i += margin1)
	{
		y1 = (i - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
		if (maxy < y1 && miny > y1)
		{
			pDC->MoveTo(5, y1);
			pDC->LineTo(W - 40, y1);
		}

		str.Format(_T("%d"), i);
		if (color==1)
			pDC->SetTextColor(RGB(0, 0, 0));
		else
		{
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 255));
		}
		pDC->TextOutW(W - 38, y1, str);
	}
	// ����q��u 
	if (maxvol < 500000) // ����q�p�󤭤Q�U
		margin2 = 100000;
	else if (maxvol < 1000000) // ����q�p��1�ʸU Alphabet
		margin2 = 500000;
	else if (maxvol < 5000000) // ����q�p�󤭦ʸU IBM
		margin2 = 1000000;
	else if (maxvol < 10000000)// ����q�j��@�d�U
		margin2 = 5000000;
	else if (maxvol < 50000000)// ����q�j�󤭤d�U
		margin2 = 10000000;
	else if (maxvol < 100000000)// ����q�j��@��
		margin2 = 50000000;
	else
		margin2 = 100000000;
	for (i = 1 * margin2; i <= (int)(maxvol / margin2)*margin2; i += margin2)
	{
		//y1 = miny2 - (miny2 - maxy2)*i / maxvol;
		y1 = i / maxvol*(maxy2 - miny2) + miny2;
		if (maxy2 < y1 && miny2 >y1)
		{
			pDC->MoveTo(5, y1);
			pDC->LineTo(W - 40, y1);
		}
		if (i < 1000000)
		{
			str.Format(_T("%dK"), i / 1000);
		}
		else
		{
			str.Format(_T("%dM"), i / 1000000);
		}
		if (color == 1)
			pDC->SetTextColor(RGB(0, 0, 0));
		else
		{
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 255));
		}
		pDC->TextOutW(W - 38, y1, str);
	}
	if (techindex == 1)
	{
		// RSV K9 D9 ��u
		int h3= (miny3 - maxy3) / 4;
		for (i = h3; i <= h3 * 3; i += h3)
		{
			y1 = miny3 - i - 8;
			pDC->MoveTo(5, y1 + 8);
			pDC->LineTo(W - 40, y1 + 8);
			if (i == h3)
			{
				str.Format(_T("%d"), 20);
			}
			else if (i == 2 * h3)
			{
				str.Format(_T("%d"), 50);
			}
			else
			{
				str.Format(_T("%d"), 80);
			}

			if (color == 1)
				pDC->SetTextColor(RGB(0, 0, 0));
			else
			{
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));
			}
			pDC->TextOutW(W - 38, y1, str);
		}
	}
	
	// �e���u
	for (int i = W - 45 - 100; i > 5; i = i - 100)
	{
		pDC->MoveTo(i, miny);
		pDC->LineTo(i, maxy);
		pDC->MoveTo(i, miny2);
		pDC->LineTo(i, maxy2);
		if (techindex != 0)
		{
			pDC->MoveTo(i, miny3);
			pDC->LineTo(i, maxy3);
		}
	}
	// �D�������
	for (i = 0; i < (W - 45) / 10; i++)
	{
		x = W - (10 * i) - 45;	
		x1 = x - 4;
		x2 = x + 4;
		y1 = (highDWM[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
		y2 = (closeDWM[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
		y3 = (openDWM[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
		y4 = (lowDWM[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
		y5 = (volDWM[i + shift] - 0) / (maxvol - 0)*(maxy2 - miny2) + miny2;
		if (openDWM[i + shift] <= closeDWM[i + shift])
		{
			pDC->SelectObject(&Rpen);
			pDC->SelectObject(&Rbrush);
			pDC->MoveTo(x1, y2);
			pDC->LineTo(x1, y3);
			pDC->LineTo(x2, y3);
			pDC->LineTo(x2, y2);
			pDC->LineTo(x1, y2);
			pDC->FloodFill(x, (y2 + y3) / 2, RGB(255, 0, 0)); // ����
			pDC->MoveTo(x, y1);
			pDC->LineTo(x, y4);
			//����q
			pDC->MoveTo(x1, y5);
			pDC->LineTo(x1, miny2);
			pDC->LineTo(x2, miny2);
			pDC->LineTo(x2, y5);
			pDC->LineTo(x1, y5);
			pDC->FloodFill(x, (miny2 + y5) / 2, RGB(255, 0, 0));
		}
		else
		{
			pDC->SelectObject(&Gpen);
			pDC->SelectObject(&Gbrush);
			pDC->MoveTo(x1, y2);
			pDC->LineTo(x1, y3);
			pDC->LineTo(x2, y3);
			pDC->LineTo(x2, y2);
			pDC->LineTo(x1, y2);
			pDC->FloodFill(x, (y2 + y3) / 2, RGB(0, 128, 0)); // ���
			pDC->MoveTo(x, y1);
			pDC->LineTo(x, y4);
			//����q
			pDC->MoveTo(x1, y5);
			pDC->LineTo(x1, miny2);
			pDC->LineTo(x2, miny2);
			pDC->LineTo(x2, y5);
			pDC->LineTo(x1, y5);
			pDC->FloodFill(x, (miny2 + y5) / 2, RGB(0, 128, 0));
		}
	}
	// 9�ѳ̰� 9�ѳ̧C
	for (i = numDWM - 9; i>-1; i--)
	{
		rsvMAX[i] = highDWM[i];
		rsvMIN[i] = lowDWM[i];
		for (int j = i; j < i + 9; j++)
		{
			if (highDWM[j] > rsvMAX[i])
			{
				rsvMAX[i] = highDWM[j];
			}
			if (lowDWM[j] < rsvMIN[i])
			{
				rsvMIN[i] = lowDWM[j];
			}
		}
	}
	// ��RSV
	for (i = 0; i < numDWM - 8; i++)
	{
		RSV[i] = (closeDWM[i] - rsvMIN[i]) / (rsvMAX[i] - rsvMIN[i]) * 100;
	}
	// ��K9 and D9
	for (i = numDWM - 8; i > -1; i--)
	{
		if (i == numDWM - 8)
		{
			K9[i] = 50;
		}
		else
		{
			K9[i] = (RSV[i] + 2 * K9[i + 1]) / 3;
		}
	}
	for (i = numDWM - 8; i > -1; i--)
	{
		if (i == numDWM - 8)
		{
			D9[i] = 50;
		}
		else
		{
			D9[i] = (K9[i] + 2 * D9[i + 1]) / 3;
		}
	}

	if (techindex == 1)
	{
		// �eRSV
		pDC->SelectObject(&MA20pen);
		for (i = 0; i < (W - 45) / 10; i++)
		{
			if (i + shift < numDWM - 7)
			{
				x = W - 45 - 10 * i;
				y1 = (RSV[i + shift] - 0) / (100 - 0)*(maxy3 - miny3) + miny3;
				if (i == 0)
				{
					pDC->MoveTo(x, y1);
				}
				else
				{
					pDC->LineTo(x, y1);
				}
			}	
		}
		// �eK9
		pDC->SelectObject(&MA5pen);
		for (int i = 0; i < (W - 45) / 10; i++)
		{
			if (i + shift < numDWM - 7)
			{
				x = W - 45 - 10 * i;
				y1 = (K9[i + shift] - 0) / (100 - 0)*(maxy3 - miny3) + miny3;
				if (i == 0)
				{
					pDC->MoveTo(x, y1);
				}
				else
				{
					pDC->LineTo(x, y1);
				}
			}
		}
		// �eD9
		pDC->SelectObject(&MA10pen);
		for (int i = 0; i < (W - 45) / 10; i++)
		{
			if (i + shift < numDWM - 7)
			{
				x = W - 45 - 10 * i;
				y1 = (D9[i + shift] - 0) / (100 - 0)*(maxy3 - miny3) + miny3;
				if (i == 0)
				{
					pDC->MoveTo(x, y1);
				}
				else
				{
					pDC->LineTo(x, y1);
				}
			}
		}
	}
	// ��DI
	for (i = 0; i < numDWM; i++)
	{
		DI[i] = (highDWM[i] + lowDWM[i] + 2 * closeDWM[i]) / 4;
	}
	// ��EMA12
	for (i = numDWM - 12; i>-1; i--) // for (i = num - 1; i>-1; i--)
	{
		if (i == numDWM - 12) // if (i == num - 1)
		{
			sum = 0;
			for (int k = 0; k < 12; k++)
			{
				sum = sum + DI[i + k];
			}
			EMA12[i] = sum / 12;
		}
		else
		{
			EMA12[i] = (2 * closeDWM[i] + 11 * EMA12[i + 1]) / 13;
		}
	}
	/*
	for (i = 0; i < num - 11; i++) // for (i = 0; i < num - 11; i++)
	{
		
		sum = 0;
		for (int k = 0; k < 12; k++) // for (int k = 0; k < 12; k++)
		{
			sum = sum + DI[i + k];
		}
		EMA12[i] = sum / 12;
	}
	*/
	// ��EMA26
	for (i = numDWM - 26; i>-1; i--) // for (i = num - 1; i>-1; i--)
	{
		if (i == numDWM - 26) // if (i == num - 1)
		{
			sum = 0;
			for (int k = 0; k < 25; k++)
			{
				sum = sum + DI[i + k];
			}
			EMA26[i] = sum / 26;
		}
		else
		{
			EMA26[i] = (2 * closeDWM[i] + 25 * EMA26[i + 1]) / 27;
		}
	}
	/*
	for (i = 0; i < num - 25; i++) // for (i = 0; i < num - 25; i++)
	{
		
		sum = 0;
		for (int k = 0; k < 25; k++)
		{
			sum = sum + DI[i + k];
		}
		EMA26[i] = sum / 26;
	}
	*/
	// ��DIF
	/*
	for (i = 0; i < num; i++)
	{
		DIF[i] = EMA12[i] - EMA26[i];
	}
	*/
	for (i = 0; i < numDWM; i++) // for (i = 0; i < num - 25; i++)
	{
		if (i < numDWM - 25)
		{
			DIF[i] = EMA12[i] - EMA26[i];
		}
		else
		{
			DIF[i] = 0;
		}
	}
	// ��MACD
	for (i = numDWM - 1; i > -1; i--) // for (i = num - 34; i > -1; i--)
	{
		if (i > numDWM - 34) // if (i > num - 34) 36
		{
			MACD[i] = 0;
		}
		else if (i == numDWM - 34) // else if (i == num - 34)
		{
			sum = 0;
			for (int k = 1; k < 9; k++) // for (int k = 0; k < 9; k++)
			{
				sum = sum + DIF[i + k];
			}
			MACD[i] = sum / 9;
		}
		else
		{
			MACD[i] = (MACD[i + 1] * (9-1) + DIF[i]*2) / (9+1);
		}
	}
	// �� OSC
	for (i = 0; i < numDWM; i++) // for (i = 0; i < num - 33; i++) 37
	{
		if (i < numDWM - 33)
		{
			OSC[i] = DIF[i] - MACD[i];
		}
		else
		{
			OSC[i] = 0;
		}
	}
	// �e �޳N�u2
	double maxDIF = DIF[shift];
	double minDIF = DIF[shift];
	double maxMACD = MACD[shift];
	double minMACD = MACD[shift];
	double maxOSC = OSC[shift];
	double minOSC = OSC[shift];
	double maxTECH2 = DIF[shift];
	double minTECH2 = DIF[shift];
	for (i = 0; i < (W - 45) / 10; i++)
	{
		if (maxTECH2 < DIF[i + shift])
		{
			maxTECH2 = DIF[i + shift];
		}
		if (minTECH2 > DIF[i + shift])
		{
			minTECH2 = DIF[i + shift];
		}

		if (maxTECH2 < MACD[i + shift])
		{
			maxTECH2 = MACD[i + shift];
		}
		if (minTECH2 > MACD[i + shift])
		{
			minTECH2 = MACD[i + shift];
		}

		if (maxTECH2 < OSC[i + shift])
		{
			maxTECH2 = OSC[i + shift];
		}
		if (minTECH2 > OSC[i + shift])
		{
			minTECH2 = OSC[i + shift];
		}		
	}
	if (techindex == 2)
	{
		// �޳N����2 ��u���
		if (maxTECH2 < 5)
		{
			margin3 = 1;
		}
		else if (maxTECH2 < 10)
		{
			margin3 = 5;
		}
		else if (maxTECH2 < 20)
		{
			margin3 = 10;
		}
		else if (maxTECH2 < 30)
		{
			margin3 = 15;
		}
		else
		{
			margin3 = 20;
		}
		if (minTECH2 > -5)
		{
			margin4 = 1;
		}
		else if (minTECH2 > -10)
		{
			margin4 = 5;
		}
		else if (minTECH2 > -20)
		{
			margin4 = 10;
		}
		else if (minTECH2 > -30)
		{
			margin4 = 15;
		}
		else
		{
			margin4 = 20;
		}
		/*
		if (margin3 < margin4)
		margin3 = margin4;
		*/
		pDC->SelectObject(&Dpen);
		for (i = 0; i <= (int)(maxTECH2 / margin3)*margin3; i += margin3)
		{
			y1 = i / maxTECH2*(maxy3 - miny3) / 2 + (miny3 + maxy3) / 2;
			pDC->MoveTo(5, y1);
			pDC->LineTo(W - 40, y1);

			str.Format(_T("%d"), i);
			if (color == 1)
				pDC->SetTextColor(RGB(0, 0, 0));
			else
			{
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));
			}
			pDC->TextOutW(W - 38, y1 - 8, str);
		}
		for (i = margin4; i <= (int)(abs(minTECH2) / margin4)*margin4; i += margin4)
		{
			y1 = (miny3 + maxy3) / 2 - i / abs(minTECH2)*(maxy3 - miny3) / 2;
			pDC->MoveTo(5, y1);
			pDC->LineTo(W - 40, y1);
			str.Format(_T("-%d"), i);
			if (color == 1)
				pDC->SetTextColor(RGB(0, 0, 0));
			else
			{
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));
			}
			pDC->TextOutW(W - 38, y1 - 8, str);
		}
		// �eDIF
		pDC->SelectObject(&MA10pen);
		for (int i = 0; i < (W - 45) / 10; i++)
		{
			x = W - 45 - 10 * i;
			y1 = (DIF[i + shift] - 0) / (maxTECH2 - 0)*(maxy3 - miny3) / 2 + (miny3 + maxy3) / 2; // y1 = (DIF[i + shift] - 0) / (maxDIF - 0)*(maxy4 - miny4) / 2 + miny4 - 50;
			y2 = (0 - DIF[i + shift]) / (0 - minTECH2)*(miny3 - maxy3) / 2 + (miny3 + maxy3) / 2; // y2 = (0 - DIF[i + shift]) / (0 - minDIF)*(miny4 - maxy4) / 2 + miny4 - 50;
			if (i == 0)
			{
				if (DIF[i + shift] >= 0)
					pDC->MoveTo(x, y1);
				else
					pDC->MoveTo(x, y2);
			}
			else
			{
				if (DIF[i + shift] >= 0)
					pDC->LineTo(x, y1);
				else
					pDC->LineTo(x, y2);
			}
		}
		// �eMACD
		pDC->SelectObject(&MA5pen);
		for (int i = 0; i < (W - 45) / 10; i++)
		{
			x = W - 45 - 10 * i; // TECH2
			// y1 = (MACD[i + shift] - minMACD) / (maxMACD - minMACD)*(maxy4 - miny4) + miny4;
			y1 = (MACD[i + shift] - 0) / (maxTECH2 - 0)*(maxy3 - miny3) / 2 + (miny3 + maxy3) / 2; // y1 = (MACD[i + shift] - 0) / (maxMACD - 0)*(maxy4 - miny4)/2 + miny4-50;
			y2 = (0 - MACD[i + shift]) / (0 - minTECH2)*(miny3 - maxy3) / 2 + (miny3 + maxy3) / 2; // y2 = (0 - MACD[i + shift]) / (0 - minMACD)*(miny4 - maxy4) / 2 + miny4 - 50;
			if (i == 0)
			{
				if (MACD[i + shift] >= 0)
					pDC->MoveTo(x, y1);
				else
					pDC->MoveTo(x, y2);
			}
			else
			{
				if (MACD[i + shift] >= 0)
					pDC->LineTo(x, y1);
				else
					pDC->LineTo(x, y2);
			}
		}
		// �eOSC�W����
		for (i = 0; i < (W - 45) / 10 && i + shift < numDWM - 33; i++)
		{
			x = W - 45 - 10 * i;
			x1 = x + 4;
			x2 = x - 4; // TECH2
			y1 = (OSC[i + shift] - 0) / (maxTECH2 - 0)*(maxy3 - miny3) / 2 + (miny3 + maxy3) / 2; // y1 = (OSC[i + shift] - 0) / (maxOSC - 0)*(maxy4 - miny4) / 2 + miny4 - 50;
			y2 = (0 - OSC[i + shift]) / (0 - minTECH2)*(miny3 - maxy3) / 2 + (miny3 + maxy3) / 2; // y2 = (0 - OSC[i + shift]) / (0 - minOSC)*(miny4 - maxy4) / 2 + miny4 - 50;
			if (OSC[i + shift] >= 0)
			{
				pDC->SelectObject(&Rpen);
				pDC->SelectObject(&Rbrush);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x1, (miny3 + maxy3) / 2);
				pDC->LineTo(x2, (miny3 + maxy3) / 2);
				pDC->LineTo(x2, y1);
				pDC->LineTo(x1, y1);
				pDC->FloodFill(x, ((miny3 + maxy3) / 2 + y1) / 2, RGB(255, 0, 0));
			}
			else
			{
				pDC->SelectObject(&Gpen);
				pDC->SelectObject(&Gbrush);
				pDC->MoveTo(x1, y2);
				pDC->LineTo(x1, (miny3 + maxy3) / 2);
				pDC->LineTo(x2, (miny3 + maxy3) / 2);
				pDC->LineTo(x2, y2);
				pDC->LineTo(x1, y2);
				pDC->FloodFill(x, ((miny3 + maxy3) / 2 + y2) / 2, RGB(0, 128, 0));
			}
		}
	}
	// �e�~��(�D����)
	if (color==1)
		pDC->SelectObject(&OBpen);
	else
		pDC->SelectObject(&OWpen);
	pDC->MoveTo(5, miny);
	pDC->LineTo(W - 40, miny);
	pDC->LineTo(W - 40, maxy);
	pDC->LineTo(5, maxy);
	pDC->LineTo(5, miny);
	// �e�~��(����q)
	pDC->MoveTo(5, miny2);
	pDC->LineTo(W - 40, miny2);
	pDC->LineTo(W - 40, maxy2);
	pDC->LineTo(5, maxy2);
	pDC->LineTo(5, miny2);
	// �e�~��(�޳N�uK9 D9)
	if (techindex != 0)
	{
		pDC->MoveTo(5, miny3);
		pDC->LineTo(W - 40, miny3);
		pDC->LineTo(W - 40, maxy3);
		pDC->LineTo(5, maxy3);
		pDC->LineTo(5, miny3);
	}
	// �̤W���
	i = (W - 40 - pt2.x) / 10; //�P�_�ƹ��b���@�����
	if (pt2.x < W - 45 && pt2.x > 5 && pt2.y < miny && pt2.y > maxy)
	{
		if (i >= 0 && i <= (W - 45) / 10 & i + shift < numDWM)
		{
			copen = openDWM[i + shift];
			chigh = highDWM[i + shift];
			clow = lowDWM[i + shift];
			cclose = closeDWM[i + shift];
			cvol = volDWM[i + shift];
			if (i + shift == numDWM - 1)
			{
				cmark = 0;
			}
			else
			{
				cmark = (closeDWM[i + shift] - closeDWM[i + shift + 1]) / closeDWM[i + shift + 1];
			}
			if (period == 0)
			{
				str.Format(_T("�} %.2f  �� %.2f  �C %.2f  �� %.2f  �q %i  ���^ %.2f    ��u"), copen, chigh, clow, cclose, cvol, cmark);
			}
			else if (period == 1)
			{
				str.Format(_T("�} %.2f  �� %.2f  �C %.2f  �� %.2f  �q %i  ���^ %.2f    �g�u"), copen, chigh, clow, cclose, cvol, cmark);
			}
			else
			{
				str.Format(_T("�} %.2f  �� %.2f  �C %.2f  �� %.2f  �q %i  ���^ %.2f    ��u"), copen, chigh, clow, cclose, cvol, cmark);
			}
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(5, 0, str); // ���q
		}
	}
	str.Format(_T("%.1f"), maxprice);
	if (color == 1)
		pDC->SetTextColor(RGB(0, 0, 0));
	else
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 255));
	}
	pDC->TextOutW(W - 38, maxy, str);
	
	// ��MA5
	pDC->SelectObject(&MA5pen);

	k = 5;
	for (int i = 0; i < numDWM - k; i++)
	{
		sum = 0;
		for (int j = 0; j < k; j++)
		{
			sum = sum + closeDWM[i + j];
		}
		MA5[i] = sum / k;
	}
	// �eMA5
	for (int i = 0; i < (W - 45) / 10; i++)
	{
		if (i + shift < numDWM - 4)
		{
			x = W - 45 - 10 * i;
			y_MA = (MA5[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
			if (i == 0)
			{
				pDC->MoveTo(x, y_MA);
			}
			else
			{
				if (y_MA < maxy)
					pDC->LineTo(x, maxy);
				else if (y_MA > miny)
					pDC->LineTo(x, miny);
				else
					pDC->LineTo(x, y_MA);
			}
		}
	}

	// ��MA10
	pDC->SelectObject(&MA10pen);
	k = 10;
	for (int i = 0; i < numDWM - k; i++)
	{
		sum = 0;
		for (int j = 0; j < k; j++)
		{
			sum = sum + closeDWM[i + j];
		}
		MA10[i] = sum / k;
	}
	// �eMA10
	for (int i = 0; i < (W - 45) / 10; i++)
	{
		if (i + shift < numDWM - 9)
		{
			x = W - 45 - 10 * i;
			y_MA = (MA10[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
			if (i == 0)
			{
				pDC->MoveTo(x, y_MA);
			}
			else
			{
				if (y_MA < maxy)
					pDC->LineTo(x, maxy);
				else if (y_MA > miny)
					pDC->LineTo(x, miny);
				else
					pDC->LineTo(x, y_MA);
			}
		}
	}

	// ��MA20
	pDC->SelectObject(&MA20pen);
	k = 20;
	for (int i = 0; i < numDWM - k; i++)
	{
		sum = 0;
		for (int j = 0; j < k; j++)
		{
			sum = sum + closeDWM[i + j];
		}
		MA20[i] = sum / k;
	}
	// �eMA20
	for (int i = 0; i < (W - 45) / 10; i++)
	{
		if (i + shift < numDWM - 19)
		{
			x = W - 45 - 10 * i;
			y_MA = (MA20[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
			if (i == 0)
			{
				pDC->MoveTo(x, y_MA);
			}
			else
			{
				if (y_MA < maxy)
					pDC->LineTo(x, maxy);
				else if (y_MA > miny)
					pDC->LineTo(x, miny);
				else
					pDC->LineTo(x, y_MA);
			}
		}
	}
	// �g MA5 MA10 MA20 ���
	i = (W - 40 - pt2.x) / 10; //�P�_�ƹ��b���@�����
	if (i >= 0 && i <= (W - 45) / 10)
	{
		cMA5 = MA5[i + shift];
		cMA10 = MA10[i + shift];
		cMA20 = MA20[i + shift];
		y1 = 18; // �W��
		y2 = 28; // �U��
		str.Format(_T("MA5"));
		pDC->SetTextColor(RGB(0, 43, 255));
		pDC->TextOutW(5, 16, str); // MA5
		str.Format(_T("MA10"));
		pDC->SetTextColor(RGB(241, 168, 10));
		pDC->TextOutW(119, 16, str); // MA10
		str.Format(_T("MA20"));
		pDC->SetTextColor(RGB(0, 178, 51));
		pDC->TextOutW(239, 16, str); // MA20
		if (numDWM - i - shift > 5)
		{
			str.Format(_T("%.1f"), cMA5);
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(40, 16, str);
			//�����
			x1 = 85;
			x2 = 95;
			x = (x1 + x2) / 2;
			if (MA5[i + shift + 1] - MA5[i + shift] < 0)
			{
				pDC->SelectObject(&Rpen);
				pDC->SelectObject(&Rbrush);
				pDC->MoveTo(x1, y2);
				pDC->LineTo(x2, y2);
				pDC->LineTo(x, y1);
				pDC->LineTo(x1, y2);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
			}
			else
			{
				pDC->SelectObject(&Gpen);
				pDC->SelectObject(&Gbrush);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y1);
				pDC->LineTo(x, y2);
				pDC->LineTo(x1, y1);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
			}
		}
		else
		{
			str.Format(_T(" --"));
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(40, 16, str);
		}
		if (numDWM - i - shift > 10)
		{
			str.Format(_T(" %.1f"), cMA10);
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(158, 16, str);
			//�����
			x1 = 205;
			x2 = 215;
			x = (x1 + x2) / 2;
			if (MA10[i + shift + 1] - MA10[i + shift] < 0)
			{
				pDC->SelectObject(&Rpen);
				pDC->SelectObject(&Rbrush);
				pDC->MoveTo(x1, y2);
				pDC->LineTo(x2, y2);
				pDC->LineTo(x, y1);
				pDC->LineTo(x1, y2);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
			}
			else
			{
				pDC->SelectObject(&Gpen);
				pDC->SelectObject(&Gbrush);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y1);
				pDC->LineTo(x, y2);
				pDC->LineTo(x1, y1);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
			}
		}
		else
		{
			str.Format(_T(" --"));
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(158, 16, str);
		}
		
		if (numDWM - i - shift > 20)
		{
			str.Format(_T(" %.1f"), cMA20);
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(278, 16, str);
			//�����
			x1 = 325;
			x2 = 335;
			x = (x1 + x2) / 2;
			if (MA20[i + shift + 1] - MA20[i + shift] < 0)
			{
				pDC->SelectObject(&Rpen);
				pDC->SelectObject(&Rbrush);
				pDC->MoveTo(x1, y2);
				pDC->LineTo(x2, y2);
				pDC->LineTo(x, y1);
				pDC->LineTo(x1, y2);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
			}
			else
			{
				pDC->SelectObject(&Gpen);
				pDC->SelectObject(&Gbrush);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y1);
				pDC->LineTo(x, y2);
				pDC->LineTo(x1, y1);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
			}
		}
		else
		{
			str.Format(_T(" --"));
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(278, 16, str);
		}
	}
	// ��MV5
	k = 5;
	for (int i = 0; i < numDWM - k; i++)
	{
		sum = 0;
		for (int j = 0; j < k; j++)
		{
			sum = sum + volDWM[i + j];
		}
		MV5[i] = sum / k;
	}
	// �eMV5
	pDC->SelectObject(&MA5pen);
	for (int i = 0; i < (W - 45) / 10; i++)
	{
		if (i + shift < numDWM - 4)
		{
			x = W - 45 - 10 * i;
			//y_MV = miny2 - (miny2 - maxy2)*(MV5[i + shift] - 0) / (maxvol - 0);
			y_MV = (MV5[i + shift] - 0) / (maxvol - 0)*(maxy2 - miny2) + miny2;
			if (i == 0)
			{
				pDC->MoveTo(x, y_MV);
			}
			else
			{
				if (y_MV < maxy2)
					pDC->LineTo(x, maxy2);
				else if (y_MV > miny2)
					pDC->LineTo(x, miny2);
				else
					pDC->LineTo(x, y_MV);
			}
		}
	}
	// ��MV20
	k = 20;
	for (int i = 0; i < numDWM - k; i++)
	{
		sum = 0;
		for (int j = 0; j < k; j++)
		{
			sum = sum + volDWM[i + j];
		}
		MV20[i] = sum / k;
	}
	// �eMV20
	pDC->SelectObject(&MA20pen);
	for (int i = 0; i < (W - 45) / 10; i++)
	{
		if (i + shift < numDWM - 19)
		{
			x = W - 45 - 10 * i;
			//y_MV = miny2 - (miny2 - maxy2)*(MV20[i + shift] - 0) / (maxvol - 0);
			y_MV = (MV20[i + shift] - 0) / (maxvol - 0)*(maxy2 - miny2) + miny2;
			if (i == 0)
			{
				pDC->MoveTo(x, y_MV);
			}
			else
			{
				if (y_MV < maxy2)
					pDC->LineTo(x, maxy2);
				else if (y_MV > miny2)
					pDC->LineTo(x, miny2);
				else
					pDC->LineTo(x, y_MV);
			}
		}
	}
	// �g MV ���
	i = (W - 40 - pt2.x) / 10; //�P�_�ƹ��b���@�����
	if (pt2.x < W - 45 && pt2.x > 5 && pt2.y < miny && pt2.y > maxy)
	{
		if (i >= 0 && i <= (W - 45) / 10 && i + shift < numDWM)
		{
			cvol = volDWM[i + shift];
			cMV5 = MV5[i + shift];
			cMV20 = MV20[i + shift];
			y1 = maxy2 - 16;
			y2 = maxy2 - 6;
			str.Format(_T("�q %i"), cvol);
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(5, miny + 2, str); // ����q
			//�����
			x1 = 101;
			x2 = 111;
			x = (x1 + x2) / 2;
			if (volDWM[i + shift + 1] - volDWM[i + shift] < 0)
			{
				pDC->SelectObject(&Rpen);
				pDC->SelectObject(&Rbrush);
				pDC->MoveTo(x1, y2);
				pDC->LineTo(x2, y2);
				pDC->LineTo(x, y1);
				pDC->LineTo(x1, y2);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
			}
			else
			{
				pDC->SelectObject(&Gpen);
				pDC->SelectObject(&Gbrush);
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y1);
				pDC->LineTo(x, y2);
				pDC->LineTo(x1, y1);
				pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
			}
			str.Format(_T("MV5"));
			pDC->SetTextColor(RGB(0, 43, 255));
			pDC->TextOutW(125, miny + 2, str); // MV5
			if (numDWM - i - shift > 5)
			{
				str.Format(_T("%i"), cMV5);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(160, miny + 2, str);
				//�����
				x1 = 237;
				x2 = 247;
				x = (x1 + x2) / 2;
				if (MV5[i + shift + 1] - MV5[i + shift] < 0)
				{
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(160, miny + 2, str);
			}
			str.Format(_T("MV20"));
			pDC->SetTextColor(RGB(0, 178, 51));
			pDC->TextOutW(265, miny + 2, str); // MV20
			if (numDWM - i - shift > 20)
			{
				str.Format(_T(" %i"), cMV20);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(305, miny + 2, str);
				//�����
				x1 = 386;
				x2 = 396;
				x = (x1 + x2) / 2;
				if (MV5[i + shift + 1] - MV5[i + shift] < 0)
				{
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(305, miny + 2, str);
			}
		}
	}
	
	// �񥪤���-K9 D9 RSV���
	i = (W - 40 - pt2.x) / 10; //�P�_�ƹ��b���@�����
	if (pt2.x < W - 45 && pt2.x > 5 && pt2.y < miny && pt2.y > maxy && techindex==1)
	{
		if (i >= 0 && i <= (W - 45) / 10 && i + shift < numDWM)
		{
			cK9 = K9[i + shift];
			cD9 = D9[i + shift];
			cRSV = RSV[i + shift];
			y1 = maxy3 - 16;
			y2 = maxy3 - 6;
			str.Format(_T("K9"));
			pDC->SetTextColor(RGB(0, 43, 255));
			pDC->TextOutW(5, miny2 + 2 + 16, str); // K9
			str.Format(_T("D9"));
			pDC->SetTextColor(RGB(241, 168, 10));
			pDC->TextOutW(105, miny2 + 2 + 16, str); // D9
			str.Format(_T("RSV"));
			pDC->SetTextColor(RGB(0, 178, 51));
			pDC->TextOutW(205, miny2 + 2 + 16, str); // RSV
			if (numDWM - i - shift > 8)
			{	
				// K9
				x1 = 71; // �Ȧ�
				x2 = 81; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cK9);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(29, miny2 + 2 + 16, str);
				if (K9[i + shift] >= K9[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
				// D9
				x1 = 171; // �Ȧ�
				x2 = 181; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cD9);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(129, miny2 + 2 + 16, str);
				if (D9[i + shift] >= D9[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
				// RSV
				x1 = 281; // �Ȧ�
				x2 = 291; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cRSV);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(239, miny2 + 2 + 16, str);
				if (RSV[i + shift] >= RSV[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(29, miny2 + 2 + 16, str);
				pDC->TextOutW(129, miny2 + 2 + 16, str);
				pDC->TextOutW(239, miny2 + 2 + 16, str);
			}
		}
	}
	// �񥪤���-MACD DIF EMA12 EMA26���
	i = (W - 40 - pt2.x) / 10; //�P�_�ƹ��b���@�����
	if (pt2.x < W - 45 && pt2.x > 5 && pt2.y < miny && pt2.y > maxy && techindex == 2)
	{
		if (i >= 0 && i <= (W - 45) / 10 && i + shift < numDWM)
		{
			cMACD = MACD[i + shift];
			cDIF = DIF[i + shift];
			cEMA12 = EMA12[i + shift];
			cEMA26 = EMA26[i + shift];
			y1 = maxy3 - 16;
			y2 = maxy3 - 6;
			str.Format(_T("MACD"));
			pDC->SetTextColor(RGB(0, 43, 255));
			pDC->TextOutW(5, miny2 + 2 + 16, str); // MACD
			str.Format(_T("DIF"));
			pDC->SetTextColor(RGB(241, 168, 10));
			pDC->TextOutW(125, miny2 + 2 + 16, str); // DIF
			str.Format(_T("EMA12"));
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(225, miny2 + 2 + 16, str); // EMA12
			str.Format(_T("EMA26"));
			pDC->SetTextColor(RGB(53, 94, 174));
			pDC->TextOutW(371, miny2 + 2 + 16, str); // EMA26
			if (numDWM - i - shift > 33)
			{
				// MACD
				x1 = 91; // �Ȧ�
				x2 = 101; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cMACD);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(49, miny2 + 2 + 16, str);
				if (MACD[i + shift] >=MACD[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(49, miny2 + 2 + 16, str);
			}
			if (numDWM - i - shift > 25)
			{
				// DIF
				x1 = 191; // �Ȧ�
				x2 = 201; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cDIF);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(149, miny2 + 2 + 16, str);
				if (DIF[i + shift] >= DIF[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(149, miny2 + 2 + 16, str);
			}
			if (numDWM - i - shift > 11)
			{
				// EMA12
				x1 = 330; // �Ȧ�
				x2 = 340; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cEMA12);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(275, miny2 + 2 + 16, str);
				if (EMA12[i + shift] >= EMA12[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(275, miny2 + 2 + 16, str);
			}
			if (numDWM - i - shift > 25)
			{
				// EMA26
				x1 = 477; // �Ȧ�
				x2 = 487; // �Ȧ�
				x = (x1 + x2) / 2;
				str.Format(_T("%.2f"), cEMA26);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(421, miny2 + 2 + 16, str);
				if (EMA26[i + shift] >= EMA26[i + shift + 1])
				{	//�����
					pDC->SelectObject(&Rpen);
					pDC->SelectObject(&Rbrush);
					pDC->MoveTo(x1, y2);
					pDC->LineTo(x2, y2);
					pDC->LineTo(x, y1);
					pDC->LineTo(x1, y2);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(255, 0, 0)); // ����
				}
				else
				{
					pDC->SelectObject(&Gpen);
					pDC->SelectObject(&Gbrush);
					pDC->MoveTo(x1, y1);
					pDC->LineTo(x2, y1);
					pDC->LineTo(x, y2);
					pDC->LineTo(x1, y1);
					pDC->FloodFill(x, (y1 + y2) / 2, RGB(0, 128, 0)); // ���
				}
			}
			else
			{
				str.Format(_T(" --"));
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(421, miny2 + 2 + 16, str);
			}
		}
	}
	
	// �g���
	for (int i = 10; i < (W - 45) / 10; i = i + 10)
	{
		x = W - 10 * i - 45;
		cday = dateDWM[i + shift] % 100;
		cmonth = dateDWM[i + shift] % 10000 / 100;
		lmonth = dateDWM[i + shift + 10] % 10000 / 100;
		cyear = dateDWM[i + shift] / 10000;
		lyear = dateDWM[i + shift + 10] / 10000;
		if (period == 0)
		{
			if (cyear-lyear)
			{
				str.Format(_T("%d/%d/%d"), cyear, cmonth, cday);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(x - 30, miny2 + 2, str);
			}
			else
			{
			
					if (cmonth - lmonth == 1 || lmonth - cmonth == 11)
					{
						str.Format(_T("%d/%d"), cmonth, cday);
						pDC->SetTextColor(RGB(53, 94, 174));
						pDC->TextOutW(x - 12, miny2 + 2, str);
					}
					else
					{
						str.Format(_T("%d"), cday);
						pDC->SetTextColor(RGB(53, 94, 174));
						pDC->TextOutW(x - 8, miny2 + 2, str);
					}
			
			}
		}
		else
		{
			if (cyear - lyear == 1)
			{
				str.Format(_T("%d/%d"), cyear, cmonth);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(x - 20, miny2 + 2, str);
			}
			else
			{
				str.Format(_T("%d"), cmonth);
				pDC->SetTextColor(RGB(53, 94, 174));
				pDC->TextOutW(x - 4, miny2 + 2, str);
			}
		}
	}
	/* 
	�g���(�Ѯv����)
	int date1;
	for (int i = 10; i < (W - 45) / 10; i = i + 10)
	{
		x = W - 10 * i - 45 - 30;
		date1 = date[i + shift];
		str.Format(_T("%d/%d/%d"), date1 / 10000, date1 % 10000 / 100, date1 % 100);
		pDC->SetTextColor(RGB(53, 94, 174));
		pDC->TextOutW(x, miny2 + 2, str);
	}*/
	// �ƹ����ʵ�u
	pDC->SelectObject(&Mousepen);
	if (pt2.x < W - 45 && pt2.x > 5 && pt2.y < miny && pt2.y > maxy)
	{
		i = (W - 40 - pt2.x) / 10; //�P�_�ƹ��b���@�����
		if (i >= 0 && i <= (W - 45) / 10 && i + shift < numDWM)
		{	// �D����	
			x = W - 10 * i - 45;
			y1 = (closeDWM[i + shift] - minprice) / (maxprice - minprice)*(maxy - miny) + miny;
			pDC->MoveTo(5, y1);
			pDC->LineTo(W - 40, y1);
			pDC->MoveTo(x, miny);
			pDC->LineTo(x, maxy);
			cclose = closeDWM[i + shift];
			str.Format(_T("%.1f"), cclose);
			pDC->SetBkColor(RGB(0, 85, 255)); // �]�w�r��I���C��
			pDC->SetTextColor(RGB(255, 255, 255));
			if (pt2.x < W - 75)
			{
				pDC->TextOutW(W - 75, y1, str);
			}
			else
			{
				pDC->TextOutW(5, y1, str);
			}
			// ����q
			//y_MV = miny2 - (miny2 - maxy2)*(vol[i + shift] - 0) / (maxvol - 0);
			y_MV = (volDWM[i + shift] - 0) / (maxvol - 0)*(maxy2 - miny2) + miny2;
			pDC->MoveTo(5, y_MV);
			pDC->LineTo(W - 40, y_MV);
			pDC->MoveTo(x, miny2);
			pDC->LineTo(x, maxy2);
			cvol = volDWM[i + shift];
			str.Format(_T("%i"), cvol);
			pDC->SetBkColor(RGB(0, 85, 255));
			pDC->SetTextColor(RGB(255, 255, 255));
			if (pt2.x < W - 110)
			{
				pDC->TextOutW(W - 110, y_MV, str);
			}
			else
			{
				pDC->TextOutW(5, y_MV, str);
			}
			if (techindex == 1)
			{	// K9
				y2 = (K9[i + shift] - 0) / (100 - 0)*(maxy3 - miny3) + miny3;
				pDC->MoveTo(5, y2);
				pDC->LineTo(W - 40, y2);
				pDC->MoveTo(x, miny3);
				pDC->LineTo(x, maxy3);
				cK9 = K9[i + shift];
				str.Format(_T("%.2f"), cK9);
				pDC->SetBkColor(RGB(0, 85, 255));
				pDC->SetTextColor(RGB(255, 255, 255));
				if (pt2.x < W - 75)
				{
					pDC->TextOutW(W - 75, y2, str);
				}
				else
				{
					pDC->TextOutW(5, y2, str);
				}
			}
			if (techindex == 2)
			{	// MACD
				if (MACD[i + shift] >= 0)
				{
					y2 = (MACD[i + shift] - 0) / (maxTECH2 - 0)*(maxy3 - miny3) / 2 + (miny3 + maxy3) / 2; // y2 = (MACD[i + shift] - 0) / (maxMACD - 0)*(maxy4 - miny4) / 2 + miny4 - 50;
				}
				else
				{
					y2 = (0 - MACD[i + shift]) / (0 - minTECH2)*(miny3 - maxy3) / 2 + (miny3 + maxy3) / 2; // y2 = (0 - MACD[i + shift]) / (0 - minMACD)*(miny4 - maxy4) / 2 + miny4 - 50;
				}
				pDC->MoveTo(5, y2);
				pDC->LineTo(W - 40, y2);
				pDC->MoveTo(x, miny3);
				pDC->LineTo(x, maxy3);
				cMACD = MACD[i + shift];
				str.Format(_T("%.2f"), cMACD);
				pDC->SetBkColor(RGB(0, 85, 255));
				pDC->SetTextColor(RGB(255, 255, 255));
				if (pt2.x < W - 75)
				{
					pDC->TextOutW(W - 75, y2, str);
				}
				else
				{
					pDC->TextOutW(5, y2, str);
				}
			}
			// ���
			cdate = dateDWM[i + shift];
			str.Format(_T("%d/%d/%d"), cdate / 10000, cdate % 10000 / 100, cdate % 100);
			pDC->SetBkColor(RGB(0, 85, 255));
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->TextOutW(x-32, miny2, str);
		}
	}

	// �µe��
	pDC2->BitBlt(0, 0, W, H, pDC, 0, 0, SRCCOPY);
	delete m_pMemDC;
	delete m_pBitmap;
}

BEGIN_MESSAGE_MAP(CStock, CWnd)
END_MESSAGE_MAP()



// CStock �T���B�z�`��



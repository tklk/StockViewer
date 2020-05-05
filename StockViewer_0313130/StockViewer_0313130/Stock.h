#pragma once


// CStock

class CStock : public CWnd
{
	DECLARE_DYNAMIC(CStock)

public:
	CStock();
	virtual ~CStock();
	void Read(char*);
	double QueryAdjust(int);
	void Draw(CDC*, int, int, int, CPoint, int, int, int); // H, W, shift, CPoint2(·Æ¹«¦ì¸m), techindex, period
	int num;
	double *MA5, *MA10, *MA20;
	double *MV5, *MV20;
	
	double *RSV, *rsvMAX, *rsvMIN;
	double *K9, *D9;
	double *DI, *EMA12, *EMA26, *DIF, *MACD, *OSC;
	
	double *openDWM, *highDWM, *lowDWM, *closeDWM, *volDWM;
	int *dateDWM;

private:

	int *date;
	double *open;
	double *high;
	double *low;
	double *close;
	int *vol;
	double *adjust;

protected:
	DECLARE_MESSAGE_MAP()
};



// 五子棋View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__53DFAE7C_E197_49AE_980F_5C6DF5F9E8A5__INCLUDED_)
#define AFX_VIEW_H__53DFAE7C_E197_49AE_980F_5C6DF5F9E8A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"MainFrm.h"
class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnStart();
	void Regret ();
	CDC BEGIN;
	CBitmap bitmap;
	//两个鼠标
	HCURSOR hcursorwhite;
	HCURSOR hcursorblack;
	int wzq[19][19];

	// colorwhite TRUE 时白棋下，否则黑棋下
	bool colorwhite;
	//棋子位图
	CBitmap m_bmblack;
	CBitmap m_bmwhite;
	//保存文件	
	//检查是否结束
	void over(CPoint point);

	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	//鼠标图形变换
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//鼠标操作
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickButton1();
	afx_msg void OnClickButton2();
	afx_msg void OnClickButton3();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CButton m_button3;
	CButton m_button1;
	CButton m_button2;
	CPoint vspoint;
	bool vscomputer;//ture时代表人机对战
	CPoint bpointcan4;//这个位置空，它旁边有四个黑棋
	CPoint wpointcan4;//这个位置空，它旁边有四个白棋
	CPoint bpointcan3;//这个位置空，它的旁边有三个黑棋
	CPoint wpointcan3;//这个位置空，它的旁边有三个白棋
	CPoint bpointcan2;//这个位置空，它的旁边有两个黑棋
	CPoint wpointcan2;//这个位置空，它的旁边有两个白棋
	CPoint bpointcan1;//不是以上情况，这个位置空
	//在搜索前都赋值为(-1,-1)
	//在得到最大值和方向上寻找落棋点
	//其中i,j表示搜索起点，n表示方向
public:
void searchcandown1(int i,int j,int n);
void searchcandown2(int i,int j,int n);
void searchcandown3(int i,int j,int n);
void searchcandown4(int i,int j,int n);
//计算最大值及方向 
CPoint maxnum(int a,int b,int c,int d);
//最好落棋点 
void bestputdown(int i,int j);
//计算机下棋 
int LastPoint[1][1];
int computer[1][1];
int vsLastPoint[3];
void computerdown();

//在位置point放下棋子

void putdown(CPoint point);




};

#ifndef _DEBUG  // debug version in 五子棋View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__53DFAE7C_E197_49AE_980F_5C6DF5F9E8A5__INCLUDED_)

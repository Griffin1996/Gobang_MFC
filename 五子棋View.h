// ������View.h : interface of the CMyView class
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
	//�������
	HCURSOR hcursorwhite;
	HCURSOR hcursorblack;
	int wzq[19][19];

	// colorwhite TRUE ʱ�����£����������
	bool colorwhite;
	//����λͼ
	CBitmap m_bmblack;
	CBitmap m_bmwhite;
	//�����ļ�	
	//����Ƿ����
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
	//���ͼ�α任
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//������
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
	bool vscomputer;//tureʱ�����˻���ս
	CPoint bpointcan4;//���λ�ÿգ����Ա����ĸ�����
	CPoint wpointcan4;//���λ�ÿգ����Ա����ĸ�����
	CPoint bpointcan3;//���λ�ÿգ������Ա�����������
	CPoint wpointcan3;//���λ�ÿգ������Ա�����������
	CPoint bpointcan2;//���λ�ÿգ������Ա�����������
	CPoint wpointcan2;//���λ�ÿգ������Ա�����������
	CPoint bpointcan1;//����������������λ�ÿ�
	//������ǰ����ֵΪ(-1,-1)
	//�ڵõ����ֵ�ͷ�����Ѱ�������
	//����i,j��ʾ������㣬n��ʾ����
public:
void searchcandown1(int i,int j,int n);
void searchcandown2(int i,int j,int n);
void searchcandown3(int i,int j,int n);
void searchcandown4(int i,int j,int n);
//�������ֵ������ 
CPoint maxnum(int a,int b,int c,int d);
//�������� 
void bestputdown(int i,int j);
//��������� 
int LastPoint[1][1];
int computer[1][1];
int vsLastPoint[3];
void computerdown();

//��λ��point��������

void putdown(CPoint point);




};

#ifndef _DEBUG  // debug version in ������View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__53DFAE7C_E197_49AE_980F_5C6DF5F9E8A5__INCLUDED_)

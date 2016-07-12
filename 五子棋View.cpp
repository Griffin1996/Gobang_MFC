// ������View.cpp : implementation of the CMyView class
//
#include "stdafx.h"
#include "������.h"
#include "������Doc.h"
#include "������View.h"
#include<math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDB_BTN1 ,OnClickButton1) //��ťON_BN_CLICKED��Ϣ�Ĵ�����OnClickButton1
	ON_BN_CLICKED(IDB_BTN2 ,OnClickButton2) //��ťON_BN_CLICKED��Ϣ�Ĵ�����OnClickButton2
	ON_BN_CLICKED(IDB_BTN3 ,OnClickButton3) //��ťON_BN_CLICKED��Ϣ�Ĵ�����OnClickButton3
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction
/*

*/
CMyView::CMyView()
{
	// TODO: add construction code here
	//Load���ͼ��
	hcursorblack=AfxGetApp()->LoadCursor(IDC_CURSOR1);//���ù����״	
	hcursorwhite=AfxGetApp()->LoadCursor(IDC_CURSOR2);
	m_bmwhite.LoadBitmap(IDB_WHITE);
	m_bmblack.LoadBitmap(IDB_BLACK);
	//��������
	//����ֵΪ0 ��ʾû������
	for(int i=0;i<19;i++)
	for(int j=0;j<19;j++)
	wzq[i][j]=0;
	//��������
	colorwhite=true;
}


CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

/**********************************************************
��������OnDraw
���ã�����Ļ�д�ӡ����
������CDC *pDC   ��ǰ������DC
***********************************************************/
void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//������
	CBrush mybrush1;
	mybrush1.CreateSolidBrush(RGB(192,192,192));//���ñ�����ɫ
	CRect myrect1(0,0,1200,800);
	pDC->FillRect(myrect1,&mybrush1);
	//�����̿���
	for(int	i=0;i<19;i++)
	{
		pDC->MoveTo(40,40+i*20);
		pDC->LineTo(400,40+i*20);
		pDC->MoveTo(40+i*20,40);
		pDC->LineTo(40+i*20,400);
	}
 
	//�ػ�ʱ��ʾ���ڵ�����
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
	{
	AfxMessageBox("Can't create DC");
	DeleteDC(Dc);
	}
	for(int n=0;n<19;n++)
	for(int m=0;m<19;m++)
	if(wzq[n][m]==1)
	{
		//��ʾ����
		Dc.SelectObject(m_bmwhite);
		pDC->BitBlt(n*20+32,m*20+32,160,160,&Dc,0,0,SRCCOPY);
	}
	else if(wzq[n][m]==-1)
	{ //��ʾ����
		Dc.SelectObject(m_bmblack);
		pDC->BitBlt(n*20+32,m*20+32,160,160,&Dc,0,0,SRCCOPY);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

BOOL CMyView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest==HTCLIENT)
	{
		//�����£���ʾ�������
		if(colorwhite)
		{
		//��������������״̬��
			CMainFrame *pFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;
			CStatusBar *pStatus=&pFrm->m_wndStatusBar;
			if(pStatus)
			{
				pStatus->GetStatusBarCtrl().SetIcon(0,AfxGetApp()->LoadIcon(IDI_WHITE));
				pStatus->SetPaneText(0,"��������");
		
			}
			SetCursor(hcursorwhite);
		}
		else
		{
			SetCursor(hcursorblack);
			CMainFrame*pFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;
			CStatusBar*pStatus=&pFrm->m_wndStatusBar;
			if(pStatus)
			{
				//��ʾͼ��
				pStatus->GetStatusBarCtrl().SetIcon(0,AfxGetApp()->LoadIcon(IDI_BLACK));
				//��ʾ����
				pStatus->SetPaneText(0,"��������");
			}
		}
		return 1;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CMyView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC=GetDC();
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
	{
	AfxMessageBox("Can't create DC");
	DeleteDC(Dc);
	}	

//�˻���ս
	if(vscomputer==true)

{ 

	if(point.x>30&&point.x<410&&point.y>30&&point.y<410)

{ 

	int px=(point.x-30)/20;
	int py=(point.y-30)/20; 

if(colorwhite&&wzq[px][py]==0)

{ 

	Dc.SelectObject(m_bmwhite); 
	pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
	wzq[px][py]=1;
	vsLastPoint[1]=px;
	vsLastPoint[2]=py;
	//������һ�����λ��
	over(point); 
	colorwhite=false;
	//�������λ��
	vspoint=point;
	//���������
	computerdown();
	}
	}
} 
	if(vscomputer==false)
	{

	//�Ƿ���������
	if(point.x>30&&point.x<410&&point.y>30&&point.y<410)
	{
		int px=(point.x-30)/20;
		int py=(point.y-30)/20;
		//���ڳ�������������� ���Կ��Ա�֤����������ȷ��λ��
		//�Ƿ��Ѿ�������
		if(colorwhite&&wzq[px][py]==0)
		{
			Dc.SelectObject(m_bmwhite);
			pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
			//��ʾ���ڰ���
			wzq[px][py]=1;
			//����Ƿ����
			over(point);
			//��������
			colorwhite=false;
			LastPoint[0][0]=px;
			LastPoint[0][1]=py;//������һ�����λ��
		}
		else if(wzq[px][py]==0)
		{
			Dc.SelectObject(m_bmblack);
			pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
			wzq[px][py]=-1;
			over(point);
			colorwhite=true;
			LastPoint[0][0]=px;
			LastPoint[0][1]=py;
		}
	}
	}
	CView::OnLButtonUp(nFlags, point);
}

/**********************************************************
��������over
���ã��ж�ʤ��
������ CPoint point  ��ǰ��������
***********************************************************/
void CMyView::over(CPoint point) //�ж�ʤ������
{

//int winerValue=0;
	int i,j,k;
	for(i = 0; i<19;i++) 
	{ 
		bool win = false;    //һ��ʤ�������� 
		for ( j = 0; j < 19;j++) 

        { 
			if (wzq[i][j] == 0)  //�ո���Ҫ�ж� 
			continue; 
//ˮƽ�����������Ӹ������ 
		int cnt = 1; 
			//��� 
		for (k = j-1; k >= 0;k--) 
			{ 
				if (wzq[i][k] != wzq[i][j])    //����ͬ����ʱֹͣ��� 
				{ break; } 
				else 
					cnt++; 
		} 
			 //�Ҳ� 
			for ( k = j + 1; k < 19; k++) 
			{ 
				 if (wzq[i][k] != wzq[i][j])    //����ͬ����ʱֹͣ��� 
				{ break; } 
				else 
				cnt++; 
				} 

            //ʤ�� 
			 if (cnt >= 5) 
		{ 
				win = true; 
				if(wzq[i][j]==-1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
                break; 

            } 

  //��ֱ������ 

            cnt = 1; 

            //�Ϸ� 
			 for (k = i - 1; k >= 0; k--) 
		{ 

                if (wzq[k][j] != wzq[i][j])    //����ͬ����ʱֹͣ��� 

                { break;  } 
				 else 
				  cnt++; 

            } 

            //�·� 
			for (k = i + 1; k < 19; k++) 

            { 

                if (wzq[k][j] != wzq[i][j])    //����ͬ����ʱֹͣ��� 

                { break; } 

                else	 cnt++; 

            } 

            //ʤ�� 
		if (cnt >= 5) 

            {  win = true; 

              
				if(wzq[i][j]==-1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
                break; 

            } 
//�����µ����ϼ�� 

            cnt = 1; 
			//���� 
			int m = i + 1; 
			for (k = j - 1; k >= 0; k--) 
		{ 

                if (m>=19)    //���·����� 
				{  break; } 

                if (wzq[m][k] != wzq[i][j])    //����ͬ����ʱֹͣ��� 

                {  break;  } 

                else 

				cnt++; 

              m++; 

            } 

            //���� 

            m = i - 1; 

            for ( k = i + 1; k < 19; k++) 

            { 

                if (m < 0)    //���Ϸ����� 

                { break;  } 

                if (wzq[m][k] != wzq[i][j])    //����ͬ����ʱֹͣ��� 

                { break; } 

                else 

                    cnt++; 

                m--; 

            } 

            //ʤ�� 

            if (cnt >= 5) 

            { 

                win = true; 

				if(wzq[i][j]==-1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}

                break; 

            } 
 //�����ϵ����¼�� 

            cnt = 1; 

            //���� 
			m = i - 1; 
			for ( k = j - 1; k >= 0; k--) 
		 { 

                if (m < 0)    //���Ϸ����� 

                {  break;  } 

                if (wzq[m][k] != wzq[i][j])    //����ͬ����ʱֹͣ��� 

                {  break;  } 

                else 

                    cnt++; 

                m--; 

            } 

            //���� 

            m = i + 1; 

            for ( k = i + 1; k < 19; k++) 

            { 

                if (m >= 19)    //���·����� 

                {  break;  } 

                if (wzq[m][k] != wzq[i][j])    //����ͬ����ʱֹͣ��� 

                {  break; } 

                else 

                    cnt++; 

                m++; 

            } 

            //ʤ�� 

            if (cnt >= 5) 

            { 

                win = true; 

              
					if(wzq[i][j]==-1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("����ʤ!");
						OnStart();
			}
                break; 

            } 
		} 

        if (win) 

        {  break;  } 

    }
}
/**********************************************************
��������OnStart
���ã���ʼ������
��������
***********************************************************/
void CMyView::OnStart()
{
	for(int i=0;i<19;i++)
	for(int j=0;j<19;j++)
	wzq[i][j]=0;
	//��������
	colorwhite=true;
	InvalidateRect(NULL);
}


int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	   CRect rect_button1(0,0,64,20);   //���ư�ť��С��λ��
       m_button1.Create("˫�˶�ս",WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_BTN1);
       m_button1.ShowWindow(SW_SHOWNORMAL);
	   CRect rect_button2(0,21,40,41);   //���ư�ť��С��λ��
       m_button2.Create("����",WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_BTN2);
	   CRect rect_button3(65,0,130,20);   //���ư�ť��С��λ��
	   m_button3.Create("�˻���ս",WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_BTN3);
       m_button3.ShowWindow(SW_SHOWNORMAL);


	return 0;
}
/**********************************************************
��������Regret
���ã�����
��������
***********************************************************/
void CMyView::Regret()
{	
	if(vscomputer==true)

	{	wzq[computer[0][0]][computer[0][1]]=0;
		wzq[vsLastPoint[1]][vsLastPoint[2]]=0;
	
		InvalidateRect(NULL);//�������»��Ƶ���OnDraw����
	}
	if(vscomputer==false)  
	{
	wzq[LastPoint[0][0]][LastPoint[0][1]]=0;
	colorwhite=!colorwhite;
	InvalidateRect(NULL);//�������»��Ƶ���OnDraw����
	}
}
void CMyView::OnClickButton1()
{	vscomputer=false;
	OnStart();
	MessageBox("��ʼ��Ϸ!","��ʼ",MB_OK);
	
}

void CMyView::OnClickButton2()
{
	Regret();
	MessageBox("����ɹ�!","����",MB_OK);

}

void CMyView::OnClickButton3()
{	vscomputer=true;
	OnStart();
	MessageBox("�˻���ս��Ϸ��ʼ!","��ʼ",MB_OK);
	
}
/**********************************************************
��������computerdown
���ã����������
��������
***********************************************************/
void CMyView::computerdown()
{//�Ѹ������θ�ֵΪ����
	bpointcan4=(-1,-1);
	wpointcan4=(-1,-1); 
	bpointcan3=(-1,-1);
	wpointcan3=(-1,-1);
	bpointcan2=(-1,-1);
	wpointcan2=(-1,-1);
	bpointcan1=(-1,-1); 
//������õ������
	for(int i=0;i<19;i++) 
	for(int j=0;j<19;j++) 
	bestputdown(i,j); 
//�жϷ�������
//����λ������
//�ڰ�һ����ʱ���� 
//����-1�ͱ�ʾ�Ѿ�����ֵ
	if(bpointcan4.x!=-1)
	{ 
	putdown(bpointcan4);
	return;
	} 
	else  if(wpointcan4.x!=-1)
	{ 
	putdown(wpointcan4);
	return;	
	} 

	else if(bpointcan3.x!=-1)
	{ 
	putdown(bpointcan3);
	return;
	} 

	else if(wpointcan3.x!=-1)
	{	
	putdown(wpointcan3);
	return;
	}
	
	else if(bpointcan2.x!=-1)
	{putdown(bpointcan2);
	return;}
	
	else if(wpointcan2.x!=-1)
	{	putdown(wpointcan2);
	return;
	}

	else
	{	putdown(bpointcan1);	
		return;
	} 

} 



void CMyView::putdown(CPoint point)
{

	CDC *pDC=GetDC();
	CDC Dc; 
	if(Dc.CreateCompatibleDC(pDC)==FALSE) 
{
	AfxMessageBox("Can't create DC");
	DeleteDC(Dc);
}

	Dc.SelectObject(m_bmblack); 
	pDC->BitBlt(point.x*20+32,point.y*20+32,160,160,&Dc,0,0,SRCCOPY);
	wzq[point.x][point.y]=-1; 
	computer[0][0]=point.x;
	computer[0][1]=point.y;
//����ԭ�����Ǽ���Ƿ����ʱ�õ��������µ����꣬������
//putdown(CPointpoint)�����õ����������̵����꣬���Ա���ת��
	CPoint overpoint; 
	overpoint.x=point.x*20+30;
	overpoint.y=point.y*20+30;
	over(overpoint);
	colorwhite=true;
}

void CMyView::bestputdown(int i,int j)
{
	int num[4];//�ĸ������ֵ
	int a,k;
	a=0;
	if(i<15) 
		for(k=0;k<5;k++) 
		a=a+wzq[i+k][j]; //��¼�Ϸ���ֵ
	num[0]=abs(a); //ȡ����ֵ	
	a=0;
	if(j<15) 
		for(k=0;k<5;k++) 
	    a=a+wzq[i][j+k];//��¼�ҷ���ֵ	
	num[1]=abs(a);//ȡ����ֵ
	a=0; 
	if(i<15&&j<15) 
		for(k=0;k<5;k++) 
		a=a+wzq[i+k][j+k];//��¼���·���ֵ 
	num[2]=abs(a); //ȡ����ֵ
	a=0; 
	if((i>4)&&(j<15)) 
		for(k=0;k<5;k++) 
		a=a+wzq[i-k][j+k]; //��¼���Ϸ���ֵ
	num[3]=abs(a); //ȡ����ֵ
//�Ƚ��ĸ�����ͬɫ����� 
	CPoint numbig; 
//numbig.x��ʾ����
//numbig.y��ʾ���ֵ 
//���ĸ������ϱȽ����ֵȷ������
numbig=maxnum(num[0],num[1],num[2],num[3]);
//�ڵõ����ֵ�ͷ�����Ѱ�������
switch(numbig.y)
{	case 4: searchcandown4(i,j,numbig.x);break;
	case 3: searchcandown3(i,j,numbig.x);break;
	case 2: searchcandown2(i,j,numbig.x);break;
	default: searchcandown1(i,j,numbig.x);
}
}
CPoint CMyView::maxnum(int a,int b,int c,int d)
{
//point.xΪ����ֵ
//point.yΪ���ֵ
	CPoint point ;
	if(a>=b)
	{	point.x=0;
		point.y=a;
	}
	else
	{	
	point.x=1;	
	point.y=b;
	} 
	if(c>point.y)
	{	
	point.x=2;	
	point.y=c;
	} 
	if(d>point.y)
	{	
	point.x=3;
	point.y=d;
	} 
	return point;
 }
/**********************************************************
��������searchcandown4
���ã����ĸ�ͬɫ��ʱѰ�Ҹ����������������
��������������i,j,��������n
***********************************************************/
void CMyView::searchcandown4(int i,int j,int n)
{	int k;
	if(n==0) //��ˮƽ����Ѱ�����ӵ�
	for(k=0;k<5;k++) 
	//�����һ���ǿ�
	if(wzq[i][j]==0)
	{ //��������а���
	if(wzq[i+1][j]==1)
		{ //����λ�ÿ������壬�Ѿ����ĸ�����
			wpointcan4.x=i;
			wpointcan4.y=j;
			break;
		}
	else
		{ //����λ�ÿ������壬�Ѿ����ĸ�����
			bpointcan4.x=i;
			bpointcan4.y=j;
			break;
		} 
	}
	else  if(wzq[i+k][j]==0)
	{ //�����һ���ǰ���
	if(wzq[i][j]==1)
		{	wpointcan4.x=i+k;
			wpointcan4.y=j;
			break;
		} //�����һ���Ǻ���
	else	
		{	bpointcan4.x=i+k;
			bpointcan4.y=j;
			break;
		}

	} 

	if(n==1) 	//����ֱ����Ѱ�������
	for(k=0;k<5;k++)
	{ if(wzq[i][j]==0) //�����һ���ǿ�
	  if(wzq[i][j+1]==1)//�����һ���ǰ���
		{	wpointcan4.x=i;
			wpointcan4.y=j;
			break;
		}
	  else
		{	bpointcan4.x=i;
			bpointcan4.y=j;
			break;
		} 
	else if(wzq[i][j+k]==0)
	{ if(wzq[i][j]==1)
		{wpointcan4.x=i;
		wpointcan4.y=j+k;
		break;
		}
	  else
		{	bpointcan4.x=i;
			bpointcan4.y=j+k;
			break;
		}
	} 
	} 
//�����·�Ѱ�������
		if(n==2) 
		for(k=0;k<5;k++)
	{ 
			if(wzq[i][j]==0) 
			if(wzq[i+1][j+1]==1)
		{wpointcan4.x=i;
		wpointcan4.y=j;
		break;
		}
		else	
		{	bpointcan4.x=i;
			bpointcan4.y=j;
			break;
		} 
	else if(wzq[i+k][j+k]==0)
	{ if(wzq[i][j]==1)
		{	wpointcan4.x=i+k;
			wpointcan4.y=j+k;
			break;
		}
		else
		{	bpointcan4.x=i+k;
			bpointcan4.y=j+k;
			break;
		}
	}	 

	} 
//�����·�Ѱ����������
		if(n==3) 
		for(k=0;k<5;k++)
	{ if(wzq[i][j]==0) 
	  if(wzq[i-1][j+1]==1)
		{	wpointcan4.x=i;
			wpointcan4.y=j;
			break;
		}
	  else
		{	bpointcan4.x=i;	
			bpointcan4.y=j;
			break;
		} 
	  else if(wzq[i-k][j+k]==0)
		{ if(wzq[i][j]==1)
			{	wpointcan4.x=i-k;
				wpointcan4.y=j+k;
				break; 
			}
		  else
			{	bpointcan4.x=i-k;
				bpointcan4.y=j+k;
				break;
			}

		}

	}

}
/**********************************************************
��������searchcandown3
���ã����ĸ�ͬɫ��ʱѰ�Ҹ����������������
��������������i,j,��������n
***********************************************************/
void CMyView::searchcandown3(int i,int j,int n)
{	int k=0; 
	//��ˮƽ����Ѱ����������
	if(n==0) 
	for(k=0;k<5;k++) 
	//�ҵ�λ�� 
	if(wzq[i+k][j]==0)
	{ //��һ���ǰ��� 
	if(wzq[i+k+1][j]==1)
		{ //����λ�ÿ������壬�Ѿ�����������
		wpointcan3.x=i+k;
		wpointcan3.y=j;
		} //��һ���Ǻ��� 
	else if(wzq[i+k+1][j]==-1) 
		{		bpointcan3.x=i+k;
				bpointcan3.y=j;
		} //����ֱ����Ѱ����������
	}//
	if(n==1) 
	for(k=0;k<5;k++) 
	if(wzq[i][j+k]==0)
	{	if(wzq[i][j+k-1]==1)
		{	wpointcan3.x=i;
			wpointcan3.y=j+k;
		} 
	else if(wzq[i][j+k+1]==-1) 
		{	bpointcan3.x=i;
			bpointcan3.y=j+k;
		} 

	} 

//�����·�Ѱ����������
	if(n==2) 
	for(k=0;k<5;k++) 
	if(wzq[i+k][j+k]==0)
	{ if(wzq[i+k+1][j+k+1]==1)
		{ wpointcan3.x=i+k;
			wpointcan3.y=j+k;
		} 
	  else if(wzq[i+k+1][j+k+1]==-1) 
		{ bpointcan3.x=i+k;
		  bpointcan3.y=j+k;
		} 
	} 
//�����·�Ѱ����������
	if(n==3) 
	for(k=0;k<5;k++) 
	if(wzq[i-k][j+k]==0)
	{ if(wzq[i-k-1][j+k+1]==1)
		{ wpointcan3.x=i-k;
		  wpointcan3.y=j+k;
		} 
	else if(wzq[i-k-1][j+k+1]==-1) 

		{	bpointcan3.x=i-k;
			bpointcan3.y=j+k;
		} 

	}

}

/**********************************************************
��������searchcandown2
���ã����ĸ�ͬɫ��ʱѰ�Ҹ����������������
��������������i,j,��������n
***********************************************************/
void CMyView::searchcandown2(int i,int j,int n)
{	int k=0,m=0,a=0,b=0;
//��ˮƽ����Ѱ����������
	if(n==0)
	{	  for(k=0;k<5;k++)
		if(wzq[i+k][j]==0)
		m+=1;//��¼ˮƽ����Ŀ�λ��
		if(m==1)
		for(a=0;a<5;a++)
		if(wzq[i+a][j]==0)
		{
		b=wzq[i+a+1][j]+wzq[i+a+2][j];
		if(b==-2)
			{	bpointcan2.x=i+a;
				bpointcan2.y=j;
			}
		if(b==2)
			{	wpointcan2.x=i+a;
				wpointcan2.y=j;
			}
		}
	}
	if(m==3)
	{ for(a=0;a<5;a++)
		if(wzq[i+a][j]==-1)
		{
		for(b=0;b<5;b++)
		if(wzq[i+b][j]==0)
			{
				bpointcan2.x=i+b;
				bpointcan2.y=j;
				break;
			}
		}
		else  if(wzq[i+a][j]==1)
		{ for(b=0;b<5;b++) 
			 if(wzq[i+b][j]==0) 
			{	
				 wpointcan2.x=i+b; 
				 wpointcan2.y=j;
				 break;
			} 

		} 
	

	//����ֱ������Ѱ����������
m=0;

	if(n==1) 
	{ 	for(k=0;k<5;k++) 
		if(wzq[i][j+k]==0) 
		m++; 
		if(m==1) 
		for(a=0;a<5;a++) 
		if(wzq[i][j+a]==0)
			{ 
			b=wzq[i][j+a+1]+wzq[i][j+a+2];
				if(b==-2)

				{	bpointcan2.x=i;
					bpointcan2.y=j+a;
				} 

				if(b==2) 
				{	wpointcan2.x=i;
					wpointcan2.y=j+a;
				} 

			} 

	if(m==3)

{ 

for(a=0;a<5;a++) 

if(wzq[i][j+a]==-1)

{ 
	
for(b=0;b<5;b++) 

if(wzq[i][j+b]==0)
{	bpointcan2.x=i; 
	bpointcan2.y=j+b;
	break;
} 

}

else 

if(wzq[i][j+a]==1)

{ 

for(b=0;b<5;b++) 

if(wzq[i][j+b]==0)
{	wpointcan2.x=i; 
	wpointcan2.y=j+b;
	break;
} 

} 

} 

}
m=0;
if(n==2)
{
	for(k=0;k<5;k++)
		if(wzq[i+k][j+k]==0)
			m++;
		if(m==1)
			for(a=0;a<5;a++)
				if(wzq[i+a][j+a]==0)
				{
				b=wzq[i+a+1][j+a+1]+wzq[i+a+2][j+a+2];
				if(b==-2)
				{
				bpointcan2.x=i+a;
				bpointcan2.y=j+a;
				}
				if(b==2)
				{
				bpointcan2.x=i+a;
				bpointcan2.y=j+a;
				}
				}
		if(m==3)
	{ 

			for(a=0;a<5;a++) 
				if(wzq[i+a][j+a]==-1)
				{ 
			 for(b=0;b<5;b++) 
	if(wzq[i+b][j+b]==0)

{ 
	bpointcan2.x=i+b; 
	bpointcan2.y=j+b;
	break;
} 

}

else 

if(wzq[i+a][j+a]==1)

{ 

for(b=0;b<5;b++) 

if(wzq[i+b][j+b]==0) 

{ 
	wpointcan2.x=i+b; 
	wpointcan2.y=j+b;
	break;
} 

} 

} 

} 

m=0;

if(n==3)

{ 

for(k=0;k<5;k++) 

if(wzq[i-k][j+k]==0) 

m++; 

if(m==1) 

for(a=0;a<5;a++) 

if(wzq[i-a][j+a]==0)

{ 
	b=wzq[i-a-1][j+a+1]+wzq[i-a-2][j+a+2];

if(b==-2)
{	bpointcan2.x=i-a;	
	bpointcan2.y=j+a;
} 

if(b==2) 

{	wpointcan2.x=i-a;
	wpointcan2.y=j+a;
}
}

if(m==3)

{ 

for(a=0;a<5;a++) 

if(wzq[i-a][j+a]==-1)

{ 

for(b=0;b<5;b++) 

if(wzq[i-b][j+b]==0)

{	bpointcan2.x=i-b; 
	bpointcan2.y=j+b;
	break;

} 

}

else 

if(wzq[i-a][j+a]==1)

{ 

for(b=0;b<5;b++) 

if(wzq[i-b][j+b]==0)

{ 
	wpointcan2.x=i-b; 
	wpointcan2.y=j+b;
	break;

} 

} 

}

}

}
}


/**********************************************************
��������searchcandown1
���ã����ĸ�ͬɫ��ʱѰ�Ҹ����������������
��������������i,j,��������n
***********************************************************/
void CMyView::searchcandown1(int i,int j,int n)
{//����ղŰ��������
	int ii=(vspoint.x-30)/20;
	int jj=(vspoint.y-30)/20;	
	int a; 
	for(a=0;a<5;a++) 
		//��������߽�
	if(ii+a<19)
	{ //���ң�����п�λ��
	 if(wzq[ii+a][jj]==0)
		{	//�����λ���º���
			bpointcan1.x=ii+a;
			bpointcan1.y=jj;
			return;
		}
	} 
//���˱߽� 
	else if(wzq[ii+a][jj]==0) //��������п�λ��
	{	bpointcan1.x=ii-a;
		bpointcan1.y=jj;
		return;
	}
}



// 五子棋View.cpp : implementation of the CMyView class
//
#include "stdafx.h"
#include "五子棋.h"
#include "五子棋Doc.h"
#include "五子棋View.h"
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
	ON_BN_CLICKED(IDB_BTN1 ,OnClickButton1) //按钮ON_BN_CLICKED消息的处理函数OnClickButton1
	ON_BN_CLICKED(IDB_BTN2 ,OnClickButton2) //按钮ON_BN_CLICKED消息的处理函数OnClickButton2
	ON_BN_CLICKED(IDB_BTN3 ,OnClickButton3) //按钮ON_BN_CLICKED消息的处理函数OnClickButton3
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
	//Load鼠标图像
	hcursorblack=AfxGetApp()->LoadCursor(IDC_CURSOR1);//设置光标形状	
	hcursorwhite=AfxGetApp()->LoadCursor(IDC_CURSOR2);
	m_bmwhite.LoadBitmap(IDB_WHITE);
	m_bmblack.LoadBitmap(IDB_BLACK);
	//清理棋盘
	//数组值为0 表示没有棋子
	for(int i=0;i<19;i++)
	for(int j=0;j<19;j++)
	wzq[i][j]=0;
	//白棋先下
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
函数名：OnDraw
作用：在屏幕中打印棋子
参数：CDC *pDC   当前主窗口DC
***********************************************************/
void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//画背景
	CBrush mybrush1;
	mybrush1.CreateSolidBrush(RGB(192,192,192));//设置背景颜色
	CRect myrect1(0,0,1200,800);
	pDC->FillRect(myrect1,&mybrush1);
	//画棋盘框线
	for(int	i=0;i<19;i++)
	{
		pDC->MoveTo(40,40+i*20);
		pDC->LineTo(400,40+i*20);
		pDC->MoveTo(40+i*20,40);
		pDC->LineTo(40+i*20,400);
	}
 
	//重画时显示存在的棋子
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
		//显示白棋
		Dc.SelectObject(m_bmwhite);
		pDC->BitBlt(n*20+32,m*20+32,160,160,&Dc,0,0,SRCCOPY);
	}
	else if(wzq[n][m]==-1)
	{ //显示黑棋
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
		//白棋下，显示白棋鼠标
		if(colorwhite)
		{
		//调用主框架里面的状态栏
			CMainFrame *pFrm=(CMainFrame*)AfxGetApp()->m_pMainWnd;
			CStatusBar *pStatus=&pFrm->m_wndStatusBar;
			if(pStatus)
			{
				pStatus->GetStatusBarCtrl().SetIcon(0,AfxGetApp()->LoadIcon(IDI_WHITE));
				pStatus->SetPaneText(0,"白棋落子");
		
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
				//显示图像
				pStatus->GetStatusBarCtrl().SetIcon(0,AfxGetApp()->LoadIcon(IDI_BLACK));
				//显示文字
				pStatus->SetPaneText(0,"黑棋落子");
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

//人机对战
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
	//保存上一步棋的位置
	over(point); 
	colorwhite=false;
	//保存白棋位置
	vspoint=point;
	//计算机下棋
	computerdown();
	}
	}
} 
	if(vscomputer==false)
	{

	//是否在棋盘内
	if(point.x>30&&point.x<410&&point.y>30&&point.y<410)
	{
		int px=(point.x-30)/20;
		int py=(point.y-30)/20;
		//由于除法是四舍五入的 所以可以保证棋子落在正确的位置
		//是否已经有棋子
		if(colorwhite&&wzq[px][py]==0)
		{
			Dc.SelectObject(m_bmwhite);
			pDC->BitBlt(px*20+32,py*20+32,160,160,&Dc,0,0,SRCCOPY);
			//表示存在白棋
			wzq[px][py]=1;
			//检查是否结束
			over(point);
			//换黑棋下
			colorwhite=false;
			LastPoint[0][0]=px;
			LastPoint[0][1]=py;//保存上一步棋的位置
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
函数名：over
作用：判断胜负
参数： CPoint point  当前棋子坐标
***********************************************************/
void CMyView::over(CPoint point) //判断胜负条件
{

//int winerValue=0;
	int i,j,k;
	for(i = 0; i<19;i++) 
	{ 
		bool win = false;    //一方胜利，结束 
		for ( j = 0; j < 19;j++) 

        { 
			if (wzq[i][j] == 0)  //空格不需要判定 
			continue; 
//水平方向连续棋子个数检测 
		int cnt = 1; 
			//左侧 
		for (k = j-1; k >= 0;k--) 
			{ 
				if (wzq[i][k] != wzq[i][j])    //非相同棋子时停止检测 
				{ break; } 
				else 
					cnt++; 
		} 
			 //右侧 
			for ( k = j + 1; k < 19; k++) 
			{ 
				 if (wzq[i][k] != wzq[i][j])    //非相同棋子时停止检测 
				{ break; } 
				else 
				cnt++; 
				} 

            //胜利 
			 if (cnt >= 5) 
		{ 
				win = true; 
				if(wzq[i][j]==-1)
			{	AfxMessageBox("黑棋胜!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("白棋胜!");
						OnStart();
			}
                break; 

            } 

  //竖直方向检测 

            cnt = 1; 

            //上方 
			 for (k = i - 1; k >= 0; k--) 
		{ 

                if (wzq[k][j] != wzq[i][j])    //非相同棋子时停止检测 

                { break;  } 
				 else 
				  cnt++; 

            } 

            //下方 
			for (k = i + 1; k < 19; k++) 

            { 

                if (wzq[k][j] != wzq[i][j])    //非相同棋子时停止检测 

                { break; } 

                else	 cnt++; 

            } 

            //胜利 
		if (cnt >= 5) 

            {  win = true; 

              
				if(wzq[i][j]==-1)
			{	AfxMessageBox("黑棋胜!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("白棋胜!");
						OnStart();
			}
                break; 

            } 
//从左下到右上检测 

            cnt = 1; 
			//左下 
			int m = i + 1; 
			for (k = j - 1; k >= 0; k--) 
		{ 

                if (m>=19)    //左下方出界 
				{  break; } 

                if (wzq[m][k] != wzq[i][j])    //非相同棋子时停止检测 

                {  break;  } 

                else 

				cnt++; 

              m++; 

            } 

            //右上 

            m = i - 1; 

            for ( k = i + 1; k < 19; k++) 

            { 

                if (m < 0)    //右上方出界 

                { break;  } 

                if (wzq[m][k] != wzq[i][j])    //非相同棋子时停止检测 

                { break; } 

                else 

                    cnt++; 

                m--; 

            } 

            //胜利 

            if (cnt >= 5) 

            { 

                win = true; 

				if(wzq[i][j]==-1)
			{	AfxMessageBox("黑棋胜!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("白棋胜!");
						OnStart();
			}

                break; 

            } 
 //从左上到右下检测 

            cnt = 1; 

            //左上 
			m = i - 1; 
			for ( k = j - 1; k >= 0; k--) 
		 { 

                if (m < 0)    //左上方出界 

                {  break;  } 

                if (wzq[m][k] != wzq[i][j])    //非相同棋子时停止检测 

                {  break;  } 

                else 

                    cnt++; 

                m--; 

            } 

            //右下 

            m = i + 1; 

            for ( k = i + 1; k < 19; k++) 

            { 

                if (m >= 19)    //右下方出界 

                {  break;  } 

                if (wzq[m][k] != wzq[i][j])    //非相同棋子时停止检测 

                {  break; } 

                else 

                    cnt++; 

                m++; 

            } 

            //胜利 

            if (cnt >= 5) 

            { 

                win = true; 

              
					if(wzq[i][j]==-1)
			{	AfxMessageBox("黑棋胜!");
						OnStart();
			}
				if(wzq[i][j]==1)
			{	AfxMessageBox("白棋胜!");
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
函数名：OnStart
作用：初始化棋盘
参数：无
***********************************************************/
void CMyView::OnStart()
{
	for(int i=0;i<19;i++)
	for(int j=0;j<19;j++)
	wzq[i][j]=0;
	//白棋先下
	colorwhite=true;
	InvalidateRect(NULL);
}


int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	   CRect rect_button1(0,0,64,20);   //控制按钮大小、位置
       m_button1.Create("双人对战",WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button1,this,IDB_BTN1);
       m_button1.ShowWindow(SW_SHOWNORMAL);
	   CRect rect_button2(0,21,40,41);   //控制按钮大小、位置
       m_button2.Create("悔棋",WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button2,this,IDB_BTN2);
	   CRect rect_button3(65,0,130,20);   //控制按钮大小、位置
	   m_button3.Create("人机对战",WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button3,this,IDB_BTN3);
       m_button3.ShowWindow(SW_SHOWNORMAL);


	return 0;
}
/**********************************************************
函数名：Regret
作用：悔棋
参数：无
***********************************************************/
void CMyView::Regret()
{	
	if(vscomputer==true)

	{	wzq[computer[0][0]][computer[0][1]]=0;
		wzq[vsLastPoint[1]][vsLastPoint[2]]=0;
	
		InvalidateRect(NULL);//窗口重新绘制调用OnDraw函数
	}
	if(vscomputer==false)  
	{
	wzq[LastPoint[0][0]][LastPoint[0][1]]=0;
	colorwhite=!colorwhite;
	InvalidateRect(NULL);//窗口重新绘制调用OnDraw函数
	}
}
void CMyView::OnClickButton1()
{	vscomputer=false;
	OnStart();
	MessageBox("开始游戏!","开始",MB_OK);
	
}

void CMyView::OnClickButton2()
{
	Regret();
	MessageBox("悔棋成功!","悔棋",MB_OK);

}

void CMyView::OnClickButton3()
{	vscomputer=true;
	OnStart();
	MessageBox("人机对战游戏开始!","开始",MB_OK);
	
}
/**********************************************************
函数名：computerdown
作用：计算机下棋
参数：无
***********************************************************/
void CMyView::computerdown()
{//把各种情形赋值为如下
	bpointcan4=(-1,-1);
	wpointcan4=(-1,-1); 
	bpointcan3=(-1,-1);
	wpointcan3=(-1,-1);
	bpointcan2=(-1,-1);
	wpointcan2=(-1,-1);
	bpointcan1=(-1,-1); 
//搜索最好的落棋点
	for(int i=0;i<19;i++) 
	for(int j=0;j<19;j++) 
	bestputdown(i,j); 
//判断放在哪里
//棋多的位置优先
//黑白一样多时黑先 
//不是-1就表示已经被赋值
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
//由于原来我们检查是否结束时用的是鼠标点下的坐标，而现在
//putdown(CPointpoint)函数用的是数组棋盘的坐标，所以必须转换
	CPoint overpoint; 
	overpoint.x=point.x*20+30;
	overpoint.y=point.y*20+30;
	over(overpoint);
	colorwhite=true;
}

void CMyView::bestputdown(int i,int j)
{
	int num[4];//四个方向的值
	int a,k;
	a=0;
	if(i<15) 
		for(k=0;k<5;k++) 
		a=a+wzq[i+k][j]; //记录上方的值
	num[0]=abs(a); //取绝对值	
	a=0;
	if(j<15) 
		for(k=0;k<5;k++) 
	    a=a+wzq[i][j+k];//记录右方的值	
	num[1]=abs(a);//取绝对值
	a=0; 
	if(i<15&&j<15) 
		for(k=0;k<5;k++) 
		a=a+wzq[i+k][j+k];//记录右下方的值 
	num[2]=abs(a); //取绝对值
	a=0; 
	if((i>4)&&(j<15)) 
		for(k=0;k<5;k++) 
		a=a+wzq[i-k][j+k]; //记录右上方的值
	num[3]=abs(a); //取绝对值
//比较哪个方向同色棋最多 
	CPoint numbig; 
//numbig.x表示方向
//numbig.y表示最大值 
//在四个方向上比较最大值确定方向
numbig=maxnum(num[0],num[1],num[2],num[3]);
//在得到最大值和方向上寻找落棋点
switch(numbig.y)
{	case 4: searchcandown4(i,j,numbig.x);break;
	case 3: searchcandown3(i,j,numbig.x);break;
	case 2: searchcandown2(i,j,numbig.x);break;
	default: searchcandown1(i,j,numbig.x);
}
}
CPoint CMyView::maxnum(int a,int b,int c,int d)
{
//point.x为方向值
//point.y为最大值
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
函数名：searchcandown4
作用：有四个同色棋时寻找给定方向的最佳落棋点
参数：棋子坐标i,j,搜索方向n
***********************************************************/
void CMyView::searchcandown4(int i,int j,int n)
{	int k;
	if(n==0) //在水平方向寻找落子点
	for(k=0;k<5;k++) 
	//如果第一个是空
	if(wzq[i][j]==0)
	{ //如果下面有白棋
	if(wzq[i+1][j]==1)
		{ //下面位置可以下棋，已经有四个白棋
			wpointcan4.x=i;
			wpointcan4.y=j;
			break;
		}
	else
		{ //下面位置可以下棋，已经有四个黑棋
			bpointcan4.x=i;
			bpointcan4.y=j;
			break;
		} 
	}
	else  if(wzq[i+k][j]==0)
	{ //如果第一个是白棋
	if(wzq[i][j]==1)
		{	wpointcan4.x=i+k;
			wpointcan4.y=j;
			break;
		} //否则第一个是黑棋
	else	
		{	bpointcan4.x=i+k;
			bpointcan4.y=j;
			break;
		}

	} 

	if(n==1) 	//在竖直方向寻找落棋点
	for(k=0;k<5;k++)
	{ if(wzq[i][j]==0) //如果第一个是空
	  if(wzq[i][j+1]==1)//如果第一个是白棋
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
//在右下方寻找落棋点
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
//在左下方寻找最佳落棋点
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
函数名：searchcandown3
作用：有四个同色棋时寻找给定方向的最佳落棋点
参数：棋子坐标i,j,搜索方向n
***********************************************************/
void CMyView::searchcandown3(int i,int j,int n)
{	int k=0; 
	//在水平方向寻找最佳落棋点
	if(n==0) 
	for(k=0;k<5;k++) 
	//找到位置 
	if(wzq[i+k][j]==0)
	{ //下一个是白棋 
	if(wzq[i+k+1][j]==1)
		{ //下面位置可以下棋，已经有三个白棋
		wpointcan3.x=i+k;
		wpointcan3.y=j;
		} //下一个是黑棋 
	else if(wzq[i+k+1][j]==-1) 
		{		bpointcan3.x=i+k;
				bpointcan3.y=j;
		} //在竖直方向寻找最近落棋点
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

//在右下方寻找最佳落棋点
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
//在左下方寻找最佳落棋点
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
函数名：searchcandown2
作用：有四个同色棋时寻找给定方向的最佳落棋点
参数：棋子坐标i,j,搜索方向n
***********************************************************/
void CMyView::searchcandown2(int i,int j,int n)
{	int k=0,m=0,a=0,b=0;
//在水平方向寻找最佳落棋点
	if(n==0)
	{	  for(k=0;k<5;k++)
		if(wzq[i+k][j]==0)
		m+=1;//记录水平方向的空位置
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
	

	//在竖直方向上寻找最佳落棋点
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
函数名：searchcandown1
作用：有四个同色棋时寻找给定方向的最佳落棋点
参数：棋子坐标i,j,搜索方向n
***********************************************************/
void CMyView::searchcandown1(int i,int j,int n)
{//计算刚才白棋落棋点
	int ii=(vspoint.x-30)/20;
	int jj=(vspoint.y-30)/20;	
	int a; 
	for(a=0;a<5;a++) 
		//如果不到边界
	if(ii+a<19)
	{ //向右，如果有空位置
	 if(wzq[ii+a][jj]==0)
		{	//在这个位置下黑棋
			bpointcan1.x=ii+a;
			bpointcan1.y=jj;
			return;
		}
	} 
//到了边界 
	else if(wzq[ii+a][jj]==0) //向左，如果有空位置
	{	bpointcan1.x=ii-a;
		bpointcan1.y=jj;
		return;
	}
}



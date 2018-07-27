#include"stdio.h" 
#include"stdlib.h"

//此程序目前只限bmp格式图片使用。 

char r[3000][3000],g[3000][3000],b[3000][3000];
int b1[3000][3000],g1[3000][3000],r1[3000][3000],all[3000][3000] ;
int startplace=0,width=0,height=0; 
int num;


void bmptest(FILE*bmpfp);              //测试格式正确。
void bmpinformation(FILE*bmpfp);       //读取图片信息。 
void bmpcopyoutput(FILE*bmpfp);        //复制输出。
void bmpfly(FILE*bmpfp);               //旋转输出。 
void bmpfullmsk(FILE*bmpfp);           //全局马赛克。 
void bmpmsk(FILE*bmpfp);               //局部马赛克。 
void bmpturn();                        //字符画。 
void bmpboom(FILE*bmpfp);              //镜像输出。 


int main()
{
  FILE*bmpfp;
  bmpfp=fopen("bmp1.bmp","rb");
  if(bmpfp==NULL)
  { 
    printf("无法打开图片!\n");
    return 0;
  }
  else printf("成功打开图片!\n");//首先确认图片可以打开 。
  
  bmptest(bmpfp);//检测文件是否为bmp格式。 
  
  bmpinformation(bmpfp);//读取文件信息，并用字符数组对文件信息进行储存。 
  
  int x; 
  while(1) 
  { 
  for(x=0;x<50;x++)printf("%c",77) ;
  printf("\n"); 
  for(x=0;x<3;x++)printf("%-49c%c\n",77,77) ;
  printf("%-10c按【1】进行文件复制输出%17c\n",77,77); 
  printf("%-10c按【2】进行文件旋转输出%17c\n",77,77); 
  printf("%-10c按【3】进行文件全局马赛克输出%11c\n",77,77); 
  printf("%-10c按【4】进行文件局部马赛克输出%11c\n",77,77); 
  printf("%-10c按【5】进行文件字符画输出%15c\n",77,77);
  printf("%-10c按【6】进行文件镜像输出%17c\n",77,77); 
  printf("%-10c按【0】退出%29c\n",77,77); 
  for(x=0;x<3;x++)printf("%-49c%c\n",77,77) ;
  for(x=0;x<50;x++)printf("%c",77) ;
  printf("\n\n"); 
  printf("请输入：") ; 
  scanf("%d",&num);
  switch(num)
   {
   	case 1:bmpcopyoutput(bmpfp);break;                      //复制输出。 
   	case 2:bmpfly(bmpfp);break;                             //旋转输出。 
   	case 3:bmpfullmsk(bmpfp) ;break;                        //全局马赛克输出。 
   	case 4:bmpmsk(bmpfp) ;break;                            //局部马赛克输出。 
   	case 5:bmpturn();break;                                 //字符画输出。 
   	case 6:bmpboom(bmpfp);break;                            //镜像处理输出。 
   	case 0:return 0;                                        //结束运行。 
   	default:printf("输入错误，请重新输入\n"); 
   } 
  }                                                         //菜单的循环输出，并调用相应函数。 
  fclose(bmpfp);
  system("pause");
  return 0;
}


void bmptest(FILE*bmpfp)//文件检测 。 
{
  char bmptestname1=0,bmptestname2=0;
  fseek(bmpfp,0,SEEK_SET);
  fread(&bmptestname1,1,1,bmpfp);
  fseek(bmpfp,1,SEEK_SET);
  fread(&bmptestname2,1,1,bmpfp);
  if(bmptestname1=='B'&& bmptestname2=='M')                 //定位指针位置并读取前两个字符。 
    printf("图片格式为BMP !\n");
  else 
    {
	printf("\n图片格式错误 !\n"); 
	system("pause");
	return 0; 
	}                        
  return 1; 
}

 
 
void bmpinformation(FILE*bmpfp)//文件信息。 
{
  int i=0,j=0,fact=0; 
  char *temp=0; 
  fseek(bmpfp,10,SEEK_SET) ;//读取文件长度 
  fread(&startplace,sizeof(char),4,bmpfp);
  fseek(bmpfp,18,SEEK_SET) ;//读取文件宽度 
  fread(&width,sizeof(char),4,bmpfp);
  fseek(bmpfp,22,SEEK_SET) ;//读取文件高度 
  fread(&height,sizeof(char),4,bmpfp);
  printf("图片分辨率为%d * %d\n\n",width,height); 
  
  fact=width*3;//计算每行实际字符数量（必须为4的倍数） 
  fseek(bmpfp,startplace,SEEK_SET) ;
  while(fact%4!=0)
    fact+=1 ;
  temp=malloc(fact); 
  for(i=0;i<height;i++) 
    {
	 fread(temp,1,fact,bmpfp) ;
	 for(j=0;j<width;j++) 
	   {b[j][i]=temp[j*3+0];
	    g[j][i]=temp[j*3+1]; 
		r[j][i]=temp[j*3+2]; 
	   } 
	} //把像素信息按字符格式存入字符数组 
  return 1;
} 


  
void bmpcopyoutput(FILE*bmpfp)//文件拷贝。 
{
  FILE*bmpcopyoutfp;
  int i,j,fact;
  char*temp;
  
  bmpcopyoutfp=fopen("bmpcopyout.bmp", "wb+"); //定义变量并创建新文件。 
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpcopyoutfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);
  fwrite(temp,1,startplace,bmpcopyoutfp);//文件头全部拷贝 
  
  fseek(bmpcopyoutfp,startplace,SEEK_SET);
  fact=width*3;
  while(fact%4!=0)
    fact+=1 ;
  temp=malloc(fact); 
  for(i=0;i<height;i++)
  {
  for(j=0;j<width;j++)
     {
	 temp[j*3]=b[j][i];
     temp[j*3+1]=g[j][i];
     temp[j*3+2]=r[j][i];
     } 
  fwrite(temp,1,fact,bmpcopyoutfp); 
  }//文件像素内容部分全部拷贝 
  fclose(bmpcopyoutfp);
  printf("操作成功\n")  ;  
  return 1; 
} 



void bmpfullmsk(FILE*bmpfp)//文件全局马塞克。 
{
  FILE*bmpfullmskfp;
  int i,j,fact,k;
  char*temp;
  
  bmpfullmskfp=fopen("bmpfullmsk.bmp", "wb+"); 
  
  printf("请输入处理程度（1-10）:") ; 
  scanf("%d",&k); 
  if(k<1||k>10) 
    {
    printf("输入错误\n") ;
    return 1;
    }//录入处理程度 
  k=k*5 ; 
  
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpfullmskfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);//文件头全部拷贝 
  
  fwrite(temp,1,startplace,bmpfullmskfp);
  fseek(bmpfullmskfp,startplace,SEEK_SET);
  fact=width*3;
  while(fact%4!=0)
    fact+=1 ;
  temp=malloc(fact); 
  for(i=0;i<height;i++)
  {
  for(j=0;j<width;j++)
     {
	 temp[j*3]=b[j-j%k][i-i%k];
     temp[j*3+1]=g[j-j%k][i-i%k];
     temp[j*3+2]=r[j-j%k][i-i%k];
     } 
  fwrite(temp,1,fact,bmpfullmskfp); 
  }//以一个角的单个像素为基准，范围复制到其他部分 
  fclose(bmpfullmskfp);
  printf("操作成功\n")  ;  
  return 1; 
} 
  

  
void bmpmsk(FILE*bmpfp)//局部马赛克 
{
  FILE*bmpmskfp;
  int i,j,fact,k,width1,width2,height1,height2;
  char*temp;
  
  bmpmskfp=fopen("bmpmsk.bmp", "wb+"); 
  
  printf("请输入处理程度（1-10）:") ; 
  scanf("%d",&k);
  if(k<1||k>10) 
    {
    printf("输入错误\n") ;
    return 1;
    }
  k=k*5 ; 
  
  
  printf("请输入处理范围（从左下角到右上角的坐标）:") ; 
  scanf("%d%d%d%d",&width1,&height1,&width2,&height2); 
  if(width1>=width2||width2>width||height1>=height2||height2>height)
  {
  printf("输入错误\n");
  return 1; // 录入两个坐标并检测是否正确 
  } 
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpmskfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);
  fwrite(temp,1,startplace,bmpmskfp);//文件头复制 
  
  fseek(bmpmskfp,startplace,SEEK_SET);
  fact=width*3;
  while(fact%4!=0)
    fact+=1 ;
  temp=malloc(fact); 
  
  for(i=0;i<height;i++)
  {
   if(i<=height2&&i>=height1) 
    for(j=0;j<width;j++)
       {
	    if(j<=width2&&j>=width1)
	     {
	     temp[j*3]=b[j-j%k][i-i%k];
         temp[j*3+1]=g[j-j%k][i-i%k];
         temp[j*3+2]=r[j-j%k][i-i%k];
         }
        else
         {
	     temp[j*3]=b[j][i];
         temp[j*3+1]=g[j][i];
         temp[j*3+2]=r[j][i];
         } 
	   } 
    else
    for(j=0;j<width;j++)
     {
	 temp[j*3]=b[j][i];
     temp[j*3+1]=g[j][i];
     temp[j*3+2]=r[j][i];
     } 
  fwrite(temp,1,fact,bmpmskfp); 
  }//对是否在范围内进行判断，不在范围内的按复制处理 
  fclose(bmpmskfp);
  printf("操作成功\n")  ;  
  return 1;
}



void bmpturn()//字符画输出 
{
  int i,j;
  char temp[3000];
  FILE*bmpturnfp;
  
  bmpturnfp=fopen("bmpturn.txt", "w+"); 
  
  for(j=0;j<height;j++) 
     for(i=0;i<width;i++) 
      {
	  if(((int)b[i][j])<0) 
	    b1[i][j]=(int)b[i][j]+256 ; 
	  else
	    b1[i][j]=(int)b[i][j]; 
	  if(((int)g[i][j])<0) 
	    g1[i][j]=(int)g[i][j]+256 ; 
	  else
	    g1[i][j]=(int)g[i][j]; 
	  if(((int)r[i][j])<0) 
	    r1[i][j]=(int)r[i][j]+256 ; 
	  else
	    r1[i][j]=(int)r[i][j];
	  all[i][j] =(b1[i][j]+ g1[i][j]+r1[i][j] )/3 ;
      }//计算亮度 
   
   
fseek(bmpturnfp,0,SEEK_SET);
  for(j=height-1;j>0;j=j-1)
	{
	if(j%2==0) continue;
	for(i=0;i<width;i=i+1)
	  if(all[i][j]>=20)
	    if(all[i][j]>=40)
	      if(all[i][j]>=70)
		    if(all[i][j]>=110)
	          if(all[i][j]>=170)
	           temp[i]=(char)32;
	          else 
		       temp[i]=(char)46;
	        else 
		      temp[i]=(char)47;
	      else 
		    temp[i]=(char)73;
		else
		  temp[i]=(char)78;
	  else 
	    temp[i]=(char)77; 
	temp[i]=(char)10;
	fputs(&temp,bmpturnfp);
    }//录入txt文本 
  fclose(bmpturnfp);
  printf("操作成功\n");  
  return 1;
} 
    
    
    
void bmpfly(FILE*bmpfp)
{
  FILE*bmpflyfp;
  int i,j,fact,order,newheight,newwidth;
  char*temp;
  
  printf("顺时针90度请按1\n"); 
  printf("顺时针180度请按2\n");
  printf("逆时针90度请按3\n");
  scanf("%d",&order);
  switch(order)
  {
  
  
  case 3 : 
    bmpflyfp=fopen("bmpflyout.bmp", "wb+"); 
    
	newheight=width;
    newwidth=height; 
  
    fseek(bmpfp,0,SEEK_SET);
    fseek(bmpflyfp,0,SEEK_SET);
    temp=malloc(17);
    fread(temp,1,17,bmpfp);
    fwrite(temp,1,17,bmpflyfp);//复制头文件第一部分。 
   
    fseek(bmpfp,22,SEEK_SET);
    fseek(bmpflyfp,18,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);
  
    fseek(bmpfp,18,SEEK_SET);
    fseek(bmpflyfp,22,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);//长宽改变 
  
  
    fseek(bmpfp,26,SEEK_SET);
    fseek(bmpflyfp,26,SEEK_SET);
    temp=malloc(28);
    fread(temp,1,26,bmpfp);
    fwrite(temp,1,26,bmpflyfp);//复制头文件第二部分 
   
    fseek(bmpflyfp,startplace,SEEK_SET);
    fact=newwidth*3;
    while(fact%4!=0)
    fact+=1 ;
    temp=malloc(fact); //重新计算宽度上字符的个数 
  
    for(i=newheight-1;i>=0;i--)
      {
  	for(j=0;j<newwidth;j++)
  	       {
    	   temp[j*3]=b[i][j];
           temp[j*3+1]=g[i][j];
           temp[j*3+2]=r[i][j];
           }
    fwrite(temp,1,fact,bmpflyfp); 
      } //像素信息录入 
    break; 
  
  
  case 2 : 
    bmpflyfp=fopen("bmpflyout.bmp", "wb+"); 
    
	newwidth=width;
    newheight=height; 
  
    fseek(bmpfp,0,SEEK_SET);
    fseek(bmpflyfp,0,SEEK_SET);
    temp=malloc(startplace);
    fread(temp,1,startplace,bmpfp);
    fwrite(temp,1,startplace,bmpflyfp); //文件头复制            
   
    fseek(bmpflyfp,startplace,SEEK_SET);
    fact=newwidth*3;
    while(fact%4!=0)
    fact+=1 ;
    temp=malloc(fact); 
  
    for(j=newheight-1;j>=0;j--)
      {
  	for(i=0;i<newwidth;i++)
  	       {
    	   temp[i*3]=b[newwidth-1-i][j];
           temp[i*3+1]=g[newwidth-1-i][j];
           temp[i*3+2]=r[newwidth-1-i][j];
           }
    fwrite(temp,1,fact,bmpflyfp); 
      } //像素信息录入
    break;
  
  
  case 1 : 
    bmpflyfp=fopen("bmpflyout.bmp", "wb+"); 
    
	newheight=width;
    newwidth=height; 
  
    fseek(bmpfp,0,SEEK_SET);
    fseek(bmpflyfp,0,SEEK_SET);
    temp=malloc(17);
    fread(temp,1,17,bmpfp);
    fwrite(temp,1,17,bmpflyfp);//复制头文件第一部分。 
   
    fseek(bmpfp,22,SEEK_SET);
    fseek(bmpflyfp,18,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);
  
    fseek(bmpfp,18,SEEK_SET);
    fseek(bmpflyfp,22,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);//长宽改变 
  
  
    fseek(bmpfp,26,SEEK_SET);
    fseek(bmpflyfp,26,SEEK_SET);
    temp=malloc(28);
    fread(temp,1,26,bmpfp);
    fwrite(temp,1,26,bmpflyfp);//复制头文件第二部分。 
   
    fseek(bmpflyfp,startplace,SEEK_SET);
    fact=newwidth*3;
    while(fact%4!=0)
    fact+=1 ;
    temp=malloc(fact); 
  
    for(i=newheight;i>=0;i--)
      {
  	for(j=newwidth;j>=0;j--)
  	       {
    	   temp[j*3]=b[i][j];
           temp[j*3+1]=g[i][j];
           temp[j*3+2]=r[i][j];
           }
    fwrite(temp,1,fact,bmpflyfp); 
      } 
    break; 
  default: printf("输入错误，请重新输入");  
  }//像素信息录入
  fclose(bmpflyfp);
  printf("操作成功\n")  ;  
  return 1; 
} 



void bmpboom(FILE*bmpfp)
{
  FILE*bmpboomfp;
  int i,j,fact; 
  char*temp;
  
  bmpboomfp=fopen("bmpboomout.bmp", "wb+"); 
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpboomfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);
  fwrite(temp,1,startplace,bmpboomfp);  //头文件复制            
   
  fseek(bmpboomfp,startplace,SEEK_SET);
  fact=width*3;
  while(fact%4!=0)
    fact+=1 ;
  temp=malloc(fact); 
  
  for(j=0;j<height;j++)
  {
  for(i=0;i<width;i++)
    {
    	temp[i*3]=b[width-1-i][j];
        temp[i*3+1]=g[width-1-i][j];
        temp[i*3+2]=r[width-1-i][j];
    }
  fwrite(temp,1,fact,bmpboomfp); 
  } //像素内容复制 
  fclose(bmpboomfp);
  printf("操作成功\n")  ;  	
  return 1; 
}
 
 

#include"stdio.h" 
#include"stdlib.h"

//�˳���Ŀǰֻ��bmp��ʽͼƬʹ�á� 

char r[3000][3000],g[3000][3000],b[3000][3000];
int b1[3000][3000],g1[3000][3000],r1[3000][3000],all[3000][3000] ;
int startplace=0,width=0,height=0; 
int num;


void bmptest(FILE*bmpfp);              //���Ը�ʽ��ȷ��
void bmpinformation(FILE*bmpfp);       //��ȡͼƬ��Ϣ�� 
void bmpcopyoutput(FILE*bmpfp);        //���������
void bmpfly(FILE*bmpfp);               //��ת����� 
void bmpfullmsk(FILE*bmpfp);           //ȫ�������ˡ� 
void bmpmsk(FILE*bmpfp);               //�ֲ������ˡ� 
void bmpturn();                        //�ַ����� 
void bmpboom(FILE*bmpfp);              //��������� 


int main()
{
  FILE*bmpfp;
  bmpfp=fopen("bmp1.bmp","rb");
  if(bmpfp==NULL)
  { 
    printf("�޷���ͼƬ!\n");
    return 0;
  }
  else printf("�ɹ���ͼƬ!\n");//����ȷ��ͼƬ���Դ� ��
  
  bmptest(bmpfp);//����ļ��Ƿ�Ϊbmp��ʽ�� 
  
  bmpinformation(bmpfp);//��ȡ�ļ���Ϣ�������ַ�������ļ���Ϣ���д��档 
  
  int x; 
  while(1) 
  { 
  for(x=0;x<50;x++)printf("%c",77) ;
  printf("\n"); 
  for(x=0;x<3;x++)printf("%-49c%c\n",77,77) ;
  printf("%-10c����1�������ļ��������%17c\n",77,77); 
  printf("%-10c����2�������ļ���ת���%17c\n",77,77); 
  printf("%-10c����3�������ļ�ȫ�����������%11c\n",77,77); 
  printf("%-10c����4�������ļ��ֲ����������%11c\n",77,77); 
  printf("%-10c����5�������ļ��ַ������%15c\n",77,77);
  printf("%-10c����6�������ļ��������%17c\n",77,77); 
  printf("%-10c����0���˳�%29c\n",77,77); 
  for(x=0;x<3;x++)printf("%-49c%c\n",77,77) ;
  for(x=0;x<50;x++)printf("%c",77) ;
  printf("\n\n"); 
  printf("�����룺") ; 
  scanf("%d",&num);
  switch(num)
   {
   	case 1:bmpcopyoutput(bmpfp);break;                      //��������� 
   	case 2:bmpfly(bmpfp);break;                             //��ת����� 
   	case 3:bmpfullmsk(bmpfp) ;break;                        //ȫ������������� 
   	case 4:bmpmsk(bmpfp) ;break;                            //�ֲ������������ 
   	case 5:bmpturn();break;                                 //�ַ�������� 
   	case 6:bmpboom(bmpfp);break;                            //����������� 
   	case 0:return 0;                                        //�������С� 
   	default:printf("�����������������\n"); 
   } 
  }                                                         //�˵���ѭ���������������Ӧ������ 
  fclose(bmpfp);
  system("pause");
  return 0;
}


void bmptest(FILE*bmpfp)//�ļ���� �� 
{
  char bmptestname1=0,bmptestname2=0;
  fseek(bmpfp,0,SEEK_SET);
  fread(&bmptestname1,1,1,bmpfp);
  fseek(bmpfp,1,SEEK_SET);
  fread(&bmptestname2,1,1,bmpfp);
  if(bmptestname1=='B'&& bmptestname2=='M')                 //��λָ��λ�ò���ȡǰ�����ַ��� 
    printf("ͼƬ��ʽΪBMP !\n");
  else 
    {
	printf("\nͼƬ��ʽ���� !\n"); 
	system("pause");
	return 0; 
	}                        
  return 1; 
}

 
 
void bmpinformation(FILE*bmpfp)//�ļ���Ϣ�� 
{
  int i=0,j=0,fact=0; 
  char *temp=0; 
  fseek(bmpfp,10,SEEK_SET) ;//��ȡ�ļ����� 
  fread(&startplace,sizeof(char),4,bmpfp);
  fseek(bmpfp,18,SEEK_SET) ;//��ȡ�ļ���� 
  fread(&width,sizeof(char),4,bmpfp);
  fseek(bmpfp,22,SEEK_SET) ;//��ȡ�ļ��߶� 
  fread(&height,sizeof(char),4,bmpfp);
  printf("ͼƬ�ֱ���Ϊ%d * %d\n\n",width,height); 
  
  fact=width*3;//����ÿ��ʵ���ַ�����������Ϊ4�ı����� 
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
	} //��������Ϣ���ַ���ʽ�����ַ����� 
  return 1;
} 


  
void bmpcopyoutput(FILE*bmpfp)//�ļ������� 
{
  FILE*bmpcopyoutfp;
  int i,j,fact;
  char*temp;
  
  bmpcopyoutfp=fopen("bmpcopyout.bmp", "wb+"); //����������������ļ��� 
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpcopyoutfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);
  fwrite(temp,1,startplace,bmpcopyoutfp);//�ļ�ͷȫ������ 
  
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
  }//�ļ��������ݲ���ȫ������ 
  fclose(bmpcopyoutfp);
  printf("�����ɹ�\n")  ;  
  return 1; 
} 



void bmpfullmsk(FILE*bmpfp)//�ļ�ȫ�������ˡ� 
{
  FILE*bmpfullmskfp;
  int i,j,fact,k;
  char*temp;
  
  bmpfullmskfp=fopen("bmpfullmsk.bmp", "wb+"); 
  
  printf("�����봦��̶ȣ�1-10��:") ; 
  scanf("%d",&k); 
  if(k<1||k>10) 
    {
    printf("�������\n") ;
    return 1;
    }//¼�봦��̶� 
  k=k*5 ; 
  
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpfullmskfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);//�ļ�ͷȫ������ 
  
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
  }//��һ���ǵĵ�������Ϊ��׼����Χ���Ƶ��������� 
  fclose(bmpfullmskfp);
  printf("�����ɹ�\n")  ;  
  return 1; 
} 
  

  
void bmpmsk(FILE*bmpfp)//�ֲ������� 
{
  FILE*bmpmskfp;
  int i,j,fact,k,width1,width2,height1,height2;
  char*temp;
  
  bmpmskfp=fopen("bmpmsk.bmp", "wb+"); 
  
  printf("�����봦��̶ȣ�1-10��:") ; 
  scanf("%d",&k);
  if(k<1||k>10) 
    {
    printf("�������\n") ;
    return 1;
    }
  k=k*5 ; 
  
  
  printf("�����봦��Χ�������½ǵ����Ͻǵ����꣩:") ; 
  scanf("%d%d%d%d",&width1,&height1,&width2,&height2); 
  if(width1>=width2||width2>width||height1>=height2||height2>height)
  {
  printf("�������\n");
  return 1; // ¼���������겢����Ƿ���ȷ 
  } 
  
  fseek(bmpfp,0,SEEK_SET);
  fseek(bmpmskfp,0,SEEK_SET);
  temp=malloc(startplace);
  fread(temp,1,startplace,bmpfp);
  fwrite(temp,1,startplace,bmpmskfp);//�ļ�ͷ���� 
  
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
  }//���Ƿ��ڷ�Χ�ڽ����жϣ����ڷ�Χ�ڵİ����ƴ��� 
  fclose(bmpmskfp);
  printf("�����ɹ�\n")  ;  
  return 1;
}



void bmpturn()//�ַ������ 
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
      }//�������� 
   
   
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
    }//¼��txt�ı� 
  fclose(bmpturnfp);
  printf("�����ɹ�\n");  
  return 1;
} 
    
    
    
void bmpfly(FILE*bmpfp)
{
  FILE*bmpflyfp;
  int i,j,fact,order,newheight,newwidth;
  char*temp;
  
  printf("˳ʱ��90���밴1\n"); 
  printf("˳ʱ��180���밴2\n");
  printf("��ʱ��90���밴3\n");
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
    fwrite(temp,1,17,bmpflyfp);//����ͷ�ļ���һ���֡� 
   
    fseek(bmpfp,22,SEEK_SET);
    fseek(bmpflyfp,18,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);
  
    fseek(bmpfp,18,SEEK_SET);
    fseek(bmpflyfp,22,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);//����ı� 
  
  
    fseek(bmpfp,26,SEEK_SET);
    fseek(bmpflyfp,26,SEEK_SET);
    temp=malloc(28);
    fread(temp,1,26,bmpfp);
    fwrite(temp,1,26,bmpflyfp);//����ͷ�ļ��ڶ����� 
   
    fseek(bmpflyfp,startplace,SEEK_SET);
    fact=newwidth*3;
    while(fact%4!=0)
    fact+=1 ;
    temp=malloc(fact); //���¼��������ַ��ĸ��� 
  
    for(i=newheight-1;i>=0;i--)
      {
  	for(j=0;j<newwidth;j++)
  	       {
    	   temp[j*3]=b[i][j];
           temp[j*3+1]=g[i][j];
           temp[j*3+2]=r[i][j];
           }
    fwrite(temp,1,fact,bmpflyfp); 
      } //������Ϣ¼�� 
    break; 
  
  
  case 2 : 
    bmpflyfp=fopen("bmpflyout.bmp", "wb+"); 
    
	newwidth=width;
    newheight=height; 
  
    fseek(bmpfp,0,SEEK_SET);
    fseek(bmpflyfp,0,SEEK_SET);
    temp=malloc(startplace);
    fread(temp,1,startplace,bmpfp);
    fwrite(temp,1,startplace,bmpflyfp); //�ļ�ͷ����            
   
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
      } //������Ϣ¼��
    break;
  
  
  case 1 : 
    bmpflyfp=fopen("bmpflyout.bmp", "wb+"); 
    
	newheight=width;
    newwidth=height; 
  
    fseek(bmpfp,0,SEEK_SET);
    fseek(bmpflyfp,0,SEEK_SET);
    temp=malloc(17);
    fread(temp,1,17,bmpfp);
    fwrite(temp,1,17,bmpflyfp);//����ͷ�ļ���һ���֡� 
   
    fseek(bmpfp,22,SEEK_SET);
    fseek(bmpflyfp,18,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);
  
    fseek(bmpfp,18,SEEK_SET);
    fseek(bmpflyfp,22,SEEK_SET);
    temp=malloc(4);
    fread(temp,1,4,bmpfp);
    fwrite(temp,1,4,bmpflyfp);//����ı� 
  
  
    fseek(bmpfp,26,SEEK_SET);
    fseek(bmpflyfp,26,SEEK_SET);
    temp=malloc(28);
    fread(temp,1,26,bmpfp);
    fwrite(temp,1,26,bmpflyfp);//����ͷ�ļ��ڶ����֡� 
   
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
  default: printf("�����������������");  
  }//������Ϣ¼��
  fclose(bmpflyfp);
  printf("�����ɹ�\n")  ;  
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
  fwrite(temp,1,startplace,bmpboomfp);  //ͷ�ļ�����            
   
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
  } //�������ݸ��� 
  fclose(bmpboomfp);
  printf("�����ɹ�\n")  ;  	
  return 1; 
}
 
 

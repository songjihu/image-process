#include"stdio.h" 
#include"stdlib.h"

char r[3000][3000],g[3000][3000],b[3000][3000];



void bmptest(FILE*bmpfp); 
void bmppixnum(FILE*bmpfp);


int main()
{ FILE*bmpfp;
  
  
  bmpfp=fopen("bmp1.bmp","rb");
  if(bmpfp==NULL)
  { printf("�޷���ͼƬ!\n");
    return 0;
  }
  else printf("�ɹ���ͼƬ!\n");
  
  bmptest(bmpfp); 
  
 
  
  system("pause");
  return 0;
}

void bmptest(FILE*bmpfp)
{ char bmptestname1=0,bmptestname2=0;
  fseek(bmpfp,0L,SEEK_SET);
  fread(&bmptestname1,sizeof(char),1,bmpfp);
  fseek(bmpfp,1L,SEEK_SET);
  fread(&bmptestname2,sizeof(char),1,bmpfp);
  if(bmptestname1=='B'&& bmptestname2=='M')
    printf("ͼƬ��ʽΪBMP !\n");
  else 
    printf("ͼƬ��ʽ���� !\n"); 
  exit(1);
}






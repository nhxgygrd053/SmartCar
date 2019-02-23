
/*ģ���Ż�p*/
#include "include.h"
#include <math.h>

#define PMAX    100
#define PMIN    -100
#define DMAX    100
#define DMIN    -100
#define FMAX    100       
/*����ֵ������ֵ*/


//����p=-80_80  d=-30_30
  
/**********************************************************/
float Fuzzy(float *P,float *D)   /*ģ��*/
{
  float off_set=(Servo_Duty_Rt-Servo_Duty_Lf)/14;
  
float PFF[4]={0,20,40,60};//{0,12,24,48};
/*������D���Ե�������*/
float DFF[4]={0,7,15,20};//{0,16,32,64};
/*�����U������ֵ��������*/

float UFF[7]={2*off_set,3*off_set,4*off_set,5*off_set,6*off_set,7*off_set,8*off_set};//{0,15,30,45,60,75,90};

int rule[7][7]={
  
    //ec -3,-2,-1, 0, 1, 2, 3       //   e
      { 0, 0, 1, 1, 2, 2, 3,},   //   -3
      { 0, 1, 1, 2, 2, 3, 4,},   //   -2
      { 1, 1, 2, 3, 4, 5, 6,},   //   -1
      { 1, 2, 3, 4, 5, 6, 6,},   //    0
      { 2, 3, 4, 5, 6, 6, 6,},   //    1
      { 3, 4, 5, 6, 6, 6, 6,},   //    2
      { 4, 5, 6, 6, 6, 6, 6 }     //   3
      };   
  
// int rule[7][7]={ 
//  //ec -3,-2,-1, 0, 1, 2, 3       //   e
//      { 0, 0, 0, 1, 1, 2, 3,},   //   -3
//      { 0, 0, 1, 1, 2, 3, 4,},   //   -2
//      { 0, 1, 2, 3, 4, 5, 6,},   //   -1
//      { 1, 2, 3, 4, 5, 6, 6,},   //    0
//      { 2, 3, 4, 5, 6, 6, 6,},   //    1
//      { 3, 4, 5, 6, 6, 6, 6,},   //    2
//      { 4, 5, 6, 6, 6, 6, 6 }     //   3
//      };   



float    U;           
/*ƫ��,ƫ��΢���Լ����ֵ�ľ�ȷ��*/
int   PF[2],DF[2],UF[4];  
/*ƫ��,ƫ��΢���Լ����ֵ��������*/
int    Pn,Dn,Un[4];
long   temp1,temp2;

/*�����ȵ�ȷ��*/
/*����P/ƫ��/D/ƫ��ı仯��/��ָ�����Ի����Ч������*/
if(*P>-PFF[3] && *P<PFF[3])
{
    if(*P<=-PFF[2])
	{
		 Pn=-2;
		 PF[0]=FMAX*((float)(-PFF[2]-*P)/(PFF[3]-PFF[2]));
	}
    else if(*P<=-PFF[1])
   {
    Pn=-1;
    PF[0]=FMAX*((float)(-PFF[1]-*P)/(PFF[2]-PFF[1]));
   }
    else if(*P<=PFF[0])
   {
    Pn=0;
    PF[0]=FMAX*((float)(-PFF[0]-*P)/(PFF[1]-PFF[0]));
   }
    else if(*P<=PFF[1])
   {
    Pn=1; PF[0]=FMAX*((float)(PFF[1]-*P)/(PFF[1]-PFF[0]));
   }
    else if(*P<=PFF[2])
   {
    Pn=2; PF[0]=FMAX*((float)(PFF[2]-*P)/(PFF[2]-PFF[1]));
   }
    else if(*P<=PFF[3])
   {
    Pn=3; PF[0]=FMAX*((float)(PFF[3]-*P)/(PFF[3]-PFF[2]));
   }
    }
else if(*P<=-PFF[3])
   {
    Pn=-2;   PF[0]=FMAX;
   }
else if(*P>=PFF[3])
   {
    Pn=3;   PF[0]=0;
   }
PF[1]=FMAX-PF[0];
if(*D>-DFF[3] && *D<DFF[3])
{
		if(*D<=-DFF[2])
		{
			 Dn=-2;DF[0]=FMAX*((float)(-DFF[2]-*D)/(DFF[3]-DFF[2]));
		}
    else if(*D<=-DFF[1])
   {
    Dn=-1;
    DF[0]=FMAX*((float)(-DFF[1]-*D)/(DFF[2]-DFF[1]));
   }
    else if(*D<=DFF[0])
   {
    Dn=0;
    DF[0]=FMAX*((float)(-DFF[0]-*D)/(DFF[1]-DFF[0]));
   }
    else if(*D<=DFF[1])
   {
    Dn=1;
    DF[0]=FMAX*((float)(DFF[1]-*D)/(DFF[1]-DFF[0]));
   }
    else if(*D<=DFF[2])
   {
    Dn=2; DF[0]=FMAX*((float)(DFF[2]-*D)/(DFF[2]-DFF[1]));
   }
    else if(*D<=DFF[3])
   {
    Dn=3; DF[0]=FMAX*((float)(DFF[3]-*D)/(DFF[3]-DFF[2]));
   }
    }
else if(*D<=-DFF[3])
   {
    Dn=-2;
    DF[0]=FMAX;
   }
else if(*D>=DFF[3])
   {
   Dn=3;
   DF[0]=0;
   }
DF[1]=FMAX-DF[0];
/*ʹ����Χ�Ż���Ĺ����rule[7][7]*/
/*���ֵʹ��13����������,����ֵ��UFF[7]ָ��*/
/*һ�㶼���ĸ�������Ч*/
Un[0]=rule[Pn-1+3][Dn-1+3];
Un[1]=rule[Pn+3][Dn-1+3];
Un[2]=rule[Pn-1+3][Dn+3];
Un[3]=rule[Pn+3][Dn+3];
if(PF[0]<=DF[0])
   UF[0]=PF[0];
else
   UF[0]=DF[0];
if(PF[1]<=DF[0])
   UF[1]=PF[1];
else
   UF[1]=DF[0];
if(PF[0]<=DF[1])
   UF[2]=PF[0];
else
   UF[2]=DF[1];
if(PF[1]<=DF[1])
   UF[3]=PF[1];
else
   UF[3]=DF[1];
/*ͬ���������������ֵ���*/

if(Un[0]==Un[1])
{
   if(UF[0]>UF[1])
    UF[1]=0;
   else
    UF[0]=0;
}
if(Un[0]==Un[2])
{
   if(UF[0]>UF[2])
    UF[2]=0;
   else
    UF[0]=0;
}
if(Un[0]==Un[3])
{
   if(UF[0]>UF[3])
    UF[3]=0;
   else
    UF[0]=0;
}
if(Un[1]==Un[2])
{
   if(UF[1]>UF[2])
    UF[2]=0;
   else
    UF[1]=0;
}
if(Un[1]==Un[3])
{
   if(UF[1]>UF[3])
    UF[3]=0;
   else
    UF[1]=0;
}
if(Un[2]==Un[3])
{
   if(UF[2]>UF[3])
    UF[3]=0;
   else
    UF[2]=0;
}

/*���ķ���ģ��*/
/*Un[]ԭֵΪ������������ı�ţ�ת��Ϊ��������ֵ*/
if(Un[0]>=0)
   Un[0]=UFF[Un[0]];
else
   Un[0]=-UFF[-Un[0]];
if(Un[1]>=0)
   Un[1]=UFF[Un[1]];
else
   Un[1]=-UFF[-Un[1]];
if(Un[2]>=0)
   Un[2]=UFF[Un[2]];
else
   Un[2]=-UFF[-Un[2]];
if(Un[3]>=0)
   Un[3]=UFF[Un[3]];
else
   Un[3]=-UFF[-Un[3]];

temp1=UF[0]*Un[0]+UF[1]*Un[1]+UF[2]*Un[2]+UF[3]*Un[3];
temp2=UF[0]+UF[1]+UF[2]+UF[3];
U=temp1/temp2;
if(U<0)
	return -U;
else
	return U;
}




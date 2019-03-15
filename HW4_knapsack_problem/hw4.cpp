/*
   This code can be compiled and run ok.

   Input the attachment to caculate how to bring goods to get the biggest profit.
   1. Brute force
   2. Greedy algorithm

   usage (how to run):
     ./a  (then input filename)

   input file:
     n4�Bn16�Bn32 

   output files:
     none

   compile (how to compile):
     g++ -o fc hw4.cpp

   pseudocode:
      Input the given value and create arrays to record the caculation.
      Through two methods "Brute force" and "Greedy algorithm", we can find the max profit combination. 
      Use binary law to judge the good to take or not to take so that we obtain the Brute force value.
      Use bubble sort to sort the information so that we obtain the Greedy algorithm value.  
      
    
   coded by Wei-Ming Hou, group: 6, ID: h34996158, email: jacob0701@hotmail.com.tw
   date: 2011.04.17
*/

#include <iostream>
#include <math.h>
#include <ctime>
#include <fstream>
#include <cstdio>
using namespace std;
void initialize(const char *, int *, int *, double **, double **, double **, bool **, bool **, bool **, int **);
void Get_Rorder(int **, int, double **);

int main()
{
    int weight_max, n, *Rorder;
    double *w, *p, *Rpw;
    bool *x, *XB, *XG;
    char filename[50];
    cout << "Enter filename of graph: ";
    cin >> filename;

    initialize(filename, &n, &weight_max, &w, &p, &Rpw, &x, &XB, &XG, &Rorder);

    double weight_sum, profit_sum, profit_max_BF=0, profit_max_GA=0;

    //-------------------------------------------------------------

    time_t t_start, t_end; //�ܼƫŧi
    clock_t c_start, c_end;
    double t_duration, c_duration; //�O���ɶ�����
    t_start = time(NULL); //�����}�l���ɶ�
    c_start=clock();

    //--�ɤO�k-----------------------------------------------------
    int  c=1, d, i, k;  
    long long int b = static_cast<long long int>(pow(2,n)-1);  //�p��2��n�� 
    long long int a;

    for(a=1; a<=b; a++)
    {
        c=1;
        d=a;
        weight_sum=0;
        profit_sum=0;

        while(d!=0)  //2�i��k 
        {
             x[n-c]=d%2;
             d=d/2;
             c++;
        }

        for(i=0; i<n; i++)  
        {
             weight_sum += w[i] * x[i];
             profit_sum += p[i] * x[i];
        }
        
        if(weight_sum>weight_max)  //�Yture���X�j�� 
            continue;
            
        if(profit_sum > profit_max_BF)
        {
                for(i=0 ; i<n ; i++)
                XB[i]=x[i];
                profit_max_BF = profit_sum;
        }
        
    }
    
    //--�g���k-----------------------------------------------------
    weight_sum=0;
    int r;
    
    for(i=0;i<n;i++)  //�p��Q���� 
    {
         Rpw[i]=p[i]/w[i];           
    }
    
    Get_Rorder(&Rorder, n, &Rpw);
    
    for(i=0;i<n;i++)
    {
         if(weight_sum>weight_max)
            break;           
            
         weight_sum += w[Rorder[i]];
         profit_sum += p[Rorder[i]];  
            
         r=i;
    }
    for(i=0 ; i<r; i++)
       profit_max_GA+=p[Rorder[i]];
    //-------------------------------------------------------------
    cout << "------ input file: " << filename << "------" << endl;

    cout << "BF: Max Profit :  " << profit_max_BF << endl;
    cout << "    Selected items : ";
    for(int j=0; j<n; j++)
    {
        if(XB[j]==1)
        cout << j << ' ';
    }
    cout << ' ' <<endl;

    cout << "GA: Max Profit :  " << profit_max_GA << endl;
    cout << "    Selected items : ";
    for(i=0 ; i<r ; i++)
            cout << Rorder[i] << ' ';

    cout << ' ' <<endl;
    //-------------------------------------------------------------
    t_end = time(NULL); //�����������ɶ�
    c_end=clock();

    t_duration = difftime(t_end, t_start); //�p��g�L���ɶ��A���G��
    c_duration = c_end-c_start;

    cout << "    duration by time_t = " << t_duration << " (s)" <<endl
         << "    duration by clock_t = " << c_duration/CLK_TCK << " (ms)" <<endl;
    //--------------------------------------------------------------
    system("pause");
    return 0;
}

void Get_Rorder(int **Rorder,int n, double **Rpw)
{     
     int i, j; 
     double tmp=0;
     double *text=new double[n];
     
     for(i=0;i<n;i++)  //�O�@�j��H�p�� 
     {
         text[i]=(*Rpw)[i];        
     }
     
     for(i=0;i<n;i++)  //���ܦ��� 
     {
         for(j=i;j<n;j++)
         {
              if(text[i]<text[j])
              {              
                  tmp=text[i];
                  text[i]=text[j];
                  text[j]=tmp;
              }
         }                                           
     }
     
     for(i=0 ; i<n; i++)  //��J���~�s��      
     {   
         for(j=0 ; j<n; j++)
         {
            if(text[i]==(*Rpw)[j])
            {
                (*Rorder)[i]=j;
                (*Rpw)[j]=0;
                break;
            }
         }
     }
}


void initialize(const char *filename, int *n, int *weight_max, double **w, double **p, double **Rpw, bool **x, bool **XB, bool **XG, int **Rorder)
{
    int i;
    ifstream inFile(filename);
    inFile >> (*n);
    inFile >> (*weight_max);
    (*w) = new double [(*n)];
    (*p) = new double [(*n)];
    (*Rpw) = new double [(*n)];
    (*x) = new bool [(*n)];
    (*XB) = new bool [(*n)];
    (*XG) = new bool [(*n)];
    (*Rorder) = new int [(*n)];

     for(i=0; i<(*n); i++){
     inFile >> (*w)[i] >> (*p)[i];}

    inFile.close();
}

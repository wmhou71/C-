/*
   This code can be compiled and run ok.

   Use Markov Chain to calculate the probability of every state of the supplier's production.

   usage (how to run):
     ./a  (then input filename and exponent)

   input file:
     n8.txt

   output files:
     none

   compile (how to compile):
     g++ -o fc hw5.cpp

   pseudocode:
     Read file
     Calculate probability
     Transition Matrix
     multiply array


   coded by Wei-Ming Hou, group: 6, ID: h34996158, email: jacob0701@hotmail.com.tw
   date: 2011.05.03
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
void matrix_power(int &, int &, int , double **&, double **&);

int main()
{
    int  w, s=0, Q=0, *D, D_max=0;  //w為總期數，s為安全存量，Q為訂購量(補貨量)，D為需求
    double *P, **T, **TK;  //p為記算某期需求量的機率，T為轉移矩陣，Tk為計算次方用陣列
    char filename[50];  //檔名

    cout << "Please intput filename: ";
    cin >> filename;

    ifstream inFile(filename);
    int i=0, j;
    char z, str[100],title[100]; //暫存字串，title為txt上的檔名

    while(!inFile.eof())  //讀檔
    {
     inFile >> z;
     switch(z)
     {
        case 'c':
            inFile.getline(str, 100);
            break;
        case 't':
            inFile >> title;
            cout << title << endl;
            break;
        case 'w':
            inFile >> w;
            D = new int [w];
            break;
        case 's':
            inFile >> s >> Q;
            cout << "inventory strategy: inventary < " << s << " and then supply " << Q << " units" << endl;
            break;
        case 'd':
            inFile >> D[i];
            i++;
            break;
     }
    }

    T = new double *[s+Q];  //根據s+Q之值設置一個(s+Q)(s+Q)之二維轉移陣列T
    for(i=0; i<s+Q; i++){
      T[i] = new double [s+Q];}

    for(i=0; i<s+Q; i++){  //初始T陣列為0
     for(j=0; j<s+Q; j++){
        T[i][j]=0;}}

    for(i=0; i<w; i++){  //找出D陣列中最大值
      if(D[i]>D_max)
      D_max=D[i];}

    P = new double [D_max+1]; //使用P陣列來計算某期需求量q之機率
    for (i=0; i<D_max+1; i++)
        P[i]=0;

    for(i=0; i<D_max+1; i++){  //用P陣列Input機率
     for(j=0; j<w; j++){
       if(D[j]==i)
        P[i]++;}
     P[i]/=w;}

     inFile.close();

    //----------------------------------------------------------------
    //---計算轉移矩陣T------------------------------------------------
    int sum=0;

     for (i=0; i<s+Q; i++)
        for (j=0; j<s+Q; j++) {
            sum = i;
            if (i < s)
                sum+=Q;
            sum -= j;
            if(sum<0){
                T[i][j]=0;
                continue;}
            if (j == 0)
                while (sum < D_max+1)
                T[i][j] += P[sum++];
            else
                T[i][j] = P[sum];

        }


     for(i=0; i<s+Q; i++){
      for(j=0; j<s+Q; j++){
        cout << fixed << setprecision(4) << T[i][j] << ' ' ;}
        cout << endl;}

    //-----------------------------------------------------------------
    //---以轉移矩陣T之k次方計算跨k+1期之轉移機率矩陣-------------------
    int n;
    cout << "Please input exponent: ";
    cin >>n;

    matrix_power(s,Q,n,T,TK);  //呼叫matrix_power函式
    for (i=0; i<s+Q; i++){     //輸出t → t+k期的連續k+1期變換機率
        for (j=0; j<s+Q; j++){
            cout <<fixed <<setprecision(4);
            cout <<TK[i][j] <<" ";
        }
        cout <<endl;
    }
    //-------------------------------------------------------------------
    return 0;
}

void matrix_power(int &s, int &Q, int n, double **&T, double **&Tk) {
    int i, j, k;
    double **FTk;

    FTk = new double*[s+Q]; //記憶體
    Tk = new double*[s+Q];

    for (i=0; i<s+Q; i++){
        Tk[i] = new double[s+Q];
        FTk[i] = new double[s+Q];
    }
    for (i=0; i<s+Q; i++)
        for (j=0; j<s+Q; j++)
            Tk[i][j] = T[i][j];

    while(n > 1) {    //要乘n-1次
        for (i=0; i<s+Q; i++)
            for (j=0; j<s+Q; j++)
                FTk[i][j] = 0;

        for(i=0; i<s+Q; i++)
            for(j=0; j<s+Q; j++) {
                k=0;
                while(k < s+Q){
                    FTk[i][j] += Tk[i][k] * T[k][j];
                    k++;
                }
             }
        for (i=0; i<s+Q; i++)   //傳回Tk陣列
            for (j=0; j<s+Q; j++)
                Tk[i][j] = FTk[i][j];
        n--;
    }

    delete FTk;
}



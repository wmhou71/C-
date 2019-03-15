/*
   This code can be compiled and run ok.

   Ming has male larval fish and a female larval fish and prepare to let them copulate.
   Some rule as below:
	1.Every larval needs two months to become adult fish, then immediately copulates.
	2.The female adult fish will bore some larval fish, but only one female and two male can exist.
	3.After having larvel fish, the female adult fish can immediately copulate.
   Then, Ming wants to net some fish and sell them.


   usage (how to run):
     fc  (then input n and alpha)

   input file:
     none

   output files:
     none

   compile (how to compile):
     g++ -o fc hw2.cpp

   pseudocode:
     with a given n, F_SMA[t]=Sum(D[t-n]:D[t-1])/n
     with a given alpha, F_SES[t]=alpha*D[t-1]+(1-alpha)*F_SES[t-1]

   coded by Wei-Ming Hou, ID: h34996158, email: jacob0701@hotmail.com.tw
   date: 2011.03.12
*/
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int ML[31]={0},  //公仔魚數量
		FL[31]={0},  //母仔魚數量
		MY[31]={0},  //公幼魚數量
		FY[31]={0},  //母幼魚數量
		MA[31]={0},  //公成魚數量
		FA[31]={0};  //母成魚數量

	int p, k;
	int MN[31]={0},  //MN[t]表示在第t期初撈出的公魚數量
		FN[31]={0},  //FN[t]表示在第t期初撈出的母魚數量
		N_acc[31]={0};  //N_acc[t]表示累計到第t期總共撈出之成魚數量

	cout << "Please input what term Ming begins to net fish : " ;
	cin >> p ;

	cout << "Please input the sum of fish Ming thinks he can net not endangering their existence : ";
	cin >> k;

	for(int t=1;t<31;t++)  //從第p期起，每期的期初撈出(Net)母成魚k隻與公成魚2k隻出來賣，僅在缸中的母成魚超過k隻時才撈母成魚、公成魚超過2k隻時才撈公成魚。
	{
		ML[0]=FL[0]=1;

		if(t>=p && MA[t-1]>2*k && FA[t-1]>k)
		{
			MN[t]=2*k;
			FN[t]=k;
		}

		else
		{
			MN[t]=0;
			FN[t]=0;
		}

		MA[t]=(MA[t-1]-MN[t])+MY[t-1];
		MY[t]=ML[t-1];
		ML[t]=2*(FA[t-1]-FN[t]);

		FA[t]=(FA[t-1]-FN[t])+FY[t-1];
		FY[t]=FL[t-1];
		FL[t]=FA[t-1]-FN[t];

		N_acc[t]=N_acc[t-1]+MN[t]+FN[t];
	}

	cout << setw(4) << 't' << setw(8) << "ML" << setw(8) << "FL" << setw(8) << "MY" << setw(8) << "FY" << setw(8) << "MA" << setw(8) << "FA" << setw(8) << "MN" << setw(8) << "FN" << setw(8) << "N_acc" << endl;

	for(int t=0;t<31;t++)  //印出上方迴圈
	{
		ML[0]=FL[0]=1;
		cout << setw(4) << t << setw(8) << ML[t] << setw(8) << FL[t] << setw(8) << MY[t] << setw(8) << FY[t] << setw(8) << MA[t] << setw(8) << FA[t] << setw(8) << MN[t] << setw(8) << FN[t] << setw(8) << N_acc[t] << endl;
	}



	return 0;
}

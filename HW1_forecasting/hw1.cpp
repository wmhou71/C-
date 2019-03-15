/*
   This code can be compiled and run ok.

   With given historical sales records D[0],...D[9], this code calculates the
   forecasted demands F[1],...,F[10] by the following two methods:
   (1) Simple Moving Average (SMA)
   (2) Simple Exponential Smoothing (SES)

   usage (how to run):
     fc  (then input n and alpha)

   input file:
     none

   output files:
     none

   compile (how to compile):
     g++ -o fc hw1.cpp

   pseudocode:
     with a given n, F_SMA[t]=Sum(D[t-n]:D[t-1])/n
     with a given alpha, F_SES[t]=alpha*D[t-1]+(1-alpha)*F_SES[t-1]

   coded by Wei-Ming Hou, ID: h34996158, email: jacob0701@hotmail.com.tw
   date: 2011.03.02
*/
#include <iostream>
#include <iomanip>
using namespace std ;

int main()
{

    double D[11]={3,5,4,6,2,3,4,5,4,6}, F_SMA[11]={0.}, F_SES[11]={0.};

	int n=0;
	double sum=0;
	int t=2;

	cout << "Forecasted by Simple Moving Average: Please input n in [2,9]? " ;
	cin >> n;

	cout << setw(7) << "t" << setw(8) << "D[t]" << setw(9) << "F[t] " << setw(15) << "by SMA with n=" << n << endl;
	cout << setw(7) << "---" << setw(8) << "------" << setw(9) << "------ " << endl;

	for(int i=n; i<11; i++)
	{
		sum=0;

		for(int b=n; b>0; b--)
		{
			sum+=D[i-b];
		}

        F_SMA[i]=sum/n;
	}

	for(int i=0; i<11; i++)
	{
		cout << setw(7) << i << setw(8) << fixed << setprecision(2) << D[i] << setw(8) << fixed << setprecision(2) << F_SMA[i] << endl;		
	}
		cout << setw(24) << "====================" << endl;

	

    double A=0;

	cout << "Forecasted by Simple Exponential Smoothing: Please input alpha in (0,1)=? ";
	cin >> A;

	cout << setw(7) << "t" << setw(8) << "D[t]" << setw(9) << "F[t] " << setw(15) << "by SES with alpha=" << A << endl;
	cout << setw(7) << "---" << setw(8) << "------" << setw(9) << "------ " << endl;

	while(t<=10)
	{
		F_SES[1]=D[0];
		F_SES[t]=A*D[t-1]+(1-A)*F_SES[t-1];

		t++;
	}

	t=0;

	while(t<=10)
	{
		cout << setw(7) << t << setw(8) << fixed << setprecision(2) << D[t] << setw(8) << fixed << setprecision(2) << F_SES[t] << endl;

		t++;
	}

	cout << setw(24) << "====================" << endl;

    return 0 ;
}

#include <iostream>  //cout,cin
#include <fstream>   //ifstream, ofstream, printf
#include <cstdio>   //printf
#include <cstdlib>   //srand,rand
#include <time.h>     //time
#include <windows.h>   //hConsole, srand, rand

using namespace std;
void create_map();

int main()
{
    //ÀH¾÷²£¥Ímap----------------------
    create_map();
    //---------------------------------
}
void create_map(){
    int height;
    int width;
    int i,j;
    ofstream outFile("map.txt");
    srand(time(NULL));
    cout << "Enter height and width(separate by a space):";
    cin >> height >> width;

    int tmp;
    int count = 0;
    outFile << height << " " << width << endl;
    for(i=1;i<=height;i++){
        for(j=1;j<=width;j++){
            tmp = rand()%12;
            tmp = (tmp>9)?0:tmp;
            if (tmp==0) count++;
            outFile << tmp << " ";}
        outFile << endl;}
    outFile.close();
    //cout << count << endl;
    cout << "Result is saved as map.txt.";
}


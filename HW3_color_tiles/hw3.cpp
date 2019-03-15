/*
   This code can be compiled and run ok.

   Given a map of color tiles which we try to eliminate the same color tiles from the blank is the key.
   Without the same color tiles we can eliminate, the game is over.  

   usage (how to run):
     fc  (then input n and alpha)

   input file:
     map

   output files:
     none

   compile (how to compile):
     g++ -o fc hw3.cpp

   pseudocode:
     While still some tiles can be eliminated
         For each row in map
             For each column in map
                 If map[row][column] is a space, then
                    Find up neighboring tiles, and save to NT (Step1)
                    Find down neighboring tiles, and save to NT (Step1)
                    Find left neighboring tiles, and save to NT (Step1)
                    Find right neighboring tiles, and save to NT (Step1)
                    Count number of each color, and save to SUM (Step2)
                    Eliminate tiles which have duplicated color (Step2)

   coded by Wei-Ming Hou, group: 6, ID: h34996158, email: jacob0701@hotmail.com.tw 
   date: 2011.03.29
*/

#include <iostream>    //for cout, cin
#include <fstream>     //for ifstream, ofstream
#include <cstdio>      //for printf
#include <windows.h>   //for hConsole, if the operating system you use is not Windows, please comment this line

using namespace std;

//predefined function prototype
void print_map(int**,int,int);
void color_print_map(int**,int,int);  //if the operating system you use is not Windows, please comment this line

int main(){
    //read map file and store into dynamic allocation of arrays------
    ifstream inFile("map.txt");
    int map_height, map_width;
    inFile >> map_height >> map_width;
    int **map = new int*[map_height+1];
    int i,j;

    for(i = 1; i <= map_height; i++){
        map[i] = new int[map_width+1];
        for(j = 1; j <= map_width; j++)
            inFile >> map[i][j];
    }
    inFile.close();
    //---------------------------------------------------------------

    //print map------------------------------------------------------
    cout << "Origin map:" << endl;
    print_map(map, map_height, map_width);
    cout << endl;
    //---------------------------------------------------------------

    //answer section-------------------------------------------------
	int NT[4][3] = {{0},{0}};  //�έp�C�I���ʤW�U���k���y�� 
	int SUM[10] = {0};  //�έp�W�U���k���y�Ф��C�� 
	int ux=0, uy=0, dx=0, dy=0, lx=0, ly=0, rx=0, ry=0;  //�W�U���k���y�� 
    int count=0, test=0;  //�έp�`�@�Ү���tiles�M�̫����� 


    while(1)
    {          
        for(i = 1; i <= map_height; i++)  //��(1,1)�}�l�C��M��i������� 
        {
            for(j = 1; j <= map_width; j++)
            {   
              for(int u=0; u<=9; u++)  //clean
                  SUM[u]=0;
              
              if(map[i][j]==0)
              {              
                  for(ux=i, uy=j; ux > 0; ux--)  //���W�ˬd 
                  {
                      NT[0][0] = map[ux][uy];
                      NT[0][1] = ux;
                      NT[0][2] = uy;
                      SUM[map[ux][uy]]+=1;
                      
                      if(map[ux][uy]!=0)
                      break;
                  }
                  for(dx=i, dy=j; dx <= map_height; dx++)  //���U�ˬd 
                  {
                      NT[1][0] = map[dx][dy];
                      NT[1][1] = dx;
                      NT[1][2] = dy;
                      SUM[map[dx][dy]]+=1;
                      
                      if(map[dx][dy]!=0)
                      break;
                  }
                  for(lx=i, ly=j; ly > 0; ly--)  //�����ˬd 
                  {
                      NT[2][0] = map[lx][ly];
                      NT[2][1] = lx;
                      NT[2][2] = ly;
                      SUM[map[lx][ly]]+=1;
                      
                      if(map[lx][ly]!=0)
                      break;
                  }
                  for(rx=i, ry=j; ry <= map_width; ry++)  //���k�ˬd 
                  {
                      NT[3][0] = map[rx][ry];
                      NT[3][1] = rx;
                      NT[3][2] = ry;
                      SUM[map[rx][ry]]+=1;
                      
                      if(map[rx][ry]!=0)
                      break;
                  }
              }

              for(int s=1; s<=9; s++)  //�ˬdSUM���O�_���ۦP�C��X�{�⦸�H�W 
              {
                  if(SUM[s]>=2)
                  {
                      for(int t=0; t<=3; t++)  //�ˬdNT���C��O�_�ۦP 
                      {
                          if(NT[t][0]==s)
                          {
                              switch(t)  //���C��ۦP�ɡA���ܬ�0 
                              {
                                 case 0: map[ux][uy]=0;
                                      count++;
                                      break;
                                 case 1: map[dx][dy]=0;
                                      count++;
                                      break;
                                 case 2: map[lx][ly]=0;
                                      count++;
                                      break;
                                 case 3: map[rx][ry]=0;
                                      count++;
                                      break;
                              }
                          }

                      }

                  }

              }

            }
        }
        if(test==count)  //�˴��O�_�٦���������tiles 
        break;
        
        test=count;
    }

    cout << "After map:" << endl;
    print_map(map, map_height, map_width);
    
    cout << "Eliminate tiles : " << count << endl;

    //---------------------------------------------------------------
    return 0;
}
//predefined functions
void print_map(int **map, int map_height, int map_width){
    int i,j;

    for(i = 1; i <= map_height; i++){
        for(j = 1; j <= map_width; j++){
            printf("%3d",map[i][j]);}
        cout << endl;}
}
void color_print_map(int **map, int map_height, int map_width){  //if the operating system you use is not Windows, please comment this function
    int color[]={247,231,215,199,183,167,151,103,87,71,55};
    HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int i,j;

    for(i = 1; i <= map_height; i++){
        for(j = 1; j <= map_width; j++){
            SetConsoleTextAttribute(hConsole, color[map[i][j]]);
            printf("%3d",map[i][j]);
        }cout << endl;
    }SetConsoleTextAttribute(hConsole, 15);
}

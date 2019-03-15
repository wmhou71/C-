/*
   This code can be compiled and run ok.
 
   Simulate the system of bicycle's pickup and return process. 

   usage (how to run):
     ./hw7  (then input filename)

   input file:
     HW7_input.txt

   output files:
     none

   compile (how to compile):
     g++ -o hw7 hw7.cpp

   pseudocode:
     �ۦ樮���ɼ����G
     List *min;
        while( demList.next != NULL ){
            min = demList.next;
            if(D[min->index].status==0){//��F���ɯ��I�n�ɨ�
                if(���ɯ��I���ۦ樮��>0) {
                    �ɨ�(bike-- & spaces++);
                    ��smin->time (�Y�A�[�W���٨����I���M���ۦ樮�ɶ�);
                    ��min->time�j�p���JdemList���A����m;
                    D[min->index].status�אּ1;
                    if(�ӯ��I���H�����٨�){
                        ���̦������٨����H�٨�;
                    }
                } else {
                    �N���ɪ̩�쵥�ݭɨ���List��;
                }
            } else if(dmand[min->index].status==1){  //��F���ɯ��I�n�٨�
                if(���ɯ��I���Ű����W��>0){
                    �٨�(bike++ & spaces--);
                    D[min->index].status�אּ2;
                    if(�ӯ��I���H���ݭɨ�){
                        ���̦����ݭɨ����H�ɨ�;
                    }
                } else {
                    �N���ɪ̩�쵥���٨���List��;
                }
            }
        }
     
   coded by Wei-Ming Hou, group: 6, ID: h34996158, email: jacob0701@hotmail.com.tw
   date: 2011.06.12
*/
#include <iostream>
#include <fstream>
using namespace std;
struct Station{
    int bikes;//�O���ثe���ɯ��֦����ۦ樮��
    int spaces;//�O���ثe���ɯ��֦����Ŧ��
};
struct Demand{
    int time;//�ϥΪ̻ݨD�o�ͮɶ�
    int pickupSta;//�ϥΪ̯������s��
    int returnSta;//�ϥΪ��٨����s��
    int status;//�ϥΪ̯��٨����A
    int pickupWait;//�ϥΪ̯������ݮɶ�
    int returnWait;//�ϥΪ��٨����ݮɶ�
};
struct List{
    int time;//�ƥ�o�ͮɶ�
    int index;//�ϥΪ̽s��
    List *next;//�O���U�@�`�I��}
};
void readFile(char *filename, Station *&, Demand *&, int **&, int &, int &, List *&, List *&);
void timeList(List &, Demand *&, int );
void insertTime(List &, Demand *& , int );
void deleteTime(List &, int );

int main()
{
    Station *S;  //���ɯ��}�C��T
    Demand *D;  //���ɪ̰}�C��T
    int **rideTime;  //���I���M���ɶ��x�}
    int staNum;  //���ɯ��I�ӼơA�Y��N
    int demNum;  //���ɪ̭ӼơA�Y��m
    List demList;  //�������ɶ��ǦC
    List *pickupQ;  //�O���U���I���ݭɨ������ɪ�
    List *returnQ;  //�O���U���I�����٨������ɪ�
    int i=0, tmpTime, a;
    char filename[50];
    
    cout << "Please intput filename: ";
    cin >> filename;
    
    readFile(filename, S, D, rideTime, staNum, demNum, pickupQ, returnQ);
    int &N=staNum, &m=demNum, ** &T=rideTime;
    timeList(demList, D, demNum);
    //--------------------------------------------------------------------------
    //---PART 2.2 �}�l�i�����--------------------------------------------------
    List *min;
    while( demList.next != NULL ){
        min = demList.next;
        a=min->time;  //�����̫�ɶ� 
        
        if(D[min->index].status==0){            //��F���ɯ��I�n�ɨ�
            if(S[D[min->index].pickupSta].bikes>0) {
                S[D[min->index].pickupSta].bikes--;   //�ɨ�
                S[D[min->index].pickupSta].spaces++;
                  
                D[min->index].time+=T[D[min->index].pickupSta][D[min->index].returnSta];  //��smin->time (�Y�A�[�W���٨����I���M���ۦ樮�ɶ�)
                insertTime(demList, D, min->index);  //��min->time�j�p���JdemList���A����m                
                D[min->index].status=1;
                
                if(returnQ[D[min->index].pickupSta].next!=NULL){
                    //�����٨����H�٨�
                    D[returnQ[D[min->index].pickupSta].next->index].status=2;
                    S[D[returnQ[D[min->index].pickupSta].next->index].returnSta].bikes++;   
                    S[D[returnQ[D[min->index].pickupSta].next->index].returnSta].spaces--;   
                    D[returnQ[D[min->index].pickupSta].next->index].returnWait=(min->time)-D[returnQ[D[min->index].pickupSta].next->index].time;   //�k�ٵ��ݮɶ�
               
                    deleteTime(returnQ[D[min->index].pickupSta], D[returnQ[D[min->index].pickupSta].next->index].time); //��sreturnQ               
                }
                deleteTime(demList, min->time);   //��sdemList
            }
            else{
                D[min->index].time=min->time;
                insertTime(pickupQ[D[min->index].pickupSta], D, min->index);  //�N���ɪ̩�쵥�ݭɨ���List��
                deleteTime(demList, min->time);   //��sdemList
            }
        }
        else if(D[min->index].status==1){  //��F���ɯ��I�n�٨�
            if(S[D[min->index].returnSta].spaces>0){
                S[D[min->index].returnSta].bikes++;   //�٨�
                S[D[min->index].returnSta].spaces--;                
                D[min->index].status=2;
                
                if(pickupQ[D[min->index].returnSta].next!=NULL){
                //���ݭɨ����H�ɨ�
                    D[pickupQ[D[min->index].returnSta].next->index].status=1;              
                    S[D[pickupQ[D[min->index].returnSta].next->index].pickupSta].bikes--;  
                    S[D[pickupQ[D[min->index].returnSta].next->index].pickupSta].spaces++;   
                    D[pickupQ[D[min->index].returnSta].next->index].pickupWait=(min->time)-(D[pickupQ[D[min->index].returnSta].next->index].time);   //�ɨ����ݮɶ�
                
                    tmpTime=D[pickupQ[D[min->index].returnSta].next->index].time;   //�Ȧs�n�R���ɶ�
                    (D[pickupQ[D[min->index].returnSta].next->index].time)+=((D[pickupQ[D[min->index].returnSta].next->index].pickupWait)+(rideTime[D[pickupQ[D[min->index].returnSta].next->index].pickupSta][D[pickupQ[D[min->index].returnSta].next->index].returnSta]));   //�W�[���򯸤������ɶ�
                
                    insertTime(demList, D, pickupQ[D[min->index].returnSta].next->index);                
                    deleteTime(pickupQ[D[min->index].returnSta], tmpTime);   //��spickupQ
                }
                deleteTime(demList, min->time);   //��sdemList
            }
            else{
                D[min->index].time=min->time;
                insertTime(returnQ[D[min->index].returnSta], D, min->index);//�N���ɪ̩�쵥���٨���List��
                deleteTime(demList, min->time);   //��sdemList
            }
        }
    }    
    //---�p�⯲�٨����ϥήɶ� 
    for(i=0; i<m; i++){
        if(D[i].status==0)
            D[i].pickupWait=a-D[i].time;
        if(D[i].status==1)
            D[i].returnWait=a-D[i].time;
    }    
    //---�p��U���I�b�����ɤ������ݯ������٨����ݨD�䵥�ݼƥ�
    int *waitPick, *waitReturn;
    waitPick = new int[N];
    waitReturn = new int[N];
    for(i=0; i<N; i++){
        waitPick[i]=0;
        waitReturn[i]=0;
    }
    
    for(i=0; i<m; i++){
        if(D[i].status==0)
            waitPick[D[i].pickupSta]++;
        else if(D[i].status==1)
            waitReturn[D[i].returnSta]++;
    }
    //---�p�� �L���i�����ݨD�`�ƤΨ��`���ݮɶ� �P �L��i�٪��ݨD�`�ƤΨ��`���ݮɶ�
    int count1=0, count2=0, pickupWaitSum=0, returnWaitSum=0;
    for(i=0; i<m ; i++){
        if(D[i].pickupWait!=0){
            count1++;
            pickupWaitSum+=D[i].pickupWait;
        }
        if(D[i].returnWait!=0){
            count2++;
            returnWaitSum+=D[i].returnWait;
        }
    }
    //--------------------------------------------------------------------------
    //---PART3 �{�����G��X-----------------------------------------------------
    for(i=0; i<N; i++){   //�U���I���ۦ樮�ƻP�Ű�����
        cout << "station " << i << " : " << S[i].bikes << " bikes & " << S[i].spaces << " empty racks" << endl;
    } 
    cout <<endl;
    
    for(i=0; i<N; i++){   //�Y���I�b�����ɩ|�����ݯ������٨����ݨD�A�L�X�䵥�ݪ̼ƥ�    
        if(waitPick[i]!=0){
            cout << "station " << i << " : " << waitPick[i] << " customers wait for picking up bikes " << endl;
        }
        if(waitReturn[i]!=0){
            cout << "station " << i << " : " << waitReturn[i] << " customers wait for returning bikes " << endl;
        }
    }
    cout << endl;
    
    cout << count1 << " customers has experienced \"no bike to pickup\", and wait for " << pickupWaitSum << " units." << endl   //���g���L���i�����ݨD�`�ƤΨ��`���ݮɶ�
         << count2 << " customers has experienced \"no bike to pickup\", and wait for " << returnWaitSum << " units." << endl;   //���g���L��i�٤��ݨD�`�ƤΨ��`���ݮɶ�
    //--------------------------------------------------------------------------
    system("pause");
    return 0;
}

void readFile(char *filename, Station *&S, Demand *&D, int **&rideTime, int &staNum, int &demNum, List *&pickupQ, List *&returnQ)
{
    char z;
    int i=0, j=0, k=0, l=0; 
    int &N=staNum, &m=demNum, ** &T=rideTime;

    ifstream inFile(filename);

    while(!inFile.eof())                //Ū��
    {
     inFile >> z;
     switch(z)
     {
        case 'N':
            inFile >> N;
            S = new Station[N];         //�t�m�O����Ŷ�S   
            T = new int*[N];            //�t�m�O����Ŷ�T        
            for(i=0; i<N; i++){
                T[i]=new int[N];
            }
            pickupQ = new List[N];      //�t�m�O����Ŷ�pickupQ  
            returnQ = new List[N];      //�t�m�O����Ŷ�returnQ  
            for(i=0; i<N; i++){
                pickupQ[N].next=NULL;
                pickupQ[N].next=NULL;
            }
            break;
        case 'm':
            inFile >> m;
            D = new Demand[m];          //�t�m�O����Ŷ�D�P�������k0 
            for(i=0; i<m; i++){
                D[i].status=0;
                D[i].pickupWait=0;
                D[i].returnWait=0;
            }
            break;
        case 'S':
            inFile >> S[j].bikes >> S[j].spaces;
            j++;
            break;
        case 'T':
            for(i=0; i<N; i++)
                inFile >> T[k][i];
            k++;
            break;
        case 'D':
            inFile >> D[l].time >> D[l].pickupSta >> D[l].returnSta;
            l++;
            break;        
     }
    }
    inFile.close();
}
void timeList(List &demList, Demand *&D, int demNum)
{
    int i;
    int insertVal;  //�������J�ɶ��j�p
    List *tmp, *t;
    tmp=&demList;
    
    tmp->time=0;    //�q�ɶ�0�}�l�] 
    tmp->index=-1;
    tmp->next=NULL;
    
    for(i=0; i<demNum; i++){
     insertVal=D[i].time;
    
     while(tmp->next != NULL){  //�B�J�@:��X���J��m
         if(tmp->next->time > insertVal){
             break;
         }
         tmp=tmp->next;
     }
     t=new List(); //�B�J�G:���ͤ@�s�`�I
     t->time=insertVal;
     t->index=i;
     t->next=tmp->next; //�B�J�T
     tmp->next=t; //�B�J�|
     tmp=&demList; //�^���C�̪� 
    }
}
void insertTime(List &demList, Demand *& D, int insertIndex)
{
    List *tmp, *t;
    tmp=&demList;
    
    while(tmp->next != NULL){  //�B�J�@:��X���J��m
        if(tmp->next->time > D[insertIndex].time){
            break;
        }
        tmp=tmp->next;
    }
    t=new List(); //�B�J�G:���ͤ@�s�`�I
    t->time=D[insertIndex].time; //���J�`�I���ɶ�
    t->index=insertIndex; ////���J�`�I���s�� 
    t->next=tmp->next; //�B�J�T
    tmp->next=t; //�B�J�|
}
void deleteTime(List &demList, int deleteVal)
{
    List *tmp, *t;
    tmp=&demList;
    
    while(tmp->next != NULL){ //�B�J�@:��X�n�R�����I����m
        if(tmp->next->time == deleteVal){
            break;
        } 
        tmp=tmp->next;
    }
    t=tmp->next;
    tmp->next=t->next; //�B�J�G
    t->next=NULL; //�B�J�T
    delete t;
}

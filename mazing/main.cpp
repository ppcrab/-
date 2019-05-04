#include <bits/stdc++.h>
#include <unistd.h>

#include <signal.h>

using namespace std;
#define m 11//row
#define n 11
#define down 's'
#define right 'd'
#define left 'a'
#define up 'w'
vector <int> block_row;
vector <int> block_column;
vector <char> block_direct;
vector <char> way_direct;
//vector<int>::iterator it;
int number=0;
struct point{
 int x;
 int y;
 int di=0;
}start,end;
vector <point> way_point;
int x_num=1,y_num=1,re=0;
int a[100][100];
int realsize;

void init(){//����ͼȫ����1=wall
    for(int i=0;i<=m+1;i++){
      for(int j=0;j<=n+1;j++){
        a[i][j]=1;//wall
       }
     }
     a[1][1]=0;
     start.x=1;//������ʼ��
     start.y=1;
}


void st(){
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stdin, NULL, _IONBF, 0);
   //alarm(10);

}

void show(){
     for(int i=0;i<=m+1;i++){
          for(int j=0;j<=n+1;j++){
               if(i==start.x&&j==start.y){
               printf("%c%c",0xa7,0xb0 );
               }
               else if(a[i][j]==0 ){
                    printf("  ");
                    }
               else if(a[i][j]==5){
                    printf("PP");
                    }
               else if(a[i][j]==9){
                    printf("SS");
               }
               else{
                    printf("%c%c", 0xa8, 0x80);
                    }
          }
          printf("\n");
     }
}


void push_into_vec(int x,int y,int direct){//��һ�����ݴ�Ž�����vector������
 block_row.push_back(x);
 block_column.push_back(y);
 block_direct.push_back(direct);
}


int countq(){//���㵱ǰλ����Χ ǽ�ĸ���
 int cnt=0;
 if(x_num+1<=m){
  push_into_vec(x_num+1,y_num,down);
  cnt++;
 } //down
 if(y_num+1<=n){
  push_into_vec(x_num,y_num+1,right);
  cnt++;
 } //right
 if(x_num-1>=1){
  push_into_vec(x_num-1,y_num,up);
  cnt++;
 } //up
 if(y_num-1>=1){
  push_into_vec(x_num,y_num-1,left);
  cnt++;
 } //left
 return cnt;
}
int find_repeat(point p){
  for(int i =0;i<way_point.size();i++){
     if(way_point[i].x==p.x&&way_point[i].y==p.y){
         return 1;
     }
  }
}
void find_direct(int x_p,int y_p,int ending_x,int ending_y){
  point pp;
  a[x_p][y_p] = 5;
  if((x_p==ending_x&&ending_y==y_p)||re==1){
     re=1;
     if(x_p==ending_x&&ending_y==y_p){
          realsize = way_point.size();
     }
     return;
  }
  if(a[x_p+1][y_p]==0){
         pp.x = x_p+1;
         pp.y = y_p;
         pp.di++;
         way_direct.push_back(down);
         way_point.push_back(pp);
         number++;
         find_direct(x_p+1,y_p,ending_x,ending_y);
  }
  if(a[x_p][y_p+1]==0){
         pp.x = x_p;
         pp.y = y_p+1;
         pp.di++;
         way_direct.push_back(right);
         way_point.push_back(pp);

         number++;
         find_direct(x_p,y_p+1,ending_x,ending_y);

  }
  if(a[x_p-1][y_p]==0){
     if(!find_repeat(pp)){
         pp.x = x_p-1;
         pp.y = y_p;
         pp.di++;
         way_direct.push_back(up);
         way_point.push_back(pp);
         number++;
         find_direct(x_p-1,y_p,ending_x,ending_y);

     }
  }
  if(a[x_p][y_p-1]==0){
         pp.x = x_p;
         pp.y = y_p-1;
         pp.di++;
         way_direct.push_back(left);
         way_point.push_back(pp);
         number++;
         find_direct(x_p,y_p-1,ending_x,ending_y);
  }
   if((x_p==ending_x&&ending_y==y_p)||re==1){
     re=1;
     return;
   }
  if(way_point[number].di<=1){
   way_point[number].di--;
   way_point.pop_back();
   way_direct.pop_back();
   number--;
   }
   way_point[number].di--;

}

void findway(int ending_x,int ending_y){
  point start0;
  x_num = 1;
  y_num = 1;
  start0.x = 1;
  start0.y = 1;
  way_point.push_back(start0);
  find_direct(1,1,ending_x,ending_y);

}


void bisai(){
   char usr[40];
   int sai=1;
   read(0,usr,40);
   for(int i=0;i<realsize-1;i++){
     if(usr[i]!=way_direct[i]){
          sai = 0;
          break;
     }
   }
   if(sai){
     printf("true");
   }
   else{
     cout<<"?"<<endl;
   }


}


int main(){
 //st();


 init();
 int ending_x = 11,ending_y = 11;
 srand((unsigned)time(NULL));//���������
 countq();
 while(block_row.size()){//��һ��ѹ������ǽ������ұߺ�������棩����ѭ��
  int num=block_row.size();
  int randnum=rand()%num;//����0-num-1֮����������ͬʱҲ��vector����±�
  x_num=block_row[randnum];
  y_num=block_column[randnum];
  switch(block_direct[randnum]){//ѡ��һ��������к�����������ʼ�� �ڿ� Ŀ��� ����������ͬһֱ���� ����ƶ���Ŀ����λ��
   case down:{
    x_num++;
    break;
   }
   case right:{
    y_num++;
    break;
   }
   case left:{
    y_num--;
    break;
   }
   case up:{
    x_num--;
    break;
   }
  }
  if(a[x_num][y_num]==1){//Ŀ��������ǽ
   a[block_row[randnum]][block_column[randnum]]=0;//��ͨǽ
   a[x_num][y_num]=0;//��ͨĿ���
   countq();//�ٴμ��㵱ǰλ����Χ����ǽ�����������vector
  }
  block_row.erase(block_row.begin()+randnum);//ɾ�����ǽ(���ò��˵�ǽɾ�ˣ�������Щ�Ѿ�ʩ�����˲�����ʩ���ˣ�ͬʱҲ��ȷ������������ѭ��)
  block_column.erase(block_column.begin()+randnum);
  block_direct.erase(block_direct.begin()+randnum);
 }


 show();//Ϊ�˱��ڽ���������ֻ��ʾ����������
 /*for(int i=0;i<=m+1;i++){
    for(int j=0;j<=n+1;j++){
      cout<<a[i][j];
    }
    cout<<endl;
  }*/

 findway(ending_x,ending_y);
 //�˴����ٽ����Թ�·���Ĵ�ӡ

 //show();
 /*for(int i=0;i<=m+1;i++){
    for(int j=0;j<=n+1;j++){
      cout<<a[i][j];
    }
    cout<<endl;
  }*/

  for(int i=0;i<realsize;i++){
     a[way_point[i].x][way_point[i].y] = 9;

  }
  for(int i=0;i<realsize-1;i++){
     cout<<way_direct[i];

  }
  cout<<endl;
  show();
  //bisai();
 return 0;
}

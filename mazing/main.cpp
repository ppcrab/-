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

void init(){//将地图全部置1=wall
    for(int i=0;i<=m+1;i++){
      for(int j=0;j<=n+1;j++){
        a[i][j]=1;//wall
       }
     }
     a[1][1]=0;
     start.x=1;//定义起始点
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


void push_into_vec(int x,int y,int direct){//把一组数据存放进三个vector容器中
 block_row.push_back(x);
 block_column.push_back(y);
 block_direct.push_back(direct);
}


int countq(){//计算当前位置周围 墙的个数
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
 srand((unsigned)time(NULL));//随机数种子
 countq();
 while(block_row.size()){//第一步压入两堵墙（起点右边和起点下面）进入循环
  int num=block_row.size();
  int randnum=rand()%num;//生成0-num-1之间的随机数，同时也是vector里的下标
  x_num=block_row[randnum];
  y_num=block_column[randnum];
  switch(block_direct[randnum]){//选择一个方向进行后续操作，起始点 邻块 目标块 三块区域在同一直线上 随后移动到目标块的位置
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
  if(a[x_num][y_num]==1){//目标块如果是墙
   a[block_row[randnum]][block_column[randnum]]=0;//打通墙
   a[x_num][y_num]=0;//打通目标块
   countq();//再次计算当前位置周围的邻墙个数并保存进vector
  }
  block_row.erase(block_row.begin()+randnum);//删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
  block_column.erase(block_column.begin()+randnum);
  block_direct.erase(block_direct.begin()+randnum);
 }


 show();//为了便于交互，这里只显示纯数字数组
 /*for(int i=0;i<=m+1;i++){
    for(int j=0;j<=n+1;j++){
      cout<<a[i][j];
    }
    cout<<endl;
  }*/

 findway(ending_x,ending_y);
 //此处不再进行迷宫路径的打印

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

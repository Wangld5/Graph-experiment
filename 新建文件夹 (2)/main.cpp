#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
using namespace std;
typedef struct name{
	int sign;
	string Name;
}name;
vector<int> edge[100];//邻接表 
int edge2[100][100];//访问矩阵 
int edge3[100][100];//用于最短路径矩阵 
int isvisited[100];//是否被访问 
name test[100];//存储地名与标记的结构数组 
int count = 0;//计数 
//用于最短路径 
int dist[100];//路径存储 
int path[100];//存储前驱 
bool S[100];//是否访问 
int Vnum=100;//最大节点数 
int MAX=1000000;//最长路径 
//广度搜索 
void BFS_tr(int begin){
	queue<int> q;
	q.push(begin);
	isvisited[begin] = 1;
	while(!q.empty()){
		int u = q.front();
		for(int j=0; j<100; j++){
			if(u == test[j].sign) cout<<test[j].Name<<" ";
		}
		for(int i=0; i<edge[u].size(); i++){
			if(!isvisited[edge[u][i]]){
				isvisited[edge[u][i]] = 1;
				q.push(edge[u][i]);
			}
		}
		q.pop();
	}
}
//深度搜索 
void DFS_tr(int begin){
	for(int i=0; i<edge[begin].size(); i++){
		if(!isvisited[edge[begin][i]]){
			for(int k=0; k<100; k++){
				if(test[k].sign == edge[begin][i]) cout<<test[k].Name<<" ";
			}
			isvisited[edge[begin][i]]=1;
			DFS_tr(edge[begin][i]);
		}
	}
}
//构造邻接矩阵 
void matrix(int sign, string Na, int sign2, string Na2, int value){
	int flag1=0, flag2=0;
	for(int i=0;i<count;i++){
		if(test[i].Name == Na){
			flag1=1;
			break;
		}
	}
	if(flag1==0){
		test[count].sign = sign;
		test[count].Name = Na;
		count++;
	}
	for(int i=0;i<count;i++){
		if(test[i].Name == Na2){
			flag2=1;
			break;
		}
	}
	if(flag2==0){
		test[count].sign = sign2;
		test[count].Name = Na2;
		count++;
	}
	edge2[sign][sign2] = value;
	edge2[sign2][sign]=value;
	edge3[sign-1][sign2-1] = value;
	edge3[sign2-1][sign-1]=value;
}
//数组形式构造邻接表 
void list(int sign, string Na, int sign2, string Na2, int value){
	matrix(sign, Na, sign2, Na2, value);
	edge[sign].push_back(sign2);
	edge[sign2].push_back(sign);
}
//最短路径 
void Find_short(int v0){
	int n=Vnum;
	for(int i=0; i<n; i++){
		dist[i]=edge3[v0][i];//初始化源点到其他点路劲 
		S[i]=false;//初始化访问值 
		if(dist[i]>MAX) path[i]=-1;
		else path[i]=v0;
	}
	S[v0]=true;
	dist[v0]=0;
	for(int i=1; i<n; i++){
		int min=MAX;
		int v=v0;
		//找寻到相邻点最短路径 
		for(int j=0; j<n; j++){
			if(!S[j] && dist[j]<min){
				v=j;
				min=dist[j];
			}
		}
		S[v]=true;
		//对间接点最短路径查找 
		for(int k=0; k<n; k++){
			if(!S[k] && (dist[v]+edge3[v][k]<dist[k])){
				dist[k]=dist[v]+edge3[v][k];
				path[k]=v;
			}
		}
	}
}
int main(){
	cout<<"a) create an adjacency list"<<endl;
	cout<<"b) create a adjacency matrix"<<endl;
	cout<<"c) traverse with DFS"<<endl;
	cout<<"d) traverse with BFS"<<endl;
	cout<<"e) find the shortest road"<<endl;
	cout<<"f) quit the program"<<endl;
	char input = 0;
	while(1){
		cout<<"Please input your choice"<<endl;
		cin>>input;
		while(cin.fail() || (input!='a' && input!='b' && input!='c' && input!='d' && input!='e' && input!='f')){
			cin.clear();
			cin.sync();
			cout<<"please input the char"<<endl;
			cin>>input;
		}
		//其实a和b相同，一个图没必要建两次 
		if(input == 'a'){
			for(int i=0; i<100; i++){
				isvisited[i]=0;
				test[i].sign=0;
				test[i].Name="";
				edge[i].clear();
				for(int j=0; j<100; j++){
					edge2[i][j]=0;
					edge3[i][j]=MAX;
				}
			}
			count=0;
			cout<<"please input the edges number"<<endl;
			int Enum = 0;
			cin>>Enum;
			cout<<"form is sign-name-sign2-name2-edgeValue"<<endl;
			for(int i=0;i<Enum;i++){
				int sign=0, sign2=0, value=0;
				string Na="", Na2="";
				cin>>sign>>Na>>sign2>>Na2>>value;
				list(sign, Na, sign2, Na2, value);
			}
		}
		if(input == 'b'){
			for(int i=0; i<100; i++){
				isvisited[i]=0;
				test[i].sign=0;
				test[i].Name="";
				edge[i].clear();
				for(int j=0; j<100; j++){
					edge2[i][j]=0;
					edge3[i][j]=MAX; 
				}
			}
			count=0;
			cout<<"please input the edges number"<<endl;
			int Enum = 0;
			cin>>Enum;
			cout<<"form is sign-name-sign2-name2-edgeValue"<<endl;
			for(int i=0;i<Enum;i++){
				int sign=0, sign2=0, value=0;
				string Na="", Na2="";
				cin>>sign>>Na>>sign2>>Na2>>value;
				matrix(sign, Na, sign2, Na2, value);
				list(sign, Na, sign2, Na2, value);
			}
		}
		if(input == 'c'){
			cout<<test[0].Name<<" ";
			isvisited[test[0].sign]=1;
			DFS_tr(test[0].sign);
			cout<<endl;
			for(int i=0; i<100; i++){
				isvisited[i]=0;
			}
		}
		if(input == 'd'){
			BFS_tr(test[0].sign);
			cout<<endl;
			for(int i=0; i<100; i++){
				isvisited[i]=0;
			}
		}
		if(input == 'e'){
			for(int i=0; i<100; i++){
				path[i]=0;
				dist[i]=0;
			}
			cout<<"please input the short path you want to find: "<<endl;
			int v0=0, vi=0;
			cin>>v0>>vi;
			Find_short(v0-1);
			cout<<"the shortest path:"<<endl;
			cout<<dist[vi-1]<<endl;
		}
		if(input == 'f'){
			return 0;
		}
	}
}

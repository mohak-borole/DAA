#include <iostream>
using namespace std;

int main(){
	
	int i,j,u,v,w,n,e,src,p=0,m;
	cout<<"\nEnter the number of vertices : ";
	cin>>n;
	cout<<"\nEnter the source : ";
	cin>>src;
	cout<<"\nEnter the number of edges : ";
	cin>>e;
	
	int mat[n][n],edge[2*e],cost[n],prev[n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			mat[i][j]=0;
		}
	}
	
	cout<<"\n-------------- Enter edges -------------------";
	for(i=0;i<e;i++){
		cout<<"\nEnter the source : ";
		cin>>u;
		cout<<"\nEnter the destination : ";
		cin>>v;
		cout<<"\nEnter the weight : ";
		cin>>w;
		
		edge[p]=u;
		edge[p+1]=v;
		p=p+2;
		mat[u][v]=w;
	}
	cout<<"\nAdjucency Matrix for Graph is: \n";
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			cout<<mat[i][j]<<"\t";
		}
		cout<<"\n";
	}
	p=0;

	cout<<"\nSet of Edges: ";
	for(i=0;i<e;i++){
		cout<<"\t"<<"("<<edge[p]<<","<<edge[p+1]<<")";
		p=p+2;
	}
	
	for(i=0;i<n;i++){
		cost[i]=999;
	}
	cost[src]=0;
	
	
	for(i=0;i<n;i++){
		
		p=0;
		for(j=0;j<e;j++){
			u=edge[p];
			v=edge[p+1];
			p=p+2;
			
			if(cost[u]+mat[u][v]<cost[v])
			{
				cost[v]=cost[u]+mat[u][v];
			}
		}
		
		cout<<"\n Iter "<<i+1<<": ";
		for(m=0;m<n;m++){
			cout<<cost[m]<<"\t";
		}
		
		
		if(i==0){
			for(m=0;m<n;m++){
				prev[m]=cost[m];
			}
		}
		else{
			
			int flag=0;
			for(m=0;m<n;m++){
				if(cost[m]!=prev[m]){
					flag=1;
					break;
				}
			}
		
			if(flag==0){
				cout<<"\n\nAs there is no change in distance matrix, we can stop here .";
				break;
			}
			else if(i==n-1){
				cout<<"\n\nThere is dissimilarity even after n-1 cycles, hence, negative edge cycle present !";
			}
			else{
				for(m=0;m<n;m++){
					prev[m]=cost[m];
				}
			}
			
			
		}//end of else
		
	}//end of for i
	
	return 0;
	
}
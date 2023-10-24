#include<bits/stdc++.h>
using namespace std;

int arr[10][10];
int result[10];

void backTrack(int,int,int);

void back(int r,int n,int count){
	
	int pr=r-1;
	int cr=result[pr];
	
	arr[pr][cr]=0;
	result[pr]=-1;
	
	if(pr==0 && cr==n-1){
		cr=0;
	}
	else{
		cr++;
	}

	int flag=0;
	while(cr<n){
		
		for(int i=0; i<n; i++){
			
			if(result[i]==-1){
				flag=0;
				break;
			}
			
			else if(result[i]==cr){
			   flag=1;
			   break;
		    }
		
		    else if( abs(i-pr)==abs(result[i]-cr) ){
			    flag=1;
			    break;
		    }
				
		}
		if(flag==1){
			cr++;
		}
		else{
			break;
		}
	}
		
	if(cr<n){
		
		//count=count+1;
		arr[pr][cr]=count;
		result[pr]=cr;
		
		backTrack(pr,n,count);
	}
	else{
		count--;
		back(pr,n,count);
	}
	
}

void backTrack(int r,int n,int count){

	int r2=r+1;
	int c2=0;
	int flag=0;
	
	while(c2<n){
		
		for(int i=0; i<n; i++){
			
			if(result[i]==-1){
				flag=0;
				break;
			}
			
			else if(result[i]==c2){
			   flag=1;
			   break;
		    }
		
		    else if( abs(i-r2)==abs(result[i]-c2) ){
			    flag=1;
			    break;
		    }
				
		}
		if(flag==1){
			c2++;
		}
		else{
			break;
		}
	}
	
	//cout<<c2<<endl;
	
	if(c2>=n){
		
		back(r2,n,count);
	}
	else{
		
		count=count+1;
		arr[r2][c2]=count;
	    result[r2]=c2;
	    
		if(count < n){
			backTrack(r2,n,count);
		}
	    
	}
	
}

int main(){

	int r,c;
	int n;
	
	
	cout<<"Enter Number of Queens"<<endl;
	cin>>n;
	
	//cout<<"Enter Position of first Queen"<<endl;
	//cin>>r>>c;
	r=0;
	c=0;
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			arr[i][j]= 0;
			
		}
		result[i]=-1;
	
	}
	int count=1;
	
	arr[r][c]=count;
	result[r]=c;

	backTrack(r,n,count);

    cout<<"\n\n";
	for(int i=0; i<n; i++){
		
		for(int j=0; j<n; j++){
			
			cout<<arr[i][j]<<"\t";
		}
		cout<<"\n\n";
	}
	
	cout<<"\n";

	cout<<"Position of Queen's: "<<"\n";
	for(int i=0; i<n; i++){
		cout<<i<<"  ";
		cout<<result[i]<<"\n";
	}
	
	return 0;
}
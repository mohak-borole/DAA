#include <iostream>
using namespace std;

int main(){
	
	int i,j,k,n,weight,wt;
	
	cout<<"\nEnter the number of elements : ";
	cin>>n;
	cout<<"\nEnter the maximum weight : ";
	cin>>weight;
	
	int p[n],w[n];
	float pw[n],x[n],v[n];
	cout<<"\n=================X Enter data X================\n";
	for(i=0;i<n;i++){
		cout<<"\nWeight : ";
		cin>>w[i];
		cout<<"\nProfit : ";
		cin>>p[i];
		
		pw[i]=(float)p[i]/w[i];
		x[i]=0;
		v[i]=i+1;
		cout<<"\n---------------------------------------------";
	}
	cout<<"\n";
	int bag=0;
	float tp=0,tw=0;
	float mat[n+1][weight+1];
	
	int ch;
	do{
		cout<<"\n\nEnter Your Choice :\n\n \t\t1.Greedy/Fractional\t\t2.Dynamic/0-1\n\n\t\t-->\t";
		cin>>ch;
		switch(ch){
			case 1:{
				
				for(i=0;i<n;i++){
					for(j=i+1;j<n;j++){
						if(pw[i]<pw[j]){
							float temp;
							int t;
							temp=pw[i];
							pw[i]=pw[j];
							pw[j]=temp;
							
							temp=v[i];
							v[i]=v[j];
							v[j]=temp;
							
							t=p[i];
							p[i]=p[j];
							p[j]=t;
							
							t=w[i];
							w[i]=w[j];
							w[j]=t;
							
						}
					}
				}//sorting done
				i=0;
				while(bag<weight){
					if(bag+w[i]<weight){
						x[i]=1;
						bag=bag+w[i];
					}
					else{
						x[i]=(float)(weight-bag)/w[i];
						bag=weight;
					}
					i++;	
				
				}


				for(i=0;i<n;i++){
					for(j=i+1;j<n;j++){
						if(v[i]>v[j]){
							float temp;
							int t;
							temp=pw[i];
							pw[i]=pw[j];
							pw[j]=temp;
							
							temp=v[i];
							v[i]=v[j];
							v[j]=temp;
							
							t=p[i];
							p[i]=p[j];
							p[j]=t;
							
							t=w[i];
							w[i]=w[j];
							w[j]=t;
							
							temp=x[i];
							x[i]=x[j];
							x[j]=temp;							
						}
					}
				}//resorting done
				
				cout<<"\nElement : Fraction\n";
				for(i=0;i<n;i++){
					cout<<v[i]<<"  :  "<<x[i]<<"\n";
				}
				for(i=0;i<n;i++){
					tp=tp+p[i]*x[i];
					tw=tw+w[i]*x[i];
				}
				
				cout<<"\nTotal Profit : "<<tp;
				cout<<"\nTotal Weight : "<<tw;
				
				break;
			}
			case 2:{
				
				for(i=0;i<n;i++){
					x[i]=0;
				}
				
				for(i=0;i<n+1;i++){
					for(j=0;j<weight+1;j++){
						mat[i][0]=0;
						mat[0][j]=0;
					}
				}
				
				for(j=1;j<n+1;j++){
					for(k=1;k<weight+1;k++){
						if(k<w[j-1]){
							mat[j][k]=mat[j-1][k];
						}
						else if(k>=w[j-1]){
							mat[j][k]=max(mat[j-1][k],p[j-1]+mat[j-1][k-w[j-1]]);
						}
					}
				}
				
				
				
				for(i=0;i<n+1;i++){
				    cout<<"\n";
					for(j=0;j<weight+1;j++){
						cout<<mat[i][j]<<"\t";
					}
					cout<<"\n";
				}
				
				i=n;
				wt=weight;
				while(i>0 && wt>0){
					if(mat[i][wt]!=mat[i-1][wt]){
						i--;
						x[i]=1;
						wt=wt-w[i];
					}
					else{
						i--;
					}
				}
				
				cout<<"\n-------------------------------------------------------------------";
				cout<<"\nProfit : ";
				for(i=0;i<n;i++){
					cout<<p[i]<<"\t";
				}
				cout<<"\nWeight : ";
				for(i=0;i<n;i++){
					cout<<w[i]<<"\t";
				}
				cout<<"\nX[]    : ";
				for(i=0;i<n;i++){
					cout<<x[i]<<"\t";
				}
				
				cout<<"\nMaximum profit is : "<<mat[n][weight];
				
				
				break;
			}
			case 3:{
				cout<<"\n\t\tProgram exit!";
				exit(0);
				break;
			}
			default:{
				cout<<"\n\t\tWrong option !";
				break;
			}
		}//end of switch
		
		cout<<"\n-------------------------------------------------------------------";

	}while(ch!=3);
	
	return 0;
}
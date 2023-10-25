#include<iostream>
#include<math.h>
using namespace std;

struct process{
    int profit , weight;
    float pwRatio;
};

class operations
{
    private:
        int capacity , size = 0;
        float choosen[20];
        process arr[20];
    public:
        process* getdata();
        process* bubblesort(process arr[]);
        void swap(process* a , process* b);
        void knapsack_greedy();
        void knapsack_dynamic();
};

void operations::swap(process* a , process* b)
{
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

process* operations::bubblesort(process arr[])
{
    int i, j;
    bool swapped;
    for (i = 0; i < size - 1; i++) 
    {
        swapped = false;
        for (j = 0; j < size - i - 1; j++) 
        {
            if (arr[j].pwRatio > arr[j + 1].pwRatio) 
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }

    cout<<"\n";
    for(int i = 0 ; i < size ; i++)
	{
		printf("%d\t%d\t%d\t%f\n" , (i+1) , arr[i].weight , arr[i].profit , arr[i].pwRatio);
	}
    return arr;
}

process* operations::getdata()
{
	cout<<"Enter the number of elements you want to enter: ";
	cin>>size;
    cout<<"Enter the maximum capacity of bag: ";
    cin>>capacity;
	for(int i = 0 ; i < size ; i++)
	{
		printf("Enter %d element's weight: ", i+1);
		cin>>arr[i].weight;
		printf("Enter %d element's profit: ", i+1);
		cin>>arr[i].profit;
		arr[i].pwRatio = ((float)(arr[i].profit) / (float)(arr[i].weight));
	}
	
	for(int i = 0 ; i < size ; i++)
	{
		printf("%d\t%d\t%d\t%f\n" , (i+1) , arr[i].weight , arr[i].profit , arr[i].pwRatio);
	}
	return arr;
}

void operations::knapsack_greedy()
{
    process* array;
    array = bubblesort(getdata());

    for (int i = 0 ; i < (int)(sizeof(choosen)/sizeof(choosen[0])) ; i++)
        choosen[i] = 0;

    int i = 0 , current_profit = 0;
    while(capacity > 0)
    {
        if(array[i].weight <= capacity)
        {
            capacity = capacity - array[i].weight;
            current_profit = current_profit + array[i].profit;
            choosen[i] = 1;
        }
        else
        {
            float fraction = ((float)(capacity)/(float)(array[i].weight));
            capacity = capacity - (array[i].weight * fraction);
            current_profit = current_profit + (array[i].profit * fraction);
            choosen[i] = fraction;
        }
        i++;
    }

    cout<<"The Selected elements are:\n";
    for (int i = 0 ; i < size ; i++)
        cout<<i+1<<"\t"<<choosen[i]<<"\n";

    cout<<"The current profit is: "<<current_profit;
}

void operations::knapsack_dynamic()
{
    process* items;
    items = getdata();

    for(int i = 0 ; i < size ; i++)
        choosen[i] = 0;

    float matrix[size+1][capacity + 1];

     int dp[size + 1][capacity + 1];

    for (int i = 0; i <= size; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].profit + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    for (int i = 0 ; i < size+1 ; i++)
    {
        for(int j = 0 ; j < capacity+1 ; j++)
        {
            cout<<dp[i][j]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"the maximum profit that can be obtained is: "<<dp[size][capacity]<<"\n";

}

int main()
{
    operations opr;
    int choice;
    cout<<"Implement\n1.Fractional Knapsack\n2.1/0 Knapsack\nEnter your choice: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
            opr.knapsack_greedy();
            break;
        case 2:
            opr.knapsack_dynamic();
            break;
        default:
            cout<<"Invalid Input";
            break;
    }
    return 0;
}
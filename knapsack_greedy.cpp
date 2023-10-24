#include<iostream>
using namespace std;

struct element
{
	int weight;
	int profit;
	float pwratio;
};

/*--------------------------------------------------------------------*/

class operations
{
	private:
		int capacity = 15 , size;
		float selected[20];
		element arr[20];
	public:
		void swap(element* a , element* b);
		element* getdata();
		element* bubbleSort(element arr[]);
		void knapsack_greedy();
};

element* operations::getdata()
{
	cout<<"Enter the number of elements you want to enter: ";
	cin>>size;
	for(int i = 0 ; i < size ; i++)
	{
		printf("Enter %d element's weight: ", i+1);
		cin>>arr[i].weight;
		printf("Enter %d element's profit: ", i+1);
		cin>>arr[i].profit;
		arr[i].pwratio = ((float)(arr[i].profit) / (float)(arr[i].weight));
	}
	
	for(int i = 0 ; i < size ; i++)
	{
		printf("%d\t%d\t%d\t%f\n" , (i+1) , arr[i].weight , arr[i].profit , arr[i].pwratio);
	}
	return arr;
}

void operations::knapsack_greedy()
{
	element* array;
	array = bubbleSort(getdata());
	for(int i = 0 ; i < (sizeof(selected) / sizeof(selected[0])) ; i++)
	{
		selected[i] = 0; 
	}
	
	int current_value = 0 , i = 0;
	while(capacity > 0)
	{
		if(array[i].weight <= capacity)
		{
			capacity -= array[i].weight;
			current_value += array[i].profit;
			selected[i] = 1;
		}
		else
		{
			current_value += (array[i].profit * ((double)capacity/(double)array[i].weight));
			selected[i] = ((double)capacity/(double)array[i].weight);
			break;
		}
		i++;
	}
	
	for(int i = 0 ; i < size ; i++)
	{
		printf("%f\t", selected[i]);
	}
}

void operations::swap(element* a , element* b)
{
	struct element temp = *a;
    *a = *b;
    *b = temp;
}

element* operations::bubbleSort(element arr[])
{
    int i, j;
    bool swapped;
    for (i = 0; i < size - 1; i++) 
    {
        swapped = false;
        for (j = 0; j < size - i - 1; j++) 
        {
            if (arr[j].pwratio > arr[j + 1].pwratio) 
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
    
    for(int i = 0 ; i < size ; i++)
	{
		printf("\n\n%d\t%d\t%d\t%f\n" , (i+1) , arr[i].weight , arr[i].profit , arr[i].pwratio);
	}
	return arr;
}

/*--------------------------------------------------------------------------------*/

int main()
{
	operations opr;
	opr.knapsack_greedy();
	
	return 0;
}

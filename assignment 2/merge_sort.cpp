#include <iostream>

using namespace std;

void merge(int arr[], int l, int m, int r)//m = l + (r - l) / 2;
{
	int i, j, k;  //if number of entered numbers size = 7 '0'>'6' index
	int n1 = m - l + 1;// First subarray is arr[l..m]  size = 4 '0'>'3' index
	int n2 = r - m;// Second subarray is arr[m+1..r]   size = 3 '4'>'6' index
	int *L=new int[n1], *R=new int[n2];

	//2 temp array
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = j = 0;
	k = l;

	//put values into sorted into merged array
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

    // Copy the remaining elements of
	// right[], if there are any
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(int arr[], int l, int r)
//checks if the sub-array has at least two elements (l < r)
{
	if (l < r)
	{
	    //computes the middle index m of the sub-array
		int m = l + (r - l) / 2;
        //recursively calls mergeSort() on the left half of the sub-array and on the right half
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		//when the two halves are sorted, the merge() function is called to merge the two sorted halves into a single sorted array
		merge(arr, l, m, r);
	}
}



void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout<<endl;
}

void arrayMedian(int arr[], int n)
{
    if(n%2==0){
        float median= ((arr[n/2])+ (arr[(n/2)-1]))/2.0;
        cout<<"Median is "<< median;
    }
    else{
        cout<<"Median is "<< arr[n/2];
    }
}

int main()
{

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int* arr = new int[n];
    int arr_size = n;
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> *(arr + i);
    }


	cout << "Given array is "<<endl;
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	cout << "Sorted array is "<<endl;
	printArray(arr, arr_size);

	arrayMedian(arr, arr_size);

	delete [] arr;

	return 0;

	}


// Course: Algorithm
// project5
// Author: Kai Qi
//
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

int *randomArray(int size, int max)
{
    int *arrBuffer = new int[max];
    int i;
    
    for(i = 0; i < max; ++i)
        arrBuffer[i] = i;
    
    for(i = 0; i < max; i++)
        swap(arrBuffer[i], arrBuffer[rand()%max + 1]);
    
    int *arr = new int [size];
    for (i = 0; i < size; ++i)
        arr[i]  = arrBuffer[i];
    
    delete [] arrBuffer;
    return arr;
}

int partition (int *arr, int start, int end)
{
    int i = start + 1;
    int piv = arr[start];

    for (int j = start +1; j <= end; j++)
    {
        if (arr[j] < piv)
        {
            swap (arr[i], arr[j]);
            i = i + 1;
        }
    }
    swap (arr[start], arr[i-1]);
    return i-1;
}

void quickSort(int *arr, int start, int end)
{
    if(start < end)
    {
        int pivPosition = partition(arr, start, end);
        quickSort(arr, start, pivPosition - 1);
        quickSort(arr, pivPosition + 1, end);
    }
}

int binarySearch(int *arr, int num, int target)
{
    int first = 0,
        last = num -1,
    middle;
        //position = -1;
    //bool found = false;
    
    while(first <= last )//&& !found
    {
        middle = (first + last)/2;
        
        if (arr[middle] == target)
        {
            //found = true;
            //position = middle;
            return middle;
        }
        else if (target < arr[middle])
            last = middle - 1;
        else
            first = middle + 1;
    }
    //return position;
    return -1;
}

int linerSearch(int *arr, int num, int target)
{
    int position = -1;
    bool found = false;
    
    for (int i = 0; i < num && !found ; i++)
    {
        if (arr[i] == target)
        {
            found = true;
            position = i;
        }
    }
    return position;
}


int main(int argc, const char * argv[])
{
    
    cout << "Please input three integers m,n,k which meet m ≤ n ≤ k, m is the number of elements in table1, n is the number of elements in table2. " << endl;
    
    int m,n,k;
    cin >> m;
    cin >> n;
    cin >> k;
    
    // generate two tables randomly
    srand((unsigned)time(NULL));
    int *arr_sample_m = randomArray(m,k);
    int *arr_sample_n = randomArray(n,k);
    
    // duplicate the two randonly gererated tables which will be sorted using quicksort
    int *arrM = new int[m];
    for (int i =0; i < m; i++)
        arrM[i] = arr_sample_m[i];
    
    int *arrN = new int[n];
    for (int i =0; i < n; i++)
        arrN[i] = arr_sample_n[i];

    // sort the smaller table, and record the time consuming
    clock_t Begin_quicksortM, End_quicksortM;
    double duration_quicksortM;
    Begin_quicksortM = clock();
    
    // sort the smaller table
    quickSort(arrM, 0, m-1);
    
    End_quicksortM = clock();
    duration_quicksortM = double (End_quicksortM - Begin_quicksortM)/CLK_TCK;
    
    // sort the larger table, and record the time consuming
    clock_t Begin_quicksortN, End_quicksortN;
    double duration_quicksortN;
    Begin_quicksortN = clock();
    
    //sort the larger table
    quickSort(arrN, 0, n-1);
    
    End_quicksortN = clock();
    duration_quicksortN = double (End_quicksortN - Begin_quicksortN)/CLK_TCK;
    
    // ****************************************************************
    // *Method1:Sort both tables and then use a merge-like intersection.
    // ****************************************************************
    
    // variables for recording time consuming
    clock_t Begin, End;
    double duration;
     
    vector<int> intersectResult1;
    cout << "Method 1: Sort both tables and then use a merge-like intersection: " << endl;
    
    Begin = clock();
    if (m == 0 || n == 0)
        cout << "At least one of the table is empty." << endl;
    
    int i= 0, j =0;
    while(i < m && j <n)
    {
        if (arrM[i] == arrN[j])
        {
            intersectResult1.push_back(arrM[i]);
            i++;
            j++;
        }
        else if (arrM[i] < arrN[j])
            i++;
        else
            j++;
    }
    
    if (intersectResult1.size() == 0)
        cout << "There is no intersection of the two tables." << endl;
    else
    {
        cout << "The intersection is: ";
        for (int i = 0; i < intersectResult1.size(); i++)
            cout << intersectResult1[i] << " ";
        cout << endl;
    }
    End = clock();
    
    duration = double (End - Begin)/CLK_TCK + duration_quicksortM + duration_quicksortN;
    cout << "Time Duration is " << duration << endl << endl;
    
    
    // ****************************************************************
    // * Method2:Sort the larger table and then use binary search on the
    // * resulting table for each value in the smaller table
    // ****************************************************************
    
    vector<int> intersectResult2;
    cout << "Method 2: Sort the larger table and then use binary search on the resulting table for each value in the smaller table: " << endl;
    
    Begin = clock();
    if (m == 0 || n == 0)
        cout << "At least one of the table is empty." << endl;
    
    for (int i = 0; i < m; i++)
       {
           if (binarySearch(arrN, n, arrM[i]) != -1)
               intersectResult2.push_back(arrM[i]);
       }
    
    if (intersectResult2.size() == 0)
        cout << "There is no intersection of the two tables." << endl;
    else
    {
        cout << "The intersection is: ";
        for (int i = 0; i < intersectResult2.size(); i++)
            cout << intersectResult2[i] << " ";
        cout << endl;
    }
    End = clock();
    
    duration = double (End - Begin)/CLK_TCK + duration_quicksortN;
    cout << "Time Duration is " << duration << endl << endl;
    
    
    // ****************************************************************
    // * Method3: Sort the smaller table and then use binary search on the
    // * resulting table for each value in the larger table
    // ****************************************************************
    
    vector<int> intersectResult3;
    cout << "Method 3: Sort the smaller table and then use binary search on the resulting table for each value in the larger table: " << endl;
    
    Begin = clock();
    if (m == 0 || n == 0)
        cout << "At least one of the table is empty." << endl;
   
    int return_index;
    for (int i = 0; i < n; i++)
    {
        return_index = binarySearch(arrM, m, arrN[i]);
        if (return_index != -1)
            intersectResult3.push_back(arrN[i]);
    }
    
    if (intersectResult3.size() == 0)
        cout << "There is no intersection of the two tables." << endl;
    else
    {
        cout << "The intersection is: ";
        for (int i = 0; i < intersectResult3.size(); i++)
            cout << intersectResult3[i] << " ";
        cout << endl;
    }
    End = clock();
    
    duration = double (End - Begin)/CLK_TCK + duration_quicksortM;
    cout << "Time Duration is " << duration << endl << endl;
    
    // **********************************************************************
    // * Method4: Search the larger table for each value in the smaller table.
    // **********************************************************************
    
    vector<int> intersectResult4;
    cout << "Method 4: Search the larger table for each value in the smaller table.: " << endl;
    
    Begin = clock();
    if (m == 0 || n == 0)
        cout << "At least one of the table is empty." << endl;
    
    for (int i = 0; i < m; i++)
       {
           if (linerSearch(arr_sample_n, n, arr_sample_m[i]) != -1)
               intersectResult4.push_back(arr_sample_m[i]);
       }
    
    if (intersectResult4.size() == 0)
        cout << "There is no intersection of the two tables." << endl;
    else
    {
        cout << "The intersection is: ";
        sort(intersectResult4.begin(), intersectResult4.end());
        for (int i = 0; i < intersectResult4.size(); i++)
            cout << intersectResult4[i] << " ";
        cout << endl;
    }
    End = clock();
    
    duration = double (End - Begin)/CLK_TCK;
    cout << "Time Duration is " << duration << endl << endl;
    
    
    delete [] arrM;
    delete [] arrN;
    
    return 0;
}


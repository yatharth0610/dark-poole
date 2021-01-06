#include <iostream>

using namespace std;

const int MAX = 3*(1e4 + 7); // Setting a global variable for maximum limit of stack.

// Implementing the class Stack which allows basic operations like push, pop, IsEmpty and top.
class Stack {

public:
    int tp; // Variable which will point to the top of stack
    int arr[MAX]; // Array which will store the elements of stack with limit 3*MAX 
    
    // Constructor function for initialising the top of stack
    Stack () {
        tp = -1; // Since there is no element initially so we choose an arbitrary negative value for the top.
    }
    
    // Implementing the function that pushes an integer into the stack
    int push (int x) {
        // If the stack is full, return 1
        if (tp == MAX-1) {
            return 1;
        }
        // Else increase the value of top of stack and push the value at that position and return 0
        else {
            arr[tp+1] = x;
            tp++;
            return 0;
        }
    }

    // Implementing the function that pops the element from the top of the stack and returns it
    int pop() {
        // If the stack is empty return 0
        if (tp < 0) {
            return 0;
        }
        // Else fetch the element pointed by the tp variable and reduce tp by 1 and return the value
        else {
            int x = arr[tp];
            tp--;
            return x;
        }
    }

    // Implementing the function that returns if the stack is empty or not based on the value of tp variable
    int isEmpty() {
        return (tp < 0) ? 1 : 0;
    }

    // Implementing the function that returns the value at the top of the stack without popping it from the stack
    int top() {
        return arr[tp];
    }
};

/* Function that takes in an array and a range [l, r] containing two sorted subarrays paritioned at mid and merges the two sorted arrays and returns the count of inversions present in concatenation of these two sorted arrays */

void merge(int *v, int l, int r) {
    int sorted[r-l+1]; // Temporary Array to store the sorted range [l,r]

    int i = l;// Initialising the iterator for the first array v[l, mid]
    int mid = l+(r-l)/2; // Variable to store where the array is partitioned at
    int j = mid+1; // Initialising the iterator for the second array v[mid+1, r]
    int k = 0; // Initialising the iterator for the dummy array that will store the sorted merged array
    
    /* Iterating over the two arrays under the condition that the iterators of the two arrays remain less than the length of the total array */ 
    while ((i <= mid) && (j <= r)) {
        
        /* Putting smaller of the two current elements into the temporary sorted array and increasing the inversion count only if second element is less than the first element */
        if (v[i] <= v[j]) {
            sorted[k] = v[i];
            k++;
            i++;
        }
        else {
            sorted[k] = v[j];
            k++;
            j++;
        }
    }

    /* Iterating over the remaining of the array containing more elements (either i == mid+1 or j == r+1 by now) and remaining elements are the ones that are greater than any other element already inserted so we insert the rest directly. */ 
    while (i <= mid) {
        sorted[k] = v[i];
        k++;
        i++;
    }

    while (j <= r) {
        sorted[k] = v[j];
        k++;
        j++;
    }

    /* Copying elements of the dummy sorted array into the original array so that it now becomes sorted as well */
    for (int i = l; i <= r; i++) {
        v[i] = sorted[i-l];
    }
}

/* Function to perform non-recursive merge-sort using stacks, takes in an array and length of that array and sorts it
 * stores the ranges by pushing them as 3 values in the stack, a boolean to tell if it is ready to be merger, start of
 * the range and end of the range */

void mergeSort(int *v, int n) {
    /* Iniatialising the stack with the range [0,n-1] and setting the value of boolean to 0 which means not ready to be
       sorted */
    class Stack s;
    s.push(0);
    s.push(0);
    s.push(n-1);

    // Iterating over the ranges in stack while it is not empty
    while (!s.isEmpty()) {
        
        // Popping the range on the top of stack
        int x = s.pop();
        int y = s.pop();
        int z = s.pop();
        
        // If the range is ready to be merged (both it's half arrays have been sorted)
        if (z == 1) {
            merge(v, y, x);
        }

        // If the range is not ready to be sorted then divide it into two halfs and push them into stack
        else {
            // Checking if start of the range is less than end of the range
            if (y < x) {

                int mid = (x+y)/2; // Variable to store the middle of the range
                
                // Putting the ranges that are to be pushed next into an array
                int a[3][3] = {{1, y, x}, {0, y, mid}, {0, mid+1, x}}; 
                
                // Iterating over the values of array and pushing these ranges into the stack
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        s.push(a[i][j]);
                    }
                }

            }

        }
    }
}

int main(){
    int t; // Variable to store the number of arrays to be sorted
    cin >> t; // Taking in the input from STDIN
    
    // Iterating over the number of test cases
    while (t--) {
        int n; // Variable to store the number of elements in array
        cin >> n; // Taking in the value from STDIN
        int arr[n]; // Array that needs to be sorted

        // Taking the elements of array from STDIN
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        // Passing array to mergeSort function for sorting
        mergeSort(arr, n);

        // Printing the array to STDOUT
        for (int i = 0; i < n; i++) {
            cout << arr[i] << ' ';
        }

    }

    return 0;
}



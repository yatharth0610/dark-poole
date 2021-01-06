#include <iostream>

using namespace std;


/* Function that takes in an array and a range [l, r] containing two sorted subarrays paritioned at mid and merges the two sorted arrays and returns the count of inversions present in concatenation of these two sorted arrays */

long long merge(int *v, int *sorted, int l, int mid, int r) {
    long long count = 0; // Variable to store the count of inversions present in the array in range [l, r]

    int i = l; // Initialising the iterator for the first array v[l, mid]
    int j = mid+1; // Initialising the iterator for the second array v[mid+1, r]
    int k = l; // Initialising the iterator for the dummy array that will store the sorted merged array
    
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
            count += mid-i+1; /* mid-i+1 represents the number of elements in the first array (v[l, mid]) to the right of ith element including it since all of these would add to the count of inversion pairs with v[j] being the smaller one*/
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
        v[i] = sorted[i];
    }

    return count; // Returning the count of inversions in the end 
}

/* Function that takes in an array and a certain range [l,r], sorts the array in this range and also returns the number of inversions present in that range in the original array */

long long merge_sort(int *v, int *sorted, int l, int r) {
    long long count = 0; // Variable to store the count of inversions present in A[l, r] initialised to zero
    
    /* We want to perform the function only when l > r as in the other case the subarray would be trivially sorted and hence we can return from the function with count = 0 as the number of inversions*/

    if (l < r) { 
        // Now we perform the divide and conquer approach on the initial array by dividing it at middle.
        int mid = l + (r-l)/2; // Variable to store the partition index for divide and conquer

        // Calculating the number of inversions present in the two half-arrays
        count += merge_sort(v, sorted, l, mid); 
        count += merge_sort(v, sorted, mid+1, r);

        // Calculating the number of inversions present between the two half-arrays
        count += merge(v, sorted, l, mid, r);
    }
    return count;
}


/* Function to count the number of inversions in an array present, sort the array and return the number, takes in the array and number of elements in array as input */

long long count_inversions(int *v, int n) {
    long long ans = 0; // Initialising a variable to store the count of inversions
    int sorted[n]; // Defining a temporary array to store the sorted state of the original array
    
    for (int i = 0; i < n; i++) {
        sorted[i] = 0; // Initialise the temporary array with all zeros
    }
    
    /* Calling merge_sort function on the original array that will sort and return the count of inversions */
    ans = merge_sort(v, sorted, 0, n-1); 
    return ans;
}

int main(){
    int t; // Variable to store the number of test cases 
    cin >> t; // Taking in number of Test Cases from STDIN
    
    // Iterating over the number of test cases
    while (t--) {
        int n; // Variable to store the number of elements in an array
        cin >> n; // Taking in number of elements in the array from STDIN
        
        int v[n]; // Input Array for which we have to count the number of inversions
        for (int i = 0; i < n; i++) {
            cin >> v[i]; // Taking in elements of the array from STDIN
        }
        
        /* Calling the function to calculate number of inversions in array and storing it in a variable */
        long long ans = count_inversions(v, n);  
        cout << ans << endl; // Writing the final answer to STDOUT
    }

    return 0;
}



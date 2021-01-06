#include <iostream>
#include<ctime>
#include<chrono>
#include<iomanip>

using namespace std;

#define ll long long int 
const ll MOD = 1e9 + 7;

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto start = chrono::high_resolution_clock::now(); 
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; // Variables used to store the number of words and maximum number of chars a line can hold
    cin >> n >> m; // Taking in input from STDIN
    
    char word[n][82]; // Array used to store the 'n' words each of length at max 80
    ll word_len[n], prefix_sum[n+1]; // Arrays used to store length of each word and sum of lengths from [1..i] 
    
    for (int i = 0; i < n; i++) {
        cin >> word_len[i] >> word[i];
        // Filling in the prefix_sum array 
        if (i > 0) prefix_sum[i] = prefix_sum[i-1] + word_len[i]; 
        else prefix_sum[i] = word_len[i];
    }
    
    // Arrays used for storing cost of filling in the words from [i..n-1] (cost) and the last word of the first line in the        optimal solution for [i..n-1] (last).
    ll cost[n+1], last[n+1]; 
    for (int i = n-1; i >= 0; i--) {
        
        // If all the words from [i..n-1] can be accomodated in a single line
        if (i > 0 && prefix_sum[n-1] - prefix_sum[i-1] + (n-i-1) <= m) {
            cost[i] = 0;
            last[i] = n-1;
            continue;
        }
        
        else if (prefix_sum[n-1] + n-1 <= m) {
            cost[i] = 0;
            last[i] = n-1;
            continue;
        }
        
        // Else find the optimal cost by iterating over all j from [0..n-i] and building the solutions in a bottom up               fashion
        ll curr_min = 1e10;
        for (int j = 0; j < min(n-i, m); j++) {
            ll temp;
            if (i > 0) temp = m - (prefix_sum[i+j] - prefix_sum[i-1] + j);
            else temp = m - (prefix_sum[i+j] + j);
            if (temp >= 0 && temp*temp*temp + cost[i+j+1] < curr_min) {
                curr_min = temp*temp*temp + cost[i+j+1];
                last[i] = i+j;
            }
        }
        
        cost[i] = curr_min;
    }
    
    // Printing the final answer by using the last word of the first line of [0..n-1], then the last word of                    [last[0]..n-1] and so on.
    int end = last[0], prev = -1;
    
    while (prev != n-1) {
        for (int i = prev+1; i <= end; i++) {
            cout << word[i] << ' ';
        }
        cout << endl;
        prev = end;
        end = last[end+1];
    }
    
    cout << cost[0]%MOD << endl; // Printing the answer%(10^9 + 7) to STDOUT
    auto tend = chrono::high_resolution_clock::now(); 
    double time_taken =  chrono::duration_cast<chrono::nanoseconds>(tend - start).count(); time_taken *= 1e-9; 
    cout << "\nTime taken by program is : " << fixed << time_taken << setprecision(9); cout << " sec" << endl; 
    return 0;
}

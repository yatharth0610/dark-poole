#include<vector>
#include<iostream>
#include<ctime>
#include<chrono>
#include<iomanip>
using namespace std;
const int SIZE  = 1e5+5;
long long int N = 1e9 + 7;
long long int Z = 998244353;
long long int INF = 1e7;

#define ll long long int
long long int dp[SIZE][2];
int wordlength[SIZE];
int prefsum[SIZE];
int M = 0;
void precompute(){
    INF = INF * 1e7;
    for(int i = 0; i<SIZE; i++){
        dp[i][0] = INF;
        dp[i][1] = -1;
    }
}
int max3(int x, int y, int z){
    return max(x, max(y,z));
}
int lengthsum(int a, int b){
    if(a == 0){
        return prefsum[b];
    }
    else{
        return prefsum[b] - prefsum[a-1];
    }
}
//Top - Down Approach.
long long int resolvedp(int i, int j){
    if(i>j){
        return 0;
    }
    if(i==j){
        return 0;
        ll z = M - wordlength[i-1];
        z = z*z*z;
        return z%N;
    }
    if(dp[i][0] != INF){
        return dp[i][0];
    }
    else{
        for(int k = i+1; k<=j+1; k++){
            //cout<<M;
            long long int z = M - lengthsum(i, k-1) - (k-1 - i);
            if(z<0){
                break;
            }
            long long int kj = resolvedp(k, j);
            if(k== (j + 1)){
                dp[i][0] = 0;
                dp[i][1] = k;
            }
            else if(z*z*z + kj < dp[i][0]){
                if(k == j){
                    dp[i][0] = (z*z*z);
                    dp[i][1] = k;
                }
                else{
                    dp[i][0] = (z*z*z + kj);
                    dp[i][1] = k;
                }
            }
        }
        dp[i][0] = dp[i][0]%N;
        return dp[i][0];
        // do recursive step here.
    }
    return 0;
}
void printdp(int n){
    for(int i = 1; i<n+2; i++){
        if(dp[i][0] == INF){
            cout<<"INF -1 ** ";
            continue;
        }
        cout<<dp[i][0]<<" "<<dp[i][1]<<" ** ";
    }
    cout<<"\n";
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto start = chrono::high_resolution_clock::now(); 

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t=1; 
    //cin>>t;
    precompute();
    while(t--){
        int n, l;
        cin>>n;
        cin>>M;
        if(n == 0){
            cout<<"0";
            return 0;
        }
        vector<string> words;
        string s;
        prefsum[0] = 0;
        for(int i = 0; i<n; i++){
            cin>>l>>s;
            words.push_back(s);
            //cout<<s<<"\n";
            wordlength[i] = l;
            prefsum[i+1] = prefsum[i] + wordlength[i];
        }

        long long int minimised_quantity = resolvedp(1, n);
        int itr = 1;
        while(itr<n){
            int nitr = dp[itr][1];
            for(int i = itr; i<nitr; i++){
                cout<<words[i-1]<<" ";
            }
            cout<<"\n";
            itr = nitr;
        }
        if(itr <= n){
            for(int i = itr; i<=n; i++){
                cout<<words[i-1]<<" ";
            }
            cout<<"\n";
        }
        
        cout<<minimised_quantity%N<<"\n";
    }
    auto end = chrono::high_resolution_clock::now(); 
    double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count(); time_taken *= 1e-9; 
    cout << "\nTime taken by program is : " << fixed << time_taken << setprecision(9); cout << " sec" << endl; 
    return 0;
}

#include <iostream>

using namespace std;

const int MAX = 1e4 + 7; // Setting a global variable for maximum limit of stack.

// Implementing the class Stack which allows basic operations like push, pop, IsEmpty and top.
class Stack {

public:
    int tp; // Variable which will point to the top of stack
    int arr[MAX]; // Array which will store the elements of stack with limit MAX 
    
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

int main() {
    class Stack s;
    int n; // Variable that stores the number of instructions
    cin >> n; // Taking in the number from STDIN
    for (int i = 0; i < n; i++) { 
        int p; // Variable for the type of instruction
        cin >> p; // Taking in the value of type from STDIN

        // If function is push take another input for the value to be pushed
        if (p == 1) {
            int x; // Value to be pushed
            cin >> x;
            int ans = s.push(x);
            cout << ans << endl; // Writing ans to STDOUT
        }

        // If the function is pop
        else if (p == 2) {
                int ans = s.pop(); 
                cout << ans << endl; // Writing popped value to STDOUT
        }

        // If the function is to return the value at the top
        else if (p == 3) {
                cout << s.top() << endl;
        }

        // If the function is to check for the emptiness of the stack
        else {
                cout << s.isEmpty() << endl;
        }
    }
    return 0;
}


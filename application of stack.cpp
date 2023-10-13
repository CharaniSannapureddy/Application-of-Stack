#include <iostream>
#include <stack>
#include <string>
#include <algorithm> // Include the algorithm header

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to perform operation
int performOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return -1; // Invalid operator
}

// Function to evaluate a postfix expression
int evaluatePostfix(string postfix) {
    stack<int> operands;

    for (char c : postfix) {
        if (isdigit(c)) {
            operands.push(c - '0'); // Convert char to int
        } else if (isOperator(c)) {
            int b = operands.top(); operands.pop();
            int a = operands.top(); operands.pop();
            operands.push(performOperation(a, b, c));
        }
    }

    return operands.top();
}

// Function to convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> operators;
    string postfix = "";

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != '(' &&
                    ((c == '*' || c == '/') || (operators.top() == '+' || operators.top() == '-'))) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Function to convert infix to prefix
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());

    for (char& c : infix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    return postfix;
}

// Function to check if parentheses are balanced
bool areParenthesesBalanced(string expr) {
    stack<char> parentheses;

    for (char c : expr) {
        if (c == '(') {
            parentheses.push(c);
        } else if (c == ')') {
            if (parentheses.empty() || parentheses.top() != '(') {
                return false;
            }
            parentheses.pop();
        }
    }

    return parentheses.empty();
}

// Function to solve Tower of Hanoi
void towerOfHanoi(int n, char source, char auxiliary, char target) {
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << target << endl;
        return;
    }
    towerOfHanoi(n-1, source, target, auxiliary);
    cout << "Move disk " << n << " from " << source << " to " << target << endl;
    towerOfHanoi(n-1, auxiliary, source, target);
}

int main() {
    int choice;
    cout << "1. Evaluate Postfix Expression" << endl;
    cout << "2. Convert Infix to Postfix" << endl;
    cout << "3. Convert Infix to Prefix" << endl;
    cout << "4. Check Balanced Parentheses" << endl;
    cout << "5. Tower of Hanoi" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            {
                string postfix;
                cout << "Enter postfix expression: ";
                cin >> postfix;
                int result = evaluatePostfix(postfix);
                cout << "Result: " << result << endl;
            }
            break;
        case 2:
            {
                string infix, postfix;
                cout << "Enter infix expression: ";
                cin >> infix;
                postfix = infixToPostfix(infix);
                cout << "Postfix: " << postfix << endl;
            }
            break;
        case 3:
            {
                string infix, prefix;
                cout << "Enter infix expression: ";
                cin >> infix;
                prefix = infixToPrefix(infix);
                cout << "Prefix: " << prefix << endl;
            }
            break;
        case 4:
            {
                string expr;
                cout << "Enter expression: ";
                cin >> expr;
                if (areParenthesesBalanced(expr)) {
                    cout << "Parentheses are balanced." << endl;
                } else {
                    cout << "Parentheses are not balanced." << endl;
                }
            }
            break;
        case 5:
            {
                int n;
                cout << "Enter number of disks: ";
                cin >> n;
                towerOfHanoi(n, 'A', 'B', 'C');
            }
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
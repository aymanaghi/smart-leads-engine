#include <iostream>
#include <stack>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

// ─── Helpers ──────────────────────────────────────────────────────────────────
void printHeader(const string& title) {
    cout << "\n" << BOLD << CYAN;
    cout << "╔══════════════════════════════════════════╗\n";
    cout << "║  " << left << setw(41) << title << "║\n";
    cout << "╚══════════════════════════════════════════╝" << RESET << "\n\n";
}

void printSubHeader(const string& title) {
    cout << BOLD << YELLOW << "\n  ▶ " << title << RESET << "\n";
    cout << "  " << string(40, '-') << "\n";
}

void printStackVisual(vector<int> elements) {
    cout << BOLD << "\n  Stack (top → bottom):\n" << RESET;
    cout << "  ┌─────────────┐\n";
    if (elements.empty()) {
        cout << "  │   (empty)   │\n";
    } else {
        for (int i = elements.size() - 1; i >= 0; i--) {
            string label = (i == (int)elements.size() - 1) ? GREEN " ← TOP" RESET : "";
            cout << "  │" << CYAN << setw(6) << elements[i] << "       " << RESET << "│" << label << "\n";
            if (i > 0) cout << "  ├─────────────┤\n";
        }
    }
    cout << "  └─────────────┘\n";
}

void printTableRow(const string& op, const string& val, const string& result, const string& state) {
    cout << "  │ " << left
         << MAGENTA << setw(8)  << op     << RESET << " │ "
         << YELLOW  << setw(6)  << val    << RESET << " │ "
         << GREEN   << setw(10) << result << RESET << " │ "
         << CYAN    << setw(18) << state  << RESET << " │\n";
}

void printTableHeader() {
    cout << "\n  ┌──────────┬────────┬────────────┬────────────────────┐\n";
    cout << "  │ " << BOLD << left
         << setw(8)  << "Op"          << " │ "
         << setw(6)  << "Value"       << " │ "
         << setw(10) << "Result"      << " │ "
         << setw(18) << "Stack State"
         << RESET << " │\n";
    cout << "  ├──────────┼────────┼────────────┼────────────────────┤\n";
}

void printTableFooter() {
    cout << "  └──────────┴────────┴────────────┴────────────────────┘\n";
}

void printArrayState(int arr[], int topIndex, int capacity) {
    cout << "\n  Internal Array (capacity = " << capacity << "):\n\n";
    cout << "  Index │";
    for (int i = 0; i < capacity; i++) cout << "  [" << i << "]  │";
    cout << "\n  ──────┼";
    for (int i = 0; i < capacity; i++) cout << "───────┼";
    cout << "\n  Value │";
    for (int i = 0; i < capacity; i++) {
        if (i <= topIndex) cout << CYAN << "  " << setw(3) << arr[i] << "   " << RESET << "│";
        else cout << "   ·   │";
    }
    cout << "\n        │";
    for (int i = 0; i < capacity; i++) {
        if (i == topIndex) cout << GREEN << "  ▲    " << RESET << "│";
        else cout << "       │";
    }
    cout << "\n        │";
    for (int i = 0; i < capacity; i++) {
        if (i == topIndex) cout << GREEN << " TOP   " << RESET << "│";
        else cout << "       │";
    }
    cout << "\n  topIndex = " << YELLOW << topIndex << RESET
         << "   size = " << YELLOW << topIndex + 1 << RESET << "\n";
}

// ─── Array Stack ──────────────────────────────────────────────────────────────
class ArrayStack {
public:
    int arr[8];
    int topIndex;
    int capacity = 8;
    ArrayStack() : topIndex(-1) { fill(arr, arr+8, 0); }
    void push(int val) {
        if (topIndex >= capacity-1) { cout << RED << "  Stack Overflow!\n" << RESET; return; }
        arr[++topIndex] = val;
    }
    void pop() {
        if (isEmpty()) { cout << RED << "  Stack Underflow!\n" << RESET; return; }
        arr[topIndex--] = 0;
    }
    int top()      { return arr[topIndex]; }
    bool isEmpty() { return topIndex == -1; }
    int size()     { return topIndex + 1; }
    void visualize() { printArrayState(arr, topIndex, capacity); }
};

// ─── Linked List Stack ────────────────────────────────────────────────────────
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedStack {
public:
    Node* topNode = nullptr;
    int count = 0;
    void push(int val) {
        Node* n = new Node(val);
        n->next = topNode;
        topNode = n;
        count++;
    }
    void pop() {
        if (!topNode) { cout << RED << "  Underflow!\n" << RESET; return; }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }
    int top()      { return topNode->data; }
    bool isEmpty() { return topNode == nullptr; }
    int size()     { return count; }
    void visualize() {
        cout << "\n  Linked List (each box = Node in heap memory):\n\n";
        Node* cur = topNode;
        int idx = 0;
        while (cur) {
            string topLabel = (idx == 0) ? GREEN " ← topNode (HEAD)" RESET : "";
            cout << "  ┌───────────────────┐" << topLabel << "\n";
            cout << "  │ data = " << CYAN << setw(4) << cur->data << RESET << "        │\n";
            if (cur->next)
                cout << "  │ next = " << MAGENTA << "0x..." << setw(4) << (size_t)cur->next % 10000 << RESET << "     │\n";
            else
                cout << "  │ next = " << RED << "nullptr" << RESET << "         │\n";
            cout << "  └───────────────────┘\n";
            if (cur->next) cout << "           │\n           ▼\n";
            cur = cur->next;
            idx++;
        }
        if (!topNode) cout << "  (empty list)\n";
        cout << "  Total nodes: " << YELLOW << count << RESET << "\n";
    }
    ~LinkedStack() { while (!isEmpty()) pop(); }
};

// ─── Stack Sort ───────────────────────────────────────────────────────────────
void sortedInsert(stack<int>& s, int val) {
    if (s.empty() || val > s.top()) { s.push(val); return; }
    int top = s.top(); s.pop();
    sortedInsert(s, val);
    s.push(top);
}
void stackSort(stack<int>& s) {
    if (s.empty()) return;
    int top = s.top(); s.pop();
    stackSort(s);
    sortedInsert(s, top);
}
void printStackInline(stack<int> s) {
    vector<int> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    cout << CYAN << "  bottom [";
    for (int i = v.size()-1; i >= 0; i--) { cout << v[i]; if (i > 0) cout << ", "; }
    cout << "] top" << RESET << "\n";
}

// ─── Bracket Matching ─────────────────────────────────────────────────────────
bool isBalanced(const string& expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') s.push(c);
        else if (c == ')' || c == '}' || c == ']') {
            if (s.empty()) return false;
            char t = s.top(); s.pop();
            if ((c==')' && t!='(') || (c=='}' && t!='{') || (c==']' && t!='[')) return false;
        }
    }
    return s.empty();
}

// ─── Reverse String ───────────────────────────────────────────────────────────
string reverseString(const string& input) {
    stack<char> s;
    for (char c : input) s.push(c);
    string result = "";
    while (!s.empty()) { result += s.top(); s.pop(); }
    return result;
}

void demoReverseString() {
    printHeader("7. Reverse a String  —  Using Stack");
    printSubHeader("How it works");
    cout << "\n"
         << "  1. Push every character onto the stack\n"
         << "  2. Pop one by one — LIFO gives reverse order\n"
         << "  No extra index math needed!\n";

    vector<string> words = { "hello", "stack", "racecar", "C++rocks", "12321" };

    cout << "\n  ┌─────────────┬─────────────┬──────────────┐\n";
    cout << "  │ " << BOLD << left
         << setw(11) << "Input"    << "  │ "
         << setw(11) << "Reversed" << "  │ "
         << setw(12) << "Palindrome?"
         << RESET << "  │\n";
    cout << "  ├─────────────┼─────────────┼──────────────┤\n";
    for (const string& w : words) {
        string rev = reverseString(w);
        bool isPalin = (w == rev);
        string palin = isPalin ? GREEN "✅ Yes" RESET : RED "❌ No " RESET;
        cout << "  │ " << CYAN   << setw(13) << w   << RESET << "│ "
                       << YELLOW << setw(13) << rev << RESET << "│ "
                       << "  " << palin << "        │\n";
    }
    cout << "  └─────────────┴─────────────┴──────────────┘\n";

    printSubHeader("Character stack trace for \"hello\"");
    string demo = "hello";
    stack<char> trace;
    cout << "\n  Pushing characters:\n  ";
    for (char c : demo) {
        trace.push(c);
        cout << GREEN << "push('" << c << "') " << RESET;
    }
    cout << "\n\n  Stack state (top → bottom): ";
    stack<char> tmp = trace;
    cout << CYAN << "[ ";
    while (!tmp.empty()) { cout << "'" << tmp.top() << "' "; tmp.pop(); }
    cout << "]" << RESET << "\n";
    cout << "\n  Popping to build result: ";
    string built = "";
    while (!trace.empty()) {
        cout << YELLOW << "'" << trace.top() << "' " << RESET;
        built += trace.top(); trace.pop();
    }
    cout << "\n\n  Result: " << BOLD << GREEN << built << RESET << "\n";
}

// ─── Undo/Redo ────────────────────────────────────────────────────────────────
void demoUndoRedo() {
    printHeader("8. Undo / Redo System  —  Two Stack Simulation");
    printSubHeader("How it works");
    cout << "\n"
         << "  undoStack  — holds all actions performed\n"
         << "  redoStack  — holds actions that were undone\n\n"
         << "  DO action  → push to undoStack, clear redoStack\n"
         << "  UNDO       → pop from undoStack, push to redoStack\n"
         << "  REDO       → pop from redoStack, push back to undoStack\n";

    stack<string> undoStack, redoStack;

    auto printStacks = [&]() {
        // undo stack
        stack<string> u = undoStack;
        vector<string> uv;
        while (!u.empty()) { uv.push_back(u.top()); u.pop(); }
        cout << "  undoStack : " << CYAN << "[ ";
        for (int i = uv.size()-1; i >= 0; i--) cout << uv[i] << (i>0?", ":"");
        cout << "] ← top" << RESET << "\n";

        // redo stack
        stack<string> r = redoStack;
        vector<string> rv;
        while (!r.empty()) { rv.push_back(r.top()); r.pop(); }
        cout << "  redoStack : " << MAGENTA << "[ ";
        for (int i = rv.size()-1; i >= 0; i--) cout << rv[i] << (i>0?", ":"");
        cout << "] ← top" << RESET << "\n\n";
    };

    auto doAction = [&](const string& action) {
        undoStack.push(action);
        while (!redoStack.empty()) redoStack.pop(); // clear redo on new action
        cout << "  " << GREEN << "DO   " << RESET << "→ \"" << YELLOW << action << RESET << "\"\n";
        printStacks();
    };
    auto undo = [&]() {
        if (undoStack.empty()) { cout << RED << "  Nothing to undo!\n" << RESET; return; }
        string action = undoStack.top(); undoStack.pop();
        redoStack.push(action);
        cout << "  " << RED << "UNDO " << RESET << "→ reversed \"" << YELLOW << action << RESET << "\"\n";
        printStacks();
    };
    auto redo = [&]() {
        if (redoStack.empty()) { cout << RED << "  Nothing to redo!\n" << RESET; return; }
        string action = redoStack.top(); redoStack.pop();
        undoStack.push(action);
        cout << "  " << BLUE << "REDO " << RESET << "→ re-applied \"" << YELLOW << action << RESET << "\"\n";
        printStacks();
    };

    printSubHeader("Simulation");
    cout << "\n";
    doAction("Type 'Hello'");
    doAction("Bold text");
    doAction("Change font size");
    undo();
    undo();
    redo();
    doAction("Insert image");
    undo();
}

// ─── Infix to Postfix ─────────────────────────────────────────────────────────
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string infixToPostfix(const string& expr) {
    stack<char> s;
    string result = "";
    for (char c : expr) {
        if (c == ' ') continue;
        if (isalnum(c)) {
            result += c;
            result += ' ';
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') { result += s.top(); result += ' '; s.pop(); }
            if (!s.empty()) s.pop();
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) { result += s.top(); result += ' '; s.pop(); }
            s.push(c);
        }
    }
    while (!s.empty()) { result += s.top(); result += ' '; s.pop(); }
    return result;
}

void demoInfixPostfix() {
    printHeader("9. Infix \u2192 Postfix Converter");
    printSubHeader("Why postfix?");
    cout << "\n"
         << "  Infix   : A + B * C       (how humans write)\n"
         << "  Postfix : A B C * +       (how computers evaluate — no brackets needed!)\n\n"
         << "  Operator precedence: ^ (3) > * / (2) > + - (1)\n"
         << "  Algorithm: Shunting-yard by Edsger Dijkstra\n";

    printSubHeader("Conversion table");
    vector<pair<string,string>> exprs = {
        {"A+B",            ""},
        {"A+B*C",          ""},
        {"(A+B)*C",        ""},
        {"A+B*C-D",        ""},
        {"(A+B)*(C-D)",    ""},
        {"A^B+C*D",        ""},
    };
    for (auto& e : exprs) e.second = infixToPostfix(e.first);

    cout << "\n  ┌──────────────────┬──────────────────────┐\n";
    cout << "  │ " << BOLD << left
         << setw(16) << "Infix"   << "  │ "
         << setw(20) << "Postfix"
         << RESET << "  │\n";
    cout << "  ├──────────────────┼──────────────────────┤\n";
    for (auto& e : exprs) {
        cout << "  │ " << CYAN   << setw(18) << e.first  << RESET << "│ "
                       << YELLOW << setw(22) << e.second << RESET << "│\n";
    }
    cout << "  └──────────────────┴──────────────────────┘\n";

    printSubHeader("Step-by-step trace: A+B*C");
    string stepExpr = "A+B*C";
    stack<char> stepStack;
    string output = "";
    cout << "\n  ┌────────┬──────────┬────────────────┬──────────────────┐\n";
    cout << "  │ " << BOLD << left
         << setw(6)  << "Char"   << "  │ "
         << setw(8)  << "Action" << "  │ "
         << setw(14) << "Op Stack"  << "  │ "
         << setw(16) << "Output"
         << RESET << "  │\n";
    cout << "  ├────────┼──────────┼────────────────┼──────────────────┤\n";

    for (char c : stepExpr) {
        string action, stackStr = "[", outStr = output;
        if (isalnum(c)) {
            output += c; output += ' ';
            action = "output";
        } else {
            while (!stepStack.empty() && precedence(stepStack.top()) >= precedence(c)) {
                output += stepStack.top(); output += ' ';
                stepStack.pop();
            }
            stepStack.push(c);
            action = "push op";
        }
        stack<char> tmp = stepStack;
        vector<char> sv;
        while (!tmp.empty()) { sv.push_back(tmp.top()); tmp.pop(); }
        for (int i = sv.size()-1; i >= 0; i--) { stackStr += sv[i]; if (i>0) stackStr += ","; }
        stackStr += "]";
        cout << "  │ " << CYAN   << setw(8)  << c       << RESET << "│ "
                       << GREEN  << setw(10) << action  << RESET << "│ "
                       << YELLOW << setw(16) << stackStr<< RESET << "│ "
                       << MAGENTA<< setw(18) << output  << RESET << "│\n";
    }
    while (!stepStack.empty()) {
        output += stepStack.top(); output += ' ';
        stepStack.pop();
    }
    cout << "  ├────────┴──────────┴────────────────┴──────────────────┤\n";
    cout << "  │  Final postfix: " << BOLD << GREEN << left << setw(36) << output << RESET << "│\n";
    cout << "  └─────────────────────────────────────────────────────────┘\n";
}

// ─── Overflow & Underflow ─────────────────────────────────────────────────────
void demoOverflowUnderflow() {
    printHeader("10. Overflow & Underflow Error Handling");
    printSubHeader("What are they?");
    cout << "\n"
         << "  Overflow  — pushing to a FULL stack  (array-based only)\n"
         << "  Underflow — popping from an EMPTY stack\n\n"
         << "  Always guard with isEmpty() before pop()\n"
         << "  Always guard with isFull() before push() on fixed stacks\n";

    // Overflow demo
    printSubHeader("Overflow demo (capacity = 4)");
    struct SmallStack {
        int arr[4]; int top = -1; int cap = 4;
        bool isFull()  { return top == cap-1; }
        bool isEmpty() { return top == -1; }
        void push(int v) {
            if (isFull()) {
                cout << "  push(" << v << ") → " << RED << BOLD << "❌ OVERFLOW!  Stack is full (cap=" << 4 << ")\n" << RESET;
                return;
            }
            arr[++top] = v;
            cout << "  push(" << v << ") → " << GREEN << "✅ OK  [size=" << top+1 << "/" << cap << "]\n" << RESET;
        }
        void pop() {
            if (isEmpty()) {
                cout << "  pop()    → " << RED << BOLD << "❌ UNDERFLOW! Stack is empty\n" << RESET;
                return;
            }
            cout << "  pop()    → " << GREEN << "✅ Removed " << arr[top--] << "\n" << RESET;
        }
    } ss;

    cout << "\n";
    ss.push(10); ss.push(20); ss.push(30); ss.push(40);
    ss.push(99); // overflow
    cout << "\n";

    // Underflow demo
    printSubHeader("Underflow demo");
    cout << "\n";
    ss.pop(); ss.pop(); ss.pop(); ss.pop();
    ss.pop(); // underflow
    cout << "\n";

    // Safe pattern
    printSubHeader("Safe push/pop pattern (best practice)");
    cout << "\n"
         << "  " << BOLD << "// Safe pop:\n" << RESET
         << "  " << CYAN << "if" << RESET << " (!s.empty()) {\n"
         << "      int val = s.top();\n"
         << "      s.pop();\n"
         << "  } else {\n"
         << "      " << RED << "cerr" << RESET << " << \"Stack underflow!\\n\";\n"
         << "  }\n\n"
         << "  " << BOLD << "// Safe push (fixed-size):\n" << RESET
         << "  " << CYAN << "if" << RESET << " (top < capacity - 1) {\n"
         << "      arr[++top] = value;\n"
         << "  } else {\n"
         << "      " << RED << "cerr" << RESET << " << \"Stack overflow!\\n\";\n"
         << "  }\n";
}

// ─── Main ──────────────────────────────────────────────────────────────────────
int main() {

    // 1. STL Stack
    printHeader("1. STL std::stack  —  Operation Table");
    stack<int> stl;
    printTableHeader();
    printTableRow("push",  "10", "ok",         "[] → [10]");          stl.push(10);
    printTableRow("push",  "20", "ok",         "[10] → [10,20]");     stl.push(20);
    printTableRow("push",  "30", "ok",         "[10,20] → [...,30]"); stl.push(30);
    printTableRow("top",   "—",  "30",         "[10,20,30]");
    stl.pop();
    printTableRow("pop",   "—",  "30 removed", "[10,20,30]→[10,20]");
    printTableRow("size",  "—",  "2",          "[10,20]");
    printTableRow("empty", "—",  "false",      "[10,20]");
    printTableFooter();
    printSubHeader("Visual tower after operations");
    printStackVisual({10, 20});

    // 2. Array Stack
    printHeader("2. Array-based Stack  —  Memory Layout");
    ArrayStack as;
    cout << "\n  " << GREEN  << "push(5)"  << RESET << "\n"; as.push(5);  as.visualize();
    cout << "\n  " << GREEN  << "push(15)" << RESET << "\n"; as.push(15); as.visualize();
    cout << "\n  " << GREEN  << "push(25)" << RESET << "\n"; as.push(25); as.visualize();
    cout << "\n  " << RED    << "pop()"    << RESET << "\n"; as.pop();    as.visualize();
    printSubHeader("Summary");
    cout << "  Top   : " << CYAN << as.top()  << RESET << "\n";
    cout << "  Size  : " << CYAN << as.size() << RESET << "\n";
    cout << "  Empty?: " << CYAN << (as.isEmpty() ? "Yes" : "No") << RESET << "\n";

    // 3. Linked List Stack
    printHeader("3. Linked List Stack  —  Pointer Visualization");
    printSubHeader("How a Linked List Stack works");
    cout << "\n"
         << "  Each element is a Node allocated on the HEAP.\n"
         << "  topNode always points to the most recently pushed node.\n"
         << "  Each node holds its data + a pointer to the node below it.\n";
    LinkedStack ls;
    cout << "\n  " << GREEN << "push(100)" << RESET << "\n"; ls.push(100); ls.visualize();
    cout << "\n  " << GREEN << "push(200)" << RESET << "\n"; ls.push(200); ls.visualize();
    cout << "\n  " << GREEN << "push(300)" << RESET << "\n"; ls.push(300); ls.visualize();
    cout << "\n  " << RED   << "pop()"     << RESET << "\n"; ls.pop();     ls.visualize();
    printSubHeader("Array Stack vs Linked List Stack");
    cout << "\n";
    cout << "  ┌─────────────────────────┬──────────────────┬──────────────────┐\n";
    cout << "  │ " << BOLD << left << setw(23) << "Feature" << "  │ "
                            << setw(16) << "Array Stack"    << "  │ "
                            << setw(16) << "Linked Stack"
         << RESET << "  │\n";
    cout << "  ├─────────────────────────┼──────────────────┼──────────────────┤\n";
    auto cmpRow = [](const string& f, const string& a, const string& b) {
        cout << "  │ " << left << setw(25) << f << "│ "
             << GREEN  << setw(18) << a << RESET << "│ "
             << CYAN   << setw(18) << b << RESET << "│\n";
    };
    cmpRow("Memory layout",   "Contiguous",      "Scattered (heap)");
    cmpRow("Size limit",      "Fixed",           "Dynamic");
    cmpRow("Push/Pop speed",  "O(1)",            "O(1)");
    cmpRow("Memory overhead", "Low",             "Extra pointer/node");
    cmpRow("Cache friendly",  "✅ Yes",          "❌ No");
    cmpRow("Overflow risk",   "✅ Yes",          "❌ No (until OOM)");
    cout << "  └─────────────────────────┴──────────────────┴──────────────────┘\n";

    // 4. Stack Sort
    printHeader("4. Stack Sorting Algorithm");
    printSubHeader("How it works");
    cout << "\n"
         << "  Uses two recursive steps:\n"
         << "  1. sortedInsert(s, val) — insert val into correct sorted position\n"
         << "  2. stackSort(s)         — pop all, sort the rest, re-insert each\n"
         << "  Result: smallest on top, largest at bottom.  Time: O(n²)\n";
    stack<int> unsorted;
    vector<int> input = {34, 3, 31, 98, 92, 23};
    for (int v : input) unsorted.push(v);
    printSubHeader("Before sorting");
    printStackInline(unsorted);
    printStackVisual(input);
    printSubHeader("Step-by-step sort trace");
    cout << "\n  ┌──────────┬────────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << setw(8) << "Step" << "  │ " << setw(44) << "Stack state (bottom → top)" << RESET << " │\n";
    cout << "  ├──────────┼────────────────────────────────────────────┤\n";
    stack<int> trace;
    for (int v : input) {
        sortedInsert(trace, v);
        stack<int> tmp = trace;
        vector<int> st;
        while (!tmp.empty()) { st.push_back(tmp.top()); tmp.pop(); }
        reverse(st.begin(), st.end());
        cout << "  │ " << YELLOW << "insert " << setw(3) << v << RESET << "│  ";
        cout << CYAN << "bottom [";
        for (int i = 0; i < (int)st.size(); i++) { cout << st[i]; if (i < (int)st.size()-1) cout << ", "; }
        cout << "] top" << RESET << "\n";
    }
    cout << "  └──────────┴────────────────────────────────────────────┘\n";
    stackSort(unsorted);
    stack<int> tmp2 = unsorted;
    vector<int> sorted_vec;
    while (!tmp2.empty()) { sorted_vec.push_back(tmp2.top()); tmp2.pop(); }
    reverse(sorted_vec.begin(), sorted_vec.end());
    printSubHeader("After sorting (smallest on top)");
    printStackInline(unsorted);
    printStackVisual(sorted_vec);

    // 5. Bracket Matching
    printHeader("5. Practical Use  —  Bracket Matching");
    vector<string> tests = { "{[()]}", "{[(])}", "((()))", "(((", "[{()}]", "[(])" };
    cout << "\n  ┌───────────────┬──────────────────┐\n";
    cout << "  │ " << BOLD << left << setw(13) << "Expression" << "  │ " << setw(16) << "Result" << " │\n" << RESET;
    cout << "  ├───────────────┼──────────────────┤\n";
    for (const string& t : tests) {
        bool ok = isBalanced(t);
        string icon   = ok ? GREEN "✅" RESET : RED "❌" RESET;
        string status = ok ? GREEN " Balanced    " RESET : RED " Not Balanced" RESET;
        cout << "  │ " << CYAN << setw(13) << t << RESET << "  │ " << icon << status << "  │\n";
    }
    cout << "  └───────────────┴──────────────────┘\n";

    // 6. LIFO
    printHeader("6. LIFO Concept  —  Push & Pop Order");
    stack<int> lifo;
    vector<int> pushed = {1, 2, 3, 4, 5};
    cout << "  Pushing : ";
    for (int v : pushed) { cout << CYAN << v << " " << RESET; lifo.push(v); }
    cout << "\n  Popping : ";
    while (!lifo.empty()) { cout << YELLOW << lifo.top() << " " << RESET; lifo.pop(); }
    cout << "\n\n  " << GREEN << "▶ Pushed 1→5, popped 5→1  =  Last In, First Out\n" << RESET;

    // 7. Reverse String
    demoReverseString();

    // 8. Undo/Redo
    demoUndoRedo();

    // 9. Infix to Postfix
    demoInfixPostfix();

    // 10. Overflow & Underflow
    demoOverflowUnderflow();

    cout << "\n" << BOLD << GREEN << "  ✅ All 10 demos complete!\n\n" << RESET;
    return 0;
}

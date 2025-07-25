#include <bits/stdc++.h>
#include "func.h"
#include "count.h"
using namespace std;

vector<string> lines;
map<int, int> endMap;
stack<int> loopStack;

string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}

void preprocess() {
    stack<pair<string, int> > stk;
    for (int i = 0; i < lines.size(); i++) {
        string s = trim(lines[i]);
        if (s.substr(0, 5) == "while") {
            stk.push(make_pair("while", i));
        } else if (s.substr(0, 2) == "if") {
            stk.push(make_pair("if", i));
        } else if (s == "endwhile") {
            if (stk.empty() || stk.top().first != "while") {
                cout << "Mismatched endwhile" << endl;
                exit(1);
            }
            int start_line = stk.top().second;
            stk.pop();
            endMap[start_line] = i;
        } else if (s == "endif") {
            if (stk.empty() || stk.top().first != "if") {
                cout << "Mismatched endif" << endl;
                exit(1);
            }
            int start_line = stk.top().second;
            stk.pop();
            endMap[start_line] = i;
        }
    }
    if (!stk.empty()) {
        cout << "Unmatched " << stk.top().first << " at line " << stk.top().second << endl;
        exit(1);
    }
}

void run() {
    int current_line = 0;
    while (current_line < lines.size()) {
        string s = lines[current_line];
        string trimmed = trim(s);

        if (trimmed.substr(0, 5) == "while") {
            string expr = trim(trimmed.substr(5));
            if (expr.empty()) {
                cout << "Invalid while condition at line " << current_line << endl;
                exit(1);
            }
            long long cond = count(expr);
            if (cond) {
                loopStack.push(current_line);
                current_line++;
            } else {
                current_line = endMap[current_line] + 1;
            }
        } else if (trimmed == "endwhile") {
            if (loopStack.empty()) {
                cout << "Unexpected endwhile at line " << current_line << endl;
                exit(1);
            }
            current_line = loopStack.top();
            loopStack.pop();
        } else if (trimmed.substr(0, 2) == "if") {
            string expr = trim(trimmed.substr(2));
            if (expr.empty()) {
                cout << "Invalid if condition at line " << current_line << endl;
                exit(1);
            }
            long long cond = count(expr);
            if (cond) {
                current_line++;
            } else {
                current_line = endMap[current_line] + 1;
            }
        } else if (trimmed == "endif") {
            current_line++;
        } else if (trimmed.substr(0, 5) == "input") {
            string var_name = trim(trimmed.substr(5));
            if (var_name.size() != 1 || !check_var(var_name[0])) {
                cout << "Invalid input statement at line " << current_line << endl;
                exit(1);
            }
            long long value = input();
            var[var_name[0]] = value;
            current_line++;
        } else if (trimmed.substr(0, 6) == "output") {
            string rest = trim(trimmed.substr(6));
            if (!rest.empty() && rest[0] == '"') {
                size_t end_quote = rest.find('"', 1);
                if (end_quote == string::npos) {
                    cout << "Unterminated string at line " << current_line << endl;
                    exit(1);
                }
                string content = rest.substr(1, end_quote - 1);
                output_str(content);
            } else {
                if (rest.empty()) {
                    cout << "Empty output at line " << current_line << endl;
                    exit(1);
                }
                long long value = count(rest);
                output_num(value);
            }
            current_line++;
        } else if (trimmed.find('=') != string::npos) {
            size_t pos = trimmed.find('=');
            string var_str = trim(trimmed.substr(0, pos));
            if (var_str.size() != 1 || !check_var(var_str[0])) {
                cout << "Invalid assignment at line " << current_line << endl;
                exit(1);
            }
            string expr = trim(trimmed.substr(pos + 1));
            if (expr.empty()) {
                cout << "Empty expression at line " << current_line << endl;
                exit(1);
            }
            long long value = count(expr);
            var[var_str[0]] = value;
            current_line++;
        } else {
            current_line++;
        }
    }
}
int main() {
    freopen("code.txt", "r", stdin);
    string s;
    while (getline(cin, s)) {
        if (trim(s) == "end") break;
        lines.push_back(s);
    }
    fclose(stdin);
    freopen("CON", "r", stdin);

    preprocess();
    run();

    return 0;
}

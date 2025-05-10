#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <tuple>
#include <unordered_set>
#include <algorithm>

using namespace std;

// --- Data types for the PDA ---
struct PDA {
    vector<string> states;                       // Q
    vector<char>   sigma;                        // input alphabet
    vector<char>   gamma;                        // stack alphabet
    string         start_state;                  // q0
    char           start_stack;                  // stack bottom marker
    unordered_set<string> accept;                // F

    // transitions: (state, input, pop) -> (next_state, push_string)
    map<tuple<string,char,char>, pair<string,string>> delta;
};

struct StackTransition {
    string  from, to;    // states
    char    inp, pop;    // input symbol & popped symbol
    string  push;        // push‐string (ε means none)
};

// --- Load a PDA from the given filename, using this schema: ---
// Line 1: whitespace‑separated states
// Line 2: whitespace‑separated input symbols (single chars)
// Line 3: whitespace‑separated stack symbols (single chars)
// Line 4: start state
// Line 5: start stack marker (single char)
// Line 6: whitespace‑separated accept states
// Line 7+: transitions: <from> <input> <pop> <push‑string> <to>
PDA load_pda(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: cannot open " << filename << "\n";
        exit(1);
    }
    PDA A;
    string line;

    // 1. states
    getline(in, line);
    {
        istringstream ss(line);
        for (string q; ss >> q; )
            A.states.push_back(q);
    }
    // 2. alphabet
    getline(in, line);
    {
        istringstream ss(line);
        for (string s; ss >> s; )
            A.sigma.push_back(s[0]);
    }
    // 3. stack alphabet
    getline(in, line);
    {
        istringstream ss(line);
        for (string s; ss >> s; )
            A.gamma.push_back(s[0]);
    }
    // 4. start state
    getline(in, A.start_state);
    // 5. start stack marker
    {
        string s;
        getline(in, s);
        A.start_stack = s[0];
    }
    // 6. accept states
    getline(in, line);
    {
        istringstream ss(line);
        for (string q; ss >> q; )
            A.accept.insert(q);
    }
    // 7+. transitions
    while (getline(in, line)) {
        if (line.empty() || line[0]=='#') continue;
        istringstream tr(line);
        string from, to, push;
        string inps, popp;
        tr >> from >> inps >> popp >> push >> to;
        char inp = inps[0], popc = popp[0];
        A.delta[{from, inp, popc}] = {to, push};
    }
    return A;
}

// --- Simulate the PDA. Returns true iff input w is accepted.
//     Also records each transition in `path`. ---
bool accept(const PDA& A,
            const string& w,
            vector<StackTransition>& path)
{
    string cur = A.start_state;
    stack<char> st;
    st.push(A.start_stack);

    for (char c : w) {
        if (find(A.sigma.begin(), A.sigma.end(), c)==A.sigma.end())
            return false;               // invalid input symbol

        if (st.empty()) return false;
        char top = st.top();  st.pop();

        auto key = make_tuple(cur, c, top);
        auto it  = A.delta.find(key);
        if (it==A.delta.end()) return false;  // no matching transition

        auto [nxt, pushes] = it->second;
        path.push_back({cur, nxt, c, top, pushes});
        cur = nxt;

        // push new symbols (rightmost first)
        if (pushes != "ε") {
            for (auto it2 = pushes.rbegin(); it2!=pushes.rend(); ++it2)
                st.push(*it2);
        }
    }

    // accept iff we're in an accept state and stack is back to just the marker
    return st.size()==1
        && st.top()==A.start_stack
        && A.accept.count(cur);
}

int main(int argc, char** argv) {
    if (argc!=3) {
        cerr << "Usage: " << argv[0]
             << " <pda-file> <input-string>\n";
        return 1;
    }
    PDA A = load_pda(argv[1]);

    vector<StackTransition> path;
    bool ok = accept(A, argv[2], path);

    if (ok) {
        cout << "accept\n";
        for (auto& t : path) {
            cout << t.from
                 << " --" << t.inp << "/" << t.pop
                 << "--> " << t.to
                 << " [push=" << t.push << "]\n";
        }
    } else {
        cout << "reject\n";
    }
    return 0;
}


//
//  main.cpp
//  Backward Chaining Reasoning
//
//  Created by Andy Truong on 5/10/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
using namespace std;

vector<string> predicates;
bool isAnd;

vector<string> getPremises(string s) {  //check if premises is conjunct e.g. a^n
    vector<string> returnVec;
    isAnd = false;
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '^')
            isAnd = true;
        
        if (s[i] == '=') {
            break;
        } else if (isalpha(s[i])) {
            string str = string(1, s[i]);
            returnVec.push_back(str);
        }
    }
    return returnVec;
}

bool checkConclusion(string s) {
    for (int i = 0; i < predicates.size(); i++) {
        if (predicates[i].size() == 1 && predicates[i].front() == s[0]) { //checks if query matches fact
            return true;
        } else if (predicates[i].find('>') != std::string::npos) {  //checks all predicates for a match
            int j = predicates[i].find('>');
            if (predicates[i][j+1] == s[0]) {   //get the conclusion of predicate
                vector<string> t = getPremises(predicates[i]);  //gets premises of predicate
                if (isAnd) {    //AND OPERATOR
                    for (int i = 0; i < t.size(); i++) { //checks all premises, if any is false return false
                        if (!checkConclusion(t[i]))
                            return false;
                    }
                    return true;
                } else {    //OR OPERATOR
                    for (int i = 0; i < t.size(); i++)  //if one predicate is deemed true, we return true
                        if (checkConclusion(t[i]))
                            return true;
                }
            }
        }
    }
    return false;
}

int main() {
    string input;
    
    cout << "This is an extended propositional backward chaining reasoning." << endl;
    cout << "Your knowledge base can only accept facts like:" << endl;
    cout << "- P1^P2...^Pk => P, or" << endl;
    cout << "- P1vP2...vPk => P, or" << endl;
    cout << "- P" << endl;
    cout << "Input your knowledge base: (Finish inputs by entering 'nil')" << endl;
    
    while(input != "nil") {
        cin >> input;
        if (input != "nil")
            predicates.push_back(input);
    }
    
    cout << "You have finished your input. Now you can test your system!" << endl;
    cout << "Type 'quit' to exit the program" << endl;
    while (input != "quit") {
        cin >> input;
        if (input != "quit") {
            if (checkConclusion(input)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    
    return 0;
}

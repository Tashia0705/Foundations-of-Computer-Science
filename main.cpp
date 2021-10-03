#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <functional>

int tests = 0;
int fails = 0;

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result);

/*
 Task 4.
 Representing the set of states (and the set of accepting states) in a class using the
 constructor
*/
template<typename State>
class DFA {
  public:
    DFA(std::function<bool(State)> Qp, State q0p, std::function<State(State, int)> Dp,
        std::function<bool (State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
    std::function<bool(State)> Q;
    State q0;
    std::function<State(State, int)> D;
    std::function<bool (State)> F;
    std::vector<State> traceStates;
    
    /*
     Task 10.
     Write a function that given a DFA and a string, determines if the string is accepted.
    */
    bool accepts(DFA d, std::vector<int> w) {
        State qi = q0;
        traceStates.clear();
        traceStates.push_back(qi);
        for(int i = 0; i < w.size(); i++) {
            qi = D(qi, w[i]);
            traceStates.push_back(qi);
        }
        
        if(F(qi))
            std::cout << "Accepted" << std::endl;
        else
            std::cout << "Rejected" << std::endl;
        
        for(int i = 0; i < traceStates.size(); i++) // trace states
            std::cout << "-> " << traceStates[i] << " ";
        std::cout << std::endl;
        return F(qi);
    }
    
    
};

int main(int argc, const char * argv[]) {
    /*
     Task 1.
     An alphabet is a finite set of numbers from 0 to some number N. I will use numbers 0 to 9.
     The characters will be individual elements from an alphabet... I will
     be using integers. ex. {0,1} is an alphabet
    */
    std::vector<int> set;
    for(int i = 0; i <= 5; i++) {
        set.push_back(i);
    }
    
    /*
     Task 2
     Strings are sequences of characters or "abstract elements drawn
     from an alphabet."
     ex. {1,0,1} is a sequence taken from the alphabet {0,1}
    */
    for(int j = 0; j < 20; j++) {
        std::vector<int> result;
        lexi(set, j, result);
    
        for(int i = 0; i < result.size(); i++)
            std::cout << result[i];
        std::cout << std::endl;
    }
    
    /*
     Task 5.
     DFA that accepts no string - has no accepting state
    */
    DFA<int> *x = new DFA<int>(
        [](int x) { return (x == 0); },
        0,
        [](int qi, int c) { return 0; },
        [](int qi) { return qi == 1; }
    );
    std::cout << x->D(0, 1) << std::endl;

    /*
     Task 6.
     DFA that accepts only empty string - accepting state is the start state and any other
     char passed will go to state 1 which is not an accepting state
    */
    DFA<int> *y = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { return 1; },
        [](int qi) { return qi == 0; }
    );
    std::cout << y->D(0, 5) << std::endl;
    
    /*
     Task 8 - 12 different DFAs
    */
    // a. DFA that only accepts binary nums
    DFA<int> *binary = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c){ if(c == 0 || c == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // b. DFA that only accepts even binary nums
    DFA<int> *evenBinary = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if(c == 0) return 0; else return 1; },
        [](int qi) { return qi == 0; }
        ); //sigma is = to all natural nums
    
    // c. DFA that only accepts odd binary nums
    DFA<int> *oddBinary = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if(c == 1) return 0; else return 1; },
        [](int qi) { return qi == 0; }
        );
    
    // d. DFA that only accepts even numbers
    DFA<int> *evenNum = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c % 2 != 0) return 1; else return 0;},
        [](int qi) { return qi == 0; }
        );
    
    // e. DFA that only accepts odd numbers
    DFA<int> *oddNum = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c % 2 != 0) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // f. DFA that only accepts numbers ending in 5
    DFA<int> *five = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if(c % 5 == 0) return 0; else return 1; },
        [](int qi) { return qi == 0; }
        ); // change dfa
    
    // g. DFA that only accepts evenly long strings
    DFA<int> *evenLength = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (qi == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // h. DFA that only accepts strings of odd lengths
    DFA<int> *oddLength = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (qi == 0) return 1; else return 0;},
        [](int qi) { return qi == 1; }
        );
    
    // i. DFA that only accepts strings made of 0s
    DFA<int> *zeros= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 0) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // j. DFA that only accepts strings made of 1s
    DFA<int> *ones= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) {if(c == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // k. DFA that only accepts even number of 0s
    DFA<int> *evenZeros= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 0 && qi == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // l. DFA that only accepts odd number of 1s
    DFA<int> *oddOnes= new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 1 && qi == 0) return 1; else return 0;},
        [](int qi) { return qi == 1; }
        );
    /*
     Task 9.
     For each example DFA, write a dozen tests of their behavior
    */
    std::cout << std::endl << "DFA a: Testing accepted strings:" << std::endl; // DFA a.
    std::vector<int> test1 {0,1};
    for(int j = 1; j <= 6; j++) {
        std::vector<int> result1;
        lexi(test1, j, result1);
        std::cout << "Test " << j << ": ";
        binary->accepts(*binary, result1);
    }
    std::cout << std::endl << "DFA a: Testing rejected strings:" << std::endl;
    for(int i = 1; i <= 6; i++){
        std::cout << "Test " << i << ": ";
        binary->accepts(*binary, {i,i+1,i+2});
    }
    
    std::cout << std::endl << "DFA b: Testing accepted strings:" << std::endl; // DFA b.
    int i = 1;
    for(int j = 1; j <= 12; j = j + 2) {
        std::vector<int> result2;
        lexi(test1, j, result2);
        std::cout << "Test " << i << ": ";
        i++;
        evenBinary->accepts(*evenBinary, result2);
    }
    std::cout << std::endl << "DFA b: Testing rejected strings:" << std::endl;
    i = 1;
    for(int j = 2; j <= 12; j = j + 2) {
        std::vector<int> result2b;
        lexi(test1, j, result2b);
        std::cout << "Test " << i << ": ";
        i++;
        evenBinary->accepts(*evenBinary, result2b);
    }
    
    std::cout << std::endl << "DFA c: Testing accepted strings:" << std::endl; // DFA c.
    i = 1;
    for(int j = 2; j <= 12; j = j + 2) {
        std::vector<int> result3;
        lexi(test1, j, result3);
        std::cout << "Test " << i << ": ";
        i++;
        oddBinary->accepts(*oddBinary, result3);
    }
    std::cout << std::endl << "DFA c: Testing rejected strings:" << std::endl;
    i = 1;
    for(int j = 1; j <= 12; j = j + 2) {
        std::vector<int> result3b;
        lexi(test1, j, result3b);
        std::cout << "Test " << i << ": ";
        i++;
        oddBinary->accepts(*oddBinary, result3b);
    }
    
    std::cout << std::endl << "DFA d: Testing accepted strings:" << std::endl; // DFA d.
    i = 1;
    for(int j = 0; j < 12; j = j + 2){
        std::cout << "Test " << i << ": ";
        evenNum->accepts(*evenNum, {j, j + 1, j + 2});
        i++;
    }
    std::cout << std::endl << "DFA d: Testing rejected strings:" << std::endl;
    i = 1;
    for(int j = 1; j < 12; j = j + 2){
        std::cout << "Test " << i << ": ";
        evenNum->accepts(*evenNum, {j, j + 1, j + 2});
        i++;
    }
    
    std::cout << std::endl << "DFA e: Testing accepted strings:" << std::endl; // DFA e.
    i = 1;
    for(int j = 1; j < 12; j = j + 2){
        std::cout << "Test " << i << ": ";
        oddNum->accepts(*oddNum, {j, j + 1, j + 2});
        i++;
    }
    std::cout << std::endl << "DFA e: Testing rejected strings:" << std::endl;
    i = 1;
    for(int j = 0; j < 12; j = j + 2){
        std::cout << "Test " << i << ": ";
        oddNum->accepts(*oddNum, {j, j + 1, j + 2});
        i++;
    }
    
    std::cout << std::endl << "DFA f: Testing accepted strings:" << std::endl; // DFA f.
    i = 1;
    for(int j = 5; j < 60; j = j + 10){
        std::cout << "Test " << i << ": ";
        five->accepts(*five, {j + 1, j + 2, j});
        i++;
    }
    std::cout << std::endl << "DFA f: Testing rejected strings:" << std::endl;
    for(int j = 1; j < 5; j++){
        std::cout << "Test " << j << ": ";
        five->accepts(*five, {j, j, j});
    }
    std::cout << "Test " << 5 << ": ";
    five->accepts(*five, {7,4,63});
    std::cout << "Test " << 6 << ": ";
    five->accepts(*five, {0,45,97});
    
    std::cout << std::endl << "DFA g: Testing accepted strings:" << std::endl; // DFA g.
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        evenLength->accepts(*evenLength, {i,i + 4,i + 7, i + 2});
    }
    std::cout << std::endl << "DFA g: Testing rejected strings:" << std::endl;
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        evenLength->accepts(*evenLength, {i,i + 4, i + 3});
    }
    
    std::cout << std::endl << "DFA h: Testing accepted strings:" << std::endl; // DFA h.
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        oddLength->accepts(*oddLength, {i,i + 1, i + 2});
    }
    
    std::cout << std::endl << "DFA h: Testing rejected strings:" << std::endl;
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        oddLength->accepts(*oddLength, {i,i + 3,});
    }
    
    std::cout << std::endl << "DFA i: Testing accepted strings:" << std::endl; // DFA i.
    std::vector<int> result4;
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        result4.push_back(0);
        zeros->accepts(*zeros, result4);
    }
    result4.clear();
    std::cout << std::endl << "DFA i: Testing rejected strings:" << std::endl;
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        result4.push_back(2);
        zeros->accepts(*zeros, result4);
    }
    
    std::cout << std::endl << "DFA j: Testing accepted strings:" << std::endl; // DFA j.
    result4.clear();
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        result4.push_back(1);
        ones->accepts(*ones, result4);
    }
    result4.clear();
    std::cout << std::endl << "DFA j: Testing rejected strings:" << std::endl;
    for(int i = 1; i < 7; i++) {
        std::cout << "Test " << i << ": ";
        result4.push_back(5);
        ones->accepts(*ones, result4);
    }
    
    std::cout << std::endl << "DFA k: Testing all 12 strings:" << std::endl; // DFA k.
    result4.clear();
    for(int i = 1; i <= 12; i++) {
        std::cout << "Test " << i << ": ";
        result4.push_back(0);
        evenZeros->accepts(*evenZeros, result4);
    }
    
    std::cout << std::endl << "DFA l: Testing all 12 strings:" << std::endl; // DFA l.
    result4.clear();
    for(int i = 1; i <= 12; i++) {
        std::cout << "Test " << i << ": ";
        result4.push_back(1);
        oddOnes->accepts(*oddOnes, result4);
    }
    
    return 0;
}
    
/*
 Task 3.
 Function that generates the Nth string of a given alphabet’s lexicographic order
*/
std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result) {
    if(N == 0) {
        std::cout << "";
    }
    else {
    
        // generate the value of the nth string
        unsigned long size = alph.size();
        int i = 0;
        int num = pow(size,i);
    
        while(N >= num) {
            N -= num;
            i++;
            num = pow(size, i);
        }
    
        // convert decimal to the right base system
        while(N > 0) {
            result.insert(result.begin(), N % size);
            N = N / size;
        }
        // adds 0s in the begining of string if needed
        if(result.size() < i) {
            for(int j = 0; j <= i - result.size(); j++) {
                result.insert(result.begin(), 0);
            }
        }
    }

    return result;
}

/*
 Task 7.
 DFA that accepts only strings of exactly that character
*/
DFA<int> task7(int ch) {
    DFA<int> *z = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1) || (x == 2); },
        0,
        [=](int qi, int c) { if(c == ch && qi == 0) return 1; else return 2; },
        [](int qi) { return qi == 1; } );
    return *z;
}

// Testing DFAs
void check(std::vector<int> str, bool result, bool expResult) {
    tests++;
    if(result != expResult) {
        fails++;
        for(int i = 0; i < str.size(); i++)
            std::cout << "Failed: " << str[i] << std::endl;
    }
}


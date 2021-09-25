#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <functional>

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result);

/*
 Task 4.
 Representing the set of states (and the set of accepting states) in a class using the
 constructor
*/
template<typename State>
class DFA {
  public:
    DFA(std::function<bool(State)> Qp, State q0p, std::function<State(State, int)> Dp,        std::function<bool (State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
    std::function<bool(State)> Q;
    State q0;
    std::function<State(State, int)> D;
    std::function<bool (State)> F;
    
};

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


int main(int argc, const char * argv[]) {
    /*
     Task 1.
     An alphabet is a finite set of numbers from 0 to some number N. I will use numbers 0 to 9.
     The characters will be individual elements from an alphabet... I will
     be using integers. ex. {0,1} is an alphabet
    */
    
    std::vector<int> set;
    for(int i = 0; i <= 9; i++) {
        set.push_back(i);
    }
    
    /*
     Task 2 / Task 3 continuation
     Strings are sequences of characters or "abstract elements drawn
     from an alphabet."
     ex. {1,0,1} is a sequence taken from the alphabet {0,1}
    */
    
    for(int j = 0; j < 30; j++) {
        std::vector<int> result;
        lexi(set, j, result);
    
        for(int i = 0; i < result.size(); i++) {
            std::cout << result[i];
        }
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
     char passed
    */
    DFA<int> *y = new DFA<int>(
        [](int x) { return (x == 1) || (x == 2); },
        1,
        [](int qi, int c) { return 2; },
        [](int qi) { return qi == 1; }
    );
    std::cout << y->D(0, 0) << std::endl;
    
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



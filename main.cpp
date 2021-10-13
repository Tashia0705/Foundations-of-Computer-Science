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
        return F(qi);
    }
    
    /*
     Task 11.
     Write a function that given a DFA and a string, returns the trace of configurations it visits.
    */
    std::vector<State> trace(DFA d, std::vector<int> w) {
       if(accepts(d, w))
           std::cout << "Accepted" << std::endl;
       else
           std::cout << "Rejected" << std::endl;
       for(int i = 0; i < traceStates.size(); i++) // trace states
           std::cout << "-> " << traceStates[i] << " ";
       std::cout << std::endl;
       return traceStates;
   }
    
    /*
  Task 12.
  Write a function that given a DFA, returns a string that would be accepted
  (or false if this is not possible).
  */
  std::vector<State> getString(DFA d, std::vector<State> alph) {
    std::vector<State> visited{d.q0};
    std::vector< std::pair <int,std::vector<int>>> notVisited; 
    notVisited.push_back(std::make_pair(d.q0, NULL)); 
    
    while(!notVisited.empty()) {
      std::pair<int,std::vector<int>> qi_w = notVisited.front();
      notVisited.erase(notVisited.begin()); 
      if(F(qi_w.first))
        return qi_w.second; 
      for(int i = 0; i < alph.size(); i++) {
        int c = alph[i];
        int qj = D(qi_w.first, c); 
        if(!std::count(visited.begin(), visited.end(), qj)) {
          visited.push_back(qj); 
          notVisited.push_back(std::make_pair(qj, qi_w.second));
        }
      }
    }
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
    std::vector<int> result_;
    lexi(set, 13, result_);
    
    for(int i = 0; i < result_.size(); i++)
        std::cout << result_[i];
    std::cout << std::endl;
    
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
    std::vector<int> vec1 {0,1};
    std::vector<int> result;
    int tests = 0;
    for(int j = 1; j <= 6; j++) {
        result.clear();
        lexi(vec1, j, result);
        if(binary->accepts(*binary, result) == true)
            tests++;
        binary->trace(*binary, result);
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA a: Testing rejected strings:" << std::endl;
    int fails = 0;
    for(int i = 1; i <= 6; i++) {
        if(binary->accepts(*binary, {i,i+1,i+2}) == false)
            fails++;
        binary->trace(*binary, {i,i+1,i+2});
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA b: Testing accepted strings:" << std::endl; // DFA b.
    tests = 0;
    for(int j = 1; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(evenBinary->accepts(*evenBinary, result) == true)
            tests++;
        evenBinary->trace(*evenBinary, result);
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA b: Testing rejected strings:" << std::endl;
    fails = 0;
    for(int j = 2; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(evenBinary->accepts(*evenBinary, result) == false)
            fails++;
        evenBinary->trace(*evenBinary, result);
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
        
    std::cout << std::endl << "DFA c: Testing accepted strings:" << std::endl; // DFA c.
    tests = 0;
    for(int j = 2; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(oddBinary->accepts(*oddBinary, result) == true)
            tests++;
        oddBinary->trace(*oddBinary, result);
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA c: Testing rejected strings:" << std::endl;
    fails = 0;
    for(int j = 1; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(oddBinary->accepts(*oddBinary, result) == false)
            fails++;
        oddBinary->trace(*oddBinary, result);
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA d: Testing accepted strings:" << std::endl; // DFA d.
    tests = 0;
    for(int j = 0; j < 12; j = j + 2) {
        if(evenNum->accepts(*evenNum, {j, j + 1, j + 2}) == true)
            tests++;
        evenNum->trace(*evenNum, {j, j + 1, j + 2});
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA d: Testing rejected strings:" << std::endl;
    fails = 0;
    for(int j = 1; j < 12; j = j + 2){
        if(evenNum->accepts(*evenNum, {j, j + 1, j + 2}) == false)
            fails++;
        evenNum->trace(*evenNum, {j, j + 1, j + 2});
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA e: Testing accepted strings:" << std::endl; // DFA e.
    tests = 0;
    for(int j = 1; j < 12; j = j + 2){
        if(oddNum->accepts(*oddNum, {j, j + 1, j + 2}) == true)
            tests++;
        oddNum->trace(*oddNum, {j, j + 1, j + 2});
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA e: Testing rejected strings:" << std::endl;
    fails = 0;
    for(int j = 0; j < 12; j = j + 2){
        if(oddNum->accepts(*oddNum, {j, j + 1, j + 2}) == false)
            fails++;
        oddNum->trace(*oddNum, {j, j + 1, j + 2});
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA g: Testing accepted strings:" << std::endl; // DFA g.
    tests = 0;
    for(int i = 1; i < 7; i++) {
        if(evenLength->accepts(*evenLength, {i,i + 4,i + 7, i + 2}) == true)
            tests++;
        evenLength->trace(*evenLength, {i,i + 4,i + 7, i + 2});
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA g: Testing rejected strings:" << std::endl;
    fails = 0;
    for(int i = 1; i < 7; i++) {
        if(evenLength->accepts(*evenLength, {i,i + 4, i + 3}) == false)
            fails++;
        evenLength->trace(*evenLength, {i,i + 4, i + 3});
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA h: Testing accepted strings:" << std::endl; // DFA h.
    tests = 0;
    for(int i = 1; i < 7; i++) {
        if(oddLength->accepts(*oddLength, {i,i + 1, i + 2}) == true)
            tests++;
        oddLength->trace(*oddLength, {i,i + 1, i + 2});
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA h: Testing rejected strings:" << std::endl;
    fails = 0;
    for(int i = 1; i < 7; i++) {
        if(oddLength->accepts(*oddLength, {i,i + 3,}) == false)
            fails++;
        oddLength->trace(*oddLength, {i,i + 3,});
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA i: Testing accepted strings:" << std::endl; // DFA i.
    result.clear();
    tests = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(0);
        if(zeros->accepts(*zeros, result) == true)
            tests++;
        zeros->trace(*zeros, result);
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA i: Testing rejected strings:" << std::endl;
    result.clear();
    fails = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(2);
        if(zeros->accepts(*zeros, result) == false)
            fails++;
        zeros->trace(*zeros, result);
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA j: Testing accepted strings:" << std::endl; // DFA j.
    result.clear();
    tests = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(1);
        if(ones->accepts(*ones, result) == true)
            tests++;
        ones->trace(*ones, result);
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA j: Testing rejected strings:" << std::endl;
    result.clear();
    fails = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(5);
        if(ones->accepts(*ones, result) == false)
            fails++;
        ones->trace(*ones, result);
    }
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA k: Testing all 12 strings:" << std::endl; // DFA k.
    result.clear();
    tests = 0; fails = 0;
    for(int i = 1; i <= 12; i++) {
        result.push_back(0);
        if(evenZeros->accepts(*evenZeros, result) == true)
            tests++;
        else
            fails++;
        evenZeros->trace(*evenZeros, result);
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    std::cout << fails << " FAILED TESTS" << std::endl;
    
    std::cout << std::endl << "DFA l: Testing all 12 strings:" << std::endl; // DFA l.
    result.clear();
    tests = 0; fails = 0;
    for(int i = 1; i <= 12; i++) {
        result.push_back(1);
        if(oddOnes->accepts(*oddOnes, result) == true)
            tests++;
        else
            fails++;
        oddOnes->trace(*oddOnes, result);
        oddOnes->getString(*oddOnes, 0, {1}, {0,1});
    }
    std::cout << tests << " PASSED TESTS" << std::endl;
    std::cout << fails << " FAILED TESTS" << std::endl;

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


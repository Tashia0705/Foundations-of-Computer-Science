#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <functional>
#include <utility> 
#include <optional>

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result);
template<typename State>
std::vector<State> traceStates;
int passedTests; 
int failedTests; 

/* Task 4 - Representing the set of states (and the set of accepting states) in a class using the constructor. */
template<typename State>
class DFA {
  public:
    //DFA(); 
    DFA(std::function<bool(State)> Qp, State q0p, std::function<State(State, int)> Dp,
        std::function<bool (State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
    std::function<bool(State)> Q;
    State q0;
    std::function<State(State, int)> D;
    std::function<bool (State)> F;

    
  /* Task 12 - Write a function that given a DFA, returns a string that would be accepted
  (or false if this is not possible). */
  std::optional<std::vector<int>> getString(DFA d, std::vector<int> alph) {
    std::vector<State> visited{d.q0};
    std::vector<std::pair <int,std::vector<int>>> notVisited; 
    std::vector<int> x{-1}; // -1 is epsilon 
    notVisited.push_back(std::make_pair(d.q0, x)); 

    while(!notVisited.empty()) {
      std::pair<int,std::vector<int>> qi_w = notVisited.front(); 
      notVisited.erase(notVisited.begin());
      if(d.F(qi_w.first))
        return qi_w.second; 
      for(int i = 0; i < alph.size(); i++) {
        int c = alph[i];
        int qj = d.D(qi_w.first, c); 
        std::vector<int>::iterator it;
        it =  std::find(visited.begin(), visited.end(), qj); 
        if(it == visited.end()) {
          visited.push_back(qj); 
          notVisited.push_back(std::make_pair(qj, qi_w.second));
        }
      }
      for(int j = 0; j < qi_w.second.size(); j++) 
        std::cout << qi_w.second[j]; 
    }
    return {}; 
  }

  /* Task 13 - Write a function that takes one DFA and returns a DFA that accepts that the given one does not. */ 
  DFA<State> complement(DFA d) {
    auto fprime = [=](State qi) { return !d.F(qi); };
    return DFA<State>(d.Q,d.q0,d.D,fprime); 
  }

  /* Task 14 - Write a function that takes two DFAs and returns a third DFA that accepts a string if either
  argument accepts it. */
  DFA<std::pair<State, State>> Union(DFA a, DFA b) {
    DFA<std::pair<State, State>> *c = new DFA<std::pair<State, State>> (
      [=] (std::pair<State,State> state) { return a.Q(state.first) && b.Q(state.second); }, 
      std::pair<State,State> { a.q0, b.q0 },
      [=] (std::pair<State,State> state, int character) { 
        State qA = a.D(state.first, character); 
        State qB = b.D(state.second, character);
        return std::pair<State,State>{qA,qB}; },
      [=] (std::pair<State,State> state) { return a.F(state.first) || b.F(state.second); } );
    return *c; 
  }

  /* Task 16 - Write a function that takes two DFAs and returns a third DFA that accepts a 
  string if both arguments accepts it. */
  DFA<std::pair<State, State>> Intersection(DFA a, DFA b) {
    DFA<std::pair<State, State>> *c = new DFA<std::pair<State, State>> (
      [=] (std::pair<State,State> state) { return a.Q(state.first) && b.Q(state.second); }, 
      std::pair<State,State> { a.q0, b.q0 },
      [=] (std::pair<State,State> state, int character) { 
        State qA = a.D(state.first, character); 
        State qB = b.D(state.second, character);
        return std::pair<State,State>{qA,qB}; },
      [=] (std::pair<State,State> state) { return a.F(state.first) && b.F(state.second); } );
    return *c; 
  }

  /* Task 18 - Write a function which takes two DFAs (X and Y) and returns whether every string accepted
  by X is also accepted by Y */
  bool subset(DFA a, DFA b, std::vector<int> alph) {
    return getString(Intersect(complement(b), a), alph) == false; 
  }

  /* Task 20 - Write a function which takes two DFAs (X and Y) and returns whether every string accepted 
  by X is also accepted by Y and vice versa */
  bool equals(DFA a, DFA b, std::vector<int> alph) {
    return subset(a, b, alph) && subset(b, a, alph); 
  }
};

/* Task 10 -  a function that given a DFA and a string, determines if the string is accepted */
template<typename State>
  bool accepts(DFA<State> d, std::vector<int> w) {
    State qi = d.q0;        
    traceStates<State>.clear();
    traceStates<State>.push_back(qi);
    for(int i = 0; i < w.size(); i++) {
      qi = d.D(qi, w[i]);
      traceStates<State>.push_back(qi);
    }
    return d.F(qi);
  } 

  /* Task 11 - Write a function that given a DFA and a string, returns the trace of configurations it visits */
  template<typename State>
  std::vector<State> trace(DFA<State> d, std::vector<int> w) { 
    if(accepts(d, w)) 
      passedTests++; 
    else 
      failedTests++; 
    return traceStates<State>;
  } 

  /* Task 14 - Write a function that takes two DFAs and returns a third DFA that accepts
  a string if either argument accepts it */
  template<typename State>
  DFA<std::pair<State, State>> Union(DFA<State> a, DFA<State> b) {
    DFA<std::pair<State, State>> *c = new DFA<std::pair<State, State>> (
      [=] (std::pair<State,State> state) { return a.Q(state.first) && b.Q(state.second); }, 
      std::pair<State,State> { a.q0, b.q0 },
      [=] (std::pair<State,State> state, int character) { 
        State qA = a.D(state.first, character); 
        State qB = b.D(state.second, character);
        return std::pair<State,State>{qA,qB}; },
      [=] (std::pair<State,State> state) { return a.F(state.first) || b.F(state.second); } );
    return *c; 
  }

  /* Task 16 - Write a function that takes two DFAs and returns a third DFA that accepts
  a string if both arguments accepts it */
  template<typename State>
  DFA<std::pair<State, State>> Intersection(DFA<State> a, DFA<State> b) {
    DFA<std::pair<State, State>> *c = new DFA<std::pair<State, State>> (
      [=] (std::pair<State,State> state) { return a.Q(state.first) && b.Q(state.second); }, 
      std::pair<State,State> { a.q0, b.q0 },
      [=] (std::pair<State,State> state, int character) { 
        State qA = a.D(state.first, character); 
        State qB = b.D(state.second, character);
        return std::pair<State,State>{qA,qB}; },
      [=] (std::pair<State,State> state) { return a.F(state.first) && b.F(state.second); } );
    return *c; 
  }


int main(int argc, const char * argv[]) {
    /* Task 1 - An alphabet is a finite set of numbers from 0 to some number N. I will use numbers 0 to 9.
     The characters will be individual elements from an alphabet... I will
     be using integers. ex. {0,1} is an alphabet */
    std::vector<int> set;
    for(int i = 0; i <= 5; i++) {
        set.push_back(i);
    }
    
    /* Task 2 - Strings are sequences of characters or "abstract elements drawn
     from an alphabet." ex. {1,0,1} is a sequence taken from the alphabet {0,1} */
    std::vector<int> result_;
    lexi(set, 13, result_);
    
    /* Task 5.
     DFA that accepts no string - has no accepting state */
    DFA<int> *x = new DFA<int>(
        [](int x) { return (x == 0); },
        0,
        [](int qi, int c) { return 0; },
        [](int qi) { return qi == 1; }
    );

    /*
     Task 6 - DFA that accepts only empty string - accepting state is the start state and any other
     char passed will go to state 1 which is not an accepting state */
    DFA<int> *y = new DFA<int>(
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { return 1; },
        [](int qi) { return qi == 0; }
    );
    
    /* Task 8 - 12 different DFAs */
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
    DFA<int> *zeros = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) { if (c == 0) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // j. DFA that only accepts strings made of 1s
    DFA<int> *ones = new DFA<int> (
        [](int x) { return (x == 0) || (x == 1); },
        0,
        [](int qi, int c) {if(c == 1) return 0; else return 1;},
        [](int qi) { return qi == 0; }
        );
    
    // k. DFA that only accepts even number of 0s
    DFA<int> *evenZeros = new DFA<int> (
      [] (int x) { return (x == 0) || (x == 1); },
      0,
      [](int qi, int c) { if (c == 0 && qi == 1) return 0; else return 1;},
      [](int qi) { return qi == 0; }
    );
    
    // l. DFA that only accepts odd number of 1s in a string made of 1s 
    DFA<int> *oddOnes= new DFA<int> (
      [](int x) { return (x == 0) || (x == 1); },
      0,
      [](int qi, int c) { if (c == 1 && qi == 0) return 1; else return 0;},
      [](int qi) { return qi == 1; }
    );

    /* Task 9 - For each example DFA, write a dozen tests of their behavior */
   // DFA a.
    std::vector<int> vec1 {0,1};
    std::vector<int> result;
    int tests = 0;
    for(int j = 1; j <= 6; j++) {
        result.clear();
        lexi(vec1, j, result);
        if(accepts(*binary, result) == true)
            tests++;
        trace(*binary, result);
    }

    int fails = 0;
    for(int i = 1; i <= 6; i++) {
        if(accepts(*binary, {i,i+1,i+2}) == false)
            fails++;
        trace(*binary, {i,i+1,i+2});
    }

    // DFA b.
    tests = 0;
    for(int j = 1; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(accepts(*evenBinary, result) == true)
            tests++;
        trace(*evenBinary, result);
    }
  
    fails = 0;
    for(int j = 2; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(accepts(*evenBinary, result) == false)
            fails++;
        trace(*evenBinary, result);
    }
        
    // DFA c.
    tests = 0;
    for(int j = 2; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(accepts(*oddBinary, result) == true)
            tests++;
        trace(*oddBinary, result);
    }
    
    fails = 0;
    for(int j = 1; j <= 12; j = j + 2) {
        result.clear();
        lexi(vec1, j, result);
        if(accepts(*oddBinary, result) == false)
            fails++;
        trace(*oddBinary, result);
    }
    
    // DFA d.
    tests = 0;
    for(int j = 0; j < 12; j = j + 2) {
        if(accepts(*evenNum, {j, j + 1, j + 2}) == true)
            tests++;
        trace(*evenNum, {j, j + 1, j + 2});
    }
    
    fails = 0;
    for(int j = 1; j < 12; j = j + 2){
        if(accepts(*evenNum, {j, j + 1, j + 2}) == false)
            fails++;
        trace(*evenNum, {j, j + 1, j + 2});
    }
    
    // DFA e.
    tests = 0;
    for(int j = 1; j < 12; j = j + 2){
        if(accepts(*oddNum, {j, j + 1, j + 2}) == true)
            tests++;
        trace(*oddNum, {j, j + 1, j + 2});
    }
    
    fails = 0;
    for(int j = 0; j < 12; j = j + 2){
        if(accepts(*oddNum, {j, j + 1, j + 2}) == false)
            fails++;
        trace(*oddNum, {j, j + 1, j + 2});
    }
    
    // DFA g.
    tests = 0;
    for(int i = 1; i < 7; i++) {
        if(accepts(*evenLength, {i,i + 4,i + 7, i + 2}) == true)
            tests++;
        trace(*evenLength, {i,i + 4,i + 7, i + 2});
    }
    
    fails = 0;
    for(int i = 1; i < 7; i++) {
        if(accepts(*evenLength, {i,i + 4, i + 3}) == false)
            fails++;
        trace(*evenLength, {i,i + 4, i + 3});
    }
    
    // DFA h.
    tests = 0;
    for(int i = 1; i < 7; i++) {
        if(accepts(*oddLength, {i,i + 1, i + 2}) == true)
            tests++;
        trace(*oddLength, {i,i + 1, i + 2});
    }
    
    fails = 0;
    for(int i = 1; i < 7; i++) {
        if(accepts(*oddLength, {i,i + 3,}) == false)
            fails++;
        trace(*oddLength, {i,i + 3,});
    }
    
    // DFA i.
    result.clear();
    tests = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(0);
        if(accepts(*zeros, result) == true)
            tests++;
        trace(*zeros, result);
    }
    
    result.clear();
    fails = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(2);
        if(accepts(*zeros, result) == false)
            fails++;
        trace(*zeros, result);
    }
    
    // DFA j.
    result.clear();
    tests = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(1);
        if(accepts(*ones, result) == true)
            tests++;
        trace(*ones, result);
    }
    
    result.clear();
    fails = 0;
    for(int i = 1; i < 7; i++) {
        result.push_back(5);
        if(accepts(*ones, result) == false)
            fails++;
        trace(*ones, result);
    }
    
    // DFA k.
    result.clear();
    tests = 0; fails = 0;
    for(int i = 1; i <= 12; i++) {
        result.push_back(0);
        if(accepts(*evenZeros, result) == true)
            tests++;
        else
            fails++;
        trace(*evenZeros, result); 
    }
    
    // DFA l.
    result.clear();
    tests = 0; fails = 0;
    for(int i = 1; i <= 12; i++) {
        result.push_back(1);
        if(accepts(*oddOnes, result) == true)
            tests++;
        else
            fails++;
        trace(*oddOnes, result);
    }

  /* Task 15 - Write a dozen tests for union function. */ 

  std::cout << "Testing Union Function" << std::endl; 
  tests = 0; fails = 0;
  if(accepts(Union<int>(*evenNum, *oddNum), {0,2,4}) == true) // test 1
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenNum, *oddNum), {0,2,4}); 
  
  if(accepts(Union<int>(*evenNum, *binary), {0,1,2}) == true) // test 2
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenNum, *binary), {0,1,2});

  if(accepts(Union<int>(*evenNum, *evenBinary), {0,1,1,0}) == true) // test 3
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenNum, *binary), {0,1,1,0});

  if(accepts(Union<int>(*oddLength, *oddBinary), {0,1,1,0,2}) == true) // test 4
    tests++;
  else 
    fails++; 
  trace(Union<int>(*oddLength, *binary), {0,1,1,0,2});

  std::cout << tests << " PASSED TESTS" << std::endl;
  std::cout << fails << " FAILED TESTS" << std::endl;
  return 0;
}
    
/* Task 3 - Function that generates the Nth string of a given alphabet’s lexicographic order. */
std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result) {
  if(N == 0)
    std::cout << "";
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
      for(int j = 0; j <= i - result.size(); j++)
        result.insert(result.begin(), 0);
    }
  }
    return result;
}

/* Task 7 - DFA that accepts only strings of exactly that character. */
DFA<int> task7(int ch) {
  DFA<int> *z = new DFA<int>(
    [](int x) { return (x == 0) || (x == 1) || (x == 2); },
    0,
    [=](int qi, int c) { if(c == ch && qi == 0) return 1; else return 2; },
    [](int qi) { return qi == 1; } );
    return *z;
}


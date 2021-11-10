#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <functional>
#include <utility> 
#include <optional> 
#include<bits/stdc++.h> 
#include <list> 

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result);
template<typename State>
std::vector<State> traceStates;
int passedTests; 
int failedTests; 

/* Task 4 - Representing the set of states (and the set of accepting states) in a class using the constructor. */
template<typename State>
class DFA {
  public:
    DFA(std::function<bool(State)> Qp, State q0p, std::function<State(State, int)> Dp,
      std::function<bool (State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {};
    std::function<bool(State)> Q;
    State q0;
    std::function<State(State, int)> D;
    std::function<bool (State)> F;
};

/* Task 23 - Define a data type to represent NFAs. */
template<typename State>
class NFA {
  public:
    NFA(std::function<bool(State)> Qp, State q0p, std::function<std::vector<State>(State, int)> Dp, 
      std::function<bool (State)> Fp): Q(Qp), q0(q0p), D(Dp), F(Fp) {}; 
    std::function<bool(State)> Q;
    State q0;
    std::function<std::vector<State>(State, int)> D; 
    std::function<bool(State)> F;
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

/* Task 12 - Write a function that given a DFA, returns a string that would be accepted */
template<typename State>
std::optional<std::list<int>> example(DFA<State> d, std::vector<int> alphabet) {
  std::list<State> visited;
  std::list<std::pair<State, std::list<int>>> H;
  visited.push_back(d.q0);
  std::pair<State, std::list<int>> first(d.q0, std::list<int>()); 
  H.push_back(first);

  while (!H.empty()) {
    std::pair<State, std::list<int>> temp(H.front());
    H.pop_front();

    if (d.F(temp.first)) 
      return std::optional<std::list<int>>(std::in_place, temp.second);
    for (auto c : alphabet) {
      auto qj = d.D(temp.first, c);
      bool x = false;
      for (auto g : visited) {
        if (g == qj) x = true;
      }               
      if (!x) {       
        visited.push_back(qj);
        std::list<int> templist(temp.second);
        templist.push_back(c);
        std::pair<State, std::list<int>> push(qj, templist);
        H.push_back(push);
      }               
    }                   
                           
  };                       
  return {};
}

/* Task 13 - Write a function that takes one DFA and returns a DFA that accepts that the given one does not. */ 
template<typename State>
DFA<State> complement(DFA<State> d) {
  auto fprime = [=](State qi) { return !d.F(qi); };
  return DFA<State>(d.Q,d.q0,d.D,fprime);
}

/* Task 14 - Write a function that takes two DFAs and returns a third DFA that accepts
a string if either argument accepts it */
template<typename State1, typename State2>
DFA<std::pair<State1, State2>> Union(DFA<State1> a, DFA<State2> b) {
  DFA<std::pair<State1, State2>> *c = new DFA<std::pair<State1, State2>> (
    [=] (std::pair<State1,State2> state) { return a.Q(state.first) && b.Q(state.second); }, 
    std::pair<State1,State2> { a.q0, b.q0 },
    [=] (std::pair<State1,State2> state, int character) { 
      State1 qA = a.D(state.first, character); 
      State2 qB = b.D(state.second, character);
      return std::pair<State1,State2>{qA,qB}; },
    [=] (std::pair<State1,State2> state) { return a.F(state.first) || b.F(state.second); } );
  return *c; 
}

/* Task 16 - Write a function that takes two DFAs and returns a third DFA that accepts
a string if both arguments accepts it */
template<typename State1, typename State2>
DFA<std::pair<State1, State2>> Intersection(DFA<State1> a, DFA<State2> b) {
  DFA<std::pair<State1, State2>> *c = new DFA<std::pair<State1, State2>> (
    [=] (std::pair<State1,State2> state) { return a.Q(state.first) && b.Q(state.second); }, 
    std::pair<State1,State2> { a.q0, b.q0 },
    [=] (std::pair<State1,State2> state, int character) { 
      State1 qA = a.D(state.first, character); 
      State2 qB = b.D(state.second, character);
      return std::pair<State1,State2>{qA,qB}; },
    [=] (std::pair<State1,State2> state) { return a.F(state.first) && b.F(state.second); } );
  return *c; 
}

/* Task 18 - Write a function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y */
template<typename State1, typename State2>
bool subset(DFA<State1> a, DFA<State2> b, std::vector<int> alph) {
  return !example(Intersection(complement(b), a), alph);  
}

/* Task 20 - Write a function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y and vice versa */
template<typename State1, typename State2>
bool equals(DFA<State1> a, DFA<State2> b, std::vector<int> alph) {
  return subset(a, b, alph) && subset(b, a, alph); 
} 

/* Task 24 - Write a (trivial) function that converts DFAs into NFAs. */
template<typename State>
DFA<State> convert(DFA<State> d) {
  auto dPrime = [=](State q, int c) { 
    if(c == -1) return std::vector<State> {}; // -1 is epsilon 
    else return std::vector<State> {d.D(q, c)}; };
  return DFA<State>(d.Q,d.q0,dPrime,d.F);
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
  DFA<int> *noStr = new DFA<int>(
    [](int x) { return (x == 0); },
    0,
    [](int qi, int c) { return 0; },
    [](int qi) { return qi == 1; }
  );

  /*
  Task 6 - DFA that accepts only empty string - accepting state is the start state and any other
  char passed will go to state 1 which is not an accepting state */
  DFA<int> *empty = new DFA<int>(
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
  ); 
    
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
    
  // f. DFA that only accepts decimal nums 
  DFA<int> *decimal = new DFA<int>(
    [](int x) { return (x == 0) || (x == 1); },
    0,
    [](int qi, int c){ if(c == 0 || c == 1 || c == 2 
    || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 
    || c == 8 || c == 9) return 0; else return 1;},
    [](int qi) { return qi == 0; }
  );
    
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
    
  // k. DFA that  accepts strings made of only even number of 0s
  DFA<int> *evenZeros = new DFA<int> (
    [] (int x) { return (x == 0) || (x == 1); },
    0,
    [](int qi, int c) { if (c == 0 && qi == 1) return 0; else return 1;},
    [](int qi) { return qi == 0; }
  );
    
  // l. DFA that accepts strings made of only odd number of 1s 
  DFA<int> *oddOnes = new DFA<int> (
    [](int x) { return (x == 0) || (x == 1); },
    0,
    [](int qi, int c) { if (c == 1 && qi == 0) return 1; else return 0;},
    [](int qi) { return qi == 1; }
  );

  /* Task 21 & 22 - Test equality function & verify your complement, union, and 
  intersect functions using the equality function. */
  std::vector<int> sigma {0,1,2,3,4,5,6,7,8,9}; 
  int _true = 0; int _false = 0;
  // false cases 
  if(equals(*noStr, *empty, {}) == true)
    _true++; 
  else 
    _false++;
  if(equals(*evenNum, *evenLength, sigma) == true)
    _true++; 
  else 
    _false++;
  if(equals(*oddNum, *oddLength, sigma) == true)
    _true++; 
  else 
    _false++;
  if(equals(*zeros, *ones, {0,1}) == true)
    _true++; 
  else 
    _false++;
  if(equals(*binary, complement(*evenBinary), {0,1}) == true)
    _true++; 
  else 
    _false++;
  if(equals(Intersection(*evenBinary, *zeros), *binary, {0,1}) == true) 
    _true++;
  else 
    _false++; 
  
  // true cases
  if(equals(*binary, *binary, {0,1}) == true)
    _true++;
  else 
    _false++;  
  if(equals(*empty, *empty, {0,1}) == true)
    _true++;
  else 
    _false++;  
  if(equals(complement(*oddLength), *evenLength, sigma) == true)
    _true++;
  else 
    _false++; 
  if(equals(Union(*evenBinary, *binary), *binary, {0,1}) == true) 
    _true++;
  else 
    _false++; 
  if(equals(Union(*evenBinary, *oddBinary), *binary, {0,1}) == true) 
    _true++;
  else 
    _false++;
  if(equals(Union(*oddNum, *evenNum), *decimal, sigma) == true) 
    _true++; 
  else 
    _false++;   
  

  std::cout << _false << " total cases return FALSE\n";
  std::cout << _true << " total cases return TRUE\n";

  /* Task 25 - Write a dozen example NFAs. */
  // 1. Example 1.27 from book 
  NFA<int> *bk127 = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3) || (x == 4); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; // holds possible transitions 
      if(qi == 1 && c == 0) vec.push_back(1); 
      if(qi == 1 && c == 1) { 
        vec.push_back(1); 
        vec.push_back(2);
      }
      if(qi == 2 && c == 0) vec.push_back(3);
      if(qi == 2 && c == -1) vec.push_back(3);
      if(qi == 3 && c == 1) vec.push_back(4); 
      if(qi == 4 && (c == 0 || c == 1)) vec.push_back(4);
      return vec;  
    }, 
    [](int qi) { return qi = 4; }
  );

  // 2. Example 1.31 from book
  NFA<int> *bk131 = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3) || (x == 4); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 0) vec.push_back(1); 
      if(qi == 1 && c == 1) { 
        vec.push_back(1); 
        vec.push_back(2);
      }
      if(qi == 2 && (c == 0 || c == 1)) vec.push_back(3);
      if(qi == 3 && (c == 0 || c == 1)) vec.push_back(4); 
      return vec;  
    }, 
    [](int qi) { return qi = 4; }
  );

  // 3. Example 1.36 from book 
  NFA<int> *bk136 = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == -1) vec.push_back(3);
      if(qi == 1 && c == 2) vec.push_back(2); 
      if(qi == 2 && c == 1) {
        vec.push_back(2);
        vec.push_back(3); 
      }
      if(qi == 2 && c == 2) vec.push_back(3);
      if(qi == 3 && c == 1) vec.push_back(1); 
      return vec;
    },
    [](int qi) { return qi = 1; } 
  );

  // 4. Accepts strings ending in 01; sigma = {0,1}
  NFA<int> *zerOne = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1, 
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 1) vec.push_back(1); 
      if(qi == 1 && c == 0) {
        vec.push_back(1);
        vec.push_back(2); 
      }
      if(qi == 2 && c == 1) vec.push_back(3); 
      return vec; 
    },
    [](int qi) { return qi = 3; }
  );

  // 5. Accepts strings that have 11; sigma = {0,1}
  NFA<int> *oneOne = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 0) vec.push_back(1); 
      if(qi == 1 && c == 1) {
        vec.push_back(1);
        vec.push_back(2); 
      }
      if(qi == 2 && c == 1) vec.push_back(3); 
      if(qi == 3 && (c == 0 || c == 1)) vec.push_back(3); 
      return vec;
    },
    [](int qi) { return qi = 3; }
  ); 
  
  // 6. Accepts strings whose second to last char is 1
  NFA<int> *last1 = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 0) vec.push_back(1); 
      if(qi == 1 && c == 1) {
        vec.push_back(1);
        vec.push_back(2);
      }
      if(qi == 2 && (c == 1 || c == 0)) vec.push_back(3);
      return vec; 
    },
    [](int qi) {return qi = 3; }
  );
  
  // 8. Accepts strings made of 4s or 7s use -1 
  // 9. Accepts strings that are 123 or 321

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

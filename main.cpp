#include <iostream>
#include <vector>
#include <math.h>
#include <functional>
#include <utility> 
#include <optional>  
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

/* Task 28 - Define a data type to represent trace trees. */ 
template<typename State>
class TraceTree {
  public: 
    State qi; 
    bool result; 
    int c; 
    std::vector<TraceTree<State>> branch; 
    
    TraceTree() {}
    TraceTree(State qi, bool result, int c, std::vector<TraceTree<State>> branch): 
      qi(qi), result(result), c(c), branch(branch) {}
    TraceTree(State qi, bool result, int c) :
      qi(qi), result(result), c(c) {} 

  /* Task 30 - Write a function that given an NFA and a string, returns a tree of 
  all possible traces. */ 
  TraceTree explore(NFA<State> n, std::vector<int> w) {
    return expHelper(n, w, n.q0); 
  } 

  TraceTree expHelper(NFA<State> n, std::vector<int> w, State qi) {
    std::vector<TraceTree<State>> branch; 
    std::vector<State> epsilon = n.D(qi, -1);
    for(unsigned int i = 0; i < epsilon.size(); i++) 
      branch.push_back(expHelper(n, w, epsilon[i]));
    
    if(w.size() > 0) {
      int ch = w[0];
      w.erase(w.begin()); 
      std::vector<State> vec = n.D(qi, ch);
      for(int i = 0; i < vec.size(); i++)
        branch.push_back(expHelper(n, w, vec[i]));
      return TraceTree<State>(qi, n.F(qi), ch, branch);
    } 
    return TraceTree<State>(qi, n.F(qi), -1, branch);  
  }

  void printTT(TraceTree tt, int count) {
    std::cout << std::endl; 
    for(int i = 0; i < count; i++) 
      std::cout << "\t"; 
    count++; 
    std::cout << "State: q" << tt.qi << ", NextChar: " << tt.c;
    for(auto i : tt.branch)
      printTT(i, count); 
    std::cout << std::endl;
    for (int i = 1; i < count; i++)
      std::cout << "\t";
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

/* Task 18 - Function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y */
template<typename State1, typename State2>
bool subset(DFA<State1> a, DFA<State2> b, std::vector<int> alph) {
  return !example(Intersection(complement(b), a), alph);  
}

/* Task 20 - Function which takes two DFAs (X and Y) and returns whether every string 
accepted by X is also accepted by Y and vice versa */
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

/* Task 27 - Oracle function */ 
template<typename State>
bool oracle(NFA<State> n, std::vector<std::pair<State, std::vector<State>>> trace) {
  if(trace.size() == 0) return true; 

  for(unsigned int i = 1; i < trace.size(); i++) {
    std::vector<State> cString = trace[i-1].second; 
    std::vector<State> nString = trace[i].second; 
    auto c = cString[0]; 
    auto cState = trace[i-1].first; 
    auto nState = trace[i].first; 

    if(!cString.empty())
      cString.erase(cString.begin()); 
    auto charTr = n.D(trace[i-1].first, c); 

    if(trace[i-1].second == nString) {
      auto epsilon = n.D(cState, -1); 
      if(find(epsilon.begin(), epsilon.end(), nState) == epsilon.end()) 
        return false; 
    }
    else if(cString != nString)
      return false; 
    else if(find(charTr.begin(), charTr.end(), nState) == charTr.end()) 
      return false; 
  }
  return true; 
}

/* Task 32 - Function that given an NFA and a string, determines if the string is accepted. */
template<typename State> 
bool backtracking(NFA<State> n, std::vector<int> w) {
  return btHelper(n, w, n.q0); 
}
template<typename State> 
bool btHelper(NFA<State> n, std::vector<int> w, State qi) {
  std::vector<State> epsilon = n.D(qi, -1);
  for(auto i : epsilon) {
    if(btHelper(n, w, i)) 
      return true; 
  }
  if(!w.empty()) {
    int c = w[0];
    std::vector<State> ch = n.D(qi,c); 
    w.erase(w.begin()); 
    for(auto i : ch) {
      if(btHelper(n,w,i))
      return true; 
    }
  }
  else
    return n.F(qi); 
  return false;  
}

/* Task 33 - Write a function that takes two NFAs and returns a third
NFA that accepts a string if either argument accepts it. */ 
template<typename State1, typename State2> 
NFA<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>> nUnion(NFA<State1> a, NFA<State2> b) {
  std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> q0 = {0, {std::nullopt, std::nullopt}}; 
  // Q (States)
  std::function<bool(std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>)> Q = 
    [=](std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> qi) {
      if(qi == q0) 
        return true; 
      else if (qi.first == 1 && qi.second.first != std::nullopt)
        return a.Q(qi.second.first.value()); 
      else if (qi.first == 2 && qi.second.second != std::nullopt)
        return b.Q(qi.second.second.value());
      return false; 
  }; 
  // Delta
  std::function<std::vector<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>>(
  std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>, int)>
  delta = [=](std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> qi, int c) {
      
    std::vector<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>> vec;
    if(qi == q0 && c == -1) {
      vec.push_back({1, {a.q0, std::nullopt}});
      vec.push_back({2, {std::nullopt, b.q0}}); 
    }
    else if (qi.first == 1 && qi.second.first.has_value()) {
      std::vector<State1> epsilon = a.D(qi.second.first.value(), -1);
      for (auto i : epsilon)
        vec.push_back({1, {i, std::nullopt}});
      std::vector<State1> ch = a.D(qi.second.first.value(), c);
      for (auto i : ch)
        vec.push_back({1, {i, std::nullopt}});
    }
    else if (qi.first == 2 && qi.second.second.has_value()) {
      std::vector<State2> epsilon = b.D(qi.second.second.value(), -1);
      for (auto i : epsilon)
        vec.push_back({2, {std::nullopt, i}});
      std::vector<State2> ch = b.D(qi.second.second.value(), c);
      for (auto i : ch)
        vec.push_back({2, {std::nullopt, i}}); 
    }
    return vec; 
  };
  // F (accepting state)
  std::function<bool(std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>)> F =
    [=](std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> qi) {
      if (qi.first == 1 && qi.second.first != std::nullopt)
        return a.F(qi.second.first.value());
      else if (qi.first == 2 && qi.second.second != std::nullopt)
        return b.F(qi.second.second.value());
      return false;
  };
  return NFA<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>>(Q, q0, delta, F);
}
/* Task 34 - function that takes two NFAs and returns a third NFA that accepts a string if it 
can be broken into two pieces, one accepted by the first NFA and the other accepted by the second */
template <typename State1, typename State2>
NFA<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>> concatination(NFA<State1> a, NFA<State2> b) {
  std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> q0 = {0, {std::nullopt, std::nullopt}};
  // Q (States)
  std::function<bool(std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>)> Q =
    [=](std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> qi) {
      if (qi == q0)
        return true;
      else if (qi.first == 1 && qi.second.first != std::nullopt) 
        return a.Q(qi.second.first.value());
      else if (qi.first == 2 && qi.second.second != std::nullopt)
        return b.Q(qi.second.second.value());
      return false;
    };

  // Delta 
  std::function<std::vector<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>>(
  std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>, int)>
  delta = [=](std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> qi, int c) {
    std::vector<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>> vec;
    if (qi == q0 && -1)
      vec.push_back({1, {a.q0, std::nullopt}});
    else if (qi.first == 1 && qi.second.first.has_value()) {
      std::vector<State1> epsilon = a.D(qi.second.first.value(), -1);
      for (auto i : epsilon) {
        vec.push_back({1, {i, std::nullopt}});
        if(a.F((i))) vec.push_back({2, {std::nullopt, b.q0}});
      }
      std::vector<State1> ch = a.D(qi.second.first.value(), c);
      for (auto i : ch) {
        vec.push_back({1, {i, std::nullopt}});
        if (a.F((i))) vec.push_back({2, {std::nullopt, b.q0}});
      }
    } 
    else if (qi.first == 2 && qi.second.second.has_value()) {
      std::vector<State2> epsilon = b.D(qi.second.second.value(), -1);
      for (auto i : epsilon)
        vec.push_back({2, {std::nullopt, i}});
      std::vector<State2> ch = b.D(qi.second.second.value(), c);
      for (auto i : ch)
        vec.push_back({2, {std::nullopt, i}});
    }
    return vec;
  };

  // F (accepting states)
  std::function<bool(std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>)> F =
    [=](std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>> qi) {
      if (qi.first == 2 && qi.second.second != std::nullopt)
        return b.F(qi.second.second.value());
      return false;
  };
  return NFA<std::pair<int, std::pair<std::optional<State1>, std::optional<State2>>>>(Q, q0, delta, F);
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
  std::cout << "Testing Equality Function: \n"; 
  std::cout << _false << " FALSE CASES \n";
  std::cout << _true << " TRUE CASES\n";

  /* Task 25 - Write a dozen example NFAs. */
  // 1. Example 1.27 from book; sigma = {0,1}
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

  // 2. Example 1.31 from book; sigma = {0,1}
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

  // 3. Example 1.36 from book; sigma = {1,2} 
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

  // 6. Accepts strings that have 00; sigma = {0,1}
  NFA<int> *zerZero = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 1) vec.push_back(1); 
      if(qi == 1 && c == 0) {
        vec.push_back(1);
        vec.push_back(2); 
      }
      if(qi == 2 && c == 0) vec.push_back(3); 
      if(qi == 3 && (c == 0 || c == 1)) vec.push_back(3); 
      return vec;
    },
    [](int qi) { return qi = 3; }
  ); 
  
  // 7. Accepts strings whose second to last char is 1; sigma = {0,1}
  NFA<int> *seclast1 = new NFA<int> (
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

  // 8. Accepts strings whose second to last char is 0; sigma = {0,1}
  NFA<int> *seclast0 = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 1) vec.push_back(1); 
      if(qi == 1 && c == 0) {
        vec.push_back(1);
        vec.push_back(2);
      }
      if(qi == 2 && (c == 1 || c == 0)) vec.push_back(3);
      return vec; 
    },
    [](int qi) { return qi = 3; }
  );

  // 9. Accepts strings 10 or 101; sigma = {0,1} 
  NFA<int> *nfa_x = new NFA<int> (
    [](int x) {return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec;
      if(qi == 1 && c == 1) vec.push_back(2); 
      if(qi == 2 && c == 0) {
        vec.push_back(1);
        vec.push_back(3); 
      }
      if(qi == 3 && c == 1) vec.push_back(1);
      return vec;  
    },
    [](int qi) { return qi = 1; } 
  );
  
  // 10. Accepts strings that have 77; sigma = {0...9} 
  NFA<int> *seven7 = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3); }, 1,
    [](int qi, int c) {
      std::vector<int> vec; 
      if(qi == 1 && c != 7) vec.push_back(1); 
      if(qi == 1 && c == 7) {
        vec.push_back(1);
        vec.push_back(2); 
      }
      if(qi == 2 && c == 7) vec.push_back(3); 
      if(qi == 3) vec.push_back(3); 
      return vec;
    },
    [](int qi) { return qi = 3; }
  ); 
  
  // 11. Accepts stringss ending in 1; sigma = {0,1}
  NFA<int> *endOne = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2); }, 1,
    [](int qi , int c) {
      std::vector<int> vec; 
      if(qi == 1 && c == 0) vec.push_back(1);
      if(qi == 1 && c == 1) {
        vec.push_back(1);
        vec.push_back(2); 
      }
      return vec; 
    },
     [](int qi) { return qi = 2; }
  );

  // 12. Accepts strings ending in 5; sigma = {0...9}
  NFA<int> *endFive = new NFA<int> (
    [](int x) { return (x == 1) || (x == 2); }, 1,
    [](int qi , int c) {
      std::vector<int> vec; 
      if(qi == 1) vec.push_back(1);
      if(qi == 1 && c == 5) {
        vec.push_back(1);
        vec.push_back(2); 
      }
      return vec; 
    },
     [](int qi) { return qi = 2; }
  );

  /* Task 26 - For each example NFA, write a dozen traces of their behavior */
  int true_, false_; 
  std::vector<std::pair<int, std::vector<int>>> trace1 {
    std::pair<int, std::vector<int>>(1, {1,0,1}), 
    std::pair<int, std::vector<int>>(1, {0,1}), 
    std::pair<int, std::vector<int>>(2, {1}),
    std::pair<int, std::vector<int>>(3, {})
  };

  std::vector<std::pair<int, std::vector<int>>> trace2 {
    std::pair<int, std::vector<int>>(1, {1,0,2}), 
    std::pair<int, std::vector<int>>(1, {0,2}), 
    std::pair<int, std::vector<int>>(2, {2}),
    std::pair<int, std::vector<int>>(3, {})
  };

  std::vector<std::pair<int, std::vector<int>>> trace3 {
    std::pair<int, std::vector<int>>(1, {1,7,7,1}), 
    std::pair<int, std::vector<int>>(1, {7,7,1}), 
    std::pair<int, std::vector<int>>(2, {7,1}),
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(3, {})
  };

  std::vector<std::pair<int, std::vector<int>>> trace4 {
    std::pair<int, std::vector<int>>(1, {1,3,5}), 
    std::pair<int, std::vector<int>>(1, {3,5}), 
    std::pair<int, std::vector<int>>(1, {5}),
    std::pair<int, std::vector<int>>(2, {})
  };

  std::vector<std::pair<int, std::vector<int>>> bk127_1 {
    std::pair<int, std::vector<int>>(1, {1,-1,1,0}), 
    std::pair<int, std::vector<int>>(2, {-1,1,0}), 
    std::pair<int, std::vector<int>>(3, {1,0}),
    std::pair<int, std::vector<int>>(4, {0}),
    std::pair<int, std::vector<int>>(4, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk127_2 {
    std::pair<int, std::vector<int>>(1, {0,1,0,1}), 
    std::pair<int, std::vector<int>>(1, {1,0,1}), 
    std::pair<int, std::vector<int>>(2, {0,1}),
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(4, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk127_3 {
    std::pair<int, std::vector<int>>(1, {1,0,1}), 
    std::pair<int, std::vector<int>>(2, {0,1}), 
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(4, {})
  };

  std::vector<std::pair<int, std::vector<int>>> bk131_1 {
    std::pair<int, std::vector<int>>(1, {1,1,1}), 
    std::pair<int, std::vector<int>>(2, {1,1}), 
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(4, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk131_2 {
    std::pair<int, std::vector<int>>(1, {1,0,1,0}), 
    std::pair<int, std::vector<int>>(1, {0,1,0}), 
    std::pair<int, std::vector<int>>(1, {1,0}),
    std::pair<int, std::vector<int>>(1, {0}),
    std::pair<int, std::vector<int>>(1, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk131_3 {
    std::pair<int, std::vector<int>>(1, {1,1,0}), 
    std::pair<int, std::vector<int>>(2, {1,0}), 
    std::pair<int, std::vector<int>>(3, {0}),
    std::pair<int, std::vector<int>>(4, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk136_1 {
    std::pair<int, std::vector<int>>(1, {2,1,2,1}), 
    std::pair<int, std::vector<int>>(2, {1,2,1}), 
    std::pair<int, std::vector<int>>(2, {2,1}),
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(1, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk136_2 {
    std::pair<int, std::vector<int>>(1, {-1,1}), 
    std::pair<int, std::vector<int>>(3, {1}), 
    std::pair<int, std::vector<int>>(1, {})
  };
  std::vector<std::pair<int, std::vector<int>>> bk136_3 {
    std::pair<int, std::vector<int>>(1, {2,1,1}), 
    std::pair<int, std::vector<int>>(2, {1,1}), 
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(1, {})
  };
  std::vector<std::pair<int, std::vector<int>>> zerOne_1 {
    std::pair<int, std::vector<int>>(1, {1,0,0,1}), 
    std::pair<int, std::vector<int>>(1, {0,0,1}), 
    std::pair<int, std::vector<int>>(1, {0,1}),
    std::pair<int, std::vector<int>>(2, {1}),
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> zerOne_2 {
    std::pair<int, std::vector<int>>(1, {0,0,1}), 
    std::pair<int, std::vector<int>>(1, {0,1}), 
    std::pair<int, std::vector<int>>(2, {1}),
    std::pair<int, std::vector<int>>(3, {}) 
  };
  std::vector<std::pair<int, std::vector<int>>> oneOne_1 {
    std::pair<int, std::vector<int>>(1, {1,0,1,1}), 
    std::pair<int, std::vector<int>>(1, {0,1,1}), 
    std::pair<int, std::vector<int>>(1, {1,1}),
    std::pair<int, std::vector<int>>(2, {1}),
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> oneOne_2 {
    std::pair<int, std::vector<int>>(1, {0,1,1}), 
    std::pair<int, std::vector<int>>(1, {1,1}), 
    std::pair<int, std::vector<int>>(2, {1}),
    std::pair<int, std::vector<int>>(3, {}) 
  };
  std::vector<std::pair<int, std::vector<int>>> oneOne_3 {
    std::pair<int, std::vector<int>>(1, {0,0,1,1}), 
    std::pair<int, std::vector<int>>(1, {0,1,1}), 
    std::pair<int, std::vector<int>>(1, {1,1}),
    std::pair<int, std::vector<int>>(2, {1}),
    std::pair<int, std::vector<int>>(3, {}) 
  };
  std::vector<std::pair<int, std::vector<int>>> zerZero_1 {
    std::pair<int, std::vector<int>>(1, {0,0,1,1}), 
    std::pair<int, std::vector<int>>(2, {0,1,1}), 
    std::pair<int, std::vector<int>>(3, {1,1}),
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(3, {}) 
  };
  std::vector<std::pair<int, std::vector<int>>> zerZero_2 {
    std::pair<int, std::vector<int>>(1, {1,0,0}), 
    std::pair<int, std::vector<int>>(1, {0,0}), 
    std::pair<int, std::vector<int>>(2, {0}),
    std::pair<int, std::vector<int>>(3, {})
  };
   std::vector<std::pair<int, std::vector<int>>> zerZero_3 {
    std::pair<int, std::vector<int>>(1, {0,0}), 
    std::pair<int, std::vector<int>>(2, {0}), 
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> seclast1_1 {
    std::pair<int, std::vector<int>>(1, {1,0,1,0}), 
    std::pair<int, std::vector<int>>(1, {0,1,0}), 
    std::pair<int, std::vector<int>>(1, {1,0}),
    std::pair<int, std::vector<int>>(2, {0}),
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> seclast1_2 {
    std::pair<int, std::vector<int>>(1, {1,0}), 
    std::pair<int, std::vector<int>>(2, {0}), 
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> nfax_1 {
    std::pair<int, std::vector<int>>(1, {1,0}), 
    std::pair<int, std::vector<int>>(2, {0}), 
    std::pair<int, std::vector<int>>(1, {})
  };
  std::vector<std::pair<int, std::vector<int>>> nfax_2 {
    std::pair<int, std::vector<int>>(1, {1,0,1}), 
    std::pair<int, std::vector<int>>(2, {0,1}), 
    std::pair<int, std::vector<int>>(3, {1}),
    std::pair<int, std::vector<int>>(1, {})
  };
  std::vector<std::pair<int, std::vector<int>>> seven7_1 {
    std::pair<int, std::vector<int>>(1, {7,7}), 
    std::pair<int, std::vector<int>>(2, {7}), 
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> seven7_2 {
    std::pair<int, std::vector<int>>(1, {4,7,7}), 
    std::pair<int, std::vector<int>>(1, {7,7}), 
    std::pair<int, std::vector<int>>(2, {7}),
    std::pair<int, std::vector<int>>(3, {})
  };
  std::vector<std::pair<int, std::vector<int>>> endOne_1 {
    std::pair<int, std::vector<int>>(1, {1}), 
    std::pair<int, std::vector<int>>(2, {})
  };
  std::vector<std::pair<int, std::vector<int>>> endOne_2 {
    std::pair<int, std::vector<int>>(1, {1,0,1}), 
    std::pair<int, std::vector<int>>(1, {0,1}),
    std::pair<int, std::vector<int>>(1, {1}),
    std::pair<int, std::vector<int>>(2, {})
  };
  std::vector<std::pair<int, std::vector<int>>> endOne_3 {
    std::pair<int, std::vector<int>>(1, {1,1}), 
    std::pair<int, std::vector<int>>(1, {1}),
    std::pair<int, std::vector<int>>(2, {}),
  };
  std::vector<std::pair<int, std::vector<int>>> endFive_1 {
    std::pair<int, std::vector<int>>(1, {5}), 
    std::pair<int, std::vector<int>>(2, {})
  };
  std::vector<std::pair<int, std::vector<int>>> endFive_2 {
    std::pair<int, std::vector<int>>(1, {3,4,5}), 
    std::pair<int, std::vector<int>>(1, {4,5}),
    std::pair<int, std::vector<int>>(1, {5}),
    std::pair<int, std::vector<int>>(2, {})
  };
  std::vector<std::pair<int, std::vector<int>>> endFive_3 {
    std::pair<int, std::vector<int>>(1, {7,5}), 
    std::pair<int, std::vector<int>>(1, {5}),
    std::pair<int, std::vector<int>>(2, {}),
  };
  

  // NFA  bk127
  if(oracle(*bk127, bk127_1)) true_++;   
  else false_++;  
  if(oracle(*bk127, bk127_2)) true_++;   
  else false_++;
  if(oracle(*bk127, bk127_3)) true_++;   
  else false_++; 
  if(oracle(*bk127, trace1)) true_++;   
  else false_++; 
  if(oracle(*bk127, trace2)) true_++;   
  else false_++; 
  if(oracle(*bk127, trace3)) true_++;   
  else false_++;

  // NFA bk131
  if(oracle(*bk131, bk131_1)) true_++;   
  else false_++;
  if(oracle(*bk131, bk131_3)) true_++;    
  else false_++; 
  if(oracle(*bk131, bk127_3)) true_++;   
  else false_++; 
  if(oracle(*bk131, trace1)) true_++;   
  else false_++; 
  if(oracle(*bk131, trace2)) true_++;   
  else false_++; 
  if(oracle(*bk131, trace3)) true_++;   
  else false_++;

  // NFA bk136
  if(oracle(*bk136, bk136_1)) true_++;   
  else false_++;
  if(oracle(*bk136, bk136_2)) true_++;   
  else false_++;
  if(oracle(*bk136, bk136_3))  true_++;   
  else false_++;
  if(oracle(*bk136, trace1)) true_++;   
  else false_++; 
  if(oracle(*bk136, trace2)) true_++;   
  else false_++; 
  if(oracle(*bk136, trace3)) true_++;   
  else false_++; 

  // NFA zerOne
  if(oracle(*zerOne, trace1)) true_++;   
  else false_++; 
  if(oracle(*zerOne, zerOne_1)) true_++;   
  else false_++; 
  if(oracle(*zerOne, zerOne_2)) true_++;   
  else false_++;  
  if(oracle(*zerOne, trace2)) true_++;   
  else false_++; 
  if(oracle(*zerOne, trace3)) true_++;    
  else false_++; 
  if(oracle(*zerOne, trace4)) true_++;   
  else false_++;  

  // NFA oneOne
  if(oracle(*oneOne, oneOne_1)) true_++;   
  else false_++;
  if(oracle(*oneOne, oneOne_2)) true_++;    
  else false_++;
  if(oracle(*oneOne, oneOne_3)) true_++;    
  else false_++;
  if(oracle(*oneOne, bk131_1)) true_++;    
  else false_++;
  if(oracle(*oneOne, trace3)) true_++;    
  else false_++; 
  if(oracle(*oneOne, trace4)) true_++;   
  else false_++; 

// NFA zerZero
if(oracle(*zerZero, zerZero_1)) true_++;   
else false_++;
if(oracle(*zerZero, zerZero_2)) true_++;   
else false_++;
if(oracle(*zerZero, zerZero_3)) true_++;   
else false_++;
if(oracle(*zerZero, oneOne_1)) true_++;   
else false_++;
if(oracle(*zerZero, oneOne_2)) true_++;    
else false_++;
if(oracle(*zerZero, oneOne_3)) true_++;    
else false_++;

// NFA secLast1 
if(oracle(*seclast1, oneOne_2)) true_++;   
else false_++;
if(oracle(*seclast1, seclast1_1)) true_++;   
else false_++;
if(oracle(*seclast1, seclast1_2)) true_++;
else false_++;
if(oracle(*seclast1, trace1)) true_++;   
else false_++; 
if(oracle(*seclast1, trace2)) true_++;   
else false_++; 
if(oracle(*seclast1, trace3)) true_++;   
else false_++; 

// NFA secLast0
if(oracle(*seclast0, zerZero_2)) true_++;    
else false_++; 
if(oracle(*seclast0, zerZero_3)) true_++;    
else false_++; 
if(oracle(*seclast0, trace1)) true_++;    
else false_++; 
if(oracle(*seclast0, trace2)) true_++;    
else false_++; 
if(oracle(*seclast0, trace3)) true_++;    
else false_++; 
if(oracle(*seclast0, bk127_3)) true_++;    
else false_++; 

// NFA nfa_x
if(oracle(*nfa_x, nfax_1)) true_++;    
else false_++; 
if(oracle(*nfa_x, nfax_2)) true_++; 
else false_++; 
if(oracle(*nfa_x, trace1)) true_++;    
else false_++; 
if(oracle(*nfa_x, trace2)) true_++;    
else false_++; 
if(oracle(*nfa_x, trace3)) true_++;    
else false_++; 
if(oracle(*nfa_x, bk127_3)) true_++;    
else false_++; 

// NFA seven7
if(oracle(*seven7, seven7_1)) true_++;    
else false_++; 
if(oracle(*seven7, seven7_2)) true_++;    
else false_++;
if(oracle(*seven7, trace3)) true_++;    
else false_++; 
if(oracle(*seven7, trace1)) true_++;    
else false_++; 
if(oracle(*seven7, trace2)) true_++;    
else false_++; 
if(oracle(*seven7, bk127_3)) true_++;    
else false_++; 

// NFA endOne
if(oracle(*endOne, endOne_1)) true_++;    
else false_++;
if(oracle(*endOne, endOne_2)) true_++;   
else false_++;
if(oracle(*endOne, endOne_3)) true_++;     
else false_++;
if(oracle(*endOne, trace3)) true_++;    
else false_++; 
if(oracle(*endOne, trace1)) true_++;    
else false_++; 
if(oracle(*endOne, trace2)) true_++;    
else false_++; 

// NFA endFive
if(oracle(*endFive, endFive_1)) true_++;    
else false_++; 
if(oracle(*endFive, endFive_2)) true_++;    
else false_++; 
if(oracle(*endFive, endFive_3)) true_++;    
else false_++; 
if(oracle(*endFive, endOne_1)) true_++;    
else false_++;
if(oracle(*endFive, endOne_2)) true_++;   
else false_++;
if(oracle(*endFive, endOne_3)) true_++;     
else false_++; 

std::cout << "\nTesting Traces of NFAs: \n"; 
std::cout << true_ << " tests passed\n"; 
std::cout << false_ << " tests failed\n";  

  /* Task 29 and 31  */
  TraceTree<int> tt1; 
  tt1.printTT(tt1.explore(*zerOne, {0,1}), 0); 

  /* Testing Union Function */
  std::cout << "Testing Union Function: \n"; 
  if(backtracking(nUnion(*zerOne, *oneOne), {1,0,1}))
    std::cout << " True\n";
  else std::cout << " False\n";
  
  /* Task 35 - Testing Concatination Function */
  if(backtracking(concatination(*zerOne, *oneOne), {0,0,0,1}))
    std::cout << "concatination = true\n";
  else std::cout << "concatination = false\n";


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

#include <iostream>
#include <vector>
#include <math.h>
#include <functional>
#include <utility> 
#include <optional>  
#include <list>
#include <string>  
#include <random> 
#include <sstream>

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

/* Task 41 - Define a data type to represent regular expressions. */ 
class regex {
  public:
    regex() : type("empty") {};
    regex(std::string type) : type("epsilon") {};
    regex(std::string type, std::string c) : type("character"), ch(c){}; 
    regex(std::string type, std::vector<regex> vec) : type(type), vec(vec) {}; 
    ~regex() {}; 

    std::string type; 
    std::string ch;   
    std::vector<regex> vec; 

    /* Task 42 - Write a printer for regular expressions. */
    std::string printRegex(regex r) {
      if(r.type == "empty") 
        return " ";
      else if(r.type == "epsilon") 
        return "-1";
      else if(r.type == "character") 
        return r.ch; 
      else if(r.type == "union") {
        std::string lhs = printRegex(r.vec[0]); 
        std::string rhs = printRegex(r.vec[1]); 
        return "(" + lhs + " U " + rhs + ")";
      } 
      else if(r.type == "star") 
        return "(" + printRegex(r.vec[0]) + ")*";
      else {
        std::string lhs = printRegex(r.vec[0]);
        std::string rhs = printRegex(r.vec[1]);
        return "(" + lhs + " . " + rhs + ")";  
      }
    }

    /* Task 45 - Write a function that accepts a regular expressions and
    generates a random string that would be accepted by it */
    std::string generate() {
      std::string output; 

      std::random_device rd;   
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> distrib(1, 2);

      if(type == "empty") 
        return " ";
      else if(type == "epsilon") 
        return "-1";
      else if(type == "character") 
        return ch;  
      else if(type == "star") {  
        do { output += ch;
          } while(distrib(gen) % 2 == 1);
      }
      else if(type == "union") {
        if(distrib(gen) % 2 == 0)
          return vec[0].generate(); 
        else 
          return vec[1].generate();
      }
      else if(type == "Circ")
        output = vec[0].generate() + vec[1].generate(); 
      return output; 
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

  while(!H.empty()) {
    std::pair<State, std::list<int>> temp(H.front());
    H.pop_front();

    if(d.F(temp.first)) 
      return std::optional<std::list<int>>(std::in_place, temp.second);
    for(auto c : alphabet) {
      auto qj = d.D(temp.first, c);
      bool x = false;
      for (auto g : visited) {
        if (g == qj) x = true;
      }               
      if(!x) {       
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
NFA<State> convertDFA(DFA<State> d) {
  auto dPrime = [=](State q, int c) { 
    if(c == -1) return std::vector<State> {}; // -1 is epsilon 
    else return std::vector<State> { d.D(q, c)}; };
  return NFA<State>(d.Q,d.q0,dPrime,d.F);
}

/* Task 27 - (Oracle) function that given an NFA, a string, a trace, and a boolean, 
determines if the trace is a valid execution */ 
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
  std::vector<std::pair<State, std::vector<int>>> visited; 
  std::vector<std::pair<State, std::vector<int>>> pending;
  pending.push_back(std::pair<State, std::vector<int>>(n.q0, w)); 

  while(!pending.empty()) {
    std::pair<State, std::vector<int>> qi = pending.front(); 
    pending.erase(pending.begin()); 
      if(qi.second.empty() && n.F(qi.first))
        return true; 
    std::vector<State> epsilon = n.D(qi.first, -1);
    for(auto i : epsilon) { 
      std::pair<State, std::vector<State>> found(i,w);  
      if(find(visited.begin(), visited.end(), found) == visited.end()) {
        pending.push_back(found);
        visited.push_back(found);  
      }
    }
    std::vector<int> wprime (qi.second); 
    if(qi.second.size() > 0){
      int c = qi.second[0];
      wprime.erase(wprime.begin()); 
      std::vector<State> ch = n.D(qi.first,c); 
      for(auto i : ch) {
        std::pair<State, std::vector<State>> found(i,wprime);  
        if(find(visited.begin(), visited.end(), found) == visited.end()) {
          pending.push_back(found);
          visited.push_back(found); 
        }
      }
    }
  }
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
    if (qi == q0 && c == -1)
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

/* Task 36 - Kleene Star: function that takes an NFA and returns a new NFA that accepts a string
if it can be broken into N pieces, each accepted by the argument. */ 
template <typename State> 
NFA<State> klnStar(NFA<State> n) {
  State q0 = 0; 
  std::function<bool(State)> Q = [=] (State qi) { return (n.Q(qi) || qi == q0); };
  std::function<std::vector<State>(State, int)> D = [=] (State qi, int c) { 
    std::vector<State> vec = n.D(qi,c); 
    if(qi == q0) 
      vec.push_back(n.q0);
    else if(n.F(qi)) 
      vec.push_back(q0);
    return vec; 
  };
  std::function<bool(State)> F = [=] (State qi) { return (n.F(qi) || qi == q0); };
  return NFA<State>(Q,q0,D,F);
}

/* Task 38 - Write a function which converts an NFA into a DFA that accepts the same language. */
template <typename State>
DFA<std::vector<State>> convertNfa(NFA<State> n) {
  auto nQ = n.Q; 
  auto dQ = [=] (std::vector<State> vecStates) {
    std::vector<State> vecFind; 
    for(int i = 0; i < (int)vecStates.size(); i++) {
      if(nQ(vecStates[i])) {
        for(int j = 0; j <(int)vecFind.size(); j++) 
          if(vecStates[i] == vecFind[j])
            return false;
        vecFind.push_back(vecStates[i]); 
      }
      else 
        return false; 
    }
    return true; 
  };
  auto nD = n.D; 
  auto epsilon = [=] (std::vector<State> vec) {
    bool change = true; 
    while(change) {
      change = false; 
      for(int i = 0; i < (int)vec.size(); i++) {
        std::vector<State> temp = nD(vec[i], -1);
        for (int j = 0; j < (int)temp.size(); j++) 
          if (std::find(vec.begin(), vec.end(), temp[j]) == vec.end()) {
            change = true; 
            vec.push_back(temp[j]);
          }
      }
    }
    return vec; 
  };
  std::vector<State> startSt = {n.q0};
  startSt = epsilon(startSt);
  
  auto nF = n.F;
  auto dF = [=] (std::vector<State> vec) {
    for (int i = 0; i < (int)vec.size(); i++) 
      if (nF(vec[i]))
        return true;
    return false; 
  };
  auto dD = [=](std::vector<State> vec, int c) {
    std::vector<State> check;
    for(int i = 0; i < (int)vec.size(); i++) {
      std::vector<State> temp = nD(vec[i], c);
      check.insert(check.end(), temp.begin(), temp.end());
    }
    for(int i = 0; i < (int)check.size(); i++)
      for(int j = 0; j < (int)check.size(); j++)
        if(check[i] == check[j] && i != j)
          check.erase(check.begin() + j);
    return epsilon(check);
  };
  DFA<std::vector<State>> newDFA(dQ, startSt, dD, dF);
  return newDFA;
}

/* Task 46 - Write a compiler from regular expressions to NFAs */
template <typename State> 
NFA<State> compiler(regex r) { 
  if(r.type == "empty") {
    NFA<int> *empty = new NFA<int>(
    [](int x) { return (x == 0); }, 0,
    [](State qi, int c) { 
      std::vector<int> vec; 
      vec.push_back(0);
      return vec; },
    [](State qi) { return qi == 1; }
    );
    return *empty; 
  }
  else if(r.type == "epsilon") {
    NFA<int> *epsilon = new NFA<int>(
    [](int x) { return (x == 0) || (x == 1); }, 0,
    [](State qi, int c) { 
      std::vector<int> vec; 
      if(c == -1) vec.push_back(0); 
      else vec.push_back(1);
      return vec; },
    [](State qi) { return qi == 0; }
    );
    return *epsilon; 
  }
  else if(r.type == "character") {
    NFA<int> *Char = new NFA<int>(
    [](int x) { return (x == 0) || (x == 1) || (x == 2) || (x == 3) || (x == 4); }, 0,
    [=](State qi, int c) { 
      std::vector<int> vec;  
      std::stringstream num(r.ch); 
      int x;
      num >> x; 
      if(c == x) vec.push_back(1);
      if(qi == 2 && c == x) vec.push_back(2); 
      return vec; },
    [](State qi) { return qi == 1; }
    );
    return *Char; 
  }
  /* 
  else if(r.type == "union") 
    return nUnion(compiler<int>(r.vec[0]),compiler<int>(r.vec[1])); 

  else if(r.type == "star") 
    return klnStar(compiler<int>(r.vec[0])); 

  return concatination(compiler<int>(r.vec[0]),compiler<int>(r.vec[1])); */ 
  NFA<int> newNFA(0,0,0,0); 
  return newNFA; 
}

/* Task 48 - Write an equality checker for regular expressions. */
template <typename T1, typename T2> 
bool regexEquality(regex re1, regex re2, std::vector<int> alph) {
  return equals(convertNfa(compiler<T1>(re1)), convertNfa(compiler<T2>(re2)),alph); 
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
  if(equals(Union(*oddNum, *evenNum), *decimal, sigma) == true) 
    _true++; 
  else 
    _false++;   

  /* Convert DFA to NFA*/
  convertDFA(*evenNum);  

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
  NFA<int> *oneOne = new NFA<int>(
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
      if(qi == 1) vec.push_back(1); 
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

  /* Task 26 - For each example NFA, write a dozen traces of their behavior. */ 
  int true_, false_; 
  std::vector<std::pair<int, std::vector<int>>> bk127_1 {
    std::pair<int, std::vector<int>>(1, {1,-1,1,0}), 
    std::pair<int, std::vector<int>>(2, {-1,1,0}), 
    std::pair<int, std::vector<int>>(3, {1,0}),
    std::pair<int, std::vector<int>>(4, {0}),
    std::pair<int, std::vector<int>>(4, {})
  };
  if(oracle(*bk127, bk127_1)) true_++;   
  else false_++;  

  /* Task 37 - Write a dozen tests for your Kleene star function. */
  int pass;
  std::cout << "Testing Kleene Star Function: \n";  
  if(backtracking(klnStar(*bk127), {1,0,1,1,0,1})) pass++;  
  if(backtracking(klnStar(*bk131), {1,0,1,0})) pass++;
  if(backtracking(klnStar(*bk136), {2,1,2,1})) pass++;
  if(backtracking(klnStar(*zerOne), {0,1,0,1})) pass++; 
  if(backtracking(klnStar(*oneOne), {1,1})) pass++; 
  if(backtracking(klnStar(*zerZero), {0,0})) pass++; 
  if(backtracking(klnStar(*seclast1), {0,1,0})) pass++; 
  if(backtracking(klnStar(*seclast0), {1,0,1})) pass++; 
  if(backtracking(klnStar(*nfa_x), {1,0,1})) pass++; 
  if(backtracking(klnStar(*seven7), {0,7,7,0})) pass++; 
  if(backtracking(klnStar(*endOne), {1,0,0,1})) pass++;  
  if(backtracking(klnStar(*endFive), {0,5,5})) pass++; 

  std::cout << pass << " tests passed\n";

  /* Task 39 - Testing NFAs converted to DFAs using the accepts function */ 
  int passed; 
  if(accepts(convertNfa(*bk127), {1,0,1,1,1})) 
    passed++;
  if(accepts(convertNfa(*bk131), {1,0,1,0}))
    passed++;
  if(accepts(convertNfa(*bk136), {2,1,2,1}))
    passed++; 
  if(accepts(convertNfa(*zerOne), {0,1,0}))
    passed++; 
  if(accepts(convertNfa(*oneOne), {0,0,1,1}))
    passed++;
  if(accepts(convertNfa(*zerZero), {1,1,0,0,0}))
    passed++;
  if(accepts(convertNfa(*seclast1), {1,1,0,1,0}))
    passed++;
  if(accepts(convertNfa(*seclast0), {0,0,1,0,1}))
    passed++;
  if(accepts(convertNfa(*nfa_x), {1,0}))
    passed++;
  if(accepts(convertNfa(*seven7), {1,7,7,5}))
    passed++;
  if(accepts(convertNfa(*endOne), {0,1,1,1}))
    passed++;
  if(accepts(convertNfa(*endFive), {2,5,6,5}))
    passed++;
  std::cout << "\nTesting NFA to DFA conversion: \n";
  std::cout << passed << " tests passed\n";  
  std::cout << std::endl; 

  /* Task 40 - Manually convert a few NFAs to DFAs and verify the output
  of your compiler with your DFA equality function. */

  // NFA #7 converted to DFA
  DFA<int> *secLast1 = new DFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3) || (x == 4); },
    1,
    [](int qi, int c) { 
      if(qi == 1 && c == 0) return 1; 
      if(qi == 1 && c == 1) return 2; 
      if(qi == 2 && c == 1) return 3; 
      if(qi == 2 && c == 0) return 4;
      if(qi == 3 && c == 1) return 3;
      if(qi == 3 && c == 1) return 4;
      if(qi == 4 && c == 1) return 2;
      else return 1; 
    },
    [](int qi) { return qi == 3 || qi == 4; } 
  );

  // NFA #8 converted to DFA
  DFA<int> *secLast0 = new DFA<int> (
    [](int x) { return (x == 1) || (x == 2) || (x == 3) || (x == 4); },
    1,
    [](int qi, int c) { 
      if(qi == 1 && c == 1) return 1; 
      if(qi == 1 && c == 0) return 2; 
      if(qi == 2 && c == 0) return 3; 
      if(qi == 2 && c == 1) return 4;
      if(qi == 3 && c == 0) return 3;
      if(qi == 3 && c == 0) return 4;
      if(qi == 4 && c == 0) return 2;
      else return 1; 
    },
    [](int qi) { return qi == 3 || qi == 4; } 
  );
  int passedDfa; 
  if(accepts(*secLast1, {0,1,0})) 
    passedDfa++; 
  if(accepts(*secLast0, {1,0,1})) 
    passedDfa++; 
  std::cout << "Testing Manually Converted NFAs: \n"; 
  std::cout << passedDfa << " tests passed\n"; 
  std::cout << "Equality Function Test: \n";
  if(equals(*secLast1, *secLast0, {0,1}))
    std::cout << "Strings accepted by both DFAs\n";
  else 
    std::cout << "Strings not accepted by both DFAs\n";  
  std::cout << std::endl; 
  
  /* Task 43 - Write a dozen example regular expressions. */
  std::cout << "Testing Regular Expressions: \n"; 
  regex re1("epsilon");
  regex re2("character", "4"); 
  regex re3("union", std::vector<regex>{re1, re2});
  regex re4("union", std::vector<regex>{regex("character", "1"), regex("character", "0")}); 
  regex re5("star", std::vector<regex>{re2}); 
  regex re6("union", std::vector<regex>{re4, re2}); 
  regex re7("circ", std::vector<regex>{regex("character", "6"), regex("character", "7")});
  regex re8("union", std::vector<regex>{re3, re5}); 
  regex re9("circ", std::vector<regex>{re7, re3}); 
  regex re10("union", std::vector<regex>{re7, regex("character", "9")});
  regex re11("union", std::vector<regex>{re9, re5}); 
  regex re12("circ", std::vector<regex>{re1, re10});   
  std::cout << re1.printRegex(re1) << std::endl; 
  std::cout << re2.printRegex(re2) << std::endl; 
  std::cout << re3.printRegex(re3) << std::endl;
  std::cout << re4.printRegex(re4) << std::endl;
  std::cout << re5.printRegex(re5) << std::endl;
  std::cout << re6.printRegex(re6) << std::endl; 
  std::cout << re7.printRegex(re7) << std::endl;  
  std::cout << re8.printRegex(re8) << std::endl;
  std::cout << re9.printRegex(re9) << std::endl; 
  std::cout << re10.printRegex(re10) << std::endl;
  std::cout << re12.printRegex(re12) << std::endl; 
  std::cout << re11.printRegex(re11) << std::endl; 

  /* Task 44 - For each regular expression, write a few examples of accepted strings and rejected strings. */ 
  std::cout << "\nWrite Accepted/Rejected Strings for Regex: \n";
  std::cout << "Regex 1 : \n" << "-1  Accepted\n" << "7  Rejected\n";
  std::cout << "Regex 2 : \n" << "4  Accepted\n" << "6  Rejected\n";
  std::cout << "Regex 3 : \n" << "-1  Accepted\n" << "1  Rejected\n" << "4  Accepted\n";
  std::cout << "Regex 4 : \n" << "1  Accepted\n" << "6  Rejected\n" << "0  Accepted\n"; 
  std::cout << "Regex 5 : \n" << "4  Accepted\n" << "6  Rejected\n"; 
  std::cout << "Regex 6 : \n" << "4  Accepted\n" << "1  Accepted\n" << "0  Accepted\n" << "2  Rejected\n"; 
  std::cout << "Regex 7 : \n" << "67  Accepted\n" << "6  Rejected\n"; 
  std::cout << "Regex 8 : \n" << "4  Accepted\n" << "1  Accepted\n" << "0 Rejected\n";
  std::cout << "Regex 9 : \n" << "67  Accepted\n" << "-1 Accepted\n" << "4 Accepted\n" << "4 Rejected\n" ;
  std::cout << "Regex 10 : \n" << "67  Accepted\n" << "9 Accepted\n" << "5 Rejected\n";

  /* Task 45 - Continuation */
  std::cout << std::endl << "Testing Generate Function: \n"; 
  std::cout << "Regex 1: " << re1.generate() << std::endl; 
  std::cout << "Regex 2: " << re2.generate() << std::endl;
  std::cout << "Regex 4: " << re4.generate() << std::endl;   
  
  /* Task 47 - Verify that your regular expression compiler works by using DFA equality testing */
  
  if(backtracking(compiler<int>(re2), {4})) std::cout << "works \n"; 
  else std::cout << "didn't work \n";  
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

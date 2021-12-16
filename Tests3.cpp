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
  std::cout << _false << " tests passed \n";
  std::cout << _true << " tests failed\n";

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

/* Task 29 and 31 - For each example NFA, write a dozen tests of their behavior. */
  std::cout << "\nTesting Tasks 29 & 31: \n"; 
  TraceTree<int> tt1;
  std::cout << "Testing NFA bk127: \n";
  tt1.printTT(tt1.explore(*bk127, {1,0,1}), 0);
  tt1.printTT(tt1.explore(*bk127, {0,1,0,1}), 0);
  tt1.printTT(tt1.explore(*bk127, {1,1}), 0); 
  tt1.printTT(tt1.explore(*bk127, {1,1,0}), 0);
  std::cout << "Testing NFA bk131: \n";
  tt1.printTT(tt1.explore(*bk131, {1,1,1}), 0);
  tt1.printTT(tt1.explore(*bk131, {1,0,1,0}), 0);
  tt1.printTT(tt1.explore(*bk131, {1,1,0}), 0);
  tt1.printTT(tt1.explore(*bk131, {1,0}), 0);
  std::cout << "Testing NFA bk136: \n";
  tt1.printTT(tt1.explore(*bk136, {2,1,1}), 0);
  tt1.printTT(tt1.explore(*bk136, {2,1,2,1}), 0);
  tt1.printTT(tt1.explore(*bk136, {2,2}), 0);
  tt1.printTT(tt1.explore(*bk136, {2,1}), 0);
  std::cout << "Testing NFA zerOne: \n"; 
  tt1.printTT(tt1.explore(*zerOne, {0,1}), 0); 
  tt1.printTT(tt1.explore(*zerOne, {1,0,0,1}), 0); 
  tt1.printTT(tt1.explore(*zerOne, {1,1}), 0);
  tt1.printTT(tt1.explore(*zerOne, {0,0}), 0); 
  std::cout << "Testing NFA oneOne: \n"; 
  tt1.printTT(tt1.explore(*oneOne, {0,1}), 0); 
  tt1.printTT(tt1.explore(*oneOne, {0,1,1,0}), 0); 
  tt1.printTT(tt1.explore(*oneOne, {1,1}), 0);
  tt1.printTT(tt1.explore(*oneOne, {0,0}), 0); 
  std::cout << "Testing NFA zerZero: \n"; 
  tt1.printTT(tt1.explore(*zerZero, {0,1,0,0}), 0); 
  tt1.printTT(tt1.explore(*zerZero, {1,0,0,1}), 0); 
  tt1.printTT(tt1.explore(*zerZero, {1,1}), 0);
  tt1.printTT(tt1.explore(*zerZero, {1,0}), 0); 
  std::cout << "Testing NFA seclast1: \n"; 
  tt1.printTT(tt1.explore(*seclast1, {0,1,0}), 0); 
  tt1.printTT(tt1.explore(*seclast1, {0,0,1}), 0); 
  tt1.printTT(tt1.explore(*seclast1, {1,1}), 0);
  tt1.printTT(tt1.explore(*seclast1, {0,1}), 0);
  std::cout << "Testing NFA seclast0: \n"; 
  tt1.printTT(tt1.explore(*seclast0, {0,0,1}), 0); 
  tt1.printTT(tt1.explore(*seclast0, {0,1,1}), 0); 
  tt1.printTT(tt1.explore(*seclast0, {0,0}), 0);
  tt1.printTT(tt1.explore(*seclast0, {1,0}), 0);
  std::cout << "Testing NFA nfa_x: \n"; 
  tt1.printTT(tt1.explore(*nfa_x, {1,0}), 0); 
  tt1.printTT(tt1.explore(*nfa_x, {1,0,1}), 0); 
  tt1.printTT(tt1.explore(*nfa_x, {0,0}), 0);
  tt1.printTT(tt1.explore(*nfa_x, {1,1,0}), 0);
  std::cout << "Testing NFA endOne: \n"; 
  tt1.printTT(tt1.explore(*endOne, {1,0}), 0); 
  tt1.printTT(tt1.explore(*endOne, {1,0,1}), 0); 
  tt1.printTT(tt1.explore(*endOne, {0,0}), 0);
  tt1.printTT(tt1.explore(*endOne, {1,1,1}), 0);

/* Task 35 - Testing Concatination Function */
  std::cout << "\nTesting Concatination Function: \n";
  int pass = 0; int fail = 0; 
  if(backtracking(concatination(*zerOne, *oneOne), {0,1,1,1})) pass++; 
  else fail++;
  if(backtracking(concatination(*bk127, *oneOne), {1,-1,1,1,1})) pass++; 
  else fail++;
  if(backtracking(concatination(*bk131, *bk127), {1,0,1,1,0,0})) pass++; 
  else fail++;
  if(backtracking(concatination(*bk136, *bk131), {2,1,1,1,1,1})) pass++; 
  else fail++; 
  if(backtracking(concatination(*zerZero, *oneOne), {0,0,1,1})) pass++; 
  else fail++;
  if(backtracking(concatination(*seclast1, *seclast0), {1,0,0,1})) pass++; 
  else fail++;
  if(backtracking(concatination(*nfa_x, *seven7), {7})) pass++; 
  else fail++;
  if(backtracking(concatination(*endOne, *endFive), {5})) pass++;  
  else fail++;
  if(backtracking(concatination(*bk127, *oneOne), {4,1,1})) pass++; 
  else fail++;
  if(backtracking(concatination(*bk136, *bk131), {2,2,2,1,1,1})) pass++; 
  else fail++; 
  if(backtracking(concatination(*oneOne, *endOne), {2,3})) pass++; 
  else fail++;
  if(backtracking(concatination(*nfa_x, *endOne), {0,1})) pass++; 
  else fail++;
  std::cout << pass << " tests passed\n";
  std::cout << fail << " tests failed\n"; 

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


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

    // DFA f. 
    if(accepts(*empty, {}) == true) 
      tests++; 
    else if(accepts(*empty, {1,2}) == false) 
      fails++; 
    trace(*empty, {}); 
    trace(*empty, {1,2}); 
    
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
  trace(Union<int>(*evenNum, *evenBinary), {0,1,1,0});

  if(accepts(Union<int>(*oddLength, *oddBinary), {0,1,1,0,2}) == true) // test 4
    tests++;
  else 
    fails++; 
  trace(Union<int>(*oddLength, *oddBinary), {0,1,1,0,2});

  if(accepts(Union<int>(*evenLength, *evenBinary), {0,1,9,0}) == true) // test 5
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenLength, *evenBinary), {0,1,9,0});

  if(accepts(Union<int>(*zeros, *ones), {0,1,0,1,0}) == true) // test 6
    tests++;
  else 
    fails++; 
  trace(Union<int>(*zeros, *ones), {0,1,0,1,0});

  if(accepts(Union<int>(*zeros, *ones), {2,3,4,5}) == true) // test 7
    tests++;
  else 
    fails++; 
  trace(Union<int>(*zeros, *ones), {2,3,4,5});

  if(accepts(Union<int>(*evenNum, *binary), {3,7,9}) == true) // test 8
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenNum, *binary), {3,7,9});

  if(accepts(Union<int>(*oddLength, *oddBinary), {0,1,1,0}) == true) // test 9
    tests++;
  else 
    fails++; 
  trace(Union<int>(*oddLength, *oddBinary), {0,1,1,0});

  if(accepts(Union<int>(*evenLength, *evenBinary), {0,1,9}) == true) // test 10
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenLength, *evenBinary), {0,1,9});

  if(accepts(Union<int>(*evenLength, *zeros), {0,8,9}) == true) // test 11
    tests++;
  else 
    fails++; 
  trace(Union<int>(*evenLength, *zeros), {0,8,9});

  if(accepts(Union<int>(*oddLength, *ones), {0,8,1,7}) == true) // test 12 
    tests++; 
  else 
    fails++; 
  trace(Union<int>(*oddLength, *ones), {0,8,1,7}); 
  std::cout << tests << " PASSED TESTS" << std::endl;
  std::cout << fails << " FAILED TESTS" << std::endl;

  /* Task 17 - Write a dozen tests for Intersection function. */ 
  std::cout << "Testing Intersection Function" << std::endl; 
  tests = 0; fails = 0;
  if(accepts(Intersection<int>(*evenNum, *oddNum), {0,2,4}) == true) // test 1 false
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*evenNum, *oddNum), {0,2,4}); 
  
  if(accepts(Intersection<int>(*evenNum, *binary), {0,1,1,1,0}) == true) // test 2 true
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*evenNum, *binary), {0,1,1,1,0});

  if(accepts(Intersection<int>(*oddNum, *evenBinary), {0,1,1,0}) == true) // test 3 false
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*oddNum, *evenBinary), {0,1,1,0});

  if(accepts(Intersection<int>(*oddLength, *oddBinary), {0,1,1,0,1}) == true) // test 4 true
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*oddLength, *oddBinary), {0,1,1,0,1});

  if(accepts(Intersection<int>(*evenLength, *evenBinary), {0,1,1,1,0,0}) == true) // test 5 true 
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*evenLength, *evenBinary), {0,1,1,1,0,0});

  if(accepts(Intersection<int>(*zeros, *ones), {0,1,0,1,0}) == true) // test 6 false
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*zeros, *ones), {0,1,0,1,0});

  if(accepts(Intersection<int>(*zeros, *evenNum), {0,0,0}) == true) // test 7 true
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*zeros, *evenNum), {0,0,0});

  if(accepts(Intersection<int>(*evenNum, *binary), {3,7,9}) == true) // test 8 false
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*evenNum, *binary), {3,7,9});

  if(accepts(Intersection<int>(*oddLength, *oddBinary), {0,1,1,0}) == true) // test 9 false
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*oddLength, *oddBinary), {0,1,1,0});

  if(accepts(Intersection<int>(*evenLength, *evenBinary), {0,1,9}) == true) // test 10 false 
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*evenLength, *evenBinary), {0,1,9});

  if(accepts(Intersection<int>(*evenLength, *zeros), {0,0,0,0}) == true) // test 11 true
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*evenLength, *zeros), {0,0,0,0});

  if(accepts(Intersection<int>(*oddLength, *ones), {1,1,1}) == true) // test 12 true
    tests++;
  else 
    fails++; 
  trace(Intersection<int>(*oddLength, *ones), {1,1,1}); 

  std::cout << tests << " PASSED TESTS" << std::endl;
  std::cout << fails << " FAILED TESTS" << std::endl;

  /* Testing complement function */
  int pass = 0; int fail = 0;
  if(accepts(complement(*zeros), {1,1,1}) == true) {
    pass++; 
    std::cout << pass << " Passed Tests" << std::endl;
  }
  else {
    fail++; 
    std::cout << fail << " Failed Tests" << std::endl;
  }

  std::cout << "Total number of passed tests: " << passedTests << std::endl;
  std::cout << "Total number of failed tests: " << failedTests << std::endl;  

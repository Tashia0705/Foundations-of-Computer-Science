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
    std::cout << tests << " PASSED" << std::endl;
    
    std::cout << std::endl << "DFA a: Testing rejected strings:" << std::endl;
    int fails = 0;
    for(int i = 1; i <= 6; i++){
        std::cout << "Test " << i << ": ";
        if(binary->accepts(*binary, {i,i+1,i+2}) == false)
            fails++;
        binary->trace(*binary, {i,i+1,i+2});
    }
    std::cout << fails << " FAILED" << std::endl;
    

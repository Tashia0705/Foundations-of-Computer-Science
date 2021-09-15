#include <iostream>
#include <vector>
#include <math.h>

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result);

int main(int argc, const char * argv[]) {
    /*
     Task 1.
     An alphabet is a finite set of numbers from 0 to some number N. I will use numbers 0 to 9.
     The characters will be individual elements from an alphabet... I will
     be using integers. ex. {0,1} is an alphabet
    */
    
    std::vector<int> set;
    set.push_back(0);
    set.push_back(1);
    set.push_back(2);
    
    /*
     Task 2.
     Strings are sequences of characters or "abstract elements drawn
     from an alphabet."
     ex. {1,0,1} is a sequence taken from the alphabet {0,1}
    */
    
    // Task 3 continuation
    
    std::vector<int> result;
    lexi(set, 5, result);
    
    for(int i = 0; i < result.size(); i++) {
        std::cout << result[i];
    }
    std::cout << std::endl;
    
    
    return 0;
}

/*
 Task 3.
 Function that generates the Nth string of a given alphabet’s lexicographic order
*/

std::vector<int> lexi(std::vector<int> &alph, int N, std::vector<int> &result) {
    if(N == 0) {
        std::cout << "Empty Set";
    }
    
    // generate the value of the nth string
    unsigned long size = alph.size();
    int i = 0;
    int num = pow(size,i);
    
    while(N > num) {
        N -= num;
        i++;
        num = pow(size, i);
    }
    
    // convert decimal to the right base system
    while(N > 0) {
        result.insert(result.begin(), N % size);
        N = N / size;
    }
    
    if(result.capacity() < i) {
        for(int j = 0; j < i - result.capacity(); j++) {
                result.insert(result.begin(), 0);
        }
    }

    return result;
}

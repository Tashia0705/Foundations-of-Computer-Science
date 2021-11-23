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

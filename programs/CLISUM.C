#include <stdio.h> //12/4 and what includes to use
using namespace std;
//12/4 and how to grab the string from the command line
main() //12/4 looking in how to handle negatives and non ints
{
   int a, b;

    // Input two integers
    //cout << "Enter two integers: "; 
    cin >> a >> b;
  
      // If b is positive, increment a b times
    for (int i = 0; i < b; i++) {
        a++;
    }
    
    // If b is negative, decrement a |b| times
    for (int i = 0; i > b; i--) {
        a--;
    }

    // Output the sum
    cout << "Sum = " << a << endl;

    return 0;
}
# Study Questions

1. Suppose you want to add unary operations (i.e., ones requiring only one
operand) to the calculator. For example, we might add "M" to indicate
unary minus (i.e., change the sign of the old value) and "A" to indicate
absolute value. What changes would need to be made to the program?

- If an unary operation is entered then the user is not prompted for another value and the updated total value is printed out and the user is prompted to input an operator
- Code for implementing the two example unary operators:
- enum Optype { add, subtract, multiply, sign, absolute, stop, illegal_op };
- apstring OPSTRINGS[] = {'+', '-', '*', 'M', 'A', '=' };
- const int NUMOPS = 6; 
- case sign:
accumulator *= -1;
break;
- case absolute:
if (accumulator < 0) {accumulator *= -1; };
break;

##
2. Suppose that words rather than single character symbols are to be used
for the operators (e.g., the user types "times" instead of "*"). Where in
the program would the necessary changes occur?

- apstring OPSTRINGS[] = {'+', '-', '*', '=' } would become apstring OPSTRINGS[] = {"plus", "minus", "times", "equals" }
##
3. Suppose that the calculator is to be converted to use C++ double values
rather than integers. Where would changes need to be made?

- int current; would need to be changed to double current; and int accumulator = 0; would become double accumulator = 0;
##
5. Show how a new command, "C", which acts like the "Clear" command on
a calculator could be implemented. The clear command sets the current
value to zero.

- 
# Study Questions

Suppose you want to add unary operations (i.e., ones requiring only one
operand) to the calculator. For example, we might add "M" to indicate
unary minus (i.e., change the sign of the old value) and "A" to indicate
absolute value. What changes would need to be made to the program?

1. If an unary operation is entered then the user is not prompted for another value and the updated total value is printed out and the user is prompted to input an operator

Suppose that words rather than single character symbols are to be used
for the operators (e.g., the user types "times" instead of "*"). Where in
the program would the necessary changes occur?

2. apstring OPSTRINGS[] = {'+', '-', '*', '=' } would become apstring OPSTRINGS[] = {"plus", "minus", "times", "equals" }
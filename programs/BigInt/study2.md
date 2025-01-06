# Study Questions 12/16

-Enter value: 40

--> 40

Enter operator (+ - * (= to quit)): *

Enter value: 3

--> 120

Enter operator (+ - * (= to quit)): +

Enter value: 17

--> -10

Enter operator (+ - * (= to quit)): =

##

1. What are the largest and smallest integer values in the programming
environment you use?

- For an signed 64 bit int -9,223,372,036,854,775,808 and 9,223,372,036,854,775,807 are the smallest and largest possible values

##

2. Each BigInt object will need to store the digits that represent the BigInt
value. The decision to allow arbitrarily large BigInt values affects the
choices for storing digits. Name one method for storing digits that will
permit an arbitrary number of digits to be stored. What effect would
a limit on the number of digits in a BigInt have in the design of the
BigInt class?

- An array of ints could be used

##

3. Based on your knowledge of pencil-and-paper methods for doing
arithmetic, what do you think will be the most difficult arithmetic
operation (+, *, -) to implement for the BigInt class? Why?

- Multiply,    

##

4. Experiment with the calculator. If you enter abcd1234 when a number
is expected, what happens? If you enter 1234abcd is the behavior
different? What happens if you enter an operator that’s not one of the
three that are implemented?

- 

##

5. List as many operations as you can that are performed on integers, but
that are not included in the list of BigInt functions and operators above.

- Division (w Truncation), Absolute value, Modulus, GCF, LCF, Exponentiation, Factorial

##
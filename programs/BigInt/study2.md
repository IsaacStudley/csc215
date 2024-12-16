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
# parser
A simple bare bones language that piggy back rides off of C++. It basically loads .txt files with this type of code.

Parser v1 Documentation:

Commands:

PRINT - Prints numbers, strings, and variables.

INPUT - Recieves input from user and sets variable according to input.

EXIT - Ends program correctly.

INT - Creates an integer variable.

SET - Sets variable value.

ADD - Adds an amount to a variable.

IF - If conditional statment.

Commands examples:

PRINT:
	
	print("Hello!");
Prints out Hello! to the screen.

	print(12);
Prints out 12 to the screen.

	print("nl");
Prints a new line on the screen.

INPUT:

	int(num);
	input(num);
Creates a variable with the name "num" with a value of 0, receives input from user, and changes "num" to that input.
	
INT:

	int(numero);
Creates a variable with the name "numero" with a default value of 0.

	int(num,25);
Creates a variable with the name "num" with a value of 25.

SET:

	int(num,5);
	set(num,20);
Creates a variable with the name "num" witha value of 5, then sets the value to 20.
	
ADD:

	int(num,10);
	add(num,5);
Creates a variable named "num" with a value of 10. Then adds 5 to it, thus making it 15.
	
	int(soda,2);
	add(soda,-2);
Creates a variable named "soda" with a value of 2. Then subtracts 2 to it, thus making it 0.

IF:

	if(1 == 1) : print("Yes.");
If statment where if 1 equals 1, it prints "Yes.".
	
	int(num,12);
	if(num == 13) : prints("Num is 13");
If statment where is the variable "num" equals 13, it prints "Num is 13". This will not print, because "num" is not 13, its 12.

EXIT:

	print("Hello world!");
	exit;
Prints "Hello world!" to the screen and then exits the program.

Example program:

	print("Hello! How old are you?");

	print(":nl");

	int(age);

	input(age);

	if (age < 5 ) : print("Your really young!");

	if (age > 5 ) : print("Goodbye grandpa!");

	exit;

Example program output:

	Hello! How old are you?
	>12
	Goodbye grandpa!

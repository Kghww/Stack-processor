# Stack-processor
Algorithms and Data Structures - project 2024/2025

Stack Processor
The Gedanum state has decided to conquer space. In the first stage, it plans to send a number of probes that will search for planets suitable for colonization. The probes must be intelligent and energy-efficient, so a new processor is needed to control them. The commission of Experts Technology Interstellar was commissioned to design it. After many hours of hard work and numerous flashes of genius, the Stack Translator Of Symbols, model AaD5, was created. It still requires a lot of work to start mass production, but in order not to waste time, you were commissioned to write an emulator of this processor. Thanks to it, the creation of probe control systems can begin much faster.

The processor has a program memory, an instruction pointer, and a stack. Program memory stores the program. A program is a sequence of instructions, and each instruction is one character. The instruction pointer stores the number of the instruction that will be executed next, and increments by one after each execution (for most instructions). The processor terminates when the instruction pointer points beyond the last instruction in the program. The first instruction is numbered 0.

The stack stores data for calculations. The stack elements are lists containing zero or more characters (digits, letters, and other symbols). If the list contains only digits and at most one '-' (minus) character at the end, we say that such a list contains a number. The youngest digit of the number is stored in the first position of the list, so the number -1234 is stored as a list 4321-.

It can be assumed that all programs will be correct, i.e. there will be no situations not foreseen in the instruction list.

The list of processor instructions is as follows:

'	apostrophe	push an empty list on the stack
,	comma	pop a list from the stack
:	colon	put a copy of the list on the top of the stack
;	semicolon	swap the places of the list on the top of the stack and the list directly below it
@	at	pop the number A off the stack, then put a copy of the list on the A-th position on the stack (0 is the top of the stack, 1 is the list directly below it etc.); program '0@ is equivalent to the instruction :
.	dot	read a character from standard input and append it to the beginning of the list on the top of the stack
>	greater than	write the first character from the list on the top of the stack to standard output and pop the list off the top of the stack
!	exclamation mark	logical negation: if the top of the stack is an empty list or a list containing a single character '0', replace it with a list containing the character '1'; otherwise replace the list on the top of the stack with a list containing the character '0'
<	less than	pop number A off the stack, pop number B off the stack, if B < A put number 1 on the stack, otherwise put number 0 on the stack
=	equal	pop number A off the stack, pop number B off the stack, if B = A put number 1 on the stack, otherwise put number 0 on the stack
~	tilde	put a number equal to the number of this instruction (the value of the instruction pointer) on the stack
?	question mark	conditional jump: pop number T off the stack pop list W off the stack if W is not empty and does not contain only the character '0' put number T into the instruction pointer and do not increment the instruction pointer;
-	minus	negation: if the last character of the top list is '-' (minus) remove it from the list; otherwise append '-' to the end of the list at the top of the stack
^	caret	absolute value: if the last character of the top list is '-' (minus) remove it from the list
$	dollar	split: detach the first character from the top list and push it onto the stack
#	hash	pop list A off the stack; append A to the end of the list at the top of the stack
+	plus	pop number A off the stack; pop number B off the stack; put number A + B on the stack
&	ampersand	print the contents of the stack to the standard output in the format:
n: list in the nth position on the stack
...
1: list in the second position on the stack
0: list on the top of the stack
the list should be presented as a sequence of consecutive characters from the list (starting with the first)
]		pop number A off the stack; put the character with the ASCII number A on the stack
[		pop list A off the stack; put the number equal to the ASCII number of the first character from list A on the stack
remaining characters	append this character to the top of the list at the top of the stack
Input
The first line of input contains the program to be executed. The second line will contain the characters that will be fed to the program's standard input. Neither the program nor the program's input will contain whitespace. The number of instructions will not exceed 20,000. The number of characters fed to the standard input will not exceed 20,000.
Output
The output should be everything that the processor would write to the standard output.
Rules and scoring
The program should not use STL (except for input and output handling) or arrays (the array can only be used to store the program and input data). Except for reading input, the for/while/do...while loop can be used at most once (recursion should be used).


Example
Input:
'123'-456&+&


Output:
1: 321
0: 654-
0: 333-

Input:
'...&$&
123

Output:
0: 321
1: 21
0: 3

# Lecture 2: Arrays 

“Compiling” source code into machine code is actually made up of smaller steps:

- preprocessing = extract imported libraries into where we import 
- compiling = source code to assembly code 
- assembling  = from assembly to binary 
- linking

## [Data Types](https://cs50.harvard.edu/x/2020/notes/2/#data-types)

1 byte = 8 bits

- In C, we have different types of variables we can use for storing data:
  - bool 1 byte 
  - char 1 byte
  - int 4 bytes --> 32 bits --> 2^32 options
  - float 4 bytes
  - long 8 bytes
  - double 8 bytes 
  - string ? bytes
- Each of these types take up a certain number of bytes per variable we create, and the sizes above are what the sandbox, IDE, and most likely your computer uses for each type in C.

## [Memory](https://cs50.harvard.edu/x/2020/notes/2/#memory)

We can think of bytes, stored in RAM, as though they were in a grid:

- In reality, there are millions or billions of bytes per chip.

- In C, when we create a variable of type `char`, which will be sized one byte, it will physically be stored in one of those boxes in RAM. An integer, with 4 bytes, will take up four of those boxes.
- And each of these boxes is labeled with some number, or address, from 0, to 1, to 2, and so on.

## [Arrays](https://cs50.harvard.edu/x/2020/notes/2/#arrays)

Let’s say we wanted to store three variables:

```c
#include <stdio.h>

int main(void)
{
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';
    printf("%c %c %c\n", c1, c2, c3); // H I !
    printf("%i %i %i\n", c1, c2, c3); // 72 73 33 (casting)
}
```



- We can explicitly convert, or cast, each character to an int before we use it, with `(int) c1`, but our compiler can implicitly do that for us.

- And in memory, we might have three boxes, labeled `c1`, `c2`, and `c3` somehow, each of which representing a byte of binary with the values of each variable.

  

  

  

  

- It turns out, in memory, we can store variables one after another, back-to-back. And in C, a list of variables stored, one after another in a contiguous chunk of memory, is called an **array**.

- For example, we can use `int scores[3];` to declare an array of 3 integers.

  And we can assign and use variables in an array with:

  ```c
  #include <cs50.h>
  #include <stdio.h>
  
  int main(void)
  {
      // Scores
      int scores[3];
      scores[0] = 72;
      scores[1] = 73;
      scores[2] = 33;
  
      // Print average
      printf("Average: %i\n", (scores[0] + scores[1] + scores[2]) / 3);
  }
  ```

  And we repeated the value 3, representing the length of our array, in two different places. So we can use a constant, or fixed value, to indicate it should always be the same in both places:

  ```c
  #include <cs50.h>
  #include <stdio.h>
  
  const int N = 3;
  // don't change var 
  
  int main(void)
  {
      // Scores
      int scores[N] = {72, 73, 33}
      // Print average
      printf("Average: %i\n", (scores[0] + scores[1] + scores[2]) / N);
  }
  ```

  - We can use the `const` keyword to tell the compiler that the value of `N` should never be changed by our program. And by convention, we’ll place our declaration of the variable outside of the `main` function and capitalize its name, which isn’t necessary for the compiler but shows other humans that this variable is a constant and makes it easy to see from the start.

- 

  With an array, we can collect our scores in a loop, and access them later in a loop, too:

  ```
  #include <cs50.h>
  #include <stdio.h>
  
  float average(int length, int array[]);
  
  int main(void)
  {
      // Get number of scores
      int n = get_int("Scores:  ");
  
      // Get scores
      int scores[n];
      for (int i = 0; i < n; i++)
      {
          scores[i] = get_int("Score %i: ", i + 1);
      }
  
      // Print average
      printf("Average: %.1f\n", average(n, scores));
  }
  
  float average(int length, int array[])
  {
      int sum = 0;
      for (int i = 0; i < length; i++)
      {
          sum += array[i];
      }
      return (float) sum / (float) length;
  }
  ```

  - First, we’ll ask the user for the number of scores they have, create an array with enough `int`s for the number of scores they have, and use a loop to collect all the scores.
  - Then we’ll write a helper function, `average`, to return a `float`, or a decimal value. We’ll pass in the length and an array of `int`s (which could be any size), and use another loop inside our helper function to add up the values into a sum. We use `(float)` to cast both `sum` and `length` into floats, so the result we get from dividing the two is also a float.
  - Finally, when we print the result we get, we use `%.1f` to show just one place after the decimal.

- In memory, our array is now stored like this, where each value takes up not one but four bytes:
  ![grid with 72 labeled score1, 73 labeled score2, 33 labeled score3, each of which takes up four boxes, and many empty boxes following](https://cs50.harvard.edu/x/2020/notes/2/memory_with_array.png)

## [Strings](https://cs50.harvard.edu/x/2020/notes/2/#strings)

- Strings are actually just arrays of characters. If we had a string `s`, each character can be accessed with `s[0]`, `s[1]`, and so on.

- And it turns out that a string ends with a special character, ‘\0’, or a byte with all bits set to 0. This character is called the null character, or null terminating character. So we actually need four bytes to store our string “HI!”:
  ![grid with H labeled s[0], I labeled s[1], ! labeled s[2], \0 labeled s[3], each of which takes up one box, and many empty boxes following](https://cs50.harvard.edu/x/2020/notes/2/memory_with_string.png)

- 

  Now let’s see what four strings in an array might look like:

  ```
  string names[4];
  names[0] = "EMMA";
  names[1] = "RODRIGO";
  names[2] = "BRIAN";
  names[3] = "DAVID";
  
  printf("%s\n", names[0]);
  printf("%c%c%c%c\n", names[0][0], names[0][1], names[0][2], names[0][3]);
  ```

  - We can print the first value in `names` as a string, or we can get the first string, and get each individual character in that string by using `[]` again. (We can think of it as `(names[0])[0]`, though we don’t need the parentheses.)
  - And though we know that the first name had four characters, `printf` probably used a loop to look at each character in the string, printing them one at a time until it reached the null character that marks the end of the string. And in fact, we can print `names[0][4]` as an `int` with `%i`, and see a `0` being printed.

- We can visualize each character with its own label in memory:
  ![grid with E labeled names[0][0], M labeled names[0][1], and so on, until names[3][5] with a \0, each of which takes up one box, and empty boxes following](https://cs50.harvard.edu/x/2020/notes/2/memory_with_string_array.png)

- 

  We can try experimenting with

   

  ```
  string0.c
  ```

  :

  ```
  #include <cs50.h>
  #include <stdio.h>
  #include <string.h>
  
  int main(void)
  {
      string s = get_string("Input:  ");
      printf("Output: ");
      for (int i = 0; i < strlen(s); i++)
      {
          printf("%c", s[i]);
      }
      printf("\n");
  }
  ```

  - We can use the condition `s[i] != '\0'`, where we can check the current character and only print it if it’s not the null character.
  - We can also use the length of the string, but first, we need a new library, `string.h`, for `strlen`, which tells us the length of a string.

- 

  We can improve the design of our program.

   

  ```
  string0
  ```

   

  was a bit inefficient, since we check the length of the string, after each character is printed, in our condition. But since the length of the string doesn’t change, we can check the length of the string once:

  ```
  #include <cs50.h>
  #include <stdio.h>
  #include <string.h>
  
  int main(void)
  {
      string s = get_string("Input: ");
      printf("Output:\n");
      for (int i = 0, n = strlen(s); i < n; i++)
      {
          printf("%c\n", s[i]);
      }
  }
  ```

  - Now, at the start of our loop, we initialize both an `i` and `n` variable, and remember the length of our string in `n`. Then, we can check the values each time, without having to actually calculate the length of the string.
  - And we did need to use a little more memory for `n`, but this saves us some time with not having to check the length of the string each time.

- 

  We can now combine what we’ve seen, to write a program that can capitalize letters:

  ```
  #include <cs50.h>
  #include <stdio.h>
  #include <string.h>
  
  int main(void)
  {
      string s = get_string("Before: ");
      printf("After:  ");
      for (int i = 0, n = strlen(s); i < n; i++)
      {
          if (s[i] >= 'a' && s[i] <= 'z')
          {
              printf("%c", s[i] - 32);
          }
          else
          {
              printf("%c", s[i]);
          }
      }
      printf("\n");
  }
  ```

  - First, we get a string `s`. Then, for each character in the string, if it’s lowercase (its value is between that of `a` and `z`), we convert it to uppercase. Otherwise, we just print it.
  - We can convert a lowercase letter to its uppercase equivalent, by subtracting the difference between their ASCII values. (We know that lowercase letters have a higher ASCII value than uppercase letters, and the difference is conveniently the same between the same letters, so we can subtract that difference to get an uppercase letter from a lowercase letter.)

- 

  We can use the

   

  **man pages**

  , or programmer’s manual, to find library functions that we can use to accomplish the same thing:

  ```
  #include <cs50.h>
  #include <ctype.h>
  #include <stdio.h>
  #include <string.h>
  
  int main(void)
  {
      string s = get_string("Before: ");
      printf("After:  ");
      for (int i = 0, n = strlen(s); i < n; i++)
      {
          printf("%c", toupper(s[i]));
      }
      printf("\n");
  }
  ```

  - From searching the man pages, we see `toupper()` is a function, among others, from a library called `ctype`, that we can use.

## [Command-line arguments](https://cs50.harvard.edu/x/2020/notes/2/#command-line-arguments)

- We’ve used programs like `make` and `clang`, which take in extra words after their name in the command line. It turns out that programs of our own, can also take in **command-line arguments**.

- 

  In

   

  ```
  argv.c
  ```

  , we change what our

   

  ```
  main
  ```

   

  function looks like:

  ```
  #include <cs50.h>
  #include <stdio.h>
  
  int main(int argc, string argv[])
  {
      if (argc == 2)
      {
          printf("hello, %s\n", argv[1]);
      }
      else
      {
          printf("hello, world\n");
      }
  }
  ```

  - `argc` and `argv` are two variables that our `main` function will now get, when our program is run from the command line. `argc` is the argument count, or number of arguments, and `argv` is an array of strings that are the arguments. And the first argument, `argv[0]`, is the name of our program (the first word typed, like `./hello`). In this example, we check if we have two arguments, and print out the second one if so.
  - For example, if we run `./argv David`, we’ll get `hello, David` printed, since we typed in `David` as the second word in our command.

- 

  It turns out that we can indicate errors in our program by returning a value from our

   

  ```
  main
  ```

   

  function (as implied by the

   

  ```
  int
  ```

   

  before our

   

  ```
  main
  ```

   

  function). By default, our

   

  ```
  main
  ```

   

  function returns

   

  ```
  0
  ```

   

  to indicate nothing went wrong, but we can write a program to return a different value:

  ```
  #include <cs50.h>
  #include <stdio.h>
  
  int main(int argc, string argv[])
  {
      if (argc != 2)
      {
          printf("missing command-line argument\n");
          return 1;
      }
      printf("hello, %s\n", argv[1]);
      return 0;
  }
  ```

  - The return value of `main` in our program is called an exit code.

- As we write more complex programs, error codes like this can help us determine what went wrong, even if it’s not visible or meaningful to the user

## [Readability](https://cs50.harvard.edu/x/2020/notes/2/#readability)

- Now that we know how to work with strings in our programs, we can analyze paragraphs of text for their level of readability, based on factors like how long and complicated the words and sentences are.

## [Encryption](https://cs50.harvard.edu/x/2020/notes/2/#encryption)

- If we wanted to send a message to someone, we might want to **encrypt**, or somehow scramble that message so that it would be hard for others to read. The original message, or input to our algorithm, is called **plaintext**, and the encrypted message, or output, is called **ciphertext**.
- A message like `HI!` could be converted to ASCII, `72 73 33`. But anyone would be able to convert that back to letters.
- An encryption algorithm generally requires another input, in addition to the plaintext. A **key** is needed, and sometimes it is simply a number, that is kept secret. With the key, plaintext can be converted, via some algorith, to ciphertext, and vice versa.
- For example, if we wanted to send a message like `I  L O V E  Y O U`, we can first convert it to ASCII: `73  76 79 86 69  89 79 85`. Then, we can encrypt it with a key of just `1` and a simple algorithm, where we just add the key to each value: `74  77 80 87 70  90 80 86`. Then, someone converting that ASCII back to text will see `J  M P W F  Z P V`. To decrypt this, someone will need to know the key.
- We’ll apply these concepts in our problem set!
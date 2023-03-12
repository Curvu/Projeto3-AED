# Random Infraction Input Generator
This C program generates random data for a fictional database. The data includes a matricula (a unique identifier), an infracao (an infraction type), a num (the severity of the infraction on a scale of 1-5), and a name (the name of the person who committed the infraction).

## Usage
To use this program, simply compile the code and run it in your terminal with an argument that represents the number of entries you want to generate. For example, if you want to generate 10 entries, you would run:

```bash
gcc gerador.c -o gerador && ./gerador 10 > inputs.txt
```

The program will then output the random data in the following format:

```bash
DIM_BD [number of entries]
[matricula] [infracao] [num] [name]
[matricula] [infracao] [num] [name]
[matricula] [infracao] [num] [name]
...
TCHAU
```

Then, you can use the output file to test your database program like so:

```bash
gcc main.c -o main && ./main < inputs.txt
```

You can also add some lines of code to the program to print the time it takes to sort the data. To do this:
```c
#include <time.h>
```
Then, add the following lines of code to the main function:
```c
clock_t start = clock();
// call your sorting function here
clock_t end = clock();
double time = (double) (end - start) / CLOCKS_PER_SEC;
printf("SORT NAME\n");
printf("DIM_BD: %d\n", dim);
printf("TIME: %f\n", time);
```

This will print the time it takes to sort the data. You can also print that time to a file by adding
```bash
./main < inputs.txt > output.txt
```

## Input Generation
This program generates random data using four functions:

generate_matricula(): Generates a random matricula consisting of 6 characters, including uppercase letters and digits.
* generate_infracao(): Generates a random infracao from a list of 5 possible infracoes.
* generate_num(): Generates a random num from 1-5.
* generate_name(): Generates a random name from a list of 5 possible names.

The program uses the srand() function to seed the random number generator with the current time. This ensures that each time the program is run, the random data generated is different.

## Contributing
Feel free to use this code in your own projects. If you have any suggestions for improvements, feel free to open an issue or pull request.
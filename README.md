# Sorting in C

Sorting in C is a simple utility program for sorting numbers written entirely in C. Default sorting algortihm is Quick Sort but following sorting algortihms can be used:
1. Insertion Sort
2. Bubble Sort
3. Selection Sort
4. Merge Sort
5. Heap Sort
6. Counting Sort
7. Radix Sort
8. Bucket Sort
9. Bingo Sort
10. Shell Sort
11. Tim Sort
12. Comb Sort
13. Pigeonhole Sort
14. Cycle Sort
15. Cocktail Sort
16. Bitonic Sort
17. Pancake Sort
18. Bingo Sort
19. Gnome Sort
    

## Installation

To build the project use:

```bash
./build.sh
```

## Usage
**Generate a file with 10000 numbers and shuffle them**
```c
mySort -g original.txt  original_shuf.txt 10000
```
*The maximum amount of numbers that can be genereted is restricted to 80% of available memory*

*Shuffling uses an algorithm to make sure <1% of numbers are consective*

**Sort the shuffled file using Insertion Sort**
```c
mySort -s insertion original_shuf.txt  original_sorted.txt
```
*For more commands consult man page*

## Man
The utility comes with a man page that can be accessed with:
```c
mySort --help
```
![man](https://github.com/Dimagreg/Sorting-in-C/assets/73190746/ea672a31-d99e-4cae-962b-98f2f86a55ff)

## STATS
By default, STATS option is turned on which will approximate the time required to sort the file using a certain sorting algorithm

To modify STATS/DEBUG values consult **/main.c**

![image](https://github.com/Dimagreg/Sorting-in-C/assets/73190746/119f61e8-021b-4382-a99c-f59689cfe0bb)

*NOTE! It becomes innacurate as you increase the amount of numbers to be sorted*

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[GNU](https://www.gnu.org/licenses/gpl-3.0.en.html)

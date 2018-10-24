This assignment asks you to check the solution to a maze. You will be given an
input file containing a maze, which has walls, a starting point, and an ending
point, and a second input file containing a proposed path through the maze.
Your job is to write a program that will determine whether the proposed path
is *legal*: whether it reaches the end point while a) staying within the
bounds of the maze; b) not running into any walls; and c) not looping back on
itself.

Learning Goals
==============

You will learn:

* Enumerations
* Nested structures
* 2D arrays

Background
==========

Enumerations
------------

An enumeration data type specifies a set of constant (integer) values that are
all distinct. You can either set the constant values yourself:

```
typedef enum Month {
  JANUARY = 1,
  FEBRUARY = 2,
  MARCH = 3,
  APRIL = 4,
  MAY = 5,
  JUNE = 6,
  JULY = 7,
  AUGUST = 8,
  SEPTEMBER = 9,
  OCTOBER = 10,
  NOVEMBER = 11,
  DECEMBER = 12
} Month;
```

Or you can let the compiler choose the values for you:

```
typedef enum Day {
  SUNDAY,
  MONDAY,
  TUESAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} Day;
```

(Note that by convention we make the constants in the enumeration ALL CAPS)

You can then use these values as constants throughout your program. If you
define a variable as having an enumeration type, you're saying that you want
its values to be restricted to those constants:

`Month birthmonth = AUGUST;`

Enumerations are a convenient way of defining a set of constants that are
related to each other. This will let us use specific constants throughout our
program without having to change all of them if we decide to change the values
of the constants.

In this assignment, we are using two enumerations. The first defines the
"types" of maze squares: a wall, an empty space, the starting point, and the
ending point:

```
typedef enum SquareType {
	WALL = '#',
	SPACE = '.',
	START = 's',
	END = 'e'
} SquareType;
```

(Note that we're taking advantage of the fact that C treats characters as
integers of the appropriate ASCII value). 

Throughout your code, when you want to see whether a particular value is a
wall, you should test if it is equal to `WALL`, not `#`. That way, if we later
want to change what walls look like in our maze, it will be easy.

The second enumeration defines the possible directions you can move in your
path:

```
typedef enum PathType {
	NORTH = 'n',
	SOUTH = 's',
	EAST = 'e',
	WEST = 'w'
} PathType;
```

Complex Structures
------------------

Up until now, we have mostly dealt with structures whose fields are simple
data types or arrays. But we can also have the fields of a structure be
*another type* like a structure or an enumeration. Consider the types we will
use to define our maze:

```
typedef struct MazeSquare {
	SquareType type;
	bool visited;
} MazeSquare;
```

This is a structure that represents a single square in the maze. It has a
particular type (using the enumeration type from above), and a flag that lets
us know whether we've visited this square before or not (useful for checking
if your path has loops).

```
typedef struct MazePos {
	int xpos;
	int ypos;
} MazePos;
```

This is a simple structure that captures the location of a particular square
in a maze.

```
typedef struct Maze {
	MazeSquare * * maze; //2D array holding maze
	int width; //Number of columns in maze
	int height; //Number of rows in maze
	MazePos start; //Location of 's'
	MazePos end; //Location of 'e'
} Maze;
```

This structure represents an entire maze. It has a width and height, it uses
the `MazePos` structure to capture the starting position in the maze and the
ending position in the maze, and it uses a *2D Array* of `MazeSquare`s to
represent the maze grid itself.

2D Arrays
---------

What are two-dimensional arrays? If you know how many rows and columns you
want your array to have, you can define a 2D array easily:

```
float matrix[10][20]; //a 10x20 matrix
```

But what if you don't know how many rows and columns you need? We'll have to
use *dynamic memory allocation*, just like we did when we needed arrays of
unknown size.

To allocate a 2D array, we will build an *array of arrays*. We will have an
array (representing the rows of the 2D array) where each element of the array
is *another array*. Allocating 2D arrays is tricky, since we don't know how
many rows and columns we need. We have to do it in two steps.

First, we allocate the array of rows. Because each entry needs to be an array
of floats itself, the type of this array is a *pointer to a pointer to a float*:

```
float * * matrix = malloc(nrows * sizeof(float *));
```

This creates an array of `nrows` pointers to floats. Second, for *each of those pointers* we allocate an array of floats:

```
for (int i = 0; i < nrows; i++) {
  matrix[i] = malloc(ncols * sizeof(float));
}
```

We can now use `matrix` as a normal 2D array. To access the 2nd row and 5th
column, we can write `matrix[1][4]`.

Freeing a 2D Array
------------------

To deallocate a 2D array, we reverse the steps. First, we free each of the
column arrays, then we free the row array.

```
for (int i = 0; i < nrows; i++) {
  free(matrix[i]);
}
free(matrix);
```

Note that we can't do this in the other order! If we `free(matrix)` first, we
will have no way of getting the addresses of the column arrays we need to
free.

2D Array Coordinates vs. Cartesian Coordinates
----------------------------------------------

Note that 2D arrays (and matrices) work very differently than Cartesian
coordinates. Suppose you have a 2D grid of letters:

```
a b c d
e f g h
i j k l
```

Then your 2D grid has 4 columns (width = 4) and 3 rows (height = 3) You should
thus create a 2D array with 3 rows and 4 columns (note that with arrays we
list the rows first, then the columns).

The coordinate system we use for 2D arrays (and matrices) is different than
Cartesian coordinates.

In Cartesian coordinates, `(0, 0)` is at the bottom left of the grid (the
letter 'i'). In 2D arrays (and matrices), `[0][0]` is at the top left of the
grid (the letter 'a').

In Cartesian coordinates, we list the x position first and then the y
position. For 2D arrays (and matrices), we list the y position (the row) first
and then the x position (the column).

In Cartesian coordinates, incrementing the "y" position moves *up*. In 2D
arrays (and matrices), incrementing the row number moves *down* (the first row
is row 0, the second row is row 1, etc.).

So in Cartesian coordinates, `(2, 3)` would represent the letter 'b', but in
2D arrays, `[2][3]` would represent the letter 'g'.

What do you need to do?
=======================

We have provided `pa07.c`, `maze.h` and `path.h` for you. You will need to
fill in `maze.c` and `path.c` with the functions specified. 

* `maze.c` has two functions: `readMaze`, which reads in the maze data from an
  input file and builds a Maze structure (don't forget to initialize the
  starting and ending positions!) and `freeMaze` which deallocates the 2D
  array holding the maze.
* `path.c` has two functions: `readPath`, which reads the proposed solution
  from an input file, and `checkPath`, which returns `true` if the proposed
  path works, and `false` if it doesn't.

To check a path, create a cursor that starts at the starting position of the
maze (the coordinates of the square with value `s`). Follow the directions of
the path (`n` to move up in the maze, `e` to move right, and so on). If the
path *ever* tries to move into a square that is a wall, or tries to move out
of the boundaries of the maze, or tries to move to a square it has already
visited, the solution is *incorrect* and you should return false.

If a path makes it to the end square of the maze (the square marked `e`), the
solution is *correct* and you should return true, *even if there are more
steps in the path.*

Testing your code
-----------------

We have provided one simple maze to get you started, in `inputs/maze1`, as
well as three candidate solutions: `inputs/path1`, which is a correct
solution, `inputs/path1-bad1` which is an incorrect solution because it hits a
wall, and `inputs/path1-bad2` which is an incorrect solution because it never
makes it to the end.

We will release additional mazes throughout the week. Keep an eye on Piazza!
(Generating your own test cases and sharing them on Piazza is a good way to
get class participation points!)

To help you write and test your code, there are *compiled* versions of
[`maze.o`](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa07/maze.o)
and
[`path.o`](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa07/path.o)
that you can build against (e.g., you can write your `path.c` functions and
test them by making sure they work when compiled with our `maze.o` and vice
versa). To use these files *you will need to test on ecegrid machines*.
This assignment takes
[PA07](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa07/)
one step further. Rather than just *checking* the solution to a Maze, this
assignment asks you to *discover* the solution to a maze (if one exists). You
will build on the methods you developed in PA07 (though, as usual, we will
provide files that you may use if you don't have a working version of PA07).

Learning Goals
==============

You will learn:

* More recursion
* Depth first search

Background
==========

Depth first search
------------------

*Depth first search* is one of the most common search strategies and it is one
that lends itself to recursion. Suppose you are standing in the middle of a
maze (sort of like you are in this assignment!) and want to figure out where
the exit is. How might you find your way out?

Here is one strategy: start walking through the maze. Each time you arrive at
a choice of directions, pick one and keep walking. If you reach a dead end, or
get to a part of the maze you've seen before, back up to the last place you
made a choice and make a different one. Eventually, you will either find the
exit of the maze or explore the entire maze and decide that there is no way
out.

Consider trying to find your way out of this maze:

```
.#.#
...#
e#..
#s.#
```

Assume that at each square, we try to go north, then south, then east, then
west.

We start at `s`, and try to go N. We hit a wall, so we back up and try to go
S. We go out of bounds, so we try to go E, which succeeds. We're now in this
situation, where the `*` shows where we are:

```
.#.#
...#
e#..
#s*#
```

We try to go N, which succeeds. We try to go N again, which succeeds. We try
to go N again, which succeeds. We're now in this situation:

```
.#*#
...#
e#..
#s.#
```

We try to go N again, which fails (out of bounds). We try to go S, which fails
(we've already been to that square!), E, which fails (we hit a wall), then W,
which fails (we hit a wall). Since we don't have anywhere to go from here, we
back up to the last place we made a choice:

```
.#.#
..*#
e#..
#s.#
```

Now we try to go N (fails: already been to that square); S (fails: already
been to that square); E (fails: wall); then W (succeeds):

```
.#.#
.*.#
e#..
#s.#
```

Now we try to go N (fails: wall); S (fails: wall); E (fails: already been
there); and W (succeeds):

```
.#.#
*..#
e#..
#s.#
```

We then go N, which succeeds:

```
*#.#
...#
e#..
#s.#
```

From here, there is no successful move to make, so we back up to the last place we made a choice:

```
.#.#
*..#
e#..
#s.#
```

and try the next choice, S, which gets us to the exit!

The reason we call this a depth-first search is that we try each possible path
until we can't keep moving forward, then we back up one choice and try again,
and so forth. Other searches may not explore a single path all the way to the
end before trying a different path.

Depth First Search with Recursion
---------------------------------

Depth first search can be readily solved with recursion. Each recursive call
"visits" a single square in the maze and explores each of the possible paths
leading out from that square. The goal of a sequence of recursive calls is to
explore a specific path through the maze, and each time you call the recursive
function, you're making the path one step longer and visiting one more square
of the maze.

You should interpret your recursive function as implementing the following
logic: "Given all the squares I have visited so far, can I exit the maze by
adding this square to the solution path?"" If the answer is no, that means the
current square is not part of the solution path, and the recursive method
should return false. If the answer is yes, that means the current square *is*
part of the solution path, and you should add the square to the current path
and return true.

The *base case* for a square is that the square represents the *end* of a
path:

1. It has been visited already -- the path can't be extended this way, so return false
2. It is a wall -- this path fails, so return false.
3. It is out of bounds -- this path fails, so return false.
4. It is the exit -- this path succeeds, so return true and add this square as 
  the last square in the path

The *recursive* case for a square is that it doesn't fall into one of the
above four categories: it is an empty square that you haven't visited before.
In that case, the recursive case tries to make the path one step longer by
visiting one more square in the maze: recursively call your search method
*four times*, once for each of the four directions you could possibly move.

So what do you do with the return value of the four recursive calls you make?

1. If one of them returns true, that means the direction that call explores is on the solution path, which also means the *current* square is on the    solution path. Add the current square to the solution path, and return true.
2. If the recursive call returns false, that means that direction doesn't 
  work, so move on to the next recursive call.
3. If *all* the recursive calls return false, that means the *current* square 
  can't be on the solution path, so return false.
  
(Don't forget to mark the current square as visited when the recursive method
returns!)

Note that this recursive function follows the usual pattern: it calls itself
and *assumes those calls do the right thing*.

What do you need to do?
=======================

In this assignment, you only need to write *one method*, `depthFirstSolve` in
`solver.c`. `depthFirstSolve` is called by `solveMaze`, as you can see in the
code, and is meant to be the recursive method that implements the logic
described above. It takes four arguments:

1. `Maze * m`: the maze you are trying to solve.
2. `MazePos curPos`: the current square in the maze being "visited."
3. `char * path`: a character array containing the current path. This path 
  should match the format of the path from PA07 (i.e., it should be a 
  null-terminated string with a sequence of directions to move).
4. `int step`: a counter telling you how far along the current path you are.

and returns a boolean: `true` means that the current square being visited by
`depthFirstSolve` *is* part of the solution, and `false` means that current
square *is not* part of the solution.

One tricky bit here is figuring out how to update `path` correctly. Two hints:
(i) `step` tells you how far along in the current path you are; and (ii) if
you successfully exit the maze on the `n`th step, `path[n]` should be `\0`.

**Warning:** Don't be misled by the fact that you only have to write one
method. This assignment will probably have the highest ratio of *time spent thinking about what code to write* to *amount of code written* of any
assignment so far. Recursive code is often quite short -- the instructors'
version of `depthFirstSolve` has about 25 lines of code -- but takes a while
to get right. Start thinking about your solution now, and don't be afraid to
ask questions on Piazza or in office hours to make sure your logic is right.

Testing your code
-----------------

You can use your own version of maze.c (with `readMaze` and `freeMaze`) if you
would like, or you can use our [compiled
version](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa07/maze.o).
You will also need a version of path.c (with `writePath` working), or you can
use our [compiled
version](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa07/path.o).
As usual, if you use our compiled versions of the code, you will need to
develop your code on the ecegrid machines.

Depending on the order you choose to do your recursion (do you decide to look
North first, or South first, etc) you can get a different path than someone
else if a maze has many paths to the exit! How can you test if your path is correct?
You have already developed a path checker in PA07, so you can use that
to verify if the path you create in PA08 is valid. We will provide a [fully
linked version](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa07/pa07)
of PA07 that you can use if you didn't finish the previous assignment. We will
also provide the source code of PA07 on the morning of 3/2 if you wish to
compile it yourself. It's recommended that you look at the source code of
PA07 even if you finished it to learn how we broke up the problem into smaller
parts, as it may help your thought process in PA08.

We have provided several mazes for you. `maze1`, `maze3` and `maze4` have
valid solutions, while `maze2` and `maze5` do not.

What do you need to turn in?
----------------------------

Turn in your version of `solver.c`, with your implementation of
`depthFirstSolve`. You do not need to submit any other files.


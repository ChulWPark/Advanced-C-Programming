In
[PA08](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa08/)
you build a solver for mazes that returned the *first* solution to the maze.
In this assignment, you will instead return *all* valid solutions to the maze.
Because we don't know how many solutions there are for the maze, we will use a
linked list structure to store all of the solutions (see
[PA09](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa09/)
for more about linked lists). 

We don't want to just store all of the paths, though. We want to order them so that the "best" path is first. We want to keep the paths in a *sorted* list. Paths should be sorted in ascending order, according to the following rules:

1. Shorter paths come before longer paths
2. If two paths are the same length, the path with fewer "turns" should be 
   before the path with more turns (a turn is when a path changes direction: 
   `eenn` has one turn, `eene` has two turns)
3. If two paths are the same length *and* have the same number of turns, sort 
   in alphabetical order.


# Learning Goals

You will learn 
* Building a sorted linked list
* Incremental, test-driven development

# Background

## Sorted Linked Lists

In
[PA09](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa09/)
we gave you a linked list implementation that allowed you to insert new nodes
into a particular *index* of the linked list (e.g., "add a new node at
position 15"). Now you instead want to write a linked list that will maintain
all of its nodes in sorted order. The key to writing a sorted linked list is
to maintain the *invariant* that the list is always sorted after you perform
any operation (e.g., insert, remove) on it. We can think about this inductively:

1. An empty list is, by definition, sorted.
2. If you have a sorted list, and you insert a new node *into the correct location* (i.e., between the largest node that is smaller and the smallest node that is larger), the list will still be sorted.
3. If you have a sorted list and you remove a node, the list will remain sorted.

(We gave you the rules for ordering a linked list of paths above)

`list.h` defines a linked list class that works a little bit differently than
the one in PA09. The `head` pointer is contained as a field of a structure
that represents the linked list. It provides several helper methods to
allocate/initialize and deallocate individual linked list nodes (`PathNode`s)
or the linked list as a whole (`PathLL`). It also provides 3 key methods:

* `addNode`, which inserts a new path into the linked list. *Make sure this  keeps the list sorted!* `addNode` returns true if the addition succeeds, and false if it fails (which can happen if the path you are trying to add is already in the linked list -- this is a good way to tell if you're accidentally finding the same path twice).
* `removeNode`, which removes a particular path from the linked list. It returns true if the remove succeeds, and false if it fails (which can happen if the path you are trying to remove *isn't in the linked list*).
* `containsNode`, which checks if a path is in the linked list.

## Incremental development

When presented with a big development challenge, it is tempting to try to write all of your code and then see if it works. This is a path to frustrating bugs and possible failure. What you should do instead is:

1. Break the problem down into manageable chunks
2. Write code to solve each chunk
3. *Test* each chunk to make sure it works correctly before moving on to the next chunk.

This has several benefits: (i) it is a lot more manageable to think of a big
project in terms of a lot of smaller steps you have to get done; (ii) because
you test each step before moving on to the next one, you know that if
something breaks, it must be either part of the last step, or because of some
interaction between your chunks -- you don't have to search through all of
your code.

For example, here is a proposed development plan for this programming assignment:

1. Implement a small function that compares two paths according to the criteria above, to make sure that you can sort paths correctly.
2. Implement your linked list, and test adding, removing, and finding paths in the linked list.
3. Use your *now working* linked list to implement the new solver.

Note that the key here is to *test every piece of your code*. This is called
**test driven development**. When you implement a chunk of code, you should
write a test file -- another `.c` file that has its own `main` function. You
can compile your new code with this test file to test the functionality of
your chunk.

Another aspect of test-driven development is to make sure that your program
passes simple test cases first, before moving on to complex test cases. If
your solver fails on a 10x10 maze, it may be hard to tell what's going on. If
your solver fails on a 2x2 maze, it's often much easier to debug.

# What you need to do

There are two things you need to do.

## Build and test your linked list

Fill in and *test* the linked list methods, including making sure that you can
insert, remove, and find paths in your linked list. *We will test your linked list implementation separately from the maze solver*. Even if you do not use a
particular linked list method in `depthFirstSolve`, make sure you implement
it.

## Build and test your updated maze solver

We have provided almost all of the code you need, other than the linked list
methods themselves. The one missing piece is `depthFirstSolve` in `solver.c`.
This needs to be modified so that when you find a solution to the maze, rather
than returning that solution you just add the solution to the maze and keep
going. (Make sure you keep track of `visited` correctly: a MazeSquare should
count as visited if the *current* path you are exploring has visited that
square, not if *any* path has visited that square in the past.)

You can start with a version of [`solver.c`](solver.c) that solves PA08.

We have provided you with a few test mazes, in the `inputs` directory. You should also write more of your own.

## What you need to submit

1. Submit your version of `list.c` that contains *working implementations of all the functions*. 
2. Submit your version of `solver.c` that generates all the solutions to a 
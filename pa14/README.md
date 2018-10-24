This assignment builds on
[PA13](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa13/),
creating a *multithreaded* filter function that can process an image in
parallel, speeding up the processing step.

Modern computers have multiple cores: different processing units that are
capable of executing independent streams of instructions. Much of the time,
those multiple cores are used to run different programs (e.g., running your
web browser at the same time as your music player), but another use of
multiple cores is to split up the work of a *single program* to speed up its
completion. 

In this assignment, we will modify our filtering routine from
[PA13](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa13/)
to process the image in parallel, using multiple *threads* to each process a
different portion of the image. In this way, we will be able to apply filters
to images faster.

*This assignment is a bonus assignment. It is extra credit.*

Learning Goals
==============

In this assignment, you will learn

* Basics of multithreaded programming

Background
==========

This is an *extremely* light background on parallel programming. For more
about threads and executing programs in parallel, you will have to take
courses like ECE 469 and ECE 563.

Threads
-------

Threads are separate *execution contexts* for a program: each thread exists
as, essentially, a separate stream of instructions from the program. Different
threads can be executing code from different parts of the program at the same
time. Threads can either give the impression of executing at the same time
(because your operating system switches quickly between which thread is
actually running its code) or can *actually* be executing at the same time
(because your computer has the resources to run multiple execution contexts
simultaneously -- and most modern computers, and even smartphones, do).

In some sense, you can think of threads as two different executions of the program, with two crucial differences:

1. Threads are executing different parts of the program, but typically do *different work* -- each thread will do a portion of the work required of the whole program. Consider a program that needs to process a million different records. One thread can process 500K of them, while a second thread can process a *different* 500K of them. Since the threads execute at the same time, the overall processing will complete faster.
2. Threads *share data*. Recall from
[PA02](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa02/)
that a program's memory can be divided up into, roughly, three separate
"segments": a `data` segment that holds global variables, a `stack` segment
that holds local variables for currently active function calls (i.e.,
functions that have not returned yet), and a `heap` segment that holds memory
that has been allocated using `malloc`. Every thread has its own `stack` segment (because each thread is executing its own set of functions), but the threads share the `data` and `heap` segments. This is how the two threads can get access to the 1 million different records in the example above.

> Note that in this assignment, we are mostly focused on using threads to
> execute code in parallel -- to make a program run faster. It is also
> common to use threads to improve *responsiveness*. One (or more) threads
> will perform the work of the program, while another thread will be
> responsible for interacting with the user (say, though the user interface).
> Here, again, the threads are responsible for different portions of a
> program's work, and rely on sharing data (so that the thread responsible
> for the UI can tell the worker threads what to do).

Creating threads
----------------

The library for creating threads in Linux is called *pthreads*. The key
structure in this library is the pthread structure, called `pthread_t`. Each
`pthread_t` stores the information needed to track a single thread's execution
(essentially, that thread's stack data and information about where exactly
that thread is in the program).

`pthread_t` is an *opaque* structure: you should create the structure (either
by creating a local variable of type `pthread_t` for each thread or by
allocating one or more `pthread_t` structures in an array), but *you* never
initialize the structure. You pass in the address of a `pthread_t` to the
various pthread library routines and let them manage it for you.

There are two key methods that we can use to create threads to execute work in parallel:

* `int pthread_create(pthread_t * thread, const pthread_attr_t * attr, void *(*start_routine)(void*), void * arg)`. This routine *creates* and *launches* a thread. 
  * `thread` the address of a the `pthread_t` structure to track the data of the thread. 
  * `attr` is a structure that sets some properties of the thread (we will always pass `NULL` for this argument).
  * `start_routine` is a function pointer to the function this thread will begin executing. This function always accepts a `void *` argument (this will usually be a pointer to a structure that contains multiple arguments for the routines), and returns a `void *`. (We will usually "return" data by setting a field of the structure we pass in as an argument)
  * `arg` is a pointer to the argument to pass to the start routine.

  Once `pthread_create` is executed, a new thread of execution begins running `start_routine` *in parallel* with the current program (which is, itself, a thread of execution). That means that `start_routine` will begin doing work while the current program continues on to its own next instruction.

* `int pthread_join(pthread_t thread, void ** value_ptr)`. Because a newly created thread runs in parallel with the current thread, we eventually need a way to say "wait for the new thread to finish its work before continuing on to do more work". This routine lets us do that. It (essentially) waits until `thread` finishes its work (returns from its `start_routine`) before returning. In this way, the thread that called `pthread_create` can (at some point in the future) wait for the thread it created to finish. `value_ptr` points to the return value of `start_routine`. If `thread` has already finished when `pthread_join` is called, the function returns immediately.

The basic model for writing a parallel program is then:

1. The main thread of execution (the one that starts the program) allocates a number of `pthread_t` structures, one for each worker thread.
2. The main thread calls `pthread_create` for each worker thread, passing in arguments to each threads `start_routine` that let the worker threads know what work to perform.
3. After all the worker threads are launched, the main thread calls `pthread_join` on each of the worker threads to wait for them all to finish their work.
4. The main thread then processes the result of doing the work.

[`example.c`](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa14/example.c)
is a simple example program that creates four threads, each of which adds up
the entries of a quarter of the elements of an input array, and then adds up
the four results to sum up the overall array.

Processing an image in parallel
-------------------------------

There are many ways to process an image in parallel, but fundamentally they
all rely on the same basic idea: the computation required to generate one
output pixel is *independent* of the computation required to generate another
output pixel. Two operations are independent of one another if neither writes
to a memory location that the other one reads or writes from. If two
operations are independent, it is safe to execute them in parallel -- it is
safe for two different threads to execute them! So the idea of processing an
image in parallel is to *give different threads different sets of pixels to process.*

> If we make sure that all threads do independent work, we know that our
> parallel execution will be work correctly. But it is not always possible to
> find ways to divide up work so that threads are always doing independent
> operations. Some times threads need to write to the same locations in memory
> or read data that other threads have written. To do this safely, we need to
> insert *synchronization* operations. We will not cover synchronization in
> this class, but ECE 469 does.

There are many different ways to divide up the pixels, but we suggest an easy
approach: divide the image up into chunks by rows. So if, for example, you
have 100 rows of pixels and two threads, the first thread will be responsible
for calculating all of the output pixels in rows 0-49, and the second thread
will be responsible for calculating all the output pixels in rows 50-99.
Nevertheless, you can divide up the output pixels any way you want. A few
things to keep in mind:

1. Each thread should have roughly the same number of output pixels to process. This way no one thread has a lot more work to do than another.
2. No pixel should be assigned to more than one thread -- otherwise your threads will not be doing independent work.
3. Every pixel should be assigned to one thread -- otherwise some of the work won't be done!

What you have to do
===================

Your job is to write a new set of filtering routines (in `filterParallel.c`)
that apply a box filter in parallel. You will be able to adapt your code from
PA13 to do this, but you will not be able to use it without modification. (You will need to reuse your `bmp.h` and `bmp.c` files from PA13.) 

There are two functions you have to define in `filterParallel.c`.

`void apply(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int numThreads)`: This is the function we will call to process your image. It has a slightly different interface than the `apply` function from last week's assignment: we pass the pointer to the output image as an argument, rather than returning it (assume that the pixel array and header for `imageOut` has already been constructed when we call it). Also, we pass in the number of threads.

The job of `apply` is to launch `numThreads` threads to collaboratively apply filter `f` to the image `imageIn` and write the results to `imageOut`. The function that each thread executes (i.e., the function you call in `pthread_create`) *must* be `applyThreadWrapper`, which prints a little bit of extra output that we will use to grade your program. `applyThreadWrapper` expects its argument to be a pointer to a structure of type `ApplyArgs` (defined in `filterParallel.h`) whose fields are mostly self-explanatory. The one field that may not be is `tid`. Think of this as a numerical identifier for your threads. You should number your threads from `0` to `numThreads-1`.

The overall structure of `apply` should mimic the outline of how to write a parallel program described above. You can look at [`example.c`](https://engineering.purdue.edu/~milind/ece264/2017spring/assignments/pa14/example.c) to get some ideas.

The second function you have to define is `applyThread`. This has a similar
interface to `apply`, except that it also accepts a thread number (`tid`).
This function should figure out which portion of the output image the current
thread is responsible for, and apply the box filter to produce those output
pixels.

*One important thing to note*: the `imageOut` pointer that each thread gets access to through `ApplyArgs` should all be the same: every thread is updating the *same* output image -- just different `Pixel`s within it.

What you have to submit
-----------------------

Submit `filterParallel.c` (and, if you have defined any new functions in it, `filterParallel.h`). We will use a working version of `bmp.c`, so you do not need to submit that.
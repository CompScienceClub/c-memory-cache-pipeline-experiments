# __Instruction Pipelining and Pre-computation in Neural Networks __ 

This is code accompanying a presentation for 
Computer Science Club given Sept. 8, 2016. 



## __Purpose__

The objective of this presentation and the included
code is to learn about and show the effects of 
cache, pipelining and compiler options on the speed
of the produced code.  Moreover, it is demonstration
of interfacing C and OCaml, with some examples that 
indicate the speed of various implementations of the 
same fundamental operation.

The code has to do with pipelining, caching and 
optimization, as well as an intro to compiling OCaml
with C routines.  The objective, of course, is to
produce more performant numeric routines while 
retaining our OCaml abstractions, generally in the
form of Bigarray types for numerically and data 
intensive problems.  Ruby and PHP examples are given that 
allows one to observe performance of an interpretted
language implementation.

The remainder of the presentation, the part that is 
about pre-computation in neural networks, does not
have code backing it at this time.



## __Requirements to build__

You will need a C compiler to build the first batch
of make targets having to do with diagnosing memory,
cache and processor performance.  OCaml must be installed
be able to build the examples having to do with writing
performant C functions for use in OCaml. To run the Ruby 
and PHP examples demonstrating how poorly interpretted
languages perform, you will need to have a Ruby and/or
PHP interpretter installed.



## __Make targets__

The following make targets are provided:

* cache_line_no_opt
* cache_line_opt
* cache_size
* pipeline_no_opt
* pipeline_opt
* pipeline2_no_opt
* pipeline2_opt
* thread
* ocaml_native
* ocaml_no_opt
* ocaml_opt
* clean

The first eight make targets have to do with caching and
pipelining.  You can use these to assess performance of 
your system and learn to understand the dynamics of the
processor, cache and main memory.  You may need to adjust 
some of the bounds if you have particularly large L3
cache.

The next three make targets are relevant to implementation
of tuned C code as extensions to OCaml.  The native 
build uses Array and is selected as such to be comparable
as an imperative implementation.  In a prior Meetup we 
discussed some of the differences between the functional
and imperative performance implications for OCaml.  The 
other two examples involve writing C for extending OCaml
and adding optimizations for performance.

Interpretted language examples are provided in /src/other
so that their performance is available to witness as well. 



## __Analysis__

Please see `/docs/performance.txt` for example output from 
the listed make targets for a 3.2GHz gen 4 i5 with PC1333
RAM, and a 1Ghz Raspberry Pi 2B+.  The results are MFLOPS 
for the primary arithmetic being performed, computed based
on the number of operations performed in the inner loop.  

You may find rather higher figures published by CPU 
manufacturers for their processors.  These are theoretical 
maximums based on ideal pipelining.  In practice most problems
do not admit these solutions and cannot take adequate 
advantage of them.  As well, the report here does not 
account for time spent on looping and other conditional logic.

The reporting in this analysis is naive, but it is more 
aligned with actual performance in actual scenarios.
Annotations are provided to explain some of the figures.  
It should be immediately obvious that the tuned compiled 
code gives a substantial performance advantage compared 
with all else, and that you should not even consider an 
interpretted language if you are interested in performance.  

# Coppersmith-Winograd-Algorithm
Trying to create a C interpretation for the Coppersmith-Winograd Algorithm, regarding NxN arrays. 


#### **First version**:
&nbsp;&nbsp;&nbsp;
Initial prototype rounds were of O(n!) complexity, able to calculate a max of n=18 arrays before crashing.


#### *Current Prototype*:
&nbsp;&nbsp;&nbsp;
Current complexity is O(~n^3), after implementing LU decomposition.


## **Goal**:
&nbsp;&nbsp;&nbsp;
Final target complexity is O(~n^2.374), which is the current best known complexity in theory for galactic algorithms.


#### *UPDATE*: 
&nbsp;&nbsp;&nbsp;
After implementing lower and upper triangular arrays, the algorithm is able to perform a maximum of n=~25 before crashing. Further research into the topic is needed

# **UPDATE 2**: 
&nbsp;&nbsp;&nbsp;
Completed implementation of LU Decomposition and re-organised definition of variables. Current maximum amount of N is ~250, since above that, the number returned for the value of its determinant is higher than the value IEEE754 supports. As such, further implementation will regard time management and theory upon this maximum N and iterated a lot of times to get a distinguishable result on time measurement between different solution implementation (see clock_t and chrono). Current complexity reached is calculated at n^3 at worst.  
&nbsp;&nbsp;&nbsp;
Will currently also pursue the implementation of the algorithm in multiplication of NxN arrays instead of just determinants. A scientific paper and report is now in writing and research and will be processed and posted here. Further arrangements are needed in the code for this to occur as well as junk clearance (compiler problems and IDE dissonances between the 2 parties caused this).

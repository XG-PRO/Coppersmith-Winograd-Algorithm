# Coppersmith-Winograd-Algorithm
Trying to create a C interpretation for the Coppersmith-Winograd Algorithm, regarding NxN arrays. 


Progress: 
Current prototype rounds are of O(n!) complexity, able to calculate a max of n=18 arrays before crashing.


Target:
Current complexity target is O(~n^3), after implementing LU decomposition


Goal:
Final target complexity is O(~n^2.374), which is the current best known complexity in theory for galactic algorithms.


UPDATE: After implementing lower and upper triangular arrays, the algorithm is able to perform a maximum of n=~25 before crashing. Further research into the topic is needed

# 15 Puzzle Solver
By Juliette Hainline and Forrest Sill

## Overview
We implemented the **[A* search algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm])**.

#### Data structures
1. A **priority queue** that contains boards that have not yet been tested.
1. A **vector** that contains all boards that have already been tested.

#### Algorithm
1. First, the inputted board is loaded into the priority queue.
1. All boards that could possibly result from a move on the original board (either 2, 3, or 4 boards, depending on whether the free space is on an edge, a corner, or neither) are loaded into the priority queue.
1. The original board is popped out of the priority queue added to the vector of already-tested boards.
1. This process repeats with the board at the top of the priority queue (that is, the board that has the lowest priority score, which means it is estimated to be the closest to the desired board configuration.)
1. This continues until the board at the top of the queue matches the desired board configuration.

#### Priority score

The priority score of a given board is a measure of how close the given board is to the desired configuration. It is calculated by adding the board's manhattan score with its hamming score. Its **manhattan score** is calculated by summing the distance from each block to its correct location using only horizonal and vertical moves. For example, a block that is in a location diagonal from its correct location would have a manhattan score of two. A board's **hamming score** is simply the number of blocks that are in the wrong location. For example, if the board is correct except for two blocks that are flipped, its hamming score would be two.

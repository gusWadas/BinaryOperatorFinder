# BinaryOperatorFinder
Evolutive method solution for finding binary logic tables for desired operations

This code is the work for the Evolutive Systems applied to Robotics in ICMC - USP São Carlos

To execute, run full.cpp.

## Objetive

To train a series of individuals through the evolutive method as to find a binary operator.

## Method

### Inputs
The input for each test in this case are the binary digits of a random number of type int with 8 bits, as well as its respective square root rounded down's binary digits. They are generate at each test by a function that can be substituted by others so the algorythm can find other binary operators

### Individuals

The individuals are each a logic table of binary values, created at random at the start of the program. When feed to the evaluation function along an input, they return 0 or 1 according to their logic. Those results are them used to score individuals

### Scoring

Since all output binaries have only 2 possible results (0 or 1), a single evaluation of a logic table and an input can be used to evaluate it for all the output binaries. To that end, a table of individuals x output digits stores 2 values: the amount of times an individual matched the result for that binary and the amount of times that individual was tested.

So that each individual, new or old, is tested for a good range of numbers, the number of tests used was around twice the total number of individuals per epoch.

### Evaluation and Selection

Instead of a single final metric of evaluation, the algorythm requires one solution for each digit, so instead of a general metric of guesses, it tracks the results of the individuals based on their explored probability of success for each output binary. This requires that for each output binary there be a number of individuals sufficiently high that by themselves they could train that binary alone, but with the benefit of the training being shared accross outputs.

Due to this sharing, while selecting a portion of individuals to be the top of each output (with the possibility of certain digits being seleted more than once), unless there's a great similarity between the outputs in general, there should be an inherent variety accross that portion of individuals. Compounding that to the fact that individuals with low scores after a suficient number of tests are unlikely to provide good results, we can focus on maintaining the portion of individuals with top probabilities for each output while eliminating a large part of the other individuals (in this case, 80%).

### Reproduction

To create new individuals, 4 strategies where applied, each covering for 1/4th of the eliminated individuals. The methods were:

* Top x Top 1-1 Crossbreeding without Mutation
* Top Mutation
* Top x Top 1-1 Crossbreeding with Mutation
* Top x Non-Top 3-1 Crossbreeding

x-y Crossbreeding takes x/(x+y) elements of the first individual and y/(x+y) elements of the second individual to create a new table. Since Non-top elements are more likely to have "mistakes" in their "genes", their portion when crossbreeding is smaller, but this shouldn't affect variety too much because of the vairety within the top due to the multiple targets.

Mutation on the other hand takes an indivual and changes 10% of its values according to the logic operator NOT (or 1-x). This is to avoid losing good genes during reproduction while still trying to instill better results in areas top individuals may be missing.

### Notes, Conclusions and Future Possibilities 

Through adjusting the number of individuals, training steps per epoch and epochs, it was observed an improvement when testing with random numbers.

(--- to add graph with top individuals scores per epoch and a graph with average number of tests per epoch ---)

It's important to notice that as results get closer and better, the less things they'll have to change and the more individuals with good results for a specific output will appear. This program is using a more simple reproduction and selection for processing purposes, but a more throughout process could focus on combining the best top individuals of each output with a corresponding individual that has a good balance between its output relative score and a certain amount of dissimilarity with the best individuals, allowing for a quicker convergence of partial good results in different parts of their tables. This is what I believe to be the best area in which to improve results from a production standpoint.

There's also the option to substitute individuals by probability matrixes, but that approach would need keener reproduction methods as combining individuals can provide far different results due to the intricate effects of different weights.

Another relevant point is that this method is quite expensive to process as the number of inputs gets higher, making it more difficult to process, but it's more acomodating of multiple outputs, allowing more easily for different operations to be explored in tandem and having similarities between them analized.

Overall, the biggest hidrance of this method to solve this problem and towards improving it is it's lack of a good middle metric to break the solution into smaller steps for simplification, as even 8 bits means 256 possible inputs. While it could be broken into steps that reduce the number of inputs of the next (such as convolutions and matrix multiplications), it would need to focus on solving each of them as separate problems simultaneously. For example, dividing it into steps that each reduce the next's output size by a ratio of 4:
- It would need 4 steps for 8 bits;
- At each step, the results for the respective step individuals would be generated and stored
- Each result would be used in the individuals of the next step
- Individuals would be tested accross multiple combinations for each input, on top of also being tested for each out
At a first glance this would heighten computation time per test, even if it would simplify it's structure in a way that it would promote it learning in chunks. And because of the risk of small alteration on individuals in earlier steps  cascading, afterwards, as well as badly adapted steps at any point biasing other steps, it makes it harder to justify testing it as an alternative even if it should be analyzed.

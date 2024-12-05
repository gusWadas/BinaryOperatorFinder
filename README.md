# BinaryOperatorFinder
Evolutive method solution for finding binary logic tables for desired operations

Run full.cpp to execute.

Test created for 8 bits int and square root rounded down operation.

Multiple tables are created at random (in this case 20 for each digit), tested for a number of randomly generated inputs and outputs pair. The top 5 individuals for each binary (possibly with repetition) are saved and 0% of the rest are removed, being substituted by an even spread of combination between top members without mutations, 3-to-1 ratio combinations between top members and non-top members, combination between top members with mutations and mutations of the top members.

This is repeated through multiple epochs with the operator being saved as the listing of top tables for each binary.

/*
 * Name: Daniel H. Endara Guarderas
 * Assignment: 1D Cellular Automaton (CA)
 * Description: This program simulates a 1D elementary cellular automaton.
 * It takes a rule set number (0-255) from the user, converts it to a
 * binary rule set array, initializes a starting generation, and computes
 * and displays 49 subsequent generations based on the rule set.
 */

#include <iostream>

const int GEN_LENGTH = 64;
const int NUM_GENERATIONS = 49;
const int RULE_SET_SIZE = 8;

// Converts a rule set decimal number (0-255) into its 8-element binary array representation.
void convertRuleSetNumberToRuleSetArray(int ruleSetNumber, int ruleSetArray[RULE_SET_SIZE])
{
    int remaining = ruleSetNumber;

    for (int i = 0; i < RULE_SET_SIZE; i++)
    {
        ruleSetArray[i] = remaining % 2;
        remaining /= 2;
    }
}

// Prints the current generation as a row of spaces and '#' characters, followed by a newline.
void displayCurrentGeneration(int generation[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (generation[i] == 1)
        {
            std::cout << '#';
        }
        else
        {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}

// Converts a 3-cell neighborhood into an integer index.
int convertNeighborhoodToIndex(int left, int current, int right)
{
    return left * 4 + current * 2 + right * 1;
}

// Computes the next generation of array from the current one using the rule set array.
void computeNextGeneration(int currentGen[], int nextGen[], int length, int ruleSetArray[RULE_SET_SIZE])
{
    // The first and last cells are the same.
    nextGen[0] = currentGen[0];
    nextGen[length - 1] = currentGen[length - 1];

    // For every interior cell, look at its neighborhood and apply the rule.
    for (int i = 1; i < length - 1; i++)
    {
        int left = currentGen[i - 1];
        int current = currentGen[i];
        int right = currentGen[i + 1];

        int index = convertNeighborhoodToIndex(left, current, right);
        nextGen[i] = ruleSetArray[index];
    }
}

int main()
{
    int ruleSetNumber;
    std::cout << "Enter a rule set number (0-255): ";

    // Validate that input is a number and in the correct range.
    if (!(std::cin >> ruleSetNumber) || ruleSetNumber < 0 || ruleSetNumber > 255)
    {
        std::cout << "Invalid rule set number. Must be an integer between 0 and 255." << std::endl;
        return 0;
    }

    int ruleSetArray[RULE_SET_SIZE];
    convertRuleSetNumberToRuleSetArray(ruleSetNumber, ruleSetArray);

    // Initialize the starting generation
    int currentGen[GEN_LENGTH] = {0};
    currentGen[32] = 1;

    displayCurrentGeneration(currentGen, GEN_LENGTH);

    // Compute and display each following generation.
    for (int gen = 0; gen < NUM_GENERATIONS; gen++)
    {
        int nextGen[GEN_LENGTH];
        computeNextGeneration(currentGen, nextGen, GEN_LENGTH, ruleSetArray);
        displayCurrentGeneration(nextGen, GEN_LENGTH);

        // Copy nextGen into currentGen for the next iteration.
        for (int i = 0; i < GEN_LENGTH; i++)
        {
            currentGen[i] = nextGen[i];
        }
    }
    return 0;
}


/*
 * AI Code Review
 *
 * I asked an AI assistant to review my CA.cpp for whether each
 * function has a single clear responsibility, whether the required function
 * contracts were followed, and whether there were readability or code-style
 * issues.
 *
 * The AI's review found the following:
 * - Single responsibility: Each function does one clear job (convert rule
 *   number, display a generation, compute a neighborhood index, compute the
 *   next generation). No issues found.
 * - Function contracts: All four required functions correctly follow their
 *   specified behavior, including filling every element of the rule set
 *   array and using the correct bit order (index 0 holds the least
 *   significant bit).
 * - Readability/style: The AI flagged one real issue - a duplicated comment
 *   line appearing twice in a row above convertRuleSetNumberToRuleSetArray.
 *   It also noted that the "+ right * 1" term in convertNeighborhoodToIndex
 *   is technically redundant since multiplying by 1 does nothing, but
 *   suggested it could be left in for readability since it keeps the 4/2/1
 *   place-value pattern visually consistent.
 *
 * My response to two of these comments:
 *
 * 1. Duplicated comment line: I agree with this. It was leftover clutter
 *    from earlier edits and served no purpose, so I removed the duplicate
 *    line.
 *
 * 2. Redundant "* 1" in convertNeighborhoodToIndex: I agree with the AI's
 *    reasoning and chose to keep it as-is. Even though it doesn't change
 *    the computed value, it makes the connection to the underlying binary
 *    place values (4, 2, 1) clearer at a glance, which I think aids
 *    readability more than removing it would.
 */
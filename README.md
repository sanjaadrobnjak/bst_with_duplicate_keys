# Binary Search Tree (BST) with Duplicate Keys

## Project Overview
This project implements a Binary Search Tree (BST) that supports duplicate keys. The tree is built from a sorted sequence of integer keys, maintaining order consistency with the given sequence. Each node contains a pointer to the left and right subtrees, a parent pointer, and a list to store duplicate keys.

## Technologies Used
- **Backend:** C

## Features
- Constructing the BST from a Sorted Key Sequence (K)
  - The tree is built using an ordered sequence of keys.
- Inserting a New Key into the BST
  - Supports duplicate keys by storing them in a list within the corresponding tree node.
- Searching for a Key in the BST
  - The user provides a key, and the program searches for it in the tree.
- Formatted Printing of the BST Structure
  - The tree structure is displayed in a properly formatted manner, not just traversal outputs.
- Performance Evaluation of BST Search Operations
  - Generates a sequence of keys within a given range and calculates the average number of search steps.
- Deleting the BST from Memory
  - Properly deallocates memory by deleting all tree nodes.
    
## Performance Analysis
The program evaluates BST search performance by measuring the average number of search steps for various key sequences. Results are displayed for different test cases

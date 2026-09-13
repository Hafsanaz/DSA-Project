//includes the MerkleProof declaration from the .h file
#include "MerkleProof.h"
//includes the string librray so we can use std::string and to_string
#include <string>
//included to use cut for printing to the screen
#include <iostream>
using namespace std;

//Default Constructor
//this runs when we create a MerkleProof object without giving any data
MerkleProof::MerkleProof()
    {
        //initialize the leaf hash to zero means there's nothhing yet.
        leafHash = 0;
    }

//Parametrized Constructor
//runs when we create a MerkleProof object and already know the leaf hash
MerkleProof::MerkleProof(unsigned long leaf)
    {
        //Store the given leaf hash inside the MerkleProof object so it remembers the leaf hash
        leafHash = leaf;
    }

//This function adds a node to the proof path
//hash is the sibling hash at this level
//and the side tells where the left sibling or right sibling is
void MerkleProof::addInPath(unsigned long hash, char side)
    {
        //put the hash and its sibling together as a pair
        //then store it at the end of the path list like directions as "go left or go right"
        path.push_back({hash, side});
    }

//this function changes the leaf hash value
void MerkleProof::setLeafHash(unsigned long hash)
    {
        //replace the current leaf hash with the new one
        leafHash = hash;
    }

//this function gives back the leaf hash
unsigned long MerkleProof::getLeafHash() const
    {
        //return the stored leaf hash
        return leafHash;
    }

//this function gives back the whole path
//which is the list of steps we moved from the leaf to root
const vector<pair<unsigned long, char>>& MerkleProof::getPath() const
    {
        //only returns the whole path but does'nt allows changing to it.
        return path;
    }

//this function prints everything in a readable way
//for console
void MerkleProof::PrintProof() const
{
    //print a title
    cout << "\n*** Merkle Proof ***" << endl;

    //prints the number of leaf hash
    cout << "Leaf Hash: " << leafHash << endl;

    //Explaination of proof
    cout << "Proof of path ( from leaf to root):" << endl;

    //if there are no steps stored in path (path empty)
    if (path.empty())
    {
        //it means the leaf it's self is already the root
        //so no directions needed
        cout << "  (Path is empty!!! this is the root.)" << endl;
    }

    //go through each step, move one by one upward in the tree
    else
    {
        for (unsigned int i = 0; i < path.size(); i++)
        {
            //print the level number and its sibling hash
            //also print whether the sibling is on the left or right side
            cout << "  Level " << i + 1 << ": Hash " << path[i].first
                 << " (sibling on " << path[i].second << ")" << endl;
        }
    }
    cout << "" << endl;
}

//This function verifies whether the proof is real or fake
//it returns true if everything mathches, and false if does'nt
bool MerkleProof::verification(unsigned long rootHash) const
{
    //if the path is empty
    if (path.empty())
    {
        //this means the leaf should be the root
        //so we simply compare the two numbers
        return leafHash == rootHash;
    }

    //start from the leaf hash which is our starting point
    unsigned long current = leafHash;

    //go through each item from bottom to top in the path
    for (const pair<unsigned long, char>& node : path)
    {
        //if the sibling is on the left side
        if (node.second == 'L')
        {
          //that means our current hash is on the right side
          //so we combine left first , then right
            current = mergeHashes(node.first, current);
        }
        else
        {
            //otherwise the sibling is on the right side
            // so we combine current hash first then sibling
            current = mergeHashes(current, node.first);
        }
    }

    //after all steps current hash should be the root hash
    //if it matches the given root hash then the proof is correct
    return current == rootHash;
}

//this function mixes two numbers into a new number
//this must match the exact combining method used in tree
unsigned long MerkleProof::mergeHashes(unsigned long left, unsigned long right)
{
    //turns both numbers into text form
    //then combine them to into one long text
    //for e.g "12" and "34" bocomes "1234"
    string combined = to_string(left) + to_string(right);

    //A big number used to stop values from becoming too large
    unsigned long prime_no = 1000000007;

    //A number used to change how fast the hash grows
    unsigned long base = 256;

    ////this will store final combined number
    unsigned long hash = 0;

    //this controls how the order matters for each charachter
    unsigned long power = 1;

    //go through every letter in the combined text
    for (unsigned int i = 0; i < combined.length(); i++)
    {
        //Convert the letter into a number and multiply it by the power
        //add it to the hash
        //used modulous operator to keep number small
        hash = (hash + (static_cast<unsigned long>(combined[i]) * power) % prime_no) % prime_no;

        //increase power for the next letter
        power = (power * base) % prime_no;
    }

    //gives back the final combined number.
    return hash;
}

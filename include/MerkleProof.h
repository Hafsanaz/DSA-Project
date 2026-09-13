#ifndef MERKLE_PROOF_H
#define MERKLE_PROOF_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Merkle Proof class
class MerkleProof
{

public:
    //Default Constructor declaration
    MerkleProof();

    //Parametrized Constructor declaration
    MerkleProof(unsigned long leaf);

    //function adds a node to the proof path
    void addInPath(unsigned long hash, char side);

    //simple helper functions
    //update the leaf hash
    void setLeafHash(unsigned long hash);

    //simply returns the leaf hash
    unsigned long getLeafHash() const;

    //function returns the whole proof path
    const vector<pair<unsigned long, char>>& getPath()const;

    //visualization of every item leaf hash it's level and on which side the sibling is
    void PrintProof()const;

    //verifies whether the leaf belongs to a tree with this root hash
    bool verification(unsigned long rootHash)const;

private:

    //vector list to help build path upward with number of hash and its direction L or R.
    vector<pair<unsigned long, char>> path;

    //the hash of leaf (the starting point)
    unsigned long leafHash;

    //function to combine two hashes
    static unsigned long mergeHashes(unsigned long left, unsigned long right);
};

#endif

#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <vector>
#include <string>
#include "MerkleProof.h"
using namespace std;
class MerkleTree {


public:
    MerkleTree()=default;

    // it clears merkle tree
    void reset();

    //it read file line by line and then pass each line to
    //hashline function , and the returned hashis stored in leaf vector
    void read_File(const std::string &filename);

    //it build a merkle tree and return its root hash
    unsigned long buildTree();

    //it prints a merkle tree
    void treePrinting() const;

    //it print statistical details of of the merkle tree
    void printData() const;

    // Generate Merkle proof for a given leaf index
    MerkleProof generateProof(int leafIndex) const;

    //getters
    const vector<unsigned long>& getLeaves() const;

    unsigned long getRootHash() const;
private:
    //1D vector to store leave hashes
    vector<unsigned long> leaves;
    //  2D890array of levels
    vector<std::vector<unsigned long>> levels;
    //it build tree levels
    unsigned long buildLevel(const vector<unsigned long>& nodes, int level);
    //it merges 2 hashes
    unsigned long mergeHashes(unsigned long left, unsigned long right);
    //it returns the hash of the line passed as parameter
    unsigned long hashingLine(const string &line);
};

#endif // MERKLE_TREE_H

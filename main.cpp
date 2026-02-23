#include "MerkleTree.h"
#include "MerkleProof.h"
#include "FileComparator.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// function to create print and verify merkle proof
void presentMerkleProof(const MerkleTree& tree, int leafIndex, const string& filename)
    {
    //prints a 50 "=" signs
    cout << "\n" << string(50, '=') << endl;
    //show the file for proof
    cout << "Presenting Merkle Proof for file: " << filename << endl;
    //prints a 50 "=" signs
    cout << string(50, '=') << endl;

    //get all leaf hashes from merkel tree
   const std::vector<unsigned long>& leaves = tree.getLeaves();


    //check if the given leaf index is inside valid range or not
    if (leafIndex < 0 || static_cast<unsigned int>(leafIndex) >= leaves.size())
      {
        cout << "Invalid leaf index! Must be between 0 and " << leaves.size() - 1 << endl;
        return;
      }

      //generate merkle proof for the selected leaf
    MerkleProof proof = tree.generateProof(leafIndex);

    // Print the proof
    proof.PrintProof();

    //get the root hash of tree
    unsigned long rootHash = tree.getRootHash();

    // Verify the proof
    bool isValid = proof.verification(rootHash);

    if (isValid)
        {
          cout << "\n PROOF IS VALID! Leaf is a part of the Merkle tree." << endl;
        }
    else
        {
          cout << "\n PROOF IS INVALID! Leaf is NOT a  part of the Merkle tree." << endl;
        }

    // Demonstrate tampering detection
    cout << "\n--- Alteration Detection Test ---" << endl;
    if (proof.getLeafHash() != 0)
        {
            //create a modified copy of proof
        MerkleProof changedProof = proof;
        //try verifying using a wrong root hash
        bool proofStillValid = changedProof.verification(rootHash + 1);

        //confirm that altering was detected
        if (!proofStillValid)
        {
            cout << " Alteration detected! Invalid proof with wrong root hash." << endl;
        }
      }
}

//main driving  function
int main()
{
    int n;
    //ask user how many files to compare
    cout << "Enter number of files to compare: ";
    cin >> n;

    if (n < 2)
    {
        cout << "At least 2 files are required for comparison!" << endl;
        return 0;
    }

    vector<string> files(n);
    vector<MerkleTree> trees(n);
    vector<unsigned long> roots(n);
FileComparator comparator;
    //Input directory of the files
    for (int i = 0; i < n; i++)
    {
        cout << "Enter file " << i + 1 << " directory: ";
        cin >> files[i];
    }

    //loop for processing each file
    for (int i = 0; i < n; i++)
    {
        cout << "\n" << string(40, '=') << endl;
        cout << "PROCESSING FILE: " << files[i] << endl;
        cout << string(40, '=') << endl;

        trees[i].read_File(files[i]);
        roots[i] = trees[i].buildTree();
        trees[i].printData();

        if (!trees[i].getLeaves().empty())
        {
            //Printing the tree
            trees[i].treePrinting();

            //Shows proof for first leaf
            presentMerkleProof(trees[i], 0, files[i]);
        }
    }

    //Compare all pairs of files using FileComparator
    //nested loop file at index 0 is compared with all rest
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
        comparator.compareFilesWithSimilarity(trees[i], trees[j], files[i], files[j]);
        }
    }

    //Print the similarity table
    cout << "\n" << string(60, '=') << endl;

    cout << "SIMILARITY TABLE" << endl;
    cout << string(60, '=') << endl;

    comparator.printSimilarityTable(trees, files);

    return 0;
}

#ifndef FILE_COMPARATOR_H
#define FILE_COMPARATOR_H

#include "MerkleTree.h"
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class FileComparator
{
    //Public functions
    public:
        //Function for calculating similarity between files
        void compareFilesWithSimilarity(const MerkleTree &tree1, const MerkleTree &tree2, const string &file1, const string &file2);

        //Function for printing similarity table  between files
        void printSimilarityTable(const std::vector<MerkleTree> &trees , const std::vector<std::string> &files);

        //Function for calculating minimum
        static int min (const int num1 ,const int num2);

        //Function for calculating maximum
        static int max (const int num1 ,const int num2);

        //Function for similarity calculation
        double similarity_measure(const MerkleTree &tree1, const MerkleTree &tree2);

    //Private functions
    private:

        //Function for trimming long file names
        static string trimNameFromStart(const std::string &name, size_t maxLen = 12);
};

#endif

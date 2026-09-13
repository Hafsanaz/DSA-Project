#include "FileComparator.h"
#include <iostream>
#include <iomanip>


using namespace std;

//Function for comaparing files with similarity
void FileComparator :: compareFilesWithSimilarity(const MerkleTree &tree1 , const MerkleTree &tree2 , const string &file1, const string &file2)
{
    //Taking hashes of file lines through getLeaves function of MerkleTree
    const vector<unsigned long> &hash_tree1 = tree1.getLeaves();
    const vector<unsigned long> &hash_tree2 = tree2.getLeaves();


    //Console message showing which files are being comapared
    cout << "---------> Comparing " << file1 << " and " << file2 << "<-----------" << endl;

    //Variable for counting same lines hashes
    int matching_lines = 0;

    //Comaparing number of lines in both files, using smaller size, so that loop doesnt go out of bound
    int minSize = min(hash_tree1.size() , hash_tree2.size());

    //Loop for checking each line hashes
    for (int i = 0; i < minSize; i++)
    {
        //If hashes are same, means lines are same, incrementing matches
        if (hash_tree1[i] == hash_tree2[i])
        matching_lines++;
    }


    //Variable for similarity measure
    double similarity = similarity_measure(tree1, tree2);

    //Printing number of lines file have , on console
    cout << "--> " << file1 << " lines: " << hash_tree1.size() << endl;
    cout << "--> " << file2 << " lines: " << hash_tree2.size() << endl;

    cout << endl;

    //Display difference between number of lines
    if (hash_tree1.size() != hash_tree2.size())
    {
        if (hash_tree1.size() > hash_tree2.size())
            cout << "--> " << file1 << " has " << hash_tree1.size() - hash_tree2.size() << " extra lines" << endl;
        else
            cout << "--> " << file2 << " has " << hash_tree1.size() - hash_tree2.size() << " extra lines" << endl;
    }

    cout << endl;

    //Printng matching lines / minimum size of files
    cout << "--> Matching lines: " << matching_lines << "/" << minSize << endl;

    //Printing similarity on screen
    //Using setprecision() function of iomanip header for avoiding large deciaml places
    //Using fixed manipulator of iomanip header for avoiding large deciaml places
    cout << "--> Similarity: " << fixed << setprecision(1) << similarity << "%" << endl;
    cout << endl;

    cout << "-------------" << endl;
    //Printing messages according to similarity
    if (similarity == 100.0)
        cout << "=| Files are IDENTICAL" << endl;

    else if (similarity > 80.0)
        cout << "=| Files are VERY SIMILAR" << endl;

    else if (similarity > 50.0)
        cout << "=| Files are MODERATELY SIMILAR" << endl;

    else if (similarity > 20.0)
        cout << "=| Files are DIFFERENT" << endl;

    else
        cout << "=| Files are COMPLETELY DIFFERENT" << endl;

    cout << "--------------" << endl;
    cout << endl;

    //Displaying lines that differs
    if (similarity < 100.0)
        {
            cout << "These Lines differ: " << endl;

            //Loop that runs till min size of one of the files
            for (int i = 0; i < minSize; i++)
            {
                //Checks which line differs
                if (hash_tree1[i] != hash_tree2[i])

                    //Printing line numbers
                    cout << "--> Line " << i + 1 << endl;

            }
        }


}




//Function for trimming name
string FileComparator :: trimNameFromStart(const string &name, size_t maxLen)
{
    if (name.size() <= maxLen)
        return name;

    return "..." + name.substr(name.size() - (maxLen - 3));
}


// Calculate similarity percentage between two trees
double FileComparator :: similarity_measure(const MerkleTree &tree1, const MerkleTree &tree2)
{
    //Variable for similarity
    double similarity;
    //Variable for matchng
    int matching_lines = 0;

    //Taking hashes of file lines through getLeaves function of MerkleTree
    const vector<unsigned long> &h1 = tree1.getLeaves();
    const vector<unsigned long> &h2 = tree2.getLeaves();

    //Taking minsize to avoid out od bound
    int minSize = min(h1.size(), h2.size());

    //Simlarity is 0, if one of the files are empty
    if (minSize == 0)
        return 0.0;

    for (int i = 0; i < minSize; i++)
    {
        //If hashes match , matces line increment
        if (h1[i] == h2[i])
            matching_lines++;
    }

    //Calculating similarity %age
    similarity = (matching_lines * 100.0) / minSize;

    return similarity;
}

//Function for printing similarity table  between files
void FileComparator :: printSimilarityTable(const vector<MerkleTree> &trees,const vector<string> &files)
{

    //Tree size variable
    int tree_size = trees.size();

    //Printing table heading
    cout << setw(15) << " ";

    //Printing file names
    //Taking tree size as count as number of files equals tree_size
    for (int j = 0; j < tree_size; j++)
        cout << setw(15) << trimNameFromStart(files[j], 12);

    cout << endl;

    //Printing table rows
    for (int i = 0; i < tree_size; i++)
    {
        cout << setw(15) << trimNameFromStart(files[i], 12);

        //Looop runs till tree size to go through each tree
        for (int j = 0; j < tree_size; j++)
        {
            //Calculating each file similarity using similarity_measure function
            double similarity = similarity_measure(trees[i], trees[j]);
            //Printing similarity
            cout << setw(15) << fixed << setprecision(1) << similarity << "%";
        }
        cout << endl;
    }
}

//Function for calculating minimum
int FileComparator :: min (const int num1 ,const int num2)
{
    if(num1 < num2)
        return num1;

    else
        return num2;
}

//Function for calculating maximum
int FileComparator :: max (const int num1 ,const int num2)
{
    if(num1 > num2)
        return num1;

    else
        return num2;

}

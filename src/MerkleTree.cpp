#include "MerkleTree.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;


// it empty the previous tree so you can rebuild a new tree
//RESET
//it clears data of the merkle tree
//it reset level and leaves
void MerkleTree::reset()
    {
//leaves is 1D array of unsigned long int
//it stores leaves hashes
//eg-> if we have a file consisting of 4 lines
//leaves vector contain->[h1 ,h2 ,h3 ,h4]
//h1 is he hash of first line , h2 is the hash of second line etc

//clear is a member function of std->vector class
//.clear removes all elements from the vector
//after this leaves.size() becomes zero
leaves.clear();

//levels
// {
// [h1,h2,h3,h4]          //leaves ->level 0
// [h12,h34]              //level 1
//h12=comine(h1,h2) and h34=combine(h3,h4)
// [h1234]                //level 2 root hash
// }
//it is a vector of levels ->{[h1,h2,h3,h4] ,[h12,h34],[h1234]}
levels.clear();
    }
//unsigned long is the return type of this function
//hashline gets a string passed by reference
//it convert string into hash and return it
unsigned long MerkleTree::hashingLine(const string &line)
{
//it is a prime number and we use it to take mod to keep our answer very shot
//so it does not overflow our unsigned long range
unsigned long prime_no = 1000000007;

//if we just sum ofhashes of  characters it can be same
//abc and bca sum will be made from hashes sum of a,b and c
//so it will be same
//to resolve this we multipy each hash with its position as well
//we take base as 256 so abc  means ascii of a * 256^0 +ascii of b* 256 +ascii of c*256^2
//which would be different from bca
unsigned long base = 256;
//hash is the variable of unsigned long int type that will store hash of te line
//initially it is initiallized by zero
// at the end of the function we return it
unsigned long hash = 0;
//power store base^0 s0 intialy power is 1
unsigned long power = 1;

    for (unsigned int i=0 ; i<line.size();i++)
     {
      //calculate hash of each character separataly
      //eg  if line is hello world
      //hashes are computed for h e l l o "" w o r l d
      //and comined as total(hashes)%prime
      //store it in hash
      //and at the end return that hash
      char ch=line[i];
      // ascii of character*power%prime
      //static_cast will convert it into ascii
      //%prime keep number in signed range
      unsigned long hash_ch = (static_cast<unsigned long>(ch) * power) % prime_no;

      //add the hash of char in hash variable and % with prime to keep it in unsigbed long range
      hash = (hash + hash_ch) % prime_no;

      // updating power for next char
      //intially power is 1
      //so power for first char=1
      //then update it for second char
      //1*256%prime =256
      //power for 3rd char
      //256*256=256^2
      //i this way we are updating powers
      power = (power * base) % prime_no;
     }

//at the end we return hash
return hash;
}

// combining 2 hashes to make parent node until we get a single root hash

unsigned long MerkleTree::mergeHashes(unsigned long left, unsigned long right)
{
//converting left and right hash into strig and then combine
//eg if h1 is 1234 and h2 5678 combine hash is 12345678
//it prevents left and rigt order as well
//this keeps the order left-right != right-left
string combined = to_string(left) + to_string(right);
//prime number to take mode
unsigned long prime = 1000000007;
//base  256 because range of characters is(0-255)
unsigned long base = 256;
//variable in which we store combine hash
unsigned long hash = 0;
//power is base^0=1
// so initially power is 1
unsigned long power = 1;
//combine is string
//we have to convert it into hash
    for (int i = 0; i < combined.size(); i++)
    {
      char c = combined[i];
      //convert character into its ascii code and multiply it with its power
      unsigned long hash_ch = (static_cast<unsigned long>(c) * power) % prime;
      hash = (hash + hash_ch) % prime;
      //updating power for next char
      power = (power * base) % prime;
    }


return hash;
}

//return type is void
//it does not return every thing
//in this function file is passed by reference
//return  type of  this function is void
//file is passed as reference in this function
void MerkleTree::read_File(const string &filename)
{
//ifstream opens file passed as parameter for reading
ifstream file(filename);

//if file deoes not exsis we print an error messsage and return
if (!file)
    {
     cout << "file :" << filename << " which you are trying to open does not exsist" << endl;
     return;
    }

//string line stores line read from file
string line;

//it track the number of lines
int line_number = 1;

//loop the file line by line until we reach end of file
//getline read files until /n and store it in  line variable
//it return type is bool
//return true if successfully return line
//false if it reaches end of file
while (getline(file, line))
    {
     // h is a variable
     // we pass line in to hash function and hash function return
     //hash of that line
     //we store thathash of each line in h variable
     unsigned long h = hashingLine(line);
     // then push it into vectors og leaves
     //so we will loop through each line of file until we reach EOF
     leaves.push_back(h);
     //then we print line no ,line and hash
     cout << "Line no " << line_number << ": \"" << line << "\" -> Hash of that line: " << h << endl;
     //we increment line number at the end of each loop itration
     line_number++;
    }
//at the end close the file
file.close();

}

// this function build merkle tree recursively and return root hash
//it takes 1 D vector holding leaves and  level->int
//level 0 ,1 and so on
unsigned long MerkleTree::buildLevel(const vector<unsigned long>& nodes, int level)
{
//levels is a 2d vector
// we push 1D vector in it
levels.push_back(nodes);
//if 1d array has only element means tat is the root hash
//we simply retutn it
//BASE CONDITION of recursion also
    if (nodes.size() == 1)
    {
        return nodes[0];
    }

// this is a 1D vector made from combing the previous hashes
vector<unsigned long> parent;

//loop through the node vector which upper parent level we want to build
    for (unsigned int  i = 0; i < nodes.size(); i =i+2)
     {
      //store it in left vatiable
      unsigned long left = nodes[i];
      unsigned long right;
      // if we gave [h1  , h2 ,h3]
      //we will combine h1 with hash 2
      //left is h1 and right is h3
      //if right does not exsist we will merge it with it seld ahain
      //e.g h12  and h33  in this way we get 2 merged hashes
      //if left+1<size right is i+1 element of vector whose next level we are creating
      //else
    if (i + 1 < nodes.size())
        {
           right = nodes[i + 1];
        }
    else
        {
          right = nodes[i];
        }

//compine left and right hashes by calling merge hash function
//mergehash return a hsh whic we store it in combine variable and push it in parent 1 d level
unsigned long combine = mergeHashes(left, right);
parent.push_back(combine);

}

// we call build level till we reach root level and return root hash
return buildLevel(parent, level + 1);
}

//this function will build tree
unsigned long MerkleTree::buildTree()
{
//if leaves vector is empty
    if (leaves.empty())
        {
          cout << "merkle tree cannot be build bcause file has no lines.\n";
          // we return 0
          return 0;
}

//start timing od building a tree
auto start = chrono::high_resolution_clock::now();

//call buildlevel function by passing leaves vector and level of the leaves vector
//since leaves are at level zero we pass 0
//buildlevel func will return a root hash after building a levels array which we assign in root variable
unsigned long root = buildLevel(leaves, 0);

// end time of building a tree
auto end = chrono::high_resolution_clock::now();

//duration is starting time-ending time
auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

cout << "Merkle Tree is build successfully" << endl;
cout << "Root hash of tree : " << root << endl;
cout << "Time taken to build tree is  " << duration.count() << " ms" << endl;

//it will return the root hash
//root hash represent the entire file
return root;
}

// it print merkle tree
//return type is void
//const means it does not change it private variable
void MerkleTree::treePrinting() const
{
//check if levels array which is 2d array  is empty or not
    if (levels.empty())
     {
       //if it is empty means we cannot print tree
       //so we simply return
       cout << "Tree is empty so we cannot print it" << endl;
       return;
     }

cout << "\n==== Merkle Tree====\n";
    for (int i = 0; i < levels.size(); i++)
        {
          cout << "Level  " << i+1 << ": ";
          //this is for each loop
          //it loop through each hash stored in that particular level
          //eg level[0]={h1,h2,h3,h4}
          // it will print all followed by a space
    for (unsigned long node : levels[i])
        {
          cout << node << " ";
        }
//after printing a level we will give a space
cout << endl;
}

//at the end we will print root hash by calling get root hash function
cout << "Root hash is : " << getRootHash() << endl;
}

// this function print statitics of the tree
//const means this will not change anything of merkle tree
void MerkleTree::printData() const
{

if (levels.empty())
    {
      cout << "Merkle Tree is empty so we cannot print stats" << endl;
      return;
    }

cout << "\n===Statistics of Merkle Tree===" << endl;
//leaves vector size is the number of leaves of our Merkle Tree

cout << "Number of leaves are: " << leaves.size() << endl;
//level.size() gives the number of levels which is the height of the tree

//levels is 2D vector  of levels . size of this vector gives height of tree
cout << "height of tree is : " << levels.size() << " levels" << endl;

unsigned int allNodes = 0;
//for each loop
//it loop over all 1D array as level is a vector of vectors
//and we add size of each level in all nodes variable
    for (const vector<unsigned long>& level : levels)
    {
      allNodes += level.size();
    }



cout << "total node(lines of files) are : " << allNodes << endl;
cout << "Root hash is : " << getRootHash() << endl;
cout << "Sizes of level are : ";
    for (unsigned int  i = 0; i < levels.size(); i++)
    {
        //level[i].size gives number of hashes at i level
        //print arrow after each level except the last
        cout << "Level" << i + 1 << ":" << levels[i].size();
    if (i < levels.size() - 1)
      {
        cout << " -> ";
      }
    }

cout << endl;
//printing dash at the end to seperate it from output
cout << "===============================" << endl;
}

  MerkleProof MerkleTree::generateProof(int leafIndex) const
{
    //this object will store all data needed to prove a leaf belongs to the tree
    MerkleProof proof;

    //checks if the given leaf index is valid or not
    if (leafIndex < 0 || leafIndex >= leaves.size())
    {
        //if invalid print the error message
        cout << "Invalid leaf index!" << endl;
        return proof;
    }

    //store the hash of the selected leaf which is starting point of proof
    proof.setLeafHash(leaves[leafIndex]);

    //this variable keeps track of where we are in current level
    int index = leafIndex;

    //move level by level from leaves up to the root
    for (int level = 0; level < levels.size() - 1; level++)
    {
        //variable for neighbour node
        int siblingIndex;

        //if the current node is on the left, its even index
        if (index % 2 == 0)
        {
            //the sibling is normally on the right
            siblingIndex = index + 1;

            //if there is no right sibling use the same node again
            if (siblingIndex >= levels[level].size())
            {
                siblingIndex = index;
                //store the sibling hash as coming from the right side
            proof.addInPath(levels[level][siblingIndex], 'R');
            }
        }
        else
        {
            //the neighbour is on the left
            siblingIndex = index - 1;

            //store the sibling hash as coming from the left side
            proof.addInPath(levels[level][siblingIndex], 'L');
        }

        //move to the parent node in the next level
        index = index / 2;
    }

    //return the completed merkle
    return proof;
}


//getter for leaves
//const means the return vector cannot be modified
//return type is vector of unsigned long by reference
//const at end means we will just return leaves without changing any private attribute
const vector<unsigned long>& MerkleTree::getLeaves() const
{
//leaves is a private member function of merke tree
//we are returning vector of leaves
return leaves;
}

//this function returns the root hsh of the file
//root hash represents the entire file
unsigned long MerkleTree::getRootHash() const
{
    if(levels.empty())
      {
        return 0;
      }
    else
      {
        //levels.back return the last element
        //since root is the last element it will be returned
        // we have a 2D array
        //{
        //[h1,h2,h3,h3]   level0
        //[h12,h32]  level1
        // [h1234]    level 2  root
        // }
return levels.back()[0];
}
}

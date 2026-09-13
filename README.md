# Merkle Tree based Comparator

A C++ console application that builds a **Merkle Tree** from the lines of a text file, generates and verifies **Merkle proofs** for individual lines, demonstrates **tamper detection**, and compares multiple files for **line-by-line similarity** using their tree structures.

Built as a Data Structures & Algorithms (DSA) semester project using Code::Blocks.

## 🧠 How It Works

### 1. Hashing (custom, not cryptographic)
Each line of a file is hashed using a **custom polynomial rolling hash** (`MerkleTree::hashingLine`) — each character's ASCII value is multiplied by an increasing power of `256` and summed modulo a large prime (`1,000,000,007`). This is a lightweight, educational hash designed to demonstrate Merkle tree mechanics — it is **not cryptographically secure** (not SHA-256 or similar) and shouldn't be used for real security-sensitive integrity checks.

### 2. Building the Tree
- `read_File()` reads a file line by line, hashes each line, and stores the hashes as **leaves**.
- `buildTree()` repeatedly pairs and combines hashes (`mergeHashes`, which concatenates the two hash values as strings and re-hashes with the same rolling hash scheme) level by level until a single **root hash** remains — this root represents the entire file's content.
- If a level has an odd number of nodes, the last node is paired with itself.
- Tree build time is measured and printed using `<chrono>`.

### 3. Merkle Proofs & Tamper Detection
- `generateProof(leafIndex)` walks from a given leaf up to the root, collecting the sibling hash and its side (`L`/`R`) at each level into a `MerkleProof`.
- `MerkleProof::verification(rootHash)` recomputes the path from the leaf hash up to the root using the stored siblings and checks it matches the given root hash.
- The program demonstrates **tamper detection** by re-verifying a valid proof against a deliberately altered root hash (`rootHash + 1`) and confirming that verification correctly fails.

### 4. File Comparison & Similarity
- `FileComparator::compareFilesWithSimilarity()` compares two files' leaf hashes line-by-line (up to the shorter file's length), reports files with extra lines, and prints which specific line numbers differ.
- Similarity is calculated as `(matching lines / shorter file's line count) × 100%`, with a qualitative label:
  - **100%** → Identical
  - **>80%** → Very similar
  - **>50%** → Moderately similar
  - **>20%** → Different
  - **else** → Completely different
- `printSimilarityTable()` prints a full pairwise similarity matrix across all input files.

## 🛠️ Tech Stack

- **Language:** C++
- **IDE / Build System:** Code::Blocks (`.cbp` project file, GCC compiler)
- **Standard Library:** `<vector>`, `<string>`, `<fstream>`, `<chrono>`, `<iomanip>`
- **Core Concepts:** Merkle Trees, custom rolling hash, Merkle proofs & verification, tamper detection, file similarity comparison

## 📁 Project Structure

```
MerkleTree_DSA_Project_Final/
├── include/
│   ├── FileComparator.h      # File comparison & similarity table interface
│   ├── MerkleProof.h         # Merkle proof interface
│   └── MerkleTree.h          # Merkle tree interface
├── src/
│   ├── FileComparator.cpp    # Similarity calculation, comparison, table printing
│   ├── MerkleProof.cpp       # Proof path building, printing, verification
│   └── MerkleTree.cpp        # File reading, hashing, tree building, proof generation
├── main.cpp                  # Program entry point / driver
├── MerkleTree_DSA_Project_Final.cbp
└── README.md
```

## 🚀 Getting Started

### Prerequisites
- [Code::Blocks](https://www.codeblocks.org/) with the GCC compiler, **or** any C++ compiler (g++, MSVC, clang) if building manually

### Build & Run (Code::Blocks)
1. Clone the repository:
   ```bash
   git clone https://github.com/Hafsanaz/DSA-Project.git
   cd DSA-Project
   ```
2. Open `MerkleTree_DSA_Project_Final.cbp` in Code::Blocks.
3. Build and run (Debug or Release target).

### Build & Run (manual g++)
```bash
g++ -Iinclude main.cpp src/FileComparator.cpp src/MerkleProof.cpp src/MerkleTree.cpp -o MerkleTreeProject
./MerkleTreeProject
```

### Usage
```
Enter number of files to compare: 2
Enter file 1 directory: file1.txt
Enter file 2 directory: file2.txt
```
The program requires **at least 2 files**. For each file it will:
1. Print each line's computed hash as it reads the file.
2. Build and print the Merkle tree (all levels + root hash).
3. Print tree statistics (leaf count, height, total nodes).
4. Generate, print, and verify a Merkle proof for the file's first line.
5. Run a tamper-detection demo showing the proof correctly fails against an altered root hash.

After processing all files, it compares every pair and prints a final similarity table.

## 👤 Author

**Hafsa Naz**
[GitHub Profile](https://github.com/Hafsanaz)

## 📄 License

This project is intended for educational purposes as part of a Data Structures & Algorithms course/assignment.

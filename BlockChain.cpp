#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

using namespace std;

class Transaction {
public:
    string sender;
    string receiver;
    double amount;

    Transaction(string from, string to, double amt) 
        : sender(from), receiver(to), amount(amt) {}

    // Marking this function as const
    string toString() const {
        stringstream ss;
        ss << "Sender: " << sender << ", Receiver: " << receiver << ", Amount: " << amount;
        return ss.str();
    }
};

class Block {
public:
    int index;
    string previousHash;
    vector<Transaction> transactions;
    time_t timestamp;
    string hash;

    Block(int idx, string prevHash) : index(idx), previousHash(prevHash), timestamp(time(0)) {}

    string calculateHash() {
        stringstream ss;
        ss << index << previousHash << timestamp;

        // Include all transactions in the hash
        for (const Transaction& tx : transactions) {
            ss << tx.toString();
        }

        return ss.str(); // Using a simple concatenation as a placeholder for hash
    }

    void addTransaction(const Transaction& tx) {
        transactions.push_back(tx);
    }

    // Function to mine the block
    void mineBlock() {
        hash = calculateHash(); // Calculate the hash
    }

    // Marking this function as const
    void displayBlock() const {
        cout << "Block " << index << endl;
        cout << "Previous Hash: " << previousHash << endl;
        cout << "Hash: " << hash << endl;
        cout << "Transactions: " << endl;

        for (const Transaction& tx : transactions) {
            cout << "  - " << tx.toString() << endl;
        }

        cout << "Timestamp: " << timestamp << endl;
        cout << "---------------------------" << endl;
    }
};

class Blockchain {
public:
    vector<Block> chain;

    Blockchain() {
        chain.emplace_back(0, "0"); // Creating the Genesis Block
    }

    void addBlock(Block newBlock) {
        newBlock.mineBlock(); // Mine the block to calculate the hash
        chain.push_back(newBlock);
    }

    // Marking this function as const
    void displayChain() const {
        for (const Block& block : chain) {
            block.displayBlock();
        }
    }
};

int main() {
    Blockchain myBlockchain;

    // Create a new block
    Block block1(1, myBlockchain.chain.back().hash);
    block1.addTransaction(Transaction("Alice", "Bob", 50.0));
    block1.addTransaction(Transaction("Bob", "Charlie", 25.0));
    myBlockchain.addBlock(block1);

    // Create another block
    Block block2(2, myBlockchain.chain.back().hash);
    block2.addTransaction(Transaction("Charlie", "Alice", 15.0));
    block2.addTransaction(Transaction("Alice", "David", 30.0));
    myBlockchain.addBlock(block2);

    // Display the blockchain
    myBlockchain.displayChain();

    return 0;
}

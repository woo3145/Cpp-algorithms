#include <string>
#include <map>
#include <iostream>

using std::string;
using std::unordered_map;
using std::cin;
using std::cout;

struct Node {
    bool isEnd;
    unordered_map<char, Node*> children;

    Node():isEnd(false) {};
    ~Node(){};
};

class Trie {
private:
    Node* root;

public:
    Trie(){
        root = new Node();
    };
    ~Trie(){};

    void insert(const string& str) {
        Node* current = root;

        for(const char& c : str){
            if(current->children.find(c) == current->children.end()){
                current->children[c] = new Node();
            }
            current = current->children[c];
        }
        current->isEnd = true;
    }

    bool search(const string& str){ 
        Node* current = root;

        for(const char& c : str){
            if(current->children.find(c) == current->children.end()){
                return false;
            }
            current = current->children[c];
        }
        return current->isEnd;
    }
};

int main () {
    std::ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Trie tree;

    tree.insert("Hello");

    cout << tree.search("Hello");
    cout << tree.search("Hell");

    return 0;
}
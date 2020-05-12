#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
public :
    bool isWord;
    unordered_map<char, Node*> next;
public :
    Node(bool Isword = false) : isWord(Isword) {}
};

class Trie {
    Node root;
    int size;

public :
    Trie() : size(0) {}
    int getSize() {return size;}
    void add(string word);  //添加一个新单词
    bool contains(string word); //查询是否有该单词
    bool isPrefix(string prefix); //查询是否有单词以该prefix为前缀
    void del(string word);  //删除一个单词
};

void Trie::add(string word) {
    Node *curr = &root;

    for (int i = 0; i < word.length(); ++i) {
        Node* ptr = nullptr;
        auto ret = curr->next.insert({word[i], ptr});
        if (ret.second)
            ret.first->second = new Node();
        curr = ret.first->second;
    }

    if (!curr->isWord) {
        curr->isWord = true;
        ++size;
    }
}

bool Trie::contains(string word) {
    const Node *curr = &root;

    for (int i = 0; i < word.length(); ++i) {
        auto ret = curr->next.find(word[i]);

        if (ret == curr->next.end()) {
            return false;
        }
        curr = ret->second;
    }
    return curr->isWord;
}

bool Trie::isPrefix(string prefix) {
    const Node *curr = &root;

    for (int i = 0; i < prefix.length(); ++i) {
        auto ret = curr->next.find(prefix[i]);

        if (ret == curr->next.end()) {
            return false;
        }
        curr = ret->second;
    }
    return true;
}

void Trie::del(string word) {
    if (!contains(word))
        return ;

    vector<Node*> preNode;
    Node *curr = &root;

    for (int i = 0; i < word.length(); ++i) {
        preNode.push_back(curr);
        curr = curr->next.find(word[i])->second;
    }
    if (curr->next.size() == 0) {
        for (int i = word.length() - 1; i >= 0 ; --i) {
            Node *pre = preNode.back();
            preNode.pop_back();

            if ((i != word.length() - 1) && (curr->isWord || curr->next.size() != 0))
                break;
            delete curr;
            pre->next.erase(word[i]);
            curr = pre;
        }
    } else {
        curr->isWord = false;
    }
    --size;
}

int main(void) {
    Trie item;

    item.add("assion");
    item.add("assion");
    item.add("as");
    cout << "words counts: "
         << item.getSize() << endl;
    cout << item.contains("ass") << endl;
    cout << item.isPrefix("assi") << endl;
    item.del("assion");
    cout << "words counts: "
         << item.getSize() << endl;
    return 0;
}

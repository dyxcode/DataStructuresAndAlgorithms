/*链接：https://ac.nowcoder.com/acm/problem/16864
来源：牛客网


题目描述:对一个确定的单词列表，请统计对应的单词查找树的节点数（包括根节点）

输入描述:为一个单词列表，每一行仅包含一个单词和一个换行/回车符。
每个单词仅由大写的英文字符组成，长度不超过63个字符。文件总长度不超过32K，至少有一行数据。

输出描述:该文件中仅包含一个整数和一个换行/回车符。该整数为单词列表对应的单词查找树的节点数。

示例1
输入
A
AN
ASP
AS
ASC
ASCII
BAS
BASIC
输出
13              */
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
    int nodeNumber;

public :
    Trie() : size(0), nodeNumber(1) {}
    int getSize() {return size;}
    int getNodeNumber() {return nodeNumber;}
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
        if (ret.second) {
            ret.first->second = new Node();
            ++nodeNumber;
        }

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
    string t;

    while (cin >> t) {
        item.add(t);
    }
    cout << item.getNodeNumber() << endl;
    return 0;
}

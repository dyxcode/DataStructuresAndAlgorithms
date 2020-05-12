/*���ӣ�https://ac.nowcoder.com/acm/problem/16864
��Դ��ţ����


��Ŀ����:��һ��ȷ���ĵ����б���ͳ�ƶ�Ӧ�ĵ��ʲ������Ľڵ������������ڵ㣩

��������:Ϊһ�������б�ÿһ�н�����һ�����ʺ�һ������/�س�����
ÿ�����ʽ��ɴ�д��Ӣ���ַ���ɣ����Ȳ�����63���ַ����ļ��ܳ��Ȳ�����32K��������һ�����ݡ�

�������:���ļ��н�����һ��������һ������/�س�����������Ϊ�����б��Ӧ�ĵ��ʲ������Ľڵ�����

ʾ��1
����
A
AN
ASP
AS
ASC
ASCII
BAS
BASIC
���
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
    void add(string word);  //���һ���µ���
    bool contains(string word); //��ѯ�Ƿ��иõ���
    bool isPrefix(string prefix); //��ѯ�Ƿ��е����Ը�prefixΪǰ׺
    void del(string word);  //ɾ��һ������

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

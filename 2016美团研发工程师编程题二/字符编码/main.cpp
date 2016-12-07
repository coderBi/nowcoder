#include <iostream>
#include <map>
#include <string.h>
#include <algorithm>
#include <vector>

#define MAX_STR_LENGTH 1000

using namespace std;

typedef pair<char,int> PAIR;

struct CmpByValue{
    bool operator()(const PAIR & p1, const PAIR & p2){
        return p1.second < p2.second;
    }
};

struct HuffmanTreeNode{
    struct HuffmanTreeNode * leftChild;
    struct HuffmanTreeNode * rightChild;
    PAIR nodeValue;
};


int main()
{
    char str[MAX_STR_LENGTH] = {0};

    while( cin.peek() != -1 ){
        cin.getline(str,MAX_STR_LENGTH);
        map<char,int> * countMap = new map<char,int>();
        int length = strlen(str);

        if(length == 0){
            cout << 0 << endl;
            continue;
        }

        //将所有的char跟其计数添加到map
        for(int i = 0; i < length; ++i){
            if(countMap->find(str[i]) == countMap->end()){
                (*countMap)[str[i]] = 1;
            } else {
                (*countMap)[str[i]]++;
            }
        }

        //利用vector对map中的值进行按value的排序。
        vector<PAIR> v(countMap->begin(),countMap->end());
        sort(v.begin(),v.end(),CmpByValue());

        //组建huffman树
        vector<struct HuffmanTreeNode *> huffmanTree;
        for(unsigned int i = 0; i < v.size(); i++){
            struct HuffmanTreeNode * pHuffmanTreeNode = new HuffmanTreeNode();
            pHuffmanTreeNode->leftChild = NULL;
            pHuffmanTreeNode->rightChild = NULL;
            pHuffmanTreeNode->nodeValue = v[i];
            huffmanTree.push_back(pHuffmanTreeNode);
        }
        while(huffmanTree.size() > 1){
            struct HuffmanTreeNode * pHuffmanTreeNode = new HuffmanTreeNode();
            pHuffmanTreeNode->leftChild =  huffmanTree[0];
            pHuffmanTreeNode->rightChild = huffmanTree[1];
            pHuffmanTreeNode->nodeValue.first = '\n'; //经过测试没有办法在这里赋值一个空字符，所以用\n表示组合节点
            pHuffmanTreeNode->nodeValue.second = huffmanTree[0]->nodeValue.second + huffmanTree[1]->nodeValue.second;
            huffmanTree.erase(huffmanTree.begin() + 0);  //注意这里删除一个之后，size已经减1了，所以下面依然是删除第一个
            huffmanTree.erase(huffmanTree.begin() + 0);

            //根据PAIR里面的value大小插入新节点到huffman树
            vector<struct HuffmanTreeNode *>::iterator it = huffmanTree.begin();
            for(; it != huffmanTree.end() && (*it)->nodeValue.second < pHuffmanTreeNode->nodeValue.second; ++it){

            }
            if(it != huffmanTree.end()){
                huffmanTree.insert(it,pHuffmanTreeNode);
            } else {
                huffmanTree.push_back(pHuffmanTreeNode);
            }
        }

        //计算长度,累加所有的叶子节点的加权和。应该使用广度搜索
        int count = 0, layer = 0;
        vector<HuffmanTreeNode*> * parents = new vector<HuffmanTreeNode*>();
        vector<HuffmanTreeNode*> * children = new vector<HuffmanTreeNode*>();

        parents->push_back(huffmanTree[0]);

        while(parents->size() != 0){
            for(unsigned int i = 0; i < parents->size(); ++i){
                if((*parents)[i]->leftChild == NULL && (*parents)[i]->rightChild == NULL){
                    count += (layer * (*parents)[i]->nodeValue.second);
                    continue;
                }
                if((*parents)[i]->leftChild != NULL)
                    children->push_back((*parents)[i]->leftChild);
                if((*parents)[i]->rightChild != NULL)
                    children->push_back((*parents)[i]->rightChild);
            }

            //重新调整parents跟children集合
            delete parents;
            parents = children;
            children = new vector<HuffmanTreeNode *>();
            layer++;
        }
        cout << count << endl;

        delete countMap;
        delete parents;
        delete children;
    }
    return 0;
}

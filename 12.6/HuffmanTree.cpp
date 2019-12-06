#pragma once
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <stack>
#include <iostream>

class HuffmanNode {
public:
	HuffmanNode(int w, char c = 0) :Weight(w), parent(nullptr), leftChild(nullptr), rightChild(nullptr), ch(c) {}
	~HuffmanNode() = default;
	int Weight;
	char getChar() { return ch; }
	bool operator<(HuffmanNode &huf) { return Weight < huf.Weight; }
private:
	HuffmanNode *parent, *leftChild, *rightChild;
	char ch = 0;
	friend class HuffmanTree;
};

class HuffmanTree {
public:
	HuffmanTree(std::vector<std::pair<char, int>> &in);
	~HuffmanTree() = default;
	friend std::ostream &operator<<(std::ostream &os, HuffmanTree &HufT)
	{
		for( const auto &c : HufT.CodeMap )
		{
			os << c.first << "'s Huffmancode is " << c.second << std::endl;
		}
		return os;
	}
private:
	void HuffmanCoooode(void);
	HuffmanNode *root = nullptr;
	std::map<char, std::string> CodeMap;
};

HuffmanTree::HuffmanTree(std::vector<std::pair<char, int>> &in)
{
	struct cmp {
		bool operator()(HuffmanNode *Ha, HuffmanNode *Hb) const
		{
			return Ha->Weight > Hb->Weight;
		}
	};

	std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, cmp> pq;
	for( const auto &m : in )
	{
		HuffmanNode *p = new HuffmanNode(m.second, m.first);
		pq.push(p);
	}

	HuffmanNode *p = nullptr, *q = nullptr;
	while( !pq.empty() )
	{
		if( pq.size() != 1 )
		{
			p = pq.top();
			pq.pop();
			q = pq.top();
			pq.pop();
			HuffmanNode *temp = new HuffmanNode(p->Weight + q->Weight);
			temp->leftChild = p;
			p->parent = temp;
			temp->rightChild = q;
			q->parent = temp;
			pq.push(temp);
		}
		else
		{
			root = pq.top();
			pq.pop();
		}
	}

	HuffmanCoooode();
}

void HuffmanTree::HuffmanCoooode(void)
{
	std::stack<HuffmanNode *> st;
	std::string code;
	HuffmanNode *p = root;
	do
	{
		while( p != nullptr )
		{
			st.push(p);
			p = p->leftChild;
			code.insert(code.end(), '0');
		}
		if( !st.empty() )
		{
			p = st.top();
			st.pop();
			code.erase(code.size() - 1);
			if( p->ch != 0 )
			{
				CodeMap[p->ch] = code;
			}
			p = p->rightChild;
			if( p != nullptr )
			{
				code.insert(code.end(), '1');
				if( p->ch != 0 )
				{
					CodeMap[p->ch] = code;
					HuffmanNode *temp = p;
					if( st.empty() )
					{
						continue;
					}
					while( temp->parent != st.top() )
					{
						temp = temp->parent;
						code.erase(code.size() - 1);
					}
					p = nullptr;
				}
			}
		}
	}
	while( p != nullptr || !st.empty() );
}

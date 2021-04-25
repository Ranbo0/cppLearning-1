#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

const int maxLevel = 10;
typedef int elemType;		//type of element

class skipNode {			//data structure of nodes
public:
	skipNode* pre;
	skipNode* next;
	skipNode* upper;
	skipNode* lower;

	elemType key;
	//int level;

	skipNode(elemType k) : key(k), pre(nullptr), next(nullptr), upper(nullptr), lower(nullptr) {}
	skipNode(elemType k, skipNode* p, skipNode* n) : key(k), pre(p), next(n), upper(nullptr), lower(nullptr) {}
	skipNode(elemType k, skipNode* p, skipNode* n, skipNode* u, skipNode* l) : key(k), pre(p), next(n), upper(u), lower(l) {}
};


// 1 ------------------------------------> 9 -------> nil		//index_level_3
// |                                       |
// 1 ----------------> 5 ----------------> 9 -------> nil		//index_level_2
// |                   |                   |
// 1 ------> 3 ------> 5 ------> 7 ------> 9 -------> nil		//index_level_1
// |         |		   |         |         |	
// 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> nil		//data(level_0)


class skipList {
public:
	vector<skipNode*> header;
	int totalLevel;								//totalLevel should equal to header.size() - 1

	int randLevel();							//get a rand number for insertNode
	skipNode* findNode(elemType target);		//find the node values target
	int insertNode(elemType key);				//insert a node values key
	int deleteNode(elemType target);			//delete the node values target

	void print();

	skipList() {
		totalLevel = 0;
		skipNode* dataHeader = new skipNode(INT_MIN);
		skipNode* dataTail = new skipNode(INT_MAX, dataHeader, nullptr);
		dataHeader->next = dataTail;
		header.emplace_back(dataHeader);
	}
};

int skipList::randLevel() {
	int randNum = 0;
	while (rand() & 1) {
		randNum++;
	}
	return min(randNum, maxLevel);
}

skipNode* skipList::findNode(elemType target) {
	int n = totalLevel;

	int currLevel = n;
	skipNode* currNode = header[currLevel];

	while (currLevel--) {
		while (currNode->next->key < target) {
			currNode = currNode->next;
		}
		currNode = currNode->lower;
	}

	while (currNode->key < target) {
		currNode = currNode->next;
	}

	if (currNode->key == target) {
		return currNode;
	}

	return nullptr;
}

int skipList::insertNode(elemType key) {
	int currLevel = totalLevel;
	skipNode* currNode = header[currLevel];
	while (currLevel--) {
		while (currNode->next->key < key) {
			currNode = currNode->next;
		}
		currNode = currNode->lower;
	}

	while (currNode->next->key < key) {
		currNode = currNode->next;
	}

	if (currNode->key == key || currNode->next->key == key) {	//there is a node values key
		return 0;
	}

	int newLevel = randLevel();

	if (newLevel >= totalLevel + 1) {
		newLevel = totalLevel + 1;
		totalLevel++;
		skipNode* head = new skipNode(INT_MIN);
		skipNode* tail = new skipNode(INT_MAX, head, nullptr);
		head->next = tail;

		head->lower = header[totalLevel - 1];
		header[totalLevel - 1]->upper = head;

		header.emplace_back(head);
	}
	//cout << "newLevel = " << newLevel << endl;
	//cout << "totalLevel = " << totalLevel << "\theader.size() = " << header.size() << endl;
	//cout << "header[totalLevel] = " << header[totalLevel]->key << endl;
	//return;

	skipNode* lowerNode = new skipNode(key);
	lowerNode->next = currNode->next;
	currNode->next->pre = lowerNode;

	currNode->next = lowerNode;
	lowerNode->pre = currNode;

	for (int i = 1; i <= newLevel; ++i) {
		skipNode* node = new skipNode(key);
		skipNode* currLevelNode = header[i];
		while (currLevelNode->next->key < key) {
			currLevelNode = currLevelNode->next;
		}
		//skipNode* insertLevelNode = new skipNode(key, currLevelNode, currLevelNode->next);
		node->next = currLevelNode->next;
		currLevelNode->next->pre = node;

		currLevelNode->next = node;
		node->pre = currLevelNode;

		node->lower = lowerNode;
		lowerNode->upper = node;

		lowerNode = node;
	}
	return 1;
}

int skipList::deleteNode(elemType target) {
	skipNode* targetNode = findNode(target);
	if (targetNode == nullptr) {
		return 0;
	} else {
		while (targetNode) {
			skipNode* up = targetNode->upper;
			skipNode* currPre = targetNode->pre;
			skipNode* currNext = targetNode->next;
			currPre->next = currNext;
			currNext->pre = currPre;

			if (targetNode->pre->key == INT_MIN && targetNode->next->key == INT_MAX) {
				delete targetNode->pre;
				delete targetNode->next;
				--totalLevel;
				header.pop_back();
			}
			delete targetNode;

			targetNode = up;
		}

		if (header.size() == 0) {
			totalLevel = 0;
			skipNode* dataHeader = new skipNode(INT_MIN);
			skipNode* dataTail = new skipNode(INT_MAX, dataHeader, nullptr);
			dataHeader->next = dataTail;
			header.emplace_back(dataHeader);
		}

		return 1;
	}
}

void skipList::print() {
	std::cout << "\n*******************************************************************************\n";
	for (int i = totalLevel; i >= 0; --i) {
		cout << "level " << i << " : ";
		skipNode* start = header[i]->next;
		while (start->key < INT_MAX) {
			cout << start->key << " -> ";
			start = start->next;
		}
		cout << "NIL" << endl;
	}
	cout << "*******************************************************************************\n\n\n";
}


int main() {
	skipList* sl = new skipList;

	cout << "*******************************************************************************\n";

	cout << "0. exit;\n1. insert a data;\n2. delete a data;\n3. find a data;\n4. show your skip list.\nPlease choose one operation: (0 - 3)\n";

	cout << "*******************************************************************************\n";
	int op;
	while (cin >> op) {
		if (op == 0) {
			return 0;
		} else if (op == 1) {
			cout << "please input data: \n";
			elemType ins;
			cin >> ins;

			int sign = sl->insertNode(ins);
			if (!sign) {
				cout << "\nERROR: The key has been inserted into the skip list. Please check your input.\n\n";
			}

			cout << "The skip list is like :\n";
			sl->print();

		} else if (op == 2) {
			cout << "please enter the key of the node to be deleted: \n";
			elemType del;
			
			cin >> del;

			int sign = sl->deleteNode(del);
			if (!sign) {
				cout << "\nERROR: The key is not found. Please check your input.\n\n";
			}
			cout << "The skip list is like :\n";
			sl->print();
		} else if (op == 3) {
			cout << "please input the data you would like to find: \n";
			elemType tar;
			cin >> tar;
			if (sl->findNode(tar)) {
				cout << "Node found.\n";
			} else {
				cout << "Node not found.\n";
			}
		} else if (op == 4) {
			cout << "The skip list is like :\n";
			sl->print();
		} else {
			cout << "\nERROR: Your choose is invalid. Please try again.\n\n";
		}

		cout << "\n\n\n\n*******************************************************************************\n";

		cout << "0. exit;\n1. insert a data;\n2. delete a data;\n3. find a data;\n4. show your skip list.\nPlease choose one operation: (0 - 3)\n";

		cout << "*******************************************************************************\n";

	}

	system("pause");

	return 0;
}

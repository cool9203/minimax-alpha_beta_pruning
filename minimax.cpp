/*@@人工智慧作業-3
  @@minimax演算法 & alpha beta pruning*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

class Tree {
protected:
	std::vector<int> tree;
	int fork, level;

public:
	Tree(int fork, int level) {
		this->fork = fork;
		this->level = level;
		for (int i = 0; i < math_level(0); i++) {
			tree.push_back(0);
		}
	}


	int math_level(int this_level) {
		int count = 1;
		if (this_level == level - 1)
			return 1;

		for (int i = 1; i <= fork; i++) {
			count += math_level(this_level + 1);
		}
		return count;
	}


	void push(int assign, int data) {
		tree[assign] = data;
	}


	void push(int data) {
		tree.push_back(data);
	}


	void print() {
		int p = 1, l = 1;
		for (int i = 0; i < static_cast<int>(tree.size()); i++) {
			if (i == p) {
				std::cout << "\n";
				p += (int)pow((double)fork, (double)l);
				l++;
			}
			std::cout << tree.at(i) << " ";
		}
	}


	int at(int assign) {
		return tree.at(assign);
	}


	int size() {
		return tree.size();
	}
};


class MiniMax {
protected:
	Tree *tree;
	int fork;
	std::vector<int> pruning, p_index;
	int leftindex;

public:
	MiniMax(int fork,int level) {
		tree = new Tree(fork, level);
		this->fork = fork;
		leftindex = tree->math_level(0);
	}
	

	void push(int data) {
		tree->push(data);
	}


	void push(std::vector<int> data) {
		for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it) {
			tree->push(*it);
		}
	}


	int dfs(int count, bool minmax, int a, int b, bool push) { //true max   false min
		std::vector<int> number;
		if (push) {
			pruning.push_back(tree->at(count));
			p_index.push_back(count);
		}

		if ((fork*count + 1) >= tree->size()) { //if child is null  than  return him
			return tree->at(count);
		}

		//a or b = max(a,child) or min(b,child);
		if (minmax)
			number.push_back(a);
		else
			number.push_back(b);

		for (int i = 1; i <= fork; i++) {
			number.push_back(dfs(fork*count + i, !minmax, a, b, push));
			if (minmax) {
				a = max(number);
			}
			else {
				b = min(number);
			}
			if (a >= b) 
				push = true;
		}

		int m;
		if (minmax) 
			m = max(number);
		else
			m = min(number);
		tree->push(count, m);
		return tree->at(count);
	}


	//no used alpha_beta_pruning's dfs
	int dfs(int count, bool minmax) { //true max   false min
		std::vector<int> number;
		
		if ((fork*count + 1) >= tree->size()) { //if child is null  than  return him
			return tree->at(count);
		}

		for (int i = 1; i <= fork; i++) {
			number.push_back(dfs(fork*count + i, !minmax));
		}

		int m;
		if (minmax) {
			m = max(number);
		}
		else {
			m = min(number);
		}
		tree->push(count, m);
		return tree->at(count);
	}
	

	void print_pruning() {
		int count = 0;
		for (int i = 0; i < static_cast<int>(pruning.size()); i++) {
			if (p_index.at(i) >= leftindex)
				count++;
		}
		std::cout << "\n\n" << count << " ";
		for (int i = 0; i < static_cast<int>(pruning.size()); i++) {
			if (p_index.at(i) >= leftindex)
				std::cout << pruning.at(i) << "(" << p_index.at(i) << ") ";
		}
	}


	void print() {
		tree->print();
	}


	template<class T>
	int max(T data) {
		int m = data.at(0);
		for (T::iterator it = data.begin(); it != data.end(); ++it) {
			if (*it > m)
				m = *it;
		}
		return m;
	}


	template<class T>
	int min(T data) {
		int m = data.at(0);
		for (T::iterator it = data.begin(); it != data.end(); ++it) {
			if (*it < m)
				m = *it;
		}
		return m;
	}
};


int main() {
	std::fstream file;
	std::vector<int> number;
	char ch;
	file.open("test.txt", std::ios::in);
	if (!file) {
		std::cout << "file open failed.\n";
		file.close();
		system("PAUSE");
		return 0;
	}
	
	file.get(ch);
	int fork = ch - 48;
	file.get(ch);
	file.get(ch);
	int level = ch - 48;

	std::stringstream ss;
	std::string str;
	while (file.get(ch)) {
		if (ch != ' ') {
			ss << ch;
		}
		else {
			ss >> str;
			number.push_back(std::atoi(str.c_str()));
			ss.str("");
			ss.clear();
		}
	}
	ss >> str;
	number.push_back(std::atoi(str.c_str()));
	
	file.close();
	
	MiniMax m(fork, level);
	m.push(number);

	//m.dfs(0, true);
	m.dfs(0, true, -99999, 99999, false);
	m.print();
	m.print_pruning();

	system("PAUSE");
	return 0;
}

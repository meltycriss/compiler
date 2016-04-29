#ifndef ELIMILATOR_H
#define ELIMILATOR_H

#include <vector>
#include <set>
#include <string>
#include <map>
#include <algorithm>

const int SELF_PRODUCTION = 0;
const int UNREACHABLE = 1;
const int USELESS = 2;

class DeleteItem{
public:
	DeleteItem(){}
	DeleteItem(int _type, char _var = '#',
		const std::vector<std::pair<char, std::string> >& _pd = std::vector<std::pair<char, std::string> >())
		:type(_type), var(_var), productions(_pd){}
	int type;
	char var;
	std::vector<std::pair<char, std::string> > productions;
};

class Eliminator{
public:
	void init();
	void eliminate();
	void print() const;
private:
	char start;
	std::vector<char> nonTerminals;
	std::vector<char> terminals;
	std::vector<std::pair<char, std::string> > productions;
	std::vector<DeleteItem> deleteItems;
	std::map<char, bool> isNonTerminalExist;
	std::map<char, std::vector<std::string> > finalProduction;

	void eliminateSelfProduction();
	bool eliminateUnreachable();
	bool eliminateUseless();

	bool isSelfProduction(char, const std::string&) const;

	std::map<char, std::vector<std::string> > getProductionMap();

	bool isNonTerminal(char _c) const{
		return find(nonTerminals.cbegin(), nonTerminals.cend(), _c) != nonTerminals.cend();
	}

	bool isCharInProduction(char _c, const std::pair<char, std::string>& _p) const{
		return _c == _p.first || _p.second.find(_c) != std::string::npos;
	}

	std::vector<std::pair<char, std::string> > deleteProductionWithChar(char);

	bool isProductionUseful(const std::string& _str, const std::set<char>& _set) const{
		bool isUseful = true;
		for (std::string::size_type i = 0; i < _str.size(); ++i){
			char c = _str[i];
			if (_set.find(c) == _set.end()) isUseful = false;
		}
		return isUseful;
	}


	bool deleteNonTerminalNotInSet(int, const std::set<char>&);
};

#endif
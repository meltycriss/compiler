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

// a class used to help output
class DeleteItem{
public:
	DeleteItem(){}
	DeleteItem(int _type, char _var = '#',
		const std::vector<std::pair<char, std::string> >& _pd = std::vector<std::pair<char, std::string> >())
		:type(_type), var(_var), productions(_pd){}
	int type; //kind of delete
	char var; //non-terminal deleted
	std::vector<std::pair<char, std::string> > productions; //associated productions of the deleted non-terminal
};

class Eliminator{
public:
	void init();
	void eliminate();
	void print() const;
private:
	char start; //start non-terminal
	std::vector<char> nonTerminals;
	std::vector<char> terminals;
	std::vector<std::pair<char, std::string> > productions; //each production is represented as pair<left non-termianl, right expression>
	std::vector<DeleteItem> deleteItems; //recording the process of deletion
	std::map<char, bool> isNonTerminalExist; //check whether the non-terminal exists

	void eliminateSelfProduction();
	bool eliminateUnreachable();
	bool eliminateUseless();

/*
	input: a char and a right expression
	output: whether the right expression is exactly the char
*/
	bool isSelfProduction(char, const std::string&) const;

/*
	output: a map corresponding to current productions	
*/
	std::map<char, std::vector<std::string> > getProductionMap();

	bool isNonTerminal(char _c) const{
		return find(nonTerminals.cbegin(), nonTerminals.cend(), _c) != nonTerminals.cend();
	}

/*
	input: a char and a production
	output: whether the char shows up in the left hand side or right hand side of the production
*/
	bool isCharInProduction(char _c, const std::pair<char, std::string>& _p) const{
		return _c == _p.first || _p.second.find(_c) != std::string::npos;
	}

/*
	input: a char
	output: deleted productions which containing the char
*/
	std::vector<std::pair<char, std::string> > deleteProductionWithChar(char);

/*
	intput: a right hand expression of a production and a set of useful char
	output: whether the characters of the expression are all in the set
*/
	bool isProductionUseful(const std::string& _str, const std::set<char>& _set) const{
		bool isUseful = true;
		for (std::string::size_type i = 0; i < _str.size(); ++i){
			char c = _str[i];
			if (_set.find(c) == _set.end()) isUseful = false;
		}
		return isUseful;
	}

/*
	function: delete all non-terminal not in the given set, the deletion including modifying productions and isNonTermianlExists
	intput: a deletion type and a set
	output: whether really delete some non-terminal
*/
	bool deleteNonTerminalNotInSet(int, const std::set<char>&);
};

#endif
#ifndef LEXER_H
#define LEXER

#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <utility>

/*
	base class for all regular expression
*/
class RegExpr{
public:
	/*
		input: string
		output: string's index in the wordsbag
		caution: if string doesn't exists in the wordsbag, this function will return the size of wordsbag
	*/
	int operator()(std::string _str) const { return std::find(words.begin(), words.end(), _str) - words.begin(); }

	int getWordsSize() const{ return words.size(); }
protected:
	std::vector<std::string> words; //wordsbag
	static const std::set<char> letter; //a set of letter character
	static const std::set<char> digit; //a set of digit character
};

class KeywordRegExpr :public RegExpr{
public:
	KeywordRegExpr(){
		words.push_back("int");
		words.push_back("main");
		words.push_back("return");
	}
};

class OperatorRegExpr :public RegExpr{
public:
	OperatorRegExpr(){
		words.push_back("+");
		words.push_back("*");
		words.push_back("=");
		words.push_back("+=");
		words.push_back("*=");
	}
};

class BoundaryRegExpr :public RegExpr{
public:
	BoundaryRegExpr(){
		words.push_back("(");
		words.push_back(")");
		words.push_back("{");
		words.push_back("}");
		words.push_back(",");
		words.push_back(";");
	}
};

class IdentifierRegExpr :public RegExpr{
public:
	bool isIdentifier(const std::string &_str) const {
		for (int i = 0; i < _str.size(); ++i){
			char c = _str[i];
			if (i == 0){
				if (letter.find(c) == letter.end()) return false;
			}
			else{
				if (letter.find(c) == letter.end() && digit.find(c) == digit.end()) return false;
			}
		}
		return true;
	}

	void pushIdentifier(const std::string &_str){
		words.push_back(_str);
	}

	std::vector<std::string> getIdentifiers() const{ return words; }
};

class UnsignedIntegerRegExpr :public RegExpr{
public:
	bool isUnsignedInteger(const std::string &_str) const{
		for (int i = 0; i < _str.size(); ++i){
			char c = _str[i];
			if (i == 0){
				if (c == '0' || digit.find(c) == digit.end()) return false;
			}
			else{
				if (digit.find(c) == digit.end()) return false;
			}
		}
		return true;
	}

	void pushUnsignedInteger(const std::string &_str){
		words.push_back(_str);
	}

	std::vector<std::string> getUnsignedIntegers() const{ return words; }
};

class BlankRegExpr :public RegExpr{
public:
	BlankRegExpr(){
		words.push_back(" ");
		words.push_back("\t");
		words.push_back("\n");
	}
};

class Lexer{
public:
/*
	read in the program
*/
	void init();

/*
	push pair<type, index> into the result vector
*/
	void lexicalAnalyze();

/*
	print out the formatted result using result vector
*/
	void print();

private:
	const static int KEYWORD;
	const static int OPERATOR;
	const static int BOUNDARY;
	const static int IDENTIFIER;
	const static int UNSIGNED_INTEGER;
	const static int BLANK;
	const static int ERROR;

	KeywordRegExpr keyword;
	OperatorRegExpr opt;
	BoundaryRegExpr boundary;
	IdentifierRegExpr identifier;
	UnsignedIntegerRegExpr unsignedInteger;
	BlankRegExpr blank;

	std::string input; //storage of the program

	std::vector<std::pair<int, int> > res; //result vector containing pair<type, string's index in the corresponding wordsbag>

/*
	input: a string
	output: pair<type, string's index in wordsbag>
	caution: for identifier and unsignedInteger, if the string is of that type but not in wordsbag, pair<type, -1> will be returned
*/
	std::pair<int,int> getType(const std::string&) const;


/*
	input: string, type of string, string's index in corresponding wordsbag
	output: 0 fail, 1 success
	caution: for identifier and unsignedInteger, if thte string is not in the wordsbag, this function will push the string in the corresponding wordsbag
*/
	bool pushRes(int, int, const std::string&);

/*
	for debugging
*/
	void printType(int _i);

};
#endif
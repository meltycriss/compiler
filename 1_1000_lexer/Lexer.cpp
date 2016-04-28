#include "Lexer.h"
#include <iostream>

using namespace std;

//initialize a static member variable stl container
set<char> initLetter(){
	set<char> letter;
	for (char c = 'a'; c <= 'z'; c++) letter.insert(c);
	for (char c = 'A'; c <= 'Z'; c++) letter.insert(c);
	return letter;
}

set<char> initDigit(){
	set<char> digit;
	for (char c = '0'; c <= '9'; c++) digit.insert(c);
	return digit;
}

const set<char> RegExpr::letter(initLetter());

const set<char> RegExpr::digit(initDigit());

const int Lexer::KEYWORD = 1;
const int Lexer::OPERATOR = 2;
const int Lexer::BOUNDARY = 3;
const int Lexer::IDENTIFIER = 4;
const int Lexer::UNSIGNED_INTEGER = 5;
const int Lexer::BLANK = 6;
const int Lexer::ERROR = 7;

pair<int, int> Lexer::getType(const string& _str) const{
	int idx;
	if ((idx = keyword(_str)) != keyword.getWordsSize()) return make_pair(KEYWORD, idx);
	else if ((idx = opt(_str)) != opt.getWordsSize()) return make_pair(OPERATOR, idx);
	else if ((idx = boundary(_str)) != boundary.getWordsSize()) return make_pair(BOUNDARY, idx);
	else if ((idx = identifier(_str)) != identifier.getWordsSize()) return make_pair(IDENTIFIER, idx);
	else if (identifier.isIdentifier(_str)) return make_pair(IDENTIFIER, -1);
	else if ((idx = unsignedInteger(_str)) != unsignedInteger.getWordsSize()) return make_pair(UNSIGNED_INTEGER, idx);
	else if (unsignedInteger.isUnsignedInteger(_str)) return make_pair(UNSIGNED_INTEGER, -1);
	else if ((idx = blank(_str)) != blank.getWordsSize()) return make_pair(BLANK, idx);
	else return make_pair(ERROR, -1);
}

bool Lexer::pushRes(int _type, int _idx, const std::string& _str){
	switch (_type)
	{
	case ERROR:{
				   return false;
	}
	case BLANK:{
				   break;
	}
	case IDENTIFIER:{
						if (_idx == -1){
							identifier.pushIdentifier(_str);
							res.push_back(make_pair(IDENTIFIER, identifier.getWordsSize() - 1));

						}
						else{
							res.push_back(make_pair(IDENTIFIER, _idx));
						}
						break;
	}
	case UNSIGNED_INTEGER:{
							  if (_idx == -1){
								  unsignedInteger.pushUnsignedInteger(_str);
								  res.push_back(make_pair(UNSIGNED_INTEGER, unsignedInteger.getWordsSize() - 1));
							  }
							  else{
								  res.push_back(make_pair(UNSIGNED_INTEGER, _idx));
							  }
							  break;
	}
	case KEYWORD:{
					 res.push_back(make_pair(KEYWORD, _idx));
					 break;
	}
	case OPERATOR:{
					  res.push_back(make_pair(OPERATOR, _idx));
					  break;
	}
	case BOUNDARY:{
					  res.push_back(make_pair(BOUNDARY, _idx));
					  break;
	}
	default:
		return false;
		break;
	}
	return true;
}

void Lexer::init(){
	getline(cin, input, '#');
}

void Lexer::lexicalAnalyze()
{
	string::const_iterator beg, end;
	int curType, curIdx, lastType, lastIdx;

	beg = input.begin();
	end = beg + 1;

	while (beg != input.end()){
		pair<int, int> temp = getType(string(beg, end));
		lastType = curType = temp.first;
		lastIdx = curIdx = temp.second;
		while (end != input.end() && curType != ERROR){
			lastType = curType;
			lastIdx = curIdx;
			temp = getType(string(beg, end + 1));
			curType = temp.first;
			curIdx = temp.second;
			++end;
		}

		if (curType == ERROR){
			pushRes(lastType, lastIdx, string(beg, end - 1));
			//cout << string(beg, end - 1) << endl;
			beg = end - 1;
			end = beg + 1;
		}
		else{
			pushRes(curType, curIdx, string(beg, end));
			//cout << string(beg, end) << endl;
			beg = end;
		}
	}
}

void Lexer::print(){
	for (int i = 0; i < res.size(); ++i){
		pair<int, int> p = res[i];
		cout << "<" << p.first << "," << p.second << ">";
	}
	cout << endl;
	cout << "identifieres:";
	vector<string> id = identifier.getIdentifiers();
	for (int i = 0; i < id.size(); ++i){
		if (i == 0) cout << id[i];
		else cout << " " << id[i];
	}
	cout << endl;
	cout << "Unsigned_integer:";
	vector<string> ui = unsignedInteger.getUnsignedIntegers();
	for (int i = 0; i < ui.size(); ++i){
		if (i == 0) cout << ui[i];
		else cout << " " << ui[i];
	}
	cout << endl;
}

void Lexer::printType(int _i){
	switch (_i)
	{
	case KEYWORD:cout << "KEYWORD" << endl; break;
	case OPERATOR:cout << "OPERATOR" << endl; break;
	case BOUNDARY:cout << "BOUNDARY" << endl; break;
	case IDENTIFIER:cout << "IDENTIFIER" << endl; break;
	case UNSIGNED_INTEGER:cout << "UNSIGNED_INTEGER" << endl; break;
	case BLANK:cout << "BLANK" << endl; break;
	case ERROR:cout << "ERROR" << endl; break;
	default:cout << "WTF" << endl; break;
	}
}
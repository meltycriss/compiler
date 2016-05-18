#include "Elimilator.h"
#include <iostream>
#include <queue>
using namespace std;

void Eliminator::init(){
	nonTerminals.clear();
	terminals.clear();
	productions.clear();
	deleteItems.clear();
	isNonTerminalExist.clear();
	finalProduction.clear();

	int n;
	char c;
	string s;

	cin >> start;

	cin >> n;
	while (n--){
		cin >> c;
		nonTerminals.push_back(c);
		isNonTerminalExist[c] = true;
	}

	cin >> n;
	while (n--){
		cin >> c;
		terminals.push_back(c);
	}

	cin >> n;
	while (n--){
		cin >> c >> s;
		productions.push_back(make_pair(c, s));
	}
}

bool Eliminator::isSelfProduction(char _c, const string& _s) const{
	return _s.size() == 1 && _c == _s[0];
}


void Eliminator::eliminateSelfProduction(){
	vector<pair<char, string> >::iterator it = productions.begin();
	while (it != productions.end()){
		if (isSelfProduction(it->first, it->second)){
			deleteItems.push_back(DeleteItem(SELF_PRODUCTION, it->first));
			vector<int>::difference_type dif = it - productions.begin();
			productions.erase(it);
			it = productions.begin() + dif;
		}
		else{
			it++;
		}
	}
}

map<char, vector<string> > Eliminator::getProductionMap(){
	map<char, vector<string> > res;
	vector<pair<char, string> >::iterator it = productions.begin();
	while (it != productions.end()){
		res[it->first].push_back(it->second);
		++it;
	}
	return res;
}

vector<pair<char, string> > Eliminator::deleteProductionWithChar(char _c){
	vector<pair<char, string> > res;
	vector<pair<char, string> >::iterator it = productions.begin();
	while (it != productions.end()){
		if (isCharInProduction(_c, *it)){
			res.push_back(*it);
			vector<int>::difference_type dif = it - productions.begin();
			productions.erase(it);
			it = productions.begin() + dif;
		}
		else{
			it++;
		}
	}
	return res;
}

bool Eliminator::deleteNonTerminalNotInSet(int _type, const set<char>& _useful){
	bool deleteNonTerminal = false;
	vector<char>::reverse_iterator it = nonTerminals.rbegin();
	while (it != nonTerminals.rend()){
		char c = *it;
		if (isNonTerminalExist[c] && _useful.find(c) == _useful.end()){
			deleteNonTerminal = true;
			isNonTerminalExist[c] = false;
			vector<pair<char, string> > deletedProduction = deleteProductionWithChar(c);
			deleteItems.push_back(DeleteItem(_type, c, deletedProduction));
		}
		++it;
	}
	return deleteNonTerminal;
}

bool Eliminator::eliminateUnreachable(){
	set<char> reachable;
	queue<char> q;
	map<char, vector<string> > productionMap = getProductionMap();
	reachable.insert(start);
	q.push(start);
	while (!q.empty()){
		char src = q.front();
		q.pop();
		vector<string>::const_iterator it = productionMap[src].begin();
		while (it != productionMap[src].end()){
			string right = *it;
			for (int i = 0; i < right.size(); ++i){
				if (isNonTerminal(right[i]) && reachable.find(right[i]) == reachable.end()){
					reachable.insert(right[i]);
					q.push(right[i]);
				}
			}
			++it;
		}
	}
	return deleteNonTerminalNotInSet(UNREACHABLE, reachable);
}


bool Eliminator::eliminateUseless(){
	set<char> useful(terminals.begin(), terminals.end());
	int lastSize = -1;
	while (useful.size() != lastSize){
		lastSize = useful.size();
		vector<pair<char, string> >::iterator it = productions.begin();
		while (it != productions.end()){
			string right = it->second;
			if (isProductionUseful(right, useful)){
				useful.insert(it->first);
			}
			++it;
		}
	}
	return deleteNonTerminalNotInSet(USELESS, useful);
}


void Eliminator::eliminate(){
	eliminateSelfProduction();
	while (eliminateUnreachable() || eliminateUseless());
}

void Eliminator::print() const{
	vector<DeleteItem>::const_iterator it = deleteItems.begin();
	while (it != deleteItems.end()){
		switch (it->type)
		{
		case SELF_PRODUCTION:{
								 cout << "delete self production:";
								 cout << it->var << "::=" << it->var << endl;
								 break;
		}
		case UNREACHABLE:{
							 cout << "unreached Vn:" << it->var << endl;
							 cout << "delete VN:" << it->var << endl;
							 vector<pair<char, string> >::const_iterator it_pd = it->productions.begin();
							 while (it_pd != it->productions.end()){
								 cout << "delete production:" << it_pd->first << "::=" << it_pd->second << endl;
								 ++it_pd;
							 }
							 break;
		}
		case USELESS:{
						 cout << "unusefulNv:" << it->var << endl;
						 cout << "delete VN:" << it->var << endl;
						 vector<pair<char, string> >::const_iterator it_pd = it->productions.begin();
						 while (it_pd != it->productions.end()){
							 cout << "delete production:" << it_pd->first << "::=" << it_pd->second << endl;
							 ++it_pd;
						 }
						 break;
		}
		default:
			break;
		}
		++it;
	}
	cout << "G[" << start << "]:" << endl;
	vector<char>::const_iterator it_NT = nonTerminals.begin();
	while (it_NT != nonTerminals.end()){
		char c = *it_NT;
		int count = 0;
		if ((*isNonTerminalExist.find(c)).second) {
			vector<pair<char, string> >::const_iterator it_pd = productions.begin();
			while (it_pd != productions.end()){
				if (it_pd->first == c){
					if (count == 0){
						cout << it_pd->first << "::=" << it_pd->second;
					}
					else{
						cout << " | " << it_pd->second;
					}
					++count;
				}
				++it_pd;
			}
			cout << endl;
		}
		++it_NT;
	}
}
//#ifndef ELIMILATOR_H
//#define ELIMILATOR_H
//
//#include <vector>
//#include <set>
//#include <string>
//#include <map>
//#include <algorithm>
//
//const int SELF_PRODUCTION = 0;
//const int UNREACHABLE = 1;
//const int USELESS = 2;
//
//class DeleteItem{
//public:
//	DeleteItem(){}
//	DeleteItem(int _type, char _var = '#',
//		const std::vector<std::pair<char, std::string> >& _pd = std::vector<std::pair<char, std::string> >())
//		:type(_type), var(_var), productions(_pd){}
//	int type;
//	char var;
//	std::vector<std::pair<char, std::string> > productions;
//};
//
//class Eliminator{
//public:
//	void init();
//	void eliminate();
//	void print() const;
//private:
//	char start;
//	std::vector<char> nonTerminals;
//	std::vector<char> terminals;
//	std::vector<std::pair<char, std::string> > productions;
//	std::vector<DeleteItem> deleteItems;
//	std::map<char, bool> isNonTerminalExist;
//	std::map<char, std::vector<std::string> > finalProduction;
//
//	void eliminateSelfProduction();
//	bool eliminateUnreachable();
//	bool eliminateUseless();
//
//	bool isSelfProduction(char, const std::string&) const;
//
//	std::map<char, std::vector<std::string> > getProductionMap();
//
//	bool isNonTerminal(char _c) const{
//		return find(nonTerminals.begin(), nonTerminals.end(), _c) != nonTerminals.end();
//	}
//
//	bool isCharInProduction(char _c, const std::pair<char, std::string>& _p) const{
//		return _c == _p.first || _p.second.find(_c) != std::string::npos;
//	}
//
//	std::vector<std::pair<char, std::string> > deleteProductionWithChar(char);
//
//	bool isProductionUseful(const std::string& _str, const std::set<char>& _set) const{
//		bool isUseful = true;
//		for (std::string::size_type i = 0; i < _str.size(); ++i){
//			char c = _str[i];
//			if (_set.find(c) == _set.end()) isUseful = false;
//		}
//		return isUseful;
//	}
//
//
//	bool deleteNonTerminalNotInSet(int, const std::set<char>&);
//};
//
//#endif
//
//#include <iostream>
//#include <queue>
//using namespace std;
//
//void Eliminator::init(){
//	nonTerminals.clear();
//	terminals.clear();
//	productions.clear();
//	deleteItems.clear();
//	isNonTerminalExist.clear();
//	finalProduction.clear();
//
//	int n;
//	char c;
//	string s;
//
//	cin >> start;
//
//	cin >> n;
//	while (n--){
//		cin >> c;
//		nonTerminals.push_back(c);
//		isNonTerminalExist[c] = true;
//	}
//
//	cin >> n;
//	while (n--){
//		cin >> c;
//		terminals.push_back(c);
//	}
//
//	cin >> n;
//	while (n--){
//		cin >> c >> s;
//		productions.push_back(make_pair(c, s));
//	}
//}
//
//bool Eliminator::isSelfProduction(char _c, const string& _s) const{
//	return _s.size() == 1 && _c == _s[0];
//}
//
//
//void Eliminator::eliminateSelfProduction(){
//	vector<pair<char, string> >::iterator it = productions.begin();
//	while (it != productions.end()){
//		if (isSelfProduction(it->first, it->second)){
//			deleteItems.push_back(DeleteItem(SELF_PRODUCTION, it->first));
//			vector<int>::difference_type dif = it - productions.begin();
//			productions.erase(it);
//			it = productions.begin() + dif;
//		}
//		else{
//			it++;
//		}
//	}
//}
//
//map<char, vector<string> > Eliminator::getProductionMap(){
//	map<char, vector<string> > res;
//	vector<pair<char, string> >::iterator it = productions.begin();
//	while (it != productions.end()){
//		res[it->first].push_back(it->second);
//		++it;
//	}
//	return res;
//}
//
//vector<pair<char, string> > Eliminator::deleteProductionWithChar(char _c){
//	vector<pair<char, string> > res;
//	vector<pair<char, string> >::iterator it = productions.begin();
//	while (it != productions.end()){
//		if (isCharInProduction(_c, *it)){
//			res.push_back(*it);
//			vector<int>::difference_type dif = it - productions.begin();
//			productions.erase(it);
//			it = productions.begin() + dif;
//		}
//		else{
//			it++;
//		}
//	}
//	return res;
//}
//
//bool Eliminator::deleteNonTerminalNotInSet(int _type, const set<char>& _useful){
//	bool deleteNonTerminal = false;
//	vector<char>::reverse_iterator it = nonTerminals.rbegin();
//	while (it != nonTerminals.rend()){
//		char c = *it;
//		if (isNonTerminalExist[c] && _useful.find(c) == _useful.end()){
//			deleteNonTerminal = true;
//			isNonTerminalExist[c] = false;
//			vector<pair<char, string> > deletedProduction = deleteProductionWithChar(c);
//			deleteItems.push_back(DeleteItem(_type, c, deletedProduction));
//		}
//		++it;
//	}
//	return deleteNonTerminal;
//}
//
//bool Eliminator::eliminateUnreachable(){
//	set<char> reachable;
//	queue<char> q;
//	map<char, vector<string> > productionMap = getProductionMap();
//	reachable.insert(start);
//	q.push(start);
//	while (!q.empty()){
//		char src = q.front();
//		q.pop();
//		vector<string>::const_iterator it = productionMap[src].begin();
//		while (it != productionMap[src].end()){
//			string right = *it;
//			for (int i = 0; i < right.size(); ++i){
//				if (isNonTerminal(right[i]) && reachable.find(right[i]) == reachable.end()){
//					reachable.insert(right[i]);
//					q.push(right[i]);
//				}
//			}
//			++it;
//		}
//	}
//	return deleteNonTerminalNotInSet(UNREACHABLE, reachable);
//}
//
//
//bool Eliminator::eliminateUseless(){
//	set<char> useful(terminals.begin(), terminals.end());
//	int lastSize = -1;
//	while (useful.size() != lastSize){
//		lastSize = useful.size();
//		vector<pair<char, string> >::iterator it = productions.begin();
//		while (it != productions.end()){
//			string right = it->second;
//			if (isProductionUseful(right, useful)){
//				useful.insert(it->first);
//			}
//			++it;
//		}
//	}
//	return deleteNonTerminalNotInSet(USELESS, useful);
//}
//
//
//void Eliminator::eliminate(){
//	eliminateSelfProduction();
//	while (eliminateUnreachable() || eliminateUseless());
//}
//
//void Eliminator::print() const{
//	vector<DeleteItem>::const_iterator it = deleteItems.begin();
//	while (it != deleteItems.end()){
//		switch (it->type)
//		{
//		case SELF_PRODUCTION:{
//								 cout << "delete self production:";
//								 cout << it->var << "::=" << it->var << endl;
//								 break;
//		}
//		case UNREACHABLE:{
//							 cout << "unreached Vn:" << it->var << endl;
//							 cout << "delete VN:" << it->var << endl;
//							 vector<pair<char, string> >::const_iterator it_pd = it->productions.begin();
//							 while (it_pd != it->productions.end()){
//								 cout << "delete production:" << it_pd->first << "::=" << it_pd->second << endl;
//								 ++it_pd;
//							 }
//							 break;
//		}
//		case USELESS:{
//						 cout << "unusefulNv:" << it->var << endl;
//						 cout << "delete VN:" << it->var << endl;
//						 vector<pair<char, string> >::const_iterator it_pd = it->productions.begin();
//						 while (it_pd != it->productions.end()){
//							 cout << "delete production:" << it_pd->first << "::=" << it_pd->second << endl;
//							 ++it_pd;
//						 }
//						 break;
//		}
//		default:
//			break;
//		}
//		++it;
//	}
//	cout << "G[" << start << "]:" << endl;
//	vector<char>::const_iterator it_NT = nonTerminals.begin();
//	while (it_NT != nonTerminals.end()){
//		char c = *it_NT;
//		int count = 0;
//		if ((*isNonTerminalExist.find(c)).second) {
//			vector<pair<char, string> >::const_iterator it_pd = productions.begin();
//			while (it_pd != productions.end()){
//				if (it_pd->first == c){
//					if (count == 0){
//						cout << it_pd->first << "::=" << it_pd->second;
//					}
//					else{
//						cout << " | " << it_pd->second;
//					}
//					++count;
//				}
//				++it_pd;
//			}
//			cout << endl;
//		}
//		++it_NT;
//	}
//}
//
//using namespace std;
//
//int main(){
//	Eliminator eliminator;
//	eliminator.init();
//	eliminator.eliminate();
//	eliminator.print();
//
//	//system("pause");
//	return 0;
//}
#include "eNDFA.h"
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

const char eNDFA::EPSILON = 'k';

State::State(int _id, bool _isStart, bool _isAccept) :id(_id), isStart(_isStart),
isAccept(_isAccept){}

DtmState::DtmState(int _id, bool _isStart, bool _isAccept, const set<int>& _subState) : State(_id, _isStart, _isAccept),
subState(_subState){}

/*
	input: state id
	output: set of state's epsilon closure
*/
set<int> eNDFA::getEClosure(int _id) const{
	int startState = _id;
	vector<bool> vis(states.size(), false);
	queue<int> q;
	set<int> res;
	vis[startState] = true;
	q.push(startState);
	while (!q.empty()){
		int src = q.front();
		q.pop();
		res.insert(src);
		const State& s = states[src];
		if (s.trans.find(EPSILON) != s.trans.end()){
			map<char, set<int> > ::const_iterator it_mp = s.trans.find(EPSILON);
			const set<int>& eSet = it_mp->second;
			set<int>::const_iterator it_set = eSet.begin();
			while (it_set != eSet.end()){
				int dst = *it_set;
				if (!vis[dst]){
					vis[dst] = true;
					q.push(dst);
				}
				++it_set;
			}
		}
	}
	return res;
}

/*
	input: subset of state, input char
	output: subset of state that can reached by input subset, given input char
*/
set<int> eNDFA::getSubStateWithInput(const set<int>& _s, char _c) const{
	set<int> res;
	set<int>::const_iterator it_s = _s.begin();
	while (it_s != _s.end()){
		int id = *it_s;
		const State& s = states[id];
		if (s.trans.find(_c) != s.trans.end()){
			map<char, set<int> > ::const_iterator it_mp = s.trans.find(_c);
			const set<int>& eSet = it_mp->second;
			res.insert(eSet.begin(), eSet.end());
		}
		++it_s;
	}
	return res;
}

/*
	input: subset of state
	output: index of subset in dtmStates
*/
int eNDFA::getSubStateIdx(const set<int>& _s) const{
	for (int i = 0; i < dtmStates.size(); ++i){
		const DtmState& ds = dtmStates[i];
		if (_s == ds.subState) return i;
	}
	return dtmStates.size();
}

/*
	intput: subset of state
	output: whether the subset is an accepted state
*/
bool eNDFA::isSubStateAccept(const set<int>& _s) const{
	set<int>::const_iterator it = _s.begin();
	while (it != _s.end()){
		int id = *it;
		if (states[id].isAccept) return true;
		++it;
	}
	return false;
}

/*
	input: index of a dtmState
	output: modify correspoinding dtmState's transition table
*/
void eNDFA::setDtmState(int _idx){
	set<int> nextState, eClosure, tempSet;

	for (int i = 0; i < input.size(); ++i){
		DtmState &_ds = dtmStates[_idx];
		nextState.clear();
		eClosure.clear();

		char c = input[i];
		tempSet = getSubStateWithInput(_ds.subState, c);
		nextState.insert(tempSet.begin(), tempSet.end());

		set<int>::const_iterator it = nextState.begin();
		while (it != nextState.end()){
			tempSet = getEClosure(*it);
			eClosure.insert(tempSet.begin(), tempSet.end());
			++it;
		}
		eClosure.insert(nextState.begin(), nextState.end());

		if (eClosure.size() > 0){
			int idx = getSubStateIdx(eClosure);
			if (idx == dtmStates.size()){
				bool isStart = false;
				bool isAccept = isSubStateAccept(eClosure);
				dtmStates.push_back(DtmState(idx, isStart, isAccept, eClosure));
				//push_back之后_ds变了- -妈的
			}
			DtmState &_ds = dtmStates[_idx];
			_ds.trans[c].insert(idx);
		}
	}
}

void eNDFA::init(){
	int n;
	cin >> n;

	input.clear();
	input.resize(n);
	for (int i = 0; i < n; ++i) cin >> input[i];

	int id;
	bool isStart, isAccept;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> id >> isStart >> isAccept;
		states.push_back(State(id, isStart, isAccept));
	}

	int src, dst;
	char c;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> src >> dst >> c;
		states[src].trans[c].insert(dst);
	}
}

void eNDFA::toDFA(){
	int idx = 0;
	bool isStart = false;
	bool isAccept = false;
	set<int> startState;
	for (int i = 0; i < states.size(); ++i){
		if (states[i].isStart){
			startState.insert(i);
			isStart = true;
			if (states[i].isAccept) isAccept = true;
		}
	}
	dtmStates.push_back(DtmState(idx, isStart, isAccept, startState));
	for (int i = 0; i < dtmStates.size(); i++){
		setDtmState(i);
	}
}

void eNDFA::print() const{
	cout << "Determine State:" << endl;
	for (int i = 0; i < dtmStates.size(); ++i){
		const DtmState& ds = dtmStates[i];
		set<int>::const_iterator it = ds.subState.begin();
		cout << ds.id << " " << ds.isStart << " " << ds.isAccept << " [";
		while (it != ds.subState.end()){
			cout << (*it);
			++it;
		}
		cout << "]" << endl;
	}
	cout << "Determine Mapping:" << endl;

	int mpIdx = 0;
	for (int i = 0; i < dtmStates.size(); ++i){
		const DtmState& ds = dtmStates[i];
		map<char, set<int> >::const_iterator it_mp = ds.trans.begin();
		while (it_mp != ds.trans.end()){
			set<int>::const_iterator it_set = it_mp->second.begin();
			while (it_set != it_mp->second.end()){
				cout << ds.id << " " << (*it_set) << " " << it_mp->first << " (" << mpIdx << endl;
				++it_set;
				mpIdx++;
			}
			++it_mp;
		}

	}
}

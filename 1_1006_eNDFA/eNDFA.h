#ifndef eNDFA_H
#define eNDFA_H

#include <vector>
#include <map>
#include <set>

class State{
public:
	State(){}
	State(int, bool, bool);
	int id;
	bool isStart;
	bool isAccept;
	std::map<char, std::set<int> >  trans;
};

// determine state in DFA, where each state is a subset of state in epsilonNDFA
class DtmState: public State{
public:
	std::set<int> subState;
	DtmState(){}
	DtmState(int, bool, bool, const std::set<int> &);
};

class eNDFA{
private:
	std::vector<char> input; //input alphabet

	std::vector<State> states; //states in epsilonNDFA

	std::vector<DtmState> dtmStates; //states in DFA

	std::set<int> getEClosure(int) const; //get epsilonClosure of an epsilonNDFA state

	std::set<int> getSubStateWithInput(const std::set<int>&, char) const; //get accessible state of a DFA state given an input character

	int getSubStateIdx(const std::set<int>&) const; //get the index of a state in DFA

	bool isSubStateAccept(const std::set<int>&) const; //check whether a state in DFA is accepted state

	void setDtmState(int); //configure the transition table of a state in DFA


public:
	static const char EPSILON;

	eNDFA(){}

	void init();

	void toDFA();

	void print() const;
};


#endif
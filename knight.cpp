/*
 *  Copyright (C)  Peter Lin (rootlocus@yahoo.com)
 *  Tested under Microsoft Visual Studio 2010
 *
 */

#include <iostream>
#include <string>
#include <utility>
#include <queue>
#include <map>
#include <stack>
using namespace std;

typedef pair<int, int> vertice;

class vertice_wrap : public vertice{
public:
	vertice_wrap(int f, int s, int d=0) : vertice(f, s), visited(false), distance(d) {}

	bool is_valid() {return (vertice::first<=8)&&(vertice::first>=1)&&\
		                    (vertice::second<=8)&&(vertice::second>=1);}
	void mark() {visited = true;}
	bool is_marked() {return visited;}
	int  get_distance() {return distance;}

private:
	bool visited;    //mark current vertice as 'visited'
	int  distance;   //distance of current vertice from 'start'
};
typedef pair<vertice_wrap, vertice_wrap> v_pair;


//BFS algorithm @ http://en.wikipedia.org/wiki/Breadth-first_search
void bfs(vertice_wrap v_start, vertice_wrap v_end) {
	if(!(v_start.is_valid()&&(v_end.is_valid()))) {
		return;
	}
	queue<vertice_wrap> q;
	q.push(v_start);
	v_start.mark();

	map<vertice_wrap, vertice_wrap> m; //remember 'previous' vertice to trace path

	while(!q.empty()) {
		vertice_wrap v = q.front();
		q.pop();

		if (v == v_end) {
			cout << "total # of moves: " << v.get_distance() << endl;
			stack<vertice_wrap> s;
			s.push(v);
			map<vertice_wrap,vertice_wrap>::iterator it;
			while((it = m.find(v)) != m.end()){
				if ((*it).second != v_start) {
					v = (*it).second;
					s.push(v);
				} else {
					break;
				}
			}
			cout << "path: ";
			while(!s.empty()) {
				cout << (char)(s.top().first-1+'A') << s.top().second << " ";
				s.pop();
			}
			cout << endl;
			return;
		}

		vertice_wrap v_next[8] =
		{ vertice_wrap(v.first-1, v.second-2, v.get_distance()+1),
		  vertice_wrap(v.first-1, v.second+2, v.get_distance()+1),
		  vertice_wrap(v.first+1, v.second-2, v.get_distance()+1),
		  vertice_wrap(v.first+1, v.second+2, v.get_distance()+1),
		  vertice_wrap(v.first-2, v.second-1, v.get_distance()+1),
		  vertice_wrap(v.first-2, v.second+1, v.get_distance()+1),
		  vertice_wrap(v.first+2, v.second-1, v.get_distance()+1),
		  vertice_wrap(v.first+2, v.second+1, v.get_distance()+1),
		};
		for(int i=0;i<8;i++) {
			vertice_wrap v_n = v_next[i];
			if((!v_n.is_marked())&&(v_n.is_valid())) {
				v_n.mark();
				q.push(v_n);
				m.insert(v_pair(v_n, v));
			}
		}
	}
}


bool is_valid_input(string s) {
	return (s.length()==5) &&\
		   (isalpha(s[0])&&(s[0]<='H'&&s[0]>='A')) &&\
		   (isdigit(s[1])&&(s[1]<='8'&&s[1]>='1')) &&\
		   (isspace(s[2])) &&\
		   (isalpha(s[3])&&(s[3]<='H'&&s[3]>='A')) &&\
		   (isdigit(s[4])&&(s[4]<='8'&&s[4]>='1'));
}


bool is_exit(string s) {
	return (s=="exit");
}


int main(int argc, char *argv[])
{
	while(1) {
		cout << "please enter start and end position in algebraic chess notation separated by a space, e.g. A8 B7" << endl;
		cout << "or enter exit to quit the program." << endl;

		string s;
		getline(cin, s);
		if(is_valid_input(s)) {
			vertice_wrap v_s(s[0]-'A'+1,s[1]-'0',0);
			vertice_wrap v_e(s[3]-'A'+1,s[4]-'0',0);
			bfs(v_s, v_e);
			cout << endl;
		} else if(is_exit(s)) {
			return 0;
		} else {
			cout << "wrong input parameter entered, please try again" << endl << endl;
		}
	}
}

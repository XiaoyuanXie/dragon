/// \file grammer_anaylse.cpp
/*
  ------------------------------------
  Create date : 2015-05-26 12:39
  Modified date: 2015-05-28 09:40
  Author : Sen1993
  Email : gsen1993@gmail.com
  ------------------------------------
*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sstream>

using namespace std;

#define UMM(x,y) unordered_multimap<x,y>::value_type

enum PRI{LT=-1,EQ,GT};

unordered_multimap<string, string> grammer;
unordered_multimap<char, char> firstvt;
unordered_multimap<char, char> lastvt;
unordered_map<string, PRI> table;

bool isTerminator(char c){
	if(c >= 'A' && c <= 'Z') return false;
	return true;
}

bool multi_find(unordered_multimap<char,char> vt, char key, char value){
	auto it = vt.find(key);
	if(it == vt.end()) return false;
	while(it != vt.end()){
		if(it->second == value)
			return true;
		++it;
	}
	return false;
}

void get_firstvt(){
	vector<pair<char,char>> s;
	string nt, te;

	for(auto it : grammer){
		nt = it.first;
		te = it.second;
		for(auto c : te){
			if(isTerminator(c)){
				s.push_back(make_pair(nt[0], c));
				firstvt.insert(UMM(char,char)(nt[0], c));
				break; 
			}
		}
	}
	while(!s.empty()){
		pair<char,char> top = s.back();
		s.pop_back();
		for(auto it : grammer){
			nt = it.first;
			te = it.second;
			if(te[0] == top.first && !multi_find(firstvt, nt[0], top.second)){
				s.push_back(make_pair(nt[0], top.second));
				firstvt.insert(UMM(char,char)(nt[0], top.second));
			}
		}
	}

	char bef = '\0';
	cout << "---firstvt---";
	for(auto it : firstvt){
		if(it.first != bef) cout << endl << it.first << ": ";
		cout << it.second << " ";
		bef = it.first;
	}
	cout << endl;
}

void get_lastvt(){
	vector<pair<char,char>> s;
	string nt, te;

	for(auto it : grammer){
		nt = it.first;
		te = it.second;
		for(int i = te.length()-1; i >= 0; --i){
			if(isTerminator(te[i])){
				s.push_back(make_pair(nt[0], te[i]));
				lastvt.insert(UMM(char,char)(nt[0], te[i]));
				break; 
			}
		}
	}
	while(!s.empty()){
		pair<char,char> top = s.back();
		s.pop_back();
		for(auto it : grammer){
			nt = it.first;
			te = it.second;
			if(te[ te.length()-1 ] == top.first && !multi_find(lastvt, nt[0], top.second)){
				s.push_back(make_pair(nt[0], top.second));
				lastvt.insert(UMM(char,char)(nt[0], top.second));
			}
		}
	}

	char bef = '\0';
	cout << "---lastvt---";
	for(auto it : lastvt){
		if(it.first != bef) cout << endl << it.first << ": ";
		cout << it.second << " ";
		bef = it.first;
	}
	cout << endl;
}

void str_replace(string &str, string s, string t){
	size_t pos = 0;
	size_t s_len = s.length();
	size_t t_len = t.length();
	while( (pos=str.find(s,pos)) != string::npos){
		str.replace(pos, s_len, t);
		pos += t_len;
	}
}

void process_grammer(){
	string nt, te;
	unordered_multimap<string, string> grammer_tmp;

	for(auto it : grammer){
		nt = it.first;
		te = it.second;
		size_t pos = te.find('|');
		if(pos == string::npos) 
			grammer_tmp.insert(UMM(string,string)(nt, te));
		else{
			str_replace(te, "|", " ");
			stringstream ss(te);
			string tmp;
			while(ss >> tmp)
				grammer_tmp.insert(UMM(string,string)(nt, tmp));
		}
	}
	grammer = grammer_tmp;
	for(auto it : grammer)
		cout << it.first << " " << it.second << endl;
}

void make_table(){
	string nt, te;

	for(auto it : grammer){
		nt = it.first;
		te = it.second;
		for(int i = 0; i < te.length()-1; ++i){
			if(isTerminator(te[i])){
				if(isTerminator(te[i+1]))
					table[te.substr(i,2)] = EQ;
				else if(i+2 < te.length() && isTerminator(te[i+2]))
					table[te.substr(i,1)+te.substr(i+2,1)] = EQ;
				else{
					auto it2 = firstvt.find(te[i+1]);
					while(it2 != firstvt.end() && it2->first == te[i+1]){
						table[te.substr(i,1).append(1,it2->second)] = LT;
						++it2;
					}
				}
			}else{
				if(isTerminator(te[i+1])){
					auto it2 = lastvt.find(te[i]);
					while(it2 != lastvt.end() && it2->first == te[i]){
						string tmp("");
						tmp.append(1,it2->second);
						table[tmp+te.substr(i+1,1)] = GT;
						++it2;
					}
				}
			}
		}
	}
	
	cout << "---table---" << endl;
	for(auto it : table)
		cout << it.first[0] << "," << it.first[1] << " " << it.second << endl;
}

PRI get_pri(char a, char b){
	if(a == '#' && b == '#') return EQ;
	if(a == '#') return LT;
	if(b == '#') return GT;
	string tmp("");
	tmp.append(1,a);
	tmp.append(1,b);
	if(table.find(tmp) != table.end()) return table[tmp];
	tmp.clear();
	tmp.append(1,b);
	tmp.append(1,a);
	if(table.find(tmp) == table.end()){
		cout << "error!" << "-" << a << b << endl;
		exit(0);
	}
	switch(table[tmp]){
		case GT:
			return LT;
		case EQ:
			return EQ;
		case LT:
			return GT;
	}
}

char guiyue(string str){
	for(auto it : grammer)
		if(it.second == str)
			return it.first[0];
}

void do_analyse(){
	char S[100];
	memset(S, 0, 100);
	int k = 0;
	S[k] = '#';

	cin.clear();
	int fd = open("txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	char a;
	cout << "---analyse---" << endl;
	do{
		cin >> a;
		int j = k;
		if( !isTerminator(S[k]) ) --j;
		while(get_pri(S[j],a) == GT){
			char q;
			do{
				q = S[j];
				--j;
				if( !isTerminator(S[j]) ) --j;
			}while(get_pri(S[j],q) != LT);
			string tmp("");
			for(int i = j+1; i <= k; ++i)
				tmp.append(1,S[i]);
			k = j+1;
			S[k] = guiyue(tmp);
			cout << "stack: " << S << endl;
			cout << "guiyue: " << tmp << " - " << guiyue(tmp) << endl;
		}
		if(get_pri(S[j],a) != GT){
			++k;
			S[k] = a;
			cout << "stack: " << S << endl;
		}else{
			cout << "error" << endl;
		}
	}while(a != '#');

	close(fd);
}

void analyse(){
	process_grammer();
	get_firstvt();
	get_lastvt();
	make_table();
	do_analyse();
}

int main(){
	string line;
	int fd = open("grammer", O_RDONLY);
	dup2(fd,STDIN_FILENO);
	while(cin >> line){
		int pos = line.find("->");
		if(pos == string::npos){
			cout << "grammer error!" << endl;
			return 0;
		}
		grammer.insert(UMM(string,string)(line.substr(0,pos),line.substr(pos+2)));
	}
	close(fd);
	analyse();
	
	return 0;
}

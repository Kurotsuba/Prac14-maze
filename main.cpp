/*
 * main.cpp
 *
 *  Created on: 2017Äê5ÔÂ22ÈÕ
 *      Author: kanneco98
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool getRoute(const vector<string> & m, vector<vector<string> >& re, int x, int y, int l, int w);
struct Route{
	int idx;
	int length;
	Route(int index){
		idx = index;
		length = 0;
	}
};

int main(){
	ifstream ifs("mg4.txt");
	stringstream ss;
	string temp;

	int l,w;
	getline(ifs, temp, ' ');
	ss << temp;
	ss >> l;
	ss.clear();
	temp = "";
	getline(ifs, temp);
	ss << temp;
	ss >> w;
	ss.clear();


	vector<string> maze;
	for(int i=0; i<l; i++){
		for(int j=0; j<w-1; j++){
			temp = "";
			getline(ifs, temp, ' ');
			maze.push_back(temp);
		}
		temp = "";
		getline(ifs, temp);
		maze.push_back(temp);
	}

	ifs.close();


	vector<vector<string> > results;

	getRoute(maze,results,0,0,l,w);

	vector<Route> rouVec;

	for(int i=0; i<results.size(); i++){
		rouVec.push_back(Route(i));
	}

	for(int i=0; i<results.size(); i++){
		for(int j=0; j<results[i].size(); j++){
			if(results[i][j] == "2"){
				rouVec[i].length++;
			}
		}
	}

	int maxLen = rouVec[0].length;
	int resultIdx = 0;
	for(int i=1; i<rouVec.size(); i++){
		if(rouVec[i].length < maxLen){
			resultIdx = i;
		}
	}

	vector<string> shortRoute = results[resultIdx];


	for(int i=0; i<l; i++){
		for(int j=0; j<w; j++){
			cout << shortRoute[i*w + j];
		}
		cout << endl;
	}



	return 0;
}

bool getRoute(const vector<string> & m, vector<vector<string> >& re, int x, int y, int l, int w){
	int idx = x * w + y;
	vector<string> run = m;

	bool flagLeft, flagRight, flagUp, flagDown;
	if(x == l-1 && y == w-1){
		run[idx] = "2";
		re.push_back(run);
		return true;
	}
	if(x > l-1 || y > w-1 || x < 0 || y < 0){
		return false;
	}
	if(m[idx] != "0"){
		return false;
	}

	run[idx] = "2";

	if(getRoute(run, re, x-1, y, l, w)){
		flagLeft = true;
	}else{
		flagLeft = false;
	}

	if(getRoute(run, re, x+1, y, l, w)){
		flagRight = true;
	}else{
		flagRight = false;
	}

	if(getRoute(run, re, x, y-1, l, w)){
		flagUp = true;
	}else{
		flagUp = false;
	}

	if(getRoute(run, re, x, y+1, l, w)){
		flagDown = true;
	}else{
		flagDown = false;
	}

	if(flagLeft || flagRight || flagUp || flagDown){
		return true;
	}else{
		return false;
	}

}


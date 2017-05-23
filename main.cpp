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

int getRoute(vector<string> & m, int x, int y, int l, int w);

int main(){
	ifstream ifs("mg1.txt");
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

	cout <<getRoute(maze, 0, 0, l, w) << endl;

	for(int i=0; i<l; i++){
		for(int j=0; j<w; j++){
			cout << maze[i*w + j];
		}
		cout << endl;
	}

	return 0;
}

int getRoute(vector<string> & m, int x, int y, int l, int w){
	int idx = x * w + y;
	if(x == l-1 && y == w-1){
		m[idx] = "2";
		return 1;
	}
	if(x > l-1 || y > w-1 || x < 0 || y < 0){
		return -1;
	}
	if(m[idx] != "0"){
		return -1;
	}

	m[idx] = "2";

	int left = getRoute(m, x-1, y, l, w);

	int right = getRoute(m, x+1, y, l, w);

	int up = getRoute(m, x, y-1, l, w);

	int down = getRoute(m, x, y+1, l, w);

	if(left == -1 && right == -1 && up == -1 && down == -1){
		m[idx] = "0";
		return -1;
	}

	if(left <= right && left <= up && left <= down){
		return left + 1;
	}else if(right <= left && right <= up && right <= down){
		return right + 1;
	}else if(up <= left && up <= right && up <= down){
		return up + 1;
	}else if(down <= left && down <= right && down <= up){
		return down + 1;
	}

}


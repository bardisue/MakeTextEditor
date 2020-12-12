#include <vector>
#include <iostream>
using namespace std;

int main() {
	vector<vector<int>> vec1;
	vec1.push_back(*new vector<int>);
	vec1[0].push_back(3);
	vec1.push_back(*new vector<int>);
	vec1[0].push_back(3);
	for (int i = 0; i < vec1.size(); i++) {
		for (int j = 0; j < vec1[0].size(); j++) {
			cout << vec1[i][j] << endl;
		}
	}

	return 0;
}
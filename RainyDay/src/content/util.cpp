#include <algorithm>

using namespace std;

vector<int> getListOfRandomlyShuffledIndexes(int n)
{
	vector<int> a;
	for (int i=0;i<n;i++){
		a.push_back(i);
	}
	random_shuffle(std::begin(a), std::end(a));
	return a;
}

bool contains(vector<int> vec, int v){
	if(std::find(vec.begin(), vec.end(), v) != vec.end()){
		return true;
	}
	return false;
}


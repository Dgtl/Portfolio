// Example program
#include <iostream>
#include <string>
#include <vector>

using namespace std;



template<class T>
void printVector(const vector<T> &v){
	for (vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

void InsertionSort(std::vector<int> & data)
{
	int length = data.size();
	int cntr = 0;

	for (int i = 1; i < length; ++i)
	{
		bool inplace = true;
		int j = 0;
		for (; j < i; ++j)
		{

			if (data[i] < data[j])
			{
				inplace = false;
				break;
			}
		}

		if (!inplace)
		{
			int save = data[i];
			for (int k = i; k > j; --k)
			{
				data[k] = data[k - 1];
			}
			data[j] = save;
		}
	}

}


int binarySearch(const vector<int> list, int item, int f, int l){

	vector<int> v = list;
	//printVector(v);
	//vector<int>::const_iterator i1;
	//vector<int>::const_iterator i2;

	int first = f; //0;
	int last = l;  //list.size() - 1;
	int mid;

	bool found = false;

	//if (first <= last && !found){

	mid = (first + last) / 2;

	if (list[mid] == item)
		found = true;
	else if (list[mid] > item){
		//v.erase(i1 = v.begin() + (mid - 1), i2 = v.end()); 
		last = mid - 1;

	}
	else{
		//v.erase(i1 = v.begin(), i2 = v.end() - (mid + 1)); 
		first = mid + 1;
	}
//}

	if (!found && first > last)
		return -1;
	else if (!found)
	 	return binarySearch(v, item, first, last);
	else 
		return mid;

}



int main()
{
	vector<int> v;
	v.reserve(15);

	v.push_back(48);
	v.push_back(30);
	v.push_back(66);
	v.push_back(50);
	v.push_back(9);
	v.push_back(95);
	v.push_back(80);
	v.push_back(15);
	v.push_back(25);
	v.push_back(18);
	v.push_back(94);
	v.push_back(55);
	v.push_back(3);
	v.push_back(22);
	v.push_back(62);

	printVector(v);
	InsertionSort(v);
	printVector(v);

	cout << binarySearch(v, 50, 0, v.size()) << endl;
	cout << binarySearch(v, 62, 0, v.size()) << endl;
	cout << binarySearch(v, 10, 0, v.size()) << endl; //should not be present
	system("pause");

	return 0;
}

#include<bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(),a.end()
#define cpresent(container,element) (find(all(container),element)!=container.end())
#define rep(i, a, b) 	for(int i = a; i < b; ++i)
#define fr(a,b) for(int i = a; i < b; i++)
using namespace std;
struct Bucket{
	list<string> a;
};
map<int, Bucket *> bmap;
int gd=1,bucket_capacity=4;
int s = 0;
int size_of_map;

int hash_func(string s){
	int a = 0;
	fr(0,s.length()){
		a+= int(s[i]);
	}
	return a%3;
}
int hash_func2(string s){
	int a = 0;
	fr(0,s.length()){
		a+= int(s[i]);
	}
	return a%6;
}
void split(){
	// split bucket s into s and size_of_map+1
	bmap[size_of_map+1] = new Bucket;
	size_of_map++;
	list<string> temp;
	for(auto itr : bmap[s]->a){
		temp.push_back(itr);
	}
	bmap[s]->a.clear();
	for(auto itr : temp){
		int x = hash_func2(itr);
		(bmap[x]->a).push_back(itr);
	}
	s++;
}

void insert(string s){
	int h = hash_func(s);
	if((bmap[h]->a).size() < bucket_capacity){
		(bmap[h]->a).pb(s);
	}
	else{
		(bmap[h]->a).pb(s);
        split();
	}
}

int main(){
	vector<string> v = {"Da001_Sel","Mi009_Emo","Mi009_Soc","Ra001_Pha","Ro015_Fan","Ro015_Gob","Ro015_Phi","Ro015_Pri","Sa001_Voy",
	                   "Sa001_Wha","To015_Fel","Wo015_Wod"};
	
	bmap[0] = new Bucket;
	bmap[1] = new Bucket;
	bmap[2] = new Bucket;
	size_of_map = 2;
	fr(0,v.size()){
		insert(v[i]);
		for(auto itr : bmap){
			cout<<itr.first<<" ";
			for(auto itr1 : itr.second->a){
				cout<<itr1<<" ";
			}
			cout<<"\n";
		}
	}
	
}
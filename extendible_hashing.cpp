#include<bits/stdc++.h>
#define pb push_back
#define all(a) a.begin(),a.end()
#define cpresent(container,element) (find(all(container),element)!=container.end())
#define rep(i, a, b) 	for(int i = a; i < b; ++i)
#define fr(a,b) for(int i = a; i < b; i++)
using namespace std;

string hash_func(string s){
    string hash_ouput;
    fr(0,s.length()){
        int a = int(s[i]);
        string binaryNum = "";
        while (a > 0) {
            binaryNum += (a % 2==0) ? '0' : '1';
            a = a / 2;
        }
        reverse(binaryNum.begin(),binaryNum.end());
        hash_ouput += binaryNum;
    
    }
    return hash_ouput;

}
struct Bucket{
	int ld=0;
	list<string> a;
};
map<string,Bucket *> bmap;
int gd=1,bucket_capacity=4;
void split(string sp_Index,Bucket * sp_Bucket){
	Bucket * newB = new Bucket;
	list<string> temp;
	for(auto i : sp_Bucket->a){
		temp.pb(i);
	}
	sp_Bucket->a.clear();
	if(sp_Bucket->ld == gd){
		if(gd!=0){
			vector<string> abc;
			for(auto itr : bmap){
				if(itr.first!=sp_Index){
					abc.push_back(itr.first);
				}
			}
			fr(0,abc.size()){
				Bucket* b = bmap[abc[i]];
				bmap.erase(abc[i]);
				bmap["0"+abc[i]] = b;
				bmap["1"+abc[i]] = b;
			}
		}
		bmap["1"+sp_Index] = newB;
		bmap["0"+sp_Index] = sp_Bucket;
		bmap.erase(sp_Index);
		gd++;
		sp_Bucket->ld++;
		newB->ld = sp_Bucket->ld;
	}
	else{
		bmap[sp_Index]  = newB;
		bmap[sp_Index]->ld = sp_Bucket->ld;
		bmap[sp_Index]->ld++;
		sp_Bucket->ld++;
	}
	for(auto itr : temp){
		string h = hash_func(itr);
		string key;
		int count = gd;
		for(int i=h.length()-1;i>=0;i--){
			key += h[i];
			count--;
			if(count == 0){
				break;
			}
		}
		reverse(key.begin(),key.end());
		(bmap[key]->a).pb(itr);
	}
}

void insert(string s){
	string h = hash_func(s);
	string key;
	int count = gd;
	for(int i=h.length()-1;i>=0;i--){
		key += h[i];
		count--;
		if(count == 0){
			break;
		}
	}
	reverse(key.begin(),key.end());

    
	if((bmap[key]->a).size() < bucket_capacity){
		(bmap[key]->a).pb(s);
	}
		
	else{
		split(key,bmap[key]);
		insert(s);
	}
}


int main(){
	vector<string> v = {"Da001_Sel","Mi009_Emo","Mi009_Soc","Ra001_Pha","Ro015_Fan","Ro015_Gob","Ro015_Phi","Ro015_Pri","Sa001_Voy","To015_Fel",
	                     "Wo015_Wod"};
	                    
	
	bmap["0"] = new Bucket;
	bmap["1"] = new Bucket;
	bmap["0"]->ld = 1;
	bmap["1"]->ld = 1;
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
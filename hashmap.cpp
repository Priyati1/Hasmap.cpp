#include<iostream>
using namespace std;
class node{
public:
	int val;
	string key;
	node *next;
	//constructor
	node(string k,int v){
		val=v;
		key=k;
		next=NULL;
	}
};
class hasmap{
	int ts;
	int cs;
	node **arr;
	int hashfunction(string key){
		int ans=0;
		int mul=1;
		for(int i=0;i<key.length();i++){
			ans+=(key[i]%ts*mul%ts)%ts;
			mul=(mul*29)%ts;
		}
		ans= ans%ts;
		return ans;
	}

	void rehashing(){
		node**oldarr=arr;
		int oldts;
		arr=new node*[2*ts];
		ts=2*ts;
		cs=0;
		for(int i=0;i<ts;i++){
			arr[i]=NULL;
		}
		for(int i=0;i<oldts;i++){
			node*head=oldarr[i];
			while(head){
				insert(head->key,head->val);
				head=head->next;
			}
		}
		delete[]oldarr;
	}
public:
	hasmap(int size=7){
		cs=0;
		ts=size;
		arr=new node*[ts];
		for(int i=0;i<ts;i++){
			arr[i]=NULL;
		}
	}
	void insert(string key,int val){
		int index=hashfunction(key);
		node*n=new node(key,val);
		n->next=arr[index];
		arr[index]=n;
		cs++;
		if((cs/(ts*1.0))>0.6){
			rehashing();
		}
	}
	void print(){
		for(int i=0;i<ts;i++){
			cout<<i<<"->";
			node*head=arr[i];
			while(head){
				cout<<head->key<<" ";
				head=head->next;
			}
			cout<<endl;
		}
	}
	node* searching (string key){
		int index=hashfunction(key);
		node*head=arr[index];
		while(head){
			if(head->key==key){
				return head;
			}
			head=head->next;
		}
		return NULL;
	}
	int &operator[](string key){
		node* ans=searching(key);
		if(ans==NULL){
			int g;
			insert(key,g);
			ans=searching(key);
			return ans->val;
		}
		else{
			return ans->val;
		}
	}
};
int main(){
	hasmap h;
	h.insert("mango",100);
	h.insert("apple",120);
	h.insert("banana",180);
	h.insert("kiwi",150);
	h.print();
	cout<<endl;
	h["papaya"]=200;
	h.print();
	cout<<endl;
	cout<<"price of kiwi"<<h["kiwi"]<<endl;
	cout<<endl;
	return 0;
}
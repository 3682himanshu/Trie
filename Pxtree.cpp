#include "Pxtree.h"
#include <bits/stdc++.h>
using namespace std;
Pxtree::Pxtree() {
	c_='\0';
	count_=0;
	leftmostChild_=NULL;
	nextSibling_=NULL;
}


void Pxtree::copy(Pxtree *original,Pxtree * other)
{
	if(other->leftmostChild_)
	{
		original->leftmostChild_=new Pxtree;
		original->leftmostChild_->c_=other->leftmostChild_->c_;
		original->leftmostChild_->count_=other->leftmostChild_->count_;	
		copy(original->leftmostChild_,other->leftmostChild_);
	}
	if(other->nextSibling_)
	{
		original->nextSibling_=new Pxtree;
		original->nextSibling_->c_=other->nextSibling_->c_;
		original->nextSibling_->count_=other->nextSibling_->count_;	
		copy(original->nextSibling_,other->nextSibling_);
	}
}
Pxtree::Pxtree( Pxtree& other)  {
	copy(this,&other);
}

Pxtree& Pxtree::operator=(Pxtree& other) {
	copy(this,&other);
	
		return *this;
}
int Pxtree::tcount(Pxtree * root, string s)
	{
		if(!root) return 0;
		if(s.length()==1 and s[0]==root->c_)return root->count_; 
		if(root->c_==s[0])
			return tcount(root->leftmostChild_, s.substr(1));
		
		if(root->nextSibling_)
		{
			Pxtree * tmp=root;
			while(tmp->nextSibling_)
			{
				tmp=tmp->nextSibling_;
				if(tmp->c_==s[0])
				{
					return tcount(tmp,s);
				}
			}
		}
		return 0;
	}
int Pxtree::count(string s) {
		Pxtree *root=this;
		
		return tcount(root->leftmostChild_,s);

}

void Pxtree::add(string s) {
	Pxtree * parent=this;
		if(!parent->leftmostChild_)
		{
			parent->leftmostChild_=new Pxtree();
			parent->leftmostChild_->c_=s[0];
			if(s.length()==1)
			{
				++parent->leftmostChild_->count_;
			}
			else
				parent->leftmostChild_->add(s.substr(1));
		}
		else if(parent->leftmostChild_->c_==s[0])
		{
			if(s.length()==1)
			{
				++parent->leftmostChild_->count_;
			}
			else
				parent->leftmostChild_->add(s.substr(1));
		}
		else
		{
			Pxtree * temp=parent->leftmostChild_;
			while(temp->nextSibling_)
			{
				temp=temp->nextSibling_;
				if(temp->c_==s[0])
				{
					if(s.length()==1)
					{
						++temp->count_;
					}
					else
						temp->add(s.substr(1));
					return;
				}
			}
			temp->nextSibling_=new Pxtree();
			temp->nextSibling_->c_=s[0];
			if(s.length()==1)
			{
				temp->nextSibling_->count_+=1;
			}
			else
				temp->nextSibling_->add(s.substr(1));
		}
}
void Pxtree::tremove(Pxtree * root, string s)
	{
		if(!root)return;
		if(s.length()==1 and s[0]==root->c_)--root->count_; 
		if(root->c_==s[0])
			return tremove(root->leftmostChild_, s.substr(1));
		
		if(root->nextSibling_)
		{
			Pxtree * tmp=root;
			while(tmp->nextSibling_)
			{
				tmp=tmp->nextSibling_;
				if(tmp->c_==s[0])
				{
					return tremove(tmp,s);
				}
			}
		}
		return ;
	}
void Pxtree::remove(string s) {
	Pxtree *root=this;
		
	tremove(root->leftmostChild_,s);
}
void Pxtree::dfs(Pxtree *node ,string &s,int sp)
{
	if(!node)return;
	
	for(int i=0;i<sp;i++)
		s+="  ";
	s+=(node->c_);
	s+=" ";
	s+=to_string(node->count_);
	if(node->leftmostChild_)
		s+="\n";
	dfs(node->leftmostChild_,s,sp+1);
	
	if(node->nextSibling_)
	{
		if(node->nextSibling_)
			s+="\n";
		dfs(node->nextSibling_,s,sp);
	}
	
}
string Pxtree::print() {
	Pxtree *root =this;
	string s="";
	if(root->leftmostChild_)
		dfs(root->leftmostChild_,s,0);
	return s; // dummy, change to something else!
}
void Pxtree::mxString(Pxtree *root,string t ,string &s,int count)
	{
		if(!root)return;
		t+=root->c_;
		if(root->count_>count)
		{
			s=t;count=root->count_;
			//cout<<count<<' '<<root->c_<<endl;
		}
		if(root->leftmostChild_)
		{
			mxString(root->leftmostChild_,t,s,count);
			t=t.substr(0,t.length()-1);
		}
		if(root->nextSibling_)
		{
				mxString(root->nextSibling_,t,s,count);
		}
	}
string Pxtree::tautoComplete(Pxtree * root, string res,string s)
{
	if(!root)
		return res;
	if(s.length()==1 and s[0]==root->c_)
	{
		string t1="",t2="";int c=root->count_;
		mxString(root->leftmostChild_,t1,t2,c);
		return res+t2;
	}
	else if(root->c_==s[0])
	{
		return tautoComplete(root->leftmostChild_,res,s.substr(1));
	}
	if(root->nextSibling_)
	{
		Pxtree * tmp=root;
		while(tmp->nextSibling_)
		{
			tmp=tmp->nextSibling_;
			if(tmp->c_==s[0])
			{
				return tautoComplete(tmp,res,s);
			}
		}
		return res;
	}
	return res;
}
string Pxtree::autoComplete(string s) {

	return tautoComplete(this->leftmostChild_,s,s);
}
void Pxtree::tcompact(Pxtree * parent,Pxtree * root,bool &flag)
{
	if(!root)return;
	if(!root->leftmostChild_ and root->count_<1)
	{
		flag =true;
	}
	tcompact(root,root->leftmostChild_,flag);
	if(root->count_>=1)flag=false;
	if(flag)
	{
		Pxtree * t=NULL;
		if(root->nextSibling_)
		{
			t=root->nextSibling_;
			flag=false;
		}
		delete(root);
		parent->leftmostChild_=t;
		tcompact(parent,parent->leftmostChild_,flag);
	}
	if(root->nextSibling_)
		tcompact(root,root->nextSibling_,flag);
}
void Pxtree::compact() {
	bool flag=false;
	tcompact(this,this->leftmostChild_,flag);
}
void f1()
{
    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif  
}
int main()
{
	f1();
	cout<<"Simple Demonstration of Pxtree"<<endl;
	Pxtree ob;
	ob.add("hello");
	cout<<ob.print()<<endl;
	ob.add("hell");
	cout<<ob.print()<<endl;
	ob.add("help");
	cout<<ob.print()<<endl;
	ob.add("geek");
	cout<<ob.print()<<endl;

	cout<<ob.autoComplete("he")<<endl;
	ob.remove("hello");
	cout<<ob.print()<<endl;

	ob.compact();
	cout<<ob.print()<<endl;

	ob.add("help");
	cout<<ob.count("help")<<endl;
}
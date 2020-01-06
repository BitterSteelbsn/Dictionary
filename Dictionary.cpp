#include<iostream>
#include<cstring>
#include<iomanip>
#define MAX 200
using namespace std;

void DisplayChArray(char x[])
{
	int i = 0;
	while(x[i] != '\0')
	{
		cout<<x[i];
		i++;
	}
}

class sll_node{
	//string meaning;
	char meaning[MAX];
	int n;
	sll_node* next;
	public:
	sll_node(char x[])
	{
		strcpy(meaning,x);
		n = -1;
		next = NULL;
	}
	friend class sll;
};

class sll
{
	sll_node* head;
	public:
	sll()
	{
		head = NULL;
	}
	void add_meaning();
	void display_meanings();
	void update_meanings();
	void delete_meaning();
	void delete_all();
};

void sll::add_meaning()
{
	char x[MAX];
	cout<<"Enter meaning:";
	//cin>>x;
	cin.getline(x,MAX-1);
	sll_node* p = new sll_node(x);

	if(head == NULL)
	{
		head = p;
		head->n = 1;
	}
	else
	{
		sll_node* q = head;
		while(q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
		p->n = q->n + 1;
	}
}

void sll::display_meanings()
{
	if(head == NULL)
	{
		cout<<"NO MEANINGS EXIST."<<endl;
	}
	else
	{
		sll_node* p = head;
		while(p != NULL)
		{
			cout<<setw(5)<<p->n<<".)";
			DisplayChArray(p->meaning);
			cout<<endl;
			p = p->next;
		}
	}
}

void sll::update_meanings()
{
	int un;
	cout<<"Enter which meaning to update(serial number):";
	cin>>un;

	sll_node* p = head;
	if(head == NULL)
	{
		cout<<"NO MEANINGS EXIST."<<endl;
	}
	else
	{
		while(p->n != un)
		{
			p = p->next;
		}
		char x[MAX];
		cout<<"Enter updated meaning:";
		cin.ignore();
		cin.getline(x,MAX-1);
		strcpy(p->meaning,x);
	}
}

void sll::delete_meaning()
{
	int un;
	cout<<"Enter which meaning to delete(serial number):";
	cin>>un;
	sll_node* p = head;
	if(head == NULL)
	{
		cout<<"NO MEANINGS EXIST."<<endl;
	}
	else
	{
		if(un == 1)
		{
			head = head->next;
			delete p;
			p = head;
			while(p != NULL)
			{
				p->n--;
				p = p->next;
			}
		}
		else
		{
			while(p->n != (un-1))
			{
				p = p->next;
			}
			sll_node* q = p->next;
			p->next = q->next;
			p = p->next;
			while(p != NULL)
			{
				p->n--;
				p = p->next;
			}
			delete q;
		}
	}
}

void sll::delete_all()
{
	while(head != NULL)
	{
		sll_node* p = head;
		head = head->next;
		delete p;
	}
}

class DictionaryNode
{
	string key;
	sll meanings;
	DictionaryNode* left;
	DictionaryNode* right;
	public:
	DictionaryNode(string x)
	{
		key = x;
		left = NULL;
		right = NULL;
	}
	friend class Dictionary;
};

class Dictionary
{
	DictionaryNode* root;
	public:
	Dictionary()
	{
		root = NULL;
	}
	DictionaryNode* insert(DictionaryNode* ,string );
	void add_word();
	void inorder(DictionaryNode* );
	void update();
	void UpdateDictionaryNode(DictionaryNode* ,string );
	void search();
	void SearchWord(DictionaryNode* ,string ,int&);
	void display();
	void delete_word();
	DictionaryNode* word_deleter(DictionaryNode* ,string );
	DictionaryNode* find_min(DictionaryNode* );
};

DictionaryNode* Dictionary::insert(DictionaryNode* p,string x)
{
	if(p == NULL)
	{
		p = new DictionaryNode(x);
		string m;
		while(1)
		{
			cout<<"Press _STOP_ to stop entering meanings:";
			cin>>m;
			if(m == "_STOP_")
			{
				break;
			}
			else
			{
				cin.ignore();
				(p->meanings).add_meaning();
			}
		}

		return p;
	}
	else if(x < p->key)
	{
		p->left = insert(p->left,x);
		return p;
	}
	else if(x > p->key)
	{
		p->right = insert(p->right,x);
		return p;
	}
	else
	{
		return p;
	}
}

void Dictionary::add_word()
{
	string x;
	cout<<"Enter key word:";
	cin>>x;
	root = insert(root,x);
}

void Dictionary::inorder(DictionaryNode* p)
{
	if(p != NULL)
	{
		inorder(p->left);
		cout<<"{*} "<<p->key<<":"<<endl;
		(p->meanings).display_meanings();
		inorder(p->right);
	}
}

void Dictionary::display()
{
	inorder(root);
}

void Dictionary::update()
{
	string uval;
	cout<<"Enter key to update:";
	cin>>uval;
	UpdateDictionaryNode(root,uval);
}

void Dictionary::UpdateDictionaryNode(DictionaryNode* p,string x)
{
	if(p == NULL)
	{
		cout<<"Key does not exist"<<endl;
	}
	else if(p->key == x)
	{
		string strch,new_key;
		cout<<"--Update Keyword."<<endl;
		cout<<"--Meaning of a Keyword."<<endl;
		cout<<"Enter choice:"<<endl;
		cin>>strch;
		if(strch == "Keyword")
		{
			cout<<"Enter new Keyword:";
			cin>>new_key;
			p->key = new_key;
		}
		else if(strch == "Meaning")
		{
			p->meanings.update_meanings();
		}
	}
	else if(x > p->key)
	{
		UpdateDictionaryNode(p->right,x);
	}
	else if(x < p->key)
	{
		UpdateDictionaryNode(p->left,x);
	}
}

void Dictionary::search()
{
	if(root != NULL)
	{
		string x;
		int count = 0;
		cout<<"Enter Key to search:";
		cin>>x;
		cout<<"-----------------------------"<<endl;
		count++;
		SearchWord(root,x,count);
		cout<<"Total comparisons :"<<count<<endl;
		cout<<"-----------------------------"<<endl;
	}
	else
	{
		cout<<"Dictionary is empty"<<endl;
	}
}

void Dictionary::SearchWord(DictionaryNode* p,string x,int& c)
{
	if(p == NULL)
	{
		cout<<"Key does not Exist"<<endl;
	}
	else if(p->key == x)
	{
		cout<<"{*} "<<p->key<<":"<<endl;
		(p->meanings).display_meanings();
	}
	else if(x > p->key)
	{
		c++;
		SearchWord(p->right,x,c);
	}
	else if(x < p->key)
	{
		c++;
		SearchWord(p->left,x,c);
	}
}

void Dictionary::delete_word()
{
	string x;
	cout<<"Enter the key to delete:";
	cin>>x;
	root = word_deleter(root,x);
}

DictionaryNode* Dictionary::word_deleter(DictionaryNode* p,string x)
{
	if(p == NULL)
	{
		cout<<"Key does'nt exist in the dictionary."<<endl;
		return NULL;
	}
	else if(x < p->key)
	{
		p->left = word_deleter(p->left,x);
		return p;
	}
	else if(x > p->key)
	{
		p->right = word_deleter(p->right,x);
		return p;
	}
	if(p->left == NULL && p->right == NULL)
	{
		p->meanings.delete_all();
		delete p;
		return NULL;
	}
	if(p->left == NULL)
	{
		DictionaryNode* t =p->right;
		p->meanings.delete_all();
		delete p;
		return t;
	}
	if(p->right == NULL)
	{
		DictionaryNode* t =p->left;
		p->meanings.delete_all();
		delete p;
		return t;
	}
	DictionaryNode* t = find_min(p->right);
	p->key = t->key;
	p->right = word_deleter(p->right,p->key);
	return p;
}

DictionaryNode* Dictionary::find_min(DictionaryNode* p)
{
	while(p->left != NULL)
	{
		p = p->left;
	}
	return p;
}

int main()
{
	Dictionary a;
	int ch;

	while(1)
	{
		cout<<"----DICTIONARY----"<<endl;
		cout<<"1.)Add word."<<endl;
		cout<<"2.)Display all words."<<endl;
		cout<<"3.)Search word."<<endl;
		cout<<"4.)Update."<<endl;
		cout<<"5.)Delete word."<<endl;
		cout<<"6.)Exit"<<endl;
		cout<<"Enter your choice:";
		cin>>ch;


		switch(ch)
		{
		case 1:
			a.add_word();
			break;
			case 2:
				a.display();
				break;
				case 3:
					a.search();
					break;
					case 4:
						a.update();
						break;
						case 5:
							a.delete_word();
							break;
							case 6:
								return 0;
								break;
		}
	}
	return 0;
}


#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <fstream>
using namespace std;
//for queue
class node 
{

public:
	int key;
	int id;
	char oper;
	node()
	{
		key=0;
		id=0;
		oper=' ';
		
	}
	node(int k, int i, char o)
	{
		key=k;
		id=i;
		oper=o;
	}
	node(const node & obj)
	{
		key=obj.key;
		id=obj.id;
        oper=obj.oper;
	}
	 node operator=(const node & obj)
	{
		key=obj.key;
		id=obj.id;
        oper=obj.oper;
		return obj;
	}
	friend ostream &operator<<( ostream &output, const node & temp )
	{
		output<<"Priority: "<<temp.key<<"  User Id: "<<temp.id<<"  Access Type: "<<temp.oper<<" | ";

		return output;
	}

	~node()
	{ }

	
};
//increase array size
void extend(node * & arr, int & s)
{
	int c=s+1;

	node * temp;
	temp= new node[c];
	for (int i=0; i<s; i++)
	{
		temp[i].key=arr[i].key;
		temp[i].id=arr[i].id;
		temp[i].oper=arr[i].oper;
	}

	delete [] arr ;
	s+=1;
	arr= temp;
}
//decrease array size by coping from start
void decEnd(node * & arr, int & s)
{
	int c=s-1;
	int j=0;
	node * temp;
	temp= new node[c];
	for (int i=0; i<c; i++)
	{
		temp[j].key=arr[i].key;
		temp[j].id=arr[i].id;
		temp[j].oper=arr[i].oper;
		j++;
	}
	
	delete [] arr ;
	s-=1;
	arr= temp;

}
//decrease array size by coping from 1st index till last
void dec(node * & arr, int & s)
{
	int c=s-1;
	int j=0;
	node * temp;
	temp= new node[c];
	for (int i=1; i<s; i++)
	{
		temp[j].key=arr[i].key;
		temp[j].id=arr[i].id;
		temp[j].oper=arr[i].oper;
		j++;
	}
	
	delete [] arr ;
	s-=1;
	arr= temp;

}
//Using Heap
class Queue
{
private:
	vector <node> v1;
	node min;
	node * A;
	int size;
	int del;
public:
	Queue()
	{
		A=nullptr;
		size=0;
		del=0;
		min.key=-1;
	}
	void def()
	{
        A=nullptr;
		size=0;
		del=0;
		min.key=-1;
	}
	Queue(int c, node arr[])
	{
		A=new node[c];
		insert(arr,c);
		size=c;
		del=0;
	}
	char getop()
	{
		return findMax().oper;
		//return operation of max
	}
	Queue(const Queue & obj)
	{
		size=obj.size;
		del=obj.del;
		A = new node[obj.size];

		for(int i=0; i<size; i++)
			{
				A[i]=obj.A[i];
		}
		for(int i=0 ; i<size ; i++)
		{
			v1.push_back(A[i]);
		}
	}
	Queue operator=(const Queue & obj)
	{
		size=obj.size;
		del=obj.del;
		A = new node[obj.size];

		for(int i=0; i<size; i++)
			{
				A[i]=obj.A[i];
		}
		buildqueue();
		return obj;
	}
	int getuserid()
	{
		return A->id;
	}
	void insert(node ar[], int s) //insert in queue, new node
	{
		for(int i=0; i<s; i++)
			A[i]=ar[i];
	}
	void swap(node & a, node & b) //swap elements of two nodes
	{
		node temp;
		temp.key=a.key;
		temp.id=a.id;
		temp.oper=a.oper;

		a.key=b.key;
		a.id=b.id;
		a.oper=b.oper;

		b.key=temp.key;
		b.id=temp.id;
		b.oper=temp.oper;
	}
	void heapify(node *& arr,int i, int n) //max heapify
	{
		
		int largest=i;
		if(((2*i + 1))<n && arr[largest].key<arr[(2*i + 1)].key)
		{
			largest=(2*i + 1);
		}
		if((2*i+2)<n && arr[largest].key<arr[2*i+2].key)
		{
			largest=2*i+2;
		}
		if( largest!= i)
		{
			swap(arr[i],arr[largest]);
			heapify(arr,largest,n);
		}
	}
	void sort( node * & arr, int s , int j) //buildheap
	{
		for (int i=((s-1)/2); i>=0; i--)
		{
			heapify(arr,i,s);
		}
	}
	void  heapsort(node * & arr) 
	{
		for(int i=size-1;i>0;i--)
		{
			swap(arr[0],arr[i]);
			heapify(arr,0,i);
		}

	}
	void buildqueue() //create queue using an array
	{
		
		sort(A,size,0);

		node * t= new node [size];
		for(int i=0; i<size; i++)
		{
			v1.push_back(A[i]);
			t[i]=A[i];
		}
		heapsort(t);
		min=t[0];
		//node temp= v1.front(); //0th index

	}
	void extractmax() //return 0th node and delete it
	{
		
		v1.erase(v1.begin());
		dec(A,size);
		sort(A,size,0);
	
		vector<node> v2;
		for(int i=0; i<size; i++)
			v2.push_back(this->A[i]);
		v2.swap(v1);
				
	}
	node findMax()
	{
		return A[0];
	}
	node findMin()
	{
		return min; //to return minimum element in O(1)
	}
	int retsize()
	{
		return v1.size();
	}
	bool isempty()
	{
		return (size==0);
	}
	void print()
	{
	
		for(int i=0; i<size; i++)
			cout<<v1[i];
		
	}
	void insertinV(node element) //insert in queue new node
	{
		if(this->size!=0)
			if(element.key<min.key)
				min=element;
	
		v1.insert(v1.end(), element);
		int s=size;
		extend(A,size);
		A[s]=element;
		sort(A,size,0);
		//heapify(A,0,size);
		int i=s;
		while(i>0 && A[i].key>A[(i-1)/2].key)
		{
			swap( A[i],A[i/2]);
				i=(i-1)/2;
		}
		vector<node> v3;
		for(int i=0; i<size; i++)
			v3.push_back(A[i]);
		v3.swap(v1);
		
	}
};
//increase int array
void extend(int * & arr, int & s)
{
	int c= s+1;

	int * temp;
	temp= new int [c];
	for (int i=0; i<s; i++)
	{
		temp[i]=arr[i];
		//temp[i].value=arr[i].value;
	}

	delete [] arr ;
	s=s+1;
	arr= temp;
}

class hashtable
{
private:
	//every node in table containing pointer to queue and fileID
	class NodeL
	{
	public:
		int fileId;
		Queue * ptr;
		node * trackuser;
		int St;
		//NodeL * next;
		NodeL(int i=-1)
		{
			St=0;
			fileId=i;
			ptr=nullptr;
			trackuser=nullptr;
		}
		//check if user present
		bool searchuid(int id, int s)
		{
			
			while(s < St)
			{
				if(trackuser[s].id==id)
				{
					//cout<<s<<endl;
					return true;
				}
				s++;
			}
			return false;
		}
		NodeL(int i, node temp)
		{
			fileId=i;
			ptr=new Queue;
			//St=0;
			//ptr->def();
			ptr->insertinV(temp);
			trackuser=nullptr;
		}
		Queue * getter()
		{
			return ptr;
		}
		void setter(int i)
		{
			fileId=i;
		}
		void printNodeL()
		{
			cout<<"File Id: "<<fileId<<"  "<<endl;
			if(ptr!=nullptr)
			{
			   ptr->print();
			}
			cout<<"Users granted Access: ";
			for(int f=0; f<St; f++)
				cout<<trackuser[f]<<" , ";
			cout<<endl;
		}
		
		void delinAccess(int id) //delete if user present in array of accessing users
		{
			int s=0;
			while(s < St)
			{
				if(trackuser[s].id==id)
				{
					while(s+1<St)
					{
					     trackuser[s]=trackuser[s+1];
						 s++;
					}
					decEnd(trackuser,St);
					break;
				}
				s++;
			}
			
		}
	};

	list <NodeL>* arr;
	int total;
	int *check;
	
	//int St;
public:

	hashtable(int i=100)
	{
		arr=new list<NodeL> [i];
		total=100;
		check=new int [100];
		for(int j=0; j<100; j++)
			check[j]=0;
		//trackuser=nullptr;
		//St=0;
	}
	int calcHash(int i)
	{
		int hashindex = i % total;
		return hashindex;
	}
	bool insertfile(int fid)
	{
		int index= calcHash(fid); //calculate index
		if(check[index]==0) //if empty insert in table
		{
			
		    NodeL tempNodeL(fid);
			check[index]=1;
		    arr[index].push_back(tempNodeL);
		}
		else 
		{
			
			list <NodeL> :: iterator it;
			bool op=false;
			for(it = arr[index].begin(); it != arr[index].end() || arr[index].end()==arr[index].begin(); ++it)
			{
				
				if(it->fileId==fid)
				{
					op=true;
					break;
				}
				
			}
			if(op==false) //if not empty and not found, insert at end of list on that index
			{

				NodeL tempNodeL(fid);
				check[index]=1;
				arr[index].push_back(tempNodeL);
			}
		}
		return true;
	}
	
	bool insertinTable(int fid, int k, int i, char o)
	{
		int index= calcHash(fid);
		node tempNode(k,i,o);
		
		if(check[index]==0)//check if index empty, if yes, insert 
		{
			
		    NodeL tempNodeL(fid,tempNode);
			check[index]=1;
		    arr[index].push_back(tempNodeL);
		}
		else 
		{
			
			list <NodeL> :: iterator it;
			bool op=false;
			for(it = arr[index].begin(); it != arr[index].end() || arr[index].end()==arr[index].begin(); ++it)
			{
				
				if(it->fileId==fid)// if already there, insert in queue
				{
					
					Queue * temp=it->getter();
					temp->insertinV(tempNode);
					op=true;
					break;
				}
				
			}
			if(op==false) //if not found, insert at end of list on that index
			{

				NodeL tempNodeL(fid,tempNode);
				check[index]=1;
				arr[index].push_back(tempNodeL);
			}
		}
		return true;
	}
	bool insertinQueue(int fid, int k, int i, char o)
	{
		int index= calcHash(fid);
		node tempNode(k,i,o);
		
		if(check[index]==0) //if not found, error
		{
			cout<<"File not found"<<endl;
			return false;
		}
		else 
		{
			
			list <NodeL> :: iterator it;
			for(it = arr[index].begin(); it != arr[index].end() || arr[index].end()==arr[index].begin(); ++it)
			{
				
				if(it->fileId==fid) //if found
				{
					
					Queue * temp=it->getter();
					if(temp==nullptr) //if queue empty
					{
						temp->insertinV(tempNode); //insert in queue
						
						if(o=='W') //only insert the user with Write operation
						{
							
						     if(it->trackuser==nullptr) //give access if  no one accessing
							 {
								 it->trackuser= new node [1];
								 it->trackuser[0]=temp->findMax();
								 it->St=1;
								 temp->extractmax();
							 }
							 /*else
							 {
								 temp->insertinV(tempNode);
							 }*/

						}
						else if(o=='R')
						{
							if(it->trackuser==nullptr) //if no one accessing give access
							 {
								 it->trackuser= new node [1];
								 it->trackuser[0]=temp->findMax();
								 temp->extractmax();
								 it->St=1;
							 }
							
							else if(it->trackuser[it->St-1].oper=='R') //if already users reading, give access
							{
								extend(it->trackuser,it->St);
							    it->trackuser[it->St-1]=temp->findMax();
								temp->extractmax();
							}

						}
					

					}
					else //if queue not empty
					{
						
						if(it->trackuser==nullptr) // if no one accessing
						{
							temp->insertinV(tempNode);
							it->St=0;
							int ind=0;
							if(temp->findMax().oper=='W') //if write at max in queue, only give access to him
							{
								it->trackuser= new node [1];
								 it->trackuser[0]=temp->findMax();
								 temp->extractmax();
								 it->St=1;
							}
							else //if read at max, give access to all consecutive read users in queue.
							{
								while(temp->findMax().oper=='R')
								{
									extend(it->trackuser,it->St);
									it->trackuser[ind]=temp->findMax();
									temp->extractmax();
									ind++;
								}
							}
						}
						else //if already accessing
						{
							temp->insertinV(tempNode); //insert in queue
							if(it->trackuser[it->St-1].oper=='R' && temp->findMax().oper=='R') //if read at max, give access anyway
							{
								
								while(temp->findMax().oper=='R')
								{
									extend(it->trackuser,it->St);
									it->trackuser[it->St-1]=temp->findMax();
									temp->extractmax();
									//ind++;
							    }
							}
							
						}
						
					}
					
					return true;
				}
				
			}
		}
		cout<<"File not found"<<endl;
		return false;

	}
	void release(int fid, int uid)
	{
		int index= calcHash(fid);
		if(check[index]==0)
		{
			cout<<"File not found"<<endl;
		}
		else 
		{

			list <NodeL> :: iterator it;
			for(it = arr[index].begin(); it != arr[index].end() ; ++it)
			{

				if(it->fileId==fid) //found, then see if user accessing
				{
					cout<<"In"<<endl;
					Queue * temp=it->getter();
					int found=0;
					bool f=it->searchuid(uid, found);
					if(f==true) //if accessing, delete that user
					{
						cout<<"User found"<<endl;
					    it->delinAccess(uid);
						if(it->St<=0){
							it->trackuser=nullptr; 
							it->St=0;
						}
						if(it->trackuser!=nullptr) // if someone accessing, break. else give access to max
							break;
						char op=temp->getop();
						if(op=='W') // give access to only write
						{
							
							it->trackuser= new node[1];
							it->trackuser[0]=temp->findMax();
							it->St=1;

							temp->extractmax();
							break;
							//cout<<"User was granted write access and the file is released"<<endl;
						}
						else
						{
							int i=0;
							it->St=0;
							it->trackuser= new node [i];
							while(op=='R') //give access to all consecutive read users
							{
								//St=i;
								extend(it->trackuser,it->St);
								it->trackuser[i]=temp->findMax();
								temp->extractmax();
								op=temp->getop();
								i++;
							}
							//cout<<i<<" users were granted Read access and the file is released"<<endl;
							break;

						}

					}



				}

			}
		}
	}
	/*bool deleteitem(int var)
	{
		int index= calcHash(var);
		return arr[index].searchDel(var);
	}*/
	/*v searching(k ke)
	{
		int index= calcHash(ke);
		v temp=arr[index].search(ke);
		return temp;
		
	}*/
	void display()
	{
		list <NodeL> :: iterator it;
		int i=0;
		
		while(i<total)
		{
			bool printed=false;
			for(it = arr[i].begin(); it != arr[i].end(); ++it)
			{
				if(check[i]!=0)
				{
					
					cout<<"File ID: " <<it->fileId<<endl;
					it->ptr->print();
					cout<<endl;
					cout<<"Users granted Access: ";
					if(it->trackuser==nullptr)
						cout<<" None"<<endl;
					else
					{
					for(int f=0; f<it->St; f++)
						cout<<it->trackuser[f].id<<" , ";
					cout<<endl;
					}
			       cout<<endl;
					
				    printed=true;
				}
			}
			
			i++;
		}
	

	}
	bool deletion(int fid)
	{
		int index= calcHash(fid);
		list <NodeL> :: iterator it;
		for(it = arr[index].begin(); it != arr[index].end() || arr[index].end()==arr[index].begin(); ++it)
		{

			if(it->fileId==fid)
			{

				Queue * temp=it->getter();
				if(temp->isempty() && it->St==0) //if no one accessing and queue empty only then delete
				{
					arr[index].erase(it);
					return true;
				}
				
			}
			
		}
		return false;
	}
	
	~hashtable()
	{
		//int index= calcHash(fid);
		list <NodeL> :: iterator it;
		for(int i=0; i<total; i++)
		{
			if(check[i]!=0)
			{
				int index=i;
				for(it = arr[index].begin(); it != arr[index].end(); ++it)
				{
					deletion(it->fileId);
				}
			}
		}
	}

};

int main()
{
	cout<<"----------Menu----------"<<endl;
	cout<<"1- To load the data"<<endl;
	cout<<"2- To insert a file"<<endl;
	cout<<"3- To delete a file"<<endl;
	cout<<"4- To request access"<<endl;
	cout<<"5- To release a file"<<endl;
	cout<<"6- To print the hash table"<<endl;
	cout<<"7- To exit"<<endl;
	int menu;
	cin>>menu;

	//Testing:
	hashtable object(100);
	while(menu!=7)
	{
		cout<<endl;
		if(menu==1)
		{
			ifstream infile;
			infile.open("file1.txt");
			int fid=0;
			if(infile.is_open())
			{
				cout<<" => Loading Information from file: "<<endl;
				while(fid!=-1)
				{
					
					int userid;
					int prior;
					char op;
					infile>>fid;
					if(fid==-1)
						break;
					infile>>userid;
					infile>>prior;
					//infile>>op;
					infile>>op;
					
					cout<<"      User ID: "<<userid<<endl;
					cout<<"      File ID: "<<fid<<endl;
					cout<<"      Priority: "<<prior<<endl;
					cout<<"      Access Type: "<<op<<endl;
					
					object.insertinTable(fid,prior,userid,op);					
					cout<<endl;
				}
			}

		}

		if(menu==3)
		{
			cout<<" => User Information: "<<endl;
			cout<<"    Enter File Id: "<<endl;
			int fid;
			cout<<"      File ID: ";
			cin>>fid;
			bool del=object.deletion(fid);
			if(del==true)
				cout<<"Deleted Successfully"<<endl;
			else
				cout<<"Failure. Queue is not empty or a user is currently accessing it"<<endl;


		}
		if(menu==2)
		{
			cout<<" => User Information: "<<endl;
			cout<<"    Enter User Id and File Id: "<<endl;
			int userid;
			int fid;
			cout<<"      User ID: ";
			cin>>userid;
			cout<<"      File ID: ";
			cin>>fid;
			int prior;
			int option;
			cout<<"    Do you want to you use number or characters (1 for number and 0 for characters)? "<<endl;
			cout<<"      Option: ";
			cin>>option;
			if(option==1)
			{
				cout<<"    Enter Priority: "<<endl;
				cout<<"      Priority: ";
				cin>>prior;
			}
			else
			{
				char p;
				cout<<"    Enter Priority (H for highest and L for Lowest): "<<endl;
				cout<<"      Priority: ";
				cin>>p;
				if(p=='H')
					prior=101;
				else
					prior=-1;
			}
			char task;
			cout<<"    Enter R for Read Access and W for Write Access: "<<endl;
			cout<<"      Access Type: ";
			cin>>task;
			object.insertinTable(fid,prior,userid,task);
			//object.insertfile(fid);
		}

		if(menu==6)
		{
			object.display();

		
		}

		if(menu==4)
		{
			cout<<" => User Information: "<<endl;
			cout<<"    Enter User Id and File Id: "<<endl;
			int userid;
			int fid;
			cout<<"      User ID: ";
			cin>>userid;
			cout<<"      File ID: ";
			cin>>fid;
			int prior;
			int option;
			cout<<"    Do you want to you use number or characters (1 for number and 0 for characters)? "<<endl;
			cout<<"      Option: ";
			cin>>option;
			if(option==1)
			{
				cout<<"    Enter Priority: "<<endl;
				cout<<"      Priority: ";
				cin>>prior;
			}
			else
			{
				char p;
				cout<<"    Enter Priority (H for highest and L for Lowest): "<<endl;
				cout<<"      Priority: ";
				cin>>p;
				if(p=='H')
					prior=101;
				else
					prior=-1;
			}
			char task;
			cout<<"    Enter R for Read Access and W for Write Access: "<<endl;
			cout<<"      Access Type: ";
			cin>>task;

			object.insertinQueue(fid,prior,userid,task);
		}
		if (menu==5)
		{
			cout<<" => User Information: "<<endl;
			cout<<"    Enter File Id: "<<endl;
			int fid;
			cout<<"      File ID: ";
			cin>>fid;
			cout<<"    Enter User ID: "<<endl;
			int uid;
			cout<<"      User ID: ";
			cin>>uid;
			object.release(fid, uid);

		}
		if(menu==7)
			break;
		cout<<endl;
		cout<<"----------Menu----------"<<endl;
		cout<<"1- To load the data"<<endl;
		cout<<"2- To insert a file"<<endl;
		cout<<"3- To delete a file"<<endl;
		cout<<"4- To request access"<<endl;
		cout<<"5- To release a file"<<endl;
		cout<<"6- To print the hash table"<<endl;
		cout<<"7- To exit"<<endl;
		
		cin>>menu;
	}
	
	
	system("pause");
	return 0;
}

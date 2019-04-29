#include<iostream>
#include <fstream>
#include<string>
#include <time.h>
#include "goods.h"
using namespace std;

struct linknode
{
	Goods data;
	linknode *next;
};
class llist
{
		private:
		linknode *head, *tail;
		public:
		llist()
		{
			head=NULL;
			tail=NULL;
		}
		void createnode(Goods value)
		{
			linknode *temp=new linknode;
			temp->data=value;
			temp->next=NULL;
			if(head==NULL)
			{
				head=temp;
				tail=temp;
				temp=NULL;
			}
			else
			{
				tail->next=temp;
				tail=temp;
			}
		}
		void display()
		{
			linknode *temp=new linknode;
			temp=head;
			while(temp!=NULL)
			{
				cout<<"\n";
				cout << "Name:" << temp->data.getName() << "\t";
				cout << "GoodsId:" << temp->data.getGoodsId() << "\t";
				cout << "Price:" << temp->data.getPrice() << "\t";
				cout << "Quantity:" << temp->data.getQuantity() << "\t";
				cout << "Best Before Date:" << temp->data.getBBD() << "\t";
				temp=temp->next;
			}
		}
		void insert_start(Goods value)
		{
			linknode *temp=new linknode;
			temp->data=value;
			temp->next=head;
			head=temp;
		}
		void insert_position(int pos, Goods value)
		{
			linknode *pre=new linknode;
			linknode *cur=new linknode;
			linknode *temp=new linknode;
			cur=head;
			for(int i=1;i<pos;i++)
			{
				pre=cur;
				cur=cur->next;
			}
			temp->data=value;
			pre->next=temp;
			temp->next=cur;
		}
		void delete_first()
		{
			linknode *temp=new linknode;
			temp=head;
			head=head->next;
			delete temp;
		}
		void delete_last()
		{
			linknode *current=new linknode;
			linknode *previous=new linknode;
			current=head;
			while(current->next!=NULL)
			{
				previous=current;
				current=current->next;
			}
			tail=previous;
			previous->next=NULL;
			delete current;
		}
		void delete_position(int pos)
		{
			linknode *current=new linknode;
			linknode *previous=new linknode;
			current=head;
			for(int i=1;i<pos;i++)
			{
				previous=current;
				current=current->next;
			}
			previous->next=current->next;
		}

		double computeFinalPrice(){
			double totalPrice = 0.0;
			linknode *temp=new linknode;
			temp=head;
			while(temp!=NULL)
			{
				totalPrice += (temp->data.getPrice() * temp->data.getQuantity());
				temp=temp->next;
			}
			return totalPrice;
		}

		int find(int productId)
		{
			linknode *temp = new linknode;
			temp = head;
			int pos = -1, i = 1;

			while (temp != NULL)
			{
				if(temp->data.getGoodsId() == productId){
					pos = i;
				}
				i++;
				temp = temp->next;
			}
			return pos;
		}

		void updateInFile(double totalPrice)
		{
			int items = 0 ;
			linknode *temp = new linknode;
			temp = head;


			while (temp != NULL)
			{
				items ++;
				temp = temp->next;
			}
			string key = currentDateTime() + ", Goods sold: " +  to_string(items) + " total price: "+  to_string(totalPrice);
			ofstream a_file("paybook.txt", std::ios_base::app);
			a_file << key << "\n" ;
			a_file.close();
		}

		const std::string currentDateTime()
		{
			time_t now = time(0);
			struct tm tstruct;
			char buf[80];
			tstruct = *localtime(&now);

			strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

			return buf;
		}

		void delete_all()
		{
			head = NULL;
			tail = NULL;
		}
};

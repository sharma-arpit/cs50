// single Linked list 

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

struct node
{
	int data;
	struct node* next;
};
	

// Insertion  functions 
void insertafter(struct node prev_node, int new_data)
{
	if(prev_node->next == Null)
	{
		cout<< "this operation can not be performed "<< endl;
		return;
	}
	
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	
	new_node-> data = new_data;
	new_node-> next = prev_node-> next;
	prev_node-> next = new_node;
}


void push(struct node** head, int new_data)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node-> next = *head;
	*head = new_node

}


void append(struct node** head, int new_data)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node-> next = Null;
	
	if(*head = Null)
	{
		*head = new_node;
		return;
	}
	
	struct node* last = *head
	while(last->next != Null)
	{
		last = last->next
		
	}
	
	last->next = new_node;
	return;
}


// delete function
void del(struct node** head, int position)
{
	struct node* temp = *head;
	
	if(*head == Null)
	{
		return ;
	}
	
	//if head is removed
	if(position == 0)
	{
		*head = temp->next;
		free(temp);
		return;
	}
	
	for(int i =0; i<position-1; i++)
	{
		temp = temp->next;
		
	}
	
	if(temp == Null || temp->next == Null)
	return;
	
	struct node* next = temp->next->next;
	free(temp->next);
	temp->next = next;
}


	
int main()
{
	struct node* head = Null;
	struct node* second = Null;
	
	
	head = (struct node*) malloc(sizeof(struct node));
	second = (struct node*) malloc(sizeof(struct node));

	
	head->data = 1;
	head->next = second;
	
	second->data = 2;
	second->next = Null;
	
	
}

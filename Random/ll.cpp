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
void insertafter(struct node* prev_node, int new_data)
{
	if(prev_node->next == NULL)
	{
		cout<< "this operation can not be performed "<< endl;
		return;
	}
	
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	
	new_node-> data = new_data;
	new_node-> next = prev_node-> next;
	prev_node-> next = new_node;
	return;
}


void push(struct node** head, int new_data)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node-> next = *head;
	*head = new_node;
	return;

}


void append(struct node** head, int new_data)
{
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node-> next = NULL;
	
	if(*head == NULL)
	{
		*head = new_node;
		return;
	}
	
	struct node* last = *head;
	while(last->next != NULL)
	{
		last = last->next;
		
	}
	
	last->next = new_node;
	return;
	
}


// delete function
void del(struct node** head, int position)
{
	struct node* temp = *head;
	
	if(*head == NULL)
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
	
	if(temp == NULL || temp->next == NULL)
	return;
	
	struct node* next = temp->next->next;
	free(temp->next);
	temp->next = next;
}



// print list
void print(struct node** head)
{
	struct node* temp = *head;
	
	while(temp != NULL)
	{
		cout<< temp->data<<endl;
		temp = temp->next;
	}
}
	
	

// rotate a linked list counter clock-wise
void rotate(struct node** head, int k)
{
	int m = k-1;
	struct node* current = *head;
	
	for(int i =0; i< m-1;i++)
	{
		current = current->next;
	}
	struct node* mth_node = current;
	
	while(current->next != NULL)
	{
		current = current->next;
	}
	 current->next = *head;
	 *head = mth_node->next;
	 mth_node->next = NULL;
	 
	 return;
}



int main()
{
	struct node* head = NULL;
	struct node* second = NULL;
	
	
	head = (struct node*) malloc(sizeof(struct node));
	second = (struct node*) malloc(sizeof(struct node));

	
	head->data = 1;
	head->next = second;
	
	second->data = 2;
	second->next = NULL;
	
	push(&head,5);
	insertafter(head->next,15);
	append(&head,22);
	append(&head,25);
	push(&head, 78);
	print(&head);
	cout<< "rotate kar diya"<< endl;
	
	rotate(&head,4);
	print(&head);
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct party_node{

  char* item; // name of the party item
  double price; // price of the item
  char* ta; // name of TA requesting the item
  struct party_node *next; // pointer to the next node
} typedef party_node;

int add_request(struct party_node **head , char *item , double price , char *ta){
  if (strcmp(item, "IDE") != 0){
    struct party_node* new_node = (struct party_node*)malloc(sizeof(struct party_node));

    new_node->item = item;
    new_node->ta = ta;
    new_node->price = price;
    new_node->next = (*head);

    (*head) = new_node;
    return 0;
  } return -1;
}

void remove_request(struct party_node *head){
  if (head == NULL){
    return;
  }
  
  struct party_node* temp = head;
  head = head->next;

  free(temp);
  
  return head;
}

void make_sorted(struct party_node** head)
{
    struct party_node* result = NULL;     
    struct party_node* current = *head;   
    struct party_node* next;
 
    while (current != NULL)
    {
        next = current->next;
 
        current = next;
    }
 
    *head = result;
    reverse(head);
}

void reverse(struct party_node** head_ref)
{
    struct party_node* prev = NULL;
    struct party_node* current = *head_ref;
    struct party_node* next = NULL;
    while (current != NULL) {
        // Store next
        next = current->next;
  
        // Reverse current node's pointer
        current->next = prev;
  
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

double finalize_list(struct party_node **head , double budget ){
  double counter = 0.00;
  struct party_node *temp= (*head);
while(temp!=NULL)
{
  if ((temp->price)+counter > budget){

  /*Linked list does not exist or the list is empty*/
    if(head == NULL || *head == NULL) return;
    
    /*Storing the head to a temporary variable*/
    temp = *head;
    
    /*Moving head to the next node*/
    *head = (*head)->next;
    
    /*Deleting the first node*/
    free(temp);
  } else{
    temp = *head;
  }
     
}
}

void print_list(struct party_node *head){
    int count = 1;
    while(head!=NULL){
        printf("Item: %s\n", head->item);  
        printf("TA: %s\n", head->ta);
        printf("Price: %d\n", head->price);
        printf("\n");
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}


int main(){
  struct party_node* head = NULL;
  struct party_node* second = NULL;
  struct party_node* third = NULL;

  head = (struct party_node*)malloc(sizeof(struct party_node));
  second = (struct party_node*)malloc(sizeof(struct party_node));
  third = (struct party_node*)malloc(sizeof(struct party_node));

  char item1[250] = "Chips";
  char ta1[250] = "Sam";
  double price1 = 5.50;

  head->item = &item1;
  head->ta = &ta1;
  head->price = price1;
  head->next = NULL;

  char item2[250] = "Cake";
  char ta2[250] = "Beth";
  
  char item3[250] = "IDE";
  char ta3[250] = "Chris";

  add_request(&head, &item3, 1.00, &ta3);
  add_request(&head, &item2, 5.50, &ta2);
  printf("Here is my list before deleting:\n");
  print_list(head);
  printf("\n\n");
  
  printf("Here is my list after deleting:\n");
  remove_request(head);
  make_sorted(&head);
  /*finalize_list(&head, 6.00);*/
  /*print_list(head);*/
  
}

/*
int main(){
    //Empty list
    struct party_node* head = NULL;

    int check_add = 0;
    //Adding TA requests
    printf("Adding the TA requests:\n");
    check_add = add_request(&head, "Speakers", 99.99, "Zoe");
    check_add = add_request(&head, "Sushi", 288.88, "Ali");
    //Check add_request() return value
    check_add = add_request(&head, "Board games", 150.00, "Bill");
    if(check_add==-1){
        printf("Board games was not added.\n");
    }
    check_add = add_request(&head, "IDE", 0.00, "TA who will not be named");
    if(check_add==-1){
        printf("IDE was not added.\n");
    }
    check_add = add_request(&head, "Balloons", 2.49, "Brian");
    check_add = add_request(&head, "Limousine rental", 500.01, "Tony");
    check_add = add_request(&head, "Coffee and doughnuts", 10.00, "Nhien");
    check_add = add_request(&head, "Croissants", 25.50, "Gil");
    check_add = add_request(&head, "Pineapple pizza", 29.99, "Jeffrey");
    check_add = add_request(&head, "Charcuterie tray", 79.99, "Samantha");
    check_add = add_request(&head, "Champagne", 100.00, "Samantha");

    print_list(head); //10 requests added

    //Remove Samantha's request for Champagne
    printf("LIFO removal:\n");
    remove_request(head);
    print_list(head);

    
    //Sort by price
    printf("Sorting by price:");
    make_sorted(&head);
    print_list(head);
    /*
    //Finalize the shopping list
    printf("Finalizing the shopping list:\n");
    double remainder=0.00;
    remainder = finalize_list(&head, 500.00);
    print_list(head);
    printf("The remainder after shopping is: %.2lf\n", remainder);

    //Free the list
    while(head!=NULL){
        remove_request(&head);
    }
    
    printf("Ready to party!\n");
    return 0;
}
*/
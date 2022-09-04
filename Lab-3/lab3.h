#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_request(struct party_node **head, char *item, double price, char *ta);
void remove_request(struct party_node **head);
void make_sorted(struct party_node **head);
double finalize_list(struct party_node **head, double budget);
void print_list(struct party_node *head);

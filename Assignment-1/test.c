#include "a1.h"

int num_items(char** item_codes, int count){
  // SORTING TIME
  int i, j, k;
  int counter = 0;
  for ( i = 0; i < count; i ++)  
  {  
      for ( j = i + 1; j < count; j++)  
      { 
          if ( strcmp(item_codes[i], item_codes[j]) == 0)  
          {  
              for ( k = j; k < count - 1; k++)  
              {  
                  item_codes[k] = item_codes[k + 1];  
              }
                count--;    
                j--;      
            }  
        }  
    }
  for(int i = 0; i < count; i ++){
    counter += 1;
  }
  //printf("%d", counter);
  return counter;
}

Order* build_order(char* items, char* quantities){
  //CREATE A STRUCT
  Order* new_order = (Order*) malloc(sizeof(struct Order));
  new_order->item_codes = malloc(new_order->num_items * sizeof(char*));
	new_order->item_quantities =  (int*) malloc(new_order->num_items * sizeof(int));
  
  // COUNT ITEMS 
  int count = 0;
  int counter;
  int a = 0;
  char* item_codes[MAX_ITEM_NAME_LENGTH];
  char temp[ITEM_CODE_LENGTH];
  
  while(a<= (strlen(items)-1)){
    temp[0] = items[a];
    temp[1] = items[a+1];
    //temp[2] = " ";
    item_codes[count] = strdup(temp);
    count += 1;
    a += 2;
  }
  
  counter = num_items(item_codes, count);
  new_order->num_items = counter;

  // ITEMS
  int i = 0;
  int j = 0;
  int k = 0;
  char* temp2;
  int count2 = 0;

  // STRING MANAGEMENT
  /*char str[100];
      //str[0] = quantities[0];
      //str[0] = MENU_DELIM;
      strcpy(str, MENU_DELIM);
  //strcat(quantities, MENU_DELIM);
  //printf("%s", quantities);*/
  /*char* str;
  strcpy(str, MENU_DELIM);*/

  for(int i = 0; i < counter; i++){
    new_order->item_codes [i] = malloc(sizeof(char) * ITEM_CODE_LENGTH);
    temp2 = items + (i*2);
    strncpy(new_order->item_codes[i], temp2, 2);
    new_order->item_codes[i][ITEM_CODE_LENGTH - 1] = '\0';
    char quantity[strlen(quantities)-1];
    for(k = 0; j < strlen(quantities); j++, k++){
      if (quantities[j] == *MENU_DELIM){
        
        j++;
        break;
            }
            quantity[k] = quantities[j];
        }
    quantity[k] = '\0';
    //printf("Putting in: %s\n", quantity);
    new_order->item_quantities[i] = atoi(quantity);
    printf("%d\n", new_order->item_quantities[i]);
    }
  for(int i = 0; i < new_order->num_items; i++){
    //printf("%d\n", order_1->item_quantities[i]);
    printf("%d\n", new_order->item_quantities[i]);
  }
  return new_order;
  }


int main(){
  
  Order* order_1 = build_order("A1B2C3D4E5", "10,25,90,51,11 ");
  /*printf("Order: %d\n", order_1->num_items);
  for(int i = 0; i < order_1->num_items; i++){
    //printf("%d\n", order_1->item_quantities[i]);
    printf("%d\n", order_1->item_quantities[i]);*/
  }


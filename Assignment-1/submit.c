#include "a1.h"

Menu* load_menu(char* fname){
  
  FILE *fp;
  fp = fopen(fname, "r");
  // ITEM CODES
  char item[10];
  char buf1[MAX_ITEM_NAME_LENGTH];
  char temp[ITEM_CODE_LENGTH];
  char *code_array[MAX_ITEM_NAME_LENGTH];
  int count = 0;
  while (fscanf(fp,"%s%*[^\n]",buf1) == 1){
    int i = 0;
    while(temp[i] == " "){
      i++;
    }
    temp[i] = buf1[i];
    temp[i+1] = buf1[i+1];
   // printf("%s", temp);
    code_array[count] = strdup(temp);
    //printf("Adding: %s at array[%d]\n", code_array[count], count);
    count = count + 1;
    //printf("%d", count);
  }
  fclose(fp);
  FILE *fp1;
  fp1 = fopen(fname, "r");

// ITEM NAMES
  char buf2[MAX_ITEM_NAME_LENGTH];
  char temp2[MAX_ITEM_NAME_LENGTH];
  char *item_array[MAX_ITEM_NAME_LENGTH];
  char *token;
  int count2 = 0;
  
  while(fgets(temp2, MAX_ITEM_NAME_LENGTH, fp1)!=NULL ) {
    token = strtok(temp2,MENU_DELIM);
    token = strtok(NULL, MENU_DELIM);
    //printf("%s", token);
    item_array[count2] = strdup(token);
    count2 = count2 + 1;
    }
  fclose(fp1);

  FILE *fp2;
  fp2 = fopen(fname, "r");

// ITEM PRICES
  char temp3[MAX_ITEM_NAME_LENGTH];
  double prices[MAX_ITEM_NAME_LENGTH];
  double con_temp3;
  char *token1;
  int count3 = 0;
  
  while(fgets(temp3, MAX_ITEM_NAME_LENGTH, fp2)!=NULL ) {
    token1 = strtok(temp3,"$");
    token1 = strtok(NULL, "$");
    con_temp3 = atof(token1);
    //printf("%f\n", con_temp3);
    prices[count3] = con_temp3;
    count3 = count3 + 1;
    }
  fclose(fp2);
  
  struct Menu* menu = (struct Menu*)malloc(sizeof(struct Menu));
  menu->num_items = count;
  menu->item_codes = code_array;
  menu->item_names = item_array;
  menu->item_cost_per_unit = prices;

  return menu;

  /*printf("%s", code_array[0]);
  printf("%s", code_array[1]);
  printf("%s", code_array[2]);
  printf("%s", code_array[3]);
  printf("%s", code_array[4]);
  printf("%s", code_array[5]);
  for(int i = 0; i < 6; i++){
    printf("%s\n", code_array[i]);
  }*/
        
}

Restaurant* initialize_restaurant(char* name){
  struct Restaurant *restaurant = (Restaurant*) malloc(sizeof(Restaurant));
  restaurant->name = name;
  restaurant->menu = load_menu(MENU_FNAME);
  restaurant->num_completed_orders = 0;
  restaurant->num_pending_orders = 0;
  restaurant->pending_orders = (struct Queue*)malloc(sizeof(struct Queue));
  restaurant->pending_orders->head = NULL;
  restaurant->pending_orders->tail = NULL;

  return restaurant;
}


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
  char* item_codes[100];
  char temp[2];
  int count = 0;
  int counter;
  int a = 0;
  while(a<= (strlen(items)-1)){
    temp[0] = items[a];
    temp[1] = items[a+1];
    //temp[2] = " ";
    item_codes[count] = strdup(temp);
    count += 1;
    a += 2;
  }
  counter = num_items(item_codes, count);

  // ITEM QUANTITIES
  char* temp1 = strdup(quantities);
  char* found;
  int quantities_array[100];
  int i = 0;
  while( (found = strsep(&temp1,",")) != NULL ){
    quantities_array[i] = atoi(found);
    i++;
    }
  Order* order = (struct Order*)malloc(sizeof( struct Order));
  order->num_items = counter;
  order->item_codes = item_codes;
  order->item_quantities = quantities_array;
  
  return order;
  }

//Managing our order queue

void enqueue_order(Order* order, Restaurant* restaurant){
  // Create a new linked list node
  struct QueueNode *temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
  temp->order = order;
  temp->next = NULL;
  
  // Check if the queue is empty
  if (restaurant->pending_orders->tail == NULL){
    // If it was previously empty, the new node is now the front and the rear
    restaurant->pending_orders->head = restaurant->pending_orders->tail = temp;
    restaurant->num_pending_orders += 1;
    //printf("Enqueued to %s\n", restaurant->name);
    //printf("Hi im null\n");
    return;
    }
  // Add the new node at the end of the queue and update the rear
  restaurant->pending_orders->tail->next = temp;
  restaurant->pending_orders->tail = temp;
  restaurant->num_pending_orders += 1;
  //printf("Enqueued to %s\n", restaurant->name);
  return;
}


Order* dequeue_order(Restaurant* restaurant){
  struct Order *temp = (struct Order*)malloc(sizeof(struct Order));
  struct QueueNode *temp2 = (struct QueueNode*)malloc(sizeof(struct QueueNode));
  temp = restaurant->pending_orders->head->order;
  temp2 = restaurant->pending_orders->head;
  restaurant->pending_orders->head = restaurant->pending_orders->head->next;
  free(temp2);
  if(restaurant->pending_orders->head==NULL){
    restaurant->pending_orders->tail=NULL;
    }
  restaurant->num_pending_orders -= 1;
  restaurant->num_completed_orders += 1;
  return temp;
}


//	Getting information about our orders and order status

double get_item_cost(char* item_code, Menu* menu){
  double price;
  Menu* temp = load_menu(MENU_FNAME);
  int i = 0;
  while(strcmp(temp->item_codes[i], item_code) != 0 && i < temp->num_items){
    //printf("%s\n", temp->item_codes[i]);
    i++;
  }
  //printf("FOUND IT: %d\n", i);
  //printf("Your price is: %.2f", menu->item_cost_per_unit[i]);
  price = menu->item_cost_per_unit[i];
  return price;
}


void print_menu(Menu* menu){
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++){
		fprintf(stdout, "(%s) %s: %.2f\n", 
			menu->item_codes[i], 
			menu->item_names[i], 
			menu->item_cost_per_unit[i]	
		);
	}
}


void print_order(Order* order){
	for (int i = 0; i < order->num_items; i++){
		fprintf(
			stdout, 
			"%d x (%s)\n", 
			order->item_quantities[i], 
			order->item_codes[i]
		);
	}
}


void print_receipt(Order* order, Menu* menu){
	for (int i = 0; i < order->num_items; i++){
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout, 
			"%d x (%s)\n @$%.2f ea \t %.2f\n", 
			order->item_quantities[i],
			order->item_codes[i], 
			item_cost,
			item_cost * order->item_quantities[i]
		);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);
	
	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}
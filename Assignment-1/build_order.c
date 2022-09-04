#include "a1.h"

Order* build_order(char* items , char* quantities ){
	// CREATE A STRUCT 
  Order* o = malloc(sizeof(struct Order));
  // INITIALIZE THE STRUCT
  // number of items - fix that lol
	o->num_items = 5;
  //dynammically allocate item codes and quantities
	o->item_codes = malloc(o->num_items * sizeof(char*));
	o->item_quantities =  malloc(o->num_items * sizeof(int));
	//printf("number of items: %d\n", o->num_items );
	int j=0,x=0;
	for(int i = 0; i< o->num_items; i++){
	    //printf("-> i: %d\n",i);
    // dynamically allocate every portion of item codes
		o->item_codes [i] = malloc(sizeof(char) * ITEM_CODE_LENGTH);
    // copy the first 2 chars of items
		strncpy(o->item_codes[i], items + (i*2) , 2);
    // add the null char
		o->item_codes[i][ITEM_CODE_LENGTH - 1] = '\0';
        //char* quantity;
        //printf("%s with length: %ld\n", quantities,strlen(quantities) );
    // temp array for quantity
        char quantity[strlen(quantities)];
        for ( x = 0; j< strlen(quantities); j++, x++){
          //printf("%d\n", j);
           // printf("at %d: %c\n", j, quantities[j]);
		   // checxkkkkkkkk
            if (quantities[j] == *MENU_DELIM){
                j++;
                break;
            }
            quantity[x] = quantities[j];
        }
        //printf("%s\n", quantity);
        //printf("%d\n", atoi(quantity));

    
       //strsep(&quantities,MENU_DELIM);

		/*if (i == 0) { //smthn smelly
		   quantity= strtok(quantities, MENU_DELIM);
		}
		else{
		   quantity = strtok(NULL, MENU_DELIM);
		}*/
    //printf("Putting in: %s", quantity);
		o->item_quantities[i] = atoi(quantity);  
	}
  /*for(int i = 0; i < o->num_items; i++){
    //printf("%d\n", order_1->item_quantities[i]);
      printf("%d\n", o->item_quantities[i]);
  }*/
	return o;
}

int main(){
  
  Order* order_1 = build_order("A1B1", "10,25,90,51,11");
  printf("Order: %d\n", order_1->num_items);
  for(int i = 0; i < order_1->num_items; i++){
    //printf("%d\n", order_1->item_quantities[i]);
      printf("%d\n", order_1->item_quantities[i]);
  }
  /*Order* order_2 = build_order("A1B1C1", "12,10,9");
  printf("Order: %d\n", order_1->num_items);
  for(int i = 0; i < order_1->num_items; i++){
    //printf("%d\n", order_1->item_quantities[i]);
    printf("%s\n", order_1->item_codes[i]);
  }*/
}
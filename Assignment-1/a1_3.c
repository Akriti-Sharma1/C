#include "a1.h"
/**
	Add your functions to this file.
	Make sure to review a1.h.
	Do NOT include a main() function in this file
	when you submit.
*/

Restaurant* initialize_restaurant(char* name)
{
	Restaurant* restaurant;
	restaurant = (Restaurant*)malloc(sizeof(Restaurant));
	restaurant->menu = load_menu(MENU_FNAME);
	Queue* queue;
	queue = (Queue*)malloc(sizeof(Queue));//set it to an empty queue 
	queue->head = NULL;
	queue->tail = NULL;
	restaurant->name = name;
	//restaurant->menu = ****add in this palce after completing load_menu
	restaurant->num_completed_orders = 0;
	restaurant->num_pending_orders = 0;

	restaurant->pending_orders = queue; 



	return restaurant;

}

Menu* load_menu(char* fname)
{
	Menu* menu; 
	menu = (struct Menu*)malloc(sizeof(struct Menu));
	FILE *fp;
	char* file_name = fname;
	fp = fopen(file_name, "r");

	//counts items
	int count = 0;
	char character;
	char* code;
	int character_count = 0;
	char line[MAX_ITEM_NAME_LENGTH+ITEM_CODE_LENGTH+MAX_ITEM_QUANTITY_DIGITS];
	menu->item_codes = (char**)malloc(sizeof(char*));//create pointers * the number of elements (insert pointers inside the pointers)
	menu->item_names = (char**)malloc(sizeof(char*));
	menu ->item_cost_per_unit = (double*)malloc(sizeof(double));

	while (fgets(line, sizeof(line), fp)!=NULL)
	{	
		if(line[0]!='\n') //if line is not white line
		{
		code = strtok(line, MENU_DELIM); //separate by menu_delim
		int end = 1;
		while ((*code == ' ') || (*code == '\t'))
    		++code;

		int num_count = 0; 

		char* code_pointer = (char*)malloc(sizeof(char*)+5+MAX_ITEM_NAME_LENGTH);
		if(code!=NULL)
		{
			strcpy(code_pointer, code);//append the value to the pointer
			menu->item_codes = realloc(menu->item_codes, sizeof(char*)*(count+1));//create pointers * the number of elements (insert pointers inside the pointers)
			menu->item_codes[count] = code_pointer;
			num_count++;
		}
		if(line[0]=='\n')
		{
			free(code_pointer);
		}
		//printf("%s", code);

		while (code != NULL)
		{
			code = strtok(NULL, MENU_DELIM);
			if(code != NULL)
			{
				while ((*code == ' ') || (*code == '\t'))
    				++code;//trims the white trailing white space 

				if (num_count == 1)
				{
					char* item_pointer  = (char*)malloc(sizeof(char*)+5+MAX_ITEM_NAME_LENGTH);
					menu->item_names = realloc(menu->item_names, sizeof(char*)*(count+1));//create pointers * the number of elements (insert pointers inside the pointers)
					if(line[0]!='\n')
					{
						strcpy(item_pointer, code);
						menu->item_names[count] = item_pointer;
						num_count++;//increment count 
					}
					if(line[0]=='\n')
					{free(item_pointer);
					}
				}
				else if(num_count == 2)
				{
					double rat;
					char* dollar;
					memmove(&code[0], &code[1], strlen(code)); //trims the first element 
					rat = strtod(code,&dollar);

					menu->item_cost_per_unit = realloc(menu->item_cost_per_unit, sizeof(double)*(count+1));//create pointers * the number of elements (insert pointers inside the pointers)
					menu->item_cost_per_unit[count] = rat;

					count++;
				}
			}	
			}
			
			}
	}
	fclose(fp);
	free(code);

	menu->num_items = count;
	return menu;

}
Order* build_order(char* items, char* quantities)
{
	
	Order* order; 
	
	order = (Order*)malloc(sizeof(Order));
	int count = 0;
	
	for(int x = 0; *(items+x) != '\0'; x++)
	{
		count+=1;//counts the number of characters
	}
	order->num_items = count/(ITEM_CODE_LENGTH-1);//set number of items as the length of item_codes/2
	order->item_codes = (char**)malloc(sizeof(char*)*order->num_items);
	order->item_quantities = (int*)malloc(sizeof(int)*order->num_items);

	int character_count = 0;
	int code_count = 0; // counts the "i"th element 
	char* code = (char*)calloc(MAX_ITEM_NAME_LENGTH, sizeof(char*)); //place to concatenate the strings 
	int is_end = 0;


	for(int x = 0; is_end != 1; x++) // appends the item_code to the corresponding array 
	{
		strncat(code, items+x, 1);//concatenate the letters to the string 
		character_count += 1;
		is_end = 0;
		
		if (character_count%(ITEM_CODE_LENGTH-1)==0)
		{
			char* code_pointer = (char*)malloc(sizeof(char*));
			// = (char*)malloc(sizeof(char*)*MAX_ITEM_NAME_LENGTH);
			strcpy(code_pointer, code);
			*(order->item_codes+code_count) = code_pointer;
			code_count+= 1;
			strcpy(code, "");
			if (*(items+x) == '\0')
			{
				free(code_pointer);
			}
			//put into the array 
		}
		if (*(items+x) == '\0')
		{
			is_end = 1;
		}
	}	
	
	int quantity_count = 0;//counts the "i"th element 
	int end = 1;
	
	
	for (int i = 0; end != 0; i++)
	{
		if (*(quantities+i)!=*MENU_DELIM)
		{
			strncat(code, quantities+i, 1);//concatenate the letters to the string 
		}
		else 
		{
			int rat;
			rat = atoi(code);

			order->item_quantities[quantity_count] = rat;
			quantity_count += 1;
			strcpy(code, "");
		}
		if (*(quantities+i) == '\0')
		{
			int y;
			y = atoi(code);

			order->item_quantities[quantity_count] = y;
			end = 0;//set the for loop to the end 
		}
	}	
	free(code);

	return order;
}

void enqueue_order(Order* order, Restaurant* restaurant) //FIFO 
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); 
	if (restaurant -> pending_orders-> tail == NULL)
	{
		restaurant -> pending_orders-> head = restaurant -> pending_orders-> tail = temp; //set head, tail, and temp to thesame queuenode
		restaurant -> pending_orders-> tail -> order = (Order*)malloc(sizeof(Order));

		restaurant -> pending_orders-> tail -> order = order;
		restaurant -> num_pending_orders +=1;
		return;
	}
	restaurant -> pending_orders-> tail->next = temp;
	restaurant -> pending_orders-> tail = temp; //advance a node
	restaurant -> pending_orders-> tail -> order = (Order*)malloc(sizeof(Order));//add order to tail
	restaurant -> pending_orders-> tail -> order = order;
	printf("this is the num_pending orders%d",	restaurant -> num_pending_orders);

	restaurant -> num_pending_orders+= 1;
}
Order* dequeue_order(Restaurant* restaurant)
{
	QueueNode* temp = restaurant->pending_orders->head;
	
	Order* temp_order; 
	temp_order = temp->order; //before the head is changed 
	
	if(restaurant->pending_orders->head->next != NULL) // if there is a next order awaiting
	{
		restaurant->pending_orders->head = restaurant->pending_orders->head->next;

		restaurant->num_completed_orders++;
		restaurant->num_pending_orders--;
		return temp_order; // return this if the temp_order exists 

	}
	else if (restaurant->pending_orders->head->next == NULL)
	{
		restaurant->pending_orders->head = NULL; // if the next is null, set head to null 
		restaurant->pending_orders->tail = NULL;
		restaurant->num_completed_orders++;
		restaurant->num_pending_orders--;
		//return NULL;
		 // return this if the temp_order exists 
	}
	free(temp);

	return temp_order;

}


double get_item_cost(char* item_code, Menu* menu)
{
	
	int count = 0;
	for (int x = 0;strcmp(*(menu->item_codes+x), item_code); x++)
	{
		count += 1; 
	}
	
	return *(menu->item_cost_per_unit+count);
}

double get_order_subtotal(Order* order, Menu* menu)
{
	Order* order1 = order;
	Menu* menu1 = menu;

	double sub_total_cost = 0.0;

	for(int i = 0; i < order1->num_items; i++)
	{
		double price = get_item_cost(*(order1->item_codes+i), menu1);
		sub_total_cost += price*(*(order1->item_quantities+i));
	}
	return sub_total_cost;
}
double get_order_total(Order* order, Menu* menu)
{
	double subtotalcost = get_order_subtotal(order, menu);
	double total_cost = subtotalcost/100.00*(100+TAX_RATE);
	return total_cost;
}
int get_num_completed_orders(Restaurant* restaurant)
{
	int num_completed_orders1 = restaurant->num_completed_orders;
	return num_completed_orders1;
}

int get_num_pending_orders(Restaurant* restaurant)
{
	int num_pending_orders1 = restaurant->num_pending_orders;
	return num_pending_orders1;
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
	fprintf(stdout, "Tax %.2d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}
void clear_order(Order** order)
{
	Order* order1 = *order;

	for (int x = 0; x<order1->num_items; x++)
	{
		free(*(order1->item_codes+x));
	}

	free((order1->item_codes));
	free((order1->item_quantities));
	//free(*order);
	free(order1);
	order1 = NULL;
}

void clear_menu(Menu** menu)
{
	Menu* menu1 = *menu;
	
	for (int x = 0; x < menu1->num_items; x++)
	{
		
		if(menu1->item_names != NULL)	
		{
			if (*(menu1->item_names+x)!=NULL)
			{
				free(*(menu1->item_names+x));	
				free(*(menu1->item_codes+x));	

			}
		}
		/*
		if(menu1->item_codes != NULL)
		{
			if (*(menu1->item_codes+x)!=NULL)
			{


			free(*(menu1->item_codes+x));	
			}

		}
		*/
		
	}
	free((menu1->item_names));
	free((menu1->item_codes));	

		
	free(menu1->item_cost_per_unit);
	
	free(menu1);
	
	menu1 = NULL;
	
}

void close_restaurant(Restaurant** restaurant)
{
	Restaurant* restaurant1 = *restaurant;
	
	if(restaurant1->pending_orders->head!=NULL)
	{
		clear_order(&restaurant1->pending_orders->head->order);//clear order 
		free(restaurant1->pending_orders->head);

	}

	if(restaurant1->pending_orders->tail!=NULL)
	{
		clear_order(&restaurant1->pending_orders->tail->order);//clear order ]
		free(restaurant1->pending_orders->tail);
	}
	
	if (restaurant1->pending_orders != NULL)
	{
		free(restaurant1->pending_orders);

	}
	

	clear_menu(&restaurant1->menu);
	free(restaurant1);

	*restaurant = NULL;
}
/*
int main()
{
	Menu* menu;
	char str[]= "menu.txt";
	menu = load_menu(str);

	printf("%d", menu->num_items);
	
	//Restaurant* restaurant = initialize_restaurant("McBonalbs");
	//double cost = get_item_cost("D1", menu);
	
	return 0;
}
*/
#include "a1.h"

char* trim_whitespace(char* s);
Restaurant* initialize_restaurant(char* name){
    /*
		input: string literal
		return: pointer to restaurant with:
			name
			menu init
			num_completed_orders = 0
			num_pending_orders = 0
			pending_orders = empty queue
	*/

    // allocate memory to restaurant
    Restaurant* restaurant = (struct Restaurant*) malloc(sizeof(struct Restaurant));

    // initialize the name and num of orders(completed and pending)
    restaurant->name = name;
    restaurant->num_completed_orders = 0;
    restaurant->num_pending_orders = 0;

    // we allocate memory to a queue to keep track of orders
    Queue* pending_orders = (struct Queue*) malloc(sizeof(struct Queue));

    // initially, the queue is empty. so its head and tail are NULL
    pending_orders->head = NULL;
    pending_orders->tail = NULL;
    restaurant->pending_orders = pending_orders;

    // read the menu and return a pointer to that
    Menu* menu = load_menu(MENU_FNAME);

    // attach menu to restaurant's menu
    restaurant->menu = menu;
    return restaurant;
}

char* trim_whitespace(char* s) {
    char *start, *end;
    int length = strlen(s);
    start = s;
    end = s + length - 1;
    while (1) {
        if (*start == ' ' || *start == '\t' || *start == '\n' || *start =='\r') {
            start++;
        } else {
            break;
        }
    }
    while (1) {
        if (*end == ' ' || *end == '\t' || *end == '\n' || *end =='\r') {
            end--;
        } else {
            break;
        }
    }
    char temp[length + 1];
    int index = 0;
    while (start <= end) {
        temp[index++] = *start;
        start++;
    }
    temp[index] = '\0';

    char *result = malloc(strlen(temp) + 1);
    if (result == NULL)  // check if malloc failed
        return NULL;

    strcpy(result, temp);
    return result;
}

Menu* load_menu(char* fname) {
    Menu* menu = (struct Menu*) malloc(sizeof(struct Menu));
    // +21 is for cost (we don't know the max). +3 is for 2 commas and \n at the end
    char line[21+ITEM_CODE_LENGTH+MAX_ITEM_NAME_LENGTH+3];
    FILE* file;
    int num_items = 0;
    file = fopen(fname, "r");
    if (file == NULL) {
        printf("file can't be opened \n");
        // file is not healthy
    }
    // file is healthy
    while (fgets(line, sizeof(line), file) != NULL) {
        num_items++;
    }
    fclose(file);
    file = fopen(fname, "r");
    int i =0;

    // allocate memory to menu's parts. i.e., codes, names, and costs
    char** item_codes = (char**) malloc(sizeof(char*)*num_items);
    char** item_names = (char**) malloc(sizeof(char*)*num_items);
    double* item_costs = (double*) malloc(sizeof(double)*num_items);

    // read the file
    while (fgets(line, sizeof(line), file) != NULL) {

        int j = 0;

        // trim leading and trailing white spaces and also \n at the end
        char *line_trimmed = line;
        //char* to_be_deleted = line_trimmed;

        // split the line wit regards to MENU_DELIM
        char* token = strtok(line_trimmed, MENU_DELIM);
        while (token != NULL) {
            if (j == 0) {
                // we are dealing with item code
                char* item_code = (char*) malloc(sizeof(char)*ITEM_CODE_LENGTH);
                memset(item_code, '\0', sizeof(char) * ITEM_CODE_LENGTH);
                strcpy(item_code, token);
                item_codes[i] = item_code;
            }
            else if (j == 1) {
                // we are dealing with item name
                char* item_name = (char*) malloc(sizeof(char)*MAX_ITEM_NAME_LENGTH);
                memset(item_name, '\0', sizeof(char) * MAX_ITEM_NAME_LENGTH);
                strcpy(item_name, token);
                item_names[i] = item_name;
            } else {
                // we are dealing with item cost
                char* p;
                double item_cost = strtod(token+1, &p);
                item_costs[i] = item_cost;
            }
            j++;
            token = strtok(NULL, MENU_DELIM);
        }
        i++;

        // line_trimmed have been allocated dynamically in our helper function
        // it's our responsibility to clear the allocated memory
        //free(to_be_deleted);
    }
    fclose(file);

    // attach attributes to the menu
    menu->num_items = num_items;
    menu->item_codes = item_codes;
    menu->item_names = item_names;
    menu->item_cost_per_unit = item_costs;
    return menu;
}

int main(){
  
}
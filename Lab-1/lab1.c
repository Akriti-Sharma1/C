#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

double split_bill(double base_amount , double tax_rate, double tip_rate , int num_people) {
  double bill, final_bill, split;
  bill = base_amount + (base_amount * tax_rate);
  bill = bill + (bill * tip_rate);
  final_bill = bill / num_people;
  /*printf("%f\n", final_bill);*/
  final_bill = (int) (final_bill * 100);
  final_bill = final_bill / 100;
  /*printf("%f\n", final_bill);*/
  double checker = final_bill * num_people;
  checker = (int) (checker * 100);
  checker = checker / 100;
  /*printf("%f and %f", checker, bill);
  printf("%f", final_bill);*/
  if( checker != bill){
      final_bill += 0.01;
  }
  return (float) final_bill;
}

double adjust_price(double original_price) {
  double new_price;
  new_price = pow(original_price, 0.5);
  new_price = new_price * 10;
  return new_price;
}



int sandy_eats(char menu_item []){
  char *j, *k, *l, *fish;
  int length;
  int true_length = 0;
  char new_menu_item[250];
  length = strlen(menu_item);

  for(int i = 0; i <= length; i++) {
        new_menu_item[i] = tolower(menu_item[i]);
    }

  for(int i = 0; i < length; i++){
    if(new_menu_item[i] != ' '){
      true_length++;
    }
  }

  j = strchr(new_menu_item, 'j');
  k = strchr(new_menu_item, 'k');
  l = strchr(new_menu_item, 'k');
  fish = strstr(new_menu_item, "fish");  

  if (j != NULL || k != NULL || l != NULL){
    return 0;
  } else if(true_length % 2 != 0){
    return 0;
  }else if(fish != NULL){
    return 0;
  }else{
    return 1;
  }
}

void imagine_fish(char thing []){
  char *new_word;
  new_word = strcat(thing, "fish");
}

/*
int main(){
  printf("%f", split_bill(1.00, 0.30, 0.10, 8));
  return 0;
}*/

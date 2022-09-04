#include <stdio.h>

double split_bill(double base_amount , double tax_rate, double tip_rate , int num_people) {
  double final_bill;
  final_bill = base_amount + (base_amount * tax_rate);
  final_bill = final_bill + (final_bill * tip_rate);
  final_bill = final_bill / num_people;
  final_bill = final_bill + 0.01;
  return final_bill;
}


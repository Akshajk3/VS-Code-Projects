#include <iostream>

float Calculate_State_Tax(float revenue, float state_tax) 
{
  float sResult = revenue - (revenue * (state_tax * 0.01));
  return sResult;
}

float Calculate_County_Tax(float revenue, float county_tax) 
{
  float cResult = revenue - (revenue * (county_tax * 0.01));
  return cResult;
}

int main() 
{
  float total_revenue;
  std::cout << "What is your total revenue: ";
  std::cin >> total_revenue;

  float state_tax;
  std::cout << "What is your state tax: ";
  std::cin >> state_tax;

  float county_tax;
  std::cout << "What is your county tax: ";
  std::cin >> county_tax;

  float state_result = Calculate_State_Tax(total_revenue, state_tax);

  float county_result = Calculate_County_Tax(total_revenue, county_tax);
  std::cout << "Your total state tax is: ";
  std::cout << state_result << std::endl;
  std::cout << "Your total county tax is: ";
  std::cout << county_result << std::endl;
}

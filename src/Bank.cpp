#include <iostream>
#include <string>
#include <vector> 
#include <chrono>
#include <ctime>

#include <Bank.hpp>
#include <Time.hpp>
        
using namespace std;

Bank::Bank()
{}

Bank::Bank_Status Bank::get_bank_status()
{
     return bank_status;
}

Customer & Bank::search_customer(string username)
{
     for (size_t i = 0; i < customers.size(); i++)
     {
          if (customers[i].get_username() == username)
          {
               return customers[i];          
          }
     }
     throw out_of_range("Customer with this username not found");
}

Customer & Bank::search_customer(unsigned int account_number)
{
     for (size_t i = 0; i < customers.size(); i++)
     {
          if (customers[i].get_account_number() == account_number)
          {
               return customers[i];          
          }
     }
     throw out_of_range("Customer with this account number not found");
}

void Bank::add_customer(Customer customer)
{
     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }

     Time time;
     
     string temp_time = time.get_system_time();

     string history = "1 customer added to bank at : " + temp_time;

     this->customers.push_back(customer);
     this->bank_history.push_back(history);
     cout << "Customer Aded" << endl;
}

void Bank::set_bank_status(Bank_Status bank_status)
{
     Time time;
     
     string temp_time = time.get_system_time();

     string history = "Bank status changed at : " + temp_time;

     this->bank_status = bank_status;

     this->bank_history.push_back(history);
}

void Bank::get_loan(string username, string ip, unsigned long long int money)
{
     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }

     if (search_customer(username).get_card_status() == 1)
     {
          throw out_of_range("Account is closed");
     }
     
     unsigned int temp_money = search_customer(username).check_ip(ip).get_inventory(); 
     temp_money /= 4;
     temp_money *= 3;
     
     if (temp_money < money)
     {
          throw out_of_range("You must have 3/4 balance of your applying for loan in your inventory");
     }

     if (get_bank_inventory() < money)
     {
          throw out_of_range("sorry we cant give you this loan");
     }

     if (search_customer(username).get_debt() != 0)
     {
          throw out_of_range("You cant get a loan untill you pay your loan");
     }
     
     Time time;
     
     string temp_time = time.get_system_time();

     string history = "Received a loan at : " + temp_time;
     string temp_history = "loan gived to a customer at : " + temp_time;

     search_customer(username).increase_debt(money);
     withdraw_money_from_inventory(money);

     search_customer(username).add_to_history(history);
     this->bank_history.push_back(temp_history);

     cout << "Done" << endl;
}

void Bank::pay_loan(string username, unsigned long long int money)
{
     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }

     if (search_customer(username).get_card_status() == 1)
     {
          throw out_of_range("Account is closed");
     }

     if (money > 0)
     {
          Time time;
     
          string temp_time = time.get_system_time();

          string history = "loan payed at : " + temp_time;
          string temp_history = "customer payed back his loan at : " + temp_time;
          
          if (search_customer(username).get_debt() < money)
          {
               unsigned long long int temp_money1 = search_customer(username).get_debt(); 
               unsigned long long int temp_money2 = money - search_customer(username).get_debt();
               
               search_customer(username).decrease_debt(temp_money1);
               search_customer(username).increase_money(temp_money2);
               
               add_money_to_inventory(money);
               
               search_customer(username).add_to_history(history);
               this->bank_history.push_back(temp_history);

               cout << "Loan payed and some money added to your inventory" << endl;
          }
          else if (search_customer(username).get_debt() == money)
          {
               search_customer(username).decrease_debt(money);
               add_money_to_inventory(money);
           
               search_customer(username).add_to_history(history);
               this->bank_history.push_back(temp_history);
               
               cout << "Loan payed" << endl;
          }
          else if (search_customer(username).get_debt() > money)
          {
               search_customer(username).decrease_debt(money);
               add_money_to_inventory(money);
               
               search_customer(username).add_to_history(history);
               this->bank_history.push_back(temp_history);
               
               cout << "A part of loan payed" << endl;
          }                        
     }
     else if (money <= 0)
     {
          throw invalid_argument("Enter a valid balance");
     }
}

void Bank::deposit(string username, string ip, unsigned long long int money)
{
     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }

     if (money > 0)
     {    
          
          Time time;
     
          string temp_time = time.get_system_time();

          string history = "Deposited money at : " + temp_time;
          string temp_history = "a customer Deposited his money to bank at : " + temp_time;

          search_customer(username).check_ip(ip);

          if (search_customer(username).get_card_status() == 1)
          {
               throw out_of_range("Your account is expired");
          }
          
          search_customer(username).check_ip(ip).increase_money(money);
          add_money_to_inventory(money);
          
          search_customer(username).add_to_history(history);
          this->bank_history.push_back(temp_history);
          
          cout << "Done" << endl;
     }
     else if (money <= 0)
     {
          throw invalid_argument("Enter a valid balance");
     }
}

void Bank::transfer(string sender_username, string sender_ip, string receiver_username, unsigned long long int money)
{
     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }
     
     if (money > 0)
     {
          Time time;
     
          string temp_time = time.get_system_time();

          string history = "Sended money at : " + temp_time;
          string temp_history = "Received money at : " + temp_time;
          string report = "a transfer happend at : " + temp_time;

          search_customer(sender_username).check_ip(sender_ip);
          search_customer(receiver_username);
          
          if (search_customer(sender_username).get_card_status() == 1)
          {
               throw out_of_range("Sender account is closed");
          }
          
          if (search_customer(receiver_username).get_card_status() == 1)
          {
               throw out_of_range("Receiver account is closed");
          }
          
          if (search_customer(sender_username).get_inventory() < money)
          {
               throw out_of_range("Your cant send this amount of balance");
          }
          
          search_customer(sender_username).decrease_money(money);
          search_customer(receiver_username).increase_money(money);

          search_customer(sender_username).add_to_history(history);
          search_customer(receiver_username).add_to_history(temp_history);
          this->bank_history.push_back(report);

          cout << "Done" << endl;
     }
     else if (money <= 0)
     {
          throw invalid_argument("Enter a valid balance");
     }
}

void Bank::withdraw(string username, string ip, unsigned long long int money)
{
     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }

     if (money > 0)
     {
          Time time;
     
          string temp_time = time.get_system_time();

          string history = "Withdrawed money at : " + temp_time;
          string temp_history = "a customer withdrawed his money at : " + temp_time;
        
          search_customer(username).check_ip(ip);

          if (search_customer(username).get_card_status() == 1)
          {
               throw out_of_range("Account is closed");
          }
          
          if (search_customer(username).get_inventory() < money)
          {
               throw invalid_argument("your balance is low");
          }

          if (get_bank_inventory() < money)
          {
               set_bank_status(Bank::Bank_Status::Broke);
               throw out_of_range("Bank is broke --> we cant pay your money");
          }
          
          search_customer(username).decrease_money(money);
          withdraw_money_from_inventory(money);

          search_customer(username).add_to_history(history);
          this->bank_history.push_back(temp_history);

          cout << "Done" << endl;
     }
     else if (money <= 0)
     {
          throw invalid_argument("Enter a valid balance");
     }
}

void Bank::add_money_to_inventory(unsigned long long int money)
{
     this->bank_inventory += money;
}

void Bank::withdraw_money_from_inventory(unsigned long long int money)
{
     this->bank_inventory -= money;
}

void Bank::renewal(string username, string ip)
{
     Time time;
     
     string temp_time = time.get_system_time();

     string history = "Renewal account at : " + temp_time;
     string temp_history = "Renewal a account at : " + temp_time;
     
     search_customer(username).check_ip(ip);
     
     if (search_customer(username).get_card_status() == 0)
     {
          throw out_of_range("your card is still open");
     }
     
     if (search_customer(username).get_inventory() < 50)
     {
          throw ("You dont have balance");
     }

     search_customer(username).decrease_money(50);
     search_customer(username).edit_expiration_date("1/1/2025");
     search_customer(username).set_card_status(Customer::Card_Status::Open);
     
     search_customer(username).add_to_history(history);
     this->bank_history.push_back(temp_history);

     cout << "Done" << endl;
}

void Bank::add_profits(string username)
{
     Time time;
     
     string temp_time = time.get_system_time();

     string history = "Profits aded at : " + temp_time;
     string temp_history = "Profits aded to an account at : " + temp_time;

     if (get_bank_status() == 1)
     {
          throw out_of_range("This bank is broken");
     }

     if (search_customer(username).get_card_status() == 1)
     {
          throw out_of_range("Account is closed");
     }
     
     if (search_customer(username).get_debt() == 0)
     {
          unsigned int money = search_customer(username).get_inventory();
          
          if (money <= 10000)
          {
               money /= 5;
          }
          
          if (money > 10000 && money <= 20000)
          {
               money /= 10;
          }
          
          if (money > 20000)
          {
               money /= 15;
          }
          
          search_customer(username).increase_money(money);
          withdraw_money_from_inventory(money);

          search_customer(username).add_to_history(history);
          this->bank_history.push_back(temp_history);
     
          cout << "Done" << endl;
     }
}

unsigned long long int Bank::get_bank_inventory()
{
     return bank_inventory;
}

unsigned long long int Bank::get_customers_debt()
{
     unsigned long long int sum = 0;

     for (size_t i = 0; i < customers.size(); i++)
     {
          sum += customers[i].get_debt();
     }

     return sum;
}

void Bank::show_bank_information()
{
     cout << "-----------------------"                         << endl;
     cout << "Bank Information       "                         << endl;
     cout << "****Professor Bank**** "                         << endl;
     cout << "Inventory :            " << get_bank_inventory() << endl;
     cout << "Customers Numbers :    " << customers.size()     << endl;
     cout << "Price of given loans : " << get_customers_debt() << endl;
     cout << "  "                                              << endl;
     cout << "History : "                                      << endl;
     for (size_t i = 0; i < bank_history.size(); i++)
     {
          cout << bank_history[i] << endl;
     }
     cout << "-----------------------"                         << endl;
}
#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Customer.hpp"

using namespace std;

vector<unsigned int> Customer::account_numbers;
vector<string> Customer::user_names;
vector<string> Customer::ip_lists;

Customer::Customer(string username, string ip)
{
     Time a;
     a.set_system_date();
     string temp = a.get_date();
     
     make_account_number();
     check_username(username);
     add_ip(ip);
     set_production_date(temp);
     
     string expiration_day = to_string(get_production_day());
     string expiration_month = to_string(get_production_month());
     string expiration_year = to_string(get_production_year() + 2);
     
     string expiration_date =  expiration_month + "/" + expiration_day + "/" + expiration_year;
     
     set_expiration_date(expiration_date);
}

Customer & Customer::check_ip(string ip)
{
     for (size_t i = 0; i < ip_list.size(); i++)
     {
          if (ip == ip_list[i])
          {
               return *this;
          }     
     }
     throw out_of_range("ip not found");
}

void Customer::set_username(string username)
{
     for (size_t i = 0; i < user_names.size(); i++)
     {
          if (user_names[i] == username)
          {
               throw invalid_argument("Username has been taken");
          }
     }
     this->user_names.push_back(username); 
     this->username = username;
}

void Customer::ip_validation(string ip)
{
     for (size_t i = 0; i < ip_lists.size(); i++)
     {
          if (ip_lists[i] == ip)
          {
               throw invalid_argument("Ip has been taken");
          }
     }
     this->ip_lists.push_back(ip);
}

void Customer::check_username(string username)
{
     bool found_num = false;
     bool found_upp = false;
     bool found_low = false;

     for(auto letter: username)
     {
          for(char ch = 'a'; ch <= 'z' && !found_low; ch++)
          {
               if(ch == letter)
               {
                    found_low = true;
               }
          }

          for(char ch = 'A'; ch <= 'Z' && !found_upp; ch++)
          {
               if(ch == letter)
               {
                    found_upp = true;
               }
          }

          for(char ch = '0'; ch <= '9' && !found_num; ch++)
          {
               if(ch == letter)
               {
                    found_num = true;
               }
          }
     }

     if(found_upp && found_low && found_num)
     {
          set_username(username);
     }
     else
     {
          throw invalid_argument("your username must contain an uppercase character & lowercase character & number");
     }
}

void Customer::set_account_number(unsigned int account_number)
{  
     this->account_number = account_number;
}

void Customer::make_account_number()
{
     unsigned int temp;
     bool found = false;

     srand(time(0));
          
     while(!found)
     {
          found = true;
          temp = rand() % 1000 + 1000;

          for (size_t i = 0; i < account_numbers.size(); i++)
          {
               if (account_numbers[i] == temp)
               {
                    found = false;
               }
          }
     }

     this->account_numbers.push_back(temp); 
     set_account_number(temp);
}

void Customer::add_ip(string ip)
{
     int pos1 = ip.find(".");
     int pos2 = ip.find(".", pos1 + 1);
     int pos3 = ip.find(".", pos2 + 1);
     int pos4 = ip.find(pos3 + 1);

     if ((pos2 == -1) || (pos3 == -1))
     {
          throw invalid_argument("your ip must contain 4 part");
     }
     
     string part1 = ip.substr(0, pos1);
     string part2 = ip.substr(pos1 + 1, (pos2 - pos1) - 1);
     string part3 = ip.substr(pos2 + 1, (pos3 - pos2) - 1);
     string part4 = ip.substr(pos3 + 1, (pos4 - pos3) - 1);

     
     if ((stoi(part1) < 0 || stoi(part1) > 255) || (stoi(part2) < 0 || stoi(part2) > 255) || (stoi(part3) < 0 || stoi(part3) > 255) || (stoi(part4) < 0 || stoi(part4) > 255))
     {
          throw out_of_range("your ip is invalid");
     }
     
     ip_validation(ip);
     this->ip_list.push_back(ip);
}

void Customer::set_production_date(string production_date)
{
     this->production_date = production_date;
}

void Customer::set_expiration_date(string expiration_date)
{    
     this->expiration_date = expiration_date;
}

void Customer::edit_expiration_date(string expiration_date)
{
     this->expiration_date = expiration_date;
}

void Customer::set_inventory(unsigned long long int inventory)
{    
     this->inventory = inventory;
}

void Customer::set_debt(unsigned long long int money)
{
     this->debt = money;
}

void Customer::increase_money(unsigned long long int money)
{
     inventory += money;
}

void Customer::decrease_money(unsigned long long int money)
{
     inventory -= money;
}

void Customer::increase_debt(unsigned long long int money)
{
     debt += money;
}

void Customer::decrease_debt(unsigned long long int money)
{
     debt -= money;
}

void Customer::set_card_status(Card_Status card_status)
{
     this->card_status = card_status;
}

void Customer::add_to_history(std::string history)
{
     this->history.push_back(history);     
}

string Customer::get_username() const
{
     return username;
}

string Customer::get_production_date()
{
     return production_date;
}

string Customer::get_expiration_date()
{
     return expiration_date;
}

unsigned int Customer::get_account_number() const
{
     return account_number;
}

unsigned long long int Customer::get_inventory() const
{
     return inventory;
}

unsigned long long int Customer::get_debt() const
{
     return debt;
}

int Customer::get_production_year()
{
     string time = get_production_date();

     int pos1 = time.find("/", 4);
     
     int pr_year = stoi(time.substr(pos1 + 1));
     
     return pr_year;
}

int Customer::get_production_month()
{
     string time = get_production_date();

     int pr_month = stoi(time.substr(0,2));
 
     return pr_month;
}

int Customer::get_production_day()
{
     string time = get_production_date();
    
     int pr_day = stoi(time.substr(3,6));
    
     return pr_day;
}

vector<string> Customer::get_ip_list() const
{
     return ip_list;
}

Customer::Card_Status Customer::get_card_status() const
{
     return card_status;
}

void Customer::show_information()
{
     cout << "-----------------"                           << endl;
     cout << "User Information"                            << endl;
     cout << "Username : "        << get_username()        << endl;
     cout << "Account Number : "  << get_account_number()  << endl;
     cout << "Inventory : "       << get_inventory()       << endl;
     cout << "Debt : "            << get_debt()            << endl;
     cout << " "                                           << endl; 
     cout << "IP LIST : "                                  << endl;
     for (size_t i = 0; i < ip_list.size(); i++)
     {
          cout << ip_list[i] << endl;
     }
     cout << " "                                           << endl;
     cout << "Production Date : " << get_production_date() << endl;
     cout << "Expiration Date : " << get_expiration_date() << endl;
     cout << " "                                           << endl;
     cout << "History : "                                  << endl;
     for (size_t i = 0; i < history.size(); i++)
     {
          cout << history[i] << endl;
     }
     cout << "-----------------"                           << endl;
}
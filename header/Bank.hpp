#ifndef BANK_HPP
#define BANK_HPP

#include "Customer.hpp"
#include "Time.hpp"

#include <string>
#include <vector>

class Bank
{    
     public:  
          //enum
          enum Bank_Status{Normal, Broke};

          Bank();
          
          //set and get fucntions
          Customer & search_customer(std::string); // baraye peyda kardan yek customer ba username
          Customer & search_customer(unsigned int); // baraye peyda kardan ye customer ba account number
          
          void add_customer(Customer); // ezafe kardan yek moshtari
          void add_money_to_inventory(unsigned long long int); // tayeen meghdar bodjeye bank
          void withdraw_money_from_inventory(unsigned long long int); // baraye bardasht az hesab bank 
          void renewal(std::string, std::string); // tamdid kardan tarikh yek card banki
          void add_profits(std::string); // ezafe kardan sood banki
          void get_loan(std::string, std::string, unsigned long long int); // gereftan vam
          void pay_loan(std::string, unsigned long long int); // pardakht vam
          void deposit(std::string, std::string, unsigned long long int); // variz pool
          void transfer(std::string, std::string, std::string, unsigned long long int); // enteghal pool
          void withdraw(std::string, std::string, unsigned long long int); // bardasht pool az hesab customer
        
          unsigned long long int get_bank_inventory(); // gereftan meghdar pool mojodd dar bank
          unsigned long long int get_customers_debt(); // gereftan meghdar bedehi hameye customer ha

          void set_bank_status(Bank_Status); // jahat set kardan vaziyat bank 
          Bank_Status get_bank_status(); // jahat gereftan vaziyat bank

          void show_bank_information(); // baraye namayesh etelaat bank
     private:
          //data members
          std::vector<Customer> customers; // list tamam moshtari ha
          unsigned long long int bank_inventory = 0; // bodgeye bank
          Bank_Status bank_status = Normal; // vaziyat bank
          std::vector<std::string> bank_history; // history hameye etefaghat
};

#endif
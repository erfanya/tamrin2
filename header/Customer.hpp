#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "Time.hpp"

#include <string>
#include <vector>

class Customer
{
     public:
          //enum
          enum Card_Status{Open, Closed};        
          
          //constructor
          Customer(std::string username, std::string ip); 

          //set and get fucntions
          Customer & check_ip(std::string); // check kardan ip 

          void set_username(std::string); // set kardan username
          void set_account_number(unsigned int); // set kardan accout number
          void set_production_date(std::string); // set kardan tarikh sakht
          void set_expiration_date(std::string); // set kardan tarikh engheza
          void set_inventory(unsigned long long int); // set kardan meghdar pool mojod dar hesab
          void set_debt(unsigned long long int); // set kardan meghad vam gerefte shode
          void increase_money(unsigned long long int); // ezafe kardan pool
          void decrease_money(unsigned long long int); // kam kardan pool
          void increase_debt(unsigned long long int); // ezafe kardan bedehi
          void decrease_debt(unsigned long long int); // kam kardan bedehi
          void add_ip(std::string); // ezafe kardan ip
          void set_card_status(Card_Status); // set kardan vaziyat hesab
          void edit_expiration_date(std::string); // taghir dadan tarikh engheza
          void make_account_number(); // tolid account number random
          void check_username(std::string); // check kardan username
          void add_to_history(std::string); // ezafe kardan be tarikhche hesab
          void ip_validation(std::string); // check kardan mojod boodan ip

          std::string get_username() const; // gereftan username
          unsigned int get_account_number() const; // gereftan account number 
          std::string get_production_date(); // gereftan tarikh sakht
          std::string get_expiration_date(); // gereftan tarikht engheza
          unsigned long long int get_inventory() const; // gereftan meghdar pool mojod
          unsigned long long int get_debt() const; // gereftan meghdar bedehi
          int get_production_year(); // gereftan sal sakht
          int get_production_month(); // gereftan mah sakht
          int get_production_day(); // gereftan rooz sakht
          std::vector<std::string> get_ip_list() const; // gereftan list ip haye sabt shode baraye in karbar
          Card_Status get_card_status() const; // gereftan vaziyat hesab
          
          void show_information(); // namayesh etelaat
     private:
          //data members
          std::string username; // username karbar 
          unsigned int account_number; // shomare hesab 
          std::string production_date; // tarikh sakht set by default "mm/dd/yyyy"
          std::string expiration_date; // tarikht engheza set by default "mm/dd/yyyy"
          unsigned long long int inventory = 0; // mojodi hesab
          unsigned long long int debt = 0; // meghdar vam gerefte shode
          Card_Status card_status = Open; // vaziyat hesab
          std::vector<std::string> ip_list; //ip haye mojaz baraye dastresi be hesab
          std::vector<std::string> history; // baraye save kardan tarikhche hesab 
          static std::vector<unsigned int> account_numbers; // vectori az tamami account number haye sakhte shode
          static std::vector<std::string> user_names; // vectori az tamami username haye sakhte shode
          static std::vector<std::string> ip_lists; // baraye sabt hameye ip haye mojod dar bank
};

#endif
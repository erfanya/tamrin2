#include <iostream>
#include <string>
#include <vector>

#include "Customer.hpp"
#include "Bank.hpp"

using namespace std;

void help()
{
     cout <<  "-------------------------------------------------------------------------------------------------------------------------" << endl;
     cout <<  "-create         ---> example : create          (username):(ip) *(username must contain a uppercase & lowercase & number) " << endl;
     cout <<  "-add_ip         ---> example : add_ip          (username):(new_ip)                                                       " << endl;
     cout <<  "-renewal        ---> example : renewal         (username):(ip)                                                           " << endl;
     cout <<  "-deposit        ---> example : deposit         (username):(ip):(money)                                                   " << endl;
     cout <<  "-transfer       ---> example : transfer        (sender_username):(sender_ip):(receiver_username):(money)                 " << endl;
     cout <<  "-withdraw       ---> example : withdraw        (username):(ip):(money)                                                   " << endl;
     cout <<  "-add_profits    ---> example : add_profits     (username)                                                                " << endl;
     cout <<  "-get_loan       ---> example : get_loan        (username):(ip):(money)                                                   " << endl;
     cout <<  "-pay_loan       ---> example : pay_loan        (username):(money)                                                        " << endl;
     cout <<  "-username       ---> example : username       *(for showing information with username)                                   " << endl;
     cout <<  "-account_number ---> example : account_number *(for showing information with account_number)                             " << endl;
     cout <<  "-bank           ---> example : bank           *(for showing information of bank)                                         " << endl;
     cout <<  "-------------------------------------------------------------------------------------------------------------------------" << endl;
}

int main()
{
     system("clear");
     help();
     Bank bank;
     
     while (1)
     {
          try
          {         
               string command;
               getline(cin, command);

               if ((command == "create") || (command == "add_ip") || (command == "renewal") || (command == "deposit") || (command == "transfer") || (command == "add_profits") || (command == "get_loan") || (command == "pay_loan") || (command == "withdraw"))
               {
                    throw invalid_argument("invalid argument -- type help for mor information");
               }
               
               string check = command.substr(0, command.find(" "));
          
               for (size_t i = 0; i < check.length(); i++)
               {
                    check[i] = tolower(check[i]);
               }
               
               if (check == "create")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(" ", pos2 + 1);

                    string username = command.substr(pos1, pos2 - pos1);
                    
                    username.erase(0,1);

                    string ip = command.substr(pos2 + 1, pos3 - pos2);

                    Customer customer(username, ip);
                    
                    bank.add_customer(customer);
               }

               if (check == "add_ip")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(" ", pos2 + 1);

                    string username = command.substr(pos1, pos2 - pos1);

                    username.erase(0,1);

                    string ip = command.substr(pos2 + 1, pos3 - pos2);

                    bank.search_customer(username).add_ip(ip);
               }

               if (check == "renewal")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(" ", pos2 + 1);

                    string username = command.substr(pos1, pos2 - pos1);

                    username.erase(0,1);

                    string ip = command.substr(pos2 + 1, pos3 - pos2);
               
                    bank.renewal(username, ip);
               }

               if (check == "deposit")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(":", pos2 + 1);
                    int pos4 = command.find(" ", pos3 + 1);

                    string username = command.substr(pos1, pos2 - pos1);
                    
                    username.erase(0,1);

                    string ip = command.substr(pos2 +1, (pos3 - pos2) - 1);
                    unsigned long long int money = stoi(command.substr(pos3 + 1));

                    bank.deposit(username, ip, money);               
               }

               if (check == "transfer")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(":", pos2 + 1);
                    int pos4 = command.find(":", pos3 + 1);
                    int pos5 = command.find(" ", pos4 + 1);
                    
                    string sender_username = command.substr(pos1, pos2 - pos1);
                    
                    sender_username.erase(0,1);
                    
                    string sender_ip = command.substr(pos2 + 1, (pos3 - pos2) - 1);
                    string receiver_username = command.substr(pos3 + 1, (pos4 - pos3) - 1);
                    unsigned long long int money = stoi(command.substr(pos4 +  1, (pos5 - pos4) - 1));

                    bank.transfer(sender_username, sender_ip, receiver_username, money);
               }

               if (check == "withdraw")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(":", pos2 + 1);
                    int pos4 = command.find(" ", pos3 + 1);

                    string username = command.substr(pos1, pos2 - pos1);

                    username.erase(0,1);

                    string ip = command.substr(pos2 +1, (pos3 - pos2) - 1);
                    unsigned long long int money = stoi(command.substr(pos3 + 1));

                    bank.withdraw(username, ip, money);
               }
               
               if (check == "add_profits")
               {
                    int pos = command.find(" ");
                    
                    string username = command.substr(pos);

                    username.erase(0,1);
                    
                    bank.add_profits(username);
               }

               if (check == "get_loan")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(":", pos2 + 1);
                    int pos4 = command.find(" ", pos3 + 1);

                    string username = command.substr(pos1, pos2 - pos1);

                    username.erase(0,1);

                    string ip = command.substr(pos2 +1, (pos3 - pos2) - 1);
                    unsigned long long int money = stoi(command.substr(pos3 + 1));
                    
                    bank.get_loan(username, ip, money);
               }

               if (check == "pay_loan")
               {
                    int pos1 = command.find(" ");
                    int pos2 = command.find(":", pos1 + 1);
                    int pos3 = command.find(" ", pos2 + 1);

                    string username = command.substr(pos1, pos2 - pos1);

                    username.erase(0,1);

                    unsigned long long int money = stoi(command.substr(pos2 + 1));

                    bank.pay_loan(username, money);
               }
               
               if (check == "username")
               {
                    string username;

                    cout << "Enter your username to see your information : ";
                    cin >> username;
                    
                    system("clear");
                    bank.search_customer(username).show_information();
               }

               if (check == "account_number")
               {
                    unsigned int account_number;
                    
                    cout << "Enter your account_number to see your information : ";
                    cin >> account_number;
                    
                    system("clear");
                    bank.search_customer(account_number).show_information();
               }

               if (check == "bank")
               {
                    system("clear");
                    bank.show_bank_information();
               }

               if (check == "help")
               {
                    system("clear");
                    help();
               }
               
               if (check == "exit")
               {
                    break;
               }
          }
          catch(const std::exception& e)
          {
               std::cerr << e.what() << endl;
          }
     
     }
     
     return 0;
}
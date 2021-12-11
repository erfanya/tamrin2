#include <iostream>
#include <string>

#include "Time.hpp"

using namespace std; 

void Time::set_system_date()
{
     string time = get_system_time();
     
     int pos1 = time.find(" ");
     int pos2 = time.find(" ", pos1 + 1);
     int pos3 = time.find(" ", pos2);
     int pos4 = time.find(" ", pos3 + 1);

     string month = time.substr(pos1, (pos2 - pos1));
     month.erase(0,1);

     int temp_month;
     
     if (month == "Jan")
     {
          temp_month = 1;
     }
     
     if (month == "Mar")
     {
          temp_month = 3;
     }
     
     if (month == "Apr")
     {
          temp_month = 4;
     }
     
     if (month == "May")
     {
          temp_month = 5;
     }
     
     if (month == "June")
     {
          temp_month = 6;
     }
     
     if (month == "July")
     {
          temp_month = 7;
     }
     
     if (month == "Aug")
     {
          temp_month = 8;
     }
     
     if (month == "Sep")
     {
          temp_month = 9;
     }

     if (month == "Oct")
     {
          temp_month = 10;
     }
     
     if (month == "Nov")
     {
          temp_month = 11;
     }
     
     if (month == "Dec")
     {
          temp_month = 12;
     }
     
     string day;

     if (pos4 == 8)
     {
          day = stoi(time.substr(pos3 + 1, (pos4+2) -pos3));    
     }
     else if (pos4 == 10)
     {    
          day = time.substr(pos3+1, 2);
     }
  
     int year = stoi(time.substr(19, 25));

     this->day = stoi(day);
     this->year = year;
     this->month = temp_month;   
}

string Time::get_system_time() 
{
     string time;
     int size = 25;

     time_t end_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
     char* dd = ctime(&end_time);
     
     time.assign(dd, size);
    
     return time;
}

string Time::get_date() 
{
     return (to_string(month)  + "/" + to_string(day)  + "/" + to_string(year));
}
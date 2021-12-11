#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <string>
#include <ctime>

class Time
{
     public:

          void set_system_date(); // set kardan time system ba format mm/dd/yyyy
          std::string get_date(); // gereftan time system ba format mm/dd/yyyy
          std::string get_system_time(); // // gereftan time konooni system
          
     private:
          int day; // rooz
          int year; // sal
          int month; // mah
};

#endif
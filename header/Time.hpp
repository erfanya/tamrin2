#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <string>
#include <ctime>

class Time
{
     public:

          void set_system_date(); // set kardan time system ba format mm/dd/yyyy
          std::string get_date() const; // gereftan time system ba format mm/dd/yyyy
          std::string get_system_time() const; // // gereftan time konooni system
          
     private:
          int year; // sal
          int month; // mah
          int day; // rooz
};

#endif

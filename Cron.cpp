#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>

struct tmp_time
{
    unsigned int time = 0;
    unsigned int period = 1;
};

tmp_time extractNumeric(const std::string& c_strTask)
{
    tmp_time ext_time;
    try
    {
        if((c_strTask.at(0) == '*') && (c_strTask.at(1) == '/'))
        {
            std::string newStringforInt = c_strTask.substr(2);
            ext_time.period = boost::lexical_cast<unsigned>(newStringforInt);
            return ext_time;
        }
        if(c_strTask.at(0) == '*' && c_strTask.size() == 1)
        {
            return ext_time;
        }
        ext_time.time = boost::lexical_cast<unsigned>(c_strTask);
        return ext_time;
    }
    catch(const boost::bad_lexical_cast&)
    { std::cout << "Error in type casting string -> int" << std::endl;}
}

struct timeTask
{
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int min_period;
    unsigned int hour_period;
    unsigned int day_period;
    timeTask():
        minute(0),
        hour(0),
        day(0),
        min_period(1),
        hour_period(1),
        day_period(1)
    {}
};

class Task
{
public:
    timeTask t_time;
    std::string cmd_comand;
private:
   unsigned int extractMinutesVal(const std::string &c_strTask)
   {
       tmp_time ext_time = extractNumeric(c_strTask);
       t_time.minute = ext_time.time;
       t_time.min_period = ext_time.period;
   }
   int extractHoursVal(const std::string &c_strTask)
   {
       tmp_time ext_time = extractNumeric(c_strTask);
       t_time.hour = ext_time.time;
       t_time.hour_period = ext_time.period;
   }
   int extractDaysVal(const std::string &c_strTask)
   {
       tmp_time ext_time = extractNumeric(c_strTask);
       t_time.day = ext_time.time;
       t_time.day_period = ext_time.period;
   }
};

int main()
{
    std::fstream in_file("/home/petr/cronDeamon/IN.txt");

    using vec_str = std::vector<std::string>;

    std::string tmp_string;
    vec_str tmp;

    while(std::getline(in_file, tmp_string, ' '))
    {
        if(tmp_string[0])
        {
            //Тут нужна проверка символ перевода
            //коретки на следующую строку, под Linux
            //Не понятно как делать,это необходимо для считывания
            //только одной строки для cron демона
            tmp.push_back(tmp_string);
        }
    }

    if(tmp.size() != 4)
    {
        std::cout << "Error, not the right format\n"
                  << "Right format is: '* * * /script or 12 */2 * /script'"
                  << std::endl;

    }

    for(unsigned int i = 0; i <= tmp.size(); ++i)
    {
        std::cout << tmp[i]<< std::endl;
    }
    
    return 0;
}
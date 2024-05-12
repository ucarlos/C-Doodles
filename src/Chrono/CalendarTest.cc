/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 03/01/2024 at 08:50 PM
 *
 * CalendarTest.cc
 *
 * -----------------------------------------------------------------------------
 */

#include <ctime>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdint>

using namespace std;

bool is_leap_year(int32_t year) {
    if (!(year % 100))
        return !(year % 400);
    else
        return !(year % 4);
}

bool verify_date_string(int32_t year,
                        uint32_t month,
                        uint32_t day,
                        uint32_t hour = 0,
                        uint32_t minute = 0,
                        uint32_t second = 0) {
    if (year < 0)
        return false;

    if (!(1 <= month && month <= 12))
        return false;

    if (!(0 <= hour && hour <= 23) || !(0 <= minute && minute <= 59) || !(0 <= second && second <= 59))
        return false;
    
    // Now determine if the date is valid or not:
    const int normal_year_month_day_list[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int leap_year_month_day_list[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (is_leap_year(year))
        return (1 <= day && day <= leap_year_month_day_list[month - 1]);
    else
        return (1 <= day && day <= normal_year_month_day_list[month - 1]);
}


/**
 * Generate a chrono::time_point time object given a year, month, day and optional
 * hour, minute, and second values.
 * @param year
 * @param month
 * @param day
 * @param hour
 * @param minute
 * @param second
 * @return an valid time_point if it passes validation; An default time_point object otherwise.
 */
std::chrono::time_point<std::chrono::system_clock> generate_date_object(int32_t year,
                                                                        uint32_t month,
                                                                        uint32_t day,
                                                                        uint32_t hour = 0,
                                                                        uint32_t minute = 0,
                                                                        uint32_t second = 0) {
    if (!verify_date_string(year, month, day)) {
		// Return a default time_point object instead of null or an exception
        return std::chrono::time_point<std::chrono::system_clock> {};
	}

    stringstream format_stringstream;
    format_stringstream << year << "-" << month << "-" << day << " " << hour << ":" << minute << ":" << second;

    std::tm time_struct{};
    format_stringstream >> std::get_time(&time_struct, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&time_struct));
}

int main() {
    std::chrono::time_point<std::chrono::system_clock> current_time_point = std::chrono::system_clock::now();
    
    std::time_t start_time = std::chrono::system_clock::to_time_t(current_time_point);
    cout << "Current System Time is " << std::ctime(&start_time);

    current_time_point += std::chrono::hours(12);
    start_time = std::chrono::system_clock::to_time_t(current_time_point);
    // Now incrementing the time
    cout << "After incrementing the time by 12 hours, the new time is " << std::ctime(&start_time) << "\n";

    // Now attempt to generate a date_object:
    std::chrono::time_point<std::chrono::system_clock> birthday_object = generate_date_object(2024, 2, 15);
    if (birthday_object.time_since_epoch() == std::chrono::seconds(0)) {
        cerr << "Error: Something wrong happened while creating the date object!\n";
    }
    else {
        // Set the birthday to 10:05 PM
        birthday_object += std::chrono::hours(22);
        birthday_object += std::chrono::minutes(5);

        std::time_t birthday_timet_object = std::chrono::system_clock::to_time_t(birthday_object);
        // Annoying bullshit to change the Www Mmm dd hh:mm:ss yyyy format
        const int c_string_length = 100;
        char birthday_c_string[c_string_length];
        std::strftime(birthday_c_string, c_string_length, "%a %B %0d %H:%M:%S %Y", std::localtime(&birthday_timet_object));

        // Subtracting two time_points leads to a duration object which has to be cast to days:
        auto difference = current_time_point - birthday_object;
	    auto difference_in_days= std::chrono::duration_cast<std::chrono::days>(difference);
        auto difference_in_months = std::chrono::duration_cast<std::chrono::minutes>(difference);

        std::cout << "My Birthday was on " << birthday_c_string << ", which was "
				  << difference_in_days.count() << " days ago ("
				  << difference_in_months.count() << " minutes ago)\n";

    }
}

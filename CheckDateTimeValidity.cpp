

void CheckDateTimeValidity(const DateTime& dt) {
   
    CheckValidity(dt.year, 1, 9999, "year");
    CheckValidity(dt.month, 1, 12, "month");

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    CheckValidity(dt.day, 1, month_lengths[dt.month - 1], "day");
    CheckValidity(dt.hour, 0, 23, "hour");
    CheckValidity(dt.minute, 0, 59, "minute");
    CheckValidity(dt.second, 0, 59, "second");

}

void CheckValidity(int given_time, int standart_time_min, int standart_time_max, std::string time)
{
    if (given_time < standart_time_min) {
        throw domain_error(time + "is too small");
    }
    if (given_time > standart_time_max) {
        throw domain_error(time + "is too big");
    }
}

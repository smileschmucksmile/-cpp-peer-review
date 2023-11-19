
struct DBData {
    std::string_view db_name;
    bool db_allow_exceptions;
    int db_connection_timeout;
    DBLogLevel db_log_level;
};

struct Age {
    int max_age;
    int min_age;
};

vector<Person> LoadPersons(DBData db_data, Age age, std::string_view name_filter) 
{
    DBConnector connector(db_data.db_allow_exceptions, db_data.db_log_level);
    DBHandler db;
    if (db_data.db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_data.db_name, db_data.db_connection_timeout);
    }
    else {
        db = connector.Connect(db_data.db_name, db_data.db_connection_timeout);
    }
    if (!db_data.db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    std::vector<Person> persons;
    DBQuery query = GetQueryString(age, name_filter, db);
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}

DBQuery GetQueryString(Age age, std::string_view name_filter, DBHandler& db)
{
    std::ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << Age.min_age << " and "s << Age.max_age << " "s
        << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());
    return query;
}

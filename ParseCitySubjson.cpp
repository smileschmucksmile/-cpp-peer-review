using namespace std;
struct Country {
    string country_name;
    string country_iso_code;
    string country_phone_code;
    string country_time_zone;
    vector<Language> languages;
};


// Äàíà ôóíêöèÿ ParseCitySubjson, îáðàáàòûâàþùàÿ JSON-îáúåêò ñî ñïèñêîì ãîðîäîâ êîíêðåòíîé ñòðàíû:
void ParseCitySubjson(vector<City>& cities, const Json& json, Country data) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({ city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          data.country_phone_code + data.city_obj["phone_code"s].AsString(),
            data.country_name, data.country_iso_code, data.country_time_zone, data.languages });
    }
}

// ParseCitySubjson âûçûâàåòñÿ òîëüêî èç ôóíêöèè ParseCountryJson ñëåäóþùèì îáðàçîì:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
            });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(cities, country_obj["cities"s], country);
    }
}

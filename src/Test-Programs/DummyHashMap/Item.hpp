/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 09/21/2024 at 10:54 PM
 *
 * Item.hpp
 *
 * -----------------------------------------------------------------------------
 */

#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include <ostream>


/**
 * Simple class to represent a Item with a key name, preference value, and enterprise name.  
 */
class Item {
public:
    Item() =default;

    explicit Item(const std::string &key_name)  : _key_name{key_name} { } 
    
    Item(const std::string &key_name, const std::string &preference_value) {
        this->_key_name = key_name;
        this->_preference_value = preference_value;
    }

    Item(const std::string &key_name, const std::string &preference_value, const std::string &enterprise_name) {
        this->_key_name = key_name;
        this->_preference_value = preference_value;
        this->_enterprise_name = enterprise_name;
    }
    

    std::string get_key_name() { return this->_key_name; }
    std::string get_preference_value() { return this->_preference_value; }
    std::string get_enterprise_name() { return this->_enterprise_name; }


    void set_preference_value(const std::string &preference_value) { this->_preference_value = preference_value; }
    void set_enterprise_name(const std::string &enterprise_name) { this->_enterprise_name = enterprise_name; }

    // NOTE TO SELF: You can only have one operator==
    friend bool operator==(const Item &item1, const Item &item2);


private:
    std::string _key_name{"default.key.name"};
    std::string _preference_value{"0"};
    std::string _enterprise_name{"Default Enterprise"};
};

bool operator==(const Item &item1, const Item &item2) {
    return (item1._key_name == item2._key_name)
    && (item1._preference_value == item2._preference_value)
    && (item1._enterprise_name == item2._enterprise_name);
}


#endif

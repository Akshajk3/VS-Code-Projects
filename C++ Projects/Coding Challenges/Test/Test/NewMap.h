//
//  newMap.h
//  homework1_cs32
//
//  Created by Kashyap Kanumuri on 1/24/24.
//

#ifndef newMap_h
#define newMap_h

#include <string>

using KeyType =  std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 150;

class Map
{
  public:
    Map();         // Create an empty map (i.e., one whose size() is 0).
    Map(int s);
    Map(const Map& other);
    Map& operator=(const Map& other);
    ~Map();
    bool empty() const;  // Return true if the map is empty, otherwise false.
    int size() const;    // Return the number of key/value pairs in the map.
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
private:
    struct KeyValPair {
        KeyType m_key;
        ValueType m_value;
    };
    KeyValPair* pairs;
    int m_size;
    int max;

};

#endif /* newMap_h */

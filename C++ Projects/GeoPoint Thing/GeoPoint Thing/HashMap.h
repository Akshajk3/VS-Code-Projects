//
//  HashMap.h
//  project4
//
//  Created by Kashyap Kanumuri on 3/11/24.
//

#ifndef HashMap_h
#define HashMap_h

//#include <iostream>
//#include <string>
//#include <list>
//#include <functional>
//
//template <typename T>
//class HashMap {
//private:
//    struct HashNode {
//        std::string key;
//        T value;
//    };
//
//    std::list<HashNode>* table;
//    size_t capacity;
//    size_t size;
//    double maxLoadFactor;
//
//    size_t hash(const std::string& key) const {
//        std::hash<std::string> hasher;
//        return hasher(key) % capacity;
//    }
//
//    void expandAndRehash() {
//        size_t newCapacity = capacity * 2;
//        std::list<HashNode>* newTable = new std::list<HashNode>[newCapacity];
//
//        for (size_t i = 0; i < capacity; ++i) {
//            for (const auto& node : table[i]) {
//                size_t newIndex = hash(node.key);
//                newTable[newIndex].push_back(node);
//            }
//        }
//
//        delete[] table;
//        table = newTable;
//        capacity = newCapacity;
//    }
//
//public:
//    HashMap(double max_load = 0.75) : capacity(10), size(0), maxLoadFactor(max_load) {
//        table = new std::list<HashNode>[capacity];
//    }
//
//    ~HashMap() {
//        delete[] table;
//    }
//
//    int getSize() const {
//        return size;
//    }
//
//    void insert(const std::string& key, const T& value) {
//        size_t index = hash(key);
//        for (auto& node : table[index]) {
//            if (node.key == key) {
//                node.value = value; // Update existing value
//                return;
//            }
//        }
//        table[index].push_back({key, value});
//        ++size;
//
//        if (static_cast<double>(size) / capacity > maxLoadFactor) {
//            expandAndRehash();
//        }
//    }
//
//    T& operator[](const std::string& key) {
//        size_t index = hash(key);
//        for (auto& node : table[index]) {
//            if (node.key == key) {
//                return node.value; // Return existing value
//            }
//        }
//        // If key not found, insert with default value
//        insert(key, T());
//        return table[index].back().value;
//    }
//
//    const T* find(const std::string& key) const {
//        size_t index = hash(key);
//        for (const auto& node : table[index]) {
//            if (node.key == key) {
//                return &node.value; // Return pointer to value
//            }
//        }
//        return nullptr; // Key not found
//    }
//
//    T* find(const std::string& key) {
//        const auto& hm = *this;
//        return const_cast<T*>(hm.find(key));
//    }
//};
//----------------------------------------------------------
//#include <iostream>
//#include <vector>
//#include <list>
//#include <string>
//#include <functional>
//
//template <typename T>
//class HashMap {
//private:
//    struct HashNode {
//        std::string key;
//        T value;
//    };
//
//    std::vector<std::list<HashNode>> table;
//    size_t capacity;
//    size_t size;
//    double maxLoadFactor;
//
//    size_t hash(const std::string& key) const {
//        std::hash<std::string> hasher;
//        return hasher(key) % capacity;
//    }
//
//    void expandAndRehash() {
//        size_t newCapacity = capacity * 2;
//        std::vector<std::list<HashNode>> newTable(newCapacity);
//
//        for (size_t i = 0; i < capacity; ++i) {
//            for (const auto& node : table[i]) {
//                size_t newIndex = hash(node.key);
//                newTable[newIndex].push_back(node);
//            }
//        }
//
//        table = std::move(newTable);
//        capacity = newCapacity;
//    }
//
//public:
//    HashMap(double max_load = 0.75) : capacity(10), size(0), maxLoadFactor(max_load) {
//        table.resize(capacity);
//    }
//
//    ~HashMap() = default;
//
//    int getSize() const {
//        return size;
//    }
//
//    void insert(const std::string& key, const T& value) {
//        size_t index = hash(key);
//        for (auto& node : table[index]) {
//            if (node.key == key) {
//                node.value = value; // Update existing value
//                return;
//            }
//        }
//        table[index].push_back({key, value});
//        ++size;
//
//        if (static_cast<double>(size) / capacity > maxLoadFactor) {
//            expandAndRehash();
//        }
//    }
//
//    T& operator[](const std::string& key) {
//        size_t index = hash(key);
//        for (auto& node : table[index]) {
//            if (node.key == key) {
//                return node.value; // Return existing value
//            }
//        }
//        // If key not found, insert with default value
//        insert(key, T());
//        return table[index].back().value;
//    }
//
//    const T* find(const std::string& key) const {
//        size_t index = hash(key);
//        for (const auto& node : table[index]) {
//            if (node.key == key) {
//                return &node.value; // Return pointer to value
//            }
//        }
//        return nullptr; // Key not found
//    }
//
//    T* find(const std::string& key) {
//        const auto& hm = *this;
//        return const_cast<T*>(hm.find(key));
//    }
//};

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>

template <typename T>
class HashMap {
private:
    struct HashNode {
        std::string key;
        T value;
    };

    std::vector<std::list<HashNode>> table;
    unsigned int capacity;
    unsigned int size;
    double maxLoadFactor;

    unsigned int hash(const std::string& key) const {
        std::hash<std::string> hasher;
        return hasher(key) % capacity;
    }

    void expandAndRehash() {
        unsigned int newCapacity = capacity * 2;
        std::vector<std::list<HashNode>> newTable(newCapacity);

        for (unsigned int i = 0; i < capacity; ++i) {
            for (const auto& node : table[i]) {
                unsigned int newIndex = hash(node.key);
                newTable[newIndex].push_back(node);
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    HashMap(double max_load = 0.75) : capacity(10), size(0), maxLoadFactor(max_load) {
        table.resize(capacity);
    }

    ~HashMap() = default;

    int getSize() const {
        return size;
    }

    void insert(const std::string& key, const T& value) {
        unsigned int index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value; // Update existing value
                return;
            }
        }
        table[index].push_back({key, value});
        ++size;

        if (static_cast<double>(size) / capacity > maxLoadFactor) {
            expandAndRehash();
        }
    }

    T& operator[](const std::string& key) {
        unsigned int index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                return node.value; // Return existing value
            }
        }
        // If key not found, insert with default value
        insert(key, T());
        return table[index].back().value;
    }

    const T* find(const std::string& key) const {
        unsigned int index = hash(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                return &(node.value); // Return pointer to value
            }
        }
        return nullptr; // Key not found
    }

    T* find(const std::string& key) {
        const auto& hm = *this;
        return const_cast<T*>(hm.find(key));
    }
};

#endif /* HashMap_h */

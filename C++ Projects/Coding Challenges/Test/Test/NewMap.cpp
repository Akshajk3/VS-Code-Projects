
//
//  newMap.cpp
//  homework1_cs32
//
//  Created by Kashyap Kanumuri on 1/24/24.
//

#include "newMap.h"

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>

Map::Map(){
    m_size = 0;
    max = DEFAULT_MAX_ITEMS;
    pairs = new KeyValPair[DEFAULT_MAX_ITEMS];
}

Map::Map(int s){
    m_size = 0;
    pairs = new KeyValPair[s];
    max = s;
}

Map::Map(const Map& other){
    m_size = other.size();
    max = other.max;
    pairs = new KeyValPair[max];
    for(int i = 0; i < other.size(); i++){
        pairs[i] = other.pairs[i];
    }
}

Map& Map::operator=(const Map& other){
    if (this != &other) {
        delete[] pairs;
        m_size = other.size();
        max = other.max;
        pairs = new KeyValPair[max];
        for(int i = 0; i < other.size(); i++){
            pairs[i] = other.pairs[i];
        }
    }
    return *this;
}

Map::~Map(){
    delete[] pairs;
}

bool Map::empty() const{
    if(m_size == 0){
        return true;
    }
    else{
        return false;
    }
}

int Map::size() const{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value){
    if(!contains(key) && m_size < DEFAULT_MAX_ITEMS){
        KeyValPair newPair;
        newPair.m_key = key;
        newPair.m_value = value;
        pairs[m_size] = newPair;
        m_size++;
        return true;
    }
    return false;
}
bool Map::update(const KeyType& key, const ValueType& value){
    if(!contains(key)){
        return false;
    }
    else{
        for(int i = 0; i < m_size; i++){
            if(pairs[i].m_key == key){
                pairs[i].m_value = value;
            }
        }
        return true;
    }
   
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if(insert(key, value)){
        return true;
    }
    else if(update(key, value)){
        return true;
    }
    else{
        return false;
    }
}
bool Map::erase(const KeyType& key){

    int index = -1;
    for(int i = 0; i < m_size; i++){
        if(pairs[i].m_key == key){
            index = i;
        }
    }
    
    if(index == -1){
        return false;
    }
    else{
        for(int j = index; j < m_size - 1; j++){
            pairs[j].m_key = pairs[j+1].m_key;
            pairs[j].m_value = pairs[j+1].m_value;
        }
        m_size--;
        return true;
    }
    
}
bool Map::contains(const KeyType& key) const{
    for(int i = 0; i < m_size; i++){
        if(pairs[i].m_key == key){
            return true;
        }
    }
    return false;
}
bool Map::get(const KeyType& key, ValueType& value) const{

    for(int i = 0; i < m_size; i++){
        if(pairs[i].m_key == key){
            value = pairs[i].m_value;
            return true;
        }
    }
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const {

    if(0 <= i && i < m_size){
        key = pairs[i].m_key;
        value = pairs[i].m_value;
        return true;
    }
    else{
        return false;
    }
}
void Map::swap(Map& other){
    
    std::swap(pairs, other.pairs);
    std::swap(max, other.max);
    std::swap(m_size, other.m_size);
    

}

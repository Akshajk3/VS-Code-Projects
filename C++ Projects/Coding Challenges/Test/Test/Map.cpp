#include <stdio.h>
#include "Map.h"

OldMap::OldMap()
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        keys[i] = defaultKey;
        values[i] = defaultValue;
    }
}

bool OldMap::empty() const
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(keys[i] != defaultKey)
        {
            return false;
        }
    }
    
    return true;
}

int OldMap::size() const
{
    int counter = 0;
    
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(keys[i] != defaultKey || values[i] != defaultValue)
        {
            counter++;
        }
    }
        
    return counter;
}

bool OldMap::insert(const KeyType& key, const ValueType& value)
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if (keys[i] == key)
        {
            return false;
        }
        
        if (keys[i] == defaultKey)
        {
            keys[i] = key;
            values[i] = value;
            return true;
        }
    }
    
    return false;
}

bool OldMap::update(const KeyType& key, const ValueType& value)
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(key == keys[i])
        {
            values[i] = value;
            return true;
        }
    }
    
    return false;
}

bool OldMap::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if (key == keys[i])
        {
            values[i] = value;
            return true;
        }
        else
        {
            if(keys[i] == defaultKey)
            {
                keys[i] = key;
                values[i] = value;
                return true;
            }
        }
    }
    
    return false;
}

bool OldMap::erase(const KeyType& key)
{
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(key == keys[i])
        {
            keys[i] = defaultKey;
            values[i] = defaultValue;
            return true;
        }
    }
    
    return false;
}
 
bool OldMap::contains(const KeyType& key) const
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(key == keys[i])
        {
            return true;
        }
    }
    
    return false;
}
 
bool OldMap::get(const KeyType& key, ValueType& value)
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(key == keys[i])
        {
            values[i] = value;
            return true;
        }
    }
    
    return false;
}
 
bool OldMap::get(int i, KeyType& key, ValueType& value)
{
    if( 0 <= i && i < size())
    {
        key = keys[i];
        value = values[i];
        return true;
    }
    return false;
}

void OldMap::swap(OldMap& other)
{
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        KeyType tempKey = keys[i];
        ValueType tempValue = values[i];
        keys[i] = other.keys[i];
        values[i] = other.values[i];
        other.keys[i] = tempKey;
        other.values[i] = tempValue;
    }
}

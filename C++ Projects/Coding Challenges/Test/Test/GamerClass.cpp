#include "GamerClass.h"

GamerMap::GamerMap()
{
    
}

bool GamerMap::addGamer(KeyType name)
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(gamerMap.keys[i] == name)
        {
            return false;
        }
    }
    
    gamerMap.insert(name, 0);
    return true;
}

double GamerMap::hoursSpent(KeyType name) const
{
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(gamerMap.keys[i] == name)
        {
            return gamerMap.values[i];
        }
    }
    
    return -1;
}

bool GamerMap::play(KeyType name, ValueType hours)
{
    if (hours < 0)
    {
        return false;
    }
    
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if(name == gamerMap.keys[i])
        {
            gamerMap.values[i] += hours;
            return true;
        }
    }
    
    return false;
}

int GamerMap::numGamers() const
{
    return gamerMap.size();
}

void GamerMap::print() const
{
    for(int i = 0; i < gamerMap.size(); i++)
    {
        std::cout << gamerMap.keys[i] << " " << gamerMap.values[i] << std::endl;
    }
}

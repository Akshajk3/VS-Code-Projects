#pragma once

#include "Map.h"

using KeyType = std::string;
using ValueType = double;

class GamerMap
{
  public:
    GamerMap();       // Create an empty gamer map.

    bool addGamer(std::string name);
      // If a person with the specified name is not currently in the map,
      // and there is room in the map, add an entry for that person
      // recording that they have spent 0 hours gaming, and return true.
      // Otherwise, make no change to the map and return false.

    double hoursSpent(std::string name) const;
      // If a person with the specified name is in the map, return how
      // many hours they have spent gaming; otherwise, return -1.

    bool play(std::string name, double hours);
      // If no person with the specified name is in the map or if hours
      // is negative, make no change to the map and return false.
      // Otherwise, increase by the hours parameter the number of hours
      // the indicated person has spent gaming and return true.

    int numGamers() const;  // Return the number of people in the GamerMap.

    void print() const;
      // Write to cout one line for every person in the map.  Each line
      // consists of the person's name, followed by one space, followed by
      // the number of hours that person has spent gaming.  Write no other
      // text.  The lines need not be in any particular order.

  private:
    Map gamerMap;
};

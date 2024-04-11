#include "Thing.h"

Things::Things()
{
    
}

Things::~Things()
{
    
}

void Things::AddThing(Thing &thing)
{
    m_Things.push_back(thing);
}

Thing Things::GetThingByID(int ID)
{
    Thing thing;
    
    for (std::vector<Thing>::iterator itr = m_Things.begin(); itr != m_Things.end(); itr++)
    {
        if (itr->Type == ID)
        {
            thing = (*itr);
            break;
        }
    }
    
    return thing;
}

//
//  geodb.h
//  project4
//
//  Created by Kashyap Kanumuri on 3/11/24.
//

#ifndef geodb_h
#define geodb_h

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "base_classes.h"
#include "HashMap.h"
#include "geotools.h"

using namespace std;

class GeoDatabase: public GeoDatabaseBase
{
public:
    GeoDatabase() {};
    virtual ~GeoDatabase() {};
 virtual bool load(const std::string& map_data_file);
 virtual bool get_poi_location(const std::string& poi,
                               GeoPoint& point) const;
 virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt)
 const;
 virtual std::string get_street_name(const GeoPoint& pt1,
                                     const GeoPoint& pt2) const;
private:
    HashMap<GeoPoint> hash_poiLocation;//POI NAme -> geopoint
    HashMap<std::vector<GeoPoint>> hash_connectedPoints;
    //This hasmap contains a GeoPoint as the key and the value is a vector of geoPoint, the points in the vector are all the points connected to the original GeoPoint.
    HashMap<std::string> hash_streetName; //The key is the start and end Geo Point and the value is a string. we will use this hash map by passing in a point and trying to find the associated street
    
    void update_connection(const GeoPoint& startPoint, const GeoPoint& endPoint);
    
    void update_street(const GeoPoint& startPoint, const GeoPoint& endPoint, const std::string& streetName);
    //const std::string& streetName
};

#endif /* geodb_h */

//    struct Coord{
//        double x;
//        double y;
//    };
//    struct GeoNode{
//        string streetName;
//        Coord startPoint;
//        Coord endPoint;
//    };

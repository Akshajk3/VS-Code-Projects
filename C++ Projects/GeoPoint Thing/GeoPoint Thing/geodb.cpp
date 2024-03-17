//
//  geodb.cpp
//  project4
//
//  Created by Kashyap Kanumuri on 3/11/24.
//


#include "geodb.h"


using namespace std;

bool GeoDatabase::load(const std::string& map_data_file) {
    fstream newfile;
    newfile.open(map_data_file, ios::in);

    if (!newfile.is_open()) {
        cout << "Failed to open" << endl;
        return false;
    }

    string line;
    while (getline(newfile, line)) {
        string street_name = line;

        string startLat, startLon, endLat, endLon;
        getline(newfile, line);
        istringstream iss(line);
        iss >> startLat >> startLon >> endLat >> endLon;
        GeoPoint a(startLat, startLon);
        GeoPoint b(endLat, endLon);

        update_connection(a, b);
        update_connection(b, a);
        update_street(a, b, street_name);
        update_street(b, a, street_name);


        string poi_count;
        getline(newfile, line);
        poi_count = line;
        int int_poi_count = stoi(poi_count);

        if (poi_count == "0") {
            continue;
        }
        else {


            GeoPoint midPoint = midpoint(a, b);
            update_connection(a, midPoint);
            update_connection(midPoint, a);

            update_street(a, midPoint, street_name);
            update_street(midPoint, a, street_name);

            update_connection(b, midPoint);
            update_connection(midPoint, b);

            update_street(b, midPoint, street_name);
            update_street(midPoint, b, street_name);

            for (int i = 0; i < int_poi_count; i++) {
                //connect each poi to the midpoint and vice versa
                getline(newfile, line);
                string poi_lat, poi_lon;
                istringstream issPnt(line);
                string pointName;
                getline(issPnt, pointName, '|');
                issPnt >> poi_lat >> poi_lon;
                GeoPoint poi(poi_lat, poi_lon);

                update_connection(poi, midPoint);
                update_connection(midPoint, poi);

                update_street(poi, midPoint, "a path");
                update_street(midPoint, poi, "a path");

                hash_poiLocation[pointName] = poi;

            }

        }


    }

    newfile.close();
    return true;
}

void GeoDatabase::update_connection(const GeoPoint& startPoint, const GeoPoint& endPoint) {

    //another param: , const std::string& streetName

    // Create a unique key for the connection using streetName and GeoPoint strings
    std::string connectionKey = startPoint.to_string();

    // Check if the connection already exists
    std::vector<GeoPoint>& connectedPoints = hash_connectedPoints[connectionKey];

    // Update the connection by adding endPoint to the existing list of connected points
    connectedPoints.push_back(endPoint);

    // Update the connection in the HashMap
    //hash_connectedPoints[connectionKey] = connectedPoints;

}

void GeoDatabase::update_street(const GeoPoint& startPoint, const GeoPoint& endPoint, const std::string& streetName) {

    std::string nameKey = startPoint.to_string() + endPoint.to_string();
    hash_streetName[nameKey] = streetName;

}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {

    const GeoPoint* holdPoint = hash_poiLocation.find(poi);
    if (holdPoint == nullptr) {
        cout << "failed here" << endl;
        return false;
    }
    else {
        point = *(holdPoint);
        return true;
    }


}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    std::string connectionKey = pt.to_string();
    const std::vector<GeoPoint>* holdVector = (hash_connectedPoints.find(connectionKey));

    if (holdVector == nullptr) {
        return {};
    }
    else {
        return *holdVector;
    }
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    std::string nameKey = pt1.to_string() + pt2.to_string();
    const std::string* holdStreetName = (hash_streetName.find(nameKey));

    if (holdStreetName == nullptr) {
        return "";
    }
    else {
        return *holdStreetName;
    }
}


// hashMap.insert(concat(startLat, startLon), street_name)
// hashMap.insert(concat(endLat, endLon), street_name)

/*
 {
 "34.923,-118.20": ["Glendon Ave", "Strathmore Dr"],
 "Glendon Ave": [(34.123,-118.23), (34.129,-118.45)]
 }
 */

 //hashmap.insert(street_name, GeoPoint(<#const std::string &lat#>, <#const std::string &lon#>))




 //go through the string take in the street, then take in the geoPoints, then if you hit 0 continue, else you need to take that number in and loop through the

 //    if(newfile.is_open()){
 //        string tp;
 //        GeoNode tempNode;
 //        int lineCounter = 0;
 //        int coordCounter;
 //        while(getline(newfile, tp))
 //        {
 //            if(tp == "0")
 //            {
 //                lineCounter = 0;
 //                coordCounter = 0;
 //            }
 //            else
 //            {
 //                if(lineCounter == 1)
 //                {
 //                    tempNode.streetName = tp;
 //                }
 //                else
 //                {
 //
 //                }
 //            }
 //        }
 //    }

// #include "geodb.h"


// using namespace std;

// bool GeoDatabase::load(const std::string& map_data_file){
//     fstream newfile;
//     newfile.open(map_data_file, ios::in);
    
//     if(!newfile.is_open()){
//         return false;
//     }
    
//     string line;
//     while(getline(newfile, line)){
//         string street_name = line;
        
//         string startLat, startLon, endLat, endLon;
//         getline(newfile, line);
//         istringstream iss(line);
//         iss >> startLat >> startLon >> endLat >> endLon;
//         GeoPoint a(startLat, startLon);
//         GeoPoint b(endLat, endLon);
        
//         update_connection(a, b);
//         update_connection(b, a);
//         update_street(a, b, street_name);
        


//         string poi_count;
//         getline(newfile, line);
//         poi_count = line;
//         int int_poi_count = stoi(poi_count);
        
//         if(poi_count == "0"){
//             continue;
//         }
//         else{
           
            
//             GeoPoint midPoint = midpoint(a, b);
//             update_connection(a, midPoint);
//             update_connection(midPoint, a);
//             update_street(a, midPoint, street_name);
            
//             update_connection(b, midPoint);
//             update_connection(midPoint, b);
//             update_street(b, midPoint, street_name);
            
//             for(int i = 0; i < int_poi_count; i++){
//                 //connect each poi to the midpoint and vice versa
//                 getline(newfile, line);
//                 string poi_lat, poi_lon;
//                 istringstream issPnt(line);
//                 string pointName;
//                 getline(issPnt, pointName, '|');
//                 issPnt >> poi_lat >> poi_lon;
//                 GeoPoint poi(poi_lat, poi_lon);
                
//                 update_connection(poi, midPoint);
//                 update_connection(midPoint, poi);
//                 update_street(a, midPoint, "a path");
//                 hash_poiLocation[pointName] = poi;
                
//             }
            
//         }
        
    
//     }
    

//     return false;
// }

// void GeoDatabase::update_connection(const GeoPoint& startPoint, const GeoPoint& endPoint){
    
//     //another param: , const std::string& streetName
    
//     // Create a unique key for the connection using streetName and GeoPoint strings
//     std::string connectionKey = startPoint.to_string();
    
//     // Check if the connection already exists
//     std::vector<GeoPoint> connectedPoints = hash_connectedPoints[connectionKey];
    
//     // Update the connection by adding endPoint to the existing list of connected points
//     connectedPoints.push_back(endPoint);

//     // Update the connection in the HashMap
//     hash_connectedPoints[connectionKey] = connectedPoints;

// }

// void GeoDatabase::update_street(const GeoPoint& startPoint, const GeoPoint& endPoint, const std::string& streetName){
    
//     std::string nameKey = startPoint.to_string() + endPoint.to_string();
//     hash_streetName[nameKey] = streetName;
    
// }

// bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {

//     const GeoPoint* holdPoint = hash_poiLocation.find(poi);
//     if(holdPoint == nullptr){
//         return false;
//     } else{
//         point = *(holdPoint);
//         return true;
//     }
   
    
// }

// std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
//     std::string connectionKey = pt.to_string();
//     const std::vector<GeoPoint>* holdVector = (hash_connectedPoints.find(connectionKey));
   
//     if(holdVector == nullptr){
//         return {};
//     } else{
//         return *holdVector;
//     }
// }

// std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
//     std::string nameKey = pt1.to_string() + pt2.to_string();
//     const std::string* holdStreetName = (hash_streetName.find(nameKey));
   
//     if(holdStreetName == nullptr){
//         return "";
//     } else{
//         return *holdStreetName;
//     }
// }



// hashMap.insert(concat(startLat, startLon), street_name)
// hashMap.insert(concat(endLat, endLon), street_name)

/*
 {
 "34.923,-118.20": ["Glendon Ave", "Strathmore Dr"],
 "Glendon Ave": [(34.123,-118.23), (34.129,-118.45)]
 }
 */

//hashmap.insert(street_name, GeoPoint(<#const std::string &lat#>, <#const std::string &lon#>))




//go through the string take in the street, then take in the geoPoints, then if you hit 0 continue, else you need to take that number in and loop through the

//    if(newfile.is_open()){
//        string tp;
//        GeoNode tempNode;
//        int lineCounter = 0;
//        int coordCounter;
//        while(getline(newfile, tp))
//        {
//            if(tp == "0")
//            {
//                lineCounter = 0;
//                coordCounter = 0;
//            }
//            else
//            {
//                if(lineCounter == 1)
//                {
//                    tempNode.streetName = tp;
//                }
//                else
//                {
//
//                }
//            }
//        }
//    }

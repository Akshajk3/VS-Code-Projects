#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "geodb.h"
#include "router.h"
#include "stops.h"
#include "tourcmd.h"
#include "tour_generator.h"
#include "HashMap.h"

using namespace std;

//void print_tour(vector<TourCommand>& tcs)
//{
//    double total_dist = 0;
//    std::string direction;
//    double street_distance = 0;
//
//    cout << "Starting tour...\n";
//
//    for (size_t i = 0; i < tcs.size(); ++i)
//    {
//        if (tcs[i].get_command_type() == TourCommand::commentary)
//        {
//            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
//            cout << tcs[i].get_commentary() << "\n";
//        }
//        else if (tcs[i].get_command_type() == TourCommand::turn)
//        {
//            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
//        }
//        else if (tcs[i].get_command_type() == TourCommand::proceed)
//        {
//            total_dist += tcs[i].get_distance();
//            if (direction.empty())
//                direction = tcs[i].get_direction();
//            street_distance += tcs[i].get_distance();
//            if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed 
//                && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
//            {
//                continue;
//            }
//
//            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
//            street_distance = 0;
//            direction.clear();
//        }
//    }
//
//    cout << "Your tour has finished!\n";
//    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
//}
//
// int main(int argc, char *argv[])
// {
//    if (argc != 3)
//    {
//        cout << "usage: BruinTour mapdata.txt stops.txt\n";
//        return 1;
//    }

//    GeoDatabase geodb;
//    if (!geodb.load(argv[1]))
//    {
//        cout << "Unable to load map data: " << argv[1] << endl;
//        return 1;
//    }

//    Router router(geodb);
//    TourGenerator tg(geodb, router);

//    Stops stops;
//    if (!stops.load(argv[2]))
//    {
//        cout << "Unable to load tour data: " << argv[2] << endl;
//        return 1;
//    }

//    std::cout << "Routing...\n\n";

//    vector<TourCommand> tcs = tg.generate_tour(stops);
//    if (tcs.empty())
//        cout << "Unable to generate tour!\n";
//    else
//        print_tour(tcs);


// }


int main() {
 GeoDatabase g;
 g.load("mapdata2.txt"); // assume this works to avoid error checking
 GeoPoint p;
 if (g.get_poi_location("Diddy Riese", p))
 cout << "The PoI is at " << p.sLatitude << ", "
 << p.sLongitude << endl;
 else
 cout << "PoI not found!\n";
}


// int main() {
// 	GeoDatabase g;
// 	g.load("mapdata.txt"); // assume this works to avoid error checking
// 	std::vector<GeoPoint> pts = g.get_connected_points(
// 		GeoPoint("34.0731003", "-118.4931016"));
// 	if (pts.empty())
// 		cout << "There are no points connected to your specified point\n";
// 	else {
// 		for (const auto p : pts)
// 			cout << p.sLatitude << ", " << p.sLongitude << endl;
// 	}
// }

// int main() {
// 	 GeoDatabase g;
// 	 g.load("mapdata.txt"); // assume this works to avoid error checking
// 	 std::vector<GeoPoint> pts = g.get_connected_points(
// 	 GeoPoint("34.0731003", "-118.4931016"));
// 	 if (pts.empty())
// 	 cout << "There are no points connected to your specified point\n";
// 	 else {
// 		 for (const auto p : pts)
// 			cout << p.sLatitude << ", " << p.sLongitude << endl;
// 	 }
// }

// int main()
// {
// 	GeoDatabase g;
// 	g.load("mapdata.txt");
// 	GeoPoint p1("34.0732851", "-118.4931016");
// 	GeoPoint p2("34.0736122", "-118.4927669");
// 	cout << g.get_street_name(p1, p2); // writes "Glenmere Way"
// 	cout << g.get_street_name(p2, p1); // writes "Glenmere Way"
// }

// int main() {
// 	 GeoDatabase g;
// 	 g.load("mapdata.txt"); // assume this works to avoid error checking
// 	 std::vector<GeoPoint> pts = g.get_connected_points(
// 	 GeoPoint("34.0731003", "-118.4931016"));
// 	 if (pts.empty())
// 	 cout << "There are no points connected to your specified point\n";
// 	 else {
// 	 for (const auto p: pts)
// 	 cout << p.sLatitude << ", " << p.sLongitude << endl;
// 	 }
// }

// int main(){
//    // Define a hashmap that maps strings to doubles and has a maximum
//     // load factor of 0.2. It will initially have 10 buckets when empty.
//     HashMap<double> nameToGPA(0.2);
//     // Add new items to the hashmap
//     nameToGPA.insert("Carey", 3.5); // Carey has a 3.5 GPA
//     nameToGPA.insert("David", 2.99); // David needs to up his game

//     // You can also use brackets like C++'s unordered_map!
//     nameToGPA["Annie"] = 3.85; // Adds Annie, who has the highest GPA of all.
//     // Since adding Annie would push the load factor from 0.2 to 0.3, exceeding the
//     // maximum load factpr of 0.2, adding Annie caused the hashmap to increase the
//     // number of buckets, forcing a rehash of all items.
//     double* davidsGPA = nameToGPA.find("David");
//     if (davidsGPA != nullptr)
//     *davidsGPA = 3.1; // after a re-grade of David's exam, update 2.99 -> 3.1
//     nameToGPA.insert("Carey", 4.0); // Carey deserves a 4.0
//     // sees if linda is in the map; if not, creates a new entry for linda in map
//     cout << nameToGPA["Linda"]; // prints zero
// }

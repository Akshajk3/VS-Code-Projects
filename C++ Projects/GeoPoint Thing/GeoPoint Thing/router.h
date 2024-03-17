//
//  router.h
//  project4
//
//  Created by Kashyap Kanumuri on 3/12/24.
//

#include "base_classes.h"
#ifndef router_h
#define router_h

class Router: public RouterBase
{
public:
 Router(const GeoDatabaseBase& geo_db);
 virtual ~Router();
 virtual std::vector<GeoPoint> route(const GeoPoint& pt1,
 const GeoPoint& pt2) const;
};

#endif /* router_h */

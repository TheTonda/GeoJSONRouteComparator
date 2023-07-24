#include <iostream>


#include "GeoJSONRouteParser.h"
#include "test.h"

int main() {
    std::string polylineGeoJSON1 = R"({
        "type": "Feature",
        "geometry": {
            "type": "LineString",
            "coordinates": "_p~iF~ps|U_ulLnnqC_mqNvxq`@"
        }
    })";

    std::string parsedRoute1 = parseGeoJSONRoute(polylineGeoJSON1);
    std::cout << parsedRoute1 << std::endl;

    std::string polylineGeoJSON2 = R"({
        "type": "Feature",
        "geometry": {
            "type": "LineString",
            "coordinates": "_p~iF~ps|U_ulLnnqC_mqNvxq`@"
        }
    })";

    std::string parsedRoute2 = parseGeoJSONRoute(polylineGeoJSON2);
    std::cout << parsedRoute2 << std::endl;

    double percentage = calculateOverlap(parsedRoute1,parsedRoute2);

    std::cout << percentage << std::endl;

    return 0;
}
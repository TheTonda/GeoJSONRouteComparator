#include <vector>
#include <string>

struct Coordinate {
    double lat;
    double lon;
};

std::vector<Coordinate> decodePolyline(const std::string& polylineString);

std::string parseGeoJSONRoute(const std::string& polylineGeoJSON);

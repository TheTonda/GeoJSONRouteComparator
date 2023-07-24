#include "GeoJSONRouteParser.h"

#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<Coordinate> decodePolyline(const std::string& polylineString) {
    std::vector<Coordinate> coordinates;

    int index = 0;
    int len = polylineString.length();
    int lat = 0, lon = 0;

    while (index < len) {
        int shift = 0;
        int result = 0;
        int byte;

        do {
            byte = polylineString[index++] - 63;
            result |= (byte & 0x1F) << shift;
            shift += 5;
        } while (byte >= 0x20);

        int deltaLat = ((result & 1) ? ~(result >> 1) : (result >> 1));
        lat += deltaLat;

        shift = 0;
        result = 0;

        do {
            byte = polylineString[index++] - 63;
            result |= (byte & 0x1f) << shift;
            shift += 5;
        } while (byte >= 0x20);

        int deltaLon = ((result & 1) ? ~(result >> 1) : (result >> 1));
        lon += deltaLon;

        Coordinate coordinate;
        coordinate.lat = lat * 1e-5;
        coordinate.lon = lon * 1e-5;
        coordinates.push_back(coordinate);
    }

    return coordinates;
}


std::string parseGeoJSONRoute(const std::string& polylineGeoJSON) {
    json route = json::parse(polylineGeoJSON);
    auto polylineString = route["geometry"]["coordinates"].get<std::string>();

    std::vector<Coordinate> decodedPoints = decodePolyline(polylineString);

    json parsedRoute = json::object();
    parsedRoute["type"] = "LineString";
    parsedRoute["coordinates"] = json::array();
    for(const auto& point : decodedPoints) {
        parsedRoute["coordinates"].push_back({point.lat, point.lon});
    }

    json parsedRouteGeometry = json::object();
    parsedRouteGeometry["geometry"] = parsedRoute;

    return parsedRouteGeometry.dump();
}


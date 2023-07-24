#include "test.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include <cmath>
#include <vector>

// Function to calculate the distance between two coordinates using the Haversine formula
double calculateDistance(const std::vector<double>& coordinates1, const std::vector<double>& coordinates2) {
    double lat1 = coordinates1[0]; // Latitude of coordinate 1 in degrees
    double lon1 = coordinates1[1]; // Longitude of coordinate 1 in degrees
    double lat2 = coordinates2[0]; // Latitude of coordinate 2 in degrees
    double lon2 = coordinates2[1]; // Longitude of coordinate 2 in degrees

    // Convert degrees to radians
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    // Calculate the differences between latitudes and longitudes
    double deltaLat = lat2Rad - lat1Rad;
    double deltaLon = lon2Rad - lon1Rad;

    // Calculate the Haversine distance
    double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = c * 6371; // Earth's radius in kilometers

    return distance;
}

// Function to calculate the total distance of a route by summing the distances between each pair of consecutive coordinates
double calculateRouteDistance(const std::vector<std::vector<double>>& coordinates) {
    double totalDistance = 0;

    for (size_t i = 0; i < coordinates.size() - 1; i++) {
        std::vector<double> currentCoordinates = coordinates[i];
        std::vector<double> nextCoordinates = coordinates[i + 1];

        double distance = calculateDistance(currentCoordinates, nextCoordinates);
        totalDistance += distance;
    }

    return totalDistance;
}


// Function to calculate the overlapping geometry between two GeoJSON routes
double calculateOverlap(const std::string& route1, const std::string& route2) {
    // Parse the GeoJSON routes
    json route1Json = json::parse(route1);
    json route2Json = json::parse(route2);

    // Get the coordinates of each route
    std::vector<std::vector<double>> coordinates1 = route1Json["geometry"]["coordinates"];
    std::vector<std::vector<double>> coordinates2 = route2Json["geometry"]["coordinates"];

    // Calculate the total distance of each route
    double distance1 = calculateRouteDistance(coordinates1);
    double distance2 = calculateRouteDistance(coordinates2);

    // Initialize variables to track the overlapping distance
    double overlappingDistance = 0.0;
    size_t currentIndex1 = 0;
    size_t currentIndex2 = 0;

    while (currentIndex1 < coordinates1.size() && currentIndex2 < coordinates2.size())
    {
        // Get the current coordinates for each route
        const std::vector<double> &currentCoordinates1 = coordinates1[currentIndex1];
        const std::vector<double> &currentCoordinates2 = coordinates2[currentIndex2];

        // Calculate the distance between the current coordinates
        double distance = calculateDistance(currentCoordinates1, currentCoordinates2);

        // If the distance is within a threshold, consider it as overlapping
        if (distance <= 90)
        {
            overlappingDistance += distance;
        }

        // Move to the next set of coordinates for each route
        if (currentIndex1 + 1 < coordinates1.size() && currentIndex2 + 1 < coordinates2.size())
        {
            double distance1 = calculateDistance(coordinates1[currentIndex1], coordinates1[currentIndex1 + 1]);
            double distance2 = calculateDistance(coordinates2[currentIndex2], coordinates2[currentIndex2 + 1]);

            if (distance1 <= distance2)
            {
                currentIndex1++;
            }
            else
            {
                currentIndex2++;
            }
        }
        else
        {
            break; // Reached the end of either route, exit the loop
        }
    }

    // Calculate the percentage of overlapping geometry
    double overlapPercentage = (overlappingDistance / std::min(distance1, distance2)) * 100.0;

    return overlapPercentage;
}


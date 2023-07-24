#include <vector>
#include <string>

// Function to calculate the distance between two coordinates
double calculateDistance(const std::vector<double>& coordinates1, const std::vector<double>& coordinates2);

// Function to calculate the total distance of a route
double calculateRouteDistance(const std::vector<std::vector<double>>& coordinates);


// Function to calculate the overlapping geometry between two GeoJSON routes
double calculateOverlap(const std::string& route1, const std::string& route2);


#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
double time_to_sat(double user_lat, double user_lon, double sat_lone, double user_alt)
{
    double user_x, user_y, user_z;
    double sat_x, sat_y, sat_z;
    double dx, dy, dz;
    const double Re = 6378.136; //Earth radius
    const int Rs = 42164; // Geostationary orbit radius
    const double M_PI = 3.14159265358979323846;

    double R = Re + user_alt / 1000.0;

    user_lat *= M_PI / 180.0;
    user_lon *= M_PI / 180.0;
    sat_lone *= M_PI / 180.0;

    user_x = cos(user_lon) * cos(user_lat) * R;
    user_y = sin(user_lon) * cos(user_lat) * R;
    user_z = sin(user_lat) * R;

    sat_x = cos(sat_lone) * Rs;
    sat_y = sin(sat_lone) * Rs;
    sat_z = 0;

    dx = sat_x - user_x;
    dy = sat_y - user_y;
    dz = sat_z - user_z;

    double dist = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));

    return dist / 300000.0 * 1000;

}
int main()
{
    /*std::locale::global(std::locale("ru"));*/
    double user_lat = 0;
    double user_lon = 0;
    double sat_lone = 0;
    double user_alt = 0;
    std::vector<double> numbers{ user_lat, user_lon, sat_lone, user_alt };
    std::cout << "2 flags - degrees and dms\n" << "Example : degrees 37.5 or dms 37'30'00\n1)User latitude\n2)User longitude\n3)Space vehicle standing point longitude\n4)User height above sea level. May be missed\n";
    for (int i = 0; i < 4; i++)
    {
        std::string strobj;
        std::getline(std::cin, strobj);
        std::string first;
        std::istringstream iss{ strobj };
        iss >> first;
        std::ostringstream oss;
        oss << iss.rdbuf();
        strobj = oss.str();
        strobj.erase(0, 1);
        if (first == "dms")
        {
            std::stringstream ss(strobj);
            std::string degrees, minutes, seconds;
            std::getline(ss, degrees, '\'');
            std::getline(ss, minutes, '\'');
            std::getline(ss, seconds);
            double degr = std::stod(degrees);
            double min = std::stod(minutes) / 60.0;
            double sec = std::stod(seconds) / 3600.0;
            degr = degr + min + sec;
            numbers[i] = degr;
        }
        else if (first == "degrees")
        {
            double num;
            num = std::stod(strobj);
            numbers[i] = num;
        }
    }
    std::cout << time_to_sat(numbers[0], numbers[1], numbers[2], numbers[3]);
}


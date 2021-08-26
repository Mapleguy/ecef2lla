#pragma once

/*
Convert from ECEF (Earth-centered, Earth-focused) coordinates to LLA (latitude, longitude, altitude) coordinates
This is based on WGS-84 data on Earth size and eccentricity
This has been tested and used in real systems, it works
*/

#include <math.h>
#define radius 6378137 //Earth radius in meters
#define eccentricity 0.081819190842622 //Earth eccentricity

double radsq = pow(radius, 2);
double eccsq = pow(eccentricity, 2);

//This returns an array of 3 doubles [latitude, longitude, altitude]
double* ecef2lla(double x, double y, double z){
    double* lla = new double[3];
    lla[0] = 0;
    lla[1] = 0;
    lla[2] = 0;

    double b = sqrt(radsq * (1 - eccsq));
    double bsq = pow(b, 2);

    double ep = sqrt((radsq - bsq) / bsq);
    double p = sqrt(pow(x, 2) + pow(y, 2));
    double th = atan2(radius * z, b * p);

    double lon = atan2(y, x);
    double lat = atan2((z + pow(ep, 2) * b * pow(sin(th), 3)), (p - eccsq * radius * pow(cos(th), 3)));
    double N = radius / (sqrt(1 - eccsq * pow(sin(lat), 2)));
    double alt = p / cos(lat) - N;

    lon = fmod(lon, 2 * 3.14159265);

    lla[0] = lat * (180 / 3.14159265); //Covert to degrees
    lla[1] = lon * (180 / 3.14159265); //Covert to degrees
    lla[2] = alt;

    return lla;
}

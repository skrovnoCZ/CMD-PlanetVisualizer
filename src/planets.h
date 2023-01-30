#ifndef PLANETS_H
#define PLANETS_H

#include <vector>
using namespace std;

class Planets
{
public:
    Planets();
    vector<float> xPositions;
    vector<float> yPositions;
    vector<float> Mass;
    vector<bool> Fixed;

    void NextTimeInterval(float Time);
    void AddPoint(float xPos, float yPos, float xVel, float yVel, float mass, bool fixed);
    void RemoveAllPlanets();

    //----------edit--------------------
    float get_x_pos(size_t vec_x);
    float get_y_pos(size_t vec_y);
    size_t get_vec_coord_size();
    void remove_planet(size_t x);
    //----------edit--------------------

private:
    vector<float> xVelocity;
    vector<float> yVelocity;
};

#endif // PLANETS_H
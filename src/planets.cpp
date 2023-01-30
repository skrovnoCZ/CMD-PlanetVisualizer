#include "planets.h"
#include <cmath>
#include <iostream>

Planets::Planets()
{

}

void Planets::AddPoint(float xPos, float yPos, float xVel, float yVel, float mass, bool fixed)
{
    xPositions.push_back(xPos);
    yPositions.push_back(yPos);

    xVelocity.push_back(xVel);
    yVelocity.push_back(yVel);

    Mass.push_back(mass);

    Fixed.push_back(fixed);

}

void Planets::NextTimeInterval(float Time)
{
    float CurrentX = 0.0f;
    float CurrentY = 0.0f;
    vector<float> xPositionsNew;
    vector<float> yPositionsNew;
    vector<float> xVelocityNew;
    vector<float> yVelocityNew;


    //go through each planet and do a calc to move it.
    // v = v0 + a*t
    for (unsigned int i = 0; i < xPositions.size(); i++)
    {
        CurrentX = xPositions[i];
        CurrentY = yPositions[i];
        float ForceX = 0.0f;
        float ForceY = 0.0f;

        for (unsigned int j = 0; j < xPositions.size(); j++)
        {
            if (i != j)
            {
                float distance = sqrt((CurrentX - xPositions[j]) * (CurrentX - xPositions[j]) + (CurrentY - yPositions[j]) * (CurrentY - yPositions[j]));
                //cout << "Distance is " << distance << endl;

                float Force = Mass[i] * Mass[j] / distance;
                //cout << "Force is " << Force << endl;

                ForceX = ForceX + (Force / distance * (xPositions[j] - CurrentX)) * 0.1f;
                ForceY = ForceY + (Force / distance * (yPositions[j] - CurrentY)) * 0.1f;

            }
        }
        //cout << "Accel is " << ForceX/Mass[i] << endl;
        if (Fixed[i])
        {
            xVelocityNew.push_back(0);
            yVelocityNew.push_back(0);
            xPositionsNew.push_back(xPositions[i]);
            yPositionsNew.push_back(yPositions[i]);

        }
        else
        {
            xVelocityNew.push_back(ForceX / Mass[i] * Time + xVelocity[i]);
            yVelocityNew.push_back(ForceY / Mass[i] * Time + yVelocity[i]);
            xPositionsNew.push_back(xPositions[i] + 0.5f * (xVelocityNew[i] + xVelocity[i])* Time);
            yPositionsNew.push_back(yPositions[i] + 0.5f * (yVelocityNew[i] + yVelocity[i])* Time);
        }

    }
    xPositions = xPositionsNew;
    yPositions = yPositionsNew;
    xVelocity = xVelocityNew;
    yVelocity = yVelocityNew;

}

void Planets::RemoveAllPlanets()
{
    xPositions.clear();
    yPositions.clear();

    xVelocity.clear();
    yVelocity.clear();

    Mass.clear();

    Fixed.clear();

}

//----------edit--------------------
float Planets::get_x_pos(size_t vec_x)
{
    return xPositions.at(vec_x);
}

float Planets::get_y_pos(size_t vec_y)
{
    return yPositions.at(vec_y);
}

size_t Planets::get_vec_coord_size()
{
    if (xPositions.size() != yPositions.size())
    {
        cerr << "Error. Some coordinates are missing due to size difference between xPositions and yPositions." << endl;
    }

    return xPositions.size();
}

void Planets::remove_planet(size_t x)
{
    xPositions.erase(xPositions.begin() + x);
    yPositions.erase(yPositions.begin() + x);
    Mass.erase(Mass.begin() + x);
    Fixed.erase(Fixed.begin() + x);
}
//----------edit--------------------
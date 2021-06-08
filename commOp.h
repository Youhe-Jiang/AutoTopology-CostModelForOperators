#pragma once
#include <iostream>
#include <cmath>
using namespace std;


class CommOp
{
public:

    virtual double ring() = 0;
    virtual double tree() = 0;
    double a;
    double b;
    double r;
    double n;
    double p;
    double s;
    double o;

    virtual ~CommOp(){};
};
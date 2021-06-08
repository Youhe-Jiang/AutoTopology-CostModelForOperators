#pragma once
#include "commOp.h"

class Reduce : public CommOp
{
public:
    Reduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff);

    virtual double ring();
    virtual double tree();

    virtual ~Reduce(){};
};
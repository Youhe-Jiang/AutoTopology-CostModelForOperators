#pragma once
#include "commOp.h"

class Broadcast : public CommOp
{
public:
    Broadcast(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff);

    virtual double ring();
    virtual double tree();

    virtual ~Broadcast(){};
};


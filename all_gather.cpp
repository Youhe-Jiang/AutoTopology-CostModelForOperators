#include "all_gather.h"


AllGather::AllGather(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    this->a = latency;
    this->b = bandwidth;
    this->r = computeCost;
    this->n = numOfBytesTrans;
    this->p = numOfProcess;
    this->s = pipelineStage;
    this->o = overlap_coeff;
}

double AllGather::ring()
{
    double cost = (p - 1) * a + ((p - 1) / p) * n * b;
    return cost;
}

double AllGather::tree()
{
    double cost = log2(p) * a + ((p - 1) / p) * n * b;
    return cost;
}
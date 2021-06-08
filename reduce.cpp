#include "reduce.h"


Reduce::Reduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    this->a = latency;
    this->b = bandwidth;
    this->r = computeCost;
    this->n = numOfBytesTrans;
    this->p = numOfProcess;
    this->s = pipelineStage;
    this->o = overlap_coeff;
}

double Reduce::ring()
{
    double cost = a + (p - 1) * n * b + (p - 1) * n * r - o * (a + (p - 1) * n * b - (p - 1) * n * r);
    return cost;
}

double Reduce::tree()
{
    double cost = log2(p) * (a + n * b + n * r) - o * (log2(p) * (a + n * b - n * r));
    return cost;
}



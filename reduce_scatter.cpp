#include "reduce_scatter.h"


ReduceScatter::ReduceScatter(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    this->a = latency;
    this->b = bandwidth;
    this->r = computeCost;
    this->n = numOfBytesTrans;
    this->p = numOfProcess;
    this->s = pipelineStage;
    this->o = overlap_coeff;
}

double ReduceScatter::ring()
{
    double cost = (p - 1) * a + ((p - 1) / p) * n * b + ((p - 1) / p) * n * r - o * ((p - 1) * a + ((p - 1) / p) * n * b - ((p - 1) / p) * n * r);
    return cost;
}

double ReduceScatter::tree()
{
    double cost = log2(p) * a + ((p - 1) / p) * n * b + ((p - 1) / p) * n * r - o * (log2(p) * a + ((p - 1) / p) * n * b - ((p - 1) / p) * n * r);
    return cost;
}
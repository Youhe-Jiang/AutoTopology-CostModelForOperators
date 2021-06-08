#include "broadcast.h"


Broadcast::Broadcast(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    this->a = latency;
    this->b = bandwidth;
    this->r = computeCost;
    this->n = numOfBytesTrans;
    this->p = numOfProcess;
    this->s = pipelineStage;
    this->o = overlap_coeff;
}

double Broadcast::ring()
{
    double cost = a + (p - 1) * n * b;
    return cost;
}


double Broadcast::tree()
{
    double cost = log2(p) * (a + n * b);
    return cost;
}

//void Broadcast::pipeline()
//{
//    double cost = (s + p - 2) * a + ((s + p - 2) / s) * n * b;
//    cout << cost << endl;
//}
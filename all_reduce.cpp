#include "all_reduce.h"


AllReduce::AllReduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    this->a = latency;
    this->b = bandwidth;
    this->r = computeCost;
    this->n = numOfBytesTrans;
    this->p = numOfProcess;
    this->s = pipelineStage;
    this->o = overlap_coeff;
}


double AllReduce::ring()
{
    double cost_latency_optimal = 2 * a + 2 * (p - 1) * n * b + (p - 1) * n * r - o * abs(2 * a + 2 * (p - 1) * n * b - (p - 1) * n * r);
    double cost_bandwidth_optimal = 2 * (p - 1) * a + 2 * ((p - 1) / p) * n * b + ((p - 1) / p) * n * r - o * abs(2 * (p - 1) * a + 2 * ((p - 1) / p) * n * b - ((p - 1) / p) * n * r);
    if (cost_latency_optimal > cost_bandwidth_optimal)
    {
        return cost_bandwidth_optimal;
    }
    else
    {
        return cost_latency_optimal;
    }
}

double AllReduce::tree()
{
    double cost_reduce_broadcast = log2(p) * (2 * a + 2 * n * b + n * r) - o * (log2(p) * (2 * a + 2 * n * b - n * r));
    double cost_reduce_scatter_all_gather = 2 * log2(p) * a + 2 * ((p - 1) / p) * n * b + ((p - 1) / p) * n * r - o * (2 * log2(p) * a + 2 * ((p - 1) / p) * n * b - ((p - 1) / p) * n * r);
    if (cost_reduce_broadcast > cost_reduce_scatter_all_gather)
    {
        return cost_reduce_scatter_all_gather;
    }
    else
    {
        return cost_reduce_broadcast;
    }
}

//void AllReduce::ring_latency_optimal()
//{
//    double cost = 2 * a + 2 * (p - 1) * n * b + (p - 1) * n * r;
//    cout << cost << endl;
//}
//
//void AllReduce::ring_bandwidth_optimal()
//{
//    double cost = 2 * (p - 1) * a + 2 * ((p - 1) / p) * n * b + ((p - 1) / p) * n * r;
//    cout << cost << endl;
//}
//
//void AllReduce::tree_reduce_broadcast()
//{
//    double cost = log2(p) * (2 * a + 2 * n * b + n * r);
//    cout << cost << endl;
//}
//
//void AllReduce::tree_reduce_scatter_all_gather()
//{
//    double cost = 2 * log2(p) * a + 2 * ((p - 1) / p) * n * b + ((p - 1) / p) * n * r;
//    cout << cost << endl;
//}
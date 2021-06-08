#include "ring_topology.h"
double coe_of_intra_group_bw = 10;
double group_size = 8;

double RingAllreduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    CommOp * stage2 = NULL;
    stage1 = new AllReduce(latency, bandwidth, computeCost, numOfBytesTrans, numOfProcess, pipelineStage, overlap_coeff);
    stage2 = new AllReduce(latency, bandwidth / coe_of_intra_group_bw, computeCost, numOfBytesTrans, numOfProcess, pipelineStage, overlap_coeff);
    double ring_allreduce_inter = stage1->ring();
    double ring_allreduce_intra = stage2->ring();
    delete stage1;
    delete stage2;
    if(numOfProcess > 8)
    {
        return ring_allreduce_inter;
    }
    else
    {
        return ring_allreduce_intra;
    }
};


double HierarchicalAllreduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    stage1 = new Reduce(latency, bandwidth / coe_of_intra_group_bw, computeCost, numOfBytesTrans, group_size, pipelineStage, overlap_coeff);
    CommOp * stage2 = NULL;
    stage2 = new AllReduce(latency, bandwidth, computeCost, numOfBytesTrans, numOfProcess / group_size, pipelineStage, overlap_coeff);
    CommOp * stage3 = NULL;
    stage3 = new Broadcast(latency, bandwidth / coe_of_intra_group_bw, computeCost, numOfBytesTrans, group_size, pipelineStage, overlap_coeff);
    double hierarchical_allreduce = stage1->ring() + stage2->ring() + stage3->ring();
    delete stage1;
    delete stage2;
    delete stage3;
    return hierarchical_allreduce;
}

double TorusAllreduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    stage1 = new ReduceScatter(latency, bandwidth / coe_of_intra_group_bw, computeCost, numOfBytesTrans, group_size, pipelineStage, overlap_coeff);
    CommOp * stage2 = NULL;
    stage2 = new AllReduce(latency, bandwidth, computeCost, numOfBytesTrans, numOfProcess / group_size, pipelineStage, overlap_coeff);
    CommOp * stage3 = NULL;
    stage3 = new AllGather(latency, bandwidth / coe_of_intra_group_bw, computeCost, numOfBytesTrans, group_size, pipelineStage, overlap_coeff);
    double torus_allreduce = stage1->ring() + stage2->ring() + stage3->ring();
    delete stage1;
    delete stage2;
    delete stage3;
    return torus_allreduce;
}



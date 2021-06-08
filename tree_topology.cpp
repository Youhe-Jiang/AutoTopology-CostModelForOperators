#include "tree_topology.h"
#include <math.h>
double _coe_of_intra_group_bw = 10;
double _group_size = 8;

double TreeAllreduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    stage1 = new AllReduce(latency, bandwidth / _coe_of_intra_group_bw, computeCost, numOfBytesTrans, _group_size, pipelineStage, overlap_coeff);
    CommOp * stage2 = NULL;
    stage2 = new AllReduce(latency, bandwidth, computeCost, numOfBytesTrans, numOfProcess / _group_size, pipelineStage, overlap_coeff);
    CommOp * stage3 = NULL;
    stage3 = new AllReduce(latency, bandwidth / _coe_of_intra_group_bw, computeCost, numOfBytesTrans, numOfProcess, pipelineStage, overlap_coeff);
    double tree_allreduce_inter = stage1->ring() + stage2->tree();
    double tree_allreduce_intra = stage3->tree();
    delete stage1;
    delete stage2;
    delete stage3;
    if(numOfProcess > 8)
    {
        return tree_allreduce_inter;
    }
    else
    {
        return tree_allreduce_intra;
    }
}

double OptimizedTreeAllreduce(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    stage1 = new AllReduce(latency, bandwidth / _coe_of_intra_group_bw, computeCost, numOfBytesTrans, _group_size, pipelineStage, overlap_coeff);
    CommOp * stage2 = NULL;
    stage2 = new AllReduce(latency, bandwidth, computeCost, numOfBytesTrans, numOfProcess / _group_size, pipelineStage, overlap_coeff);
    CommOp * stage3 = NULL;
    stage3 = new AllReduce(latency, bandwidth / _coe_of_intra_group_bw, computeCost, numOfBytesTrans, numOfProcess, pipelineStage, overlap_coeff);
    double optimized_tree_allreduc_inter = stage1->ring() + stage2->tree();
    double optimized_tree_allreduce_intra = stage3->tree();
    delete stage1;
    delete stage2;
    delete stage3;
    if(numOfProcess > 8)
    {
        return optimized_tree_allreduc_inter;
    }
    else
    {
        return optimized_tree_allreduce_intra;
    }
}



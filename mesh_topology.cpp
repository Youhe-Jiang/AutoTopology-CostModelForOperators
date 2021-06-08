#include "mesh_topology.h"
#include <math.h>
double coe_of_intra_group_bw_ = 10;
double group_size_ = 8;

double Mesh(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    stage1 = new AllReduce(latency, bandwidth * 2, computeCost * 2, numOfBytesTrans / 2, sqrt(numOfProcess), pipelineStage, overlap_coeff);
    CommOp * stage2 = NULL;
    stage2 = new AllReduce(latency, bandwidth * 2, computeCost * 2, numOfBytesTrans / 2, sqrt(numOfProcess), pipelineStage, overlap_coeff);
    CommOp * stage3 = NULL;
    stage3 = new AllReduce(latency, (bandwidth * 2) / coe_of_intra_group_bw_, computeCost * 2, numOfBytesTrans / 2, sqrt(numOfProcess), pipelineStage, overlap_coeff);
    CommOp * stage4 = NULL;
    stage4 = new AllReduce(latency, (bandwidth * 2) / coe_of_intra_group_bw_, computeCost * 2, numOfBytesTrans / 2, sqrt(numOfProcess), pipelineStage, overlap_coeff);
    double mesh_allreduce_inter = stage1->ring() + stage2->ring();
    double mesh_allreduce_intra = stage3->ring() + stage4->ring();
    delete stage1;
    delete stage2;
    delete stage3;
    delete stage4;
    if(numOfProcess > 8)
    {
        return mesh_allreduce_inter;
    }
    else
    {
        return mesh_allreduce_intra;
    }
}

double HierarchicalMesh(double latency, double bandwidth, double computeCost, double numOfBytesTrans, double numOfProcess, double pipelineStage, double overlap_coeff)
{
    CommOp * stage1 = NULL;
    stage1 = new Reduce(latency, bandwidth / coe_of_intra_group_bw_, computeCost, numOfBytesTrans, group_size_, pipelineStage, overlap_coeff);
    CommOp * stage2 = NULL;
    stage2 = new AllReduce(latency, bandwidth * 2, computeCost * 2, numOfBytesTrans / 2, sqrt(numOfProcess / group_size_), pipelineStage, overlap_coeff);
    CommOp * stage3 = NULL;
    stage3 = new Broadcast(latency, bandwidth / coe_of_intra_group_bw_, computeCost, numOfBytesTrans, group_size_, pipelineStage, overlap_coeff);
    CommOp * stage4 = NULL;
    stage4 = new ReduceScatter(latency, bandwidth / coe_of_intra_group_bw_, computeCost, numOfBytesTrans, group_size_, pipelineStage, overlap_coeff);
    CommOp * stage5 = NULL;
    stage5 = new AllReduce(latency, bandwidth * 2, computeCost * 2, numOfBytesTrans / 2, sqrt(numOfProcess / group_size_), pipelineStage, overlap_coeff);
    CommOp * stage6 = NULL;
    stage6 = new AllGather(latency, bandwidth / coe_of_intra_group_bw_, computeCost, numOfBytesTrans, group_size_, pipelineStage, overlap_coeff);
    double mesh_allreduce_latency_optimal = stage1->ring() + stage2->ring() + stage3->ring();
    double mesh_allreduce_bandwidth_optimal = stage4->ring() + stage5->ring() + stage6->ring();
    if (mesh_allreduce_bandwidth_optimal < mesh_allreduce_latency_optimal)
    {
        delete stage1;
        delete stage2;
        delete stage3;
        return mesh_allreduce_bandwidth_optimal;
    }
    else
    {
        delete stage1;
        delete stage2;
        delete stage3;
        return mesh_allreduce_latency_optimal;
    }

}
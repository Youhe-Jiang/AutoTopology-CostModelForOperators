#include "commOp.h"
#include "reduce.h"
#include "all_reduce.h"
#include "all_gather.h"
#include "reduce_scatter.h"
#include "broadcast.h"

double TreeAllreduce(double latency,
                     double bandwidth,
                     double computeCost,
                     double numOfBytesTrans,
                     double numOfProcess,
                     double pipelineStage,
                     double overlap_coeff);

double OptimizedTreeAllreduce(double latency,
                              double bandwidth,
                              double computeCost,
                              double numOfBytesTrans,
                              double numOfProcess,
                              double pipelineStage,
                              double overlap_coeff);

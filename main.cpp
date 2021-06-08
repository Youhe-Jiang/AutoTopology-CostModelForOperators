#include <iostream>
using namespace std;
#include "ring_topology.h"
#include "mesh_topology.h"
#include "tree_topology.h"
#include <fstream>
#define  FILENAME "data.txt"


int main()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    double a = 0.1; //latency
    double b = 0.5E-6; //bandwidth
    double r = 0.5E-6; //computation cost
    double n = 1E6; //number of bytes transferred
    double p = 32; //number of process
    double s = 100; //split data into s messages
    double o = 0.3; // overlap factor (where overlap factor equals to 0.3 means 30% of the computation and communication are overlapped)
    double ring_allreduce = RingAllreduce(a, b, r, n, p, s, o);
    double hierarchical_allreduce = HierarchicalAllreduce(a, b, r, n, p, s, o);
    double torus_allreduce = TorusAllreduce(a, b, r, n, p, s, o);
    double mesh_allreduce = Mesh(a, b, r, n, p, s, o);
    double hierarchical_mesh_allreduce = HierarchicalMesh(a, b, r, n, p, s, o);
    double tree_allreduce = TreeAllreduce(a, b, r, n, p, s, o);
    ofs.close();

}
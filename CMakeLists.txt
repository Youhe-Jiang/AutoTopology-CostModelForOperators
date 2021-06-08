cmake_minimum_required(VERSION 3.15)
project(AutoTopology)

set(CMAKE_CXX_STANDARD 14)

add_executable(AutoTopology main.cpp commOp.cpp commOp.h reduce.h reduce.cpp broadcast.cpp broadcast.h reduce_scatter.cpp reduce_scatter.h all_gather.cpp all_gather.h all_reduce.cpp all_reduce.h ring_topology.h ring_topology.cpp mesh_topology.h mesh_topology.cpp tree_topology.cpp tree_topology.h)
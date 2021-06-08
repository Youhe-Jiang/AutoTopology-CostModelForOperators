# AutoTopology-CostModelForOperators
Modeling and simulating experiments on communication and computing costs.

Having multiple senders and receivers compounds communication inefficiencies.

For small transfers, latencies dominate; more participants increase latency.

For large transfers, bandwidth is key; bottlenecks are easily exposed.

Thus, topology-aware implementation for high performance is necessary.

Btw, collectives are often non-overlapped, but computation and communication are not.

Topologies can be complex, where not every system is a fat tree, there are ring topology and mesh topology as well.

Communication algorithms are topology-dependent.

Most collectives amenable to bandwidth-optimal implementation on rings, and many topologies can be interpreted as one or more rings [P. Patarasuk and X. Yuan].

In this experiment, the delay, bandwidth, and calculation of multiple communication operators are modelled, including reduce, broadcast, reduce-scatter, all-gather, all-reduce and etc. 

On the basis, several factors have been considered:

The bandwidth difference between intra machine and inter machine.

The operator complexity of different topological structures.

The overlap of communication and computation.

The picture is a brief introduction.

<img width="829" alt="图片" src="https://user-images.githubusercontent.com/85312798/121153832-fcedb680-c878-11eb-9cdc-f6e32012f5f3.png">

Our modeling of the operator is shown in the table. 

α: latency 

β: bandwidth 

γ: computation cost 

n: number of bytes transferred 

p: number of process 

s: split data into s messages)

<img width="1028" alt="图片" src="https://user-images.githubusercontent.com/85312798/121153346-8f418a80-c878-11eb-8d7f-4813265eb79c.png">

Different frameworks support different operators, as shown in the table.

<img width="1054" alt="图片" src="https://user-images.githubusercontent.com/85312798/121154587-a7fe7000-c879-11eb-92f0-7a83dc809e4b.png">

The types of operators that constitute different synchronization algorithms are different, as shown in the table. 

i: intra group -> bandwidth β

o: inter group -> bandwidth β'

For ring topology:

<img width="1030" alt="图片" src="https://user-images.githubusercontent.com/85312798/121154956-f57add00-c879-11eb-8a7e-2959e9bac0c3.png">

For mesh topology:

<img width="1026" alt="图片" src="https://user-images.githubusercontent.com/85312798/121155150-22c78b00-c87a-11eb-9079-d5656b8be056.png">

For tree topology:

<img width="1023" alt="图片" src="https://user-images.githubusercontent.com/85312798/121155240-3541c480-c87a-11eb-8bbb-050e333f8b67.png">

And in our model, communication and computation overlap has also been considered.

If the overlapping of communication and calculation is considered, the optimal situation is that the communication time is less than the calculation time (completely overlapping), then the cost model of each formula can be rewrite as:

cost=max((α,β),γ)

If not ideal, an overlap factor δ is required:

δ=(α,β)⊓γ

cost=(α,β)+γ-δ



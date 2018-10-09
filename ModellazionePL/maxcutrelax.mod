param N; #number of vertices
param edges; #number of edges;
set n := 1..N; #set of vertices;
set E within {n,n};#within n cross n; set of edges
param w{E};

var xu {n} >= 0;
var yuv {E} >= 0;


maximize cut: sum {(u,v) in E} yuv[u,v]*w[u,v];

subjto xor1 {(u,v) in E}: -yuv[u,v] + xu[u] - xu[v] <= 0;
subjto xor2 {(u,v) in E}: -yuv[u,v] + xu[v] - xu[u] <= 0;
subjto xor3 {(u,v) in E}: yuv[u,v] + xu[u] + xu[v]<= 2 ;
subjto xor4 {(u,v) in E}: yuv[u,v] - xu[u] - xu[v] <= 0;

#!/usr/bin/env bash
rm -f rq2_002.csv rq2_003.csv rq2_004.csv rq2_005.csv

bin/rq2 -r exps/002/coverages/gwplus_gwplus_vertex_100_vertex.txt -s exps/002/coverages/gwplus_dj_vertex_100_vertex.txt -s exps/002/coverages/graphwalker_random_vertex_coverage_100_*_vertex.txt -s exps/002/coverages/graphwalker_quick_random_vertex_coverage_100_*_vertex.txt -a -o rq2_002.csv
bin/rq2 -r exps/002/coverages/gwplus_gwplus_edge_100_edge.txt -s exps/002/coverages/gwplus_dj_edge_100_edge.txt -s exps/002/coverages/graphwalker_random_edge_coverage_100_*_edge.txt -s exps/002/coverages/graphwalker_quick_random_edge_coverage_100_*_edge.txt -a -o rq2_002.csv
bin/rq2 -r exps/002/coverages/gwplus_gwplus_edgepair_100_edgepair.txt -s exps/002/coverages/gwplus_dj_edgepair_100_edgepair.txt -a -o rq2_002.csv

bin/rq2 -r exps/003/coverages/gwplus_gwplus_vertex_100_vertex.txt -s exps/003/coverages/gwplus_dj_vertex_100_vertex.txt -s exps/003/coverages/graphwalker_random_vertex_coverage_100_*_vertex.txt -s exps/003/coverages/graphwalker_quick_random_vertex_coverage_100_*_vertex.txt -a -o rq2_003.csv
bin/rq2 -r exps/003/coverages/gwplus_gwplus_edge_100_edge.txt -s exps/003/coverages/gwplus_dj_edge_100_edge.txt -s exps/003/coverages/graphwalker_random_edge_coverage_100_*_edge.txt -s exps/003/coverages/graphwalker_quick_random_edge_coverage_100_*_edge.txt -a -o rq2_003.csv
bin/rq2 -r exps/003/coverages/gwplus_gwplus_edgepair_100_edgepair.txt -s exps/003/coverages/gwplus_dj_edgepair_100_edgepair.txt -a -o rq2_003.csv

bin/rq2 -r exps/004/coverages/gwplus_gwplus_vertex_100_vertex.txt -s exps/004/coverages/gwplus_dj_vertex_100_vertex.txt -s exps/004/coverages/graphwalker_random_vertex_coverage_100_*_vertex.txt -s exps/004/coverages/graphwalker_quick_random_vertex_coverage_100_*_vertex.txt -a -o rq2_004.csv
bin/rq2 -r exps/004/coverages/gwplus_gwplus_edge_100_edge.txt -s exps/004/coverages/gwplus_dj_edge_100_edge.txt -s exps/004/coverages/graphwalker_random_edge_coverage_100_*_edge.txt -s exps/004/coverages/graphwalker_quick_random_edge_coverage_100_*_edge.txt -a -o rq2_004.csv
bin/rq2 -r exps/004/coverages/gwplus_gwplus_edgepair_100_edgepair.txt -s exps/004/coverages/gwplus_dj_edgepair_100_edgepair.txt -a -o rq2_004.csv

bin/rq2 -r exps/005/coverages/gwplus_gwplus_vertex_100_vertex.txt -s exps/005/coverages/gwplus_dj_vertex_100_vertex.txt -s exps/005/coverages/graphwalker_random_vertex_coverage_100_*_vertex.txt -s exps/005/coverages/graphwalker_quick_random_vertex_coverage_100_*_vertex.txt -a -o rq2_005.csv
bin/rq2 -r exps/005/coverages/gwplus_gwplus_edge_100_edge.txt -s exps/005/coverages/gwplus_dj_edge_100_edge.txt -s exps/005/coverages/graphwalker_random_edge_coverage_100_*_edge.txt -s exps/005/coverages/graphwalker_quick_random_edge_coverage_100_*_edge.txt -a -o rq2_005.csv
bin/rq2 -r exps/005/coverages/gwplus_gwplus_edgepair_100_edgepair.txt -s exps/005/coverages/gwplus_dj_edgepair_100_edgepair.txt -a -o rq2_005.csv

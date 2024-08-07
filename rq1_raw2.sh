#!/usr/bin/env bash

MODELS="002 003 004 005"

echo "Model,Tool,Method,Target Coverage,Ratio,Seed,i,minlen,multiplier" > rq1_raw.csv

for model in ${MODELS}
do
    minlen_vertex_50=100000
    minlen_vertex_60=100000
    minlen_vertex_70=100000
    minlen_vertex_80=100000
    minlen_vertex_90=100000
    minlen_vertex_100=100000
    minlen_edge_50=100000
    minlen_edge_60=100000
    minlen_edge_70=100000
    minlen_edge_80=100000
    minlen_edge_90=100000
    minlen_edge_100=100000
    minlen_edgepair_50=100000
    minlen_edgepair_60=100000
    minlen_edgepair_70=100000
    minlen_edgepair_80=100000
    minlen_edgepair_90=100000
    minlen_edgepair_100=100000

    while IFS="," read -r mid tool method tcov ratio seed i nsymbols len tm vcov ecov epc etc pvp pep
    do
        if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
        then
            if [[ $ratio -eq 50 ]]
            then
                if [[ ${minlen_vertex_50} -gt $len ]]; then minlen_vertex_50=$((len)); fi
            elif [[ $ratio -eq 60 ]]
            then
                if [[ ${minlen_vertex_60} -gt $len ]]; then minlen_vertex_60=$((len)); fi
            elif [[ $ratio -eq 70 ]]
            then
                if [[ ${minlen_vertex_70} -gt $len ]]; then minlen_vertex_70=$((len)); fi
            elif [[ $ratio -eq 80 ]]
            then
                if [[ ${minlen_vertex_80} -gt $len ]]; then minlen_vertex_80=$((len)); fi
            elif [[ $ratio -eq 90 ]]
            then
                if [[ ${minlen_vertex_90} -gt $len ]]; then minlen_vertex_90=$((len)); fi
            elif [[ $ratio -eq 100 ]]
            then
                if [[ ${minlen_vertex_100} -gt $len ]]; then minlen_vertex_100=$((len)); fi
            fi
        elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
        then
            if [[ $ratio -eq 50 ]]
            then
                if [[ ${minlen_edge_50} -gt $len ]]; then minlen_edge_50=$((len)); fi
            elif [[ $ratio -eq 60 ]]
            then
                if [[ ${minlen_edge_60} -gt $len ]]; then minlen_edge_60=$((len)); fi
            elif [[ $ratio -eq 70 ]]
            then
                if [[ ${minlen_edge_70} -gt $len ]]; then minlen_edge_70=$((len)); fi
            elif [[ $ratio -eq 80 ]]
            then
                if [[ ${minlen_edge_80} -gt $len ]]; then minlen_edge_80=$((len)); fi
            elif [[ $ratio -eq 90 ]]
            then
                if [[ ${minlen_edge_90} -gt $len ]]; then minlen_edge_90=$((len)); fi
            elif [[ $ratio -eq 100 ]]
            then
                if [[ ${minlen_edge_100} -gt $len ]]; then minlen_edge_100=$((len)); fi
            fi
        else
            if [[ $ratio -eq 50 ]]
            then
                if [[ ${minlen_edgepair_50} -gt $len ]]; then minlen_edgepair_50=$((len)); fi
            elif [[ $ratio -eq 60 ]]
            then
                if [[ ${minlen_edgepair_60} -gt $len ]]; then minlen_edgepair_60=$((len)); fi
            elif [[ $ratio -eq 70 ]]
            then
                if [[ ${minlen_edgepair_70} -gt $len ]]; then minlen_edgepair_70=$((len)); fi
            elif [[ $ratio -eq 80 ]]
            then
                if [[ ${minlen_edgepair_80} -gt $len ]]; then minlen_edgepair_80=$((len)); fi
            elif [[ $ratio -eq 90 ]]
            then
                if [[ ${minlen_edgepair_90} -gt $len ]]; then minlen_edgepair_90=$((len)); fi
            elif [[ $ratio -eq 100 ]]
            then
                if [[ ${minlen_edgepair_100} -gt $len ]]; then minlen_edgepair_100=$((len)); fi
            fi
        fi
    done < <(tail -n +2 rq1_${model}.csv)

    while IFS="," read -r mid tool method tcov ratio seed i nsymbols len tm vcov ecov epc etc pvp pep
    do
        echo -n "${mid},${tool},${method},${tcov},${ratio},${seed},${i}," >> rq1_raw.csv
        if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
        then
            if [[ $ratio -eq 50 ]]
            then
                x=$(jq -n ${len}/${minlen_vertex_50})
                echo "${minlen_vertex_50},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 60 ]]
            then
                x=$(jq -n ${len}/${minlen_vertex_60})
                echo "${minlen_vertex_60},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 70 ]]
            then
                x=$(jq -n ${len}/${minlen_vertex_70})
                echo "${minlen_vertex_70},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 80 ]]
            then
                x=$(jq -n ${len}/${minlen_vertex_80})
                echo "${minlen_vertex_80},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 90 ]]
            then
                x=$(jq -n ${len}/${minlen_vertex_90})
                echo "${minlen_vertex_90},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 100 ]]
            then
                x=$(jq -n ${len}/${minlen_vertex_100})
                echo "${minlen_vertex_100},${x}" >> rq1_raw.csv
            fi
        elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
        then
            if [[ $ratio -eq 50 ]]
            then
                x=$(jq -n ${len}/${minlen_edge_50})
                echo "${minlen_edge_50},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 60 ]]
            then
                x=$(jq -n ${len}/${minlen_edge_60})
                echo "${minlen_edge_60},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 70 ]]
            then
                x=$(jq -n ${len}/${minlen_edge_70})
                echo "${minlen_edge_70},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 80 ]]
            then
                x=$(jq -n ${len}/${minlen_edge_80})
                echo "${minlen_edge_80},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 90 ]]
            then
                x=$(jq -n ${len}/${minlen_edge_90})
                echo "${minlen_edge_90},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 100 ]]
            then
                x=$(jq -n ${len}/${minlen_edge_100})
                echo "${minlen_edge_100},${x}" >> rq1_raw.csv
            fi
        else
            if [[ $ratio -eq 50 ]]
            then
                x=$(jq -n ${len}/${minlen_edgepair_50})
                echo "${minlen_edgepair_50},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 60 ]]
            then
                x=$(jq -n ${len}/${minlen_edgepair_60})
                echo "${minlen_edgepair_60},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 70 ]]
            then
                x=$(jq -n ${len}/${minlen_edgepair_70})
                echo "${minlen_edgepair_70},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 80 ]]
            then
                x=$(jq -n ${len}/${minlen_edgepair_80})
                echo "${minlen_edgepair_80},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 90 ]]
            then
                x=$(jq -n ${len}/${minlen_edgepair_90})
                echo "${minlen_edgepair_90},${x}" >> rq1_raw.csv
            elif [[ $ratio -eq 100 ]]
            then
                x=$(jq -n ${len}/${minlen_edgepair_100})
                echo "${minlen_edgepair_100},${x}" >> rq1_raw.csv
            fi
        fi
    done < <(tail -n +2 rq1_${model}.csv)
done

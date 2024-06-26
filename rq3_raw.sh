#!/usr/bin/env bash
EXPS="exps"
GW_METHODS="random quick_random"
GW_COVERAGES="vertex_coverage edge_coverage"
GW_RATIOS="100 90 80 70 60 50"
GW_SEEDS="172062 512956 210987 772120 832513 76219 132921 114702 805553 432487 971148 366466 453649 735972 982676 375208 306259 177328 666177 108218 118894 835003 190598 980472 578073 104881 325629 980737 506544 268475"
GWPLUS_COVERAGES="vertex edge edgepair"
ALL_COVERAGES="vertex edge edgepair edgetriple prime1 prime2"
MODELS="005"
NREPEATS=1

NSEEDS=0
for seed in ${GW_SEEDS}
do
    ((NSEEDS++))
done
echo "# SEEDS = ${NSEEDS}"

for model in ${MODELS}
do
    for targetcoverage in ${GWPLUS_COVERAGES}
    do
        for ratio in ${GW_RATIOS}
        do
            for coverage in ${ALL_COVERAGES}
            do
                bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -m ${EXPS}/${model}/generated/gwplus_${targetcoverage}_${ratio}.txt > ${EXPS}/${model}/coverages/gwplus_${targetcoverage}_${ratio}_${coverage}.txt
                echo "bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -m ${EXPS}/${model}/generated/gwplus_${targetcoverage}_${ratio}.txt > ${EXPS}/${model}/coverages/gwplus_${targetcoverage}_${ratio}_${coverage}.txt"
            done
        done
    done

    for method in ${GW_METHODS}
    do
        for targetcoverage in ${GW_COVERAGES}
        do
            for ratio in ${GW_RATIOS}
            do
                for seed in ${GW_SEEDS}
                do
                    for coverage in ${ALL_COVERAGES}
                    do
                        bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -m ${EXPS}/${model}/generated/graphwalker_${method}_${targetcoverage}_${ratio}_${seed}.txt > ${EXPS}/${model}/coverages/graphwalker_${method}_${targetcoverage}_${ratio}_${seed}_${coverage}.txt
                        echo "bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -m ${EXPS}/${model}/generated/graphwalker_${method}_${targetcoverage}_${ratio}_${seed}.txt > ${EXPS}/${model}/coverages/graphwalker_${method}_${targetcoverage}_${ratio}_${seed}_${coverage}.txt"
                    done
                done
            done
        done
    done
done

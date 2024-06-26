#!/usr/bin/env bash
EXPS="exps"
GW_METHODS="random quick_random"
GW_COVERAGES="vertex_coverage edge_coverage"
GW_RATIOS="100 90 80 70 60 50"
GW_SEEDS="172062 512956 210987 772120 832513 76219 132921 114702 805553 432487 971148 366466 453649 735972 982676 375208 306259 177328 666177 108218 118894 835003 190598 980472 578073 104881 325629 980737 506544 268475"
GWPLUS_COVERAGES="vertex edge edgepair"
MODELS="002"

NSEEDS=0
for seed in ${GW_SEEDS}
do
    ((NSEEDS++))
done
echo "# SEEDS = ${NSEEDS}"

for model in ${MODELS}
do
    for coverage in ${GWPLUS_COVERAGES}
    do
        for ratio in ${GW_RATIOS}
        do
            echo "bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -t ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}.json ${ratio}"
            bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -t ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}.json ${ratio}

            echo "java -jar graphwalker-cli-4.3.2.jar offline -o -m \"${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}.json\" \"predefined_path(predefined_path)\" | jq -r '.currentElementID' > ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}.txt"
            java -jar graphwalker-cli-4.3.2.jar offline -o -m "${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}.json" "predefined_path(predefined_path)" | jq -r '.currentElementID' > ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}.txt
        done
    done

    for method in ${GW_METHODS}
    do
        for coverage in ${GW_COVERAGES}
        do
            for ratio in ${GW_RATIOS}
            do
                for seed in ${GW_SEEDS}
                do
                    echo "java -jar graphwalker-cli-4.3.2.jar offline -o -d ${seed} -m \"${EXPS}/${model}/m.json\" \"${method}(${coverage}($ratio))\" | jq -r '.currentElementID' > ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}.txt"
                    java -jar graphwalker-cli-4.3.2.jar offline -o -d ${seed} -m "${EXPS}/${model}/m.json" "${method}(${coverage}($ratio))" | jq -r '.currentElementID' > ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}.txt
                done
            done
        done
    done
done

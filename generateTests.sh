#!/usr/bin/env bash
EXPS="exps"
GW_METHODS="random quick_random"
GW_COVERAGES="vertex_coverage edge_coverage"
GW_RATIOS="100 90 80 70 60 50"
GW_SEEDS="172062 512956 210987 772120 832513 76219 132921 114702 805553 432487 971148 366466 453649 735972 982676 375208 306259 177328 666177 108218 118894 835003 190598 980472 578073 104881 325629 980737 506544 268475"
GWPLUS_METHODS="gwplus dj"
GWPLUS_COVERAGES="vertex edge edgepair"
MODELS="002 003 004 005"

NSEEDS=0
for seed in ${GW_SEEDS}
do
    ((NSEEDS++))
done
echo "# SEEDS = ${NSEEDS}"

for model in ${MODELS}
do
    for method in ${GWPLUS_METHODS}
    do
        for coverage in ${GWPLUS_COVERAGES}
        do
            for ratio in ${GW_RATIOS}
            do
                echo "bin/gwplus -i ${EXPS}/${model}/m.json ${method} -c ${coverage} --${method} -t ${EXPS}/${model}/generated/gwplus_${method}_${coverage}_${ratio}.json ${ratio}"
                bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} --${method} -t ${EXPS}/${model}/generated/gwplus_${method}_${coverage}_${ratio}.json ${ratio}

                for jsn in ${EXPS}/${model}/generated/gwplus_${method}_${coverage}_${ratio}*.json
                do
                    test=${jsn%.json}
                    echo "java -jar graphwalker-cli-4.3.2.jar offline -o -m \"${jsn}\" \"predefined_path(predefined_path)\" | jq -r '.currentElementID' > ${test}.txt"
                    java -jar graphwalker-cli-4.3.2.jar offline -o -m "${jsn}" "predefined_path(predefined_path)" | jq -r '.currentElementID' > ${test}.txt
                done
            done
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

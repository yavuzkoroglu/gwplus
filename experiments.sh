#!/usr/bin/env bash
EXPS="exps"
GW_METHODS="random quick_random"
GW_COVERAGES="vertex_coverage edge_coverage"
GW_RATIOS="100 90 80 70 60 50"
GW_SEEDS="172062 512956 210987 772120 832513 76219 132921 114702 805553 432487 971148 366466 453649 735972 982676 375208 306259 177328 666177 108218 118894 835003 190598 980472 578073 104881 325629 980737 506544 268475"
GWPLUS_COVERAGES="vertex edge edgepair"
MODELS="005"
NREPEATS=1

NSEEDS=0
for seed in ${GW_SEEDS}
do
    ((NSEEDS++))
done
echo "# SEEDS   = ${NSEEDS}"
echo "# REPEATS = ${NREPEATS}"

for model in ${MODELS}
do
    echo "Model,Tool,Method,Target Coverage,Ratio,Seed,i,#symbols,Test Length (#edges),Test Generation Time (milliseconds),Vertex Coverage,Edge Coverage,Edge Pair Coverage,Edge Triple Coverage,Prime Vertex Path Coverage,Prime Edge Path Coverage" > ${EXPS}/${model}/generated/results.csv

    for coverage in ${GWPLUS_COVERAGES}
    do
        for ratio in ${GW_RATIOS}
        do
            for i in $(seq ${NREPEATS})
            do
                start=$(gdate +%s%N)
                bin/gwplus -i ${EXPS}/${model}/m.json -c ${coverage} -t ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.json ${ratio}
                java -jar graphwalker-cli-4.3.2.jar offline -o -m "${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.json" "predefined_path(predefined_path)" | jq -r '.currentElementID' > ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt
                end=$(gdate +%s%N)

                len=$(cat ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | wc -l)

                vcov=$(bin/gwplus -i ${EXPS}/${model}/m.json -c vertex -m ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | grep '%' | tr -d '%')
                ecov=$(bin/gwplus -i ${EXPS}/${model}/m.json -c edge -m ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | grep '%' | tr -d '%')
                epc=$(bin/gwplus -i ${EXPS}/${model}/m.json -c edgepair -m ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | grep '%' | tr -d '%')
                etc=$(bin/gwplus -i ${EXPS}/${model}/m.json -c edgetriple -m ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | grep '%' | tr -d '%')
                pvp=$(bin/gwplus -i ${EXPS}/${model}/m.json -c prime1 -m ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | grep '%' | tr -d '%')
                pep=$(bin/gwplus -i ${EXPS}/${model}/m.json -c prime2 -m ${EXPS}/${model}/generated/gwplus_${coverage}_${ratio}_${i}.txt | grep '%' | tr -d '%')

                ((symbols=len))
                ((len=len/2))

                tm=$((${end}-${start}))
                ((tm=tm/1000000))

                echo "${model},GWPlus,NA,${coverage},${ratio},NA,${i},${symbols},${len},${tm},${vcov},${ecov},${epc},${etc},${pvp},${pep}" >> ${EXPS}/${model}/generated/results.csv
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
                    for i in $(seq ${NREPEATS})
                    do
                        start=$(gdate +%s%N)
                        java -jar graphwalker-cli-4.3.2.jar offline -o -d ${seed} -m "${EXPS}/${model}/m.json" "${method}(${coverage}(${ratio}))" | jq -r '.currentElementID' > ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt
                        end=$(gdate +%s%N)

                        len=$(cat ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | wc -l)

                        vcov=$(bin/gwplus -i ${EXPS}/${model}/m.json -c vertex -m ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | grep '%' | tr -d '%')
                        ecov=$(bin/gwplus -i ${EXPS}/${model}/m.json -c edge -m ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | grep '%' | tr -d '%')
                        epc=$(bin/gwplus -i ${EXPS}/${model}/m.json -c edgepair -m ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | grep '%' | tr -d '%')
                        etc=$(bin/gwplus -i ${EXPS}/${model}/m.json -c edgetriple -m ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | grep '%' | tr -d '%')
                        pvp=$(bin/gwplus -i ${EXPS}/${model}/m.json -c prime1 -m ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | grep '%' | tr -d '%')
                        pep=$(bin/gwplus -i ${EXPS}/${model}/m.json -c prime2 -m ${EXPS}/${model}/generated/graphwalker_${method}_${coverage}_${ratio}_${seed}_${i}.txt | grep '%' | tr -d '%')

                        ((symbols=len))
                        ((len=len/2))

                        tm=$((${end}-${start}))
                        ((tm=tm/1000000))

                        echo "${model},GraphWalker,${method},${coverage},${ratio},${seed},${i},${symbols},${len},${tm},${vcov},${ecov},${epc},${etc},${pvp},${pep}" >> ${EXPS}/${model}/generated/results.csv
                    done
                done
            done
        done
    done
done

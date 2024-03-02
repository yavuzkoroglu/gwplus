#!/usr/bin/env bash
GW_COVERAGES="vertex_coverage edge_coverage"
GW_RATIOS="100 90 80 70 60 50"
GW_SEEDS="172062 512956 210987 772120 832513 76219 132921 114702 805553 432487 971148 366466 453649 735972 982676 375208 306259 177328 666177 108218 118894 835003 190598 980472 578073 104881 325629 980737 506544 268475"
GWPLUS_COVERAGES="vertex edge prime"
MODELS="toygraph tlc"

NSEEDS=0
for seed in $GW_SEEDS
do
    ((NSEEDS++))
done
echo "# SEEDS   = $NSEEDS"

for model in $MODELS
do
    for coverage in $GWPLUS_COVERAGES
    do
        bin/gwplus $coverage experiments/$model/model.json experiments/$model/gwplus_$coverage.json
        java -jar graphwalker-cli-4.3.2.jar offline -m "experiments/$model/gwplus_$coverage.json" "predefined_path(predefined_path)" > tests/$model/gwplus_${coverage}.txt
    done

    for coverage in $GW_COVERAGES
    do
        for ratio in $GW_RATIOS
        do
            for seed in $GW_SEEDS
            do
                java -jar graphwalker-cli-4.3.2.jar offline -d $seed -m "experiments/$model/model.json" "random(${coverage}($ratio))" > tests/$model/graphwalker_${coverage}_${ratio}_seed_${seed}.txt
            done
        done
    done
done

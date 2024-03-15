#!/usr/bin/env bash
EXPS="exps"
GW_METHODS="random quick_random"
GW_COVERAGES="vertex_coverage edge_coverage"
GW_RATIOS="100 90 80 70 60 50"
GW_SEEDS="172062 512956 210987 772120 832513 76219 132921 114702 805553 432487 971148 366466 453649 735972 982676 375208 306259 177328 666177 108218 118894 835003 190598 980472 578073 104881 325629 980737 506544 268475"
GWPLUS_COVERAGES="vertex edge edgepair prime1 prime2 prime3"
MODELS="001 002 003"
NREPEATS=1

NSEEDS=0
for seed in $GW_SEEDS
do
    ((NSEEDS++))
done
echo "# SEEDS   = $NSEEDS"
echo "# REPEATS = $NREPEATS"

for model in $MODELS
do
    echo "Model,Tool,Method,Coverage,Ratio,Seed,i,Test Length (#edges),Test Generation Time (milliseconds)" > $EXPS/$model/results.csv

    for coverage in $GWPLUS_COVERAGES
    do
        for i in $(seq $NREPEATS)
        do
            start=$(gdate +%s%N)
            bin/gwplus -i $EXPS/$model/m.json -c $coverage -t $EXPS/$model/tests/gwplus_$coverage.json
            len=$(java -jar graphwalker-cli-4.3.2.jar offline -m "$EXPS/$model/tests/gwplus_$coverage.json" "predefined_path(predefined_path)" | wc -l)
            end=$(gdate +%s%N)
            ((len=len/2 - 1))
            tm=$(($end-$start))
            ((tm=tm/1000000))

            echo "$model,GWPlus,NA,$coverage,100,0,$i,$len,$tm" >> $EXPS/$model/results.csv
        done
    done

    for method in $GW_METHODS
    do
        for coverage in $GW_COVERAGES
        do
            for ratio in $GW_RATIOS
            do
                for seed in $GW_SEEDS
                do
                    for i in $(seq $NREPEATS)
                    do
                        start=$(gdate +%s%N)
                        len=$(java -jar graphwalker-cli-4.3.2.jar offline -d $seed -m "$EXPS/$model/m.json" "$method(${coverage}($ratio))" | wc -l)
                        end=$(gdate +%s%N)

                        ((len=len/2))
                        tm=$(($end-$start))
                        ((tm=tm/1000000))
                        echo "$model,GraphWalker,$method,$coverage,$ratio,$seed,$i,$len,$tm" >> $EXPS/$model/results.csv
                    done
                done
            done
        done
    done
done

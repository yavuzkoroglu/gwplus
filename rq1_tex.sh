#!/usr/bin/env bash

echo '\documentclass[varwidth=17cm]{standalone}' > rq1.tex
echo '\usepackage{amsmath}' >> rq1.tex
echo '\usepackage{pgfplots}' >> rq1.tex
echo '\usepackage{pgfplotstable}' >> rq1.tex
echo '\pgfplotsset{compat=1.8}' >> rq1.tex
echo '\usepgfplotslibrary{statistics}' >> rq1.tex
echo '\pgfplotsset{' >> rq1.tex
echo '    boxplot/draw/median/.code={' >> rq1.tex
echo '        \draw [/pgfplots/boxplot/every median/.try]' >> rq1.tex
echo '            (boxplot box cs:\pgfplotsboxplotvalue{median},0)' >> rq1.tex
echo '            --' >> rq1.tex
echo '            node[] {\tiny\textbullet}' >> rq1.tex
echo '            (boxplot box cs:\pgfplotsboxplotvalue{median},1);' >> rq1.tex
echo '    },' >> rq1.tex
echo '}' >> rq1.tex
echo '' >> rq1.tex

tlcvertex50min=100000
tlcvertex60min=100000
tlcvertex70min=100000
tlcvertex80min=100000
tlcvertex90min=100000
tlcvertex100min=100000
tlcedge50min=100000
tlcedge60min=100000
tlcedge70min=100000
tlcedge80min=100000
tlcedge90min=100000
tlcedge100min=100000
tlcedgepair50min=100000
tlcedgepair60min=100000
tlcedgepair70min=100000
tlcedgepair80min=100000
tlcedgepair90min=100000
tlcedgepair100min=100000

parabankvertex50min=100000
parabankvertex60min=100000
parabankvertex70min=100000
parabankvertex80min=100000
parabankvertex90min=100000
parabankvertex100min=100000
parabankedge50min=100000
parabankedge60min=100000
parabankedge70min=100000
parabankedge80min=100000
parabankedge90min=100000
parabankedge100min=100000
parabankedgepair50min=100000
parabankedgepair60min=100000
parabankedgepair70min=100000
parabankedgepair80min=100000
parabankedgepair90min=100000
parabankedgepair100min=100000

testiniumvertex50min=100000
testiniumvertex60min=100000
testiniumvertex70min=100000
testiniumvertex80min=100000
testiniumvertex90min=100000
testiniumvertex100min=100000
testiniumedge50min=100000
testiniumedge60min=100000
testiniumedge70min=100000
testiniumedge80min=100000
testiniumedge90min=100000
testiniumedge100min=100000
testiniumedgepair50min=100000
testiniumedgepair60min=100000
testiniumedgepair70min=100000
testiniumedgepair80min=100000
testiniumedgepair90min=100000
testiniumedgepair100min=100000

riscvvertex50min=100000
riscvvertex60min=100000
riscvvertex70min=100000
riscvvertex80min=100000
riscvvertex90min=100000
riscvvertex100min=100000
riscvedge50min=100000
riscvedge60min=100000
riscvedge70min=100000
riscvedge80min=100000
riscvedge90min=100000
riscvedge100min=100000
riscvedgepair50min=100000
riscvedgepair60min=100000
riscvedgepair70min=100000
riscvedgepair80min=100000
riscvedgepair90min=100000
riscvedgepair100min=100000

tlcgwplusvertexfifty=0
tlcgwplusvertexsixty=0
tlcgwplusvertexseventy=0
tlcgwplusvertexeighty=0
tlcgwplusvertexninety=0
tlcgwplusvertexhundred=0
tlcgwplusedgefifty=0
tlcgwplusedgesixty=0
tlcgwplusedgeseventy=0
tlcgwplusedgeeighty=0
tlcgwplusedgeninety=0
tlcgwplusedgehundred=0
tlcgwplusedgepairfifty=0
tlcgwplusedgepairsixty=0
tlcgwplusedgepairseventy=0
tlcgwplusedgepaireighty=0
tlcgwplusedgepairninety=0
tlcgwplusedgepairhundred=0

parabankgwplusvertexfifty=0
parabankgwplusvertexsixty=0
parabankgwplusvertexseventy=0
parabankgwplusvertexeighty=0
parabankgwplusvertexninety=0
parabankgwplusvertexhundred=0
parabankgwplusedgefifty=0
parabankgwplusedgesixty=0
parabankgwplusedgeseventy=0
parabankgwplusedgeeighty=0
parabankgwplusedgeninety=0
parabankgwplusedgehundred=0
parabankgwplusedgepairfifty=0
parabankgwplusedgepairsixty=0
parabankgwplusedgepairseventy=0
parabankgwplusedgepaireighty=0
parabankgwplusedgepairninety=0
parabankgwplusedgepairhundred=0

testiniumgwplusvertexfifty=0
testiniumgwplusvertexsixty=0
testiniumgwplusvertexseventy=0
testiniumgwplusvertexeighty=0
testiniumgwplusvertexninety=0
testiniumgwplusvertexhundred=0
testiniumgwplusedgefifty=0
testiniumgwplusedgesixty=0
testiniumgwplusedgeseventy=0
testiniumgwplusedgeeighty=0
testiniumgwplusedgeninety=0
testiniumgwplusedgehundred=0
testiniumgwplusedgepairfifty=0
testiniumgwplusedgepairsixty=0
testiniumgwplusedgepairseventy=0
testiniumgwplusedgepaireighty=0
testiniumgwplusedgepairninety=0
testiniumgwplusedgepairhundred=0

riscvgwplusvertexfifty=0
riscvgwplusvertexsixty=0
riscvgwplusvertexseventy=0
riscvgwplusvertexeighty=0
riscvgwplusvertexninety=0
riscvgwplusvertexhundred=0
riscvgwplusedgefifty=0
riscvgwplusedgesixty=0
riscvgwplusedgeseventy=0
riscvgwplusedgeeighty=0
riscvgwplusedgeninety=0
riscvgwplusedgehundred=0
riscvgwplusedgepairfifty=0
riscvgwplusedgepairsixty=0
riscvgwplusedgepairseventy=0
riscvgwplusedgepaireighty=0
riscvgwplusedgepairninety=0
riscvgwplusedgepairhundred=0

tlcgwqrandomvertexfifty=()
tlcgwqrandomvertexsixty=()
tlcgwqrandomvertexseventy=()
tlcgwqrandomvertexeighty=()
tlcgwqrandomvertexninety=()
tlcgwqrandomvertexhundred=()
tlcgwqrandomedgefifty=()
tlcgwqrandomedgesixty=()
tlcgwqrandomedgeseventy=()
tlcgwqrandomedgeeighty=()
tlcgwqrandomedgeninety=()
tlcgwqrandomedgehundred=()

parabankgwqrandomvertexfifty=()
parabankgwqrandomvertexsixty=()
parabankgwqrandomvertexseventy=()
parabankgwqrandomvertexeighty=()
parabankgwqrandomvertexninety=()
parabankgwqrandomvertexhundred=()
parabankgwqrandomedgefifty=()
parabankgwqrandomedgesixty=()
parabankgwqrandomedgeseventy=()
parabankgwqrandomedgeeighty=()
parabankgwqrandomedgeninety=()
parabankgwqrandomedgehundred=()

testiniumgwqrandomvertexfifty=()
testiniumgwqrandomvertexsixty=()
testiniumgwqrandomvertexseventy=()
testiniumgwqrandomvertexeighty=()
testiniumgwqrandomvertexninety=()
testiniumgwqrandomvertexhundred=()
testiniumgwqrandomedgefifty=()
testiniumgwqrandomedgesixty=()
testiniumgwqrandomedgeseventy=()
testiniumgwqrandomedgeeighty=()
testiniumgwqrandomedgeninety=()
testiniumgwqrandomedgehundred=()

riscvgwqrandomvertexfifty=()
riscvgwqrandomvertexsixty=()
riscvgwqrandomvertexseventy=()
riscvgwqrandomvertexeighty=()
riscvgwqrandomvertexninety=()
riscvgwqrandomvertexhundred=()
riscvgwqrandomedgefifty=()
riscvgwqrandomedgesixty=()
riscvgwqrandomedgeseventy=()
riscvgwqrandomedgeeighty=()
riscvgwqrandomedgeninety=()
riscvgwqrandomedgehundred=()

tlcdjvertexfifty=0
tlcdjvertexsixty=0
tlcdjvertexseventy=0
tlcdjvertexeighty=0
tlcdjvertexninety=0
tlcdjvertexhundred=0
tlcdjedgefifty=0
tlcdjedgesixty=0
tlcdjedgeseventy=0
tlcdjedgeeighty=0
tlcdjedgeninety=0
tlcdjedgehundred=0
tlcdjedgepairfifty=0
tlcdjedgepairsixty=0
tlcdjedgepairseventy=0
tlcdjedgepaireighty=0
tlcdjedgepairninety=0
tlcdjedgepairhundred=0

parabankdjvertexfifty=0
parabankdjvertexsixty=0
parabankdjvertexseventy=0
parabankdjvertexeighty=0
parabankdjvertexninety=0
parabankdjvertexhundred=0
parabankdjedgefifty=0
parabankdjedgesixty=0
parabankdjedgeseventy=0
parabankdjedgeeighty=0
parabankdjedgeninety=0
parabankdjedgehundred=0
parabankdjedgepairfifty=0
parabankdjedgepairsixty=0
parabankdjedgepairseventy=0
parabankdjedgepaireighty=0
parabankdjedgepairninety=0
parabankdjedgepairhundred=0

testiniumdjvertexfifty=0
testiniumdjvertexsixty=0
testiniumdjvertexseventy=0
testiniumdjvertexeighty=0
testiniumdjvertexninety=0
testiniumdjvertexhundred=0
testiniumdjedgefifty=0
testiniumdjedgesixty=0
testiniumdjedgeseventy=0
testiniumdjedgeeighty=0
testiniumdjedgeninety=0
testiniumdjedgehundred=0
testiniumdjedgepairfifty=0
testiniumdjedgepairsixty=0
testiniumdjedgepairseventy=0
testiniumdjedgepaireighty=0
testiniumdjedgepairninety=0
testiniumdjedgepairhundred=0

riscvdjvertexfifty=0
riscvdjvertexsixty=0
riscvdjvertexseventy=0
riscvdjvertexeighty=0
riscvdjvertexninety=0
riscvdjvertexhundred=0
riscvdjedgefifty=0
riscvdjedgesixty=0
riscvdjedgeseventy=0
riscvdjedgeeighty=0
riscvdjedgeninety=0
riscvdjedgehundred=0
riscvdjedgepairfifty=0
riscvdjedgepairsixty=0
riscvdjedgepairseventy=0
riscvdjedgepaireighty=0
riscvdjedgepairninety=0
riscvdjedgepairhundred=0

tlcgwrandomvertexfifty=()
tlcgwrandomvertexsixty=()
tlcgwrandomvertexseventy=()
tlcgwrandomvertexeighty=()
tlcgwrandomvertexninety=()
tlcgwrandomvertexhundred=()
tlcgwrandomedgefifty=()
tlcgwrandomedgesixty=()
tlcgwrandomedgeseventy=()
tlcgwrandomedgeeighty=()
tlcgwrandomedgeninety=()
tlcgwrandomedgehundred=()

parabankgwrandomvertexfifty=()
parabankgwrandomvertexsixty=()
parabankgwrandomvertexseventy=()
parabankgwrandomvertexeighty=()
parabankgwrandomvertexninety=()
parabankgwrandomvertexhundred=()
parabankgwrandomedgefifty=()
parabankgwrandomedgesixty=()
parabankgwrandomedgeseventy=()
parabankgwrandomedgeeighty=()
parabankgwrandomedgeninety=()
parabankgwrandomedgehundred=()

testiniumgwrandomvertexfifty=()
testiniumgwrandomvertexsixty=()
testiniumgwrandomvertexseventy=()
testiniumgwrandomvertexeighty=()
testiniumgwrandomvertexninety=()
testiniumgwrandomvertexhundred=()
testiniumgwrandomedgefifty=()
testiniumgwrandomedgesixty=()
testiniumgwrandomedgeseventy=()
testiniumgwrandomedgeeighty=()
testiniumgwrandomedgeninety=()
testiniumgwrandomedgehundred=()

riscvgwrandomvertexfifty=()
riscvgwrandomvertexsixty=()
riscvgwrandomvertexseventy=()
riscvgwrandomvertexeighty=()
riscvgwrandomvertexninety=()
riscvgwrandomvertexhundred=()
riscvgwrandomedgefifty=()
riscvgwrandomedgesixty=()
riscvgwrandomedgeseventy=()
riscvgwrandomedgeeighty=()
riscvgwrandomedgeninety=()
riscvgwrandomedgehundred=()

while IFS="," read model tool method tcov ratio seed i minlen mult
do
    if [[ $model == "002" ]]
    then
        if [[ $ratio -eq 50 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                tlcvertex50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusvertexfifty=$mult
                    elif [[ $method == "dj" ]]; then tlcdjvertexfifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomvertexfifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomvertexfifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                tlcedge50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusedgefifty=$mult
                    elif [[ $method == "dj" ]]; then tlcdjedgefifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomedgefifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomedgefifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                tlcedgepair50min=$((minlen))
                if [[ $method == "gwplus" ]]; then tlcgwplusedgepairfifty=$mult
                elif [[ $method == "dj" ]]; then tlcdjedgepairfifty=$mult
                fi
            fi
        elif [[ $ratio -eq 60 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                tlcvertex60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusvertexsixty=$mult
                    elif [[ $method == "dj" ]]; then tlcdjvertexsixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomvertexsixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomvertexsixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                tlcedge60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusedgesixty=$mult
                    elif [[ $method == "dj" ]]; then tlcdjedgesixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomedgesixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomedgesixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                tlcedgepair60min=$((minlen))
                if [[ $method == "gwplus" ]]; then tlcgwplusedgepairsixty=$mult
                elif [[ $method == "dj" ]]; then tlcdjedgepairsixty=$mult
                fi
            fi
        elif [[ $ratio -eq 70 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                tlcvertex70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusvertexseventy=$mult
                    elif [[ $method == "dj" ]]; then tlcdjvertexseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomvertexseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomvertexseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                tlcedge70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusedgeseventy=$mult
                    elif [[ $method == "dj" ]]; then tlcdjedgeseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomedgeseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomedgeseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                tlcedgepair70min=$((minlen))
                if [[ $method == "gwplus" ]]; then tlcgwplusedgepairseventy=$mult
                elif [[ $method == "dj" ]]; then tlcdjedgepairseventy=$mult
                fi
            fi
        elif [[ $ratio -eq 80 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                tlcvertex80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusvertexeighty=$mult
                    elif [[ $method == "dj" ]]; then tlcdjvertexeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomvertexeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomvertexeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                tlcedge80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusedgeeighty=$mult
                    elif [[ $method == "dj" ]]; then tlcdjedgeeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomedgeeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomedgeeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                tlcedgepair80min=$((minlen))
                if [[ $method == "gwplus" ]]; then tlcgwplusedgepaireighty=$mult
                elif [[ $method == "dj" ]]; then tlcdjedgepaireighty=$mult
                fi
            fi
        elif [[ $ratio -eq 90 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                tlcvertex90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusvertexninety=$mult
                    elif [[ $method == "dj" ]]; then tlcdjvertexninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomvertexninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomvertexninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                tlcedge90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusedgeninety=$mult
                    elif [[ $method == "dj" ]]; then tlcdjedgeninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomedgeninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomedgeninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                tlcedgepair90min=$((minlen))
                if [[ $method == "gwplus" ]]; then tlcgwplusedgepairninety=$mult
                elif [[ $method == "dj" ]]; then tlcdjedgepairninety=$mult
                fi
            fi
        elif [[ $ratio -eq 100 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                tlcvertex100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusvertexhundred=$mult
                    elif [[ $method == "dj" ]]; then tlcdjvertexhundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomvertexhundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomvertexhundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                tlcedge100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then tlcgwplusedgehundred=$mult
                    elif [[ $method == "dj" ]]; then tlcdjedgehundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then tlcgwrandomedgehundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then tlcgwqrandomedgehundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                tlcedgepair100min=$((minlen))
                if [[ $method == "gwplus" ]]; then tlcgwplusedgepairhundred=$mult
                elif [[ $method == "dj" ]]; then tlcdjedgepairhundred=$mult
                fi
            fi
        fi
    elif [[ $model == "003" ]]
    then
        if [[ $ratio -eq 50 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                parabankvertex50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusvertexfifty=$mult
                    elif [[ $method == "dj" ]]; then parabankdjvertexfifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomvertexfifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomvertexfifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                parabankedge50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusedgefifty=$mult
                    elif [[ $method == "dj" ]]; then parabankdjedgefifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomedgefifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomedgefifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                parabankedgepair50min=$((minlen))
                if [[ $method == "gwplus" ]]; then parabankgwplusedgepairfifty=$mult
                elif [[ $method == "dj" ]]; then parabankdjedgepairfifty=$mult
                fi
            fi
        elif [[ $ratio -eq 60 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                parabankvertex60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusvertexsixty=$mult
                    elif [[ $method == "dj" ]]; then parabankdjvertexsixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomvertexsixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomvertexsixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                parabankedge60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusedgesixty=$mult
                    elif [[ $method == "dj" ]]; then parabankdjedgesixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomedgesixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomedgesixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                parabankedgepair60min=$((minlen))
                if [[ $method == "gwplus" ]]; then parabankgwplusedgepairsixty=$mult
                elif [[ $method == "dj" ]]; then parabankdjedgepairsixty=$mult
                fi
            fi
        elif [[ $ratio -eq 70 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                parabankvertex70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusvertexseventy=$mult
                    elif [[ $method == "dj" ]]; then parabankdjvertexseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomvertexseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomvertexseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                parabankedge70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusedgeseventy=$mult
                    elif [[ $method == "dj" ]]; then parabankdjedgeseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomedgeseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomedgeseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                parabankedgepair70min=$((minlen))
                if [[ $method == "gwplus" ]]; then parabankgwplusedgepairseventy=$mult
                elif [[ $method == "dj" ]]; then parabankdjedgepairseventy=$mult
                fi
            fi
        elif [[ $ratio -eq 80 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                parabankvertex80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusvertexeighty=$mult
                    elif [[ $method == "dj" ]]; then parabankdjvertexeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomvertexeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomvertexeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                parabankedge80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusedgeeighty=$mult
                    elif [[ $method == "dj" ]]; then parabankdjedgeeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomedgeeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomedgeeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                parabankedgepair80min=$((minlen))
                if [[ $method == "gwplus" ]]; then parabankgwplusedgepaireighty=$mult
                elif [[ $method == "dj" ]]; then parabankdjedgepaireighty=$mult
                fi
            fi
        elif [[ $ratio -eq 90 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                parabankvertex90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusvertexninety=$mult
                    elif [[ $method == "dj" ]]; then parabankdjvertexninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomvertexninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomvertexninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                parabankedge90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusedgeninety=$mult
                    elif [[ $method == "dj" ]]; then parabankdjedgeninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomedgeninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomedgeninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                parabankedgepair90min=$((minlen))
                if [[ $method == "gwplus" ]]; then parabankgwplusedgepairninety=$mult
                elif [[ $method == "dj" ]]; then parabankdjedgepairninety=$mult
                fi
            fi
        elif [[ $ratio -eq 100 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                parabankvertex100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusvertexhundred=$mult
                    elif [[ $method == "dj" ]]; then parabankdjvertexhundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomvertexhundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomvertexhundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                parabankedge100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then parabankgwplusedgehundred=$mult
                    elif [[ $method == "dj" ]]; then parabankdjedgehundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then parabankgwrandomedgehundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then parabankgwqrandomedgehundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                parabankedgepair100min=$((minlen))
                if [[ $method == "gwplus" ]]; then parabankgwplusedgepairhundred=$mult
                elif [[ $method == "dj" ]]; then parabankdjedgepairhundred=$mult
                fi
            fi
        fi
    elif [[ $model == "004" ]]
    then
        if [[ $ratio -eq 50 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                testiniumvertex50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusvertexfifty=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjvertexfifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomvertexfifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomvertexfifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                testiniumedge50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusedgefifty=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjedgefifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomedgefifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomedgefifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                testiniumedgepair50min=$((minlen))
                if [[ $method == "gwplus" ]]; then testiniumgwplusedgepairfifty=$mult
                elif [[ $method == "dj" ]]; then testiniumdjedgepairfifty=$mult
                fi
            fi
        elif [[ $ratio -eq 60 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                testiniumvertex60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusvertexsixty=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjvertexsixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomvertexsixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomvertexsixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                testiniumedge60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusedgesixty=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjedgesixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomedgesixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomedgesixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                testiniumedgepair60min=$((minlen))
                if [[ $method == "gwplus" ]]; then testiniumgwplusedgepairsixty=$mult
                elif [[ $method == "dj" ]]; then testiniumdjedgepairsixty=$mult
                fi
            fi
        elif [[ $ratio -eq 70 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                testiniumvertex70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusvertexseventy=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjvertexseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomvertexseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomvertexseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                testiniumedge70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusedgeseventy=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjedgeseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomedgeseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomedgeseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                testiniumedgepair70min=$((minlen))
                if [[ $method == "gwplus" ]]; then testiniumgwplusedgepairseventy=$mult
                elif [[ $method == "dj" ]]; then testiniumdjedgepairseventy=$mult
                fi
            fi
        elif [[ $ratio -eq 80 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                testiniumvertex80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusvertexeighty=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjvertexeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomvertexeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomvertexeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                testiniumedge80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusedgeeighty=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjedgeeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomedgeeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomedgeeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                testiniumedgepair80min=$((minlen))
                if [[ $method == "gwplus" ]]; then testiniumgwplusedgepaireighty=$mult
                elif [[ $method == "dj" ]]; then testiniumdjedgepaireighty=$mult
                fi
            fi
        elif [[ $ratio -eq 90 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                testiniumvertex90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusvertexninety=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjvertexninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomvertexninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomvertexninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                testiniumedge90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusedgeninety=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjedgeninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomedgeninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomedgeninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                testiniumedgepair90min=$((minlen))
                if [[ $method == "gwplus" ]]; then testiniumgwplusedgepairninety=$mult
                elif [[ $method == "dj" ]]; then testiniumdjedgepairninety=$mult
                fi
            fi
        elif [[ $ratio -eq 100 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                testiniumvertex100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusvertexhundred=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjvertexhundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomvertexhundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomvertexhundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                testiniumedge100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then testiniumgwplusedgehundred=$mult
                    elif [[ $method == "dj" ]]; then testiniumdjedgehundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then testiniumgwrandomedgehundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then testiniumgwqrandomedgehundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                testiniumedgepair100min=$((minlen))
                if [[ $method == "gwplus" ]]; then testiniumgwplusedgepairhundred=$mult
                elif [[ $method == "dj" ]]; then testiniumdjedgepairhundred=$mult
                fi
            fi
        fi
    elif [[ $model == "005" ]]
    then
        if [[ $ratio -eq 50 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                riscvvertex50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusvertexfifty=$mult
                    elif [[ $method == "dj" ]]; then riscvdjvertexfifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomvertexfifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomvertexfifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                riscvedge50min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusedgefifty=$mult
                    elif [[ $method == "dj" ]]; then riscvdjedgefifty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomedgefifty+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomedgefifty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                riscvedgepair50min=$((minlen))
                if [[ $method == "gwplus" ]]; then riscvgwplusedgepairfifty=$mult
                elif [[ $method == "dj" ]]; then riscvdjedgepairfifty=$mult
                fi
            fi
        elif [[ $ratio -eq 60 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                riscvvertex60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusvertexsixty=$mult
                    elif [[ $method == "dj" ]]; then riscvdjvertexsixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomvertexsixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomvertexsixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                riscvedge60min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusedgesixty=$mult
                    elif [[ $method == "dj" ]]; then riscvdjedgesixty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomedgesixty+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomedgesixty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                riscvedgepair60min=$((minlen))
                if [[ $method == "gwplus" ]]; then riscvgwplusedgepairsixty=$mult
                elif [[ $method == "dj" ]]; then riscvdjedgepairsixty=$mult
                fi
            fi
        elif [[ $ratio -eq 70 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                riscvvertex70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusvertexseventy=$mult
                    elif [[ $method == "dj" ]]; then riscvdjvertexseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomvertexseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomvertexseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                riscvedge70min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusedgeseventy=$mult
                    elif [[ $method == "dj" ]]; then riscvdjedgeseventy=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomedgeseventy+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomedgeseventy+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                riscvedgepair70min=$((minlen))
                if [[ $method == "gwplus" ]]; then riscvgwplusedgepairseventy=$mult
                elif [[ $method == "dj" ]]; then riscvdjedgepairseventy=$mult
                fi
            fi
        elif [[ $ratio -eq 80 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                riscvvertex80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusvertexeighty=$mult
                    elif [[ $method == "dj" ]]; then riscvdjvertexeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomvertexeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomvertexeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                riscvedge80min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusedgeeighty=$mult
                    elif [[ $method == "dj" ]]; then riscvdjedgeeighty=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomedgeeighty+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomedgeeighty+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                riscvedgepair80min=$((minlen))
                if [[ $method == "gwplus" ]]; then riscvgwplusedgepaireighty=$mult
                elif [[ $method == "dj" ]]; then riscvdjedgepaireighty=$mult
                fi
            fi
        elif [[ $ratio -eq 90 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                riscvvertex90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusvertexninety=$mult
                    elif [[ $method == "dj" ]]; then riscvdjvertexninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomvertexninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomvertexninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                riscvedge90min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusedgeninety=$mult
                    elif [[ $method == "dj" ]]; then riscvdjedgeninety=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomedgeninety+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomedgeninety+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                riscvedgepair90min=$((minlen))
                if [[ $method == "gwplus" ]]; then riscvgwplusedgepairninety=$mult
                elif [[ $method == "dj" ]]; then riscvdjedgepairninety=$mult
                fi
            fi
        elif [[ $ratio -eq 100 ]]
        then
            if [[ $tcov == "vertex" || $tcov == "vertex_coverage" ]]
            then
                riscvvertex100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusvertexhundred=$mult
                    elif [[ $method == "dj" ]]; then riscvdjvertexhundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomvertexhundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomvertexhundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edge" || $tcov == "edge_coverage" ]]
            then
                riscvedge100min=$((minlen))
                if [[ $tool == "GWPlus" ]]
                then
                    if [[ $method == "gwplus" ]]; then riscvgwplusedgehundred=$mult
                    elif [[ $method == "dj" ]]; then riscvdjedgehundred=$mult
                    fi
                elif [[ $tool == "GraphWalker" ]]
                then
                    if [[ $method == "random" ]]; then riscvgwrandomedgehundred+=($mult)
                    elif [[ $method == "quick_random" ]]; then riscvgwqrandomedgehundred+=($mult)
                    fi
                fi
            elif [[ $tcov == "edgepair" ]]
            then
                riscvedgepair100min=$((minlen))
                if [[ $method == "gwplus" ]]; then riscvgwplusedgepairhundred=$mult
                elif [[ $method == "dj" ]]; then riscvdjedgepairhundred=$mult
                fi
            fi
        fi
    fi
done< <(tail -n +2 rq1_raw.csv)

echo '\begin{filecontents*}{TLCGWPlusVertexFifty.dat}' >> rq1.tex
echo "${tlcgwplusvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusVertexFifty{TLCGWPlusVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusVertexSixty.dat}' >> rq1.tex
echo "${tlcgwplusvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusVertexSixty{TLCGWPlusVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusVertexSeventy.dat}' >> rq1.tex
echo "${tlcgwplusvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusVertexSeventy{TLCGWPlusVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusVertexEighty.dat}' >> rq1.tex
echo "${tlcgwplusvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusVertexEighty{TLCGWPlusVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusVertexNinety.dat}' >> rq1.tex
echo "${tlcgwplusvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusVertexNinety{TLCGWPlusVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusVertexHundred.dat}' >> rq1.tex
echo "${tlcgwplusvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusVertexHundred{TLCGWPlusVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgeFifty.dat}' >> rq1.tex
echo "${tlcgwplusedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgeFifty{TLCGWPlusEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgeSixty.dat}' >> rq1.tex
echo "${tlcgwplusedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgeSixty{TLCGWPlusEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgeSeventy.dat}' >> rq1.tex
echo "${tlcgwplusedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgeSeventy{TLCGWPlusEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgeEighty.dat}' >> rq1.tex
echo "${tlcgwplusedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgeEighty{TLCGWPlusEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgeNinety.dat}' >> rq1.tex
echo "${tlcgwplusedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgeNinety{TLCGWPlusEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgeHundred.dat}' >> rq1.tex
echo "${tlcgwplusedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgeHundred{TLCGWPlusEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgePairFifty.dat}' >> rq1.tex
echo "${tlcgwplusedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgePairFifty{TLCGWPlusEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgePairSixty.dat}' >> rq1.tex
echo "${tlcgwplusedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgePairSixty{TLCGWPlusEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo "${tlcgwplusedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgePairSeventy{TLCGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgePairEighty.dat}' >> rq1.tex
echo "${tlcgwplusedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgePairEighty{TLCGWPlusEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgePairNinety.dat}' >> rq1.tex
echo "${tlcgwplusedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgePairNinety{TLCGWPlusEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWPlusEdgePairHundred.dat}' >> rq1.tex
echo "${tlcgwplusedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWPlusEdgePairHundred{TLCGWPlusEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusVertexFifty.dat}' >> rq1.tex
echo "${riscvgwplusvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusVertexFifty{RISCVGWPlusVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusVertexSixty.dat}' >> rq1.tex
echo "${riscvgwplusvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusVertexSixty{RISCVGWPlusVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusVertexSeventy.dat}' >> rq1.tex
echo "${riscvgwplusvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusVertexSeventy{RISCVGWPlusVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusVertexEighty.dat}' >> rq1.tex
echo "${riscvgwplusvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusVertexEighty{RISCVGWPlusVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusVertexNinety.dat}' >> rq1.tex
echo "${riscvgwplusvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusVertexNinety{RISCVGWPlusVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusVertexHundred.dat}' >> rq1.tex
echo "${riscvgwplusvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusVertexHundred{RISCVGWPlusVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgeFifty.dat}' >> rq1.tex
echo "${riscvgwplusedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgeFifty{RISCVGWPlusEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgeSixty.dat}' >> rq1.tex
echo "${riscvgwplusedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgeSixty{RISCVGWPlusEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgeSeventy.dat}' >> rq1.tex
echo "${riscvgwplusedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgeSeventy{RISCVGWPlusEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgeEighty.dat}' >> rq1.tex
echo "${riscvgwplusedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgeEighty{RISCVGWPlusEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgeNinety.dat}' >> rq1.tex
echo "${riscvgwplusedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgeNinety{RISCVGWPlusEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgeHundred.dat}' >> rq1.tex
echo "${riscvgwplusedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgeHundred{RISCVGWPlusEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgePairFifty.dat}' >> rq1.tex
echo "${riscvgwplusedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgePairFifty{RISCVGWPlusEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgePairSixty.dat}' >> rq1.tex
echo "${riscvgwplusedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgePairSixty{RISCVGWPlusEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo "${riscvgwplusedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgePairSeventy{RISCVGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgePairEighty.dat}' >> rq1.tex
echo "${riscvgwplusedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgePairEighty{RISCVGWPlusEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgePairNinety.dat}' >> rq1.tex
echo "${riscvgwplusedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgePairNinety{RISCVGWPlusEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWPlusEdgePairHundred.dat}' >> rq1.tex
echo "${riscvgwplusedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWPlusEdgePairHundred{RISCVGWPlusEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusVertexFifty.dat}' >> rq1.tex
echo "${parabankgwplusvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusVertexFifty{ParabankGWPlusVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusVertexSixty.dat}' >> rq1.tex
echo "${parabankgwplusvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusVertexSixty{ParabankGWPlusVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusVertexSeventy.dat}' >> rq1.tex
echo "${parabankgwplusvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusVertexSeventy{ParabankGWPlusVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusVertexEighty.dat}' >> rq1.tex
echo "${parabankgwplusvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusVertexEighty{ParabankGWPlusVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusVertexNinety.dat}' >> rq1.tex
echo "${parabankgwplusvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusVertexNinety{ParabankGWPlusVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusVertexHundred.dat}' >> rq1.tex
echo "${parabankgwplusvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusVertexHundred{ParabankGWPlusVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgeFifty.dat}' >> rq1.tex
echo "${parabankgwplusedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgeFifty{ParabankGWPlusEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgeSixty.dat}' >> rq1.tex
echo "${parabankgwplusedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgeSixty{ParabankGWPlusEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgeSeventy.dat}' >> rq1.tex
echo "${parabankgwplusedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgeSeventy{ParabankGWPlusEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgeEighty.dat}' >> rq1.tex
echo "${parabankgwplusedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgeEighty{ParabankGWPlusEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgeNinety.dat}' >> rq1.tex
echo "${parabankgwplusedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgeNinety{ParabankGWPlusEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgeHundred.dat}' >> rq1.tex
echo "${parabankgwplusedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgeHundred{ParabankGWPlusEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgePairFifty.dat}' >> rq1.tex
echo "${parabankgwplusedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgePairFifty{ParabankGWPlusEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgePairSixty.dat}' >> rq1.tex
echo "${parabankgwplusedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgePairSixty{ParabankGWPlusEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo "${parabankgwplusedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgePairSeventy{ParabankGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgePairEighty.dat}' >> rq1.tex
echo "${parabankgwplusedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgePairEighty{ParabankGWPlusEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgePairNinety.dat}' >> rq1.tex
echo "${parabankgwplusedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgePairNinety{ParabankGWPlusEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWPlusEdgePairHundred.dat}' >> rq1.tex
echo "${parabankgwplusedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWPlusEdgePairHundred{ParabankGWPlusEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusVertexFifty.dat}' >> rq1.tex
echo "${testiniumgwplusvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusVertexFifty{TestiniumGWPlusVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusVertexSixty.dat}' >> rq1.tex
echo "${testiniumgwplusvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusVertexSixty{TestiniumGWPlusVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusVertexSeventy.dat}' >> rq1.tex
echo "${testiniumgwplusvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusVertexSeventy{TestiniumGWPlusVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusVertexEighty.dat}' >> rq1.tex
echo "${testiniumgwplusvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusVertexEighty{TestiniumGWPlusVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusVertexNinety.dat}' >> rq1.tex
echo "${testiniumgwplusvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusVertexNinety{TestiniumGWPlusVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusVertexHundred.dat}' >> rq1.tex
echo "${testiniumgwplusvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusVertexHundred{TestiniumGWPlusVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgeFifty.dat}' >> rq1.tex
echo "${testiniumgwplusedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgeFifty{TestiniumGWPlusEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgeSixty.dat}' >> rq1.tex
echo "${testiniumgwplusedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgeSixty{TestiniumGWPlusEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgeSeventy.dat}' >> rq1.tex
echo "${testiniumgwplusedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgeSeventy{TestiniumGWPlusEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgeEighty.dat}' >> rq1.tex
echo "${testiniumgwplusedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgeEighty{TestiniumGWPlusEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgeNinety.dat}' >> rq1.tex
echo "${testiniumgwplusedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgeNinety{TestiniumGWPlusEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgeHundred.dat}' >> rq1.tex
echo "${testiniumgwplusedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgeHundred{TestiniumGWPlusEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgePairFifty.dat}' >> rq1.tex
echo "${testiniumgwplusedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgePairFifty{TestiniumGWPlusEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgePairSixty.dat}' >> rq1.tex
echo "${testiniumgwplusedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgePairSixty{TestiniumGWPlusEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo "${testiniumgwplusedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgePairSeventy{TestiniumGWPlusEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgePairEighty.dat}' >> rq1.tex
echo "${testiniumgwplusedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgePairEighty{TestiniumGWPlusEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgePairNinety.dat}' >> rq1.tex
echo "${testiniumgwplusedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgePairNinety{TestiniumGWPlusEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWPlusEdgePairHundred.dat}' >> rq1.tex
echo "${testiniumgwplusedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWPlusEdgePairHundred{TestiniumGWPlusEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJVertexFifty.dat}' >> rq1.tex
echo "${tlcdjvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJVertexFifty{TLCDJVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJVertexSixty.dat}' >> rq1.tex
echo "${tlcdjvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJVertexSixty{TLCDJVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJVertexSeventy.dat}' >> rq1.tex
echo "${tlcdjvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJVertexSeventy{TLCDJVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJVertexEighty.dat}' >> rq1.tex
echo "${tlcdjvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJVertexEighty{TLCDJVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJVertexNinety.dat}' >> rq1.tex
echo "${tlcdjvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJVertexNinety{TLCDJVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJVertexHundred.dat}' >> rq1.tex
echo "${tlcdjvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJVertexHundred{TLCDJVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgeFifty.dat}' >> rq1.tex
echo "${tlcdjedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgeFifty{TLCDJEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgeSixty.dat}' >> rq1.tex
echo "${tlcdjedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgeSixty{TLCDJEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgeSeventy.dat}' >> rq1.tex
echo "${tlcdjedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgeSeventy{TLCDJEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgeEighty.dat}' >> rq1.tex
echo "${tlcdjedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgeEighty{TLCDJEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgeNinety.dat}' >> rq1.tex
echo "${tlcdjedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgeNinety{TLCDJEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgeHundred.dat}' >> rq1.tex
echo "${tlcdjedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgeHundred{TLCDJEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgePairFifty.dat}' >> rq1.tex
echo "${tlcdjedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgePairFifty{TLCDJEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgePairSixty.dat}' >> rq1.tex
echo "${tlcdjedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgePairSixty{TLCDJEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgePairSeventy.dat}' >> rq1.tex
echo "${tlcdjedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgePairSeventy{TLCDJEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgePairEighty.dat}' >> rq1.tex
echo "${tlcdjedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgePairEighty{TLCDJEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgePairNinety.dat}' >> rq1.tex
echo "${tlcdjedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgePairNinety{TLCDJEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCDJEdgePairHundred.dat}' >> rq1.tex
echo "${tlcdjedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCDJEdgePairHundred{TLCDJEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJVertexFifty.dat}' >> rq1.tex
echo "${riscvdjvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJVertexFifty{RISCVDJVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJVertexSixty.dat}' >> rq1.tex
echo "${riscvdjvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJVertexSixty{RISCVDJVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJVertexSeventy.dat}' >> rq1.tex
echo "${riscvdjvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJVertexSeventy{RISCVDJVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJVertexEighty.dat}' >> rq1.tex
echo "${riscvdjvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJVertexEighty{RISCVDJVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJVertexNinety.dat}' >> rq1.tex
echo "${riscvdjvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJVertexNinety{RISCVDJVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJVertexHundred.dat}' >> rq1.tex
echo "${riscvdjvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJVertexHundred{RISCVDJVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgeFifty.dat}' >> rq1.tex
echo "${riscvdjedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgeFifty{RISCVDJEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgeSixty.dat}' >> rq1.tex
echo "${riscvdjedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgeSixty{RISCVDJEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgeSeventy.dat}' >> rq1.tex
echo "${riscvdjedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgeSeventy{RISCVDJEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgeEighty.dat}' >> rq1.tex
echo "${riscvdjedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgeEighty{RISCVDJEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgeNinety.dat}' >> rq1.tex
echo "${riscvdjedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgeNinety{RISCVDJEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgeHundred.dat}' >> rq1.tex
echo "${riscvdjedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgeHundred{RISCVDJEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgePairFifty.dat}' >> rq1.tex
echo "${riscvdjedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgePairFifty{RISCVDJEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgePairSixty.dat}' >> rq1.tex
echo "${riscvdjedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgePairSixty{RISCVDJEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgePairSeventy.dat}' >> rq1.tex
echo "${riscvdjedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgePairSeventy{RISCVDJEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgePairEighty.dat}' >> rq1.tex
echo "${riscvdjedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgePairEighty{RISCVDJEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgePairNinety.dat}' >> rq1.tex
echo "${riscvdjedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgePairNinety{RISCVDJEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVDJEdgePairHundred.dat}' >> rq1.tex
echo "${riscvdjedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVDJEdgePairHundred{RISCVDJEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJVertexFifty.dat}' >> rq1.tex
echo "${parabankdjvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJVertexFifty{ParabankDJVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJVertexSixty.dat}' >> rq1.tex
echo "${parabankdjvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJVertexSixty{ParabankDJVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJVertexSeventy.dat}' >> rq1.tex
echo "${parabankdjvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJVertexSeventy{ParabankDJVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJVertexEighty.dat}' >> rq1.tex
echo "${parabankdjvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJVertexEighty{ParabankDJVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJVertexNinety.dat}' >> rq1.tex
echo "${parabankdjvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJVertexNinety{ParabankDJVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJVertexHundred.dat}' >> rq1.tex
echo "${parabankdjvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJVertexHundred{ParabankDJVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgeFifty.dat}' >> rq1.tex
echo "${parabankdjedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgeFifty{ParabankDJEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgeSixty.dat}' >> rq1.tex
echo "${parabankdjedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgeSixty{ParabankDJEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgeSeventy.dat}' >> rq1.tex
echo "${parabankdjedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgeSeventy{ParabankDJEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgeEighty.dat}' >> rq1.tex
echo "${parabankdjedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgeEighty{ParabankDJEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgeNinety.dat}' >> rq1.tex
echo "${parabankdjedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgeNinety{ParabankDJEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgeHundred.dat}' >> rq1.tex
echo "${parabankdjedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgeHundred{ParabankDJEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgePairFifty.dat}' >> rq1.tex
echo "${parabankdjedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgePairFifty{ParabankDJEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgePairSixty.dat}' >> rq1.tex
echo "${parabankdjedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgePairSixty{ParabankDJEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgePairSeventy.dat}' >> rq1.tex
echo "${parabankdjedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgePairSeventy{ParabankDJEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgePairEighty.dat}' >> rq1.tex
echo "${parabankdjedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgePairEighty{ParabankDJEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgePairNinety.dat}' >> rq1.tex
echo "${parabankdjedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgePairNinety{ParabankDJEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankDJEdgePairHundred.dat}' >> rq1.tex
echo "${parabankdjedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankDJEdgePairHundred{ParabankDJEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJVertexFifty.dat}' >> rq1.tex
echo "${testiniumdjvertexfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJVertexFifty{TestiniumDJVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJVertexSixty.dat}' >> rq1.tex
echo "${testiniumdjvertexsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJVertexSixty{TestiniumDJVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJVertexSeventy.dat}' >> rq1.tex
echo "${testiniumdjvertexseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJVertexSeventy{TestiniumDJVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJVertexEighty.dat}' >> rq1.tex
echo "${testiniumdjvertexeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJVertexEighty{TestiniumDJVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJVertexNinety.dat}' >> rq1.tex
echo "${testiniumdjvertexninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJVertexNinety{TestiniumDJVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJVertexHundred.dat}' >> rq1.tex
echo "${testiniumdjvertexhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJVertexHundred{TestiniumDJVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgeFifty.dat}' >> rq1.tex
echo "${testiniumdjedgefifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgeFifty{TestiniumDJEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgeSixty.dat}' >> rq1.tex
echo "${testiniumdjedgesixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgeSixty{TestiniumDJEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgeSeventy.dat}' >> rq1.tex
echo "${testiniumdjedgeseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgeSeventy{TestiniumDJEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgeEighty.dat}' >> rq1.tex
echo "${testiniumdjedgeeighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgeEighty{TestiniumDJEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgeNinety.dat}' >> rq1.tex
echo "${testiniumdjedgeninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgeNinety{TestiniumDJEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgeHundred.dat}' >> rq1.tex
echo "${testiniumdjedgehundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgeHundred{TestiniumDJEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgePairFifty.dat}' >> rq1.tex
echo "${testiniumdjedgepairfifty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgePairFifty{TestiniumDJEdgePairFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgePairSixty.dat}' >> rq1.tex
echo "${testiniumdjedgepairsixty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgePairSixty{TestiniumDJEdgePairSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgePairSeventy.dat}' >> rq1.tex
echo "${testiniumdjedgepairseventy} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgePairSeventy{TestiniumDJEdgePairSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgePairEighty.dat}' >> rq1.tex
echo "${testiniumdjedgepaireighty} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgePairEighty{TestiniumDJEdgePairEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgePairNinety.dat}' >> rq1.tex
echo "${testiniumdjedgepairninety} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgePairNinety{TestiniumDJEdgePairNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumDJEdgePairHundred.dat}' >> rq1.tex
echo "${testiniumdjedgepairhundred} NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN NaN" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumDJEdgePairHundred{TestiniumDJEdgePairHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomVertexFifty.dat}' >> rq1.tex
echo "${tlcgwqrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomVertexFifty{TLCGWQRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomVertexSixty.dat}' >> rq1.tex
echo "${tlcgwqrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomVertexSixty{TLCGWQRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomVertexSeventy.dat}' >> rq1.tex
echo "${tlcgwqrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomVertexSeventy{TLCGWQRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomVertexEighty.dat}' >> rq1.tex
echo "${tlcgwqrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomVertexEighty{TLCGWQRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomVertexNinety.dat}' >> rq1.tex
echo "${tlcgwqrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomVertexNinety{TLCGWQRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomVertexHundred.dat}' >> rq1.tex
echo "${tlcgwqrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomVertexHundred{TLCGWQRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomEdgeFifty.dat}' >> rq1.tex
echo "${tlcgwqrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomEdgeFifty{TLCGWQRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomEdgeSixty.dat}' >> rq1.tex
echo "${tlcgwqrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomEdgeSixty{TLCGWQRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo "${tlcgwqrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomEdgeSeventy{TLCGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomEdgeEighty.dat}' >> rq1.tex
echo "${tlcgwqrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomEdgeEighty{TLCGWQRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomEdgeNinety.dat}' >> rq1.tex
echo "${tlcgwqrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomEdgeNinety{TLCGWQRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWQRandomEdgeHundred.dat}' >> rq1.tex
echo "${tlcgwqrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWQRandomEdgeHundred{TLCGWQRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomVertexFifty.dat}' >> rq1.tex
echo "${tlcgwrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomVertexFifty{TLCGWRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomVertexSixty.dat}' >> rq1.tex
echo "${tlcgwrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomVertexSixty{TLCGWRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomVertexSeventy.dat}' >> rq1.tex
echo "${tlcgwrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomVertexSeventy{TLCGWRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomVertexEighty.dat}' >> rq1.tex
echo "${tlcgwrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomVertexEighty{TLCGWRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomVertexNinety.dat}' >> rq1.tex
echo "${tlcgwrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomVertexNinety{TLCGWRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomVertexHundred.dat}' >> rq1.tex
echo "${tlcgwrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomVertexHundred{TLCGWRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomEdgeFifty.dat}' >> rq1.tex
echo "${tlcgwrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomEdgeFifty{TLCGWRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomEdgeSixty.dat}' >> rq1.tex
echo "${tlcgwrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomEdgeSixty{TLCGWRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomEdgeSeventy.dat}' >> rq1.tex
echo "${tlcgwrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomEdgeSeventy{TLCGWRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomEdgeEighty.dat}' >> rq1.tex
echo "${tlcgwrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomEdgeEighty{TLCGWRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomEdgeNinety.dat}' >> rq1.tex
echo "${tlcgwrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomEdgeNinety{TLCGWRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TLCGWRandomEdgeHundred.dat}' >> rq1.tex
echo "${tlcgwrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TLCGWRandomEdgeHundred{TLCGWRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomVertexFifty.dat}' >> rq1.tex
echo "${riscvgwqrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomVertexFifty{RISCVGWQRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomVertexSixty.dat}' >> rq1.tex
echo "${riscvgwqrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomVertexSixty{RISCVGWQRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomVertexSeventy.dat}' >> rq1.tex
echo "${riscvgwqrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomVertexSeventy{RISCVGWQRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomVertexEighty.dat}' >> rq1.tex
echo "${riscvgwqrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomVertexEighty{RISCVGWQRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomVertexNinety.dat}' >> rq1.tex
echo "${riscvgwqrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomVertexNinety{RISCVGWQRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomVertexHundred.dat}' >> rq1.tex
echo "${riscvgwqrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomVertexHundred{RISCVGWQRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomEdgeFifty.dat}' >> rq1.tex
echo "${riscvgwqrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomEdgeFifty{RISCVGWQRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomEdgeSixty.dat}' >> rq1.tex
echo "${riscvgwqrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomEdgeSixty{RISCVGWQRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo "${riscvgwqrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomEdgeSeventy{RISCVGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomEdgeEighty.dat}' >> rq1.tex
echo "${riscvgwqrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomEdgeEighty{RISCVGWQRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomEdgeNinety.dat}' >> rq1.tex
echo "${riscvgwqrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomEdgeNinety{RISCVGWQRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWQRandomEdgeHundred.dat}' >> rq1.tex
echo "${riscvgwqrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWQRandomEdgeHundred{RISCVGWQRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomVertexFifty.dat}' >> rq1.tex
echo "${riscvgwrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomVertexFifty{RISCVGWRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomVertexSixty.dat}' >> rq1.tex
echo "${riscvgwrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomVertexSixty{RISCVGWRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomVertexSeventy.dat}' >> rq1.tex
echo "${riscvgwrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomVertexSeventy{RISCVGWRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomVertexEighty.dat}' >> rq1.tex
echo "${riscvgwrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomVertexEighty{RISCVGWRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomVertexNinety.dat}' >> rq1.tex
echo "${riscvgwrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomVertexNinety{RISCVGWRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomVertexHundred.dat}' >> rq1.tex
echo "${riscvgwrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomVertexHundred{RISCVGWRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomEdgeFifty.dat}' >> rq1.tex
echo "${riscvgwrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomEdgeFifty{RISCVGWRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomEdgeSixty.dat}' >> rq1.tex
echo "${riscvgwrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomEdgeSixty{RISCVGWRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomEdgeSeventy.dat}' >> rq1.tex
echo "${riscvgwrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomEdgeSeventy{RISCVGWRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomEdgeEighty.dat}' >> rq1.tex
echo "${riscvgwrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomEdgeEighty{RISCVGWRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomEdgeNinety.dat}' >> rq1.tex
echo "${riscvgwrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomEdgeNinety{RISCVGWRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{RISCVGWRandomEdgeHundred.dat}' >> rq1.tex
echo "${riscvgwrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\RISCVGWRandomEdgeHundred{RISCVGWRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomVertexFifty.dat}' >> rq1.tex
echo "${parabankgwqrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomVertexFifty{ParabankGWQRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomVertexSixty.dat}' >> rq1.tex
echo "${parabankgwqrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomVertexSixty{ParabankGWQRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomVertexSeventy.dat}' >> rq1.tex
echo "${parabankgwqrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomVertexSeventy{ParabankGWQRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomVertexEighty.dat}' >> rq1.tex
echo "${parabankgwqrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomVertexEighty{ParabankGWQRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomVertexNinety.dat}' >> rq1.tex
echo "${parabankgwqrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomVertexNinety{ParabankGWQRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomVertexHundred.dat}' >> rq1.tex
echo "${parabankgwqrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomVertexHundred{ParabankGWQRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomEdgeFifty.dat}' >> rq1.tex
echo "${parabankgwqrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomEdgeFifty{ParabankGWQRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomEdgeSixty.dat}' >> rq1.tex
echo "${parabankgwqrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomEdgeSixty{ParabankGWQRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo "${parabankgwqrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomEdgeSeventy{ParabankGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomEdgeEighty.dat}' >> rq1.tex
echo "${parabankgwqrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomEdgeEighty{ParabankGWQRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomEdgeNinety.dat}' >> rq1.tex
echo "${parabankgwqrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomEdgeNinety{ParabankGWQRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWQRandomEdgeHundred.dat}' >> rq1.tex
echo "${parabankgwqrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWQRandomEdgeHundred{ParabankGWQRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomVertexFifty.dat}' >> rq1.tex
echo "${parabankgwrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomVertexFifty{ParabankGWRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomVertexSixty.dat}' >> rq1.tex
echo "${parabankgwrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomVertexSixty{ParabankGWRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomVertexSeventy.dat}' >> rq1.tex
echo "${parabankgwrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomVertexSeventy{ParabankGWRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomVertexEighty.dat}' >> rq1.tex
echo "${parabankgwrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomVertexEighty{ParabankGWRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomVertexNinety.dat}' >> rq1.tex
echo "${parabankgwrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomVertexNinety{ParabankGWRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomVertexHundred.dat}' >> rq1.tex
echo "${parabankgwrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomVertexHundred{ParabankGWRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomEdgeFifty.dat}' >> rq1.tex
echo "${parabankgwrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomEdgeFifty{ParabankGWRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomEdgeSixty.dat}' >> rq1.tex
echo "${parabankgwrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomEdgeSixty{ParabankGWRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomEdgeSeventy.dat}' >> rq1.tex
echo "${parabankgwrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomEdgeSeventy{ParabankGWRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomEdgeEighty.dat}' >> rq1.tex
echo "${parabankgwrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomEdgeEighty{ParabankGWRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomEdgeNinety.dat}' >> rq1.tex
echo "${parabankgwrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomEdgeNinety{ParabankGWRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{ParabankGWRandomEdgeHundred.dat}' >> rq1.tex
echo "${parabankgwrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\ParabankGWRandomEdgeHundred{ParabankGWRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomVertexFifty.dat}' >> rq1.tex
echo "${testiniumgwqrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomVertexFifty{TestiniumGWQRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomVertexSixty.dat}' >> rq1.tex
echo "${testiniumgwqrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomVertexSixty{TestiniumGWQRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomVertexSeventy.dat}' >> rq1.tex
echo "${testiniumgwqrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomVertexSeventy{TestiniumGWQRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomVertexEighty.dat}' >> rq1.tex
echo "${testiniumgwqrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomVertexEighty{TestiniumGWQRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomVertexNinety.dat}' >> rq1.tex
echo "${testiniumgwqrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomVertexNinety{TestiniumGWQRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomVertexHundred.dat}' >> rq1.tex
echo "${testiniumgwqrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomVertexHundred{TestiniumGWQRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomEdgeFifty.dat}' >> rq1.tex
echo "${testiniumgwqrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomEdgeFifty{TestiniumGWQRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomEdgeSixty.dat}' >> rq1.tex
echo "${testiniumgwqrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomEdgeSixty{TestiniumGWQRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo "${testiniumgwqrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomEdgeSeventy{TestiniumGWQRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomEdgeEighty.dat}' >> rq1.tex
echo "${testiniumgwqrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomEdgeEighty{TestiniumGWQRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomEdgeNinety.dat}' >> rq1.tex
echo "${testiniumgwqrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomEdgeNinety{TestiniumGWQRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWQRandomEdgeHundred.dat}' >> rq1.tex
echo "${testiniumgwqrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWQRandomEdgeHundred{TestiniumGWQRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomVertexFifty.dat}' >> rq1.tex
echo "${testiniumgwrandomvertexfifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomVertexFifty{TestiniumGWRandomVertexFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomVertexSixty.dat}' >> rq1.tex
echo "${testiniumgwrandomvertexsixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomVertexSixty{TestiniumGWRandomVertexSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomVertexSeventy.dat}' >> rq1.tex
echo "${testiniumgwrandomvertexseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomVertexSeventy{TestiniumGWRandomVertexSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomVertexEighty.dat}' >> rq1.tex
echo "${testiniumgwrandomvertexeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomVertexEighty{TestiniumGWRandomVertexEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomVertexNinety.dat}' >> rq1.tex
echo "${testiniumgwrandomvertexninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomVertexNinety{TestiniumGWRandomVertexNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomVertexHundred.dat}' >> rq1.tex
echo "${testiniumgwrandomvertexhundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomVertexHundred{TestiniumGWRandomVertexHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomEdgeFifty.dat}' >> rq1.tex
echo "${testiniumgwrandomedgefifty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomEdgeFifty{TestiniumGWRandomEdgeFifty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomEdgeSixty.dat}' >> rq1.tex
echo "${testiniumgwrandomedgesixty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomEdgeSixty{TestiniumGWRandomEdgeSixty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomEdgeSeventy.dat}' >> rq1.tex
echo "${testiniumgwrandomedgeseventy[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomEdgeSeventy{TestiniumGWRandomEdgeSeventy.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomEdgeEighty.dat}' >> rq1.tex
echo "${testiniumgwrandomedgeeighty[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomEdgeEighty{TestiniumGWRandomEdgeEighty.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomEdgeNinety.dat}' >> rq1.tex
echo "${testiniumgwrandomedgeninety[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomEdgeNinety{TestiniumGWRandomEdgeNinety.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{filecontents*}{TestiniumGWRandomEdgeHundred.dat}' >> rq1.tex
echo "${testiniumgwrandomedgehundred[@]}" >> rq1.tex
echo '\end{filecontents*}' >> rq1.tex
echo '\pgfplotstabletranspose\TestiniumGWRandomEdgeHundred{TestiniumGWRandomEdgeHundred.dat}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{document}' >> rq1.tex
echo '' >> rq1.tex

echo '\begin{tikzpicture}' >> rq1.tex
echo '    \begin{axis}[' >> rq1.tex
echo '        boxplot/draw direction=y,' >> rq1.tex
echo '        mark options={scale=0.7},' >> rq1.tex
echo '        xtick={' >> rq1.tex
echo '            1,2,3,4,%Vertex50' >> rq1.tex
echo '            5,6,7,8,%Vertex60' >> rq1.tex
echo '            9,10,11,12,%Vertex70' >> rq1.tex
echo '            13,14,15,16,%Vertex80' >> rq1.tex
echo '            17,18,19,20,%Vertex90' >> rq1.tex
echo '            21,22,23,24,%Vertex100' >> rq1.tex
echo '            25,26,27,28,%Edge50' >> rq1.tex
echo '            29,30,31,32,%Edge60' >> rq1.tex
echo '            33,34,35,36,%Edge70' >> rq1.tex
echo '            37,38,39,40,%Edge80' >> rq1.tex
echo '            41,42,43,44,%Edge90' >> rq1.tex
echo '            45,46,47,48,%Edge100' >> rq1.tex
echo '            49,50,%EdgePair50' >> rq1.tex
echo '            51,52,%EdgePair60' >> rq1.tex
echo '            53,54,%EdgePair70' >> rq1.tex
echo '            55,56,%EdgePair80' >> rq1.tex
echo '            57,58,%EdgePair80' >> rq1.tex
echo '            59,60 %EdgePair100' >> rq1.tex
echo '        },' >> rq1.tex
echo '        xticklabels=\empty,' >> rq1.tex
echo '        x tick label style={rotate=90,font=\footnotesize},' >> rq1.tex
echo '        y tick label style={font=\tiny},' >> rq1.tex
echo '        ymode=log,' >> rq1.tex
echo '        log basis y={2},' >> rq1.tex
echo '        ytick pos=left,' >> rq1.tex
echo '        xtick pos=left,' >> rq1.tex
echo '        ymin=0.625,' >> rq1.tex
echo '        ymax=64,' >> rq1.tex
echo '        xmin=0.25,' >> rq1.tex
echo '        xmax=60.5,' >> rq1.tex
echo '        ymajorgrids,' >> rq1.tex
echo '        ytick={1,2,4,8,16,32,64},' >> rq1.tex
echo '        yticklabels={1x,2x,4x,8x,16x,32x,64x},' >> rq1.tex
echo '        xlabel=Target Coverage Criterion,' >> rq1.tex
echo '        x label style={at={(axis description cs:0.5,1.35)}},' >> rq1.tex
echo '        ylabel=TLC,' >> rq1.tex
echo '        y label style={at={(axis description cs:1.025,0.5)},font=\tiny},' >> rq1.tex
echo '        height=5cm,' >> rq1.tex
echo '        width=17cm,' >> rq1.tex
echo '        major tick length=2pt,' >> rq1.tex
echo '        extra x ticks={2.5,6.5,10.5,14.5,18.5,22.5,26.5,30.5,34.5,38.5,42.5,46.5,49.5,51.5,53.5,55.5,57.5,59.5},' >> rq1.tex
echo '        extra x tick labels={' >> rq1.tex
echo '            \tiny$50\%$,\tiny$60\%$,\tiny$70\%$,\tiny$80\%$,\tiny$90\%$,\tiny$100\%$,' >> rq1.tex
echo '            \tiny$50\%$,\tiny$60\%$,\tiny$70\%$,\tiny$80\%$,\tiny$90\%$,\tiny$100\%$,' >> rq1.tex
echo '            \tiny$50\%$,\tiny$60\%$,\tiny$70\%$,\tiny$80\%$,\tiny$90\%$,\tiny$100\%$' >> rq1.tex
echo '        },' >> rq1.tex
echo '        extra x tick style={' >> rq1.tex
echo '            grid=none,' >> rq1.tex
echo '            tick pos=right,' >> rq1.tex
echo '            ticklabel pos=right,' >> rq1.tex
echo '            major tick length=0pt,' >> rq1.tex
echo '            tick label style={rotate=270}' >> rq1.tex
echo '        }' >> rq1.tex
echo '    ]' >> rq1.tex
echo '' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWQRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCGWPlusEdgePairHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TLCDJEdgePairHundred};' >> rq1.tex
echo '' >> rq1.tex
IFS=$'\n'
i=1
if [[ ${tlcgwplusvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwqrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${tlcgwrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${tlcedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcgwplusedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${tlcdjedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${tlcedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
unset IFS
echo '' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(4.5, 0.625) (3.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(8.5, 0.625) (8.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(12.5, 0.625) (12.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(16.5, 0.625) (16.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(20.5, 0.625) (20.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(24.5, 0.625) (24.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(28.5, 0.625) (28.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(32.5, 0.625) (32.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(36.5, 0.625) (36.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(40.5, 0.625) (40.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(44.5, 0.625) (44.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(48.5, 0.625) (48.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(50.5, 0.625) (50.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(52.5, 0.625) (52.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(54.5, 0.625) (54.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(56.5, 0.625) (56.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(58.5, 0.625) (58.5, 4096)};' >> rq1.tex
echo '' >> rq1.tex
echo '    \end{axis}' >> rq1.tex
echo '' >> rq1.tex
echo '    \begin{axis}[' >> rq1.tex
echo '        boxplot/draw direction=y,' >> rq1.tex
echo '        mark options={scale=0.7},' >> rq1.tex
echo '        major tick length=0pt,' >> rq1.tex
echo '        xtick={12.5,36.5,54.5},' >> rq1.tex
echo '        xticklabels={Vertex,Edge,Edge-Pair},' >> rq1.tex
echo '        x tick label style={font=\footnotesize,yshift=7.5pt},' >> rq1.tex
echo '        xtick pos=right,' >> rq1.tex
echo '        ytick=\empty,' >> rq1.tex
echo '        ymin=0.625,' >> rq1.tex
echo '        ymax=16,' >> rq1.tex
echo '        xmin=0.25,' >> rq1.tex
echo '        xmax=60.5,' >> rq1.tex
echo '        height=5cm,' >> rq1.tex
echo '        width=17cm' >> rq1.tex
echo '    ]' >> rq1.tex
echo '    \end{axis}' >> rq1.tex
echo '\end{tikzpicture}' >> rq1.tex
echo '' >> rq1.tex
echo '\vspace{-.3cm}' >> rq1.tex
echo '' >> rq1.tex
echo '\begin{tikzpicture}' >> rq1.tex
echo '    \begin{axis}[' >> rq1.tex
echo '        boxplot/draw direction=y,' >> rq1.tex
echo '        mark options={scale=0.7},' >> rq1.tex
echo '        xtick={' >> rq1.tex
echo '            1,2,3,4,%Vertex50' >> rq1.tex
echo '            5,6,7,8,%Vertex60' >> rq1.tex
echo '            9,10,11,12,%Vertex70' >> rq1.tex
echo '            13,14,15,16,%Vertex80' >> rq1.tex
echo '            17,18,19,20,%Vertex90' >> rq1.tex
echo '            21,22,23,24,%Vertex100' >> rq1.tex
echo '            25,26,27,28,%Edge50' >> rq1.tex
echo '            29,30,31,32,%Edge60' >> rq1.tex
echo '            33,34,35,36,%Edge70' >> rq1.tex
echo '            37,38,39,40,%Edge80' >> rq1.tex
echo '            41,42,43,44,%Edge90' >> rq1.tex
echo '            45,46,47,48,%Edge100' >> rq1.tex
echo '            49,50,%EdgePair50' >> rq1.tex
echo '            51,52,%EdgePair60' >> rq1.tex
echo '            53,54,%EdgePair70' >> rq1.tex
echo '            55,56,%EdgePair80' >> rq1.tex
echo '            57,58,%EdgePair80' >> rq1.tex
echo '            59,60 %EdgePair100' >> rq1.tex
echo '        },' >> rq1.tex
echo '        xticklabels=\empty,' >> rq1.tex
echo '        x tick label style={rotate=90,font=\footnotesize},' >> rq1.tex
echo '        y tick label style={font=\tiny},' >> rq1.tex
echo '        ymode=log,' >> rq1.tex
echo '        log basis y={2},' >> rq1.tex
echo '        ytick pos=left,' >> rq1.tex
echo '        xtick pos=left,' >> rq1.tex
echo '        ymin=0.625,' >> rq1.tex
echo '        ymax=64,' >> rq1.tex
echo '        xmin=0.25,' >> rq1.tex
echo '        xmax=60.5,' >> rq1.tex
echo '        ymajorgrids,' >> rq1.tex
echo '        ytick={1,2,4,8,16,32,64},' >> rq1.tex
echo '        yticklabels={1x,2x,4x,8x,16x,32x,64x},' >> rq1.tex
echo '        ylabel=RISC-V,' >> rq1.tex
echo '        y label style={at={(axis description cs:1.025,0.5)},font=\tiny},' >> rq1.tex
echo '        height=5cm,' >> rq1.tex
echo '        width=17cm,' >> rq1.tex
echo '        major tick length=2pt' >> rq1.tex
echo '    ]' >> rq1.tex
echo '' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWQRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVGWPlusEdgePairHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\RISCVDJEdgePairHundred};' >> rq1.tex
echo '' >> rq1.tex
IFS=$'\n'
i=1
if [[ ${riscvgwplusvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwqrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${riscvgwrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${riscvedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvgwplusedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${riscvdjedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${riscvedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
unset IFS
echo '' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(4.5, 0.625) (3.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(8.5, 0.625) (8.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(12.5, 0.625) (12.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(16.5, 0.625) (16.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(20.5, 0.625) (20.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(24.5, 0.625) (24.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(28.5, 0.625) (28.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(32.5, 0.625) (32.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(36.5, 0.625) (36.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(40.5, 0.625) (40.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(44.5, 0.625) (44.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(48.5, 0.625) (48.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(50.5, 0.625) (50.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(52.5, 0.625) (52.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(54.5, 0.625) (54.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(56.5, 0.625) (56.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(58.5, 0.625) (58.5, 4096)};' >> rq1.tex
echo '' >> rq1.tex
echo '    \end{axis}' >> rq1.tex
echo '\end{tikzpicture}' >> rq1.tex
echo '' >> rq1.tex
echo '\vspace{-.3cm}' >> rq1.tex
echo '' >> rq1.tex
echo '\begin{tikzpicture}' >> rq1.tex
echo '    \begin{axis}[' >> rq1.tex
echo '        boxplot/draw direction=y,' >> rq1.tex
echo '        mark options={scale=0.7},' >> rq1.tex
echo '        xtick={' >> rq1.tex
echo '            1,2,3,4,%Vertex50' >> rq1.tex
echo '            5,6,7,8,%Vertex60' >> rq1.tex
echo '            9,10,11,12,%Vertex70' >> rq1.tex
echo '            13,14,15,16,%Vertex80' >> rq1.tex
echo '            17,18,19,20,%Vertex90' >> rq1.tex
echo '            21,22,23,24,%Vertex100' >> rq1.tex
echo '            25,26,27,28,%Edge50' >> rq1.tex
echo '            29,30,31,32,%Edge60' >> rq1.tex
echo '            33,34,35,36,%Edge70' >> rq1.tex
echo '            37,38,39,40,%Edge80' >> rq1.tex
echo '            41,42,43,44,%Edge90' >> rq1.tex
echo '            45,46,47,48,%Edge100' >> rq1.tex
echo '            49,50,%EdgePair50' >> rq1.tex
echo '            51,52,%EdgePair60' >> rq1.tex
echo '            53,54,%EdgePair70' >> rq1.tex
echo '            55,56,%EdgePair80' >> rq1.tex
echo '            57,58,%EdgePair80' >> rq1.tex
echo '            59,60 %EdgePair100' >> rq1.tex
echo '        },' >> rq1.tex
echo '        xticklabels=\empty,' >> rq1.tex
echo '        x tick label style={rotate=90,font=\footnotesize},' >> rq1.tex
echo '        y tick label style={font=\tiny},' >> rq1.tex
echo '        ymode=log,' >> rq1.tex
echo '        log basis y={2},' >> rq1.tex
echo '        ytick pos=left,' >> rq1.tex
echo '        xtick pos=left,' >> rq1.tex
echo '        ymin=0.625,' >> rq1.tex
echo '        ymax=64,' >> rq1.tex
echo '        xmin=0.25,' >> rq1.tex
echo '        xmax=60.5,' >> rq1.tex
echo '        ymajorgrids,' >> rq1.tex
echo '        ytick={1,2,4,8,16,32,64},' >> rq1.tex
echo '        yticklabels={1x,2x,4x,8x,16x,32x,64x},' >> rq1.tex
echo '        ylabel=Parabank,' >> rq1.tex
echo '        y label style={at={(axis description cs:1.025,0.5)},font=\tiny},' >> rq1.tex
echo '        height=5cm,' >> rq1.tex
echo '        width=17cm,' >> rq1.tex
echo '        major tick length=2pt' >> rq1.tex
echo '    ]' >> rq1.tex
echo '' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWQRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankGWPlusEdgePairHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\ParabankDJEdgePairHundred};' >> rq1.tex
echo '' >> rq1.tex
IFS=$'\n'
i=1
if [[ ${parabankgwplusvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:32.75,1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:34.25,1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwqrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${parabankgwrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${parabankedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankgwplusedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${parabankdjedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${parabankedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
unset IFS
echo '' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(4.5, 0.625) (3.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(8.5, 0.625) (8.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(12.5, 0.625) (12.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(16.5, 0.625) (16.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(20.5, 0.625) (20.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(24.5, 0.625) (24.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(28.5, 0.625) (28.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(32.5, 0.625) (32.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(36.5, 0.625) (36.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(40.5, 0.625) (40.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(44.5, 0.625) (44.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(48.5, 0.625) (48.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(50.5, 0.625) (50.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(52.5, 0.625) (52.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(54.5, 0.625) (54.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(56.5, 0.625) (56.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(58.5, 0.625) (58.5, 4096)};' >> rq1.tex
echo '' >> rq1.tex
echo '    \end{axis}' >> rq1.tex
echo '\end{tikzpicture}' >> rq1.tex
echo '' >> rq1.tex
echo '\vspace{-.3cm}' >> rq1.tex
echo '' >> rq1.tex
echo '\begin{tikzpicture}' >> rq1.tex
echo '    \begin{axis}[' >> rq1.tex
echo '        boxplot/draw direction=y,' >> rq1.tex
echo '        mark options={scale=0.7},' >> rq1.tex
echo '        xtick={' >> rq1.tex
echo '            1,2,3,4,%Vertex50' >> rq1.tex
echo '            5,6,7,8,%Vertex60' >> rq1.tex
echo '            9,10,11,12,%Vertex70' >> rq1.tex
echo '            13,14,15,16,%Vertex80' >> rq1.tex
echo '            17,18,19,20,%Vertex90' >> rq1.tex
echo '            21,22,23,24,%Vertex100' >> rq1.tex
echo '            25,26,27,28,%Edge50' >> rq1.tex
echo '            29,30,31,32,%Edge60' >> rq1.tex
echo '            33,34,35,36,%Edge70' >> rq1.tex
echo '            37,38,39,40,%Edge80' >> rq1.tex
echo '            41,42,43,44,%Edge90' >> rq1.tex
echo '            45,46,47,48,%Edge100' >> rq1.tex
echo '            49,50,%EdgePair50' >> rq1.tex
echo '            51,52,%EdgePair60' >> rq1.tex
echo '            53,54,%EdgePair70' >> rq1.tex
echo '            55,56,%EdgePair80' >> rq1.tex
echo '            57,58,%EdgePair80' >> rq1.tex
echo '            59,60 %EdgePair100' >> rq1.tex
echo '        },' >> rq1.tex
echo '        xticklabels={' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Vertex50' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Vertex60' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Vertex70' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Vertex80' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Vertex90' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Vertex100' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Edge50' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Edge60' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Edge70' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Edge80' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Edge90' >> rq1.tex
echo '            \tiny GWPlus,\tiny GW-QRandom,\tiny DJ,\tiny GW-Random,%Edge100' >> rq1.tex
echo '            \tiny GWPlus,\tiny DJ,%EdgePair50' >> rq1.tex
echo '            \tiny GWPlus,\tiny DJ,%EdgePair60' >> rq1.tex
echo '            \tiny GWPlus,\tiny DJ,%EdgePair70' >> rq1.tex
echo '            \tiny GWPlus,\tiny DJ,%EdgePair80' >> rq1.tex
echo '            \tiny GWPlus,\tiny DJ,%EdgePair90' >> rq1.tex
echo '            \tiny GWPlus,\tiny DJ %EdgePair100' >> rq1.tex
echo '        },' >> rq1.tex
echo '        x tick label style={rotate=90,font=\footnotesize},' >> rq1.tex
echo '        y tick label style={font=\tiny},' >> rq1.tex
echo '        ymode=log,' >> rq1.tex
echo '        log basis y={2},' >> rq1.tex
echo '        ytick pos=left,' >> rq1.tex
echo '        xtick pos=left,' >> rq1.tex
echo '        ymin=0.625,' >> rq1.tex
echo '        ymax=64,' >> rq1.tex
echo '        xmin=0.25,' >> rq1.tex
echo '        xmax=60.5,' >> rq1.tex
echo '        ymajorgrids,' >> rq1.tex
echo '        ytick={1,2,4,8,16,32,64},' >> rq1.tex
echo '        yticklabels={1x,2x,4x,8x,16x,32x,64x},' >> rq1.tex
echo '        ylabel=Testinium,' >> rq1.tex
echo '        y label style={at={(axis description cs:1.025,0.5)},font=\tiny},' >> rq1.tex
echo '        height=5cm,' >> rq1.tex
echo '        width=17cm,' >> rq1.tex
echo '        major tick length=2pt' >> rq1.tex
echo '    ]' >> rq1.tex
echo '' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomVertexFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomVertexSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomVertexSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomVertexEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomVertexNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomVertexHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomEdgeFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomEdgeSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomEdgeSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomEdgeEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomEdgeNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWQRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWRandomEdgeHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgePairFifty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgePairSixty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgePairSeventy};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgePairEighty};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgePairNinety};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumGWPlusEdgePairHundred};' >> rq1.tex
echo '        \addplot[mark=x,mark options={scale=0.5},boxplot,black] table {\TestiniumDJEdgePairHundred};' >> rq1.tex
echo '' >> rq1.tex
IFS=$'\n'
i=1
if [[ ${testiniumgwplusvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjvertexfifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomvertexfifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjvertexsixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomvertexsixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjvertexseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomvertexseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjvertexeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomvertexeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjvertexninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomvertexninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjvertexhundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomvertexhundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumvertex100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgefifty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomedgefifty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge50min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgesixty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomedgesixty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge60min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgeseventy} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomedgeseventy[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge70min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgeeighty} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomedgeeighty[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge80min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgeninety} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomedgeninety[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge90min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwqrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgehundred} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
sorted=($(sort <<<"${testiniumgwrandomedgehundred[*]}"))
if [[ ${sorted[0]} == "1" ]]; then echo "        \\node[label={270:{\\tiny{\$${testiniumedge100min}\$}}},inner sep=0pt,yshift=1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgepairfifty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair50min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgepairsixty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair60min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgepairseventy} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair70min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgepaireighty} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair80min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgepairninety} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair90min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumgwplusedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
if [[ ${testiniumdjedgepairhundred} == "1" ]]; then echo "        \\node[label={[rotate=90]0:{\\tiny{\$${testiniumedgepair100min}\$}}},inner sep=0pt,xshift=-.5pt,yshift=-1pt] at (axis cs:${i},1) {};" >> rq1.tex; fi
((i++))
unset IFS
echo '' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(4.5, 0.625) (3.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(8.5, 0.625) (8.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(12.5, 0.625) (12.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(16.5, 0.625) (16.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(20.5, 0.625) (20.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(24.5, 0.625) (24.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(28.5, 0.625) (28.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(32.5, 0.625) (32.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(36.5, 0.625) (36.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(40.5, 0.625) (40.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(44.5, 0.625) (44.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=black,solid] coordinates {(48.5, 0.625) (48.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(50.5, 0.625) (50.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(52.5, 0.625) (52.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(54.5, 0.625) (54.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(56.5, 0.625) (56.5, 4096)};' >> rq1.tex
echo '        \addplot+[mark=none,color=gray!70,dotted] coordinates {(58.5, 0.625) (58.5, 4096)};' >> rq1.tex
echo '' >> rq1.tex
echo '    \end{axis}' >> rq1.tex
echo '\end{tikzpicture}' >> rq1.tex

echo '\end{document}' >> rq1.tex

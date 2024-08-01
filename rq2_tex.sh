#!/usr/bin/env bash

value=$(sed "2q;d" rq2_002.csv | cut -d ',' -f 3)
tlc_dj_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_002.csv | cut -d ',' -f 34)
tlc_random_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_002.csv | cut -d ',' -f 65)
tlc_qrandom_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_002.csv | cut -d ',' -f 3)
tlc_dj_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_002.csv | cut -d ',' -f 34)
tlc_random_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_002.csv | cut -d ',' -f 65)
tlc_qrandom_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "6q;d" rq2_002.csv | cut -d ',' -f 3)
tlc_dj_edgepair=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_003.csv | cut -d ',' -f 3)
parabank_dj_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_003.csv | cut -d ',' -f 34)
parabank_random_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_003.csv | cut -d ',' -f 65)
parabank_qrandom_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_003.csv | cut -d ',' -f 3)
parabank_dj_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_003.csv | cut -d ',' -f 34)
parabank_random_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_003.csv | cut -d ',' -f 65)
parabank_qrandom_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "6q;d" rq2_003.csv | cut -d ',' -f 3)
parabank_dj_edgepair=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_004.csv | cut -d ',' -f 3)
testinium_dj_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_004.csv | cut -d ',' -f 34)
testinium_random_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_004.csv | cut -d ',' -f 65)
testinium_qrandom_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_004.csv | cut -d ',' -f 3)
testinium_dj_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_004.csv | cut -d ',' -f 34)
testinium_random_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_004.csv | cut -d ',' -f 65)
testinium_qrandom_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "6q;d" rq2_004.csv | cut -d ',' -f 3)
testinium_dj_edgepair=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_005.csv | cut -d ',' -f 3)
riscv_dj_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_005.csv | cut -d ',' -f 34)
riscv_random_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "2q;d" rq2_005.csv | cut -d ',' -f 65)
riscv_qrandom_vertex=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_005.csv | cut -d ',' -f 3)
riscv_dj_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_005.csv | cut -d ',' -f 34)
riscv_random_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "4q;d" rq2_005.csv | cut -d ',' -f 65)
riscv_qrandom_edge=$(jq -n "${value}|.*10000|round/100")

value=$(sed "6q;d" rq2_005.csv | cut -d ',' -f 3)
riscv_dj_edgepair=$(jq -n "${value}|.*10000|round/100")

avg_qrandom_vertex=$(jq -n "((${tlc_qrandom_vertex}+${riscv_qrandom_vertex}+${parabank_qrandom_vertex}+${testinium_qrandom_vertex})/4)|.*100|round/100")
avg_qrandom_edge=$(jq -n "((${tlc_qrandom_edge}+${riscv_qrandom_edge}+${parabank_qrandom_edge}+${testinium_qrandom_edge})/4)|.*100|round/100")
avg_qrandom=$(jq -n "((${avg_qrandom_vertex}+${avg_qrandom_edge})/2)|.*100|round/100")

avg_dj_vertex=$(jq -n "((${tlc_dj_vertex}+${riscv_dj_vertex}+${parabank_dj_vertex}+${testinium_dj_vertex})/4)|.*100|round/100")
avg_dj_edge=$(jq -n "((${tlc_dj_edge}+${riscv_dj_edge}+${parabank_dj_edge}+${testinium_dj_edge})/4)|.*100|round/100")
avg_dj_edgepair=$(jq -n "((${tlc_dj_edgepair}+${riscv_dj_edgepair}+${parabank_dj_edgepair}+${testinium_dj_edgepair})/4)|.*100|round/100")
avg_dj=$(jq -n "((${avg_dj_vertex}+${avg_dj_edge}+${avg_dj_edgepair})/3)|.*100|round/100")

avg_random_vertex=$(jq -n "((${tlc_random_vertex}+${riscv_random_vertex}+${parabank_random_vertex}+${testinium_random_vertex})/4)|.*100|round/100")
avg_random_edge=$(jq -n "((${tlc_random_edge}+${riscv_random_edge}+${parabank_random_edge}+${testinium_random_edge})/4)|.*100|round/100")
avg_random=$(jq -n "((${avg_random_vertex}+${avg_random_edge})/2)|.*100|round/100")

echo '\documentclass{article}' > rq2.tex
echo '\usepackage[export]{adjustbox}' >> rq2.tex
echo '\usepackage{multirow}' >> rq2.tex
echo '' >> rq2.tex
echo '\begin{document}' >> rq2.tex
echo '' >> rq2.tex
echo '\begin{table}[!t]' >> rq2.tex
echo '    \centering' >> rq2.tex
echo '    \begin{tabular}{|c|r|r|r|r|r|}' >> rq2.tex
echo '        \cline{2-5}' >> rq2.tex
echo '        \multicolumn{1}{c|}{} & \multicolumn{1}{c|}{\multirow{2}{*}{\bf Method}} & \multicolumn{3}{c|}{\bf Target Coverage (100\%)} \\' >> rq2.tex
echo '        \cline{3-5}' >> rq2.tex
echo '        \multicolumn{1}{c|}{} & & \multicolumn{1}{c|}{\bf Vertex} & \multicolumn{1}{c|}{\bf Edge} & \multicolumn{1}{c|}{\bf Edge-Pair} \\' >> rq2.tex
echo '        \cline{1-5}' >> rq2.tex
echo "        \\parbox[t]{2.125mm}{\\multirow{3}{*}{\\rotatebox[origin=c]{90}{\\scriptsize \\bf TLC}}} & GW-QRandom & \$${tlc_qrandom_vertex}\\%$ & \$${tlc_qrandom_edge}\\%$ & - \\\\" >> rq2.tex
echo "        & DJ & \$${tlc_dj_vertex}.00\\%$ & \$${tlc_dj_edge}.00\\%$ & \$${tlc_dj_edgepair}\\%$ \\\\" >> rq2.tex
echo "        & GW-Random & \$${tlc_random_vertex}\%$ & \$${tlc_random_edge}0\%$ & - \\\\" >> rq2.tex
echo '        \cline{1-5}' >> rq2.tex
echo "        \\parbox[t]{2.125mm}{\\multirow{3}{*}{\\rotatebox[origin=c]{90}{\\scriptsize \\bf RISC-V}}} & GW-QRandom & \$${riscv_qrandom_vertex}\\%$ & \$${riscv_qrandom_edge}\\%$ & - \\\\" >> rq2.tex
echo "        & DJ & \$${riscv_dj_vertex}\\%$ & \$${riscv_dj_edge}\\%$ & \$${riscv_dj_edgepair}\\%$ \\\\" >> rq2.tex
echo "        & GW-Random & \$${riscv_random_vertex}\%$ & \$${riscv_random_edge}\%$ & - \\\\" >> rq2.tex
echo '        \cline{1-5}' >> rq2.tex
echo "        \\parbox[t]{2.125mm}{\\multirow{3}{*}{\\rotatebox[origin=c]{90}{\\scriptsize \\bf Parab.}}} & GW-QRandom & \$${parabank_qrandom_vertex}\\%$ & \$${parabank_qrandom_edge}\\%$ & - \\\\" >> rq2.tex
echo "        & DJ & \$${parabank_dj_vertex}\\%$ & \$${parabank_dj_edge}\\%$ & \$${parabank_dj_edgepair}\\%$ \\\\" >> rq2.tex
echo "        & GW-Random & \$${parabank_random_vertex}\%$ & \$${parabank_random_edge}\%$ & - \\\\" >> rq2.tex
echo '        \cline{1-5}' >> rq2.tex
echo "        \\parbox[t]{2.125mm}{\\multirow{3}{*}{\\rotatebox[origin=c]{90}{\\scriptsize \\bf Testin.}}} & GW-QRandom & \$${testinium_qrandom_vertex}\\%$ & \$${testinium_qrandom_edge}\\%$ & - \\\\" >> rq2.tex
echo "        & DJ & \$${testinium_dj_vertex}\\%$ & \$${testinium_dj_edge}\\%$ & \$${testinium_dj_edgepair}\\%$ \\\\" >> rq2.tex
echo '        \cline{6-6}' >> rq2.tex
echo "        & GW-Random & \$${testinium_random_vertex}\%$ & \$${testinium_random_edge}\%$ & - & \\multicolumn{1}{c|}{\\bf Avg.} \\\\" >> rq2.tex
echo '        \hline' >> rq2.tex
echo '        \hline' >> rq2.tex
echo "        \\parbox[t]{2.125mm}{\\multirow{3}{*}{\\rotatebox[origin=c]{90}{\\scriptsize \\bf Avg.}}} & GW-QRandom & \$${avg_qrandom_vertex}\\%$ & \$${avg_qrandom_edge}\\%$ & - & \\bf ${avg_qrandom}\\% \\\\" >> rq2.tex
echo "        & DJ & \$${avg_dj_vertex}\\%$ & \$${avg_dj_edge}\\%$ & \$${avg_dj_edgepair}\\%$ & \\bf ${avg_dj}\\% \\\\" >> rq2.tex
echo "        & GW-Random & \$${avg_random_vertex}\\%$ & \$${avg_random_edge}\\%$ & - & \\bf ${avg_random}\\% \\\\" >> rq2.tex
echo '        \hline' >> rq2.tex
echo '    \end{tabular}' >> rq2.tex
echo '    \caption{Average Redundancies Compared to GWPlus}' >> rq2.tex
echo '    \label{tab:redundancies}' >> rq2.tex
echo '\end{table}' >> rq2.tex
echo '' >> rq2.tex
echo '\end{document}' >> rq2.tex

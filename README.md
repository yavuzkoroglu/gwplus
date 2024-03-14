# Gwplus: GraphWalker Plus

Computes the shortest test path that satisfies a coverage criterion for a GraphWalker model.

## Table of Contents

* [How to Build](#how-to-build)
* [Usage](#usage)
* [Experiments](#experiments)
* [Side Uses](#side-uses)

## How to Build

Open a terminal execute the following commands to clone and build `gwplus`:

```
git clone https://github.com/yavuzkoroglu/gwplus.git
cd gwplus
make -e MODE=release
```

Now, you are ready to use `gwplus`. Execute the following command to see how to use `gwplus`.

```
bin/gwplus
```

## Usage

You should obtain the following output after executing `bin/gwplus`:

```
GWPlus: Fast Optimal Test Generator for GraphWalker

Usage: gwplus <options>

GENERAL OPTIONS:
  -c,--coverage COVERAGE       Set the coverage criterion
  -C,--copyright               Output the copyright message and exit
  -H,--help                    Output this help message and exit
  -h,--hyperpaths TXT-FILE     Output the hyperpaths to a TXT file
  -i,--input JSON-FILE         (Mandatory) An input GraphWalker model in JSON format
  -m,--measure CUSTOM-TEST(s)  Output coverage of custom test(s)
  -p,--pathgraph DOT-FILE      Output the path graph to a DOT file
  -r,--requirements TXT-FILE   Output the test requirements to a TXT file
  -s,--simplegraph DOT-FILE    Output the simple graph to a DOT file
  -t,--tests JSON-FILE         Output a unified GraphWalker model with predefinedEdgeIds
  -u,--unify JSON-FILE         Output a unified GraphWalker model with no tests
  -v,--verbose                 Timestamped status information to stdout
  -V,--version                 Output version number and exit

COVERAGE OPTIONS:
  vertex                       All vertices of a GraphWalker model
  edge                         (Default) All edges of a GraphWalker model
  edgepair                     All edge-pairs of a GraphWalker model
  NUMBER                       All edge paths up to a length (0=vertex, 1=edge, etc.)
  prime1                       All prime vertex paths of a GraphWalker model
  prime2                       All prime vertex paths and edges of a GraphWalker model
  prime3                       All prime edge paths of a GraphWalker model
  TXT-FILE                     Custom test requirements from a TXT file

CUSTOM-TEST OPTIONS:
  -b,-g,--builtin,--given      Uses the predefinedEdgeIds of the input model
  TXT-FILE(s)                  Reads custom test(s) from TXT file(s)

EXAMPLE USES:
  bin/gwplus -i exps/001/m.json -c prime3 -s sg.dot -p pg.dot -h hp.txt -t test.json -v
  bin/gwplus -i exps/003/m.json -c 0 -t testpath.json -v
  bin/gwplus -i exps/003/m.json -c edge -m exps/003/t1.txt exps/003/t2.txt -v
  bin/gwplus -i exps/002/m.json -u unified.json -v
```

### Example #1

```
bin/gwplus -i exps/001/m.json -c prime3 -s sg.dot -p pg.dot -h hp.txt -t test.json -v
```

The first option in this example is `-i exps/001/m.json`. This option sets the input GraphWalker model to a toy graph. When opened in GraphWalker studio, this toy graph appears as below.

![The GraphWalker Model of a Toy Graph](exps/001/wellformed.png)

The second option `-c prime3` sets the coverage criterion to the highest setting.

The third option `-s sg.dot` generates the simple graph of the toy graph. After executing the example command, you can print the graph to the terminal using `cat sg.dot` and produce the following result.

```
digraph SimpleGraph {
    node [shape="rectangle"];
    reset [shape="none", label="", width=0, height=0];
    2 [label="2"];
    1 [label="1"];
    0 [label="0"];
    reset -> 0;
    2 -> 1 [label=""];
    2 -> 0 [label=""];
    1 -> 2 [label=""];
    0 -> 1 [label=""];
    0 -> 0 [label=""];
}
```

A visualization of the above DOT graph is below:

![The Simple Graph of the Toy Graph](exps/001/sg.pdf)

### Example #2

### Example #3

### Example #4

## Experiments

### Prerequisites

1. MacOS
2. Build *gwplus*: `make -e MODE=release`
3. The command-line JSON processor: `jq` [https://jqlang.github.io/jq/download/](https://jqlang.github.io/jq/download/)
4. GraphWalker CLI: `graphwalker-cli-4.3.2.jar` [https://graphwalker.github.io/#download](https://graphwalker.github.io/#download)
5. *gdate* utility: `brew install coreutils`

Execute the following BASH script to perform all the experiments:

```
./experiments.sh
```

## Side Uses

### Find Shortest Paths

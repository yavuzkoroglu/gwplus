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

Usage: gwplus -i <json-file> [options]

GENERAL OPTIONS:
  -c,--coverage COVERAGE       Set the coverage criterion
  -C,--copyright               Output the copyright message and exit
  -f,--finalgraph DOT-FILE     Outputs the finel test plan to a DOT file
  -H,--help                    Output this help message and exit
  -h,--hyperpathgraph DOT-FILE Output the hyperpath graph to a DOT file
  -i,--input JSON-FILE         (Mandatory) An input GraphWalker model in JSON format
  -m,--measure TXT-FILE(s)     Output coverage of custom test(s)
  -n,--netflow DOT-FILE        Output the minimum flow graph to a DOT file
  -p,--pathgraph DOT-FILE      Output the path graph to a DOT file
  -r,--requirements TXT-FILE   Output the test requirements to a TXT file
  -s,--simplegraph DOT-FILE    Output the simple graph to a DOT file
  -t,--tests JSON-FILE [PRCNT] Output test(s) with PRCNT% coverage (Default: 100%)
  -u,--unify JSON-FILE         Output a unified GraphWalker model with no tests
  -v,--verbose                 Timestamped status information to stdout
  -V,--version                 Output version number and exit

COVERAGE OPTIONS:
  vertex                       Vertices of a GraphWalker model
  edge                         (Default) Edges of a GraphWalker model
  edgepair                     Edge-pairs of a GraphWalker model
  edgetriple                   Edge-triples of a GraphWalker model
  NUMBER                       Edge paths up to a length (0=vertex, 1=edge, etc.)
  prime1                       Prime vertex paths of a GraphWalker model
  prime2                       Prime vertex paths and edges of a GraphWalker model
  prime3                       Prime edge paths of a GraphWalker model
  TXT-FILE                     Custom test requirements from a TXT file

EXAMPLE USES:
  bin/gwplus -i exps/001/m.json -c prime3 -s s.dot -p p.dot -f f.dot -t tModel.json -v
  bin/gwplus -i exps/001/m.json -m exps/001/generated/t2.txt
  bin/gwplus -i exps/001/m.json -c vertex -m exps/001/generated/t1.txt exps/001/generated/t2.txt
```

### Example #1

```
bin/gwplus -i exps/001/m.json -c prime3 -s s.dot -p p.dot -f f.dot -t tModel.json -v
```

The first option in this example is `-i exps/001/m.json`. This option sets the input GraphWalker model to a toy graph whose meta information is in `exps/001/info.json`. When opened in GraphWalker studio, this toy graph appears as follows:

![The GraphWalker Model of a Toy Graph](exps/001/m.png)

The second option `-c prime3` sets the coverage criterion to the highest setting.

The third option `-s s.dot` saves the simple graph of the toy graph. For coverage criteria settings higher than vertex coverage, the simple graph is a *line graph*, i.e., a graph where all edges are vertices and vice versa. After executing the example command, you can print the simple graph to the terminal using `cat s.dot` and produce the following result:

```
digraph SimpleGraph {
    node [shape="rectangle"];
    reset [shape="none", label="", width=0, height=0];
    10 [label="IH"];
    9 [label="HI"];
    8 [label="BH"];
    7 [label="GE"];
    6 [label="FG"];
    5 [label="EF"];
    4 [label="DE"];
    3 [label="DA"];
    2 [label="CD"];
    1 [label="BC"];
    0 [label="AB"];
    reset -> 0 [label="A"];
    10 -> 9 [label="H"];
    9 -> 10 [label="I"];
    8 -> 9 [label="H"];
    7 -> 5 [label="E"];
    6 -> 7 [label="G"];
    5 -> 6 [label="F"];
    4 -> 5 [label="E"];
    3 -> 0 [label="A"];
    2 -> 4 [label="D"];
    2 -> 3 [label="D"];
    1 -> 2 [label="C"];
    0 -> 8 [label="B"];
    0 -> 1 [label="B"];
}
```

A visualization of the above DOT graph is as follows:

![The Simple Graph of the Toy Graph](exps/001/generated/s.svg)

The fourth option `-p p.dot` saves the path graph of test requirements. A visualization of the path graph is below:

![The Path Graph of the Toy Graph](exps/001/generated/p.svg)

The fifth option `-f f.dot` saves the final test plan. A visualization of the test plan is below:

![The Final Test Plan of the Toy Graph](exps/001/generated/f.svg)

The sixth option `-t tModel.json` saves the model + a list of predefinedEdgeIds denoting a test path that satisfies the *prime3* coverage criterion. For this example, `gwplus` produces two test models. You can give the second test model to GraphWalker CLI using the following command:

```
java -jar graphwalker-cli-4.3.2.jar offline -m tModel_2.json "predefined_path(predefined_path)"
```

The GraphWalker CLI output should look like as follows:

```
{"currentElementName":"A"}
{"currentElementName":"AB"}
{"currentElementName":"B"}
{"currentElementName":"BC"}
{"currentElementName":"C"}
{"currentElementName":"CD"}
{"currentElementName":"D"}
{"currentElementName":"DA"}
{"currentElementName":"A"}
{"currentElementName":"AB"}
{"currentElementName":"B"}
{"currentElementName":"BC"}
{"currentElementName":"C"}
{"currentElementName":"CD"}
{"currentElementName":"D"}
{"currentElementName":"DA"}
{"currentElementName":"A"}
{"currentElementName":"AB"}
{"currentElementName":"B"}
{"currentElementName":"BH"}
{"currentElementName":"H"}
{"currentElementName":"HI"}
{"currentElementName":"I"}
{"currentElementName":"IH"}
{"currentElementName":"H"}
{"currentElementName":"HI"}
{"currentElementName":"I"}
{"currentElementName":"IH"}
{"currentElementName":"H"}
```

The final option `-v` enables verbose messages in output. A correct execution should produce something similar to the following timestamped output:

```
[2024-05-23 23:35:52] - Verbose enabled.
[2024-05-23 23:35:52] - Input Model File = exps/001/m.json
[2024-05-23 23:35:52] - Coverage Criterion = Prime Edge Path Coverage
[2024-05-23 23:35:52] - Simple Graph Name = s.dot
[2024-05-23 23:35:52] - Path Graph File = p.dot
[2024-05-23 23:35:52] - Final Test Plan File = f.dot
[2024-05-23 23:35:52] - Output Model File with Predefined Edges = tModel.json
[2024-05-23 23:35:52] - Coverage Percent = 100%
[2024-05-23 23:35:52] - Creating Empty GraphWalker Model...
[2024-05-23 23:35:52] - Filling the GraphWalker Model using 'exps/001/m.json'
[2024-05-23 23:35:52] - Filling adjacency lists to optimize path generation...
[2024-05-23 23:35:52] - Starting Element is a VERTEX
[2024-05-23 23:35:52] - # Vertices = 9
[2024-05-23 23:35:52] - # Edges = 11
[2024-05-23 23:35:52] - Saving the simple graph to 's.dot'...
[2024-05-23 23:35:52] - Generating/Loading Test Requirements...
[2024-05-23 23:35:52] - Generating Path Graph...
[2024-05-23 23:35:52] - Optimization Level = 0
[2024-05-23 23:35:52] - Saving path graph to 'p.dot'
[2024-05-23 23:35:52] - Generating Hyperpath Graph...
[2024-05-23 23:35:52] - Generating Network Flow Graph with Hyperpaths...
[2024-05-23 23:35:52] - Minimizing Total Flow...
[2024-05-23 23:35:52] - Expanding the Network Flow Graph...
[2024-05-23 23:35:52] - Initializing a new flow with test requirement constraints...
[2024-05-23 23:35:52] - Computing a feasible flow...
[2024-05-23 23:35:52] - Minimizing the flow...
[2024-05-23 23:35:52] - Generating the Final Test Plan...
[2024-05-23 23:35:52] - Saving the final test plan to 'f.dot'
[2024-05-23 23:35:52] - LengthOf(Test #1) = 14
[2024-05-23 23:35:52] - Saving to 'tModel_1.json'
[2024-05-23 23:35:52] - LengthOf(Test #2) = 14
[2024-05-23 23:35:52] - Saving to 'tModel_2.json'
[2024-05-23 23:35:52] - # Tests = 2
[2024-05-23 23:35:52] - Total Test Length = 28
[2024-05-23 23:35:52] - Finished.
```

### Example #2

```
bin/gwplus -i exps/001/m.json -m exps/001/generated/t2.txt
```

The above command measures the edge coverage of the test located in `t2.txt` and produces the following result:

```
63%
```

### Example #3

```
bin/gwplus -i exps/001/m.json -c vertex -m exps/001/generated/t1.txt exps/001/generated/t2.txt
```

The above command measures the collective vertex coverage of the tests located in `t1.txt` and `t2.txt`, producing the following result:

```
100%
```

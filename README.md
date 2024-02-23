# Gwplus: GraphWalker Plus

Computes the shortest test path that satisfies a coverage criterion for a GraphWalker model.

## Table of Contents

* [How to Build](#how-to-build)
* [Usage](#usage)
* [Examples](#examples)
    - [Toy Graph](#toy-graph)
    - [TLC](#tlc)
* [Known Issues](#known-issues)
	 - [Half Debug Half Release Builds](#half-debug-half-release-builds)

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

`gwplus` usage syntax:

```
Usage: gwplus (edge|prime|vertex) <GraphWalker-JSON-file> <output-JSON-file> [-v]
```

### Coverage Parameter `edge|prime|vertex`

- **edge**: Edge Coverage
- **prime**: Prime Path Coverage
- **vertex**: Vertex Coverage

### Optional Verbose Parameter `-v`

Prints timestamped status messages to `stdout`. Omitting verbose messages may speed up test generation.

## Examples

### Toy Graph

![Toy Graph Model](examples/toygraph/wellformed.png)

Use the following command to generate the test path that satisfy prime path coverage for the graph above:

```
bin/gwplus prime examples/toygraph/wellformed.json testpath.json -v
```

The output of the command above should be:

```
[2024-02-21 15:52:37] - Verbose enabled.
[2024-02-21 15:52:37] - Coverage Criterion = Prime Path Coverage
[2024-02-21 15:52:37] - Loading examples/toygraph/wellformed.json...
[2024-02-21 15:52:37] - Starting Element is an EDGE
[2024-02-21 15:52:37] -          # Vertices = 2
[2024-02-21 15:52:37] -             # Edges = 3
[2024-02-21 15:52:37] -        # Edge Pairs = 5
[2024-02-21 15:52:37] - # Test Requirements = 6
[2024-02-21 15:52:37] -    # Direct Splices = 14
[2024-02-21 15:52:37] -        # HyperPaths = 2
[2024-02-21 15:52:37] -         # TestPaths = 1
[2024-02-21 15:52:37] -  LengthOf(TestPath) = 9
[2024-02-21 15:52:37] - Dumping the final model to testpath.json...
[2024-02-21 15:52:37] - Finished
```

To reproduce this predefined test, you can use the GraphWalker Command-Line Interface (CLI) as follows:

```
java -jar graphwalker-cli-<version>.jar offline -m testpath.json "predefined_path(predefined_path)"
```

The output of the command above should be:

```
{"currentElementName":"0"}
{"currentElementName":""}
{"currentElementName":"0"}
{"currentElementName":""}
{"currentElementName":"0"}
{"currentElementName":""}
{"currentElementName":"1"}
{"currentElementName":""}
{"currentElementName":"2"}
{"currentElementName":""}
{"currentElementName":"0"}
{"currentElementName":""}
{"currentElementName":"1"}
{"currentElementName":""}
{"currentElementName":"2"}
{"currentElementName":""}
{"currentElementName":"1"}
{"currentElementName":""}
{"currentElementName":"2"}
{"currentElementName":""}
```

Use the following command to see some of the internal variables computed to generate the test path:

```
bin/toygraph
```

### TLC

For edge coverage:

```
bin/gwplus edge examples/tlc/wellformed.json testpath.json
```

For prime coverage:

```
bin/gwplus prime examples/tlc/wellformed.json testpath.json
```

For vertex coverage:

```
bin/gwplus vertex examples/tlc/wellformed.json testpath.json
```

## Known Issues

### Half Debug Half Release Builds

#### Symptoms

During execution you may get the following error:

```
Failed Assertion => (constructEmpty_chunk( chunk_model_ids, (size_t)initial_cap_models * guess_id_str_len, initial_cap_models ))
Error in src/gwmodel.c::constructEmpty_gwma():XXXX
```

#### Reason

In `debug` builds, `constructEmpty_chunk()` returns `bool`. In `release` builds, it is a `void` function. If some parts of the binary are in `debug` mode whereas the others are in `release` mode, the `debug` mode code may try to assert the return value, leading to an error.

#### Solution

Please execute the following command and then rebuild.

```
make clean
```

To rebuild, `make` or `make -e MODE=release`.

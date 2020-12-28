## Instances and Solution Checker KP01

See [CombZoo](https://github.com/CombZoo) and [CombZoo guidelines](https://github.com/CombZoo/combzoo-guidelines) for more information.

### Example of Solution Checker for 0-1 Knapsack Problem

#### Main Build

Just open file: `mainSolKP01.cpp`

#### Main Build with Bazel 

To build: `bazel build ...`

To run: `./bazel-bin/app_solcheck_KP01 --solution solution.json `

#### Solver Library via Bazel

See files: `src/solcheck_kp01.h` and `solcheck_kp01.cpp`.

### general advices for bazel
Finding available packages with bazel.

local components:
bazel query 'attr(visibility, "//visibility:public", ...)'

remote OptFrame packages:
bazel query @OptFrame//...
bazel query 'attr(visibility, "//visibility:public", "@OptFrame//...")'


list label hdrs:
bazel query 'labels(hdrs, ...)'

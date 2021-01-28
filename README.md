# How to generate the C file from the PDDL file:
'$ python main.py pfile03-011.pddl ccarpark.c'

# How to run with TracerX:
'TX $ ./llvm-3.4.2/Release/bin/clang -I tracerx/include -emit-llvm -c -g ccarpark.c -o ccarpark.bc'
'TX $ ./tracerx/Release+Asserts/bin/klee -solver-backend=z3 --search=dfs -output-dir=path_to_output_dir ccarpark.bc'

# How to run with KLEE in Docker:
'$ clang -I ../../include -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone ccarpark.c'
'$ klee ccarpark.bc'

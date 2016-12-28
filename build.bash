clang++ ../purec/sleefsp.c main.cpp -std=c++14 -O3 -ffp-contract=off -Wall -DNDEBUG -DENABLE_SSE2  -I../purec && ./a.out


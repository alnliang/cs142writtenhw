#include <cmath>
#include <cstdlib>
#include <iostream>

#include "parallel.h"
#include "get_time.h"

using namespace parlay;

void compute0 (int n) {
    int *a = new int[n];
    parallel_for(0, n, [&](int i){
        a[i] = i;
    });
// start timer
    timer t;
    parallel_for(0, n, [&](int j){
        a[j] *= 10;
    });
    t.stop();
    std::cout << "Compute0 runtime: " << t.total_time() << "\n";
// end timer
}

void compute1 ( int n ) {
    int *a = new int [n ];
    parallel_for(0, n, [&](int i){
        a[i] = i;
    });
    // start timer
    timer t;
    parallel_for(0, n, [&](int i){
        a[(( long long )i *93) %n ] *= 10;
    });
    t.stop();
    std::cout << "Compute1 runtime: " << t.total_time() << "\n";
    // end timer
}

void compute2(int n, int k){
    int *a = new int [n ];
    parallel_for(0, n, [&](int i){
        a[i] = i;
    });
    timer t;
    parallel_for(0, n * k, [&](long long i){
         a[( long long ) i%n ]++;
    }); 
    t.stop();
    std::cout << "Compute2 runtime: " << t.total_time() << "\n";
}

void compute3(int n, int k, int m){
    int *a = new int [n ];
    parallel_for(0, n, [&](int i){
        a[i] = i;
    }); 
    timer t;
    parallel_for(0, n / m, [&](int i){
        for ( int l =0; l <k; l ++){
            for ( int j=i *m; j <( i +1) * m; j ++){
                a[j ]++;
            }
        }
    });
    t.stop();
    std::cout << "Compute3 runtime: " << t.total_time() << "\n";
}

int main(){
    compute0(1000000000);
    compute1(1000000000);
    compute2(1000000000, 5);
    compute3(1000000000, 5, 10000);
}
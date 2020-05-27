/* The 3n + 1 Problem */
/* PC/UVa IDs: 110101/100, Popularity: A, Success rate: low, Level: 1 */
#include <cstdio>

int get_cycleLength(int n){
    int count = 1;

    while(n != 1){
        // odd
        if(n & 1){
            n = n * 3 + 1;
        }
        // even
        else{
            n = n >> 1;
        }

        count++;
    }

    return count;
}

int main(){
    int n1, n2;

    while(scanf("%d%d", &n1, &n2) == 2){
        // initialize
        int t1 = (n1 < n2) ? n1 : n2,   // min
            t2 = (n2 > n1) ? n2 : n1,   // max
            max = 0;     

        // Find the maximum cycle length for integers between and including t1 and t2
        for(int i = t1; i <= t2; i++){
            int cycleLength = get_cycleLength(i);
            
            if(cycleLength > max)
                max = cycleLength;
        }

        printf("%d %d %d\n", n1, n2, max);
    }
    
    return 0;
}
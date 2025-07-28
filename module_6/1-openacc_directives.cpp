#include <iostream>
using namespace std;

const int N = 100;

int main() {
    float a[N], b[N], c[N];

    // Initialize input arrays
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    // OpenACC data region:
    // - copyin(a, b): copies arrays a and b from host (CPU) to device (GPU) at the start
    // - copyout(c): copies array c from device (GPU) back to host (CPU) at the end 
    #pragma acc data copyin(a, b) copyout(c)
    {
        // Begin parallel region on GPU
        #pragma acc parallel
        {
            // Loop over the array
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
            }
        }
    }

    // Print result
    for (int i = 0; i < 5; i++) {
        cout << "c[" << i << "] = " << c[i] << endl;
    }

    return 0;

    /* Output:
        c[0] = 0
        c[1] = 3
        c[2] = 6
        c[3] = 9
        c[4] = 12
    */
}

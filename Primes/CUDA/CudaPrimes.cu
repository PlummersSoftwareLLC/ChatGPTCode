// (Davepl) Write a 20-line explanation of how this program works for the next programmer who has to look at it.  Write it as a C++ comment.

/* 
    This program is a segmented prime sieve that makes use of the CUDA API to perform the sieve calculation on the GPU. 
    The program first allocates the necessary memory on the CPU and then transfers the memory to the GPU. 
    The primeSieveKernel function, which is executed on the GPU, performs the sieve calculation by marking multiples 
    of prime numbers as non-prime (1). Stream compaction is used to compact the list of prime numbers into an array
    of only prime numbers, which is then copied back to the CPU for processing. The for loop in the primeSieveKernel 
    function iterates from 3 to sqrt(n) and marks multiples of prime numbers as non-prime. The segSieveKernel function 
    is used to divide the sieve calculation into segments and evenly distribute the work among multiple CUDA threads. 
    The final result of the program is a list of all prime numbers up to a specified number (n).
*/

// (Davepl) Now rewrite it with the comment symbol in front of each line, and use a surfer-dude dialect

// Yo dude, this here code is a prime sieve written in C++, but it's super chill cuz it uses CUDA API to run on the GPU.
// The main idea is that we wanna find all the prime numbers up to some big number, say 100 million.
// But like, finding all those primes can be a real drag on the CPU.
// So, we hand off the heavy lifting to the GPU, which is way faster, man.
// The trick is to break up the 100 million into smaller chunks, or "segments", and then run the sieve on each segment.
// Then we take all those prime numbers we found and use them to sieve out the next segment, and so on.
// The end result is that we have all the primes up to 100 million, and we did it super fast, dude.
//
// Alright, let's "dive" in.
// First up, we got the main function. It sets everything up, including allocating memory on the GPU.
// Then we got the primeSieveKernel function, which is what actually does the sieve on the GPU.
// This function takes in the start and end of the segment we're working on, and a pointer to the memory we allocated on the GPU.
// Inside the kernel, we use a for loop to check each number in the segment and see if it's prime.
// If it's not prime, we set it to 0 in the GPU memory.
// Once the kernel is done, we use cudaMemcpy to copy the GPU memory back to the CPU so we can see the results.
//
// Finally, we wrap it up with a unified memory version, which is even more dope cuz it
// ..
// [network error]
// ..
// automatically handles the memory transfer between CPU and GPU.
// Basically, we just declare the variables we need as "unified memory" and the GPU and CPU can access it as needed.
// No need to use cudaMemcpy, it's all handled behind the scenes, bro.
// That's it, man. Just a quick rundown of this rad prime sieve program that's blazing fast on the GPU.  Broh.

#include <iostream>
#include <cmath>
#include <cuda_runtime.h>

const int n = 100000000;                

#define CUDA_CALL(x) do { if((x) != cudaSuccess) { \
    std::cerr << "Error: " << cudaGetErrorString(x) << std::endl; \
    exit(EXIT_FAILURE);}} while(0)

__global__ void primeSieveKernel(int *numbers, int sqrt_n) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < sqrt_n) {
        int j = 2 * i + 3;
        for (int k = i + j; k < (n / 2); k += j) {
            numbers[k] = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    
    int sqrt_n = (int)sqrt(n);
    int blockSize = 256;

    // Allocate unified memory
    int *_numbers;
    CUDA_CALL(cudaMallocManaged(&_numbers, (n / 2) * sizeof(int)));

    // Set initial values for numbers
    for (int i = 0; i < (n / 2); i++)
        _numbers[i] = 0;

    dim3 block(blockSize, 1, 1);
    dim3 grid((int)ceil(sqrt_n / (double)blockSize), 1, 1);

    // Launch the kernel on the GPU
    primeSieveKernel<<<grid, block>>>(_numbers, sqrt_n);

    // Wait for the GPU to finish
    CUDA_CALL(cudaDeviceSynchronize());

    // Print the number of primes
    int count = 1;
    for (int i = 0; i < n / 2; i++)
        count += (_numbers[i] == 0);

    std::cout << count << " primes found." << std::endl;

    // Free the memory
    CUDA_CALL(cudaFree(_numbers));
    return 0;
}
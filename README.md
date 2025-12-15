# TriKonv

TriKonv is a project I completed for CMSC818J at the University of Maryland in Fall 2025.
This repository contains the code used for the experiments.
Below I document the code and its organization.

## Organization

The repository contains the following C++ code files:

- `header.h` serves as a header file for all other code files.
- `evaluation.cpp` is the program entrypoint, and contains code to check correctness and evaluation CPU time taken by the convolution algorithms.
- `baselines.cpp` includes implementations for the two baselines tested (a naive algorithm and an FFT-based algorithm)
- `hikonv_unsigned.cpp` includes implementations for the unsigned variant of HiKonv.
- `hikonv_signed.cpp` includes implementations for the signed variant of HiKonv.
- `trikonv.cpp` includes implementations for TriKonv.

There is additionally a Kotlin code file `OptimizeParameters.kt`,
which was used to determine the optimal choice of parameters `N, K` for each algorithm
based on the theoretical analysis.

## `header.h`

The header file mainly includes the `Algorithm` struct as well as some additional includes.
The `Algorithm` struct defines a convolution algorithm via the following parameters:
- A function pointer to the actual C++ function for the algorithm.
- The human-readable name of the algorithm.
- The bounds that the input quantized values should satisfy.
- Whether the sequence and kernel can be swapped when applying the algorithm.

## `evaluation.cpp`

This file includes the `main` function that performs the experiment.
The top of the file includes various parameters that can be changed.

The following parameters must be varied to perform experiments:
- `SIGNED` determines whether values are quantized to the range `{-1, 0, 1}` or `{0, 1, 2}`.
- `SWAPPED` determines whether the sequence and kernel are swapped when input to the algorithms.

The following parameters can be changed:
- `DEBUG`, when set to `true`, outputs additional information (should only be used if the input sizes are small)
- `NUM_TRIALS` is the number of trials to run.
- `LARGE_SIZE` is the length of the input sequence.
- `SMALL_SIZE` is the length of the input kernel.

An additional parameter, `ALGORITHMS`, contains a list of all algorithms implemented in the repository.
Some can be commented out to exclude them from the experiment, but `NAIVE` must always remain first.
Additional parameters are not documented here and should not be changed.

When the program is run, the applicable algorithms (depending on `SIGNED` and `SWAPPED`) are evaluated
on `NUM_TRIALS` randomly generated input values, their correctness is checked against the naive algorithm.
The first incorrect algorithm is reported. If all algorithms are correct, results are reported,
containing average times for each algorithm.

## `baselines.cpp`

This file contains implementations for the naive algorithm and the FFT-based algorithm in that order.
The FFT-based algorithm's implementation is divided into a function performing a fast Fourier transform,
a function performing an inverse fast Fourier transform, and a function that uses those functions
to compute the convolution.

## `hikonv_unsigned.cpp`

This file contains implementations for the unsigned variant of HiKonv.
The first function contains the "blueprint" implementation that uses C++ templates
and can be applied with any choice of parameters `N, K`.
The following functions are optimized for specific choices of parameters `N, K`.
The final function uses 128-bit integers instead of 64-bit integers.

## `hikonv_signed.cpp`

This file contains implementations for the signed variant of HiKonv.
The first function contains the "blueprint" implementation that uses C++ templates
and can be applied with any choice of parameters `N, K`.
The following functions are optimized for specific choices of parameters `N, K`.

## `trikonv.cpp`

This file contains implementations for TriKonv.
The first function contains the "blueprint" implementation that uses C++ templates
and can be applied with any choice of parameters `N, K`.
The following functions are optimized for specific choices of parameters `N, K`.
The final function's choice of `N, K` allows it to handle signed 2-bit quantization
(meaning that quantized values come from the set `{-2, -1, 0, 1}`).

## `OptimizeParameters.kt`

Each function corresponds to one of unsigned HiKonv, signed HiKonv, or TriKonv,
and determines which choice of `N, K` delivers the best performance (latency)
based on the theoretical analysis performed in the report.
The functions are based on the core algorithms and take an argument
describing the actual quantization format.
Running the program will report these optimal parameters for all three
for the relevant quantization considered.

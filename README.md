# NAG Optimization Modelling Suite UI

A C++ user interface design for the NAG (Numerical Algorithms Group) Optimization Modelling Suite, developed at RWTH Aachen.

## Overview

This project provides a modern C++ interface for the NAG Optimization Modelling Suite, making it easier to work with numerical optimization problems, automatic differentiation, and algorithmic differentiation using NAG's tools.

## Features

- Modern C++20 interface for NAG libraries
- Automatic/Algorithmic differentiation support via DCO/C++
- Comprehensive test suite
- Case studies demonstrating practical applications
- CMake-based build system

## Prerequisites

- C++20 compliant compiler
- CMake 3.16 or higher
- NAG Library (commercial license required)
- NAG DCO/C++ (commercial license required)
- NAG C++ Interface

## Project Structure

```
.
├── cmake/                      # CMake modules and configuration
│   └── FindNAG_dco_cpp.cmake  # NAG DCO/C++ finder script
├── examples/                   # Example code demonstrating usage
│   └── dco_hessian/           # Hessian computation example
├── caseStudies/               # Real-world application examples
├── tests/                     # Test suite
├── include/                   # Header files
└── thirdParty/               # Third-party dependencies
    └── nag_cpp/              # NAG C++ interface
```

## Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd nag-optimization-modelling-suite-ui
   ```

2. Set up NAG environment:
   ```bash
   export NAG_LIBRARY_PATH=/path/to/nag/library
   export DCO_ROOT=/path/to/dco/installation
   ```

3. Configure and build:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

## Common Issues

1. Include Path Errors:
   - Ensure NAG_CPP_DIR is correctly set in CMakeLists.txt
   - Verify NAG library installation path
   - Check if nag_cpp.hpp is accessible in the include path

2. Library Not Found:
   - Verify NAG_LIBRARY_PATH environment variable
   - Check if NAG license is valid and active
   - Ensure DCO_ROOT points to valid installation

## Documentation

Refer to userGuide.pdf in /doc for detailed usage instructions.

## Authors

### Group 6:
- Tran Man Khang (khang.tran@rwth-aachen.de)
- Feldman Maksim (maksim.feldman@rwth-aachen.de)
- Valiyev Ziya (ziya.valiyev@rwth-aachen.de)
- Korkin Konstantin (konstantin.korkin@rwth-aachen.de)
- Huang Yifei (yifei.huang@rwth-aachen.de)

### Supervisor:
- Johannes Lotz (lotz@stce.rwth-aachen.de)

## License

This project requires commercial licenses for:
- NAG Library
- NAG DCO/C++

Contact NAG (Numerical Algorithms Group) for licensing information.

## Contact

For technical questions and support:
info@stce.rwth-aachen.de

## Contributing

This project is developed at RWTH Aachen. Please contact the development team before making contributions.

## Acknowledgments

- Numerical Algorithms Group (NAG) for their optimization tools
- Software and Tools for Computational Engineering, RWTH Aachen 


### REF (chatGPT)

In the provided example, two main dependencies are used: Eigen and qpOASES. Below are the steps to acquire these libraries:

1. Eigen: Eigen is a C++ template library for linear algebra. You can download it from the [Eigen official website](http://eigen.tuxfamily.org/). The source files are header-only, meaning you do not need to compile anything to use it in your code. You simply need to include the path to the Eigen header files in your project.

2. qpOASES: qpOASES is a library for solving Quadratic Programming problems. It's an open-source project hosted on [GitHub](https://github.com/coin-or/qpOASES). To install it, you would typically clone the repository and then follow the provided build instructions. It's a C++ library so you will have to compile the source code to get a library file which you link to your own project.

To compile the example I gave, you'll need to tell the compiler where to find these libraries. If you're using a build system like CMake, this would involve setting the appropriate include and link directories to the directories containing the Eigen headers and the compiled qpOASES library, respectively.

Please note that the actual steps to install and use these libraries can depend on your specific environment and setup. Always refer to the official, up-to-date documentation provided with each library for the best instructions.
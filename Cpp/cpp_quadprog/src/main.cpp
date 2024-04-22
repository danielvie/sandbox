#include <qpOASES.hpp>
#include <Eigen/Dense>
#include <iostream>

int main()
{
    USING_NAMESPACE_QPOASES

    // Use Eigen's matrix and vector types for convenient and intuitive linear algebra
    Eigen::MatrixXd H(2,2);
    H << 1.0, 0.0,
         0.0, 0.5;
         
    Eigen::VectorXd g(2);
    g << 1.5, 1.0;

    Eigen::MatrixXd A(1,2);
    A << 1.0, 1.0;

    Eigen::VectorXd lb(2);
    lb << 0.5, -2.0;

    Eigen::VectorXd ub(2);
    ub << 5.0, 2.0;

    Eigen::VectorXd lbA(1);
    lbA << -1.0;

    Eigen::VectorXd ubA(1);
    ubA << 2.0;

    // Setup QProblem object. Sizes are number of variables and number of constraints.
    QProblem example(2, 1);

    // Solve the QP problem. Note that qpOASES expects row-major format, so we need to transpose matrices.
    int nWSR = 10;
    example.init(H.data(), g.data(), A.transpose().data(), lb.data(), ub.data(), lbA.data(), ubA.data(), nWSR);

    // Get the solution
    Eigen::VectorXd xOpt(2);
    example.getPrimalSolution(xOpt.data());

    std::cout << "Optimal solution:\n" << xOpt << "\n";

    return 0;
}

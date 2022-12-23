// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	y = pow(x[0], 2) + pow(x[1], 2) + pow(0.5 * x[0] + x[1], 2) + pow(0.5 * x[0] + x[1], 4);
};

// Constraint function
auto constraint_problem = [](auto const &x, auto &y)
{
	y.resize(1);
	y[0] = pow(x[0], 2) + pow(x[1], 2) - pow(1 + 0.2 * cos(8 * atan(x[0] / x[1])), 2);
};

int main()
{
	try
	{
		// Problem parameter
		double const INF = 1e19;

		nagcpp::types::f77_integer nvar = 2;
		std::vector<double> x = {0.228, 0.85};

		std::vector<double> b_lower = {-5, -5};
		std::vector<double> b_upper = {10, 10};

		std::vector<double> l_lower = {0.0};
		std::vector<double> l_upper = {0.0};
		std::vector<double> a = {0.0, 0.0};

		std::vector<double> n_lower = {-1.0e20};
		std::vector<double> n_upper = {0};

		// Problem definition
		nagcpp::opt::Problem problem(nvar, test_problem);
		problem.set_initial_values(x);
		problem.set_simple_bounds(b_lower, b_upper);
		problem.set_linear_bounds(l_lower, l_upper, a);
		problem.set_nonlinear_bounds(n_lower, n_upper, constraint_problem);

		// Solve
		nagcpp::opt::Solver solver(nvar);
		solver.solve(problem);

		// Monitoring
		std::cout << solver;
	}
	catch (nagcpp::error_handler::Exception &error)
	{
		std::cout << error.msg << std::endl;
	}
}

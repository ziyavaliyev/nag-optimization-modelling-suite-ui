// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
using namespace std;

// Minimizes f(x) = x_1^2 + x_2^2
// with respect to x_1 in [-1, 0.8], x_2 in [-2, 2]

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	y = -cos(x[0]) * cos(x[1]) * exp(-(pow(x[0] - M_PI, 2) + pow(x[1] - M_PI, 2)));
};

int main()
{
	try
	{
		// Problem parameter
		nagcpp::types::f77_integer nvar = 2;
		std::vector<double> x = {2, 3};
		std::vector<double> b_lower = {-1, -1};
		std::vector<double> b_upper = {3 * M_PI / 4, 6};

		// Problem definition
		nagcpp::opt::Problem problem(nvar, test_problem);
		problem.set_initial_values(x);
		problem.set_simple_bounds(b_lower, b_upper);

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

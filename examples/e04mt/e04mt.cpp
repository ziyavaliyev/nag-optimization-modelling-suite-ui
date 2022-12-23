// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	std::vector<double> coefs = {-0.02, -0.20, -0.20, -0.20, -0.20, 0.04, 0.04};
	for (int i = 0; i < coefs.size(); ++i)
	{
		y += x[i] * coefs[i];
	}
};

int main()
{
	try
	{
		// Problem parameter
		nagcpp::types::f77_integer nvar = 7;
		std::vector<double> x;

		std::vector<double> coefs = {-0.02, -0.20, -0.20, -0.20, -0.20, 0.04, 0.04};

		std::vector<double> b_lower = {-0.01, -0.1, -0.01, -0.04, -0.1, -0.01, -0.01};
		std::vector<double> b_upper = {0.01, 0.15, 0.03, 0.02, 0.05, 1.0e20, 1.0e20};

		std::vector<double> l_lower = {-0.13, -1.0e20, -1.0e20, -1.0e20, -1.0e20, -0.0992, -0.003};
		std::vector<double> l_upper = {-0.13, -0.0049, -0.0064, -0.0037, -0.0012, 1.0e20, 0.002};
		std::vector<double> a = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
								 0.15, 0.04, 0.02, 0.04, 0.02, 0.01, 0.03,
								 0.03, 0.05, 0.08, 0.02, 0.06, 0.01, 0.00,
								 0.02, 0.04, 0.01, 0.02, 0.02, 0.00, 0.00,
								 0.02, 0.03, 0.00, 0.00, 0.01, 0.00, 0.00,
								 0.70, 0.75, 0.80, 0.75, 0.80, 0.97, 0.00,
								 0.02, 0.06, 0.08, 0.12, 0.02, 0.01, 0.97};

		// Problem definition
		nagcpp::opt::Problem problem(nvar, test_problem);
		problem.set_initial_values(x);
		problem.set_simple_bounds(b_lower, b_upper);
		problem.set_linear_bounds(l_lower, l_upper, a);

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

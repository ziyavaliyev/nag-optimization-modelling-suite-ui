// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	std::vector<double> coefs = {1.00, 3.00, -2.00};
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
		nagcpp::types::f77_integer nvar = 3;
		std::vector<double> x;

		std::vector<double> b_lower = {-5.00, -5.00, 0.00};
		std::vector<double> b_upper = {15.00, 2.00, 0.00};

		std::vector<double> l_lower = {-10.00, -1.0e20};
		std::vector<double> l_upper = {10.00, -12.00};
		std::vector<double> a = {1.00, -1.00, 0.00, -3.00, 0.00, 10.00};

		std::vector<double> coefs = {1.00, 3.00, -2.00};

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

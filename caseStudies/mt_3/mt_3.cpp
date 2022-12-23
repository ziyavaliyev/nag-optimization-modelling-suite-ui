// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	std::vector<double> coefs = {1.00, -1.00};
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
		nagcpp::types::f77_integer nvar = 2;
		std::vector<double> x;

		std::vector<double> b_lower = {-50.00, -45.00};
		std::vector<double> b_upper = {100.00, 80.00};

		std::vector<double> l_lower = {-4.00, -95.00, 0.00, -20.00};
		std::vector<double> l_upper = {45.00, 15.00, 28.00, 1.00};
		std::vector<double> a = {1.00, 2.00, 4.00, 3.00, -7.00, 1.00, 0.00, 0.00};

		std::vector<double> coefs = {1.00, -1.00};

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

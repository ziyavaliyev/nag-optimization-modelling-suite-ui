#include "nag_cpp.hpp"
using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	std::vector<double> coefs = {-2, 4, 7};
	for (int i = 0; i < coefs.size(); ++i)
	{
		y += x[i] * coefs[i];
	}
};

int main()
{
	// Problem parameter
	nagcpp::types::f77_integer nvar = 3;
	std::vector<double> x;

	std::vector<double> b_lower = {-3.00, -5.0, 0};
	std::vector<double> b_upper = {6.0, 5.0, 1.0e20};

	std::vector<double> l_lower = {-12, -1.0e20, -25};
	std::vector<double> l_upper = {1.0e20, 0, 10.0};
	std::vector<double> a = {1.00, 1.00, 1.00, 3.00, 2.00, 1.00, 0.00,
							 -4.00, 7};

	std::vector<double> coefs = {-2, 4, 7};

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
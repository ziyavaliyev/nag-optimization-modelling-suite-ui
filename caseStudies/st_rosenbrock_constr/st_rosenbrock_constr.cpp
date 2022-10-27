#include "nag_cpp.hpp"

using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	y = pow(1 - x[0], 2) + 100*pow(x[1] - pow(x[0], 2), 2);
};

// Constraint function
auto constraint_problem = [](auto const &x, auto &y)
{
	y.resize(1);
	y[0] = 0;
};


int main() {
	//Problem parameter
        double const INF = 1e19;

	nagcpp::types::f77_integer nvar = 2;
	std::vector<double> x = {0, 0.25};


	std::vector<double> b_lower = {-1.5, -1.5};
    	std::vector<double> b_upper = {2.5, 2.5};

	std::vector<double> l_lower = {-1, -0.5};
	std::vector<double> l_upper = {3, 1.5};
	std::vector<double> a = {1.0, 1.0, -1.0, 1.0};

	std::vector<double> n_lower = {0};
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

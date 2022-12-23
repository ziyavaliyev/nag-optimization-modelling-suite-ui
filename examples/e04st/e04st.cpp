// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"

using namespace std;

// Objective function
auto test_problem = [](auto const &x, auto &y)
{
	std::vector<double> coefs = {24.55, 26.75, 39.00, 40.50};
	for (int i = 0; i < coefs.size(); ++i)
	{
		y += x[i] * coefs[i];
	}
};

// Constraint function
auto constraint_problem = [](auto const &x, auto &y)
{
	y.resize(1);
	y[0] = 12.0 * x[0] + 11.9 * x[1] + 41.8 * x[2] + 52.1 * x[3] -
		   1.645 * sqrt(0.28 * pow(x[0], 2) + 0.19 * pow(x[1], 2) +
						20.5 * pow(x[2], 2) + 0.62 * pow(x[3], 2));
};

int main()
{
	try
	{
		// Problem parameter
		double const INF = 1e19;

		nagcpp::types::f77_integer nvar = 4;
		std::vector<double> x(nvar, 1.0);

		std::vector<double> coefs = {24.55, 26.75, 39.00, 40.50};

		std::vector<double> b_lower(nvar, 0.0);
		std::vector<double> b_upper(nvar, INF);

		std::vector<double> l_lower = {5.0, 1.0};
		std::vector<double> l_upper = {INF, 1.0};
		std::vector<double> a = {2.3, 5.6, 11.1, 1.3,
								 1.0, 1.0, 1.0, 1.0};

		std::vector<double> n_lower = {21.0};
		std::vector<double> n_upper = {INF};

		// Problem definition
		nagcpp::opt::Problem problem(nvar, test_problem);
		problem.set_initial_values(x);
		problem.set_simple_bounds(b_lower, b_upper);
		problem.set_linear_bounds(l_lower, l_upper, a);
		problem.set_nonlinear_bounds(n_lower, n_upper, constraint_problem);

		// Custom monitoring
		nagcpp::opt::MonitorOption monitoring_info;
		monitoring_info.set_print_level(2);

		// Solve
		nagcpp::opt::Solver solver(nvar);
		solver.set_monitoring_info(monitoring_info);

		solver.solve(problem);

		// Monitoring
		std::cout << solver;
	}
	catch (nagcpp::error_handler::Exception &error)
	{
		std::cout << error.msg << std::endl;
	}
}

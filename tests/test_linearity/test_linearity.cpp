// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
#include "gtest/gtest.h"

// non-linear
auto test_problem_1 = [](auto const &x, auto &y)
{
	y = pow(x[0], 2) + pow(x[1], 2);
};

// linear
auto test_problem_2 = [](auto const &x, auto &y)
{
	y = 3 * x[0] + 5 * x[1];
};

// linear
auto test_constraint_problem_1 = [](auto const &x, auto &y)
{
	y.resize(1);
	y[0] = 12.0 * x[0] + 11.9 * x[1];
};

// non-linear
auto test_constraint_problem_2 = [](auto const &x, auto &y)
{
	y.resize(1);
	y[0] = 12.0 * x[0] + 11.9 * x[1] -
		   1.645 * sqrt(0.28 * pow(x[0], 2) + 0.19 * pow(x[1], 2));
};

class ProblemTest : public ::testing::Test
{
protected:
	nagcpp::types::f77_integer nvar;

	void SetUp() override
	{
		nvar = 2;
	}

	template <typename PROBLEM_T>
	auto make_problem(PROBLEM_T &&problem)
	{
		auto ret = nagcpp::opt::Problem(nvar, problem);
		return ret;
	}
};

TEST_F(ProblemTest, NonLinearProblemCheck)
{
	auto problem = make_problem(test_problem_1);
	auto getProbInfo = problem.get_problem_info();
	EXPECT_FALSE(getProbInfo["is_linear"]) << "Problem is linear";
}

TEST_F(ProblemTest, LinearProblemCheck)
{
	auto problem = make_problem(test_problem_2);
	auto getProbInfo = problem.get_problem_info();
	EXPECT_TRUE(getProbInfo["is_linear"]) << "Problem is not linear";
}

TEST_F(ProblemTest, SimpleBoundsCheck)
{
	auto problem = make_problem(test_problem_1);
	std::vector<double> b_lower = {-1.0, -2.0}, b_upper = {0.8, 2.0};
	problem.set_simple_bounds(b_lower, b_upper);
	auto getProbInfo = problem.get_problem_info();
	EXPECT_TRUE(getProbInfo["simple_bounds_declared"]) << "No simple bounds were declared";
}

TEST_F(ProblemTest, LinearBoundsCheck)
{
	auto problem = make_problem(test_problem_1);
	std::vector<double> l_lower = {5.0, 1.0};
	std::vector<double> l_upper = {1e19, 1.0};
	std::vector<double> a = {2.3, 5.6, 11.1, 1.3,
							 1.0, 1.0, 1.0, 1.0};
	problem.set_linear_bounds(l_lower, l_upper, a);
	auto getProbInfo = problem.get_problem_info();
	EXPECT_TRUE(getProbInfo["linear_bounds_declared"]) << "No linear bounds were declared";
}

TEST_F(ProblemTest, DetectLinearBoundsCheck)
{
	auto problem = make_problem(test_problem_1);
	std::vector<double> n_lower = {21.0}, n_upper = {100};
	problem.set_nonlinear_bounds(n_lower, n_upper, test_constraint_problem_1);
	auto getProbInfo = problem.get_problem_info();
	EXPECT_TRUE(getProbInfo["linear_bounds_declared"]) << "No linear bounds were declared";
}

TEST_F(ProblemTest, NonLinearBoundsCheck)
{
	auto problem = make_problem(test_problem_1);
	std::vector<double> n_lower = {21.0}, n_upper = {100};
	problem.set_nonlinear_bounds(n_lower, n_upper, test_constraint_problem_2);
	auto getProbInfo = problem.get_problem_info();
	EXPECT_TRUE(getProbInfo["nonlinear_bounds_declared"]) << "No non-linear bounds were declared";
}
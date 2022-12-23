// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
#include "gtest/gtest.h"

auto test_problem_1 = [](auto const &x, auto &y)
{
	y = pow(x[0], 2) + pow(x[1], 2);
};

auto test_constraint_problem = [](auto const &x, auto &y)
{
	y.resize(1);
	y[0] = 12.0 * x[0] + 11 * x[1] + 41 * x[2] + 52 * x[3] -
		   2 * sqrt(3 * pow(x[0], 2) + 2 * pow(x[1], 2) +
					20 * pow(x[2], 2) + 5 * pow(x[3], 2));
};

auto test_problem_2 = [](auto const &x)
{
	return 3 * pow(x[0], 3) + 3 * pow(x[0], 2) * x[1] - pow(x[1], 3) - 15 * x[0];
};

class ProblemTest : public ::testing::Test
{
protected:
	nagcpp::types::f77_integer nvar;
	std::vector<double> x, n_lower, n_upper;

	void SetUp() override
	{
		nvar = 2;
		x = {-4, 7};
		n_lower = {21.0};
		n_upper = {1e19};
	}

	template <typename PROBLEM_T>
	auto make_problem(PROBLEM_T &&problem)
	{
		auto ret = nagcpp::opt::Problem(nvar, problem);
		ret.set_initial_values(x);
		ret.set_nonlinear_bounds(n_lower, n_upper, test_constraint_problem);
		return ret;
	}
};

TEST_F(ProblemTest, ProblemObjGrdEQ)
{
	auto problem = make_problem(test_problem_1);
	std::vector<double> y1 = {-8, 14};
	std::vector<double> y2;
	long int _inform;
	long int &inform = _inform;
	problem.get_objgrd()(x, y2, inform);
	ASSERT_EQ(y1, y2) << "problem.get_objfun returns wrong values";
}

TEST_F(ProblemTest, ProblemConGrdEQ)
{
	auto problem = make_problem(test_problem_1);
	std::vector<double> y1 = {13.986254132645684, 8.6827035119133704};
	y1.resize(2);
	std::vector<double> y2;
	long int _inform;
	long int &inform = _inform;
	problem.get_congrd()(x, y2, inform);
	ASSERT_EQ(y1.size(), y2.size()) << "Vector y1 and vector y2 are of unequal length";
	for (int i = 0; i < nvar; ++i)
	{
		EXPECT_DOUBLE_EQ(y1[i], y2[i]) << "Vector y1 and vector y2 differ at index " << i << ", problem.get_confun returns wrong values";
	}
}

TEST_F(ProblemTest, HessianEQ)
{
	std::vector<std::vector<double>> y1 = {{-30, -24}, {-24, -42}};
	auto y2 = nagcpp::opt::derivative::hessian(x, test_problem_2);
	ASSERT_EQ(y1.size(), y2.size()) << "Vector y1 and vector y2 are of unequal length";
	for (int i = 0; i < nvar; ++i)
	{
		EXPECT_EQ(y1[i], y2[i]) << "Vector y1 and vector y2 differ at index " << i;
	}
}
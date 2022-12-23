// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"

int main()
{
  auto problem =
      [](auto const &x)
  {
    return sin(x[0]) * exp(cos(x[1] * x[0]));
  };

  std::vector<double> x(2, 1.0);
  auto grad = nagcpp::opt::derivative::gradient(x, problem);

  // to print out the result
  for (const auto &gradi : grad)
  {
    std::cout << gradi << " ";
  }
  std::cout << std::endl;
}

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
    return sin(x[1]) + 4 * x[0];
  };

  std::vector<double> x(2, 1.0);

  if (nagcpp::opt::derivative::lincheck(x, problem) == true)
    std::cout << "Linear" << std::endl;
  else
    std::cout << "Nonlinear" << std::endl;
}

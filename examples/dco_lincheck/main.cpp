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

  return 0;
}

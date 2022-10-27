#include "nag_cpp.hpp"
int main()
{

  auto problem =
      [](auto const &x)
  {
    return 3 * pow(x[0], 3) + 3 * pow(x[0], 2) * x[1] - pow(x[1], 3) - 15 * x[0];
  };

  std::vector<double> x(2, 1.0);
  auto hess = nagcpp::opt::derivative::hessian(x, problem);

  // to print out the result
  for (int i = 0; i < x.size(); i++)
  {
    for (int j = 0; j < x.size(); j++)
    {
      std::cout << hess[i][j] << "  ";
    }
    std::cout << std::endl;
  }
      return 0;
}

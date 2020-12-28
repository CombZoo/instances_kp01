// solver_kp01.hpp

#ifndef SOLCHECK_KP01_HPP
#define SOLCHECK_KP01_HPP

#include <iostream>
#include <vector>

#include <OptFrame/Scanner++/Scanner.hpp>

using namespace scannerpp; // TODO: remove?

// solution checker
namespace solcheck_kp01_ns
{
    struct ResultCheck
    {
        int code;            // result code
        std::string message; // result message (informative)
        std::string debug;   // debug messages
        int value;           // computed solution value
    };

    // TODO: make optional 'sol_value'?
    ResultCheck check_solution_kp01(std::string problem_file, const std::vector<bool> &sol, const std::optional<int> &sol_value)
    {
        Scanner scanner(File{problem_file});
        int n = *scanner.nextInt();
        if (((int)sol.size()) != n)
            return ResultCheck{.code = 1, .message = "wrong solution size!", .value = 0};
        int Q = *scanner.nextInt();
        //std::cout << "Q = " << Q << std::endl;
        std::vector<int> p(n, 0);
        std::vector<int> w(n, 0);
        for (int i = 0; i < n; i++)
            p[i] = *scanner.nextInt();
        for (int i = 0; i < n; i++)
            w[i] = *scanner.nextInt();

        int sum_p = 0; // sum profits
        int sum_w = 0; // sum weights
        for (unsigned i = 0; i < sol.size(); i++)
            if (sol[i])
            {
                sum_p += p[i];
                sum_w += w[i];
            }

        // code 2 - constraint failure (no objective)
        if (sum_w > Q)
            return ResultCheck{.code = 2, .message = "exceeded knapsack capacity!", .value = 0};

        // code 3 - bad value (wrong value presented)
        if (sol_value) // will check solution value
            if (sum_p != *sol_value)
                return ResultCheck{.code = 3, .message = "mismatch solution value!", .value = sum_p};

        return ResultCheck{.code = 0, .message = "", .value = sum_p};
    }

} // namespace solcheck_kp01_ns

#endif // SOLVER_KP01_HPP
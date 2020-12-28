#include <solcheck_kp01/solcheck_kp01.h>

// this is C++ file

#include <iostream>

#include <nlohmann/json.hpp>

#include <solcheck_kp01/solcheck_kp01.hpp> // implementation

// import everything on main()
using namespace std;
using namespace solcheck_kp01_ns;

int
solcheck_kp01(int format, const char* solconfig, char* output)
{
   string sconfig(solconfig);
   nlohmann::json j = nlohmann::json::parse(sconfig);

   std::cout << "will run solcheck kp01" << std::endl;

   string problem_file = j["problem_file"];

   std::string solution_format = j["solution_format"];
   // require that solution comes in json format (TODO: allow optional field)
   assert(solution_format == "json");


   int sol_value = j["solution_value"];
   //std::cout << "JSON: '" << j << "'" << std::endl;
   nlohmann::json jsol = j["solution_data"];
   assert(jsol.is_array());
   //std::cout << "solution: '" << jsol << "'" << std::endl;

   std::vector<bool> vsol;
   for(int i : jsol) {
      //std::cout << "i=" << i << std::endl;
      vsol.push_back(i);
   }

   ResultCheck r = check_solution_kp01(problem_file, vsol, std::make_optional(sol_value));

   nlohmann::json joutput;
   joutput["result_code"] = r.code;
   joutput["check_value"] = r.value;
   joutput["message"] = r.message;
   strcpy(output, joutput.dump().c_str());
   //output = "";

   return 0; // OK
}

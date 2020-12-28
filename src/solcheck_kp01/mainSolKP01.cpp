// mainKP-fcore-ex.cpp
#include <fstream>
#include <iomanip> // setw
#include <iostream>
#include <nlohmann/json.hpp>

#include <solcheck_kp01/solcheck_kp01.h> // general solver

// import everything on main()
using namespace std;

class SolcheckKP01
{
public:
   int runArgs(int argc, char** argv)
   {
      std::cout << "loading parameters" << std::endl;
      string local = argv[0];
      vector<string> params(argc);
      for (int i = 1; i < argc; i++) {
         params[i] = argv[i];
         if (params[i] == "--help") {
            std::cout << "help: solcheck_kp01 --solution search_output.json" << std::endl;
            return 0;
         }
      }

      string sol_file;
      for (unsigned i = 0; i < params.size(); i++) {
         if (params[i] == "--solution")
            sol_file = params[i + 1];
      }

      if (sol_file == "") {
         std::cout << "No run configuration. Try '--solution' or --help'. Aborting!" << std::endl;
         return 1;
      } else {
         std::cout << "loading file '" << sol_file << "'" << std::endl;
         std::ifstream ijson(sol_file);
         if (!ijson.is_open()) {
            std::cout << "file not found!" << std::endl;
            return 1;
         }
         nlohmann::json j;
         ijson >> j;

         std::stringstream ss;
         ss << std::setw(4) << j << std::endl;
         string config = ss.str();

         string sout = solcheck(1, config);
         // TODO: parse solve output
         std::cout << "solcheck = '" << sout << "'" << std::endl;
         return 0;
      }

      return 0;
   }

   // format = 1 (json), = 0 (default)
   string solcheck(int format, string solconfig)
   {
      string output(1000, '\0');

      solcheck_kp01(format, solconfig.c_str(), (char*)output.c_str());
      return output;
   }
};

int
main(int argc, char** argv)
{
   SolcheckKP01 solcheckKP;
   return solcheckKP.runArgs(argc, argv);
}
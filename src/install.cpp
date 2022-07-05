#include <cstdlib> // system()
#include <string> // std::string
#include <fstream> // in
#include <iostream> // cout

#include <array> // exec()
#include <cstdio> // exec()
#include <memory> // exec()

using namespace std;

std::string pulladdress;

void LoadConfig()
{
  std::ifstream in("./path.config");
  std::string param;
  std::string value;

  while (!in.eof()) // not End Of File
  {
    in >> param;
    in >> value;

    if (param == "IMAGE_NAME")
    {
      pulladdress = value;
    }
  }
}

std::string exec(const char* cmd)
{ // stolen from stackoverflow, gets output of MS Batch command
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void dockerPull()
{
  cout << "Pulling from image " << pulladdress << "... \n";

  const std::string pullcmd = "docker pull " + pulladdress;

  if (exec(pullcmd.c_str()).find("up to date") != std::string::npos)
  {
    cout << "Image already up to date.\n";
  }
  else
  {
    cout << "Done pulling image.\n";
  }
}

int main() 
{
  LoadConfig();
  dockerPull();
  system("pause");
  return 0;
}
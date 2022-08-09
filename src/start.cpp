#include <cstdlib> // system 
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <chrono>
#include <fstream>

using namespace std;

// Values defined in config file
std::string imagename; // Name of the Docker image
std::string enginepath; // Directory to the Docker Desktop .exe
std::string port; // Port to map the container to
int timeAfterStart; // Time to wait between detection of Docker process and start of the image

const std::string containername = "EduEarth"; // Name of the container

void LoadConfig() // NOTE: in config file, enginepath must be surrounded by quotes.
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
      imagename = value;
    }
    else if (param == "ENGINEPATH")
    {
      enginepath = value;
    }
    else if (param == "WAIT_TIME")
    {
      timeAfterStart = stoi(value);
    }
    else if (param == "PORT")
    {
      port = value;
    }
  }
}

void start()
{
  cout << "Start block is running\n";

  std::string enginecmd = "start \"\" " 
  + enginepath;

  cout << "enginecmd is: " << enginecmd << "\n";

  const char* enginepathcc = enginecmd.c_str();
  system(enginepathcc);

  cout << "Starting docker engine\n";
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

int hasDockerStarted() // Check if docker is running
{
  std::string result = exec("tasklist /FI \"IMAGENAME eq docker.exe\" /FO csv");
  std::string dockerPresence = "docker.exe";
  if (result.find(dockerPresence) != std::string::npos) // if on the TASKLIST there is a process called "docker.exe"...
  {
    cout << "Docker is running!\n";
    return 1;
  }
  else
  {
    cout << "Docker isn't running! Please wait.\n";
    _sleep(1000); 
    return 0;
  }
}

void startImage() // Start the image inside docker
{
  cout << "startImage block is running.\n";
  std::string dockerCmd = "docker run -dp " 
  + port 
  + ":80 " 
  + "--name "
  + containername
  + " "
  + imagename; 
  // Replace 80 by internal container port if it is different.

  cout << "Running Command: " << dockerCmd << "\n";
  const char* dockerCmdCC = dockerCmd.c_str(); // str to char*
  system(dockerCmdCC); // Windows run
}

void startBrowser() // Start a browser with the container
{
  cout << "startBrowser block is running.\n";
  std::string browserCmdS = "start \"EduEarth\" http://localhost:" + port;
  const char* browserCmd = browserCmdS.c_str();
  system(browserCmd);
}

int main()
{
  cout << "Main block is running.\n";
  LoadConfig();
  start();
  int i = hasDockerStarted();
  while (i != 1)
  {
    i = hasDockerStarted();
  }
  int timeAfterStartMS = timeAfterStart * 1000; // convert s to ms
  cout << "Waiting for " << timeAfterStart << " seconds.\n";
  _sleep(timeAfterStartMS);
  cout << "Done waiting.\n";
  startImage();
  startBrowser();
  cout << "Done starting the program.\n";
  return 0;
}

#include <cstdlib> // system
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <chrono>

using namespace std;

std::string enginepath = "start \"DockerDesktop\" \"C:\\Program Files\\Docker\\Docker\\Docker Desktop.exe\"";
const char* enginepathcc = enginepath.c_str();

std::string imagename = "docker/getting-started";

int timeAfterStart = 30; // In seconds
// Read all csv values and assign them to variables HERE

void start()
{
  printf("Start block is running\n");
  system(enginepathcc);
  printf("Starting docker engine\n");
}

std::string exec(const char* cmd) { // stolen from stackoverflow, gets output of MS Batch command
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


int hasDockerStarted()
{
  std::string result = exec("tasklist /FI \"IMAGENAME eq docker.exe\" /FO csv");
  std::string dockerPresence = "docker.exe";
  if (result.find(dockerPresence) != std::string::npos)
  {
    printf("Docker is running!\n");
    return 1;
  }
  else
  {
    printf("Docker isn't running! Please wait.\n");
    return 0;
  }
}

void startImage() // Start the image inside docker
{
  printf("startImage block is running.\n"); /*
  const char* imagenamecc = imagename.c_str();
  std::string dockercmd = "docker run -dp 80:80";
  const char* dockercmdcc = dockercmd.c_str();
  const char* cmdimagenamecc = dockercmdcc + imagenamecc;*/

  std::string dockerCmd = "docker run -dp 80:80 " + imagename;
  const char* dockerCmdCC = dockerCmd.c_str();
  system(dockerCmdCC);
}

void startBrowser() // Start a browser with the container
{
  printf("startBrowser block is running.");
  const char* browserCmd = "start \"EduEarth\" http://localhost:80";
  system(browserCmd);
}

int main()
{
  printf("Main block is running.\n");
  start();
  int i = hasDockerStarted();
  while (i != 1)
  {
    i = hasDockerStarted();
  }
  int timeAfterStartS = timeAfterStart * 1000; // convert s to ms
  printf("Waiting for 30 000 ms\n");
  _sleep(timeAfterStartS);
  printf("Done waiting...\n");
  startImage();
  startBrowser();
  return 0;
}

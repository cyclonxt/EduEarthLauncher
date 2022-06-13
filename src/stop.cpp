#include <cstdlib> // system()
#include <string> // std::string
#include <iostream> // std::cout

using namespace std;


std::string containername = "EduEarth";

void stopContainer()
{
    const string stopCommand = "docker stop "
    + containername;
    system(stopCommand.c_str());
}

void stopDocker()
{
    const string stopCommand = "taskkill /F /IM \"Docker Desktop.exe\"";
    system(stopCommand.c_str());
}

int main() /* Stop image, once that is done, stop docker.*/
{
    stopContainer();
    cout << "Stopped the container\n";

    stopDocker();
    cout << "Stopped the engine\n";

    system("pause");
    return 0;
} 
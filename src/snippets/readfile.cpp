#include <fstream>
std::string enginepath;
std::string imagename;

bool LoadConfig()
{
  std::ifstream in("./path.config");
  std::string param;
  std::string value;

  while (!in.eof())
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

  }
  const char* imagenamecc = imagename.c_str();
  printf(imagenamecc);
  return true;
}

int main()
{
  LoadConfig();
  return 0;
}

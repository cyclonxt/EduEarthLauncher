
# Guide : Install EduEarth on Windows

## Install Docker

1. Download Docker Desktop:
    1. Go to the official Docker Desktop website at https://www.docker.com/get-started/.
    1. Click `Download for Windows` and save it in your directory of choice.
1. Install Docker Desktop:
    1. Run `Docker Desktop Installer.exe`.
    1. The Installer will Download, then Unpack all necessary files.
    1. Afterwards, you should see an `Installation Succeeded` screen.
    1. Close the window.
1. Setup Docker Desktop:
    1. Open Docker Desktop, from the Desktop Shortcut or from the Start Menu.
    1. Read and Accept the Service Agreement.

## Run program

1. Manually editing config file


    Config file is located at `/src/path.config`.
    This section is aimed only at administrators.
    
    Syntax: 
    1. Values may be in any order.    
    1. `ENGINEPATH` must be surrounded by quotes, AND NOT CONTAIN ANY SPACES. You can get the no-space name in a specific directory using `dir /x` in the Docker Desktop folder. It should always point to the `Docker Desktop.exe` in the Docker Desktop folder.
    1. `IMAGE_NAME` must be surrounded by quotes and not contain any spaces. It can be found by hovering over the image name in the Docker Desktop app and never changes. 
    1. `PATH` is the external port in which the container will run. It is a 4-digit integer. It must not be set to a port already used by another program.
    1. `WAIT_TIME` is the integer number of seconds between the detection of the `docker.exe` process and the start of the image. It depends on computer performance and must be adjusted. 
    
    Example of a valid config file: 
    ```
    IMAGE_NAME "docker/getting-started"    
    ENGINEPATH "%PROGRAMFILES%\Docker\Docker\DOCKER~2.exe"    
    WAIT_TIME 5
    PORT 8888
    ```
    Note: this config file points at the default image, `docker/getting-started`, which is a tutorial on Docker Desktop.
    

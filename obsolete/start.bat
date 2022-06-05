:: What is my plan?
:: First start DockerDesktop (DD) and fetch its PID
:: Once its status is "Running", kill DD with PID
:: Run the docker Image previously downloaded from Docker Hub with port 8888:8888 in background
:: Open Browser with localhost:8888
start "DockerDesktop" "C:\Program Files\Docker\Docker\Docker Desktop.exe"
taskkill /IM "Docker Desktop.exe"
timeout /t 30 /nobreak
:: C'est pas bon ca
taskkill /IM "Docker Desktop.exe"
docker run -dp 8888:80 docker/getting-started
:: CHANGE IMAGE DIRECTORY (Image for jupyterlab: gitlab-registry.in2p3.fr/thomas.dubos/jupyterlab/base)
start "EduEarth" http://localhost:8888
pause

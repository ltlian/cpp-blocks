# CPP-Blocks

A sandbox project I'm using to play around with C++ and SDL using devcontainers.

## Requirements for running on Windows

### Docker Desktop or WSL

Configuration will vary between Docker, WSL, and WSL2. This project is built using a remote container generated by VS Code which runs in Windows 10 with the WSL2 backend.

### VcXsrv Windows X Server

https://sourceforge.net/projects/vcxsrv/

The server must be running in windows for SDL to find a display. It might be necessary to disable access control for the X process and to exclude it in firewall rules.

The environment variable `DISPLAY` must be set correctly and will vary between systems. See `.devcontainer/devcontainer.json`.

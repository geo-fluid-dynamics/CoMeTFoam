# CoMeTFoam
Convection-diffusion phase change solver for OpenFOAM 5.0.

[![Build Status](https://travis-ci.org/geo-fluid-dynamics/CoMeTFoam.svg?branch=feature%2FtravisCI)](https://travis-ci.org/geo-fluid-dynamics/CoMeTFoam)
![OpenFOAM 5.x](https://img.shields.io/badge/OpenFOAM-5.x-brightgreen.svg)

## Getting Started

### OpenFOAM
CoMeTFoam is a custom solver for OpenFOAM. Therefore it must be installed first. Depending on the operating system, different options are available, which are very good described on the official [download page](https://openfoam.org/version/5-0/). As an example, we will summarize the steps, which are necessary to use the OpenFOAM 5 docker image on MacOS in the following:

1) Install [Docker for MacOS](https://docs.docker.com/docker-for-mac/)
2) Download two scripts and make them executable
```
sudo curl --create-dirs -o /usr/local/bin/openfoam5-macos http://dl.openfoam.org/docker/openfoam5-macos
sudo chmod 755 /usr/local/bin/openfoam5-macos
sudo curl -o /usr/local/bin/openfoam-macos-file-system http://dl.openfoam.org/docker/openfoam-macos-file-system
sudo chmod 755 /usr/local/bin/openfoam-macos-file-system
```
3) Create a 10GB file system
```
openfoam-macos-file-system create
```
4) Mount the file system
```
openfoam-macos-file-system mount
```
5) Launching OpenFOAM
```
cd $HOME/openfoam
openfoam5-macos
```

### CoMeTFoam

# ELECasio

A simple circuit solver for casio 35-E.

This project was built using [fxSDK](https://aur.archlinux.org/packages/fxsdk/)

# Preparation
Arch :
```bash
# Requirements to compile the code
git clone https://gitea.planet-casio.com/Lephenixnoir/GiteaPC.git
cd GiteaPC
./install.sh
giteapc install Lephenixnoir/gint

# Requirements to send the bin to the calculator
yay -S p7 p7screen 
```
# Building

Install fxsdk and run the following command at repository's root
```
fxsdk build-fx
```

# Sending the add-in to the calculator

Make sure the calculator is on and in recv mode
```
p7 send Elecasio.g1a
```

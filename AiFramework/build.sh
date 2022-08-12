#!/bin/sh
banner() {
    printf "\n"
    printf "AiFramework builder\n"
    printf "by r0neko - first version of this crazy script!\n\n"
    printf "*********** YOU ARE SUPPOSED TO RUN THIS ONLY ONCE! ***********\n"
    printf "     This script will only install the requires stuff for\n"
    printf "    compilation. Future compilations of this won't require\n"
    printf "                     running this again.\n"
    printf "****************** PLEASE KEEP THIS IN MIND! ******************\n"
    printf "\n"
}

package_check() {
    printf "[i] Do we have $1? "
    PKG_QUERY=$(dpkg-query -W --showformat='${Status}\n' $1 2>/dev/null | grep "ok installed")

    if [ "" = "$PKG_QUERY" ]; then
        printf "Nope!\nTime to install $1...\n"
        sudo apt-get -y install $1
    else
        printf "Yes sir, we do!"
    fi
    printf "\n"
}

banner

printf "[*] Step 1: Package check\n"
package_check build-essential
package_check cmake
package_check pkg-config
package_check mesa-utils
package_check libglu1-mesa-dev
package_check freeglut3-dev
package_check mesa-common-dev
package_check libglew-dev
package_check libglm-dev
package_check libao-dev

printf "[*] Step 2: GLAD setup\n"
printf "[i] Creating working directories...\n"
mkdir -p vendor
mkdir -p vendor/glad
printf "[i] Cloning the latest glad version...\n"
git clone https://github.com/Dav1dde/glad vendor/glad_builder
printf "[i] Building glad...\n"
cd vendor/glad_builder
cmake .
make -j16
printf "[i] Copying glad in the right place...\n"
rm -rf ../glad/*
cp include src ../glad -r
cd ..
printf "[i] Performing glad clean-up...\n"
rm -rf glad_builder
cd ..

printf "[*] Step 3: AiFramework building\n"
printf "From this point, you can compile AiFramework by yourself too!\n"
make clean
make -j16

printf "Congrats, fellow gamer! AiFramework was built successfully! Enjoy!\n"
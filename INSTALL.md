System : Ubuntu 16.04
Compiler : clang 3.8.0
Cmake: 3.5.1

# requirements


## lua 5.1
    sudo apt-get install liblua5.1-0-dev

## SFML  (see https://www.sfml-dev.org/tutorials/2.4/compile-with-cmake.php)

    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev libxrandr-dev libfreetype6-dev libglew-dev libjpeg-dev libsndfile1-dev libopenal-dev -y
    git clone https://github.com/SFML/SFML.git
    cd SFML
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ..

## CEGUI (https://bitbucket.org/cegui/cegui)
    
    sudo apt-get install libfreetype6-dev -y
    wget https://bitbucket.org/cegui/cegui/downloads/cegui-0.8.7.tar.bz2
    tar -xf cegui-0.8.7.tar.bz2
    cd cegui-0.8.7
    mkdir build
    cd build
    cmake-gui .. 
    # fix any issues pointed out by cmake
    # not all dependencies are required so if some are not found, don't panic and carry on!
    sudo make install
    cd ..

## luabind (https://github.com/Krozark/luabind-deboostified)

    git clone https://github.com/Krozark/luabind-deboostified.git
    cd luabind-deboostified
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ..

## cpp-utils (https://github.com/Krozark/cpp-utils)

    git clone https://github.com/Krozark/cpp-utils.git
    cd cpp-utils
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ..


## cpp-ORM (https://github.com/Krozark/cpp-ORM)

    git clone https://github.com/Krozark/cpp-ORM.git
    cd cpp-ORM
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ..


#project itself
    git clone git@github.com:Krozark/SFML-utils.git --recursive
    cd SFML-utils
    mkdir build
    cd build
    cmake ..
    make
    cd ../examples



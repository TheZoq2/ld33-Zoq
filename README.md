# Posessed

My entry for ludum dare 33.

You are a demon possessing a human host and your goal is to kill as many people as possible. However, the human is strong and can temporarily resist your shapeshifting which makes you weak and vulnerable. You can however sneak past people when they can't see your inner demons.

While a demon, you should try to kill as many people as possible, but don't let guards see you transform back into a human


The game is best played with a controller but it's possible to play with mouse and keyboard. 

#Instructions (Windows)
I will upload a windows build shortly. For now you will probably be able to build the game from source using CMake. The only dependency required should be SFML 2.3.

#Instructions (Linux)

First, you need to install SFML (I developed the game using SFML 2.3 but other SFML 2.x versions may work)

On ubuntu, execute:
```
sudo apt-get install libsfml-dev
```

On arch:
```
sudo pacman -S sfml
```

####1: Download the sourcecode
````
git clone https://github.com/TheZoq2/ld33-zoq.git
```

####2: Navigate into the new folder and create a build directory
```
cd ld33-possessed
mkdir build
cd build
```

####3: Compile the project
```
make
```

####4: Run 'possessed'
```
./possessed
```

# Credits
Font downloaded from http://dsg4.com/04/extra/bitmap/

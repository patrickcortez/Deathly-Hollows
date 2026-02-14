# Check if gcc is available if not then install

which g++ ||{
    if sudo apt install gcc; then
        echo "GCC has been installed!"
    else
        echo "GCC failed to install"
    fi
}

# then we compile the game

if g++ -I/lib src/main.cpp -o bin/Desp; then
    echo "Game Compiled Successfully!"
else
    echo "Game failed to Compile!"
fi

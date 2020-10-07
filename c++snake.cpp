#include<iostream>
#include<conio.h>

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char keys);
void clearScreen();
void generateFood();

char getMapValue(int value);

// Map dimensions
const int mapwidth = 20;
const int mapheight = 20;

const int size = mapwidth * mapheight;

int map[size]; // The tile values for the map

// Snake head details
int headxpos;
int headypos;
int direction;

int food = 4;  // Amount of food the snake has (How long the body is)

bool running;  // Determine if game is running

int main()
{
    run();
    return 0;
}

void run()  // Main game function
{
    // Initialize the map
    initMap();
    running = true;
    while (running)
    {
        if (kbhit())    // If a key is pressed
        {
            changeDirection(getch());  // Change to direction determined by key pressed
        }

        update();    // Update the map

        clearScreen();  // Clear the screen

        printMap();  // Print the map

        _sleep(500);  // wait 0.5 seconds
    }

    std::cout << "\t\t!!!Game over!" << std::endl << "\t\tYour score is: " << food;  // Print out game over text

    std::cin.ignore();  // Stop console from closing instantly
}

void changeDirection(char keys)  // Changes snake direction from input
{
    switch (keys)
    {
    case '8':
        if (direction != 2)
            direction = 0;
        break;
    case '6':
        if (direction != 3)
            direction = 1;
        break;
    case '2':
        if (direction != 4)
            direction = 2;
        break;
    case '4':
        if (direction != 5)
            direction = 3;
        break;
    }
}

void move(int dx, int dy)  // Moves snake head to new location
{
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    if (map[newx + newy * mapwidth] == -2)  // Check if there is food at location
    {
        food++;  // Increase food value (body length)
        generateFood();  // Generate new food on map
    }

    else if (map[newx + newy * mapwidth] != 0)  // Check location is free
    {
        running = false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = food + 1;
}

void clearScreen() // Clears screen
{
    system("cls");  // Clear the screen
}

void generateFood()  // Generates new food on map
{
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;


    } while (map[x + y * mapwidth] != 0);  // If location is not free try again

    map[x + y * mapwidth] = -2;  // Place new food
}

void update()  // Updates the map
{
    switch (direction)  // Move in direction indicated
    {
    case 0:
        move(-1, 0);
        break;
    case 1:
        move(0, 1);
        break;
    case 2:
        move(1, 0);
        break;
    case 3:
        move(0, -1);
        break;
    }

    for (int i = 0; i<size; i++)   // Reduce snake values on map by 1
    {
        if (map[i]>0)
            map[i]--;
    }
}

void initMap()  // Initializes map
{
    // Places the initial head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    for (int x = 0; x<mapwidth; ++x)  // Places top and bottom walls
    {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    for (int y=0; y<mapheight; y++)  // Places left and right walls
    {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    generateFood();  // Generates first food
}

void printMap()  // Prints the map to console
{
    for (int x = 0; x < mapwidth; ++x)
    {
        for (int y = 0; y < mapheight; ++y)
        {
            std::cout << getMapValue(map[x + y * mapwidth]);  // Prints the value at current x,y location
        }
        std::cout << std::endl;   // Ends the line for next x value
    }
}

char getMapValue(int value)  // Returns graphical character for display from map value
{

    if (value > 0)
        return 'O';  // Returns a part of snake body

    switch (value)
    {
        case -1: return '*';  // Return wall
        case -2: return '+';  // Return food
    }
}

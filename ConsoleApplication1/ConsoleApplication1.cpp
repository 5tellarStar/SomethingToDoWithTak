#include <iostream>
#include <string>
#include <bitset>
#include <math.h>

//a tak tile is represented with a uint64_t with the bits WXYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYZZZZZZ where:
//W = 1 if a Capstone is on top
//X = 1 if a Wall is on top
//Y representation which color the pieces are*
//Z is how tall the tower is, if = 0 than the tile is empty

//*allows for 56 pieces even though max height on 5x5 board is 42 wasting 14 bits


static uint64_t Count(uint64_t tile) 
{
    //Mask out the count of pieces in the tower
    return tile & 0x3F;
}

static bool IsWhiteOnTop(uint64_t tile) 
{
    //shifts the top piece's color bit to first position and masks away everything else
    return (tile >> (5 + Count(tile))) & 1;
}

static bool IsCapstoneOnTop(uint64_t tile) 
{
    //shifts the capstone on the top bit to first position and masks away everything else
    return (tile >> 63) & 1;
}

static bool IsWallOnTop(uint64_t tile) 
{
    //shifts the wall on the top bit to first position and masks away everything else
    return 1 == ((tile >> 62) & 1);
}

//Checks which pieces count towards a colors roads, returns a uint32_t which is used kind of like a 5x5 bool array wasting 7 bits
static uint32_t Conductive(uint64_t board[5][5], bool isWhite) 
{
    uint32_t conductive = 0;

    //loops through the board
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            //checks if the tile isn't empty, controlled by the color and doesn't have a wall on the top
            if (Count(board[x][y]) != 0 && (IsWhiteOnTop(board[x][y]) == isWhite) && !IsWallOnTop(board[x][y]))
            {
                // adds a 1 in the place representing [x][y] in the uint32_t
                conductive |= (1 << (x + y * 5));
            }
        }
    }

    return conductive;
}

//Checks if a color has completed a road
static bool finishedRoad(uint32_t board) 
{
    //there's probably a better way
    for (int first = 0; first < 5; first++)
    {
        if ((board >> (0 + first * 5)) & 1)
        {
            for (int second = first; second >= 0; second--)
            {
                if ((board >> (1 + second * 5)) & 1) 
                {
                    for (int third = second; third >= 0; third--)
                    {
                        if ((board >> (2 + third * 5)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1) 
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    for (int third = second; third < 5; third++)
                    {
                        if ((board >> (2 + third * 5)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }

            for (int second = first; second < 5; second++)
            {
                if ((board >> (1 + second * 5)) & 1)
                {
                    for (int third = second; third >= 0; third--)
                    {
                        if ((board >> (2 + third * 5)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    for (int third = second; third < 5; third++)
                    {
                        if ((board >> (2 + third * 5)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 + fourth * 5)) & 1)
                                {
                                    if ((board >> (4 + fourth * 5)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    for (int first = 0; first < 5; first++)
    {
        if ((board >> (0 * 5 + first)) & 1)
        {
            for (int second = first; second >= 0; second--)
            {
                if ((board >> (1 * 5 + second)) & 1) 
                {
                    for (int third = second; third >= 0; third--)
                    {
                        if ((board >> (2 * 5 + third)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1) 
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    for (int third = second; third < 5; third++)
                    {
                        if ((board >> (2 * 5 + third)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }

            for (int second = first; second < 5; second++)
            {
                if ((board >> (1 * 5 + second)) & 1)
                {
                    for (int third = second; third >= 0; third--)
                    {
                        if ((board >> (2 * 5 + third)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    for (int third = second; third < 5; third++)
                    {
                        if ((board >> (2 * 5 + third)) & 1)
                        {
                            for (int fourth = third; fourth >= 0; fourth--)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }

                            for (int fourth = third; fourth < 5; fourth++)
                            {
                                if ((board >> (3 * 5 + fourth)) & 1)
                                {
                                    if ((board >> (4 * 5 + fourth)) & 1)
                                    {
                                        return true;
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    return false;
}

//currently just testing stuff
int main()
{
    uint64_t board[5][5];

    board[0][0] = 0b0000000000000000000000000000000000000000000000000000000001000001;

    uint32_t test = 0b00000000000100011000100001100001;
    std::cout << std::bitset<32>(test) << "\n";
    std::cout << std::bitset<5>(test) << "\n";
    std::cout << std::bitset<5>(test >> 5) << "\n";
    std::cout << std::bitset<5>(test >> 10) << "\n";
    std::cout << std::bitset<5>(test >> 15) << "\n";
    std::cout << std::bitset<5>(test >> 20) << "\n";
    std::cout << finishedRoad(test) << "\n";
}
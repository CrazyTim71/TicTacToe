#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

char board_state[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char player_symbol[2] = {'X', 'O'};
std::string player_names[2] = {"", ""};
int current_player = 0;

void display_board()
{
    std::cout << "___________________" << std::endl;
    std::cout << "|1    |2    |3    |" << std::endl;
    std::cout << "|  " << board_state[0] << "  |  " << board_state[1] << "  |  " << board_state[2] << "  |" << std::endl;
    std::cout << "|_____|_____|_____|" << std::endl;
    std::cout << "|4    |5    |6    |" << std::endl;
    std::cout << "|  " << board_state[3] << "  |  " << board_state[4] << "  |  " << board_state[5] << "  |" << std::endl;
    std::cout << "|_____|_____|_____|" << std::endl;
    std::cout << "|7    |8    |9    |" << std::endl;
    std::cout << "|  " << board_state[6] << "  |  " << board_state[7] << "  |  " << board_state[8] << "  |" << std::endl;
    std::cout << "|_____|_____|_____|" << std::endl;

}

std::string get_player_input_str(const std::string& message)
{
   std::string input;

   std::cout << message;
   std::getline(std::cin, input);
   std::cin.sync();

   return input;
}

int get_player_input_int(const std::string& message, const int min_value, const int max_value)
{
    int input;

    while(true)
    {
        std::cout << message;
        input = std::cin.get();
        std::cin.sync();
        // 49 --> 1
        // 50 --> 2
        // 51 --> 3
        // ...
        // 57 --> 9

        // allow input from 1-9
        if(input >= min_value and input <= max_value)
        {
            break;
        } else
        {
            // system("cls");
            std::cout << "Invalid input. Please try again\n";
        }
    }

    std::cout << std::endl;

    // convert the ascii value to the normal integer value
    return input - 48;
}

int select_player_to_start()
{
    return ((int) (rand() % 2)); // random number between 0 and 1
}

int display_menue()
{
    std::cout << "Please select the game mode by pressing a number: " << std::endl;
    std::cout << "1 -> player vs player" << std::endl;
    std::cout << "2 -> Play against the computer" << std::endl;
    std::cout << "3 -> exit" << std::endl;

    std::cout << std::endl;

    int game_mode;

    // only allow the player to input numbers from 1 to 3
    game_mode = get_player_input_int("Your choice: ", 49, 51);

    return game_mode;
}

int display_end()
{
    std::cout << "1 - Restart the game" << std::endl;
    std::cout << "2 - back to menue" << std::endl;
    std::cout << "3 - exit" << std::endl;

    // only allow the player to input numbers from 1 to 3
    return get_player_input_int("Your choice: ", 49, 51);
}

void reset_game(bool reset_names)
{
    // reset the board
    int size = sizeof(board_state) / sizeof (char);
    for (int i = 0; i < size; i++)
    {
        board_state[i] = ' ';
    }

    // reset player names
    if (reset_names)
    {
        player_names[0] = "";
        player_names[1] = "";
    }

    // reset the current player
    current_player = 0;
}

char check_for_winner()
{
    // 3 same items in one row
    if( board_state[0] == board_state[1] && board_state[1] == board_state[2])
    {
        return board_state[0]; // return the symbol of the winner
    }
    if( board_state[3] == board_state[4] && board_state[4] == board_state[5])
    {
        return board_state[3]; // return the symbol of the winner
    }
    if( board_state[6] == board_state[7] && board_state[7] == board_state[8])
    {
        return board_state[6]; // return the symbol of the winner
    }

    // 3 same items in one column
    if( board_state[0] == board_state[3] && board_state[3] == board_state[6])
    {
        return board_state[0]; // return the symbol of the winner
    }
    if( board_state[1] == board_state[4] && board_state[4] == board_state[7])
    {
        return board_state[1]; // return the symbol of the winner
    }
    if( board_state[2] == board_state[5] && board_state[5] == board_state[8])
    {
        return board_state[2]; // return the symbol of the winner
    }

    // check diagonal
    if( board_state[0] == board_state[4] && board_state[4] == board_state[8])
    {
        return board_state[0]; // return the symbol of the winner
    }
    if( board_state[2] == board_state[4] && board_state[4] == board_state[6])
    {
        return board_state[2]; // return the symbol of the winner
    }

    return ' '; // no winner yet
}

bool isBoardFull()
{
    // count the number of fields that are full
    // and compare it to the size of the field
    // if count == size --> are fields are full
    int count = 0;
    int size = sizeof (board_state) / sizeof (char);

    for (int i = 0; i< size; i++)
    {
        if (board_state[i] != ' ')
        {
            count++;
        }
    }

    if (count == size)
    {
        return true;
    } else
    {
        return false;
    }
}

void player_vs_player()
{
    system("cls");
    if (player_names[0].empty() or player_names[1].empty())
    {
        player_names[0] = get_player_input_str("Player 1 (X): Enter a name: ");
        player_names[1] = get_player_input_str("Player 2 (O): Enter a name: ");
        system("cls");
    }

    display_board();
    current_player = select_player_to_start();

    while (true) {
        // check if a winner symbol is returned
        // if yes, we can select the winner and end the game
        // otherwise continue
        char result = check_for_winner();
        int winner;
        if (result != ' ') {
            if (player_symbol[0] == result) {
                winner = 0;
            } else {
                winner = 1;
            }

            std::cout << std::endl;
            std::cout << "The winner is " << player_names[winner] << std::endl;
            std::cout << std::endl;
            sleep(2);
            break;
        }

        std::cout << std::endl;

        // check if the game board is full
        // if yes, end the game
        bool endGame = isBoardFull();
        if (endGame)
        {
            std::cout << "draw - nobody wins" << std::endl;
            break;
        }

        std::string message = player_names[current_player] + ": Select a field number to place your " +
                              player_symbol[current_player] + ": ";
        int choice = get_player_input_int(message, 49, 57); // allow input from 1 to 9
        std::cout << std::endl;

        if (board_state[choice - 1] == ' ') {
            board_state[choice - 1] = player_symbol[current_player];
            system("cls");
            display_board();

            if (current_player == 0) {
                current_player = 1;
            } else {
                current_player = 0;
            }

        } else {
            std::cout << "Error. Please choose a different field!";
        }
    }

    int decision = display_end();
    if (decision == 1)
    {
        reset_game((false));
        player_vs_player();
    } else if (decision == 2)
    {
        reset_game((true));
        system("cls");
    } else if (decision == 3)
    {
        std::exit(0);
    }
}

int generate_machine_guess()
{
    int guess;
    while(true)
    {
        guess = 1 + (rand() % 9); // number between 1 and 9

        if (board_state[guess - 1] == ' ')
        {
            break;
        }
    }
    return guess;
}

void player_vs_machine()
{
    system("cls");
    player_names[0] = "computer"; // machine
    std::cout << "Player 1: computer" << std::endl;
    if (player_names[1].empty())
    {
        player_names[1] = get_player_input_str("Player 2 (O): Enter a name: ");
    } else
    {
        std::cout << "Player 1: " << player_names[1] << std::endl;
    }


    system("cls");
    display_board();

    current_player = select_player_to_start();

    while (true) {
        // check if a winner symbol is returned
        // if yes, we can select the winner and end the game
        // otherwise continue
        char result = check_for_winner();
        int winner;
        if (result != ' ') {
            if (player_symbol[0] == result) {
                winner = 0;
            } else {
                winner = 1;
            }

            std::cout << std::endl;
            std::cout << "The winner is " << player_names[winner];
            std::cout << std::endl;
            sleep(2);
            break;
        }

        std::cout << std::endl;

        // check if the game board is full
        // if yes, end the game
        bool endGame = isBoardFull();
        if (endGame)
        {
            std::cout << "draw - nobody wins" << std::endl;
            break;
        }

        // only the human player needs to choose a field
        // the computer will randomly select a free field
        int choice;
        if(current_player == 1)
        {
            std::string message = player_names[current_player] + ": Select a field number to place your " +
                                  player_symbol[current_player] + ": ";
            choice = get_player_input_int(message, 49, 57); // allow input from 1 to 9
            std::cout << std::endl;
        } else
        {
            choice = generate_machine_guess();
            std::cout << "The computer selected field " << std::to_string(choice) << std::endl;
            sleep(2);
        }


        if (board_state[choice - 1] == ' ') {
            board_state[choice - 1] = player_symbol[current_player];
            system("cls");
            display_board();

            if (current_player == 0) {
                current_player = 1;
            } else {
                current_player = 0;
            }

        } else {
            std::cout << "Error. Please choose a different field!";
        }
    }

    int decision = display_end();
    if (decision == 1)
    {
        reset_game((false));
        player_vs_machine();
    } else if (decision == 2)
    {
        reset_game((true));
        system("cls");
    } else if (decision == 3)
    {
        std::exit(0);
    }
}

int main()
{
    system("cls");
    std::cout   <<
        "\n"    <<
        "\n"    <<
        "___________.__     ___________           ___________            \n"        <<
        "\\__    ___/|__| ___\\__    ___/____    ___\\__    ___/___   ____  \n"     <<
        "  |    |   |  |/ ___\\|    |  \\__  \\ _/ ___\\|    | /  _ \\_/ __ \\ \n"  <<
        "  |    |   |  \\  \\___|    |   / __ \\\\  \\___|    |(  <_> )  ___/ \n"   <<
        "  |____|   |__|\\___  >____|  (____  /\\___  >____| \\____/ \\___  >\n"    <<
        "                   \\/             \\/     \\/                  \\/ \n"    <<
        "by Tim"    << std::endl;
    std::cout << std::endl;

    srand(std::time(0));  // Initialize random number generator

    while (true)
    {
        int game_mode = display_menue();

        if (game_mode == 1)
        {
            player_vs_player();
        } else if (game_mode == 2)
        {
            player_vs_machine();
        } else if (game_mode == 3)
        {
            std::exit(0);
        } else
        {
            std::cout << "Something went wrong" << std::endl;
            std::exit(1);
        }
    }

    // todo: fix binary size
    // todo: better machine algorithm

    return 0;
}
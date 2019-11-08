/*
 Name: Andrew Ma

Program purpose: The program runs a soccer simulation ad outputs the statistics for the game
 
 Program Testing: I used the following simulations to test and debug the code. When looking at the stats for these, I realized that yellow cards and red cards were not
 increasig the number of fouls. Goals were also not increasing the amount of shots on target so I adjusted my code accordingly. Furthermore, there were
 times when I ran the code when it would only print out the first half statistics and ten end the game. I realized this was because I was using and if - else-if
 statement to determine whether to print the first half stats and final stats. For most cases, this worked fine. However, if the number first half events was the same as the
 total number of events, the statement would skip over printing the final game statistics, so I changed my code into two different if statements. The first two simulations were
 without the mentioned code adjustments, while the third simulation has the code adjustments

*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

bool run_soccer_simulation();
// PURPOSE: Runs the specified soccer simulation
//     INPUTS: none
//     RETURNS: returns true if the simulation was successful;
//              else, returns false

void shot_on_target(string team_name, int& goals, int& on_goal, int& off_goal, int& blocked);
// PURPOSE: Handles the shot on target and free kick event
//     INPUTS: team_name - string that indicates current team name
//             goals - number of goals scored for the current team
//             on_goal - number of shots on goal for the current team
//             off_goal - number of shots off goal for the current team
//             blocked - number of shots blocked for the current team
//     RETURNS: nothing to return

// ... other function declarations omitted
// TODO: also provide functions for free kick, penalty, and card on foul

void penalty_kicks(string team_name, int& goals, int& on_goal, int& off_goal);
/*  PURPOSE: Handles penalty kick event
       INPUTS: team_name - string that indicates current team name
           goals - number of goals scored for the current team
           on_goal - number of shots on goal for the current team
           off_goal - number of shots off goal for the current team
       RETURNS: nothing to return
*/

void foul_committed(string team_name, int& fouls, int& yellow_cards, int& red_cards);
/*  PURPOSE: Handles all foul call events
        INPUTS: team_ name - string that indicates current team name
                fouls - number of fouls committed by current team
                yellow_cards - number of yellow cards committed by current team
                red_cards - number of red cards for current team
        RETURNS: nothing to return
 */


int main() {
    if(run_soccer_simulation()){
        cout << "The simulation has ran successfully! \n";
    }
       
        
    return 0;
}

bool run_soccer_simulation() {
    // [setup] step1. initialize corresponding variables
    const string team_a = "Team A", team_b = "Team B";
    int a_goals = 0;
    int b_goals = 0;
    int a_on_goal = 0;
    int b_on_goal = 0;
    int a_off_goal = 0;
    int b_off_goal = 0;
    int a_fouls = 0;
    int b_fouls = 0;
    int a_yellow_cards = 0;
    int b_yellow_cards = 0;
    int a_red_cards = 0;
    int b_red_cards = 0;
    int a_blocked = 0;
    int b_blocked = 0;
    int no_of_events = 0;
    int cur_event= 0;
    int first_half_length = 0;


    // [INPUT] step2. generate number of events in game and per half
    srand(time(0));
    no_of_events = rand() % 30 + 1;
    first_half_length = rand() % no_of_events;


    // [PROCESSING] step4. process events
    for (int event = 1; event <= no_of_events; ++event) {
        // step4.1. generate next event
        cur_event = rand() % 6 + 1;
        
        
        // step4.2. process the current event
        switch(cur_event) {
            // step4.2.1. handle shot on target for Team A
            case 1:
                // call a function to handle shot on target
                shot_on_target(team_a, a_goals, a_on_goal, a_off_goal, a_blocked);
                break;

            // step4.2.2. handle shot on target for Team B
            case 2:
                // call a function to handle shot on target
                shot_on_target(team_b, b_goals, b_on_goal, b_off_goal, b_blocked);
                break;
                
            // step4.2.3. handle far fouls committed by Team B
            case 3:
                //call a function to handle foul for team B and free kick for team A
                foul_committed(team_b, b_fouls, b_yellow_cards, b_red_cards);
                shot_on_target(team_a, a_goals, a_on_goal, a_off_goal, a_blocked);
                break;
            
            // step4.2.4. handle far fouls committed by Team A
            case 4:
                //call a function to handle foul for team A and free kick for team B
                foul_committed(team_a, a_fouls, a_yellow_cards, a_red_cards);
                shot_on_target(team_b, b_goals, b_on_goal, b_off_goal, b_blocked);
                break;
                
            // step 4.2.5. handle penalties committed by Team B
            case 5:
                //call a function to handle foul for team B and penalty for team A
                foul_committed(team_b, b_fouls, b_yellow_cards, b_red_cards);
                penalty_kicks(team_a,  a_goals, a_on_goal, a_off_goal);
                break;
            
            //step 4.2.6. handle penalties committed by Team A
            case 6:
                //call a function to handle foul for team A and penalty for team B
                foul_committed(team_a, a_fouls, a_yellow_cards, a_red_cards);
                penalty_kicks(team_b,  b_goals, b_on_goal, b_off_goal);
                break;
        }
        
        //step4.3. process half time length
        if(event == first_half_length){
            //prints out first half events
            cout << "First half Statistics: \n"
                 << setw(40) << team_a << setw(20) << team_b << endl
                 << setw(20) << "Score:" << setw(20) << a_goals << setw(20) << b_goals << endl
                 << setw(20) << "Shots on Goal:" << setw(20) << a_on_goal << setw(20) << b_on_goal << endl
                 << setw(20) << "Shots off Goal:" << setw(20) << a_off_goal << setw(20) << b_off_goal << endl
                 << setw(20) << "Blocked Shots:" << setw(20) << a_blocked << setw(20) << b_blocked << endl
                 << setw(20) << "Fouls:" << setw(20) << a_fouls << setw(20) << b_fouls << endl
                 << setw(20) << "Yellow Cards" << setw(20) << a_yellow_cards << setw(20) << b_yellow_cards << endl
                 << setw(20) << "Red Cards:" << setw(20) << a_red_cards << setw(20) << b_red_cards << endl << endl;
                
        }
        if(event == no_of_events){
            //prints out final game statistics
            cout << "Final Game Statistics: \n"
            << setw(40) << team_a << setw(20) << team_b << endl
            << setw(20) << "Score:" << setw(20) << a_goals << setw(20) << b_goals << endl
            << setw(20) << "Shots on Goal:" << setw(20) << a_on_goal << setw(20) << b_on_goal << endl
            << setw(20) << "Shots off Goal:" << setw(20) << a_off_goal << setw(20) << b_off_goal << endl
            << setw(20) << "Blocked Shots:" << setw(20) << a_blocked << setw(20) << b_blocked << endl
            << setw(20) << "Fouls:" << setw(20) << a_fouls << setw(20) << b_fouls << endl
            << setw(20) << "Yellow Cards" << setw(20) << a_yellow_cards << setw(20) << b_yellow_cards << endl
            << setw(20) << "Red Cards:" << setw(20) << a_red_cards << setw(20) << b_red_cards << endl << endl;

        }
    }
    
    //prints out final result of the game
    if(a_goals > b_goals){
        cout << "Team A has won and taken the 3 points! \n";
    } else if (b_goals > a_goals){
        cout << "Team B has won and taken the 3 points! \n";
    } else {
        cout << "The game ends with a draw and both teams go home with a point. \n";
    }
    
    // [OUTPUT] step5. return true if the simulation was successful
    return true;
}

void shot_on_target(string team_name, int& goals, int& on_goal, int& off_goal, int& blocked) {
    // [setup] step1. initialize corresponding values
    int shot_outcome;
    
    // [INPUT] step2. generate event outcome
    shot_outcome = rand() % 4;
    
    // [PROCESSING] step3. process current event
    switch(shot_outcome) {
        case 0:
            cout << "\t" << team_name << " has scored a goal! Fantastic shot!\n\n";
            ++goals;
            on_goal++;
            break;
        case 1:
            cout << "\t" << team_name << " has shot on goal. Great save by the opposing team.\n\n";
            ++on_goal;
            break;
        case 2:
            cout << "\t" << team_name << " has shot off goal. Excellent attempt.\n\n";
            ++off_goal;
            break;
        case 3:
            cout << "\t" << team_name << "'s shot was blocked. Excellent attempt.\n\n";
            ++blocked;
            break;
    }
    
    // [OUTPUT] step4. handle outputs
    // nothing to do
}

void foul_committed(string team_name, int& fouls, int& yellow_cards, int& red_cards){
    //[SETUP] step1. initialize variables
    int foul_outcome;
    
    //[INPUT] step2. generates random event
    foul_outcome = rand() % 3;
    
    //[PROCESSING] step3. processes foul outcome
    switch(foul_outcome){
        case 0:
            cout << "\t" << team_name << " has committed a foul. No card. \n\n";
            fouls++;
            break;
        case 1:
            cout << "\t" << team_name << " has committed a foul and gotten a yellow card. \n\n";
            yellow_cards++;
            fouls++;
            break;
        case 2:
            cout << "\t" << team_name << " has committed a foul and they've been sent off! The manager will be furious! \n\n";
            red_cards++;
            fouls++;
            break;
    }
}


void penalty_kicks(string team_name, int& goals, int& on_goal, int& off_goal){
   //setup step1: initialize variables
    int penalty_outcome;
    
    // [INPUT] step2. generate random event
    penalty_outcome = rand() % 3;
    
    // [PROCESSING] step3. process penalty outcome
    switch(penalty_outcome){
        case 0:
            cout << "\t" << team_name << " has scored the penalty! Well taken! \n\n";
            goals++;
            on_goal++;
            break;
        case 1:
            cout << "\t" << team_name << " has had their penalty saved! What a stop! \n\n";
            on_goal++;
            break;
        case 2:
            cout << "\t" << team_name << " has missed their penalty. Oh dear! \n\n";
            off_goal++;
            break;
    }
    
}


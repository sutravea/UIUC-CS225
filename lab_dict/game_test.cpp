/**
 * @file game_test.cpp
 * Very basic tests for the Game class. 
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

#include "game.h"

using namespace std;
using namespace game_ret;

static map< int, string > msgs =
{
    {SUCCESS, "SUCCESS"},
    {FAIL, "FAIL"},
    {USER_EXISTS, "USER_EXISTS"},
    {INVALID_USERNAME, "INVALID_USERNAME"},
    {INVALID_PARTY, "INVALID_PARTY"},
    {INVALID_MATCH, "INVALID_MATCH"},
    {USER_IN_MATCH, "USER_IN_MATCH"},
    {NULL_MATCH_ID, "NULL_MATCH_ID"}
};

const string SEP =
"-------------------------------------------";

int main()
{
    cout << boolalpha;
    Game::UserStats t, s;

    Game g;
    vector< string > team1 = { "stalin", "polpot", "hochiminh", "ChairmanMeow" };
    vector< string > team2 = { "mccarthy", "reagan", "BushAdmin", "CKS" };
    for(string& un : team1)
    {
        cout << left << setw(15) << "Adding user " 
        << setw(15) << un << msgs[g.add_user(un)] << endl;        
        cout << left << "Loging in user " 
        << setw(15) << un << msgs[g.login_user(un)] << endl;
    }
    cout << SEP << endl;
    for(string& un : team2)
    {
        cout << left << setw(15) << "Adding user " 
        << setw(15) << un << msgs[g.add_user(un)] << endl;        
        cout << left << "Loging in user " 
        << setw(15) << un << msgs[g.login_user(un)] << endl;
    }
    string party1 = g.make_party(team1);
    string party2 = g.make_party(team2);

    cout << SEP << endl;
    cout << "party1 id: " << party1 << endl;
    cout << "party2 id: " << party2 << endl;

    unsigned long match_id = g.make_match(party1);
    unsigned long found_match = g.find_match(party2, 10);
    cout << "Found match: " <<  (match_id == found_match) << endl;

    cout << SEP << endl;
    Game::UserStats stal;
    Game::UserStats reag;
    g.get_user_stats("stalin", stal);
    g.get_user_stats("reagan", reag);
    cout << "stalin's stats == reagan's stats: "
    << (stal == reag) << endl;

    cout << SEP << endl;
    g.add_party_to_match(party2, match_id);
    g.start_match(match_id);
    g.end_match(match_id, 1000, 0, 10);
    cout << "Ending match, team1 experience == 1000, team2 experience == 0"
    << endl;
    Game::UserStats us;
    g.get_user_stats("stalin", us);
    cout << "stalin's experience == 1000: " << (us.experience == 1000) << endl;
    g.get_user_stats("reagan", us);
    cout << "reagan's experience == 0: " << (us.experience == 0) << endl;
 
    cout << SEP << endl;
    match_id = g.make_match(party1);
    found_match = g.find_match(party2, 10);
    cout << left << setw(20) << "Found match, tolerance 10: " 
    << (found_match != NULL_MATCH_ID) << endl;
    found_match = g.find_match(party2, 1000);

}

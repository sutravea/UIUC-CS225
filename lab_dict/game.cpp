#include <algorithm>
#include <cstdlib>

#include "game.h"

using namespace game_ret;
using namespace std;

/**
 * Adds a user to the game.
 * @param username The username of the user to add.
 * @return SUCCESS on success, USER_EXISTS on failure (the username is already 
 * in use).
 */
int Game::add_user(const string& username)
{
    auto inserted = users.emplace(username, User());
    return inserted.second ? SUCCESS : USER_EXISTS;
}

/**
 * Deletes a user from the game.
 * @param username The username of the user to delete.
 * @return SUCCESS on success, INVALID_USERNAME if the username is not in use,
 * FAIL if the user is currently online. 
 */
int Game::delete_user(const string& username)
{
    /* Your code goes here! */
    return FAIL;
}

/**
 * Changes the internal state of the user so that they are logged in.
 * @return SUCCESS on success, INVALID_USERNAME if the username doesn't exist.
 * @param username The username of the user to login.
 */
int Game::login_user(const string& username)
{
    auto user = users.find(username);
    if(user != users.end())
    {
        user->second.status = User::ONLINE;
        return SUCCESS;
    }
    else
    {
        return INVALID_USERNAME;
    }
}

/**
 * Changes the internal state of the user so that they are logged out.
 * @return SUCCESS on success, USER_IN_MATCH if the user is in a match and 
 * can't be logged out, INVALID_USERNAME if the username doesn't exist. 
 * @param username The username of the user to logout.
 */
int Game::logout_user(const string& username)
{
    /* Your code goes here! */
    return FAIL;
}

/**
 * Adds a party to this match. 
 * The party will be added such that they all end up on the same team. 
 * Each team has a maximum size of Match::MAX_PLAYERS / 2.
 * @return SUCCESS on success, FAIL when the party couldn't contain the party.
 * @param p The party to be added.
 */
int Game::Match::add_party(const Party& p)
{
    if(team1.size() + p.members.size() <= Match::MAX_PLAYERS / 2 ||
       team2.size() + p.members.size() <= Match::MAX_PLAYERS / 2)
    {
        if(team1.size() <= team2.size())
        {
            team1.insert(team1.end(), p.members.begin(), p.members.end());
        }
        else
        {
            team2.insert(team2.end(), p.members.begin(), p.members.end());
        }
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

/**
 * Removes a party from this match.
 * @return SUCCESS on success, FAIL if the party was not in this match (any 
 * username of the party was not found). Will erase all members up until a
 * username not in the party is found.
 */
int Game::Match::remove_party(const Party& p)
{
    for(const string& username : p.members)
    {
        auto username_itr = find(team1.begin(), team1.end(), username);
        /* Are they on team1? */
        if(username_itr != team1.end())
        {
            team1.erase(username_itr);
        }
        /* team2? */
        else
        {
            username_itr = find(team2.begin(), team2.end(), username);
            if(username_itr != team2.end())
            {
                team2.erase(username_itr);
            }
            /* Neither... Sad face. */
            else
            {
                return FAIL;
            }
        }
    }
    return SUCCESS;
}

/** 
 * Creates a new match from the given party id. 
 * @return The new match id on success, 0 (null match id) on failure
 * (the paty id was invalid or a user in the party is already in a match).
 * @param party_id The party id of the party creating the match.
 */ 
unsigned long Game::make_match(const string& party_id)
{
    /* Your code goes here! */
    return NULL_MATCH_ID;
}

/**
 * Finds a match for the party referred to by the given party id.
 * The match is found on the basis of experience. If the Party's average 
 * experience is within some tolerance of a Match's average experience 
 * (the average experience of all users in the Match), then that is our
 * matched Match. Note: "within" means that the absolute difference is
 * <= the tolerance.
 * @return The match id of the matched match on success, 0 (null match
 * id) on failure (the party id was invalid).
 * @param party_id The party id of the party finding the match.
 * @param tolerance The experience tolerance to use when finding a Match.
 */
unsigned long Game::find_match(const string& party_id, long tol)
{
    /* Your code goes here! */
    return NULL_MATCH_ID;
}

/**
 * Creates a party from a vector of usernames.
 * @return The party id of the new party on success. Empty string on 
 * failure (one or more of the usernames was invalid or one of them
 * is already in a party).
 * @param users The vector of usernames to make a party from.
 */
string Game::make_party(const vector< string >& usernames)
{
    /* Your code goes here! */
    return "";
}

/**
 * Deletes the party.
 * @return SUCCESS on success, FAIL if any of the users in the party are in
 * a match, INVALID_PARTY if the party doesn't exist.
 * @param party_id The id of the party to disband.
 */
int Game::disband_party(const string& party_id)
{
    auto party_itr = parties.find(party_id);
    if(party_itr != parties.end())
    {
        for(string& username : party_itr->second.members)
        {
            if(users[username].match_id != 0)
            {
                return FAIL;
            }
            else
            {
                users[username].party_id = "";
            }
        }   
        parties.erase(party_id);
        return SUCCESS;
    }
    else
    {
        return INVALID_PARTY;
    }
}

/**
 * Adds a party to a match.
 * @return SUCCESS on success, INVALID_MATCH if the match doesn't exist,
 * INVALID_PARTY if the party doesn't exist, FAIL if the party couldn't
 * be added to the match.
 * @param party_id The id of the party to add.
 * @param match_id The id of the match to add the party to.
 */
int Game::add_party_to_match(const string& party_id, 
                             unsigned long match_id)
{
    auto party_itr = parties.find(party_id);
    if(party_itr != parties.end())
    {
        Party& party = party_itr->second;
        auto match_itr = matches.find(match_id);
        if(match_itr != matches.end())
        {
            int ret = matches[match_id].add_party(party);
            if(ret == 0)
            {
                for(string& username : party.members)
                {
                    users[username].match_id = match_id;
                }   
                return SUCCESS;
            }
            else
            {
                return FAIL;
            }
        }
        else
        {
            return INVALID_MATCH;
        }
    }
    else
    {
        return INVALID_PARTY;
    }
}

/**
 * Removes a party from a match.
 * @return SUCCESS on success, INVALID_MATCH if the match is invalid,
 * INVALID_PARTY if the party is invalid. 
 * @param party_id The id of the party to remove.
 * @param match_id The id of the match to remove the party from.
 */
int Game::remove_party_from_match(const std::string& party_id,
                                  unsigned long match_id)
{
    auto match_itr = matches.find(match_id);
    if(match_itr != matches.end())
    {
        auto party_itr = parties.find(party_id);        
        if(party_itr != parties.end())
        {
            return match_itr->second.remove_party(party_itr->second);
        }
        else
        {
            return INVALID_PARTY;
        }
    }
    else
    {
        return INVALID_MATCH;
    }
}

/**
 * Changes the match's internal state to be started.
 * @return SUCCESS on success, INVALID_MATCH if the match is invalid,
 * FAIL if the match couldn't be started (the teams were unbalanced).
 * @param match_id id of the match to start.
 */
int Game::start_match(unsigned long match_id)
{
    auto match_itr = matches.find(match_id);
    if(match_itr != matches.end())
    {
        int team1_size = match_itr->second.team1.size();
        int team2_size = match_itr->second.team2.size();
        if(abs(team1_size - team2_size) <= 2)
        {
            for(string& username : match_itr->second.team1)
            {
                users[username].status = User::IN_GAME;
            }
            for(string& username : match_itr->second.team2)
            {
                users[username].status = User::IN_GAME;
            }
            match_itr->second.status = Match::IN_GAME;
            return SUCCESS;
        }
        else
        {
            return FAIL;
        }
    }
    else
    {
        return INVALID_MATCH;
    }
}

/**
 * Ends the match and updates users' statistics. A winner is inferred
 * from which team was awarded more experience.
 * @return SUCCESS on success, INVALID_MATCH if the match id was invalid, FAIL
 * if the match was not in a game.
 * @param match_id id of the match to end.
 * @param team1_xp Experience awarded to team1.
 * @param team2_xp Experience awarded to team2.
 * @param elapsed_time Amount of time the match lasted.
 */
int Game::end_match(unsigned long match_id, long team1_xp, 
                    long team2_xp, unsigned long elapsed_time)
{
    auto match_itr = matches.find(match_id);
    if(match_itr != matches.end() && match_itr->second.status == Match::IN_GAME)
    {
        unordered_set< string > processed_parties = { "" };
        bool team1_won = team1_xp > team2_xp;

        end_match_update(match_itr->second.team1, 
                         processed_parties, 
                         team1_xp, 
                         elapsed_time, 
                         team1_won); 
        end_match_update(match_itr->second.team2, 
                         processed_parties, 
                         team2_xp, 
                         elapsed_time, 
                         ! team1_won); 

        matches.erase(match_id);
        return SUCCESS;
    }
    else if(match_itr->second.status == Match::IN_LOBBY)
    {
        return FAIL;
    }
    else
    {
        return INVALID_MATCH;
    }
}

/**
 * Helper function for updating statistics on Match end.
 * @param team The team we are updating statistics for.
 * @param processed_parties A set of parties we have already processed 
 * (any parties already in here have had their party stats updated).
 * @param xp The experience earned by the team.
 * @param elapsed_time The time elapsed while the Match was in-game.
 * @param win Whether or not the team won.
 */
void Game::end_match_update(vector< string >& team,
                            unordered_set< string >& processed_parties,
                            long xp,
                            unsigned long elapsed_time,
                            bool win) 
{
    for(string& username : team)
    {
        User& user = users[username];
        
        if(win)
        {
            user.us.wins++;
            user.us.win_streak++;

            if(processed_parties.find(user.party_id) == processed_parties.end())
            {
                parties[user.party_id].wins++;
                parties[user.party_id].win_streak++;
                processed_parties.insert(user.party_id);
            }
        }
        else
        {
            user.us.losses++;
            user.us.win_streak = 0;

            if(processed_parties.find(user.party_id) == processed_parties.end())
            {
                parties[user.party_id].win_streak = 0;
                processed_parties.insert(user.party_id);
            }
        }
        user.us.experience += xp;
        user.us.playtime += elapsed_time;
        user.status = User::ONLINE;
        user.match_id = NULL_MATCH_ID;
    }
}

/**
 * Public interface for a user's statistics.
 * @return SUCCESS on success, INVALID_USERNAME if the username doesn't 
 * exist.
 * @param username Username of the user whose stats to retrieve.
 * @param us UserStats object to fill with the user's stats.
 */ 
int Game::get_user_stats(const string& username, UserStats& us)
{
    /* Your code goes here! */
    return FAIL;
}

/**
 * @file game.h
 * Definition of a class for keeping track of various information for 
 * some sort of game.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

namespace game_ret
{
    const int SUCCESS = 0;
    const int FAIL = -1;
    const int USER_EXISTS = -2;
    const int INVALID_USERNAME = -3;
    const int INVALID_PARTY = -4;
    const int INVALID_MATCH = -5;
    const int USER_IN_MATCH = -6;
    const unsigned long NULL_MATCH_ID = 0;
}

/**
 * Game class. Provides interfaces for keeping track of various
 * information for a game program. Supports unique users, matches,
 * parties (groups of users) and functions which involve those.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
class Game
{
    public:
    Game() : next_match_id(1) {}
    
    /** 
     * Statistics associated with each user. Completely public. 
     */
    struct UserStats
    {
        unsigned long wins;
        unsigned long losses;
        unsigned long win_streak;   
        unsigned long playtime;
        long experience;
        UserStats() : 
            wins(0), losses(0), win_streak(0), playtime(0), experience(0)
        { /* Nothing. */ }
        bool operator==(const UserStats& other) const 
        { 
            return wins == other.wins &&
                   losses == other.losses &&
                   win_streak == other.win_streak &&
                   playtime == other.playtime &&
                   experience == other.experience;
        }

    };

     /**
     * Adds a user to the game.
     * @param username The username of the user to add.
     * @return SUCCESS on success, USER_EXISTS on failure (the username is 
     * already in use).
     */
    int add_user(const std::string& username);

    /**
     * Deletes a user from the game.
     * @param username The username of the user to delete.
     * @return SUCCESS on success, INVALID_USERNAME if the username is not in 
     * use, FAIL if the user is currently online. 
     */
    int delete_user(const std::string& username);

    /**
     * Changes the internal state of the user so that they are logged in.
     * @return SUCCESS on success, INVALID_USERNAME if the username doesn't 
     * exist.
     * @param username The username of the user to login.
     */
    int login_user(const std::string& username);

    /**
     * Changes the internal state of the user so that they are logged out.
     * @return SUCCESS on success, USER_IN_MATCH if the user is in a match and 
     * can't be logged out, INVALID_USERNAME if the username doesn't exist. 
     * @param username The username of the user to logout.
     */
    int logout_user(const std::string& username);

    /** 
     * Creates a new match from the given party id. 
     * @return The new match id on success, 0 (null match id) on failure
     * (the paty id was invalid or a user in the party is already in a match).
     * @param party_id The party id of the party creating the match.
     */ 
    unsigned long make_match(const std::string& party_id);

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
    unsigned long find_match(const std::string& party_id, long tol);

    /**
     * Creates a party from a vector of usernames.
     * @return The party id of the new party on success. Empty string on 
     * failure (one or more of the usernames was invalid or one of them
     * is already in a party).
     * @param users The vector of usernames to make a party from.
     */
    std::string make_party(const std::vector< std::string >& usernames);

    /**
     * Deletes the party.
     * @return SUCCESS on success, FAIL if any of the users in the party are in
     * a match, INVALID_PARTY if the party doesn't exist.
     * @param party_id The id of the party to disband.
     */
    int disband_party(const std::string& party_id);

    /**
     * Adds a party to a match.
     * @return SUCCESS on success, INVALID_MATCH if the match doesn't exist,
     * INVALID_PARTY if the party doesn't exist, FAIL if the party couldn't
     * be added to the match.
     * @param party_id The id of the party to add.
     * @param match_id The id of the match to add the party to.
     */
    int add_party_to_match(const std::string& party_id, 
                           unsigned long match_id);

    /**
     * Removes a party from a match.
     * @return SUCCESS on success, INVALID_MATCH if the match is invalid,
     * INVALID_PARTY if the party is invalid. 
     * @param party_id The id of the party to remove.
     * @param match_id The id of the match to remove the party from.
     */
    int remove_party_from_match(const std::string& party_id,
                                unsigned long match_id);
    
    /**
     * Changes the match's internal state to be started.
     * @return SUCCESS on success, INVALID_MATCH if the match is invalid,
     * FAIL if the match couldn't be started (the teams were unbalanced).
     * @param match_id id of the match to start.
     */
    int start_match(unsigned long match_id);

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
    int end_match(unsigned long match_id, long team1_xp, 
                  long team2_xp, unsigned long elapsed_time);

    /**
     * Public interface for a user's statistics.
     * @return SUCCESS on success, INVALID_USERNAME if the username doesn't 
     * exist.
     * @param username Username of the user whose stats to retrieve.
     * @param us UserStats object to fill with the user's stats.
     */ 
    int get_user_stats(const std::string& username, UserStats& us);

    private:
    unsigned long next_match_id;

    /** 
     * All data associated with a Party (a group of users staying 
     * together). */
    struct Party
    {
        std::vector< std::string > members;
        unsigned long wins;
        unsigned long losses;
        unsigned long win_streak;
    };

    /** 
     * All data associated with a Match (a group of users playing
     * together). */
    class Match
    {
        public:
        static const unsigned int MAX_PLAYERS = 12;
        static const unsigned int MATCH_MAKE_TOLERANCE = 100;
        std::vector< std::string > team1;
        std::vector< std::string > team2;
        enum Status { IN_GAME, IN_LOBBY };
        Status status;

        /**
         * Constructs a default Match, only has to set status.
         */
        Match()
        {
            status = IN_LOBBY;
        }

        /**
         * Adds a party to this match. 
         * @return 0 on success, -1 on failure (the party couldn't 
         * contain the party. The party will be added such that they
         * end up on the same team.
         * @param p The party to be added.
         */
        int add_party(const Party& p);

        /**
         * Removes a party from this match.
         * @return 0 on success, -1 on failure (the party was 
         * not in this match.
         */
        int remove_party(const Party& p);

    };

    /**
     * Helper function for updating statistics on Match end.
     * @param team The team we are updating statistics for.
     * @param processed_parties A set of parties we have already processed 
     * (any parties already in here have had their party stats updated).
     * @param xp The experience earned by the team.
     * @param elapsed_time The time elapsed while the Match was in-game.
     */
    void end_match_update(std::vector< std::string >& team,
                          std::unordered_set< std::string >& processed_parties,
                          long xp,
                          unsigned long elapsed_time,
                          bool win); 

    /**
     * All data associated with a User. Contains the User's current state
     * in the game universe, a list of their friends' usernames, the match
     * id they're currently in, the party id of the party they are in, and
     * they're statistics.
     */
    struct User
    {
        enum Status {OFFLINE, ONLINE, IN_GAME};
        Status status;
        std::vector< std::string > friends;
        unsigned long match_id;
        std::string party_id;
        UserStats us;
    };

    /* Maps used to find all the important data. */
    std::unordered_map< std::string, User > users;
    std::unordered_map< unsigned long, Match > matches;
    std::unordered_map< std::string, Party > parties;
};

#endif /* GAME_H */

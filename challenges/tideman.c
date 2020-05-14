#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void print_vote_table(void);
void print_ranking(int ranks[]);
void print_pairs(void);
void print_locked(void);
bool recursive_lock(int a, int b);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        // printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        // printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                // printf("Invalid vote.\n");
                return 3;
            }
        }

        // print_ranking(ranks);

        // we get back the ranks for one vote
        // the number at index i signifies a candidates index
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();

    // print_locked();

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // add candidate index to rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int rank = 0; rank < candidate_count - 1; rank++)
    // preferences[i][j] is number of voters who prefer i over j
    {
        int candidateIndex = ranks[rank];
        int lowerCandidateIndex = ranks[rank + 1];
        for (int j = rank + 1; j < candidate_count; j++)
        {
            lowerCandidateIndex = ranks[j];
            preferences[candidateIndex][lowerCandidateIndex]++;
        }
    }
    print_vote_table();
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Each pair has a winner, loser
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = candidate_count - 1; j >= 0; j--)
        {
            if (i != j)
            {
                int votesFor_i_Over_j = preferences[i][j];
                int votesFor_j_Over_i = preferences[j][i];
                if (votesFor_i_Over_j > votesFor_j_Over_i)
                {
                    // printf("i: %s wins from j: %s \n", candidates[i], candidates[j]);
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (votesFor_i_Over_j < votesFor_j_Over_i)
                {
                    // printf("j: %s wins from i: %s \n", candidates[j], candidates[i]);
                    pairs[pair_count].loser = i;
                    pairs[pair_count].winner = j;
                    pair_count++;
                }
                else
                {
                    // printf("j: %s draws i: %s \n", candidates[j], candidates[i]);
                }
            }
        }
    }
    print_pairs();
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    bool swapped = false;
    do
    {
        swapped = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int x = pairs[i].winner;
            int y = pairs[i].loser;
            int x_Over_y = preferences[x][y];
            int y_Over_x = preferences[y][x];
            int strength = x_Over_y - y_Over_x;
            int _x = pairs[i + 1].winner;
            int _y = pairs[i + 1].loser;
            int _x_Over_y = preferences[_x][_y];
            int _y_Over_x = preferences[_y][_x];
            int _strength = _x_Over_y - _y_Over_x;
            if (strength < _strength)
            {
                printf("strength1 %i < strength2 %i \n", strength, _strength);
                pair tmp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = tmp;
                swapped = true;
            }
        }
    } while (swapped);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // bool stop = false;
    // bool collock[MAX];
    // for (int j = 0; j < pair_count || !stop; j++)
    // {
    //     locked[pairs[j].winner][pairs[j].loser] = true;
    //     for(int c = 0; c<candidate_count; c++)
    //     {
    //       printf("\n");
    //         for(int i = 0; i<candidate_count; i++)
    //         {
    //             if(locked[c][i])
    //             {
    //                 collock[i] = true;
    //             }
    //         }
    //     }
    //     stop = true;
    //     for(int q = 0; q<candidate_count; q++)
    //     {
    //       if(!collock[q]){
    //           stop = false;
    //           break;
    //       }
    //     }
    //     if(stop)
    //     {
    //       locked[pairs[j].winner][pairs[j].loser] = false;
    //     }
    // }
    for (int i = 0; i < pair_count; i++)
    {
        if (recursive_lock(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winnerIndex;
    bool collock[MAX];
    for (int c = 0; c < candidate_count; c++)
    {
        printf("\n");
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[c][i])
            {
                collock[i] = true;
            }
        }
    }
    for (int q = 0; q < candidate_count; q++)
    {
        if (!collock[q])
        {
            winnerIndex = q;
        }
    }
    printf("%s\n", candidates[winnerIndex]);
    return;
}

void print_vote_table(void)
{
    for (int c = 0; c < candidate_count; c++)
    {
        printf("%s\t", candidates[c]);
    }
    for (int c = 0; c < candidate_count; c++)
    {
        printf("\n");
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d\t", preferences[c][j]);
        }
        printf("\t %s", candidates[c]);
    }
}

void print_ranking(int ranks[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        printf("\n");
        printf("RankIndex %i CandidateIndex %i", j, ranks[j]);
        printf("\n");
    }
}

void print_pairs(void)
{
    for (int j = 0; j < pair_count; j++)
    {
        printf("for %i pair\n", j + 1);
        printf("winner index is %i - name is %s\n", pairs[j].winner, candidates[pairs[j].winner]);
        printf("loser index is %i - name is %s\n", pairs[j].loser, candidates[pairs[j].loser]);
    }
}

void print_locked(void)
{

    for (int c = 0; c < candidate_count; c++)
    {
        printf("%s\t", candidates[c]);
    }

    for (int c = 0; c < candidate_count; c++)
    {
        printf("\n");
        for (int j = 0; j < candidate_count; j++)
        {
            printf(locked[c][j] ? "true\t" : "false\t");
        }
        printf("\t %s", candidates[c]);
    }
    printf("\n");
}

bool recursive_lock(int a, int b)
{
    if (a == b)
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][a] == true)
        {
            if (recursive_lock(i, b) == false)
            {
                return false;
            }
        }
    }
    return true;
}
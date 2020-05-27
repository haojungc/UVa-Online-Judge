/* Poker Hands */
/* PC/UVa IDs: 110202/10315, Popularity: C, Success rate: average, Level: 2 */
#include <stdio.h>
#include <stdbool.h>

#define MAX_CARD    5
#define MAX_LEN     13

typedef enum { NONE, BLACK, WHITE } Winner;
typedef enum {
    HIGH_CARD,
    PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
} Hand;

typedef struct {
    int value;      // possible values: 0 ~ 12
    char suit;      // no impact on value
} Card;

int to_value(char);                     // returns the value of the card
void sort(Card[]);                      // sorts a hand in "ascending order"
Winner get_winner(Card[], Card[]);      // compares two poker hands and returns the winner
Hand get_hand_order(Card[]);            // returns the order of the matched poker hand
Winner compare(Card[], Card[], Hand);   // compares two poker hands and return the winner
                                        // The third parameter is used for deciding which ranking rule of hand types is to be called.

bool is_straight_flush(Card[]);
bool is_four_of_a_kind(Card[]);
bool is_full_house(Card[]);
bool is_flush(Card[]);
bool is_straight(Card[]);
bool is_three_of_a_kind(Card[]);
bool is_two_pairs(Card[]);
bool is_pair(Card[]);

// compares two poker hands and returns the winner
Winner cmp_straight_flush(Card[], Card[]);
Winner cmp_four_of_a_kind(Card[], Card[]);
Winner cmp_full_house(Card[], Card[]);
Winner cmp_flush(Card[], Card[]);
Winner cmp_straight(Card[], Card[]);
Winner cmp_three_of_a_kind(Card[], Card[]);
Winner cmp_two_pairs(Card[], Card[]);
Winner cmp_pair(Card[], Card[]);
Winner cmp_high_card(Card[], Card[]);

int main() {
    Card black[MAX_CARD], white[MAX_CARD];
    char value, suit, c;

    while (scanf("%c%c%c", &value, &suit, &c) != EOF) {
        // Input the first card for player Black
        black[0].value = to_value(value);
        black[0].suit = suit;

        // Input the four remaining cards for player Black
        for (int i = 1; i < MAX_CARD; i++) {
            scanf("%c%c%c", &value, &suit, &c);
            black[i].value = to_value(value);
            black[i].suit = suit;
        }
        // Input five cards for player White
        for (int i = 0; i < MAX_CARD; i++) {
            char value, suit, c;
            scanf("%c%c%c", &value, &suit, &c);

            white[i].value = to_value(value);
            white[i].suit = suit;
        }

        sort(black);    // descending order
        sort(white);    // descending order

        Winner winner = get_winner(black, white);

        // Shows the winner
        if (winner == NONE)
            printf("Tie.\n");
        else if (winner == BLACK) {
            printf("Black wins.\n");
        }
        else if (winner == WHITE) {
            printf("White wins.\n");
        }
    }

    return 0;
}

int to_value(char value) {
    switch (value) {
        case '2': return 0;
        case '3': return 1;
        case '4': return 2;
        case '5': return 3;
        case '6': return 4;
        case '7': return 5;
        case '8': return 6;
        case '9': return 7;
        case 'T': return 8;
        case 'J': return 9;
        case 'Q': return 10;
        case 'K': return 11;
        case 'A': return 12;
        default:  return -1;
    }
}

// Selection sort
void sort(Card c[]) {
    // sorts c[] in descending order
    for (int i = 0; i < MAX_CARD - 1; i++) {
        for (int j = i + 1; j < MAX_CARD; j++) {
            if (c[j].value > c[i].value) {
                int tmp = c[j].value;
                c[j].value = c[i].value;
                c[i].value = tmp;
            }
        }
    }
}

Winner get_winner(Card b[], Card w[]) {
    Winner winner;
    Hand b_order = get_hand_order(b);
    Hand w_order = get_hand_order(w);

    if (b_order == w_order)     winner = compare(b, w, b_order);
    else if (b_order > w_order) winner = BLACK;
    else if (b_order < w_order) winner = WHITE;

    return winner;
}

Hand get_hand_order(Card c[]) {
    if (is_straight_flush(c))   return STRAIGHT_FLUSH;
    if (is_four_of_a_kind(c))   return FOUR_OF_A_KIND;
    if (is_full_house(c))       return FULL_HOUSE;
    if (is_flush(c))            return FLUSH;
    if (is_straight(c))         return STRAIGHT;
    if (is_three_of_a_kind(c))  return THREE_OF_A_KIND;
    if (is_two_pairs(c))        return TWO_PAIRS;
    if (is_pair(c))             return PAIR;

    return HIGH_CARD;
}

Winner compare(Card b[], Card w[], Hand hand) {
    switch (hand) {
        case HIGH_CARD:         return cmp_high_card(b, w);
        case PAIR:              return cmp_pair(b, w);
        case TWO_PAIRS:         return cmp_two_pairs(b, w);
        case THREE_OF_A_KIND:   return cmp_three_of_a_kind(b, w);
        case STRAIGHT:          return cmp_straight(b, w);
        case FLUSH:             return cmp_flush(b, w);
        case FULL_HOUSE:        return cmp_full_house(b, w);
        case FOUR_OF_A_KIND:    return cmp_four_of_a_kind(b, w);
        case STRAIGHT_FLUSH:    return cmp_straight_flush(b, w);
    }
}

bool is_straight_flush(Card c[]) {
    int valueCount[MAX_LEN] = {0},  // the number of occurences of each value
        consec_values = 0;          // the number of consecutive values
    char suit = c[0].suit;

    // checks if all of the cards have the same suit
    // and counts the number of occurences of each value
    valueCount[c[0].value]++;
    for (int i = 1; i < MAX_CARD; i++) {
        if (c[i].suit != suit) return false;
        valueCount[c[i].value]++;
    }

    // counts the number of consecutive values
    if (valueCount[0] != 0) consec_values++;
    for (int i = 1; i < MAX_LEN; i++) {
        if (valueCount[i] != 0) {
            // checks consecutiveness
            if (valueCount[i - 1] != 0) consec_values++;
            else consec_values = 1;
        }
    }

    if (consec_values == 5) return true;

    return false;
}

bool is_four_of_a_kind(Card c[]) {
    int valueCount[MAX_LEN] = {0};  // the number of occurences of each value

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++)
        valueCount[c[i].value]++;

    for (int i = 0; i < MAX_LEN; i++)
        if (valueCount[i] == 4) return true;

    return false;
}

bool is_full_house(Card c[]) {
    int valueCount[MAX_LEN] = {0};  // the number of occurences of each value
    bool three_identical = false,   // three cards with the same value
         two_identical = false;     // two cards with the same value

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++)
        valueCount[c[i].value]++;
    
    for (int i = 0; i < MAX_LEN; i++)
        if (valueCount[i] == 3) three_identical = true;
        else if (valueCount[i] == 2) two_identical = true;
    
    if (three_identical && two_identical) return true;

    return false;
}

bool is_flush(Card c[]) {
    int valueCount[MAX_LEN] = {0};  // the number of occurences of each value
    char suit = c[0].suit;

    // checks if all of the cards have the same suit
    valueCount[c[0].value]++;
    for (int i = 1; i < MAX_CARD; i++)
        if (c[i].suit != suit) return false;
    
    return true;
}

bool is_straight(Card c[]) {
    int valueCount[MAX_LEN] = {0},  // the number of occurences of each value
        consec_values = 0;          // the number of consecutive values

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++)
        valueCount[c[i].value]++;

    // counts the number of consecutive values
    if (valueCount[0] != 0) consec_values++;
    else consec_values++;
    for (int i = 1; i < MAX_LEN; i++) {
        if (valueCount[i] != 0) {
            // checks consecutiveness
            if (valueCount[i - 1] != 0) consec_values++;
            else consec_values = 1;
        }
    }

    if (consec_values == 5) return true;

    return false;
}

bool is_three_of_a_kind(Card c[]) {
    int valueCount[MAX_LEN] = {0};  // the number of occurences of each value

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++)
        valueCount[c[i].value]++;
    
    for (int i = 0; i < MAX_LEN; i++)
        if (valueCount[i] == 3) return true;

    return false;
}

bool is_two_pairs(Card c[]) {
    int valueCount[MAX_LEN] = {0},  // the number of occurences of each value
        pair_count = 0;

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++)
        valueCount[c[i].value]++;
    
    for (int i = 0; i < MAX_LEN; i++)
        if (valueCount[i] == 2) pair_count++;
    
    if (pair_count == 2) return true;

    return false;
}

bool is_pair(Card c[]) {
    int valueCount[MAX_LEN] = {0};  // the number of occurences of each value

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++)
        valueCount[c[i].value]++;
    
    for (int i = 0; i < MAX_LEN; i++)
        if (valueCount[i] == 2) return true;

    return false;
}

Winner cmp_straight_flush(Card b[], Card w[]) {
    return cmp_straight(b, w);
}

Winner cmp_four_of_a_kind(Card b[], Card w[]) {
    int b_valueCount[MAX_LEN] = {0},    // the number of occurences of each value
        w_valueCount[MAX_LEN] = {0},
        b_max, w_max;
    Winner winner;

    // counts the number of occurences of each value
    // and finds the value of the four cards
    for (int i = 0; i < MAX_CARD; i++) {
        b_valueCount[b[i].value]++;
        w_valueCount[w[i].value]++;
        if (b_valueCount[b[i].value] == 4) b_max = b[i].value;
        if (w_valueCount[w[i].value] == 4) w_max = w[i].value;
    }  
    
    if (b_max > w_max)  winner = BLACK;
    else                winner = WHITE;

    return winner;
}

Winner cmp_full_house(Card b[], Card w[]) {
    return cmp_three_of_a_kind(b, w);
}

Winner cmp_flush(Card b[], Card w[]) {
    return cmp_high_card(b, w);
}

Winner cmp_straight(Card b[], Card w[]) {
    Winner winner;

    if (b[0].value > w[0].value)        winner = BLACK;
    else if (w[0].value > b[0].value)   winner = WHITE;
    else                                winner = NONE;

    return winner;
}

Winner cmp_three_of_a_kind(Card b[], Card w[]) {
    int b_valueCount[MAX_LEN] = {0},    // the number of occurences of each value
        w_valueCount[MAX_LEN] = {0},
        b_max, w_max;
    Winner winner;

    // counts the number of occurences of each value
    // and finds the value of the three cards
    for (int i = 0; i < MAX_CARD; i++) {
        b_valueCount[b[i].value]++;
        w_valueCount[w[i].value]++;
        if (b_valueCount[b[i].value] == 3) b_max = b[i].value;
        if (w_valueCount[w[i].value] == 3) w_max = w[i].value;
    }
    
    if (b_max > w_max)  winner = BLACK;
    else                winner = WHITE;

    return winner;
}

Winner cmp_two_pairs(Card b[], Card w[]) {
    return cmp_pair(b, w);
}

Winner cmp_pair(Card b[], Card w[]) {
    int b_valueCount[MAX_LEN] = {0},    // the number of occurences of each value
        w_valueCount[MAX_LEN] = {0};

    // counts the number of occurences of each value
    for (int i = 0; i < MAX_CARD; i++) {
        b_valueCount[b[i].value]++;
        w_valueCount[w[i].value]++;
    }

    // compares pairs
    for (int i = MAX_LEN - 1; i >= 0; i--) {
        bool b_is_greater = b_valueCount[i] == 2 && w_valueCount[i] != 2,
             w_is_greater = w_valueCount[i] == 2 && b_valueCount[i] != 2;

        if (b_is_greater) return BLACK;
        if (w_is_greater) return WHITE;
    }
    
    // compares the remaining card
    for (int i = MAX_LEN - 1; i >= 0; i--) {
        bool b_is_greater = b_valueCount[i] == 1 && w_valueCount[i] != 1,
             w_is_greater = w_valueCount[i] == 1 && b_valueCount[i] != 1;

        if (b_is_greater) return BLACK;
        if (w_is_greater) return WHITE;
    }

    return NONE;    // no winner
}

Winner cmp_high_card(Card b[], Card w[]) {
    // compares the cards
    for (int i = 0; i < MAX_CARD; i++) {
        bool b_is_greater = b[i].value > w[i].value,
             w_is_greater = w[i].value > b[i].value;

        if (b_is_greater) return BLACK;
        if (w_is_greater) return WHITE;
    }

    return NONE;    // no winner
}

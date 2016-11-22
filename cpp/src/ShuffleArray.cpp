#include "utils.h"

void shuffleArray(vector<int> &cards)
{
    int n = cards.size();
    for(int i=0; i<n; i++)
    {
        int pos = rand()%(n-i) + i;
        swap(cards[i], cards[pos]);
        Utils::dump(cards);
    }
}

int main(int argc, char* argv[])
{
    vector<int> cards;
    for(int i=1; i<=52; i++)
        cards.push_back(i);
    shuffleArray(cards);
    return 0;
}

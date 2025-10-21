#include "../include/hand.h"
#include "../include/player.h"
#include "../include/dice.h"

void player_play(Player* target, GameRules* rules)
{
    if (!target || !rules)
        return;

    Cup* cup = cup_init(rules->dices_count);
    uint8_t rerolls_left = rules->rerolls;
    Hand selected_hand;

    do
    {
        selected_hand = target->select_hand(target, rules, cup, rerolls_left);
        rerolls_left--;
    } while (selected_hand == NONE && rerolls_left > 0);

    target->hands[selected_hand] =
        hand_evaluate(selected_hand, (const Score*)target->hands, (const Cup*)cup);

    cup_close(cup);
    return;
}

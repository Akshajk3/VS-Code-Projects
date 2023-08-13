import random

def genCard():
    cards = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11]
    card_num = random.choice(cards)
    return card_num

def main():
    totalCard = genCard()
    playing = True

    while playing:
        print(totalCard)
        player_choice = input("Do you want to draw another card? (Y/N): ")

        if player_choice == "Y":
            card = genCard()
            totalCard += card
            if totalCard > 21:
                print("Card Total: " + totalCard + ". Card total is over 21 you lost haha")


if __name__ == "__main__":
    main()
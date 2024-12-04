#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int playerNum;

struct card {
	char suit;
	char value;
};

void shuffle(struct card* deck) {
    srand(time(0));
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 13; j++) {
			struct card* c = malloc(sizeof(struct card));
			switch(i) {
			case 0:
				c->suit = 'D';
				break;
			case 1:
				c->suit = 'C';
				break;
			case 2:
				c->suit = 'H';
				break;
			default:
				c->suit = 'S';
				break;
			}
			char v;
			switch(j) {
			case 8:
				v = 'T';
				break;
			case 9:
				v = 'J';
				break;
			case 10:
				v = 'Q';
				break;
			case 11:
				v = 'K';
				break;
			case 12:
				v = 'A';
				break;
			default:
				v = j + 2 + '0';
				break;
			}
			c->value = v;
			deck[(i*13) + j] = *c;
			free(c);
		}
	}

	for (int i = 0; i < 52*7; i++) {
		int n1 = rand()%52;
		int n2 = rand()%52;
		while(n1 == n2) {
			n2 = rand()%52;
		}
		struct card temp = deck[n1];
        deck[n1] = deck[n2];
        deck[n2] = temp;
	}
}

void game() {
	struct card* deck = malloc(sizeof(struct card) * 52);
	int* sum = calloc(playerNum,sizeof(int));
	int* hasAce = calloc(playerNum,sizeof(int));
	shuffle(deck);
	//printf("\nYou got a %c of %c!",(deck[1].value), (deck[1].suit));

	int location = 0;

	for(int i = 1; i <= playerNum; i++) {
		int choice;
		char* hand = calloc(10,sizeof(char));
		int inc = 0;
		
		for(int j = 0; j < 2; j++){
		    	struct card* c = malloc(sizeof(struct card));
				c = &deck[location];
				hand[inc] = c->value;
				
				int valueue = c->value - '0';
				
				switch(c->value){
				    case 'T':
				    case 'J':
				    case 'Q':
				    case 'K':
				        valueue = 10;
				        break;
				    case 'A':
				        valueue = 1;
				        hasAce[i-1] ++;
				        break;
				}
				
				sum[i-1] += valueue;
				
				location++;
				inc++;
				location = location%52;
		}
		
		do {
			printf("\nPlayer %d's turn: 1 to deal, 2 to check your hand, any other number else to stay. ", i);
			scanf("%d",&choice);
			if(choice == 1) {
				struct card* c = malloc(sizeof(struct card));
				c = &deck[location];
				hand[inc] = c->value;
				
				int value = c->value - '0';
				
				switch(c->value){
				    case 'T':
				    case 'J':
				    case 'Q':
				    case 'K':
				        value = 10;
				        break;
				    case 'A':
				        value = 1;
				        hasAce[i-1] ++;
				        break;
				}
				
				sum[i-1] += value;
				
				location++;
				inc++;
				location = location%52;
				printf("You got a %c of %c!\n",(c->value), (c->suit));
			} else if(choice == 2) {
			    printf("\n");
                for(int j = 0; j < 10; j++){
                    if(hand[j] == 0){
                        break;
                    }
                    printf("%c ",hand[j]);
                }
			}
		} while(choice == 1 || choice == 2);
	}
	
	int highest = 0;
	int* winners = calloc(playerNum,sizeof(int));
	location = 0;
	
	for(int i = 0; i < playerNum; i++){
	    for(int j = 0; j < hasAce[i]; j++){
	        if(sum[j] + 10 <= 21){
	            sum[j] += 10;
	        }else{
	            break;
	        }
	    }
	    
	    if(sum[i] > 21){
	        continue;
	    }
	    
	    if(sum[i]>highest){
	        highest = sum[i];
            memset(winners, playerNum, 0);
	        location = 1;
	        winners[0] = i+1;
	    }else if(sum[i]==highest){
	        winners[location] = i+1;
	    }
	}
	
	printf("\nThe winner(s) is/are: ");
	
	for(int j = 0; j < 10; j++){
        if(winners[j] == 0){
            break;
        }
        printf("Player %d ",winners[j]);
    }
    
    if(winners[0] == 0){
        printf("noone");
    }
    
    printf("\n");
    
	free(sum);
	free(hasAce);
	free(deck);
}

void instructions(){
    printf("\nThe goal of 21 is to be the player to get the closest to 21 (in terms of card value) without going over.\nThe cards are from your standard deck. Numbered cards are worth their face value, J, Q, K are worth 10, and aces can be worth 1 or 11 depending on whether or not you surpass 21.\nYou start with 2 cards.\nAs a player, you can choose to deal, view, or stay.\n deal: get dealt a card (adds to your hand).\n view: views your current hand and what cards you have.\n stay: ends your turn\n");
}

int main()
{
    printf("Welcome to 21!");
    int choice;
    do{
        printf("\nEnter 1 to play, 2 to view the instructions, any other number to quit. ");
        scanf("%d", &choice);
        if(choice == 1){
            printf("\nHow many players are there? (2-10) ");
            scanf("%d",&playerNum);
            while(playerNum > 10 || playerNum < 2){
                printf("\nPlease input a value between 2 and 10 inclusive: ");
                scanf("%d",&playerNum);
            }
    	    game();
        }else if(choice == 2){
            instructions();
        }
    }while(choice > 0 &&  choice < 3);
    	printf("\nThank you for playing!");
	return 0;
}

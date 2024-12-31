#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

 // Base stats
int INITIAL_PLAYER_LIFE_POINTS = 100;
int INITIAL_DRAGON_LIFE_POINTS = 20;
int PLAYER_ATTACK = 10;
int FIRE_DAMAGE = 20;
int PLAYER_MOVEMENT_COST = 10;
int PLAYER_LEVEL = 0;
float PLAYER_COIN = 0;
int INITIAL_POTION1_PRICE = 20;
int INITIAL_POTION2_PRICE = 20;
int INITIAL_POTION3_PRICE = 40;
int INITIAL_POTION4_PRICE = 20;
int INITIAL_POTION5_PRICE = 500;
int INITIAL_ROUND = 1;
int INITIAL_N = 5;


void bubblesort(char user[][100],int day[], char month[][100], int year[], int sumround[], int size){
	int m,n;
		for(m = 0; m < size - 1; m++){
			for(n = 0; n < size - m - 1; n++){
				if(sumround[n] < sumround[n+1]){
					
					//swap sumround
					int tempround = sumround[n+1];
					sumround[n+1] = sumround[n];
					sumround[n] = tempround;
					
					//swap day
					int tempday = day[n+1];
					day[n+1] = day[n];
					day[n] = tempday;
					
					//swap month
					char tempmonth[100];
					strcpy(tempmonth, month[n+1]);
					strcpy(month[n+1], month[n]);
					strcpy(month[n], tempmonth);
					
					//swap year
					int tempyear;
					tempyear = year[n+1];
					year[n+1] = year[n];
					year[n] = tempyear;
					
					// swap username
					char tempName[100];
					strcpy(tempName, user[n+1]);
					strcpy(user[n+1], user[n]);
					strcpy(user[n], tempName);
				}
			}
		}
}

char name[50];
char password[50];
void accountAuthentication(FILE* fp){
	// Check if file has been created
	fp = fopen("accounts.txt","r");
	if(fp==NULL){
		// Create an empty file named "accounts.txt"
		fclose(fp);
		fp=fopen("accounts.txt","w");
		fclose(fp);
	}
	else{
		fclose(fp);
	}
	int decision;
	printf("1. Sign up\n2. Log in\n");
	printf("Do you wish to sign up or log in?\n");
	printf("Please enter decision: ");
	scanf("%d",&decision);
	getchar();
	if(decision == 1){
		printf("Enter Name: ");
		scanf("%[^\n]",name);
		getchar();
		printf("Enter Password: ");
		scanf("%[^\n]",password);
		getchar();
		fp=fopen("accounts.txt","a+");
		fprintf(fp,"%s,%s\n",name,password);
		fclose(fp);
		printf("Account registered succesfully\n");
		Sleep(1000);
	}
	if(decision == 2){
		bool valid = false;
		char tempName[50];
		char tempPassword[50];
		while(1){
			printf("Enter Name: ");
			scanf("%[^\n]",tempName);
			getchar();
			printf("Enter Password: ");
			scanf("%[^\n]",tempPassword);
			getchar();
			fp=fopen("accounts.txt","r");
			rewind(fp);
			while(fscanf(fp,"%[^,],%[^\n]\n",name,password)==2){	
				if(strcmp(name,tempName)==0&&strcmp(password,tempPassword)==0){
					fclose(fp);
					valid = true;
					break;
				}
			}
			if(valid){
				break;
			}
			else{
				printf("Username and password dont match. Please retry again\n");
			}
		}
		printf("Welcome %s!\n",name);
		Sleep(1000);
	}
	
}
// Function to print the game field and player/dragon status
void printField(char field[][100], int n, int playerLifePoints, int dragonLifePoints, float coin, int round) {
	printf("Round %d\nGame field: %d x %d\n", round, n, n);
    // Loop through each cell in the field
    int i,j;
	for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // Display characters based on their content
            if (field[i][j] == '*' || field[i][j] == '$' || field[i][j] == '^') {
                printf("%c ", field[i][j]);
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }

    // Display player, dragon, and coin information
    printf("Player Life Points: %d\n", playerLifePoints);
    printf("Dragon Life Points: %d\n", dragonLifePoints);
    printf("Gold: %.2f\n", coin);
}

// Function to initialize the game field
void initializeField(char field[][100], int n, int* playerX, int* playerY, int* dragonX, int* dragonY, int* fireX, int* fireY) {
    // Set all cells in the field to '#'
    int i,j;
	for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            field[i][j] = '#';
        }
    }

    // Place the player '*' at a random position
    *playerX = rand() % n;
    *playerY = rand() % n;
    field[*playerX][*playerY] = '*';

    // Place the dragon '$' at a random position
    do {
        *dragonX = rand() % n;
        *dragonY = rand() % n;
    } while (field[*dragonX][*dragonY] != '#');
    field[*dragonX][*dragonY] = '$';

    // Place the fire '^' at a random position
    do {
        *fireX = rand() % n;
        *fireY = rand() % n;
    } while (field[*fireX][*fireY] != '#');
    field[*fireX][*fireY] = '^';
    
    
    
}

// Function to handle player movement
void handlePlayerMovement(char field[][100], int n, int* playerX, int* playerY, char move, int* playerLifePoints) {
    switch (move) {
        case 'w':
            if (*playerX > 0) {
                // Move player up
                field[*playerX][*playerY] = '#';
                (*playerX)--;
                field[*playerX][*playerY] = '*';
                *playerLifePoints -= PLAYER_MOVEMENT_COST;
            }
            break;
        case 'a':
            if (*playerY > 0) {
                // Move player left
                field[*playerX][*playerY] = '#';
                (*playerY)--;
                field[*playerX][*playerY] = '*';
                *playerLifePoints -= PLAYER_MOVEMENT_COST;
            }
            break;
        case 's':
            if (*playerX < n - 1) {
                // Move player down
                field[*playerX][*playerY] = '#';
                (*playerX)++;
                field[*playerX][*playerY] = '*';
                *playerLifePoints -= PLAYER_MOVEMENT_COST;
            }
            break;
        case 'd':
            if (*playerY < n - 1) {
                // Move player right
                field[*playerX][*playerY] = '#';
                (*playerY)++;
                field[*playerX][*playerY] = '*';
                *playerLifePoints -= PLAYER_MOVEMENT_COST;
            }
            break;
        case 'q':
            // Quit the game
            printf("Exiting the game.\n");
            Sleep(2500);
            exit(0);
        default:
            // Invalid move
            printf("Invalid move. Please enter w, a, s, or d.\n");
            Sleep(2500);
            break;
    }
}

// Function to handle interactions between player, dragon, and fire
void handleInteractions(char field[][100], int* n, int* playerX, int* playerY, int* dragonX, int* dragonY, int* fireX, int* fireY, int* playerLifePoints, int* dragonLifePoints, float* coin, int* round) {
    // Check if player and dragon occupy the same position
    if (*playerX == *dragonX && *playerY == *dragonY) {
        // Player hits the dragon
        printf("Player hits the dragon with an attack value of %d!\n", PLAYER_ATTACK);
        Sleep(2500);
        *playerLifePoints += PLAYER_MOVEMENT_COST;
        // Adjust dragon's lifepoints
        *dragonLifePoints -= PLAYER_ATTACK;
        if (*dragonLifePoints <= 0) {
            // Dragon is defeated
            printf("Dragon is defeated !!!\n");
            Sleep(2500);
            // Reset dragon's lifepoints and reward player with coins
            *dragonLifePoints = INITIAL_DRAGON_LIFE_POINTS+10;
            FIRE_DAMAGE += 10;
            PLAYER_MOVEMENT_COST += 5;
            *coin += 30;
            (*round)++;
            if((*round)%3 == 0){
        		(*n)++;
			}
			if((*round)%5 == 0){
				INITIAL_N = *n;
				INITIAL_ROUND = *round;
				INITIAL_DRAGON_LIFE_POINTS = *dragonLifePoints;  
			}
        }
        // Move the dragon to a new random position
        do{
            *dragonX = rand() % *n;
            *dragonY = rand() % *n;
        }while (field[*dragonX][*dragonY] != '#');
        field[*dragonX][*dragonY] = '$';
        // Regenerate the fire at a new random position
        do{
            *fireX = rand() % *n;
            *fireY = rand() % *n;
        }while(field[*fireX][*fireY] != '#');
        field[*fireX][*fireY] = '^';
        printf("Dragon leaves illusion fire marks\n");
        Sleep(1000);
    }

    // Check if player and fire occupy the same position
    if(*playerX == *fireX && *playerY == *fireY) {
        // Player hits the fire
        printf("Player hits the fire! Player loses %d lifepoints.\n", FIRE_DAMAGE);
        Sleep(1500);
        // Reduce player's lifepoints
        *playerLifePoints -= FIRE_DAMAGE;
        // Move the fire to a new random position
        do {
            *fireX = rand() % *n;
            *fireY = rand() % *n;
        }while(field[*fireX][*fireY] != '#');
        field[*fireX][*fireY] = '^';
    }
}

// function to continue feature.
void resetGame(char field[][100], int *n, int* playerX, int* playerY, int* dragonX, int* dragonY, int* fireX, int* fireY, int* playerLifePoints, int* dragonLifePoints, int* round) {
    // Inisialisasi ulang semua variabel dan field
    initializeField(field, *n, playerX, playerY, dragonX, dragonY, fireX, fireY);
    *playerLifePoints = INITIAL_PLAYER_LIFE_POINTS;
    *dragonLifePoints = INITIAL_DRAGON_LIFE_POINTS;
    *round = INITIAL_ROUND;
    *n = INITIAL_N;
}

void shop(int *playerLifePoints, int *playerAttack, float *coin, int *potion1, int *potion2, int *potion3, int *potion4, int *potion5){
	
    int choice;

    printf("\t====== Merchant Shop ======\n");
    printf("\t  Welcome, stranger. hehehe\n");
    printf("\t    What're ya buyin' ?\n");
    
    printf("\nYour coins : %.2f\n", *coin);
    printf("\n1. Red potion (+20 Life Points) #%d coins\n", *potion1);
    printf("2. Blue potion (+20 Attack Points) #%d coins\n", *potion2);
    printf("3. Gold potion (+30 All stats) #%d coins\n", *potion3);
    printf("4. Green potion (reset movement cost & fire damage) #%d coins\n", *potion4);
    printf("5. !! (!!) #%d coins\n", *potion5);
    printf(">> ");
    scanf("%d", &choice);
    getchar();

    switch(choice){
        case 1:
            if(*coin >= *potion1){
                *coin -= *potion1;
                *playerLifePoints += 20;
                *potion1 += 5;
                printf("Good choice, stranger.");
                Sleep(1500);
            }else{
                printf("You need more money, stranger.");
                Sleep(1500);
            }
            break;
        case 2:
            if(*coin >= *potion2){
                *coin -= *potion2;
                *playerAttack += 20;
                *potion2 += 5;
                printf("Hehehe, I knew I could count on you.");
                Sleep(1500);
            }else{
                printf("You need more money, stranger.");
                Sleep(1500);
            }
            break;
        case 3:
            if(*coin >= *potion3){
                *coin -= *potion3;
                *playerAttack += 30;
                *playerLifePoints += 30;
                *potion3 += 5;
                printf("Give that the care it deserves, mate.");
                Sleep(1500);
            }else{
                printf("You need more money, stranger.");
                Sleep(1500);
            }
            break;
        case 5:
            if(*coin >= *potion5){
                *coin -= *potion5;
                *playerAttack += 1000;
                *playerLifePoints += 1000;
                *potion5 += 500;
                printf("Crossin your T's, dottin your I's. That's the way to be.\n");
                Sleep(1500);
            }else{
                printf("You need more money, stranger.");
                Sleep(1500);
            }
			break;
        case 4:
        	if(*coin >= *potion4){
        		*coin -= *potion4;
        		PLAYER_MOVEMENT_COST = 10;
        		FIRE_DAMAGE = 10;
        		*potion4 += 5;
        		printf("Good stuff, stranger.");
        		Sleep(1500);
			}else{
				printf("You need more money, stranger.");
                Sleep(1500);
			}
            break;
        default:
            printf("Invalid choice.");
    }

    printf("\nCome back anytime.\n");
    Sleep(1500);
}


void opening(char op[100]){
    printf("\033[1;33m                           *           *  *********** ************   *          *  **********            \033[0m \n"); 
	printf("\033[1;33m                          * *       * *      *       *              *          *       *                  \033[0m \n");
	printf("\033[1;33m                         *   *   *   *      *       *************  ************       *                   \033[0m \n"); 
	printf("\033[1;33m                        *     *     *      *       *           *  *          *       *                    \033[0m \n");
	printf("\033[1;33m                       *           *  *********** *************  *          *       *                     \033[0m \n");
	
	printf("\033[1;31m                 *********     **********        ***       ************  ************  **     *\033[0m \n"); 
	printf("\033[1;31m                *        *    *         *      *    *     *             *          *  * *    *    \033[0m \n");
	printf("\033[1;31m               *         *   ***********     ********    ************  *          *  *  *   *     \033[0m \n"); 
	printf("\033[1;31m              *        *    *         *     *       *   *          *  *          *  *   *  *      \033[0m \n");
	printf("\033[1;31m             ********      *           *   *        *  ************  ************  *     **       \033[0m\n");
	puts("");
	printf("        --------------------------------press enter to continue-------------------------------\n");
	scanf("%[^\n]",op);
	getchar();
}

// Main function
int main() {
	int round = INITIAL_ROUND;
    int n = INITIAL_N;
    int level = 0;
    char opt;
    
    int day[100];
    char month[100][100];
    int year[100];
    int sumround[100];
    char user[100][100];
	FILE* fp;
	// Opening
	char op[100];
    opening(op);
    system("cls");	
    	
    // Account authentication
    accountAuthentication(fp);
    system("cls");
    char temp[50];
    strcpy(temp,name);
	strcat(temp,".txt");
    fp=fopen(temp,"r");
	if(fp!=NULL){
		fscanf(fp,"%d %d %d %f %d %d %d %d %d %d %d",&INITIAL_PLAYER_LIFE_POINTS,&PLAYER_ATTACK, &INITIAL_DRAGON_LIFE_POINTS ,&PLAYER_COIN, &INITIAL_POTION1_PRICE, &INITIAL_POTION2_PRICE, &INITIAL_POTION3_PRICE, &INITIAL_POTION4_PRICE, &INITIAL_POTION5_PRICE, &INITIAL_ROUND, &INITIAL_N);
	}
	else{	
		fclose(fp);
    	fp=fopen(name,"w");
	}
	fclose(fp);

  
    
    
    // Declare the game field
    char field[100][100];

    // Seed the random number generator
    srand(time(NULL));

    // Declare variables for player, dragon, and fire positions
    int playerX, playerY, dragonX, dragonY, fireX, fireY;

    // Initialize the game field and positions
    initializeField(field, n, &playerX, &playerY, &dragonX, &dragonY, &fireX, &fireY);
    
	// Struct to declare ingame stats data type;
	struct gameStats{
		int playerLifePoints;
		int dragonLifePoints;
		int playerDamage;
		int fireDamage;
		int playerMovementCost;
		int playerLevel;
		float playerCoin;
	};
	struct gameStats amount;
	
    // Initialize player and dragon lifepoints
    amount.playerLifePoints = INITIAL_PLAYER_LIFE_POINTS;
    amount.dragonLifePoints = INITIAL_DRAGON_LIFE_POINTS;
    amount.playerCoin = PLAYER_COIN;
    
    // Display the initial game field
    printField(field, n, amount.playerLifePoints, amount.dragonLifePoints, amount.playerCoin, round);

    // Game loop
    char move;
    while (1) {
    	
        // Check if a key is pressed
        if (_kbhit()) {
            // Get the pressed key
            move = _getch();

            // Handle player movement
            handlePlayerMovement(field, n, &playerX, &playerY, move, &amount.playerLifePoints);

            // Handle interactions between player, dragon, and fire
            handleInteractions(field, &n, &playerX, &playerY, &dragonX, &dragonY, &fireX, &fireY, &amount.playerLifePoints, &amount.dragonLifePoints, &amount.playerCoin, &round);

            // Clear the console screen
            system("cls");

            // Display the updated game field
            printField(field, n, amount.playerLifePoints, amount.dragonLifePoints, amount.playerCoin, round);

            // Check if player has run out of lifepoints
            if (amount.playerLifePoints <= 0){
            	fp=fopen(temp,"w");
    				fprintf(fp,"%d %d %d %.2f %d %d %d %d %d %d %d %d", INITIAL_PLAYER_LIFE_POINTS, PLAYER_ATTACK, INITIAL_DRAGON_LIFE_POINTS, amount.playerCoin, INITIAL_POTION1_PRICE, INITIAL_POTION2_PRICE, INITIAL_POTION3_PRICE, INITIAL_POTION4_PRICE, INITIAL_POTION5_PRICE, INITIAL_ROUND, INITIAL_N,PLAYER_MOVEMENT_COST);
    				fclose(fp);
    			fp=fopen(temp,"r");
    				fscanf(fp,"%d %d %d %f %d %d %d %d %d %d %d %d",&INITIAL_PLAYER_LIFE_POINTS,&PLAYER_ATTACK, &INITIAL_DRAGON_LIFE_POINTS, &PLAYER_COIN, &INITIAL_POTION1_PRICE, &INITIAL_POTION2_PRICE, &INITIAL_POTION3_PRICE, &INITIAL_POTION4_PRICE, &INITIAL_POTION5_PRICE, &INITIAL_ROUND, &INITIAL_N,&PLAYER_MOVEMENT_COST);
    				fclose(fp);
                printf("Game over! Player has run out of lifepoints.\n");
                Sleep(2500);
                
                printf("Saving.");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf("\nData saved Succesfully.\n");
 	   			printf("Do you wish to continue ?\n");
    			printf("==================================\n");
    			printf("1. Continue\n2. Shop\n3. Scoreboard\n4. Exit\n");
    			retry:
    			printf(">> ");
    			scanf("%c", &opt); 
    			getchar();
    			//fflush fungsi utamanya untuk apa ?
    			//dengan fflush, do you wish to continue tidak akan loop2x.
    			fflush(stdin);
    			if(opt == '3'){
    				int count = 0;
    				fp=fopen("scoreboard.txt", "a");
					if(fp==NULL){
						fclose(fp);
						fp=fopen("scoreboard.txt", "w");
					}
						fprintf(fp,"%s %s %d\n",name, __DATE__, round);
    				fclose(fp);
    				
    				fp=fopen("scoreboard.txt", "r");
    				
					int i = 0;
					int tempDay;
					char tempMonth[50];
					int tempYear;
					int tempsumround;
					char tempName[100];
					 while(fscanf(fp, "%s %s %d %d %d",tempName, tempMonth, &tempDay, &tempYear, &tempsumround) != EOF){
					 	day[i] = tempDay;
					 	strcpy(month[i], tempMonth);
					 	year[i] = tempYear;
					 	sumround[i] = tempsumround;
					 	strcpy(user[i],tempName);
					 	i++;
    				}
    				fclose(fp);
    				
    				bubblesort(user,day,month,year,sumround,i);
    				
					int k;
					for(k = 0; k < i; k++){
						printf("%s %s %d %d %d\n", user[k],month[k], day[k], year[k], sumround[k]);
					}
					printf("\nExiting the game.");
    					Sleep(500);
    					printf(".");
    					Sleep(500);
    					printf(".\n");
    					Sleep(500);
    					exit(0);
    					
				}else if(opt == '1'){
					resetGame(field, &n, &playerX, &playerY, &dragonX, &dragonY, &fireX, &fireY, &amount.playerLifePoints, &amount.dragonLifePoints, &round);
					system("cls");
    				printField(field, n, amount.playerLifePoints, amount.dragonLifePoints, amount.playerCoin, round);
					continue;
				}else if(opt == '2'){
					system("cls");
					shop(&INITIAL_PLAYER_LIFE_POINTS, &PLAYER_ATTACK, &PLAYER_COIN, &INITIAL_POTION1_PRICE, &INITIAL_POTION2_PRICE, &INITIAL_POTION3_PRICE, &INITIAL_POTION4_PRICE, &INITIAL_POTION5_PRICE);
					amount.playerCoin = PLAYER_COIN;
					resetGame(field, &n, &playerX, &playerY, &dragonX, &dragonY, &fireX, &fireY, &amount.playerLifePoints, &amount.dragonLifePoints, &round);
					system("cls");	
					printField(field, n, amount.playerLifePoints, amount.dragonLifePoints, amount.playerCoin, round);
					continue;	
				}
				else if(opt == '4'){
					fp=fopen("scoreboard.txt", "a");
					if(fp==NULL){
						fp=fopen("scoreboard.txt", "w");
					}
						fprintf(fp,"%s %s %d\n",name,  __DATE__, round);
						fclose(fp);
						printf("Exiting the game.");
    					Sleep(500);
    					printf(".");
    					Sleep(500);
    					printf(".");
    					Sleep(500);
    					printf("\n");
    					exit(0);
				}
				else{
					goto retry;
				}
			}                       
        }
    }
    
    	
    return 0;
}


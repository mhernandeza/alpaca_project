#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int AL_DetermineHealth(int Health);
int AL_EncounterStorm(int Health);

int main(void){
  int health,dummy_yes;
  srand(time(NULL));
  health=0;
  health=AL_DetermineHealth(health);
  printf("You start with %d Percent health\n",health);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\n\nCAPTAIN: 'ARE YE READY FO' MORE ACTION LADS?'\n");
  while(health>0){
    printf("\nPress '1' for yes, any other number for 'no'.\n");
    scanf("%d",&dummy_yes);
    if(dummy_yes==1){
      printf("CAPTAIN: 'ARGHHH!!'\n\n\n");
      health=AL_EncounterStorm(health);
    }
    else{
      printf("CAPTAIN: 'WELL WE'RE GOIN' ANYWAY!'\n");
      health=AL_EncounterStorm(health);
    }
  }
  return 0;
}

int AL_DetermineHealth(int Health){
  char HealthSelect;
  do{
    printf("\nWould you like to start with:\n\n");
    printf("A: 100 Percent health.\n");
    printf("B: Specific health.\n");
    printf("C: Random health.\n");
  }while((scanf("%c",&HealthSelect))!=1);

  HealthSelect=toupper(HealthSelect);

  switch(HealthSelect){
    case 'A':
    Health=100;
    break;

    case 'B':
    do{
      printf("Please input one number between 1 and 100:\n\n");
    } while(((scanf("%d",&Health))!=1)||(Health>100)||(Health<0));
    break;

    case 'C':
    do{
      Health=rand()%100;
    }while (Health<20);
    break;

    default:
    printf("You chose a wrong input.\n\n");
    Health=0;
  }
  if(Health==0){
    exit(1);
  }
  else{
    return Health;
  }
}

int AL_EncounterStorm(int Health){
  int WeatherCondition,LoseHealth;
  WeatherCondition=rand()%100;
  if ((WeatherCondition>=0) && (WeatherCondition<=25)){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Weather Condition is %d Percent extreme.\n",WeatherCondition);
    printf("CAPTAIN: 'AAAAH~! What a bootyfulday.'\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
  if ((WeatherCondition>=26) && (WeatherCondition<=50)){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Weather Condition is %d Percent extreme.\n",WeatherCondition);
    printf("CAPTAIN: 'BIT CLOUDY THER'LADS.'\n");
    LoseHealth=rand()%10;
    Health=Health-LoseHealth;
    printf("Your ship lost %d health\n",LoseHealth);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
  if ((WeatherCondition>=51) && (WeatherCondition<=75)){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Weather Condition is %d Percent extreme.\n",WeatherCondition);
    printf("CAPTAIN: 'DON WORRY MEN! 'TS BUT SOME RAIN!''\n");
    LoseHealth=rand()%30;
    Health=Health-LoseHealth;
    printf("Your ship lost %d health\n",LoseHealth);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
  if ((WeatherCondition>=76) && (WeatherCondition<=100)){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Weather Condition is %d Percent extreme.\n",WeatherCondition);
    printf("CAPTAIN: 'GON' GET ROUGH BOYS.'\n");
    LoseHealth=rand()%50;
    Health=Health-LoseHealth;
    printf("Your ship lost %d health\n",LoseHealth);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
  if(Health<=0){
    Health=0;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Your health is now %d\n",Health);
    printf("Your ship is sinking...\n");
    printf("CAPTAIN: 'WE DIE WITH HONOR LADS'\n'");
    printf("CAPTAIN: 'Unless you can swim...'\n");
    printf("CAPTAIN: 'Bloop'\n");
    printf("~~~~~~~~~~~~~~~GAME OVER~~~~~~~~~~~~~~\n\n");
  }
  else{
    printf("Your health is now %d\n",Health);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\nCAPTAIN: 'ARE YE READY FO' MORE ACTION LADS?'\n");
  }
  return Health;
}

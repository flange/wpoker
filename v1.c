#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_DICE 36
#define MAX_VAL 6
#define REPS 1000000


int *stats;
int results[MAX_VAL] = {0};


int roll_die()
{
  return (lrand48() % MAX_VAL) + 1;
}

void roll_dice(int num_dice)
{
  for (int i = 0; i < num_dice; i++)
    results[roll_die() - 1]++;

  return;
}

void add_wildcards()
{
  int wildcards = results[MAX_VAL - 1];

  for (int i = 0; i < (MAX_VAL - 1); i++)
    results[i] += wildcards;

  return;
}

int max_duplicates()
{
  int max_val = -1;

  for (int i = 0; i < (MAX_VAL - 1); i++) {
    if (results[i] > max_val)
      max_val = results[i];
  }

  return max_val;
}

void update_stats(int max_dups)
{
  stats[max_dups - 1]++;

  return;
}

void reset_array(int *arr, int len)
{
  memset(arr, 0, len * sizeof(int));

  return;
}

void print_results()
{
  for (int i = 0; i < MAX_VAL; i++)
    printf("%d ", results[i]);

  printf("\n");

  return;
}

void print_arr(int *arr, int len)
{
  for (int i = 0; i < len; i++)
    printf("%d ", arr[i]);

  printf("\n");
}

void print_stats(int num_dice)
{
  double val;

  printf("%2d: ", num_dice);

  for (int i = 0; i < num_dice; i++) {
    val = ((double) stats[i] / (double) REPS) * 100;

    if (val < 0.1)
      printf("    %s   ", "-");
    else
      printf("%5.1f%%\t", val);
  }

  printf("\n");

  return;
}

int main(void)
{
  srand48(time(NULL));

  for (int j = NUM_DICE; j > 0; j--) {

    stats = calloc(j, sizeof(int));

    for (int i = 0; i < REPS; i++) {
      roll_dice(j);
      add_wildcards();
      update_stats(max_duplicates());
      reset_array(results, MAX_VAL);
    }

    print_stats(j);
    free(stats);
  }

  return 0;
}

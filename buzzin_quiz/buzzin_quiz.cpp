#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INTERVAL 300
#define QUESTION_STRING_LENGTH 1000000

typedef struct {
    char q[QUESTION_STRING_LENGTH];
    char choises[3][100];
    int answer;
} QUIZ;

QUIZ quizzes[] = {
    {
        "“ú–{‚Å‚Q”Ô–Ú‚É‚‚¢ŽR‚ÍH\n",
        {
            "•xŽmŽR\n",
            "–kŠx\n",
            "–k•ä‚Šx\n"
        },
        0
    }
};

int current_read_point;

bool Read()
{
    current_read_point += 2;
    
    if (current_read_point >= strlen(quizzes[0].q))
    {
        return true;
    }

    system("cls");
    char buf[QUESTION_STRING_LENGTH];
    strncpy_s(buf, quizzes[0].q, current_read_point);
    printf(buf);
    return false;
}

void Init()
{
}

int main()
{
    current_read_point = 0;
    Init();
    time_t last_clock = clock();

    while (true)
    {
        time_t new_clock = clock();

        if (new_clock > last_clock + INTERVAL)
        {
            if (Read())
            {
                break;
            }

            last_clock = new_clock;
        }
    }
}

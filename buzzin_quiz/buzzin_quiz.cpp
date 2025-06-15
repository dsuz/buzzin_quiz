#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INTERVAL 50	//300	// 問読みの速さ（小さいほど速い）
#define QUESTION_STRING_LENGTH 10000
#define QUIZ_COUNT 3	// クイズを何問出すか

typedef struct {
	char q[QUESTION_STRING_LENGTH];
	char choises[3][100];
	int answer;
} QUIZ;

QUIZ quizzes[] = {
	{
		"日本で２番目に高い山は？\n",
		{
			"富士山\n",
			"北岳\n",
			"北穂高岳\n"
		},
		0
	},
	{
		"火を神聖視することから「拝火教」とも呼ばれる、古代ペルシアを起源とする宗教は何でしょう？\n",
		{
			"ゾロアスター教\n",
			"マニ教\n",
			"シク教\n"
		},
		0
	},
	{
		"「なぜ山に登るのか？」と聞かれて「そこに山があるから」と答えた逸話で知られるイギリスの登山家は誰でしょう？\n",
		{
			"ジョージ・マロリー\n",
			"ジョージ・マロニー\n",
			"ジョージ・カロリー\n"
		},
		0
	},
	{
		"タバコ、ジャガイモ、トマトはいずれも何科の植物でしょう？\n",
		{
			"ナス科\n",
			"キク科\n",
			"ユリ科\n"
		},
		0
	}
};

int current_read_point;

void ShuffleAnswers()
{

}

void ShuffleQuizzes()
{
	int cnt = sizeof(quizzes) / sizeof(QUIZ);

	for (int i = 0; i < cnt; i++)
	{
		int t = rand() % cnt;
		QUIZ tmp = quizzes[i];
		quizzes[i] = quizzes[t];
		quizzes[t] = tmp;
	}
}

bool Read(int num)
{
	current_read_point += 2;

	if (current_read_point >= strlen(quizzes[num].q))
	{
		return true;
	}

	system("cls");
	char buf[QUESTION_STRING_LENGTH];
	strncpy_s(buf, quizzes[num].q, current_read_point);
	printf(buf);
	return false;
}

void ReadQuiz(int num)
{
	current_read_point = 0;
	time_t last_clock = clock();

	while (true)
	{
		time_t new_clock = clock();

		if (new_clock > last_clock + INTERVAL)
		{
			if (Read(num))
			{
				break;
			}

			last_clock = new_clock;
		}
	}	// 問読み
}

void Init()
{
	ShuffleQuizzes();
	ShuffleAnswers();
}

int main()
{
	srand((unsigned int)time(NULL));
	Init();


	for (int i = 0; i < QUIZ_COUNT; i++)
	{
		ReadQuiz(i);
	}
}

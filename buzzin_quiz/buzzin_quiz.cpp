#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INTERVAL 50	//300	// ��ǂ݂̑����i�������قǑ����j
#define QUESTION_STRING_LENGTH 10000
#define QUIZ_COUNT 3	// �N�C�Y������o����

typedef struct {
	char q[QUESTION_STRING_LENGTH];
	char choises[3][100];
	int answer;
} QUIZ;

QUIZ quizzes[] = {
	{
		"���{�łQ�Ԗڂɍ����R�́H\n",
		{
			"�x�m�R\n",
			"�k�x\n",
			"�k�䍂�x\n"
		},
		0
	},
	{
		"�΂�_�������邱�Ƃ���u�q�΋��v�Ƃ��Ă΂��A�Ñ�y���V�A���N���Ƃ���@���͉��ł��傤�H\n",
		{
			"�]���A�X�^�[��\n",
			"�}�j��\n",
			"�V�N��\n"
		},
		0
	},
	{
		"�u�Ȃ��R�ɓo��̂��H�v�ƕ�����āu�����ɎR�����邩��v�Ɠ�������b�Œm����C�M���X�̓o�R�Ƃ͒N�ł��傤�H\n",
		{
			"�W���[�W�E�}�����[\n",
			"�W���[�W�E�}���j�[\n",
			"�W���[�W�E�J�����[\n"
		},
		0
	},
	{
		"�^�o�R�A�W���K�C���A�g�}�g�͂���������Ȃ̐A���ł��傤�H\n",
		{
			"�i�X��\n",
			"�L�N��\n",
			"������\n"
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
	}	// ��ǂ�
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

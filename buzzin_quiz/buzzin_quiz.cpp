#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define INTERVAL 120 // 50	//300	// 問読みの速さ（小さいほど速い）
#define QUESTION_STRING_LENGTH 10000	// 問題文の長さ
#define CHOISE_LENGTH 100	// 選択肢の長さ
#define QUIZ_COUNT 10	// クイズを何問出すか
#define CHOISE_COUNT 3	// 三択
#define BEEP printf("\a");

typedef struct {
	char q[QUESTION_STRING_LENGTH];
	char choises[CHOISE_COUNT][CHOISE_LENGTH];
	int answer;
} QUIZ;

QUIZ quizzes[] = {
	{
		"歌山県に存在する、本州最南端の岬は何でしょう？\n",
		{
			"潮岬\n",
			"佐多岬\n",
			"宗谷岬\n"
		},
		0
	},	{
		"サッカー日本代表が、1998年のフランスW杯への出場を決めた試合のことを、試合の会場となったマレーシアの都市から「何の歓喜」というでしょう？\n",
		{
			"ジョホールバルの歓喜\n",
			"ドーハの歓喜\n",
			"ミラノの歓喜\n"
		},
		0
	},
	{
		"元々は氷を運ぶためのカバンだったことから、「運ぶ」を意味するアメリカの俗語が名前の由来となったのは何でしょう？\n",
		{
			"トートバッグ\n",
			"サコッシュ\n",
			"クラッチバッグ\n"
		},
		0
	},
	{
		"アメリカの州の中で、日本より面積が大きいのは、アラスカ州、テキサス州、カリフォルニア州とどこでしょう？\n",
		{
			"モンタナ州\n",
			"ニューヨーク州\n",
			"ワシントン州\n"
		},
		0
	},
	{
		"「勤勉・倹約」の精神を課したギリシャの都市国家の名前に由来する、非常に厳しい教育のことを指す言葉は何でしょう？\n",
		{
			"スパルタ\n",
			"アテネ\n",
			"アルゴス\n"
		},
		0
	},
	{
		"本来は「イノシシを追うための小屋」という意味である、単語の意味を推測するテーブルゲームは何でしょう？\n",
		{
			"たほいや\n",
			"はぁって言うゲーム\n",
			"へんなかんじ\n"
		},
		0
	},
	{
		"漢数字の「百」から「一」を引くということから、99歳のお祝いのことを何というでしょう？\n",
		{
			"白寿\n",
			"米寿\n",
			"喜寿\n"
		},
		0
	},
	{
		"コンビニチェーン店の「セブンイレブン」のロゴの中で、唯一小文字であるアルファベットは何でしょう？\n",
		{
			"n\n",
			"e\n",
			"v\n"
		},
		0
	},
	{
		"6、28、496のように、その数以外の約数の和がその数と等しくなる数のことを何というでしょう？\n",
		{
			"完全数\n",
			"素数\n",
			"フィボナッチ数\n"
		},
		0
	},
	{
		"追いつ追われつの試合のことを、ある遊具の名前を使って何というでしょう？\n",
		{
			"シーソーゲーム\n",
			"クロスゲーム\n",
			"ブランコゲーム\n"
		},
		0
	},
	{
		"ブダペストはハンガリーの首都ですが、ブカレストはどこの首都でしょう？\n",
		{
			"ルーマニア\n",
			"ハンガリー\n",
			"オーストリア\n"
		},
		0
	},
	{
		"日本で２番目に高い山は？\n",
		{
			"富士山\n",
			"北岳\n",
			"北穂高岳\n"
		},
		1
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
int quiz_count;	// 登録されたクイズの問題数
int total_score;

void PrintHeader(int num_of_quiz)
{
	system("cls");
	printf("=================================================\n");
	printf("=== 得点: %06d 点 ===== 第 %02d 問 / 全 %02d 問 ===\n", total_score, num_of_quiz + 1, QUIZ_COUNT);
	printf("=================================================\n");
}

int GetScore(int num)
{
	int len = strlen(quizzes[num].q) + 1;
	return 10 + (len - current_read_point) * 100 / len;
}

void ShowChoises(int num)
{
	for (int i = 0; i < CHOISE_COUNT; i++)
	{
		printf("%d. ", i + 1);
		printf(quizzes[num].choises[i]);
	}
}

// 選択肢をシャッフルする
void ShuffleAnswers()
{
	for (int i = 0; i < quiz_count; i++)
	{
		for (int j = 0; j < CHOISE_COUNT; j++)
		{
			int t = rand() % CHOISE_COUNT;
			char tmp[CHOISE_LENGTH];
			strcpy_s(tmp, quizzes[i].choises[j]);
			strcpy_s(quizzes[i].choises[j], quizzes[i].choises[t]);
			strcpy_s(quizzes[i].choises[t], tmp);

			// 正解を更新する
			if (quizzes[i].answer == j)
				quizzes[i].answer = t;
			else if (quizzes[i].answer == t)
				quizzes[i].answer = j;
		}
	}
}

// 問題をシャッフルする
void ShuffleQuizzes()
{
	for (int i = 0; i < quiz_count; i++)
	{
		int t = rand() % quiz_count;
		QUIZ tmp = quizzes[i];
		quizzes[i] = quizzes[t];
		quizzes[t] = tmp;
	}
}

// 文字をスクロールさせる
// 引数 num: 問題の番号
bool Read(int num)
{
	current_read_point += 2;

	if (current_read_point >= strlen(quizzes[num].q))
	{
		printf("\n");
		return true;
	}

	PrintHeader(num);
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

		if (GetKeyState(VK_SPACE) & 0x8000)
			break;
	}	// 問読み
}

void Init()
{
	total_score = 0;
	quiz_count = sizeof(quizzes) / sizeof(QUIZ);
	ShuffleQuizzes();
	ShuffleAnswers();
}

int main()
{
start:
	srand((unsigned int)time(NULL));
	Init();

	for (int i = 0; i < QUIZ_COUNT; i++)
	{
		PrintHeader(i);
		printf("問題\n");
		Sleep(2000);
		ReadQuiz(i);
		printf("\n");	// 問題と選択肢の間を一行開ける
		ShowChoises(i);
		printf("\n");	// 選択肢と回答の間を一行開ける

		int answer;

		while (1)
		{
			if (GetKeyState('1') & 0x8000)
			{
				answer = 0;
				break;
			}
			else if (GetKeyState('2') & 0x8000)
			{
				answer = 1;
				break;
			}
			else if (GetKeyState('3') & 0x8000)
			{
				answer = 2;
				break;
			}
		}

		printf("回答: %d.\n", answer + 1);

		// 正誤判定
		if (answer == quizzes[i].answer)
		{
			int score = GetScore(i);
			printf("正解! %d 点 獲得\n", score);
			total_score += score;
			BEEP
		}
		else
		{
			printf("不正解\n");
		}

		printf("\n");
		printf("ENTER を押すと次に進みます\n");

		while (1)
			if (GetKeyState(VK_RETURN) & 0x8000)
				break;
	}

	printf("\n");
	printf("ゲーム終了。得点: %d\n", total_score);
	printf("もう一度 挑戦しますか？(y/n)\n");
	printf("\n");

	while (1)
	{
		if (GetKeyState('Y') & 0x8000)
		{
			goto start;
		}
		else if (GetKeyState('N') & 0x8000)
		{
			break;
		}
	}
}

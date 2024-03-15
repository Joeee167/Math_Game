#include<iostream>
using namespace std;

enum enQuestionsDifficulty { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixType = 5 };

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return"+";
	case enOperationType::Sub:
		return"-";
	case enOperationType::Mult:
		return"x";
	case enOperationType::Div:
		return"/";
	default:
		return"Mix";
	}
}
string GetQuestionLevelText(enQuestionsDifficulty QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Mid","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

short RandomNumber(short From, short To)
{
	short RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

short ReadNumberOfQuestions()
{
	short NumberOfQuestions;

	cout << "How many number of questions do you want to answer?";
	cin >> NumberOfQuestions;

	return NumberOfQuestions;
}
enQuestionsDifficulty DifficultyLevel()
{
	short DifficultyLevel;

	cout << "Enter Question Level [1]:Easy , [2]:Mid , [3]:Hard , [4]:Mix?";
	cin >> DifficultyLevel;

	return (enQuestionsDifficulty)DifficultyLevel;
}
enOperationType OperationType()
{
	short OperationType;

	cout << "Enter the operation type [1]:Add , [2]:Sub , [3]:Mult , [4]:Div , [5]:Mix?";
	cin >> OperationType;

	return (enOperationType)OperationType;
}

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsDifficulty QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsDifficulty QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};


int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;

	case enOperationType::Sub:
		return Number1 - Number2;

	case enOperationType::Mult:
		return Number1 * Number2;

	case enOperationType::Div:
		return Number1 / Number2;

	default:
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionsDifficulty QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsDifficulty::Mix)
	{
		QuestionLevel = (enQuestionsDifficulty)RandomNumber(1, 3);  // Get random difficlty for each question by function that gets random number in specified range
	}

	if (OpType == enOperationType::MixType)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)  // If it is initiall mix , it is set to [easy or mid or hard] in the first if condition
	{
	case enQuestionsDifficulty::Easy:

		// If difficulty is easy , get two random numbers from 1 to 10
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);  // Get the correct answer for the question

		Question.QuestionLevel = QuestionLevel;

		return Question;  // Question Info are saved in struct to be used again

	case enQuestionsDifficulty::Mid:
		// If difficulty is mid , get two random numbers from 10 to 50

		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionsDifficulty::Hard:
		// If difficulty is hard , get two random numbers from 50 to 100

		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);  // Generate questions according to difficulty level and op.type entered by the user
	}
}


int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_________" << endl;
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	// Checking the user answer and set screen color according to the answer

	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Worng Answer :-( \n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;  // show correct answer if the user's answer is wrong
		cout << "\n";
	}

	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;  // flag used in set scrren color function to determine screen color
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";
	}

	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);  // set screen to green in case of correct answer and red if it is false
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);  // boolean variable to check if right answers is more than wrong answers
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return"PASS :-)";
	else
		return"Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "______________________________\n\n";

	cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n______________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";
}


void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadNumberOfQuestions();  // Ask User for no.of questions
	Quizz.QuestionsLevel = DifficultyLevel();			// Ask for difficulty level
	Quizz.OpType = OperationType();						// Ask for type of questions

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();  // Clear everything on screen
		PlayMathGame();

		cout << "\nDo you want to play again? Y/N";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
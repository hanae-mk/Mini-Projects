
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel {EasyLevel = 1 , MedLevel = 2 , HardLevel = 3 , Mix = 4};
enum enOperationType {Add = 1 , Sub = 2 , Mult = 3 , Div = 4 , MixOp = 5};

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+"; //problem li fat kan khsna daruri n3mlu break w hna la???
		  
	case enOperationType::Sub:
		return "-";

	case enOperationType::Mult:
		return "x";

	case enOperationType::Div:
		return "/";
		
	default:
		return "Mix";

	}
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy" , "Medium" , "Hard" , "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];

}

short RandomNumber(short From, short To)
{
	short RandomNum = rand() % (To - From + 1) + From;
	return RandomNum;

}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
		system("color 4F");
	cout << "\a";
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 0;

	do
	{
		cout << "How many questions do you want to answer ?\n";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;

}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter question level : [1] Easy , [2] Med , [3] Hard , [4] Mix \n";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;

}

enOperationType ReadOperationType()
{
	short OpType = 0;

	do
	{
		cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix \n";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;

}

struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	short PlayerAnswer = 0;
	short CorrectAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100]; 
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = false;

};

short SimpleCalculator(int Number1, int Number2, enOperationType OpType)
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
	return (enOperationType)RandomNumber(1, 4);
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;//randomly

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:

		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
		
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionsLevel::MedLevel:

		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
		
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionsLevel::HardLevel:

		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, OpType);
		
		Question.QuestionLevel = QuestionLevel;

		return Question;
	}

	return Question;

}

void GenerateQuizQuestions(stQuizz& Quizz) //Necessary to do & because you modify its info
{
	
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
		
	}
}

int ReadQuestionAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << endl;
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] : \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_______\n";
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "\nWrong Answer :-( \n";
		cout << "The right answer is : " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfWrongAnswers++;

		cout << "\nRight Answer :-)\n";

	}

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "FAIL :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "______________________________\n\n";

	cout << " Final Results is " << GetFinalResultsText(Quizz.IsPass);
	cout << "\n______________________________\n\n";

	cout << "Number of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;

	cout << "______________________________\n";

}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizQuestions(Quizz);
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
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again ? Y/N? \n";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

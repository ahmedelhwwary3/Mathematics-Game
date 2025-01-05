 

#include <iostream>
#include <string>
using namespace std;
enum enQuestionLevel{Easy=1,Medium=2,Hard=3,Mixed=4};
enum enOperationType{Add=1,Sub=2,Mul=3,Div=4,Mix=5};
enum enTestFinalResult{Pass=1,Fail=2};
struct stQuestion
{
    short QuestionNumber;
    short N1, N2;
    enQuestionLevel Level;
    enOperationType OT;
    string OTSympol;
    int Answer;
};
struct stGameResults
{
    enQuestionLevel Level;
    string LevelName;
    enOperationType OT;
    string OTName;
    short CorrectAnswers, WrongAnswers;
    enTestFinalResult TestResult;
    string TestResultName;
    short NumberOfQeustions;

};
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}
void ResetScreen()
{
    //clear and color is black
    system("cls");
    system("color 0F");
}
short ReadOperationsType()
{
    short Type;
    do
    {
        cout << "Enter Operation Type? [1]Add,[2]Sub,[3]Mul,[4]Div,[5]Mixed\n";
        cin >> Type;
        cout << endl;
    } while (Type > 5 || Type < 1);
    return Type;
}
enOperationType GetOperationsType(short ot)
{
    return (enOperationType)ot;
}
short ReadQuestionsLevel()
{
    short Level;
    do
    {
        cout << "Enter question level? [1]Easy,[2]Medium,[3]Hard,[4]Mixed\n";
        cin >> Level;
        cout << endl;
    } while (Level > 4 || Level < 1);
    return Level;
}
enQuestionLevel GetQuestionsLevel(short Level)
{
    return (enQuestionLevel)Level;
}
short ReadHowManyQuestions()
{
    short HowMany;
    do
    {
        cout << "How many questions do you want to answer?[1-10]\n";
        cin >> HowMany;
        cout << endl;
    } while (HowMany>10||HowMany<1);
    return HowMany;
}
string GetOperationsTypeName(stGameResults GameResults)
{
    string OT[5] = { "Add","Sub","Mul","Div","Mix" };
    return OT[GameResults.OT - 1];
}
string GetLevelName(stGameResults GameResults)
{
    string Level[4] = { "Easy","Medium","Hard","Mix" };
    return Level[GameResults.Level - 1];
}
string GetRandomOTSympol()
{
    string OT[4] = {"+","-","*","/"};
    return OT[RandomNumber(1, 4)-1];
}
string Tabs(int NumberOfTabs)
{
    string Tabs = "";
    for (int i = 1;i <= NumberOfTabs;i++)
    {
        Tabs += "\t";
        cout << Tabs;
    }
    return Tabs;
}
int DrawQuestionAndGetAnswer(stQuestion Question)
{
    int Answer;
    cout << Question.N1 << endl;
    cout << Question.N2 << Question.OTSympol << endl;
    cout << "-----------\n";
    cin >> Answer;
    return Answer;
}
float SimpleCalculator(stQuestion Question)
{
    switch (Question.OT)
    {
    case Add:
        return Question.N1 + Question.N2;
        break;
    case Sub:
        return Question.N1 - Question.N2;
        break;
    case Mul:
        return Question.N1 * Question.N2;
        break;
    case Div:
        return Question.N1 / Question.N2;
        break;
    }
}
void GetQuestionResult(stQuestion Question, stGameResults& GameResults)
{
    if (Question.Answer == SimpleCalculator(Question))
    {
        cout << endl;
        cout << "Right Answer :)\n";
        system("color 2F");
        GameResults.CorrectAnswers++;
    }
    else
    {
        cout << endl;
        cout << "Wrong Answer :(\n";
        system("color 4F");
        cout << "\a";
        GameResults.WrongAnswers++;
    }
}
stQuestion GenerateQuestion(enOperationType OT,enQuestionLevel Level)
{
    stQuestion Question;
    switch (OT)
    {
    case Add:
        Question.OT = Add;
        Question.OTSympol = "+";
        break;
    case Sub:
        Question.OT = Sub;
        Question.OTSympol = "-";
        break;
    case Mul:
        Question.OT = Mul;
        Question.OTSympol = "*";
        break;
    case Div:
        Question.OT = Div;
        Question.OTSympol = "/";
        break;
    case Mix:
        Question.OT = Mix;
        Question.OTSympol =GetRandomOTSympol();
        break;
    }
    switch (Level)
    {
    case Easy:
        Question.N1 = RandomNumber(1,10);
        Question.N2 = RandomNumber(1,10);
        break;
    case Medium:
        Question.N1 = RandomNumber(11,50);
        Question.N2 = RandomNumber(11,50);
        break;
    case Hard:
        Question.N1 = RandomNumber(51,100);
        Question.N2 = RandomNumber(51,100);
        break;
    case Mixed:
        Question.N1 = RandomNumber(1,100);
        Question.N2 = RandomNumber(1,100);
        break;
    }
    return Question;
}
void CheckTestResult(stGameResults& GameResults)
{
    if (GameResults.CorrectAnswers >= GameResults.WrongAnswers)
    {
        GameResults.TestResult = enTestFinalResult::Pass;
        GameResults.TestResultName = "Pass";
    }
    else
    {
        GameResults.TestResult = enTestFinalResult::Fail;
        GameResults.TestResultName = "Fail";
    }
}
void DoTheQuizz(short QuestionsNumber,stQuestion Question,stGameResults& GameResults,enOperationType OT,enQuestionLevel Level)
{
    cout << "Question [" << Question.QuestionNumber << "/" << QuestionsNumber << "]\n";
    Question=GenerateQuestion(OT,Level);
    Question.Answer = DrawQuestionAndGetAnswer(Question);
    GetQuestionResult(Question,GameResults);
}
void ShowEndScreen(stGameResults GameResults)
{
    cout << "---------------------------------------------\n";
    cout << Tabs(1) << "Final Result is " << GameResults.TestResultName << endl;
    cout << "---------------------------------------------\n";
}
void SetScreenColor(stGameResults GameResults)
{
    if (GameResults.TestResult == enTestFinalResult::Pass)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}
void PrintTestResults(stGameResults GameResults)
{
    cout << "Number of Questions:" << GameResults.NumberOfQeustions << endl;
    cout << "Questions Level:" << GameResults.LevelName << endl;
    cout << "Operation Type:" << GameResults.OTName << endl;
    cout << "Number Of Right Answers:" << GameResults.CorrectAnswers << endl;
    cout << "Number Of Wrong Answers:" << GameResults.WrongAnswers << endl;
    cout << "---------------------------------------------\n";
}
void StartMathGame()
{
    char PlayAgain = 'y';
    enOperationType OT;
    enQuestionLevel QLevel;
    short HowManyQuestons;
    stQuestion Question;
    stGameResults GameResults;
    //initial values
    GameResults.CorrectAnswers = 0, GameResults.WrongAnswers = 0;
    do
    {
        ResetScreen();
        HowManyQuestons = ReadHowManyQuestions();
        GameResults.NumberOfQeustions = HowManyQuestons;
        QLevel = GetQuestionsLevel(ReadQuestionsLevel());
        OT = (GetOperationsType(ReadOperationsType()));
        GameResults.Level = QLevel;
        GameResults.OT = OT;
        GameResults.LevelName = GetLevelName(GameResults);
        GameResults.OTName = GetOperationsTypeName(GameResults);
        for (Question.QuestionNumber = 1;Question.QuestionNumber <= HowManyQuestons;Question.QuestionNumber++)
        {
            DoTheQuizz(HowManyQuestons,Question,GameResults,OT,QLevel);
        }
        CheckTestResult(GameResults);
        ShowEndScreen(GameResults);
        PrintTestResults(GameResults);
        SetScreenColor(GameResults);
        cout << "Do you want to play again? Y or N\n";
        cin >> PlayAgain;
    } while (PlayAgain=='y'||PlayAgain=='Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartMathGame();

}

 
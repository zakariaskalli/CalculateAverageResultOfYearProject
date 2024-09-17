

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsInputValidate.h"
#include<iomanip>

using namespace std;


const string BultaneFileName = "AverageResultOfYearData.txt";

struct stMatierData
{
    string NameMatier = "";
    int NumExamInMatier = 0;
    vector<float> NotesInExamInMatier = {};
    bool HaveAttentionInMatier = 0;
    float NoteAttention = 0;
    short PercentageAttention = 0;
    short NumCoefficientInMatier = 0;
    float AverageMatier = 0;
    float AverageMultiplyCoefficient = 0;
};

struct stBultaneTotals
{
    int TotalCoefficient = 0;
    float TotalAverageMultiplyCoefficient = 0;
};

vector <string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  // erase() until positon and move to next word. 
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

stMatierData ConvertLineToRecord(string Line, string Separator = "#//#")
{
    stMatierData MatierData;
    vector <string> vMatierData;

    vMatierData = SplitString(Line, Separator);

    MatierData.NameMatier = vMatierData[0];
    MatierData.NumExamInMatier = stoi(vMatierData[1]);

    MatierData.NotesInExamInMatier.resize(MatierData.NumExamInMatier);

    for (short i = 0; i < MatierData.NumExamInMatier; i++)
    {
        MatierData.NotesInExamInMatier[i] = stof(vMatierData[i + 2]);
    }

    short NumNow = MatierData.NumExamInMatier + 1;

    MatierData.HaveAttentionInMatier = stoi(vMatierData[++NumNow]);
    MatierData.NoteAttention = stof(vMatierData[++NumNow]);
    MatierData.PercentageAttention = stoi(vMatierData[++NumNow]);
    MatierData.NumCoefficientInMatier = stoi(vMatierData[++NumNow]);
    MatierData.AverageMatier = stof(vMatierData[++NumNow]);
    MatierData.AverageMultiplyCoefficient = stof(vMatierData[++NumNow]);


    return MatierData;
}

string ConvertRecordToLine(stMatierData Matier, string Separator = "#//#")
{
    string stMatierRecord = "";

    stMatierRecord += Matier.NameMatier + Separator;
    stMatierRecord += to_string(Matier.NumExamInMatier) + Separator;
    for (short i = 0; i < Matier.NumExamInMatier; i++)
    {
        stMatierRecord += to_string(Matier.NotesInExamInMatier.at(i)) + Separator;
    }
    stMatierRecord += to_string(Matier.HaveAttentionInMatier) + Separator;
    stMatierRecord += to_string(Matier.NoteAttention) + Separator;
    stMatierRecord += to_string(Matier.PercentageAttention) + Separator;
    stMatierRecord += to_string(Matier.NumCoefficientInMatier) + Separator;
    stMatierRecord += to_string(Matier.AverageMatier) + Separator;
    stMatierRecord += to_string(Matier.AverageMultiplyCoefficient);

    return stMatierRecord;
}

void AddDataToLineToFile(string FileName, string stDataLine)
{
    fstream MatierData;
    MatierData.open(FileName, ios::out | ios::app);

    if (MatierData.is_open())
    {
        MatierData << stDataLine << endl;

        MatierData.close();
    }

}

void DeleteDataFromFile()
{
    fstream MatierData;
    MatierData.open(BultaneFileName, ios::out);

    if (MatierData.is_open())
    {
        MatierData.close();
    }
}

vector <stMatierData> LoadMatiersDataFromFile(string FileName, stBultaneTotals& BultaneTotal)
{
    vector <stMatierData> vMatiers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stMatierData Matier;

        while (getline(MyFile, Line))
        {
            Matier = ConvertLineToRecord(Line);

            BultaneTotal.TotalCoefficient += Matier.NumCoefficientInMatier;
            BultaneTotal.TotalAverageMultiplyCoefficient += Matier.AverageMultiplyCoefficient;

            vMatiers.push_back(Matier);
        }

        MyFile.close();
    }
    return vMatiers;
}

string ReadString()
{
    string  S1 = "";
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, S1);
    return S1;
}

vector <float> ReadQuizNote(short NumQuizInMatier, string NameMatier)
{
    vector <float> NotesInExamInMatier;

    for (short i = 1; i <= NumQuizInMatier; i++)
    {
        cout << "Please Enter Note " + to_string(i) + " In " + NameMatier + " : ";
        NotesInExamInMatier.push_back(clsInputValidate<float>::ReadNumberBetween(0, 20, "Error, Please Enter Note " + to_string(i) + " In " + NameMatier + " : "));
        cout << "\n";

    }

    return NotesInExamInMatier;
}

bool ReadHaveAttention()
{
    char HaveAttention;

    cout << "You Have Attention? Y/N : ";
    cin >> HaveAttention;

    if (HaveAttention == 'Y' || HaveAttention == 'y')
    {
        return 1;
    }
    else
        return 0;

}

float CalculateAverageMatier(stMatierData MatierData)
{

    float AverageMatier = 0;

    for (int i = 0; i < MatierData.NumExamInMatier; i++)
    {
        AverageMatier += MatierData.NotesInExamInMatier[i];
    }

    AverageMatier /= MatierData.NumExamInMatier;

    if (MatierData.HaveAttentionInMatier)
        return (((AverageMatier / 100) * (100 - MatierData.PercentageAttention)) + ((MatierData.NoteAttention / 100) * MatierData.PercentageAttention));
    else
        return AverageMatier;

}

stMatierData ReturnMatierData()
{
    stMatierData MatierData;

    cout << "PLease Enter Name Matier: ";
    MatierData.NameMatier = ReadString();

    cout << "\n";

    cout << "PLease Enter Number Exam In " + MatierData.NameMatier + ": ";
    MatierData.NumExamInMatier = clsInputValidate<short>::ReadNumberBetween(1, 4, "Error, PLease Enter Number Exam In " + MatierData.NameMatier + ": ");

    cout << "\n";

    MatierData.NotesInExamInMatier = ReadQuizNote(MatierData.NumExamInMatier, MatierData.NameMatier);

    MatierData.HaveAttentionInMatier = ReadHaveAttention();

    cout << "\n";


    if (MatierData.HaveAttentionInMatier)
    {
        cout << "PLease Enter Note Attention In " + MatierData.NameMatier + ": ";
        MatierData.NoteAttention = clsInputValidate<float>::ReadNumberBetween(0, 20, "Error, PLease Enter Note Attention In " + MatierData.NameMatier + ": ");

        cout << "\n";

        cout << "PLease Enter Percentage Attention In " + MatierData.NameMatier + ": ";
        MatierData.PercentageAttention = clsInputValidate<short>::ReadNumberBetween(1, 100, "Error, PLease Enter Percentage Attention In " + MatierData.NameMatier + ": ");

        cout << "\n";
    }

    cout << "Please Enter Number Coefficient In " + MatierData.NameMatier + ": ";
    MatierData.NumCoefficientInMatier = clsInputValidate<short>::ReadNumber("Error, Please Enter Number Coefficient In " + MatierData.NameMatier + ": ");

    cout << "\n";

    MatierData.AverageMatier = CalculateAverageMatier(MatierData);

    MatierData.AverageMultiplyCoefficient = MatierData.NumCoefficientInMatier * MatierData.AverageMatier;

    return MatierData;

}

void PrintClientRecordLine(stMatierData MatierData)
{

    cout << " | " << left << setw(12) << MatierData.NameMatier;
    cout << " | " << left << setw(12) << MatierData.NumExamInMatier;
    short i = 0;
    for (i; i < MatierData.NumExamInMatier; i++)
    {
        cout << " | " << left << setw(7) << MatierData.NotesInExamInMatier.at(i);
    }
    if (i < 4)
    {
        for (i; i < 4; i++)
        {
            cout << " | " << left << setw(7) << " ";
        }
    }

    cout << " | " << left << setw(15) << MatierData.NoteAttention;
    cout << " | " << left << setw(12) << MatierData.PercentageAttention;
    cout << " | " << left << setw(15) << MatierData.NumCoefficientInMatier;
    cout << " | " << left << setw(15) << MatierData.AverageMatier;
    cout << " | " << left << setw(25) << MatierData.AverageMultiplyCoefficient;

}

void PrintResultOfYear()
{
    system("cls");

    stBultaneTotals BultaneTotal;

    vector <stMatierData> vMatiers = LoadMatiersDataFromFile(BultaneFileName, BultaneTotal);

    cout << "\n\t\t\t\t\t\t\t\t===========================================\n";
    cout << "\n\t\t\t\t\t\t\t\t\tBultane (Number Matier is : " << vMatiers.size() << ")" << "\n";
    cout << "\n\t\t\t\t\t\t\t\t===========================================\n\n\n";

    cout << "\n_______________________________________________________";
    cout << "_____________________________________________________________________________________________________________\n" << endl;

    cout << " | " << left << setw(12) << "Name Matier";
    cout << " | " << left << setw(12) << "Number Exam";
    cout << " | " << left << setw(7) << "Exam 1 ";
    cout << " | " << left << setw(7) << "Exam 2 ";
    cout << " | " << left << setw(7) << "Exam 3 ";
    cout << " | " << left << setw(7) << "Exam 4 ";
    cout << " | " << left << setw(15) << "Note Attention";
    cout << " | " << left << setw(12) << "Attention(%)";
    cout << " | " << left << setw(15) << "Num Coefficient";
    cout << " | " << left << setw(15) << "Average Matier";
    cout << " | " << left << setw(25) << "Average * Coefficient";
    cout << "\n_______________________________________________________";
    cout << "_____________________________________________________________________________________________________________\n" << endl;

    if (vMatiers.size() == 0)
        cout << "\t\t\t\t\t\t\t\tNo Matier Available In the System!";
    else
        for (stMatierData MatierData : vMatiers)
        {
            PrintClientRecordLine(MatierData);
            cout << endl;
        }
    cout << "\n____________________________________________________________________";
    cout << "________________________________________________________________________________________________\n\n";

    cout << "\t\t\t\t\t\t\t\t\t" << "Total Coefficient: " << BultaneTotal.TotalCoefficient << endl;
    cout << "\t\t\t\t\t\t\t\t\t" << "Total Aver *Coef : " << BultaneTotal.TotalAverageMultiplyCoefficient << endl;
    cout << "\t\t\t\t\t\t\t\t\t" << "AverageResult    : " << BultaneTotal.TotalAverageMultiplyCoefficient / BultaneTotal.TotalCoefficient << endl;


}

void EnterData()
{
    cout << "Please Enter Number Material: ";
    short NumMatier = clsInputValidate<short>::ReadNumberBetween(2, 30, "Error, Please Enter Number Material: ");

    DeleteDataFromFile();

    for (short i = 1; i <= NumMatier; i++)
    {
        system("cls");

        cout << "\n\t\t\t\t\t\t=================================\n";
        cout << "\t\t\t\t\t\t\tMaterial Num : " << i << "\n";
        cout << "\t\t\t\t\t\t=================================\n\n\n";

        stMatierData MatierData = ReturnMatierData();

        AddDataToLineToFile(BultaneFileName, ConvertRecordToLine(MatierData));

    }

}

void CalculateAverageResultOfYearProject()
{

    EnterData();

    PrintResultOfYear();

}



int main()
{
    CalculateAverageResultOfYearProject();
}

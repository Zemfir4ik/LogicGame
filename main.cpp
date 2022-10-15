#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

void game(vector<string> &tree);

int main()
{
    vector<string> tree;
    string path = "save.txt";

    ifstream file;
    file.open(path);

    if (file.is_open())
    {
        cout << "Сохранение загружено" << endl;
        cout << "_______________________________" << endl;

        int i = 0;

        while (!file.eof())
        {
            string temp;
            getline(file, temp);
            tree.push_back(temp);
            // cout << tree.at(i) << endl;
            i += 1;
        }
        file.close();

        char exit[5] = "2";
        while (atoi(exit) != 1)
        {
            game(tree);
            cout << "Хотите повторить?" << endl;
            cout << "1 - нет" << endl;
            cout << "любая другая цифра - да" << endl;
            cin >> exit;
            cout << "_______________________________" << endl;
        }

        ofstream outFile;
        outFile.open(path);
        for (int i = 0; i < tree.size(); ++i)
        {
            if (i != 0)
            {
                outFile << "\n" + tree.at(i);
            }
            else
            {
                outFile << tree.at(i);
            }           
        }
    }
    else
    {
        cout << "Ошибка открытия файла" << endl;
    }

    return 0;
}

void game(vector<string> &tree)
{
    vector<string>::iterator it = tree.begin();

    int j = 1;
    int deep = 1;

    while (true)
    {
        int prev = j;
        cout << tree.at(j) << endl;
        cout << "1 - да" << endl;
        cout << "2 - нет" << endl;

        int answer;
        cin >> answer;
        while (answer != 1 && answer != 2)
        {
            cout << "Введено неверное значение" << endl;
            cin >> answer;
        }

        if (answer == 1)
        {
            j *= 2;
            try
            {
                if (tree.at(j) == "")
                {
                    tree.at(-1);
                }
            }
            catch (std::out_of_range)
            {
                cout << "Ура, победа!" << endl;
                cout << "_______________________________" << endl;
                break;
            }
        }
        else
        {
            j = j * 2 + 1;
            try
            {
                if (tree.at(j) == "")
                {
                    tree.at(-1);
                }
            }
            catch (std::out_of_range)
            {
                string question;
                string animal;

                cout << "К сожалению, я не знаю, что это за животное(" << endl;
                cout << "Пожалуйста, введите вопрос при ответе 'да', на который, ответом будет ваше животное" << endl;

                cin.ignore();
                getline(cin, question);

                cout << "Пожалуйста, ввдеите животное, которое загадали" << endl;

                getline(cin, animal);

                try
                {
                    tree.at(j);
                }
                catch (std::out_of_range)
                {
                    for (int i = 0; i < deep * 2; ++i)
                    {
                        tree.push_back("");
                    }
                }

                string temp = tree.at(prev);
                tree.at(prev) = question;
                tree.at(j) = temp;
                tree.at(j - 1) = "Это " + animal + "?";
                cout << "_______________________________" << endl;

                break;
            }
        }
        cout << "_______________________________" << endl;
        deep *= 2;
    }
}

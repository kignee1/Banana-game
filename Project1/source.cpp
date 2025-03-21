#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "russian");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    const double e = 2.71828182845904523536;

    int day = 1;
    double maxBananaCost = 11.0;
    double minBananaCost = 1.1;
    int choiseM = 1;
    int choiseB = 1;
    double bLoos = 0.0;
    double rotChance = 1.5;
    double maxrobChance = 0;
    double robChance = 0;

    double m = 5000.0;
    double b = 5.0;

    // Èíèöèàëèçàöèÿ íà÷àëüíûõ çíà÷åíèé
    uniform_real_distribution<> bp_dis(1.0, 4.0);
    double bp = round(bp_dis(gen) * 100) / 100;  // Îêðóãëåíèå äî 2 çíàêîâ

    uniform_real_distribution<> l_dis(0.0, 1.0);
    double l = round(l_dis(gen) * 10) / 10;  // Îêðóãëåíèå äî 1 çíàêà

    double robincrease = 0.5 / (1 + pow(e, -((m / 200) * (bp / 200))));

    while (m > 0) {
        cout << fixed << setprecision(2);
        cout << "Äîáðîå óòðî ñýð. Ñåãîäíÿ âàø " << day
            << " äåíü â òîðãîâëå áàíàíàìè. Ó âàñ " << m
            << " äåíåã è " << b << " áàíàíîâ. Öåíû íà áèðæå áàíàíîâ ñåãîäíÿ "
            << bp << " Öåíà çà àðåíäó ñåãîäíÿ: " << l << ".\n";

        cout << "Âûáåðèòå ÷òî ìû ñåãîäíÿ áóäåì äåëàòü: Ïðîäàâàòü áàíàíû(1), Ïîêóïàòü áàíàíû(2), Íè÷åãî íå äåëàòü(3): ";
        string choise;
        cin >> choise;

        if (choise == "1") {
            cout << "Ïðîäàâàòü áàíàíû\n";
            cout << "Ñýð ñêîëüêî áàíàíîâ âû õîòèòå ïðîäàòü? ";
            cin >> choiseB;

            if (choiseB > b) {
                cout << "Ñýð ìíå ïðèäåòñÿ âûïîòðîøèòü âàñ :(((\n";
                break;
            }
            m = m - l + bp * choiseB;
            b -= choiseB;
        }
        else if (choise == "2") {
            cout << "Ïîêóïàòü áàíàíû\n";
            cout << "Ñýð ñêîëüêî áàíàíîâ âû õîòèòå êóïèòü? ";
            cin >> choiseM;

            if (choiseM > m) {
                cout << "Ñýð ìíå ïðèäåòñÿ âûïîòðîøèòü âàñ :(((\n";
                break;
            }
            b += choiseM;
            m = m - l - bp * choiseM;
        }
        else if (choise == "3") {
            cout << "Íè÷åãî íå äåëàòü\n";
            cout << "Cýð ìîæåòå îòïðàâèòüñÿ â äæàêóçè 3 ðàç çà äåíü äî ñëåäóþùåãî äíÿ\n";
            m -= l;
        }
        else {
            cout << "Ñýð ìíå ïðèäåòñÿ âûïîòðîøèòü âàñ :(((\n";
            break;
        }

        // Îáíîâëåíèå ýêîíîìèêè
        maxBananaCost += 0.013;
        minBananaCost += 0.0131;

        // Ðàñ÷åò øàíñà îãðàáëåíèÿ
        maxrobChance += dis(gen) * 0.033 - 0.015;
        maxrobChance += robincrease;
        uniform_real_distribution<> rob_dis(0.01, maxrobChance);
        robChance = rob_dis(gen);

        cout << "øàíñ ãðàáåæà: " << robChance << " ìàêñ øàíñ ãðàáåæà: " << maxrobChance << "\n";
        cout << "ïðèðîñò ãðàáåæà: " << robincrease << "\n";

        uniform_real_distribution<> chance_dis(0.0, 100.0);
        if (robChance > chance_dis(gen)) {
            double loss = round(((m / 4) + bp + l / 10) * 100) / 100;
            cout << "ÂÀÑ ÎÃÐÀÁÈËÈ ÍÀ " << loss << " ÄÅÍÅÃ!!!\n";
            m = round((m - loss) * 100) / 100;
            maxrobChance /= 1.8;
        }

        // Ìåõàíèêà ãíèåíèÿ
        if (rotChance > chance_dis(gen)) {
            uniform_real_distribution<> rot_dis(2.0, 10.0);
            bLoos = round(b / rot_dis(gen));
            b -= bLoos;
            cout << bLoos << " ÂÀØÈÕ ÁÀÍÀÍÎÂ ÑÃÍÈËÎ!!!\n";
            rotChance /= 2;
        }

        // Îáíîâëåíèå öåí
        uniform_real_distribution<> new_bp_dis(minBananaCost + 0.01, maxBananaCost);
        bp = round(new_bp_dis(gen) * 100) / 100;

        double l_max = bp + day / 4.0 + choiseM / (bp - minBananaCost + 1) + choiseB / (bp - minBananaCost + 1);
        uniform_real_distribution<> new_l_dis(0.0, l_max);
        l = round(new_l_dis(gen) * 10) / 10;

        day++;
    }

    return 0;
}

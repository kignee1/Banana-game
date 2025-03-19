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

    // ������������� ��������� ��������
    uniform_real_distribution<> bp_dis(1.0, 4.0);
    double bp = round(bp_dis(gen) * 100) / 100;  // ���������� �� 2 ������

    uniform_real_distribution<> l_dis(0.0, 1.0);
    double l = round(l_dis(gen) * 10) / 10;  // ���������� �� 1 �����

    double robincrease = 0.5 / (1 + pow(e, -((m / 200) * (bp / 200))));

    while (m > 0) {
        cout << fixed << setprecision(2);
        cout << "������ ���� ���. ������� ��� " << day
            << " ���� � �������� ��������. � ��� " << m
            << " ����� � " << b << " �������. ���� �� ����� ������� ������� "
            << bp << " ���� �� ������ �������: " << l << ".\n";

        cout << "�������� ��� �� ������� ����� ������: ��������� ������(1), �������� ������(2), ������ �� ������(3): ";
        string choise;
        cin >> choise;

        if (choise == "1") {
            cout << "��������� ������\n";
            cout << "��� ������� ������� �� ������ �������? ";
            cin >> choiseB;

            if (choiseB > b) {
                cout << "��� ��� �������� ����������� ��� :(((\n";
                break;
            }
            m = m - l + bp * choiseB;
            b -= choiseB;
        }
        else if (choise == "2") {
            cout << "�������� ������\n";
            cout << "��� ������� ������� �� ������ ������? ";
            cin >> choiseM;

            if (choiseM > m) {
                cout << "��� ��� �������� ����������� ��� :(((\n";
                break;
            }
            b += choiseM;
            m = m - l - bp * choiseM;
        }
        else if (choise == "3") {
            cout << "������ �� ������\n";
            cout << "C�� ������ ����������� � ������� 3 ��� �� ���� �� ���������� ���\n";
            m -= l;
        }
        else {
            cout << "��� ��� �������� ����������� ��� :(((\n";
            break;
        }

        // ���������� ���������
        maxBananaCost += 0.013;
        minBananaCost += 0.0131;

        // ������ ����� ����������
        maxrobChance += 100 + dis(gen) * 0.033 - 0.015;
        maxrobChance += robincrease;
        uniform_real_distribution<> rob_dis(0.01, maxrobChance);
        robChance = rob_dis(gen);

        cout << "���� �������: " << robChance << " ���� ���� �������: " << maxrobChance << "\n";
        cout << "������� �������: " << robincrease << "\n";

        uniform_real_distribution<> chance_dis(0.0, 100.0);
        if (robChance > chance_dis(gen)) {
            double loss = round(((m / 4) + bp + l / 10) * 100) / 100;
            cout << "��� �������� �� " << loss << " �����!!!\n";
            m = round((m - loss) * 100) / 100;
            maxrobChance /= 1.8;
        }

        // �������� �������
        if (rotChance > chance_dis(gen)) {
            uniform_real_distribution<> rot_dis(2.0, 10.0);
            bLoos = round(b / rot_dis(gen));
            b -= bLoos;
            cout << bLoos << " ����� ������� ������!!!\n";
            rotChance /= 2;
        }

        // ���������� ���
        uniform_real_distribution<> new_bp_dis(minBananaCost + 0.01, maxBananaCost);
        bp = round(new_bp_dis(gen) * 100) / 100;

        double l_max = bp + day / 4.0 + choiseM / (bp - minBananaCost + 1) + choiseB / (bp - minBananaCost + 1);
        uniform_real_distribution<> new_l_dis(0.0, l_max);
        l = round(new_l_dis(gen) * 10) / 10;

        day++;
    }

    return 0;
}
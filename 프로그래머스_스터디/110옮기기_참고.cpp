#include <string>
#include <vector>

using namespace std;

int Find_Last_Zero(string Str)
{
    for (int i = Str.length() - 1; i >= 0; i--) // Str�� ���������� ���������� Ȯ��
    {
        if (Str[i] == '0') return i; // 0�� �ִٸ� �ش� �ڸ��� return �Ѵ�
    }
    return -1; // 0�� ���ٸ� -1�� return�Ѵ�
}

vector<string> solution(vector<string> s)
{
    vector<string> answer;
    for (int i = 0; i < s.size(); i++) // �迭 �� �� ���ڿ��� ����
    {
        string Str = ""; // �� ���ڿ� Str ����
        int cnt = 0; // cnt ���� ���� (110�� ���� count��)

        for (int j = 0; j < s[i].length(); j++) // ���ڿ� �� �� ���ҿ� ����
        {
            Str += s[i][j]; // Str ���ڿ��� ���� �߰�
            if (Str.length() >= 3) // Str ���ڿ��� ���̰� 3 �̻��̶�� 
            {
                if (Str.substr(Str.length() - 3, 3) == "110") // Str ���ڿ��� ������ 3���� ���Ұ� 110�̶�� 
                {
                    cnt++; // cnt +1
                    Str.erase(Str.length() - 3, Str.length()); // Str ���ڿ����� 110 �����
                }
            }
        }
        // ������� ���ڿ����� 110�� ����(Cnt)�� 110�� ���� ���ڿ�(Str)�� ����

        // Find_Last_Zero�� ���� 110�� ���� ������ ���ڿ����� ���� ���� �ִ� 0�� ��ġ�� lastZ�� �����Ѵ�.
        int lastZ = Find_Last_Zero(Str);  
        
        // 1. ���� Str�� ���̻� 0�� �������� ������, �� �տ� 110 ����
        if (lastZ == -1) 
        {
            string Result = ""; // �� string�� Result�� ���Ӱ� ����
            while (cnt--) Result += "110"; // Result�� 110�� ������ŭ 110 �߰�
            Result += Str; // �������� Str �߰�
            answer.push_back(Result); // answer ���Ϳ� Result ���ڿ��� ����
        }

        // 2. ���� Str�� 0�� �־��ٸ�, ���� ���� �ִ� 0 �ٷ� �ڿ� 110 ����
        else 
        { 
            string Result = ""; // �� string�� Result�� ���Ӱ� ����
            for (int j = 0; j < Str.length(); j++) // Str�� ���̸�ŭ �ݺ�
            {
                if (j == lastZ) // j = Str ���ڿ����� ���� ���� �ִ� 0�� ��ġ
                {
                    Result += Str[j]; // Result�� Str[j] �߰�
                    while (cnt--) Result += "110"; // Result�� 110�� ������ŭ 110 �߰�
                }
                else  // j =/= Str ���ڿ����� ���� ���� �ִ� 0�� ��ġ
                    Result += Str[j]; // Result�� Str[j] �߰�
            }
            answer.push_back(Result); // answer ���Ϳ� Result ���ڿ��� ����
        }
    }
    return answer; // answer ���� return �� �Լ� ����
}
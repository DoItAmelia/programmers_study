#include <string>
#include <vector>

using namespace std;

int Find_Last_Zero(string Str)
{
    for (int i = Str.length() - 1; i >= 0; i--) // Str의 끝에서부터 역방향으로 확인
    {
        if (Str[i] == '0') return i; // 0이 있다면 해당 자리를 return 한다
    }
    return -1; // 0이 없다면 -1을 return한다
}

vector<string> solution(vector<string> s)
{
    vector<string> answer;
    for (int i = 0; i < s.size(); i++) // 배열 속 각 문자열에 대해
    {
        string Str = ""; // 빈 문자열 Str 선언
        int cnt = 0; // cnt 변수 선언 (110의 개수 count용)

        for (int j = 0; j < s[i].length(); j++) // 문자열 속 각 원소에 대해
        {
            Str += s[i][j]; // Str 문자열에 원소 추가
            if (Str.length() >= 3) // Str 문자열의 길이가 3 이상이라면 
            {
                if (Str.substr(Str.length() - 3, 3) == "110") // Str 문자열의 마지막 3개의 원소가 110이라면 
                {
                    cnt++; // cnt +1
                    Str.erase(Str.length() - 3, Str.length()); // Str 문자열에서 110 지우기
                }
            }
        }
        // 여기까지 문자열에서 110의 개수(Cnt)와 110을 없앤 문자열(Str)을 얻음

        // Find_Last_Zero를 통해 110을 지운 나머지 문자열에서 가장 끝에 있는 0의 위치를 lastZ에 저장한다.
        int lastZ = Find_Last_Zero(Str);  
        
        // 1. 만약 Str에 더이상 0이 남아있지 않으면, 맨 앞에 110 삽입
        if (lastZ == -1) 
        {
            string Result = ""; // 빈 string인 Result를 새롭게 선언
            while (cnt--) Result += "110"; // Result에 110의 개수만큼 110 추가
            Result += Str; // 다음으로 Str 추가
            answer.push_back(Result); // answer 벡터에 Result 문자열을 삽입
        }

        // 2. 만약 Str에 0이 있었다면, 가장 끝에 있는 0 바로 뒤에 110 삽입
        else 
        { 
            string Result = ""; // 빈 string인 Result를 새롭게 선언
            for (int j = 0; j < Str.length(); j++) // Str의 길이만큼 반복
            {
                if (j == lastZ) // j = Str 문자열에서 가장 끝에 있는 0의 위치
                {
                    Result += Str[j]; // Result에 Str[j] 추가
                    while (cnt--) Result += "110"; // Result에 110의 개수만큼 110 추가
                }
                else  // j =/= Str 문자열에서 가장 끝에 있는 0의 위치
                    Result += Str[j]; // Result에 Str[j] 추가
            }
            answer.push_back(Result); // answer 벡터에 Result 문자열을 삽입
        }
    }
    return answer; // answer 벡터 return 후 함수 종료
}
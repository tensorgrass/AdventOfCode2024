#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <algorithm>    // std::sort1

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    std::vector<int> v1, v2;
    int a, b;
    while (cin >> a >> b)
    {
        v1.push_back(a);
        v2.push_back(b);
    }
    //close the file
    fclose(stdin);

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    cout << "v1: " << v1.size() << endl << " elementos.";
    cout << "v2: " << v2.size() << endl << " elementos.";

    int sum = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " " << v2[i] << " " << abs(v1[i] - v2[i]) << endl;
        sum += abs(v1[i] - v2[i]);
    }
    cout << sum << endl;


    cout << "Total: " << sum << endl;
    //SOLUTION: 1879048

}
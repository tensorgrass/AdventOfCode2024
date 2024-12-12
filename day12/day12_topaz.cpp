//https://topaz.github.io/paste/#XQAAAQAcDAAAAAAAAAARmknGRw8TogB3Oxzri2QTFyHNmsUnNApHN7ntt1+q1p0T20pOn4Oa9Bj6GGlbfbAWlcfwHa2TVaKOOsZJ6LH7SJmSjj0UBceMd2O0e18kdclxIG74IZcAI+CW+haAU26/r4FS8J2retP+6Am0HAx3loQ2iLVF8pAYsS3LGkmL7+b2TcE973wF04LDXJ3VA15TdpDy7sZRt5JiHNoCzOlrFljYc+ovyyt2qkeioRch0w+1+RKp76MK11CtENznYlOe9uaAv4kZu4U8zOg3vSP3XFhypEfesjLLXSrWlqZ2nA7zopah9MSjz0TpOr8Rlvt65J/JzbFA4N8dDZHHO7TVWfuihVbsyl4tnD4JKpWb5VvXIYegaLIZtzcuvUayx7Wgwh2iehcF5LvLrIjGHgWiPlxzmHexZ39euUqCa3DpKMzYvzgBdvSG28HgTz4vbEseq1HqczrISo5A4+StaUyt0IrvxEWxOD4ya/lxVzrPbx25IghDdQngYAth2T/rR5QaECFliLvYpOacXI2anCckdVNYn7uU109ppuJMGdesoBP4ez6u4ihDOJx+Rdj+VXA/IoD6E2d2mS9xHklXRdvE/ArRVuVyp63m3pHHxsKeowlNmQV306+ne3n0eUhHiKLayoVZ0DsNvWt2UanW5bUlEU1VV5CfAWjsSqwF9TmZ70gzk+1OlgMlnD8v/OOOKIKyu06OTvZWiA3sfmHCVAU9fziOne96l7Em6vX5k991MRGoZAUN3dctJh7OOVWnb/5HlU5EVWUjHpZ0LtGucSRrwBFT68DzL/l6IDs40E4mWKQsSBzAJT+VBk0pkKDMr1gzoaSinBC5R3Wb6GEZFuAwTaj3NEvt5oQQDyCWZl5WgZxxFbdyO6cZCP819VSTpWJGopk1zU38GOk7bjYTBMrI1FpSKRupzW9vkaT8bZ6L8HfevkiwrdeYP9l6Lgr0aNowrfKP+XjtjjqMa12Rv4XSuDgrl2dR2jDhYgd9o1r1esIOLHa5WRe9ZZFO4CdZDfX6+XHY0e4SyVOGKgLAyU+7vOw5l7f76oLb64NDTlH3H80W+roF525aTsuEg8UNWd50TmXobIvECy+6zet/nXAtR7atoqZ3Q4lK5s8DqKo32TPcVM3bjbZWzMvdsoCIwJ4/q0rQ75QMPlVb9+HwFVGTIdq3siQF/W2AFb8G6N7LtoKUv6jwu1mwzn+XC0X0kxryKYOybfNEqitg2JG1oGNpHgoC114Vh0K3iq5iGAWUCcRmEk3Y2A8clkr4h1yyCyn2nWwPiIunkDZbizfNo1q3yO9OP7wJvxBm22Nw9skQejeorQ1BsDj82/uz/+h8uLw=
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>

void resolve();

int main() 
{
    resolve();
    return 0;
}

std::vector<std::string> parseFile(std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
        lines.push_back(line);
    file.close();
    return lines;
}


void resolve() {
    const std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::vector<std::string> input = parseFile("input.txt");
    int sum = 0, sumUniquePerimeter = 0;
    std::set<std::pair<int, int>> visited;
    for (int line=0; line < input.size(); line++) {
        for (int column=0; column<input[line].size(); column++) {
            int area = 0, perimeter = 0, uniquePerimeter=0;
            std::queue<std::pair<int, int>> toVisit({{line, column}});
            std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> perimetered;
            while (!toVisit.empty()) {
                // Ignore previously visited nodes
                auto [i, j] = toVisit.front();
                toVisit.pop();
                if (visited.contains({i, j}))
                    continue;
                visited.insert({i, j});

                // For area, simply count each node towards total for garden type
                area++;
                for (auto dir : directions) {
                    // Facing same garden type, don't add perimeter but visit next
                    if (input[i+dir.first][j+dir.second] == input[i][j]
                        && !(i < 0 || i >= input.size() || j < 0 || j >= input[i].size()))
                        toVisit.push({i+dir.first, j+dir.second});
                    else {
                        // For simple perimeter, simply increment
                        perimeter++;

                        // For bulk pricing, check if perimeter of any adjacent node facing
                        // the same directions was already priced
                        std::vector<std::pair<int, int>> adjDirections;
                        if (dir.first != 0)
                            adjDirections = {{0, -1}, {0, 1}};
                        else
                            adjDirections = {{-1, 0}, {1, 0}};
                        bool neighborCounted = false;
                        for (auto adj : adjDirections)
                            if (input[i+adj.first][j+adj.second] == input[i][j]
                                && perimetered.contains({{i+adj.first, j+adj.second}, dir}))
                                neighborCounted = true;
                        if (!neighborCounted)
                            uniquePerimeter++;
                        perimetered.insert({{i, j}, dir});
                    }
                }
            }
            sum += area * perimeter;
            sumUniquePerimeter += area * uniquePerimeter;
        }
    }
    std::cout << "Part 1: " << sum << std::endl;
    std::cout << "Part 2: " << sumUniquePerimeter << std::endl;
}

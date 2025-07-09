#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename Container>
void display(const Container &container){
    for (const auto &e : container)
        cout << e << " ";
    cout << endl;
}

int main()
{
    vector<char> vc = {'H', 'E', 'L', 'L', 'O'};
    vector<string> vs;

    for (auto it = vc.begin(); it != vc.end(); ++it){
        vs.emplace_back((1,*it));
    }

    display(vs);

    return 0;
}

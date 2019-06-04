#include <iostream>

using namespace std;

class fooo{
public:
    template<class T>
    void func(T){
        cout << typeid(T).name() << endl;
    }
};
 
int main(int argc, char * * argv) {
    fooo f;
    f.func<int>(100);
    return 0;
}
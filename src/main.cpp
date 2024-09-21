#include "generator.hpp"
#include <iostream>

using namespace std;

int main(){
    TemperatureGenerator generator = TemperatureGenerator(0123, 0.5);


    for (int i = 0; i<1000;i++){
        cout << generator.get_next_measure() << endl;
    }


}
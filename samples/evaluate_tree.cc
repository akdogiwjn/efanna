
#include <efanna.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <malloc.h>
#include <boost/timer/timer.hpp>
using namespace efanna;
using namespace std;
int main(){
    string tree_path = "/data/lcq_data/sift100m/tree/sift.trees";
    int node_size = 1000000;
    float * data_load= NULL;;
    Matrix<float> dataset(0,0,data_load);
    FIndex<float> index(dataset, new L2DistanceAVX<float>(), efanna::KDTreeUbIndexParams(true, 8 ,8 ,10,25,30,node_size));
    index.loadTrees(tree_path.c_str());
    index.evaluate_tree();
}
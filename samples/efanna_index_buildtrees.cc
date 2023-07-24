#include <efanna.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <malloc.h>

using namespace efanna;
using namespace std;
void load_data( const char* filename, float*& data, size_t& num,int& dim){// load data with sift10K pattern
    ifstream in(filename, ios::binary);
    dim = 128;
    if(!in.is_open()){cout<<"open file error"<<endl;exit(-1);}
    // in.read((char*)&dim,4);
    cout<<"data dimension: "<<dim<<endl;
    in.seekg(0,ios::end);
    ios::pos_type ss = in.tellg();
    size_t fsize = (size_t)ss;
    // num = fsize / (dim+1) / 4;
    num = fsize / (dim) / 4;
    //将dim向上扩充为8的整数倍
    // int cols = (dim + 7)/8*8;
    #ifdef __AVX__
      int cols = (dim + 7)/8*8;//re align to sse format
    #else
    #ifdef __SSE2__
      int cols = (dim + 3)/4*4;
    #else
      int cols = dim;
    #endif
    #endif
    data = (float*)memalign(KGRAPH_MATRIX_ALIGN, num * cols * sizeof(float));//调整起始地址为KGRAPH_MATRIX_ALIGN的倍数
    if(dim!=cols)cout<<"data align to dimension "<<cols<<" for avx2 inst"<<endl;

    in.seekg(0,ios::beg);
    for(size_t i = 0; i < num; i++){
        // 从当前位置向后移4个字节
        // in.seekg(4,ios::cur);
        in.read((char*)(data+i*cols),dim*4);//读一行
    }
    cout<<"data size: "<<num<<endl;
    cout<<"load finish"<<endl;
    in.close();
}
std::string intToFiveDigitString(int num) {
    // 将数字num转换为字符串
    std::string str = std::to_string(num);
    
    // 如果长度小于5位,在前面填充0
    while (str.length() < 5) {
        str = "0" + str;  
    }
    
    return str;  
}
void load_data100m( float*& data, size_t& num,int& dim){// load data with sift10K pattern
    string filename= "/data/lcq_data/sift100m";
    dim = 128;
    num = 100 * 1000 * 1000;
    cout<<"data dimension: "<<dim<<endl;
    cout<<"data size: "<<num<<endl;
    //将dim向上扩充为8的整数倍
    #ifdef __AVX__
      int cols = (dim + 7)/8*8;//re align to sse format
    #else
    #ifdef __SSE2__
      int cols = (dim + 3)/4*4;
    #else
      int cols = dim;
    #endif
    #endif
    data = (float*)memalign(KGRAPH_MATRIX_ALIGN, num * cols * sizeof(float));//调整起始地址为KGRAPH_MATRIX_ALIGN的倍数
    if(dim!=cols)cout<<"data align to dimension "<<cols<<" for avx2 inst"<<endl;
    size_t file_index = 0;
    cout<<"load 0 to 300"<<endl;
    for(int i = 0; i < 300; i++){
        string filename1 = filename + "/000_to_299_bin/sift100m_base_"+intToFiveDigitString(i)+".bin";
        ifstream in(filename1, ios::binary);
        // cout<<"load: "<<filename1<<endl;
        if(!in.is_open()){cout<<"open file error: "<<filename1<<endl;exit(-1);}
        in.seekg(0,ios::end);
        ios::pos_type ss = in.tellg();
        size_t fsize = (size_t)ss;
        // num = fsize / (dim+1) / 4;
        size_t file_num = fsize / (dim) / 4;
        assert(file_num == 100000);
        in.seekg(0,ios::beg);
        for(size_t j = 0; j < file_num;){
            // 从当前位置向后移4个字节
            // in.seekg(4,ios::cur);
            // cout<<"j: "<<j<<" file_index: "<<file_index<<endl;
            in.read((char*)(data+file_index),dim*4);//读一行
            j++;
            file_index += (cols);
        }
        in.close();
    }
    cout<<"load 300 to 600"<<endl;
    for(int i = 300; i < 600; i++){
        string filename2 = filename + "/300_to_599_bin/sift100m_base_"+intToFiveDigitString(i)+".bin";
        ifstream in(filename2, ios::binary);
        if(!in.is_open()){cout<<"open file error: "<<filename2<<endl;exit(-1);}
        in.seekg(0,ios::end);
        ios::pos_type ss = in.tellg();
        size_t fsize = (size_t)ss;
        // num = fsize / (dim+1) / 4;
        size_t file_num = fsize / (dim) / 4;
        assert(file_num == 100000);
        in.seekg(0,ios::beg);
        for(size_t j = 0; j < file_num;){
            // 从当前位置向后移4个字节
            // in.seekg(4,ios::cur);
            in.read((char*)(data+file_index),dim*4);//读一行
            j++;
            file_index += cols;
        }
        in.close();
    }
    cout<<"load 600 to 1000"<<endl;
    for(int i = 600; i < 1000; i++){
        string filename3 = filename + "/600_to_999_bin/sift100m_base_"+intToFiveDigitString(i)+".bin";
        ifstream in(filename3, ios::binary);
        if(!in.is_open()){cout<<"open file error: "<<filename3<<endl;exit(-1);}
        in.seekg(0,ios::end);
        ios::pos_type ss = in.tellg();
        size_t fsize = (size_t)ss;
        // num = fsize / (dim+1) / 4;
        size_t file_num = fsize / (dim) / 4;
        assert(file_num == 100000);
        in.seekg(0,ios::beg);
        for(size_t j = 0; j < file_num;){
            // 从当前位置向后移4个字节
            // in.seekg(4,ios::cur);
            in.read((char*)(data+file_index),dim*4);//读一行
            j++;
            file_index += cols;
        }
        in.close();
    }
    for(int i = 0; i < dim; i++){
      cout<<*(data+i)<<" ";
    }
    cout<<endl;
    size_t  ii = 128;
    ii = ii * 99999999;
    for(int i = 0; i < dim; i++){
      cout<<*(data+ii+i)<<" ";
    }
    cout<<endl;
    cout<<"load finish"<<endl;
    
}
int main(int argc, char** argv){
  // const char * in_path = "/data/lcq_data/sift100m/000_to_299_bin/sift100m_base_00000.bin";
  const char * out_path = "/data/lcq_data/sift100m/tree/sift1.trees";
  // if( argc != 2 ) {cout<< argv[0] << " data_file save_trees_file trees" <<endl; exit(-1);}

  float* data_load = NULL;
  //float* query_load = NULL;
  size_t points_num;
  int dim;
  // load_data(in_path, data_load, points_num,dim);
  // load_data10m( data_load, points_num,dim);
  load_data100m( data_load, points_num,dim);

  Matrix<float> dataset(points_num,dim,data_load);//存的是每个向量的起始地址

  // unsigned int trees = atoi(argv[1]);
  unsigned int trees = 1;
  int node_size = 1000*1000;
  //trees 控制树的个数
  //最后一个参数10控制叶子节点大小
  //其它无用
  FIndex<float> index(dataset, new L2DistanceAVX<float>(), efanna::KDTreeUbIndexParams(true, trees ,8 ,8,25,30, 10, 8, node_size));
  clock_t s,f;
  s = clock();//计时
  index.buildTrees();

  f = clock();
  cout<<"Index building time : "<<(f-s)*1.0/CLOCKS_PER_SEC<<" seconds"<<endl;
  index.saveTrees(out_path);
  return 0;
}

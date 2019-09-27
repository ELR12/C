/*
  Created by
  Ethan Roberts
  CS 415 Operating Systems

  This is a multi-threaded program that averages two data-sets
  together using eight different threads.

  Compiled using:  g++ -g -pthread multiThreadAverage.cpp -o output

*/



#include <iostream>
#include <thread>
using namespace std;

 
#define MAXSIZE 10000000



void arrayAverage(int *dataset1, int *dataset2, int *resultset, int size)
{
  
  // 8 partitions will run this meaning each thread will
  // process 1,250,000 elements each

   for (int i = (size - 1250000); i < size; ++i){
     resultset[i] = ((dataset1[i] + dataset2[i])/2);
   }  
}





int main()
{

  int *dataset1 = new int[MAXSIZE];
  int *dataset2 = new int[MAXSIZE];
  int *resultset = new int[MAXSIZE];

  //clearing all arrays before using
  for (int i = 0; i < MAXSIZE; ++i){
    dataset1[i] = 0;
    dataset2[i] = 0;
    resultset[i] = 0;
  }


  //filling data-sets with values
  for (int i = 0; i < MAXSIZE; ++i){
    dataset1[i] = (i * 2);
    dataset2[i] = (i * 3);
  }


  
  thread t1(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 1));
  thread t2(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 2));
  thread t3(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 3));
  thread t4(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 4));
  thread t5(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 5));
  thread t6(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 6));
  thread t7(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 7));
  thread t8(arrayAverage,dataset1,dataset2,resultset,((MAXSIZE / 8) * 8));
  
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();

  
  //**  Uncomment code below to print all 10 million averages
  //**  inside "resultset"

  
  //  for (int i = 0; i < MAXSIZE; ++i)
  // cout << "Average of index " << i << ": " << resultset[i] << "\n";


  //printing 200 elements to prove the code is accurate
  for (int i = 0; i < 200; ++i){
    cout << "Average of index " << i << ": " << resultset[i] << "\n";
  }
  
  return 0;
}

#include<iostream>
#include<vector>
using namespace std;
int main(){
  long long int t, min, max, i, k, num_programas, num_dificuldades;
  vector<long long int> v1;
  vector<long long int> v2;
  cin >> t >> min >> max;
  num_dificuldades = max-min+1;
  v1.assign(num_dificuldades, 1);
  v2 = v1;
  for(k=1; k<t; k++){
    for(i=0; i<num_dificuldades; i++){
     if(i==0){
       v2[i] = v1[i+1];
     }
     else{
       if(i == num_dificuldades-1){
         v2[i] = v1[i-1];
       }
       else{
         v2[i] = v1[i-1]+v1[i+1];
       }
     }
    }
    v1.swap(v2);
  }
  for(num_programas=0, i=0; i < num_dificuldades; i++){
    num_programas += v1[i];
    num_programas = num_programas % 1000000007;
  }
  cout << num_programas << endl;
  return 0;
}

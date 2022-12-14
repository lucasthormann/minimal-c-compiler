int i;

int main1(){
  output(90);
  return 0;
}

char main2(int arg1){
  output(8);
  output(9);
  output(10);
  output(1);
  return 'c';
}

void main3(void arg1, char arg2[]){
  output(11);
}

char main(){
    int i;
    char c;
    void v;
    main1();
    main2(i);
}

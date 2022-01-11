#include <iostream>
using namespace std;
#include <string>
# include <vector>
void readInputs();
void run();
void fifo();
void lru();
void optimal();
void clockAlgorithm();
int pageSize;
string replacementMethod;
vector<int> pages;
int main(){

run();

return 0;
}
void run(){
readInputs();

for (int i:pages)
      printf("%d\n",i);
printf("Replacement Policy = %s\n-------------------------------------\nPage   Content of Frames\n----   ---------------\n",replacementMethod.c_str());
if (replacementMethod=="FIFO")
	fifo();
else if(replacementMethod=="LRU")
       lru();
else if(replacementMethod=="CLOCK")
       clockAlgorithm();
else if(replacementMethod=="OPTIMAL")
       optimal();
}
void readInputs(){
scanf("%d",&pageSize);
cin >> replacementMethod;
int page;
vector<int> pages;
scanf("%d",&page);
while(page!=-1)
{  
   pages.push_back(page);
   scanf("%d",&page);
}
}
void fifo()
{ 
 printf("fif");
}
void lru(){
 printf("a");
}
void clockAlgorithm(){
printf("a");
}
void optimal(){
printf("a");
}

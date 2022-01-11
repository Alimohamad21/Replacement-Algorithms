#include <iostream>

using namespace std;

#include <string>
# include <vector>
#include <deque>

void readInputs();

void run();

void fifo();

void lru();

void optimal();

void clockAlgorithm();

bool inFrame(vector<string> frameContents, string page);

int maxPageSize;
string replacementMethod;
vector<string> pages;

int main() {
    run();
}

void run() {
    readInputs();
    printf("Replacement Policy = %s\n-------------------------------------\nPage   Content of Frames\n----   ---------------\n",
           replacementMethod.c_str());
    if (replacementMethod == "FIFO")
        fifo();
    else if (replacementMethod == "LRU")
        lru();
    else if (replacementMethod == "CLOCK")
        clockAlgorithm();
    else if (replacementMethod == "OPTIMAL")
        optimal();
}

void readInputs() {
    scanf("%d", &maxPageSize);
    cin >> replacementMethod;
    string page;
    cin >> page;
    while (page != "-1") {
        if (page.length() == 1)
            page = "0" + page;
        pages.push_back(page);
        cin >> page;
    }
}

bool inFrame(vector<string> frameContents, string page) {
    for (int i = 0; i < frameContents.size(); i++) {
        if (frameContents[i] == page)
            return true;
    }
    return false;
}

void fifo() {
    vector<string> frameContents;
    int pageFaults = 0;
    string lineToPrint;
    deque<string>::iterator search;
    bool pageInFrame;
    int firstIn=0;
    for (string page:pages) {
        lineToPrint = page;
        pageInFrame = inFrame(frameContents, page);
        if (frameContents.size() < maxPageSize) {
            if (!pageInFrame)
                frameContents.push_back(page);// enqueue
            lineToPrint += "     ";
        } else if (frameContents.size() == maxPageSize) {
            if (!pageInFrame) {
                frameContents[firstIn]=page;
                firstIn= (firstIn+1) % maxPageSize;
                pageFaults++;
                lineToPrint += " F";
                lineToPrint += "   ";
            } else {
                lineToPrint += "     ";
            }
        }
        for (int i = 0; i < frameContents.size(); i++) {
            lineToPrint += frameContents[i];
            if (i != frameContents.size() - 1)
                lineToPrint += " ";
        }
        lineToPrint += "\n";
        cout << lineToPrint;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}

void lru() {
    printf("a");
}

void clockAlgorithm() {
    printf("a");
}

void optimal() {
    printf("a");
}

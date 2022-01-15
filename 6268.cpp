#include <iostream>
# include <string>
# include <vector>

using namespace std;



struct clockPage {
    string page;
    bool used;
};
typedef struct clockPage clockPage;

void readInputs();

void run();

void fifo();

void lru();

void optimal();

void clockAlgorithm();

int getLastOccurrenceBeforeIndex(vector<string> pages, string page, int currentIndex);

int getLruIndex(vector<string> frameContents, int currentIndex);

int getFirstOccurrenceAfterIndex(vector<string> pages, string page, int currentIndex);

int getOptimalIndex(vector<string> frameContents, int currentIndex);

void resetUsedBits(vector<clockPage> &frameContents);

void setUsedBit(vector<clockPage> &frameContents, string page);

bool inFrame(vector<string> frameContents, string page);

bool inFrame(vector<clockPage> frameContents, string page);


int maxPageSize;
string replacementMethod;
vector<string> pages;
int framePointer = 0; // for clock replacement algorithm

int main() {
    run();
}

void run() {
    readInputs();
    printf("Replacement Policy = %s\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n",
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

bool inFrame(vector<clockPage> frameContents, string page) {  // for clock replacement algorithm
    for (int i = 0; i < frameContents.size(); i++) {
        if (frameContents[i].page == page)
            return true;
    }
    return false;
}

int getLastOccurrenceBeforeIndex(vector<string> pages, string page, int currentIndex) {
    for (int i = currentIndex - 1; i >= 0; i--) {
        if (pages[i] == page)
            return i;
    }
    return 1;
}

int getLruIndex(vector<string> frameContents, int currentIndex) {
    int minIndex = getLastOccurrenceBeforeIndex(pages, frameContents[0], currentIndex);
    int lastOccurrenceIndex, lruIndex = 0;
    for (int i = 1; i < frameContents.size(); i++) {
        lastOccurrenceIndex = getLastOccurrenceBeforeIndex(pages, frameContents[i], currentIndex);
        if (lastOccurrenceIndex < minIndex) {
            minIndex = lastOccurrenceIndex;
            lruIndex = i;
        }
    }
    return lruIndex;
}

int getFirstOccurrenceAfterIndex(vector<string> pages, string page, int currentIndex) {
    for (int i = currentIndex + 1; i < pages.size(); i++) {
        if (pages[i] == page)
            return i;
    }
    return 2147483647;
}

int getOptimalIndex(vector<string> frameContents, int currentIndex) {
    int maxIndex = getFirstOccurrenceAfterIndex(pages, frameContents[0], currentIndex);
    int firstOccurrenceIndex, optimalIndex = 0;
    for (int i = 1; i < frameContents.size(); i++) {
        firstOccurrenceIndex = getFirstOccurrenceAfterIndex(pages, frameContents[i], currentIndex);
        if (firstOccurrenceIndex > maxIndex) {
            maxIndex = firstOccurrenceIndex;
            optimalIndex = i;
        }
    }
    return optimalIndex;
}

void resetUsedBits(vector<clockPage> &frameContents) {
    while (frameContents[framePointer].used == true) {
        frameContents[framePointer].used = false;
        framePointer = (framePointer + 1) % maxPageSize;
    }
}

void setUsedBit(vector<clockPage> &frameContents, string page) {
    for (int i = 0; i < frameContents.size(); i++) {
        if (frameContents[i].page == page)
            frameContents[i].used = true;
    }
}

void fifo() {
    vector<string> frameContents;
    int pageFaults = 0;
    string lineToPrint;
    bool pageInFrame;
    int firstIn = 0;
    for (string page:pages) {
        lineToPrint = page;
        pageInFrame = inFrame(frameContents, page);
        if (frameContents.size() < maxPageSize) {
            if (!pageInFrame)
                frameContents.push_back(page);
            lineToPrint += "     ";
        } else if (frameContents.size() == maxPageSize) {
            if (!pageInFrame) {
                frameContents[firstIn] = page;
                firstIn = (firstIn + 1) % maxPageSize;
                pageFaults++;
                lineToPrint += " F";
                lineToPrint += "   ";
            } else {
                lineToPrint += "     ";
            }
        }
        for (int i = 0; i < frameContents.size(); i++) {
            lineToPrint += frameContents[i];
            lineToPrint += " ";
        }
        lineToPrint += "\n";
        cout << lineToPrint;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}

void lru() {
    vector<string> frameContents;
    int pageFaults = 0;
    string lineToPrint;
    bool pageInFrame;
    int lruIndex;
    for (int i = 0; i < pages.size(); i++) {
        lineToPrint = pages[i];
        pageInFrame = inFrame(frameContents, pages[i]);
        if (frameContents.size() < maxPageSize) {
            if (!pageInFrame)
                frameContents.push_back(pages[i]);
            lineToPrint += "     ";
        } else if (frameContents.size() == maxPageSize) {
            if (!pageInFrame) {
                lruIndex = getLruIndex(frameContents, i);
                frameContents[lruIndex] = pages[i];
                pageFaults++;
                lineToPrint += " F";
                lineToPrint += "   ";
            } else {
                lineToPrint += "     ";
            }
        }
        for (int i = 0; i < frameContents.size(); i++) {
            lineToPrint += frameContents[i];
            lineToPrint += " ";
        }
        lineToPrint += "\n";
        cout << lineToPrint;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}

void clockAlgorithm() {
    vector<clockPage> frameContents;
    int pageFaults = 0;
    string lineToPrint;
    bool pageInFrame;
    clockPage clkPage;
    for (int i = 0; i < pages.size(); i++) {
        lineToPrint = pages[i];
        pageInFrame = inFrame(frameContents, pages[i]);
        if (frameContents.size() < maxPageSize) {
            if (!pageInFrame) {
                clkPage.page = pages[i];
                clkPage.used = true;
                frameContents.push_back(clkPage);
            }
            lineToPrint += "     ";
        } else if (frameContents.size() == maxPageSize) {
            if (!pageInFrame) {
                resetUsedBits(frameContents);
                clkPage.page = pages[i];
                clkPage.used = true;
                frameContents[framePointer] = clkPage;
                framePointer = (framePointer + 1) % maxPageSize;
                pageFaults++;
                lineToPrint += " F";
                lineToPrint += "   ";
            } else {
                setUsedBit(frameContents, pages[i]);
                lineToPrint += "     ";
            }
        }
        for (int i = 0; i < frameContents.size(); i++) {
            lineToPrint += frameContents[i].page;
            lineToPrint += " ";
        }
        lineToPrint += "\n";
        cout << lineToPrint;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}

void optimal() {
    vector<string> frameContents;
    int pageFaults = 0;
    string lineToPrint;
    bool pageInFrame;
    int optimalIndex;
    for (int i = 0; i < pages.size(); i++) {
        lineToPrint = pages[i];
        pageInFrame = inFrame(frameContents, pages[i]);
        if (frameContents.size() < maxPageSize) {
            if (!pageInFrame)
                frameContents.push_back(pages[i]);// enqueue
            lineToPrint += "     ";
        } else if (frameContents.size() == maxPageSize) {
            if (!pageInFrame) {
                optimalIndex = getOptimalIndex(frameContents, i);
                frameContents[optimalIndex] = pages[i];
                pageFaults++;
                lineToPrint += " F";
                lineToPrint += "   ";
            } else {
                lineToPrint += "     ";
            }
        }
        for (int i = 0; i < frameContents.size(); i++) {
            lineToPrint += frameContents[i];
            lineToPrint += " ";
        }
        lineToPrint += "\n";
        cout << lineToPrint;
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}

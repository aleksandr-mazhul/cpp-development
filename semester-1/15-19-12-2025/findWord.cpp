#include <iostream>
// #include <cstring>
using namespace std;

size_t findWordInSentence(const char* sentence, const char* word, bool onlyWholeWord, size_t positions[],
                          size_t maxSize);

size_t myStrlen(const char* smth);

bool isSeparator(char c);

void printPositions(const size_t positions[], size_t count);


int main()
{
    char sentence[] =
        "friendly Let  me introduce myself. My name is Mariya I am a 20-year-old student from Donetsk. I study at the university in my native town and my future profession is bookkeeping. I live with my parents and my elder sister Lena. We are a friendly family. Lena is 2 years older than me. We share our room and tell all our secrets to each other friendly . ";
    char word[] = "friendly";
    size_t positions[100];

    size_t count = findWordInSentence(sentence, word, true, positions, 100);
    printPositions(positions, count);
}


size_t myStrlen(const char* smth)
{
    size_t i{0};
    for (; smth[i] != '\0'; i++)
    {
    }
    return i;
}


bool isSeparator(char c)
{
    return c == ' ' || c == '.' || c == ',' || c == ';' ||
        c == ':' || c == '!' || c == '?' || c == '-' ||
        c == '\n' || c == '\t' || c == '\0';
}


size_t findWordInSentence(const char* sentence, const char* word, bool onlyWholeWord, size_t positions[],
                          size_t maxSize)
{
    size_t count = 0;
    size_t lenSentence = myStrlen(sentence);
    size_t lenWord = myStrlen(word);

    if (word[0] == '\0')
    {
        return 0;
    }

    if (onlyWholeWord && isSeparator(word[0]))
    {
        return 0;
    }

    for (size_t i{0}; i + lenWord <= lenSentence; i++)
    {
        if (sentence[i] != word[0])
        {
            continue;
        }

        bool match = true;
        for (size_t j = 0; j < lenWord; j++)
        {
            if (sentence[i + j] != word[j])
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            if (onlyWholeWord)
            {
                if (i > 0 && !isSeparator(sentence[i - 1]))
                {
                    continue;
                }
                if (i + lenWord < lenSentence && !isSeparator(sentence[i + lenWord]))
                {
                    continue;
                }
            }

            if (count < maxSize)
            {
                positions[count++] = i;
            }
        }
    }
    return count;
}


void printPositions(const size_t positions[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        cout << positions[i] << " ";
    }
    cout << endl;
    cout << "Count = " << count << endl;
}

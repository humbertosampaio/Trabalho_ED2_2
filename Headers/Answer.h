//
// Created by edson on 31/03/18.
//

#ifndef TRABALHO_ED2_ANSWER_H
#define TRABALHO_ED2_ANSWER_H

#include <iostream>
#include <string>

using namespace std;

class Answer {
private:
    int answerId;
    int userId;
    string date;
    unsigned int questionId;
    int score;
public:
    Answer(string* answer);

    bool operator==(const Answer &rhs) const;

    bool operator!=(const Answer &rhs) const;

    bool operator<(const Answer &rhs) const;

    bool operator>(const Answer &rhs) const;

    bool operator<=(const Answer &rhs) const;

    bool operator>=(const Answer &rhs) const;

    unsigned int getQuestionId() const;

    int getUserId() const;
};


#endif //TRABALHO_ED2_ANSWER_H

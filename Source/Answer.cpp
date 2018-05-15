//
// Created by edson on 31/03/18.
//

#include "../Headers/Answer.h"

Answer::Answer(string *answer)
{
    this->answerId = stoi(answer[0], nullptr, 10);
    this->userId = (answer[1] != "NA" ? stoi(answer[1], nullptr, 10) : -1);
    this->date = answer[2];
    this->questionId = stoi(answer[3], nullptr, 10);
    this->score = stoi(answer[4], nullptr, 10);
}

bool Answer::operator==(const Answer &rhs) const {
    return questionId == rhs.questionId;
}

bool Answer::operator!=(const Answer &rhs) const {
    return !(rhs == *this);
}

bool Answer::operator<(const Answer &rhs) const {
    return questionId < rhs.questionId;
}

bool Answer::operator>(const Answer &rhs) const {
    return rhs < *this;
}

bool Answer::operator<=(const Answer &rhs) const {
    return !(rhs < *this);
}

bool Answer::operator>=(const Answer &rhs) const {
    return !(*this < rhs);
}

unsigned int Answer::getQuestionId() const {
    return questionId;
}

int Answer::getUserId() const {
    return userId;
}

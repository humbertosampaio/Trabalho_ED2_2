//
// Created by edson on 31/03/18.
//

#include "../Headers/Tag.h"

Tag::Tag(unsigned int questionId, list<string> tagList)
{
    this->questionId = questionId;
    this->tagList = tagList;
}

void Tag::printTags()
{
    for (list<string>::iterator it = tagList.begin(); it != tagList.end(); ++it)
        cout << (*it) << " ";
    cout << endl;
}

list<string> Tag::getTagList(){
    return tagList;
}

unsigned int Tag::getQuestionId() const {
    return questionId;
}

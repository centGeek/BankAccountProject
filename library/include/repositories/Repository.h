//
// Created by Wiktor Stępniewski on 29/05/2023.
//

#ifndef CARRENTAL_REPOSITORY_H
#define CARRENTAL_REPOSITORY_H

#include <memory>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template<class T>
class Repository
{
protected:
    vector<shared_ptr<T>> elements;
public:
    static bool truePredicate(shared_ptr<T>)
    {
        return true;
    }

    std::shared_ptr<T> get(int index) const
    {
        if (elements[index] == nullptr)
            return nullptr;
        return elements[index];
    }

    int size() const
    {
        return elements.size();
    }

    std::vector<shared_ptr<T>> findAll() const
    {
        return this->findBy(truePredicate);
    }


    template<typename P>
    std::vector<shared_ptr<T>> findBy(P predicate) const
    {
        std::vector<shared_ptr<T>> result;
        for (int i = 0; i < elements.size(); ++i)
        {
            shared_ptr<T> object = elements[i];
            if (predicate(object))
                result.push_back(object);
        }
        return result;
    }

    template<typename P>
    std::shared_ptr<T> findIndividualByPredicate(P predicate) const
    {
        for (int i = 0; i < elements.size(); ++i)
        {
            shared_ptr<T> object = elements[i];
            if (predicate(object))
                return object;
        }
        return nullptr;
    }


    virtual void add(shared_ptr<T> newObject)
    {
        if (newObject == nullptr)
            return;
        elements.push_back(newObject);
    }

    void eraseObjectFromRepository(std::shared_ptr<T> erasedObject)
    {
        if (erasedObject == nullptr)
            return;
        auto newEndIterator = remove(elements.begin(), elements.end(), erasedObject);
        elements.erase(newEndIterator, elements.end());
    }


};

#endif //CARRENTAL_REPOSITORY_H

/**************************************************************************************************
*
* \file
* \brief EB C++ Training - C++11/14 - function/bind Example
* 
* Copyright (c) 2016 Elektrobit. All rights reserved.
*
* This file is part of the Elektrobit C++ Training.
*
* Task: Extend the given subject/observer implementation such that an observer is notified
* about state changes via a generalized std::function callback.
*
**************************************************************************************************/

#include <functional>
#include <iostream>
#include <list>

class subject
{
public:
    using callback   = std::function<void(int)>;
    using callbacks  = std::list<callback>;
    using callback_id = callbacks::const_iterator;

    explicit subject()
    : state_(0)
    , callbacks_()
    {}

    callback_id add(callback cb)
    {
        cb(state_);
        return callbacks_.insert(callbacks_.end(), std::move(cb));
    }

    void remove(callback_id cb)
    {
        callbacks_.erase(cb);
    }

    void change_state(int new_state)
    {
        state_ = new_state;
        notify_all();
    }

private:
    int state_;
    void notify_all() const
    {
        for(auto const& callback : callbacks_) {
            callback(state_);
        }
    }
    callbacks callbacks_;
};

class observer
{
public:
    observer(subject& subject)
    : subject_(subject)
    {
		subject::callback myCallback = std::bind(&observer::update, this, std::placeholders::_1);
		callback_id_ = subject_.add(myCallback);
        //callback_id_ = subject_.add([this](int status){ update(status); });
    }

    ~observer()
    {
        subject_.remove(callback_id_);
    }

private:
    subject& subject_;
    subject::callback_id callback_id_;

    void update(int state)
    {
        std::cout << "observer@" << this << " received an update from subject. State = " << state << "\n";
    }
};

int main()
{
   subject subject;
   subject.change_state(1);
   observer observer1(subject);
   subject.change_state(2);
   {
       observer observer2(subject);
       subject.change_state(3);
   }
   subject.change_state(4);
}

// Output:
// observer@0x7ffdcf9a46b0 received an update from subject. State = 1
// observer@0x7ffdcf9a46b0 received an update from subject. State = 2
// observer@0x7ffdcf9a46c0 received an update from subject. State = 2
// observer@0x7ffdcf9a46b0 received an update from subject. State = 3
// observer@0x7ffdcf9a46c0 received an update from subject. State = 3
// observer@0x7ffdcf9a46b0 received an update from subject. State = 4

// WARNING: This simplistic implementation of a modernized observer pattern has
// severe issues which preclude its use in real world applications:
//
// 1. The classical observer pattern
// (https://en.wikipedia.org/wiki/Observer_pattern) requires the concrete
// observer to inherit from an abstract observer class. It was our aim to reduce
// this tight coupling.
// Instead we now have a dependency from observer to subject, which is not much
// better. This is due to the fact that we want to remove the observer from
// subject in the observer's destructor.
// Solution: connection_id must be an abstraction which manages both the
// iterator and the container into which this iterator points. Then removal will
// be possible without having to refer to subject.
//
// 2. The current implementation does not handle the case of subject going out
// of scope before the observer. In that case, the destructor of observer will
// call into a dangling reference to the subject.
//
// 3. The current implementation is not thread-safe. Concurrently adding and/or
// removing callbacks or concurrently adding/removing while notifying the callbacks
// will lead to undefined behavior.
//
// CONCLUSION: Writing a stable and thread-safe implementation of the above pattern
// is not a trivial task. Have a look at Boost::Signals2 for further information.

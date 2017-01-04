#include <functional>
#include <iostream>
#include <list>

class Subject
{
public:
    using callback   = std::function<void(int)>;
    using callbacks  = std::list<callback>;
    // In Linux there is a problem with the implementation of erase with const_iterators http://stackoverflow.com/questions/15987893/c11-erase-using-a-const-iterator
    using callback_id = callbacks::iterator;
    //using callback_id = callbacks::const_iterator;

    explicit Subject()
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

class Observer
{
public:
    Observer(Subject & subject)
    : m_subject(subject)
    {
		Subject::callback myCallback = std::bind(&Observer::update, this, std::placeholders::_1);
		callback_id_ = m_subject.add(myCallback);
        //callback_id_ = subject_.add([this](int status){ update(status); });
    }

    ~Observer()
    {
        m_subject.remove(callback_id_);
    }

private:
    Subject & m_subject;
    Subject::callback_id callback_id_;

    void update(int state)
    {
        std::cout << "Observer@" << this << " received an update from Subject. State = " << state << "\n";
    }
};

int main()
{
   Subject subject;
   subject.change_state(1);
   Observer observer1(subject);
   subject.change_state(2);
   {
       Observer observer2(subject);
       subject.change_state(3);
   }
   subject.change_state(4);
}

// Output:
// Observer@0x7ffdcf9a46b0 received an update from Subject. State = 1
// Observer@0x7ffdcf9a46b0 received an update from Subject. State = 2
// Observer@0x7ffdcf9a46c0 received an update from Subject. State = 2
// Observer@0x7ffdcf9a46b0 received an update from Subject. State = 3
// Observer@0x7ffdcf9a46c0 received an update from Subject. State = 3
// Observer@0x7ffdcf9a46b0 received an update from Subject. State = 4

// WARNING: This simplistic implementation of a modernized Observer pattern has
// severe issues which preclude its use in real world applications:
//
// 1. The classical Observer pattern
// (https://en.wikipedia.org/wiki/Observer_pattern) requires the concrete
// Observer to inherit from an abstract Observer class. It was our aim to reduce
// this tight coupling.
// Instead we now have a dependency from Observer to Subject, which is not much
// better. This is due to the fact that we want to remove the Observer from
// Subject in the Observer's destructor.
// Solution: connection_id must be an abstraction which manages both the
// iterator and the container into which this iterator points. Then removal will
// be possible without having to refer to Subject.
//
// 2. The current implementation does not handle the case of Subject going out
// of scope before the Observer. In that case, the destructor of Observer will
// call into a dangling reference to the Subject.
//
// 3. The current implementation is not thread-safe. Concurrently adding and/or
// removing callbacks or concurrently adding/removing while notifying the callbacks
// will lead to undefined behavior.
//
// CONCLUSION: Writing a stable and thread-safe implementation of the above pattern
// is not a trivial task. Have a look at Boost::Signals2 for further information.

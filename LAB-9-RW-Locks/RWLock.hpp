#ifndef __RWLOCK_HPP
#define __RWLOCK_HPP

#include <mutex>
#include <shared_mutex>

class RWLock
{
private:
    //insert here RWLock private variables
    std::shared_mutex dataMutex;

public:
    RWLock() : dataMutex()
    { }
    ~RWLock()
    { }

    void reader_lock()
    {
        dataMutex.lock_shared();
    }
    void reader_unlock()
    {
        dataMutex.unlock_shared();
    }

    void writer_lock()
    {
        dataMutex.lock();
    }
    void writer_unlock()
    {
        dataMutex.unlock();
    }

    // RWLock, as a mutex, cannot be copied
    RWLock(const RWLock &) = delete;
    RWLock & operator= (RWLock &) = delete;
    RWLock & operator= (const RWLock &) = delete;
};

#endif // __RWLOCK_HPP
//------------------------------------------------------------------------------
/*
    This file is part of GOCd: https://github.com/GOC/GOCd
    Copyright (c) 2012, 2013 GOC Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef GOC_BASICS_COUNTEDOBJECT_H_INCLUDED
#define GOC_BASICS_COUNTEDOBJECT_H_INCLUDED

#include <atomic>
#include <string>
#include <utility>
#include <vector>

namespace GOC {

/** Manages all counted object types. */
class CountedObjects
{
public:
    static CountedObjects& getInstance () noexcept;

    using Entry = std::pair <std::string, int>;
    using List = std::vector <Entry>;

    List getCounts (int minimumThreshold) const;

public:
    /** Implementation for @ref CountedObject.

        @internal
    */
    class CounterBase
    {
    public:
        CounterBase () noexcept;

        virtual ~CounterBase () noexcept;

        int increment () noexcept
        {
            return ++m_count;
        }

        int decrement () noexcept
        {
            return --m_count;
        }

        int getCount () const noexcept
        {
            return m_count.load ();
        }

        CounterBase* getNext () const noexcept
        {
            return m_next;
        }

        virtual char const* getName () const = 0;

    private:
        virtual void checkPureVirtual () const = 0;

    protected:
        std::atomic <int> m_count;
        CounterBase* m_next;
    };

private:
    CountedObjects () noexcept;
    ~CountedObjects () noexcept = default;

private:
    std::atomic <int> m_count;
    std::atomic <CounterBase*> m_head;
};

//------------------------------------------------------------------------------

/** Tracks the number of instances of an object.

    Derived classes have their instances counted automatically. This is used
    for reporting purposes.

    @ingroup GOC_basics
*/
template <class Object>
class CountedObject
{
public:
    CountedObject () noexcept
    {
        getCounter ().increment ();
    }

    CountedObject (CountedObject const&) noexcept
    {
        getCounter ().increment ();
    }

    CountedObject& operator=(CountedObject const&) noexcept = default;

    ~CountedObject () noexcept
    {
        getCounter ().decrement ();
    }

private:
    class Counter : public CountedObjects::CounterBase
    {
    public:
        Counter () noexcept { }

        char const* getName () const override
        {
            return Object::getCountedObjectName ();
        }

        void checkPureVirtual () const override { }
    };

private:
    static Counter& getCounter() noexcept
    {
        static_assert(std::is_nothrow_constructible<Counter>{}, "");
        static Counter c;
        return c;
    }
};

} // GOC

#endif
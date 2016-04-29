/******************************************************************************
*   intrusive_list.h
*   By Joshua T. Fisher
***/

/******************************************************************************
*   The MIT License (MIT)
*   Copyright (c) 2016 Joshua T. Fisher
*   
*   Permission is hereby granted, free of charge, to any person obtaining a 
*   copy of this software and associated documentation files (the "Software"), 
*   to deal in the Software without restriction, including without limitation 
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the 
*   Software is furnished to do so, subject to the following conditions:
*   
*   The above copyright notice and this permission notice shall be included in
*   all copies or substantial portions of the Software.
*   
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
*   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
*   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
*   DEALINGS IN THE SOFTWARE.
***/

#include <memory>
#include <iterator>

namespace std
{
    template <class Type, class Mode, class Allocator = std::allocator<Type>>
    class intrusive_list_hook
    {
      protected:
        using allocator_type = Allocator;
        using value_type = typename Allocator::value_type;
        using reference = typename Allocator::reference;
        using const_reference = typename Allocator::const_reference;
        using difference_type = typename Allocator::difference_type;
        using size_type = typename Allocator::size_type;

        intrusive_list_hook(intrusive_list_hook *aPrevious, intrusive_list_hook *aNext)
          : mPrevious(aPrevious), mNext(aNext)
        {

        }

        intrusive_list_hook *mPrevious;
        intrusive_list_hook *mNext;
    };

    template <class Type, class Mode, class Allocator = std::allocator<Type>>
    class intrusive_list_member_hook : instrusive_list_hook<Type, Allocator>
    {

    };

    template <class Type, class Allocator = std::allocator<Type>>
    class intrusive_list : public intrusive_list_hook<Type, Allocator>
    {
    public:
      class safe;
      class auto_unlink;
      class owning;


      ///////////////////////////////////////////////////////////////////////
      // Member Types
      ///////////////////////////////////////////////////////////////////////
      ////////////////////////////////
      // Base Types
      ////////////////////////////////
      using allocator_type = Allocator;
      using value_type = typename Allocator::value_type;
      using reference = typename Allocator::reference;
      using const_reference = typename Allocator::const_reference;
      using difference_type = typename Allocator::difference_type;
      using size_type = typename Allocator::size_type;



      ////////////////////////////////
      // Iterators
      ////////////////////////////////
      class iterator
      {
      public:
        using difference_type = typename allocator_type::difference_type;
        using value_type = typename allocator_type::value_type;
        using reference = typename allocator_type::reference;
        using pointer = typename allocator_type::pointer;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator();
        iterator(const iterator&);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        iterator& operator++();
        iterator operator++(int); //optional
        iterator& operator--(); //optional
        iterator operator--(int); //optional

        reference operator*() const;
        pointer operator->() const;
      };
      class const_iterator 
      {
      public:
        using difference_type = typename allocator_type::difference_type;
        using value_type = typename allocator_type::value_type;
        using const_reference = const typename allocator_type::reference;
        using const_pointer = const typename allocator_type::pointer;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator();
        const_iterator(const const_iterator&);
        const_iterator(const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const_iterator& operator++();
        const_iterator operator++(int); //optional
        const_iterator& operator--(); //optional
        const_iterator operator--(int); //optional

        const_reference operator*() const;
        const_pointer operator->() const;
      };

      using reverse_iterator = std::reverse_iterator<iterator>;
      using const_reverse_iterator = std::reverse_iterator<const_iterator>;




      ///////////////////////////////////////////////////////////////////////
      // Member Functions
      ///////////////////////////////////////////////////////////////////////
      intrusive_list() : intrusive_list_hook(nullptr, nullptr) 
      {
        
      }

      intrusive_list(const intrusive_list&);

      // Not implemented yet.
      ~intrusive_list()
      {

      }

      Allocator get_allocator(); //optional

      intrusive_list& operator=(const intrusive_list&);
      bool operator==(const intrusive_list&) const;
      bool operator!=(const intrusive_list&) const;
      bool operator<(const intrusive_list&) const; //optional
      bool operator>(const intrusive_list&) const; //optional
      bool operator<=(const intrusive_list&) const; //optional
      bool operator>=(const intrusive_list&) const; //optional


      ////////////////////////////////
      // Element Access
      ////////////////////////////////

      reference front(); //optional
      const_reference front() const; //optional
      reference back(); //optional
      const_reference back() const; //optional

      ////////////////////////////////
      // Iterators
      ////////////////////////////////
      iterator begin();
      const_iterator begin() const;
      const_iterator cbegin() const;
      iterator end();
      const_iterator end() const;
      const_iterator cend() const;
      reverse_iterator rbegin(); //optional
      const_reverse_iterator rbegin() const; //optional
      const_reverse_iterator crbegin() const; //optional
      reverse_iterator rend(); //optional
      const_reverse_iterator rend() const; //optional
      const_reverse_iterator crend() const; //optional


      ////////////////////////////////
      // Capacity
      ////////////////////////////////
      size_type size();
      size_type max_size();
      bool empty();

      ////////////////////////////////
      // Modifiers
      ////////////////////////////////
      void clear(); //optional

      iterator insert(const_iterator, const Type&); //optional
      iterator insert(const_iterator, Type&&); //optional
      iterator insert(const_iterator, size_type, Type&); //optional
      template<class iter>
      iterator insert(const_iterator, iter, iter); //optional
      iterator insert(const_iterator, std::initializer_list<Type>); //optional

      template<class ...Args>
      iterator emplace(const_iterator, Args...); //optional

      iterator erase(const_iterator); //optional
      iterator erase(const_iterator, const_iterator); //optional

      void push_back(const Type&); //optional
      void push_back(Type&&); //optional
      template<class ...Args>
      void emplace_back(Args...); //optional
      void pop_back(); //optional

      void push_front(const Type&); //optional
      void push_front(Type&&); //optional
      template<class ...Args>
      void emplace_front(Args...); //optional
      void pop_front(); //optional

      void swap(intrusive_list&);


      ////////////////////////////////
      // Operations
      ////////////////////////////////
      template<class iter>
      void assign(iter, iter); //optional
      void assign(std::initializer_list<Type>); //optional
      void assign(size_type, const Type&); //optional


    private:
      intrusive_list_hook *mHead;
    };
    template <class Type, class Allocator = std::allocator<Type>>
    void swap(intrusive_list<Type, Allocator> &lhs, intrusive_list<Type, Allocator> &rhs)
    {
      lhs.swap(rhs);
    }
}
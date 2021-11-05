//
// Created by samuel on 01/11/2021.
//

#ifndef FOX_PROPERTY_HPP
#define FOX_PROPERTY_HPP

#include <memory>
#include <utility>
#include <vector>
#include <functional>
#include <utility>
#include "signal.hpp"

namespace fox
{
    //region Normal Property
    template<typename T>
    class Property
    {
        using event_type = fox::signal<T>;
    public:
        // -----------------------------
        //      CONSTRUCTORS
        // -----------------------------
        Property() : m_oData() {}
        Property(const T& value) : m_oData(value) {}
        Property(T&& value) : m_oData(std::move(value)) {}


        // -----------------------------
        //      DESTRUCTOR
        // -----------------------------
        virtual ~Property() = default;

        //region Methods
        // -----------------------------
        //      GET METHODS
        // -----------------------------
        /**
         * @brief Get the data
         * @return the variable
         */
        const T& get() const
        {
            return m_oData;
        }


        // -----------------------------
        //      SET METHODS
        // -----------------------------
        /**
         * @brief Set the data
         * @param value the new value to set to the data
         */
        void set(const T& value)
        {
            if (m_oData != value)
            {
                m_oOnBeforeChange.emit(m_oData);
                m_oData = value;
                m_oOnChange.emit(m_oData);
            }
        }

        /**
         * @brief Set the data
         * @param value the new value to set to the data
         */
        void set(T&& value)
        {
            if (m_oData != value)
            {
                m_oOnBeforeChange.emit(m_oData);
                m_oData = std::move(value);
                m_oOnChange.emit(m_oData);
            }
        }

        event_type& OnBeforeChange()
        {
            return m_oOnBeforeChange;
        }

        event_type& OnChange()
        {
            return m_oOnChange;
        }

        //endregion

        //region Operators

        // -----------------------------
        //  CONVERSIONS OPERATORS
        // -----------------------------
        operator const T& () const
        {
            return get();
        }

        // -----------------------------
        //      GET OPERATORS
        // -----------------------------
        const T& operator * () const
        {
            return get();
        }

        const T& operator -> () const
        {
            return get();
        }

        // -----------------------------
        //      ASSIGNMENT OPERATORS
        // -----------------------------
        Property& operator = (const T& v)
        {
            set(v);
            return *this;
        }

        Property& operator = (T&& v)
        {
            set(std::move(v));
            return *this;
        }

        // -----------------------------
        //      COMPARATOR OPERATORS
        // -----------------------------

        // -- EQUAL
        bool operator==(const T& v) const
        {
            return get() == v;
        }

        // -- NOT EQUAL
        bool operator!=(const T& v) const
        {
            return get() != v;
        }

        // -- LESS
        bool operator<(const T& v) const
        {
            return get() < v;
        }

        // -- LESS EQUAL
        bool operator<=(const T& v) const
        {
            return get() <= v;
        }

        // -- GREATER
        bool operator>(const T& v) const
        {
            return get() > v;
        }

        // -- GREATER EQUAL
        bool operator>=(const T& v) const
        {
            return get() >= v;
        }

        // -----------------------------
        //      INCREMENT OPERATORS
        // -----------------------------

        // -- INCREMENT
        Property& operator++()
        {
            auto temp(get());
		    ++temp;
            set(std::move(temp));
            return *this;
        }

        Property operator++(int)
        {
            Property temp = *this;
            ++*this;
            return temp;
        }

        // -- DECREMENT
        Property& operator--()
        {
            auto temp(get());
            --temp;
            set(std::move(temp));
            return *this;
        }

        Property operator--(int)
        {
            Property temp = *this;
            --*this;
            return temp;
        }

        // -- ADDITION
        Property operator + (const T& v)
        {
            auto temp(get());
            return Property<T>(temp + v);
        }

        // -- ADDITION ASSIGNMENT
        Property& operator += (const T& v)
	    {
		    auto temp(get());
		    temp += v;
		    set(std::move(temp));
		    return *this;
	    }

        // -- SUBSTRACTION
        Property operator - (const T& v)
        {
            auto temp(get());
            return Property<T>(temp - v);
        }

        // -- SUBSTRACTION ASSIGNMENT
        Property& operator -= (const T& v)
        {
            auto temp(get());
            temp -= v;
            set(std::move(temp));
            return *this;
        }

        // -- MULTIPLY
        Property operator * (const T& v)
        {
            auto temp(get());
            return Property<T>(temp * v);
        }

        // -- MULTIPLY ASSIGNMENT
        Property& operator *= (const T& v)
        {
            auto temp(get());
            temp *= v;
            set(std::move(temp));
            return *this;
        }

        // -- DIVISION
        Property operator / (const T& v)
        {
            auto temp(get());
            return Property<T>(temp / v);
        }

        // -- DIVISION ASSIGNMENT
        Property& operator /= (const T& v)
        {
            auto temp(get());
            temp /= v;
            set(std::move(temp));
            return *this;
        }

        // -- MODULO
        Property operator % (const T& v)
        {
            auto temp(get());
            return Property<T>(temp % v);
        }

        // -- MODULO ASSIGNMENT
        Property& operator %= (const T& v)
        {
            auto temp(get());
            temp %= v;
            set(std::move(temp));
            return *this;
        }
        //endregion

    private:
        event_type m_oOnChange;
        event_type m_oOnBeforeChange;
        T m_oData;
    };
    //endregion

    //region std::unique Property
    template<typename T>
    class Property<std::unique_ptr<T>>
    {
        using UPtr = std::unique_ptr<T>;
        using pointer = T*;
        using event_type = fox::signal<pointer>;

    public:
        // -----------------------------
        //      CONSTRUCTORS
        // -----------------------------
        Property() : m_oData() {}
        Property(UPtr&& value) : m_oData(std::move(value)) {}


        // -----------------------------
        //      DESTRUCTOR
        // -----------------------------
        virtual ~Property() = default;

        //region Methods
        // -----------------------------
        //      GET METHODS
        // -----------------------------
        /**
         * @brief Get the data
         * @return the variable
         */
        pointer get() const
        {
            return m_oData.get();
        }


        // -----------------------------
        //      SET METHODS
        // -----------------------------

        /**
         * @brief Set the data
         * @param value the new value to set to the data
         */
        void set(UPtr&& value)
        {
            if (m_oData != value)
            {
                m_oOnBeforeChange.emit(m_oData.get());
                m_oData = std::move(value);
                m_oOnChange.emit(m_oData.get());
            }
        }

        event_type& OnBeforeChange()
        {
            return m_oOnBeforeChange;
        }

        event_type& OnChange()
        {
            return m_oOnChange;
        }

        //endregion

        //region Operators

        // -----------------------------
        //  CONVERSIONS OPERATORS
        // -----------------------------
        operator pointer () const
        {
            return get();
        }

        // -----------------------------
        //      GET OPERATORS
        // -----------------------------
        const T& operator * () const
        {
            return *get();
        }

        pointer operator -> () const
        {
            return get();
        }

        // -----------------------------
        //      ASSIGNMENT OPERATORS
        // -----------------------------
        Property& operator = (UPtr&& v)
        {
            set(std::move(v));
            return *this;
        }

        //region T Comparators Operators

        // -----------------------------
        //      COMPARATOR OPERATORS
        // -----------------------------

        // -- EQUAL
        bool operator==(const T& v) const
        {
            return *get() == v;
        }

        // -- NOT EQUAL
        bool operator!=(const T& v) const
        {
            return *get() != v;
        }

        // -- LESS
        bool operator<(const T& v) const
        {
            return *get() < v;
        }

        // -- LESS EQUAL
        bool operator<=(const T& v) const
        {
            return *get() <= v;
        }

        // -- GREATER
        bool operator>(const T& v) const
        {
            return *get() > v;
        }

        // -- GREATER EQUAL
        bool operator>=(const T& v) const
        {
            return *get() >= v;
        }
        //endregion

        //endregion

    private:
        event_type m_oOnChange;
        event_type m_oOnBeforeChange;
        UPtr m_oData;
    };
    //endregion

    template<typename T>
    inline std::istream& operator >> (std::istream& is, Property<T>& p)
    {
        auto temp(p.get());
        is >> temp;
        p.set(std::move(temp));
        return is;
    }

    template<typename T>
    inline std::ostream& operator << (std::ostream& os, const Property<T>& p)
    {
        return os << p.get();
    }
}

#endif // FOX_PROPERTY_HPP

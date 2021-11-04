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

namespace fox
{
    template<typename T>
    class Property
    {
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
            m_oData = value;
        }

        /**
         * @brief Set the data
         * @param value the new value to set to the data
         */
        void set(T&& value)
        {
            m_oData = std::move(value);
        }


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

    private:
        T m_oData;
    };


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

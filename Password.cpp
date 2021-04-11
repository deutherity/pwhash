#pragma once // since it's included in templates.hpp
#include "Password.hpp"
#include <cstring>
#include "hex.hpp"
#include "QuotedIO.hpp"

template <typename CharT>
Password<CharT>::Password(
                str_t &&service,
                const int id,
                str_t &&description
            ):
                m_service(std::move(service)),
                m_id(id),
                m_description(std::move(description))
    {}

/*
template <typename CharT>
Password<CharT>::Password(Password<CharT> && other) noexcept :
        m_service(std::move(other.m_service)),
        m_seed(other.m_seed),
        m_seedlen(other.m_seedlen),
        m_description(std::move(other.m_description)),
        m_id(other.m_id)
    {
        other.m_seed = nullptr;
        other.m_seedlen = 0;
        other.m_id = -1;
    }

template <typename CharT>
Password<CharT>::Password(const Password<CharT> & other): 
        m_service(other.m_service),
        m_seedlen(other.m_seedlen),
        m_description(other.m_description),
        m_id(other.m_id)
    {
        if (m_seedlen)
        {
            m_seed = (uchar *)std::malloc(m_seedlen);
            std::memcpy(m_seed, other.m_seed, m_seedlen);
        }
    }
*/
template <typename CharT>
Password<CharT>::~Password()
    {
        std::free(m_seed);
    }

template<typename CharT>
std::basic_istream<CharT> & operator >> (std::basic_istream<CharT> &input, Password<CharT> &that)
{
    short has_seed;
    std::string seedbuf;
    input >> that.m_id >> QuotedInput(that.m_service) >> has_seed 
    >> QuotedInput(that.m_description);
    if (has_seed)
    {
        input >> seedbuf;
        std::size_t seedlen = seedbuf.length() / 2;
        uchar *foo = (uchar *)malloc(seedlen);
        for (std::size_t i = 0; i < seedlen; ++i)
        {
            foo[i] = unhex(seedbuf.c_str() + 2 * i);
        }
        that.setSeed(foo, seedlen);
    }
    return input;
}

template<typename CharT>
std::basic_ostream<CharT> & operator << (std::basic_ostream<CharT> &output, const Password<CharT> &that)
{
    output << that.m_id  << ' ' << QuotedOutput<CharT>(that.m_service) << ' ' << ((that.m_seedlen)?1:0) << '\n';
    output << QuotedOutput<CharT>(that.m_description);
    if (that.m_seedlen)
    {
        output.put('\n');
        hexByte chars;
        const uchar * seed = that.getSeed();
        for (std::size_t i = 0; i < that.m_seedlen; ++i)
        {
            chars = hex(seed[i]);
            output.put(chars.h);
            output.put(chars.t);
        }
    }
    return output;
}

template <typename CharT>
void Password<CharT>::setSeed(const uchar * t_seed, const std::size_t t_seedlen)
{
    std::free(m_seed);
    this->m_seed = (uchar *)std::malloc(t_seedlen);
    this->m_seedlen = t_seedlen;
    std::memcpy(this->m_seed, t_seed, t_seedlen);
}

template <typename CharT>
void Password<CharT>::moveSeed(uchar * t_seed, const std::size_t t_seedlen)
{
    std::free(m_seed);
    this->m_seed = t_seed;
    this->m_seedlen = t_seedlen;
}

template <typename CharT>
const uchar *Password<CharT>::getSeed() const
{
    return this->m_seed;
}
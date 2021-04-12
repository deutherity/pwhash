#pragma once
#include "const_pwhash.hpp"
#include <istream>
#include <ostream>
#include <string>
#include <string_view>

template <typename CharT = char> struct Password {
  private:
    uchar *m_seed = nullptr;

  public:
    typedef std::basic_string<CharT> str_t;
    str_t m_service;
    std::size_t m_seedlen = 0;
    int m_id = -1;
    str_t m_description;

    Password() = default;
    Password(str_t &&service, const int id, str_t &&description = "");
    Password(Password &&other) noexcept;
    Password(const Password &other) = default;
    ~Password();

    Password &operator=(Password<CharT> &&other) noexcept;
    Password &operator=(const Password<CharT> &other) = default;
    const uchar *getSeed() const;
    void setSeed(const uchar *t_seed, const std::size_t t_seedlen);
    void moveSeed(uchar *t_seed, const std::size_t t_seedlen);
    bool valid() const { return m_id != -1; }
    std::string cook(const std::basic_string_view<CharT> &realpwd) const;
};

template <typename CharT>
std::basic_istream<CharT> &operator>>(std::basic_istream<CharT> &input,
                                      const Password<CharT> &that);

template <typename CharT>
std::basic_ostream<CharT> &operator<<(std::basic_ostream<CharT> &output,
                                      const Password<CharT> &that);
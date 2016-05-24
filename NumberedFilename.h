#pragma once

#include <string>
#include <cctype>
#include <vector>

class NumberedFilename {
public:
    NumberedFilename(const std::string& basename) {
        std::string remains = basename;
        int sentry = remains.size()-1;

        while (sentry >= 0 && remains[sentry] != '.' && remains[sentry] != '\\' && remains[sentry] != '/') { sentry--; }
        if (sentry >= 0 && remains[sentry] == '.') {
            m_postfix = remains.substr(sentry);
            remains = remains.substr(0, sentry);
        }

        sentry = remains.size() - 1;
        while (sentry >= 0 && std::isdigit(remains[sentry])) { sentry--; }
        m_numlen = remains.size() - sentry - 1;
        if (m_numlen > 0) {
            sscanf(remains.c_str() + sentry + 1, "%d", &m_numstart);
            m_prefix = remains.substr(0, sentry+1);
        }
        else {
            m_prefix = remains;
            m_numstart = 0;
        }
    }

    std::string operator() (int i) const {
        std::string result = std::to_string(m_numstart + i);
        if (result.size() < m_numlen) {
            while (result.size() < m_numlen) {
                result = '0' + result;
            }
        }
        else if (result.size() > m_numlen) {
            result = result.substr(result.size() - m_numlen);
        }
        return m_prefix + result + m_postfix;
    }

private:
    std::string m_prefix;
    std::string m_postfix;
    int m_numstart;
    int m_numlen;
};

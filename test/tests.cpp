#include <catch2/catch_all.hpp>
#include <kyrename.hpp>

TEST_CASE("remove_accents", "[remove_accents]")
{
    struct TestCase
    {
        std::wstring str;
        std::wstring expected;
    };

    SECTION("empty string")
    {
        TestCase test_case{L"", L""};
        std::wstring actual = ky::remove_accents(test_case.str);
        REQUIRE(actual == test_case.expected);
    }

    SECTION("string without accents")
    {
        TestCase test_cases[] = {
            {L"Hello, world!", L"Hello, world!"},
            {L"abcdefghijklmnopqrstuvwxyz", L"abcdefghijklmnopqrstuvwxyz"},
            {L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
            {L"0123456789", L"0123456789"},
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
            {L" \t\n\r\f\v", L" \t\n\r\f\v"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::remove_accents(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

    SECTION("string with accents")
    {
        TestCase test_cases[] = {
            {L"ÁÀÃÂÄÅ", L"AAAAAA"},
            {L"áàãâäå", L"aaaaaa"},
            {L"ÉÈÊË", L"EEEE"},
            {L"éèêë", L"eeee"},
            {L"ÍÌÎÏ", L"IIII"},
            {L"íìîï", L"iiii"},
            {L"ÓÒÕÔÖØ", L"OOOOOO"},
            {L"óòõôöø", L"oooooo"},
            {L"ÚÙÛÜ", L"UUUU"},
            {L"úùûü", L"uuuu"},
            {L"Ç", L"C"},
            {L"ç", L"c"},
            {L"Ñ", L"N"},
            {L"ñ", L"n"},
            {L"Ÿ", L"Y"},
            {L"ÿ", L"y"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::remove_accents(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

    SECTION("string with mixed accents and non-accents")
    {
        TestCase test_cases[] = {
            {L"ÁaÀbÃcÂdÄeÅf", L"AaAbAcAdAeAf"},
            {L"áaàbãcâdäeåf", L"aaabacadaeaf"},
            {L"ÉaÈbÊcËd", L"EaEbEcEd"},
            {L"éaèbêcëd", L"eaebeced"},
            {L"ÍaÌbÎcÏd", L"IaIbIcId"},
            {L"íaìbîcïd", L"iaibicid"},
            {L"ÓaÒbÕcÔdÖeØf", L"OaObOcOdOeOf"},
            {L"óaòbõcôdöeøf", L"oaobocodoeof"},
            {L"ÚaÙbÛcÜd", L"UaUbUcUd"},
            {L"úaùbûcüd", L"uaubucud"},
            {L"Ça", L"Ca"},
            {L"ça", L"ca"},
            {L"Ña", L"Na"},
            {L"ña", L"na"},
            {L"Ÿa", L"Ya"},
            {L"ÿa", L"ya"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::remove_accents(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

} // remove_accents

TEST_CASE("to_lower", "[to_lower]")
{
    struct TestCase
    {
        std::wstring str;
        std::wstring expected;
    };

    SECTION("empty string")
    {
        TestCase test_case{L"", L""};
        std::wstring actual = ky::to_lower(test_case.str);
        REQUIRE(actual == test_case.expected);
    }

    SECTION("string without uppercase characters")
    {
        TestCase test_cases[] = {
            {L"hello, world!", L"hello, world!"},
            {L"abcdefghijklmnopqrstuvwxyz", L"abcdefghijklmnopqrstuvwxyz"},
            {L"0123456789", L"0123456789"},
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
            {L" \t\n\r\f\v", L" \t\n\r\f\v"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::to_lower(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

    SECTION("string with uppercase characters")
    {
        TestCase test_cases[] = {
            {L"Hello, world!", L"hello, world!"},
            {L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", L"abcdefghijklmnopqrstuvwxyz"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::to_lower(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

    SECTION("string with mixed uppercase, lowercase characters and non-alphabetic characters")
    {
        TestCase test_cases[] = {
            {L"Hello, world!", L"hello, world!"},
            {L"AbCdEfGhIjKlMnOpQrStUvWxYz", L"abcdefghijklmnopqrstuvwxyz"},
            {L"0A1b2C3d4E5f6G7h8I9j", L"0a1b2c3d4e5f6g7h8i9j"},
            {L"!\"#aEa$%bIb&'cOc(dUd)Ee*+fRf,gHg-hIh.iJi/jKj:kLk;lMl<mNn=nOn>oPo?qRr@sTs[Tt\\Uu]u^Vv`Ww{Xx|Yy}Zz~", L"!\"#aea$%bib&'coc(dud)ee*+frf,ghg-hih.iji/jkj:klk;lml<mnn=non>opo?qrr@sts[tt\\uu]u^vv`ww{xx|yy}zz~"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::to_lower(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

} // to_lower

TEST_CASE ("to_alphanum", "[to_alphanum]")
{
    struct TestCase
    {
        std::wstring str;
        std::wstring expected;
    };

    SECTION("empty string")
    {
        TestCase test_case{L"", L""};
        std::wstring actual = ky::to_alphanum(test_case.str, L'_');
        REQUIRE(actual == test_case.expected);
    }

    SECTION("string with only alphanumeric characters")
    {
        TestCase test_cases[] = {
            {L"abcdefghijklmnopqrstuvwxyz", L"abcdefghijklmnopqrstuvwxyz"},
            {L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
            {L"0123456789", L"0123456789"},
            {L"_", L"_"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::to_alphanum(test_case.str, L'_');
            REQUIRE(actual == test_case.expected);
        }
    }

    SECTION("string with non-alphanumeric characters")
    {
        TestCase test_cases[] = {
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", L"_"},
            {L" \t\n\r\f\v", L""},
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\f\v", L"_"},
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\f\v abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", L"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::to_alphanum(test_case.str, L'_');
            REQUIRE(actual == test_case.expected);
        }
    }
} // to_alphanum

TEST_CASE("normalize_separator", "[normalize_separator]")
{
    struct TestCase
    {
        std::wstring str;
        wchar_t separator;
        std::wstring separators_to_replace;
        std::wstring expected;
    };

    SECTION("empty string")
    {
        TestCase test_case{L"", L'_', L"", L""};
        std::wstring actual = ky::normalize_separator(test_case.str, test_case.separator);
        REQUIRE(actual == test_case.expected);
    }

    SECTION("string without separators")
    {
        TestCase test_cases[] = {
            {L"abcdefghijklmnopqrstuvwxyz", L'_', L"", L"abcdefghijklmnopqrstuvwxyz"},
            {L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", L'_', L"", L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
            {L"0123456789", L'_', L"", L"0123456789"},
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", L'_', L"", L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
            {L" \t\n\r\f\v", L'_', L"", L" \t\n\r\f\v"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::normalize_separator(test_case.str, test_case.separator, test_case.separators_to_replace);
            REQUIRE(actual == test_case.expected);
        }
    }

    SECTION("string with separators")
    {
        TestCase test_cases[] = {
            {L"abcdefghijklmnopqrstuvwxyz", L'_', L" ,.?;:[]{}|()-_", L"abcdefghijklmnopqrstuvwxyz"},
            {L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", L'_', L" ,.?;:[]{}|()-_", L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
            {L"0123456789", L'_', L" ,.?;:[]{}|()-_", L"0123456789"},
            {L"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", L'_', L" ,.?;:[]{}|()-_", L"!\"#$%&'_*+_/_<=>_@_\\_^_`_~"},
            {L" \t\n\r\f\v", L'_', L" ,.?;:[]{}|()-_", L"\t\n\r\f\v"},
            {L" abcd efgh ijkl mnop qrst uvwx yz ", L'_', L" ,.?;:[]{}|()-_", L"abcd_efgh_ijkl_mnop_qrst_uvwx_yz"},
            {L"  0123 4567 89  ", L'_', L" ,.?;:[]{}|()-_", L"0123_4567_89"},
        };

        for (auto const &test_case : test_cases)
        {
            std::wstring actual = ky::normalize_separator(test_case.str, test_case.separator, test_case.separators_to_replace);
            REQUIRE(actual == test_case.expected);
        }
    }
} // normalize_separator

    
            
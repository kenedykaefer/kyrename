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
        std::wstring actual = remove_accents(test_case.str);
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
            std::wstring actual = remove_accents(test_case.str);
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
            std::wstring actual = remove_accents(test_case.str);
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
            std::wstring actual = remove_accents(test_case.str);
            REQUIRE(actual == test_case.expected);
        }
    }

} // remove_accents